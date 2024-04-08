#--------------------------------------------------------------------
# @file    config.rb
# @author  Martin Corino
#
# @brief   DDSX11 facet configuration
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL
  module CCMX11
    module DDSX11
      COPYRIGHT = "Copyright (c) 2007-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
      TITLE = 'RIDL DDS Facet'.freeze

      def self.add_extended_options(ol)
        ol.for_switch '-G{generation options}', type: String, separator: true do |swcfg|
          swcfg.for_group :ddsx11_group do |grpcfg|
            grpcfg.on_prepare do |arg, params|
              if /^ddsx11\,(.*)/ =~ arg
                return [::Regexp.last_match(1)]
              end

              nil
            end
            grpcfg.modify_params :strings,
              params: {
                'traits' => {
                  option_name: :gen_user_defined_type_traits_for_dds,
                  description: "-Gddsx11,traits\t\tGenerate user defined conversion traits for DDSX11 (not generated by default)"
                },
                'idds' => {
                  option_name: :gen_idl_for_dds,
                  description: "-Gddsx11,idds\t\tGenerate the IDL file for DDSX11 (_dds.idl) (not generated by default)"
                },
                'ite' => {
                  option_name: :gen_idl_for_typed_entities,
                  description: "-Gddsx11,ite\t\tGenerate the IDL file for a DDSX11 typed datareader and datawriter (not generated by default)"
                },
                'its' => {
                  option_name: :gen_impl_for_type_support,
                  description: "-Gddsx11,its\t\tGenerate the implementation files for the DDSX11 type support (not generated by default)"
                },
                'adds' => {
                  option_name: :gen_all_dds_related_files,
                  description: "-Gddsx11,adds\t\tGenerate all DDSX11 related files (not generated by default)"
                }
             }
          end
        end
      end # add_extended_options

      ## Configure facet
      #
      Backend::Facet.configure('dds', File.dirname(__FILE__), TITLE, COPYRIGHT, IDL::CCMX11.ciaox11_version) do |fctcfg|
        # setup facet option handling
        #
        fctcfg.on_setup do |optlist, ridl_params|
          ridl_params[:dds_typesupport_pfx] = '_dds_typesupport'
          ridl_params[:dds_typed_entities_pfx] = '_dds_typed_entities'
          ridl_params[:dds_idl_pfx] = '_dds'
          ridl_params[:dds_traits_pfx] = '_dds_traits'

          IDL::CCMX11::DDSX11.add_extended_options(optlist)
        end

        # process input / generate code
        # arguments:
        #   in parser - parser object with full AST from parsed source
        #   in options - initialized option hash
        #
        fctcfg.on_process_input do |parser, options|
          idl_ext = (options.idlext ||= File.extname(options.idlfile))

          options.dds_idl_file_base = File.basename(options.idlfile, idl_ext) + options[:dds_idl_pfx]

          if options.gen_all_dds_related_files
            options.gen_user_defined_type_traits_for_dds = true
            options.gen_idl_for_dds = true
            options.gen_idl_for_typed_entities = true
            options.gen_impl_for_type_support = true
          end

          IDL::CCMX11::DDSX11.prepare_dds_options(options, idl_ext)

          if options.gen_idl_for_dds
            IDL::CCMX11::DDSX11.gen_idl_for_dds(options, idl_ext)
          end

          if options.gen_idl_for_typed_entities
            IDL::CCMX11::DDSX11.gen_idl_for_typed_entities(options, idl_ext)
          end

          if options.gen_impl_for_type_support
            IDL::CCMX11::DDSX11.gen_impl_for_type_support(options, idl_ext)
          end

          if options.gen_user_defined_type_traits_for_dds
            IDL::CCMX11::DDSX11.gen_user_defined_type_traits_for_dds(options, idl_ext)
          end
        end
      end # configure

      #
      # set all output files so that files can be correctly included
      #
      def self.prepare_dds_options(options, idl_ext)
        options.dds_udt_header_file_base =
          File.basename(options.idlfile, idl_ext) + options.dds_traits_pfx
      end

      #########################################################################
      ## DDS types IDL generation
      ##

      #
      # generate the IDL file which will be supplied to the DDS generator
      #
      def self.gen_idl_for_dds(options, idl_ext)
        dds_gen_idl_file = GenFile.new(File.join(options.outputdir,
                                                 options.dds_idl_file_base + idl_ext))

        # schedule dds IDL generation
        IDL.push_production(:dds_idl, ::IDL::CCMX11::DDSX11::DDSIDLWriter.new(dds_gen_idl_file, options))
      end

      #########################################################################
      ## DDSX11 typed entities generation
      ##

      #
      # generate the IDL file and it's stubs for a typed datareader and typed datawriter.
      #
      def self.gen_idl_for_typed_entities(options, idl_ext)
        options.dds_typed_entities_idl_file =
          File.join(options.outputdir,
            File.basename(options.idlfile, idl_ext) + options.dds_typed_entities_pfx + idl_ext)

        dds_typed_entities_idl_file = GenFile.new(options.dds_typed_entities_idl_file)

        # schedule dds typed entities IDL generation
        IDL.push_production(:dds_typed_entities_idl,
            ::IDL::CCMX11::DDSX11::DDSTypeEntitiesIDLWriter.new(dds_typed_entities_idl_file, options))

        # restore new (clean) options set for new input processing pass
        entities_opts = options.restore
        # keep core option values (like include paths, macros and such)
        entities_opts.copy!(options, IDL::CORE_OPTIONS)

        # copy needed export settings
        entities_opts.copy!(options,
                      :base_export_include, :base_export_macro,
                      :stub_export_include, :stub_export_macro, :stub_export_file,
                      :gen_any_ops, :gen_typecodes, :gen_localintf_any_ops,
                      :gen_ostream_operators, :no_cdr_streaming)

        # now get the resulting IDL file and schedule a parsing pass
        # generating only the stub files without a stub proxy
        entities_opts.svnt_skeletons = false
        entities_opts.no_client_proxy_hdr = true
        # Disable the generation of typecode and any support, it is not
        # used by ddsx11
        entities_opts.gen_typecodes = false
        entities_opts.gen_any_ops = false
        entities_opts.gen_localintf_any_ops = false
        entities_opts.idlfile = options.dds_typed_entities_idl_file
        IDL.push_input(options.dds_typed_entities_idl_file, entities_opts)
      end

      #########################################################################
      ## DDSX11 type support generation
      ##

      def self.check_typesupport_export_params(options)
        options.typesupport_export_macro = options.base_export_macro + "_TYPESUPPORT" + options.export_macro_pfx unless options.typesupport_export_macro || options.base_export_macro.nil?
        options.typesupport_export_include = options.base_export_include + "_typesupport" + options.export_header_pfx unless options.typesupport_export_include || options.base_export_include.nil?
      end

      def self.gen_typesupport_export(options, prefix = nil)
        return if IDL.has_production?(:typesupport_export_header)

        export_file = options.typesupport_export_include
        unless options.typesupport_export_file.nil?
          export_file = options.typesupport_export_file
        end
        if export_file
          so = GenFile.new(File.join(options.outputdir, export_file))
          IDL.push_production(
              :exec_export_header,
              ::IDL::Cxx11::ExportHeaderWriter.new(options.typesupport_export_macro, export_file, so, options))
        end
      end

      #
      # generate the header and implementation for the type support.
      #
      def self.gen_impl_for_type_support(options, idl_ext)
        options.dds_typesupport_header_file =
          File.join(options.outputdir,
            File.basename(options.idlfile, idl_ext) + options.dds_typesupport_pfx + options.hdr_ext)
        options[:dds_typesupport_source_file] =
          File.join(options.outputdir,
            File.basename(options[:idlfile], idl_ext) + options[:dds_typesupport_pfx] + options.src_ext)

        dds_typesupport_header_file = GenFile.new(options.dds_typesupport_header_file)
        dds_typesupport_source_file = GenFile.new(options.dds_typesupport_source_file)

        # check export directive parameters for derived generations
        check_typesupport_export_params (options)
        gen_typesupport_export (options)

        # schedule type support header
        IDL.push_production(:dds_typesupport_header_file,
            ::IDL::CCMX11::DDSX11::DDSTypeSupportHeaderWriter.new(dds_typesupport_header_file, options))

        # schedule type support source
        IDL.push_production(:dds_typesupport_source_file,
            ::IDL::CCMX11::DDSX11::DDSTypeSupportSourceWriter.new(dds_typesupport_source_file, options))
      end

      #
      # generate the conversion traits for the user defined types
      #
      def self.gen_user_defined_type_traits_for_dds(options, idl_ext)
        dds_traits_file = GenFile.new(File.join(options.outputdir,
                                                options.dds_udt_header_file_base + options.hdr_ext))

        # schedule dds type traits generation
        IDL.push_production(:dds_type_traits,
                            ::IDL::CCMX11::DDSX11::UserDefinedTypeTraitsWriter.new(dds_traits_file, options))
      end
    end # DDSX11
  end # CCMX11
end # IDL

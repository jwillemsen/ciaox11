#--------------------------------------------------------------------
# @file    config.rb
# @author  Martin Corino
#
# @brief   IDL language mapping configuration
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------


module IDL

  module CCMX11
    COPYRIGHT = "Copyright (c) 2007-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
    TITLE = 'RIDL CCMX11 backend'.freeze


    def self.add_extended_options(ol)
      # IMPORTANT When these flags are updated also update the docs/src/ridlc.adoc
      # which is used for our user documentation
      ol.for_switch '-W<extended option>=OPT', :type => String, :separator => true do |swcfg|
        swcfg.modify_group :b_extopt do |grpcfg|
          grpcfg.modify_params :strings,
            :params => {
              'exec_export_macro' => {:description => "-Wb,exec_export_macro=MACRO\tSet export macro for executor files"},
              'exec_export_include' => {:description => "-Wb,exec_export_include=FILE\tSet export include file for executor files"},
              'exec_export_file' => {:description => "-Wb,exec_export_file=FILE\t\tSet skeleton export file to generate for -Gxhex"},
              'conn_export_macro' => {:description => "-Wb,conn_export_macro=MACRO\tSet export macro for connector files"},
              'conn_export_include' => {:description => "-Wb,conn_export_include=FILE\tSet export include file for connector files"},
              'conn_export_file' => {:description => "-Wb,conn_export_file=FILE\t\tSet connector export file to generate for -Gxhcn"},
              'svnt_export_macro' => {:description => "-Wb,svnt_export_macro=MACRO\tSet export macro for servant files"},
              'svnt_export_include' => {:description => "-Wb,svnt_export_include=FILE\tSet export include file for servant files"},
              'svnt_export_file' => {:description => "-Wb,svnt_export_file=FILE\t\tSet servant export file to generate for -Ghst"},
              'lem_stub_export_macro' => {:description => "-Wb,lem_stub_export_macro=MACRO\tSet export macro for lem stub files"},
              'lem_stub_export_include' => {:description => "-Wb,lem_stub_export_include=FILE\tSet export include file for lem stub files"},
              'lem_stub_export_file' => {:description => "-Wb,lem_stub_export_file=FILE\tSet lem stub export file to generate for -Gxhlst"}
            }
        end
      end

      ol.for_switch '-G{generation options}', :type => String, :separator => true do |swcfg|
        swcfg.modify_group :gen_flags,
          :params => {
            'xhex' => { :option_name => :gen_export_ex,
                     :description => "-Gxhex\t\t\tGenerate export header for component executor (not generated by default)" },
            'xhsv' => { :option_name => :gen_export_svnt,
                     :description => "-Gxhsv\t\t\tGenerate export header for component servant (not generated by default)" },
            'comp' => { :option_name => :gen_comp_complete,
                     :description => "-Gcomp\t\t\tGenerate all files needed for an user component" },
            'svnt' => { :option_name => :gen_component_servant,
                     :description => "-Gsvnt\t\t\tGenerate the component servant source code (not generated by default)" },
            'ex' => { :option_name => :gen_component_executor,
                     :description => "-Gex\t\t\t(Re)generate the component executor starter code (not generated by default)" },
            'cn' => { :option_name => :gen_templated_connector_impl,
                     :description => "-Gcn\t\t\tGenerate files needed for a (templated) connector" },
            'xhcn' => { :option_name => :gen_export_conn,
                     :description => "-Gxhcn\t\t\tGenerate export header for connector executor (not generated by default)" },
            'xhlst' => { :option_name => :gen_export_lem_stub,
                     :description => "-Gxhlst\t\t\tGenerate export header for lem stubs (not generated by default)" },
          }
        swcfg.for_group :lem_group do |grpcfg|
              grpcfg.on_prepare do |arg, params|
                if /^lem(\,(.*))?/ =~ arg
                  return [$2 || ':']
                end
                nil
              end
              grpcfg.for_params :strings,
              :params => {
                ':'    => { :option_name => :gen_lem,
                        :description => "-Glem\t\t\tGenerate the CCM local executor IDL" },
                'gen'  => { :option_name => :gen_lem_gen,
                        :description => "-Glem,gen\t\t\tGenerate all files needed for the CCM local executor mapping" },
              }
        end
      end

      ol.for_switch '-X{export options}', :type => String, :separator => true do |swcfg|
        swcfg.modify_group :export_flags, :params => {
              'ex' => { :option_name => :export_ex,
                       :description => "-Xex\t\t\tExport component executor code (not exported by default)" },
              'sv' => { :option_name => :export_svnt,
                       :description => "-Xsv\t\t\tExport component servant code (not exported by default)" },
              'cn' => { :option_name => :export_conn,
                       :description => "-Xcn\t\t\tExport connector executor code (not exported by default)" },
              'lst' => { :option_name => :export_lem_stub,
                       :description => "-Xlst\t\t\tExport lem stub code (not exported by default)" },
            }
      end
    end # add_extended_options

    class << self

      VERSION_REGEXP = /\#\s*define\s+CIAOX11_(\w+)_VERSION\s+(\d+)/

      def determine_ciaox11_version
        x11_version = {
          :major => 0,
          :minor => 0,
          :micro => 0
        }

        base = File.join(File.dirname(__FILE__), '..', '..', 'ciaox11', 'versionx11.h')
        File.open(base, "r") do |file|
          while (line = file.gets)
            if VERSION_REGEXP =~ line
              x11_version[$1.downcase.to_sym] = $2.to_i
            end
          end
        end
        x11_version[:release] ||= x11_version[:micro]
        x11_version
      end # determine_ciaox11_version
      private :determine_ciaox11_version

      def ciaox11_version
        @ciaox11_version ||= determine_ciaox11_version
      end
    end

    ## Configure C++11 backend
    #
    Backend.configure('ccmx11', File.dirname(__FILE__), TITLE, COPYRIGHT, IDL::CCMX11.ciaox11_version) do |becfg|

      # load c++11 backend as base
      becfg.add_backend('c++11')

      # setup backend option handling
      #
      becfg.on_setup do |optlist, ridl_params|
        # defaults
        ridl_params[:gen_lem] = false
        ridl_params[:gen_lem_gen] = false
        ridl_params[:gen_component_servant] = false
        ridl_params[:gen_component_executor] = false
        ridl_params[:gen_templated_connector_impl] = false
        ridl_params[:gen_comp_complete] = false

        ridl_params[:svnt_impl_pfx] = '_svnt'
        ridl_params[:comp_exec_pfx] = '_exec'
        ridl_params[:conn_exec_pfx] = '_conn'
        ridl_params[:lem_pfx] = 'E'
        ridl_params[:ciaox11_version] = becfg.backend.instance_variable_get(:@version)
        ridl_params[:ciaox11_title] = TITLE

        IDL::CCMX11.add_extended_options(optlist)
      end

      # process input / generate code
      # arguments:
      #   in parser - parser object with full AST from parsed source
      #   in options - initialized option hash
      #
      becfg.on_process_input do |parser, options|
        # determine IDL file extension if not yet done
        idl_ext = (options[:idlext] ||= File.extname(options[:idlfile]))

        # This composite option must be handled before any of the other, simple, options
        # since it enables some of those in this pass and schedules others for a next
        # input pass
        # Generate all files for a component
        if options[:gen_comp_complete]
          IDL::CCMX11.gen_component_complete(options, idl_ext)
        end

        if options[:gen_lem_gen]
          IDL::CCMX11.gen_lem_gen(options, idl_ext)
        end

        if options[:gen_export_ex]
          IDL::CCMX11.gen_exec_export(options)
        end

        if options[:gen_export_svnt]
          IDL::CCMX11.gen_svnt_export(options)
        end

        if options[:gen_export_conn]
          IDL::CCMX11.gen_conn_export(options)
        end

        # Generate lem implementation
        if options[:gen_lem]
           IDL::CCMX11.gen_lem_idl(options, idl_ext)
        end

        # before gen_corba_connector since this changes the IDL file name
        if options[:gen_component_executor]
          IDL::CCMX11.gen_component_executor(options, idl_ext)
        end

        if options[:gen_templated_connector_impl]
          IDL::CCMX11.gen_templated_connector_impl(options, idl_ext)
        end

        # svnt generation
        if options[:gen_component_servant]
          IDL::CCMX11.gen_component_servant(options, idl_ext)
        end

     end # becfg.on_process_input

    end # Backend.configure

    #################################################################
    # Export macros/includes handling

    def self.check_executor_export_params(options, prefix = nil, force = false)
      if options.gen_export_ex || options.export_ex || force
        unless options.exec_export_macro || options.base_export_macro
          IDL.fatal("ERROR: it isn't allowed to use -Gxhex or -Xex without specifying the macro with -Wb,exec_export_macro=MACRO " +
                        'or with -Wb,base_export_macro=MACRO_PREFIX')
        end
        # only in case export header generation has been explicitly enabled will
        # we derive missing export parameters from base parameters
        options.exec_export_macro = options.base_export_macro + "#{(prefix || '').upcase}_EXEC" + options.export_macro_pfx unless options.base_export_macro.nil? || options.exec_export_macro
        options.exec_export_include = options.base_export_include + "#{prefix}_exec" + options.export_header_pfx unless options.base_export_include.nil? || options.exec_export_include
      end
    end

    def self.check_servant_export_params(options, prefix = nil, force = false)
      if options.gen_export_svnt || options.export_svnt || force
        unless options.svnt_export_macro || options.base_export_macro
          IDL.fatal("ERROR: it isn't allowed to use -Gxhsv or -Xsv without specifying the macro with -Wb,svnt_export_macro=MACRO " +
                        'or with -Wb,base_export_macro=MACRO_PREFIX')
        end
        # only in case export header generation has been explicitly enabled will
        # we derive missing export parameters from base parameters
        options.svnt_export_macro = options.base_export_macro + "#{(prefix || '').upcase}_SVNT" + options.export_macro_pfx unless options.base_export_macro.nil? || options.svnt_export_macro
        options.svnt_export_include = options.base_export_include + "#{prefix}_svnt" + options.export_header_pfx unless options.base_export_include.nil? || options.svnt_export_include
      end
    end

    def self.check_lem_stub_export_params(options, prefix = nil)
      # there is no separate gen_lem_stub_export parameter but rather these parameters
      # are used to overwrite regular stub parameters for stub generation from implicitly
      # generated LEM IDL;
      # set the export headers and macros for a component if possible unless already set
      options.lem_stub_export_macro = options.base_export_macro + "#{(prefix || '').upcase}_LEM_STUB" + options.export_macro_pfx unless options.base_export_macro.nil? || options.lem_stub_export_macro
      options.lem_stub_export_include = options.base_export_include + "#{prefix}_lem_stub" + options.export_header_pfx unless options.base_export_include.nil? || options.lem_stub_export_include
    end

    def self.check_conn_export_params(options, prefix = nil, force = false)
      if options.gen_export_conn || options.export_conn || force
        unless options.conn_export_macro || options.base_export_macro
          IDL.fatal("ERROR: it isn't allowed to use -Gxhcn or -Xcn without specifying the macro with -Wb,conn_export_macro=MACRO " +
                        'or with -Wb,base_export_macro=MACRO_PREFIX')
        end
        # only in case export header generation has been explicitly enabled will
        # we derive missing export parameters from base parameters
        options.conn_export_macro = options.base_export_macro + "#{(prefix || '').upcase}_CONN" + options.export_macro_pfx unless options.base_export_macro.nil? || options.conn_export_macro
        options.conn_export_include = options.base_export_include + "#{prefix}_conn" + options.export_header_pfx unless options.base_export_include.nil? || options.conn_export_include
      end
    end

    #################################################################
    # export header generation

    def self.gen_exec_export(options, prefix = nil)
      return if IDL.has_production?(:exec_export_header)
      check_executor_export_params(options, prefix, true)
      export_file = options[:exec_export_include]
      unless options[:exec_export_file].nil?
        export_file = options[:exec_export_file]
      end
      if export_file
        so = GenFile.new(File.join(options.outputdir, export_file))
        IDL.push_production(
            :exec_export_header,
            ::IDL::Cxx11::ExportHeaderWriter.new(options[:exec_export_macro], export_file, so, options))
      end
    end

    def self.gen_svnt_export(options, prefix = nil)
      return if IDL.has_production?(:svnt_export_header)
      check_servant_export_params(options, prefix, true)
      export_file = options[:svnt_export_include]
      unless options[:svnt_export_file].nil?
        export_file = options[:svnt_export_file]
      end
      if export_file
        so = GenFile.new(File.join(options.outputdir, export_file))
        IDL.push_production(
            :svnt_export_header,
            ::IDL::Cxx11::ExportHeaderWriter.new(options[:svnt_export_macro], export_file, so, options))
      end
    end

    def self.gen_conn_export(options, prefix = nil)
      return if IDL.has_production?(:conn_export_header)
      check_conn_export_params(options, prefix, true)
      export_file = options[:conn_export_include]
      unless options[:conn_export_file].nil?
        export_file = options[:conn_export_file]
      end
      if export_file
        so = GenFile.new(File.join(options.outputdir, export_file))
        IDL.push_production(
            :conn_export_header,
            ::IDL::Cxx11::ExportHeaderWriter.new(options[:conn_export_macro], export_file, so, options))
      end
    end

    #################################################################
    # LEM IDL handling

    # setup an input processing pass for the (possibly to be generated beforehand)
    # LEM idl file which will generate the LEM stubs and (optionally) export
    # header
    def self.compile_lem_idl(options, idl_ext)
      # only once per pass
      unless options[:compile_lem_idl_scheduled]
        # Check the command line options regarding export macros. Set the correct
        # macros if a base_export_macro/include is defined.
        check_lem_stub_export_params(options)

        impl_opts = setup_compile_lem_idl(options, idl_ext)

        IDL.push_input(impl_opts[:idlfile], impl_opts)

        # set this for derived backends/facets to detect
        options[:compile_lem_idl_scheduled] = true
      end
    end

    # initialize an options set for LEM idl processing pass
    def self.setup_compile_lem_idl(options, idl_ext)
      # new options set for new input processing pass
      impl_opts = options.restore # restore copy of default (clean) options
      # keep core option values (like include paths, macros and such)
      impl_opts.copy!(options, IDL::CORE_OPTIONS)
      impl_opts.copy!(options, :gen_ostream_operators)
      # set new input file to LEM IDL file created in preceding pass
      impl_opts[:idlfile] = IDL::CCMX11.lem_output_file(options[:idlfile], options, idl_ext)

      # Only (lem) stub and lem_stub_export file have to be generated from lem idl file
      impl_opts[:svnt_skeletons] = false
      # no proxy required for local interfaces only
      impl_opts[:no_client_proxy] = true
      # suppress CDR support for local interfaces only
      impl_opts[:no_cdr_streaming] = true
      # suppress Any and Typecode support for (local) code generation
      impl_opts[:gen_typecodes] = false
      impl_opts[:gen_any_ops] = false

      # do we need to generate an export header and directives for the lem stub?
      # use lem_stub_export for stub generated of lem idl
      if options.lem_stub_export_macro
        impl_opts.stub_export_macro = options.lem_stub_export_macro
      else
        impl_opts.stub_export_macro = options.stub_export_macro if options.stub_export_macro
      end
      if options.lem_stub_export_include
        impl_opts.stub_export_include = options.lem_stub_export_include
      else
        impl_opts.stub_export_include = options.stub_export_include if options.stub_export_include
      end
      if options.lem_stub_export_file
        impl_opts.stub_export_file = options.lem_stub_export_file
      else
        impl_opts.stub_export_file = options.stub_export_file if options.stub_export_file
      end
      if options.gen_export_lem_stub
        impl_opts.gen_export_st = true
      end
      if options.export_lem_stub
        impl_opts.export_st = true
      end
      impl_opts
    end

    # determine the LEM idl out-/input file name
    def self.lem_output_file(base, options, idl_ext)
      options[:lem_outputdir] = options.outputdir unless options[:lem_outputdir]
      options[:lem_output_file] = File.join(options[:lem_outputdir], File.basename(base, idl_ext ) + options[:lem_pfx] + idl_ext)
    end

    # schedule a generation (production) of the LEM idl
    def self.gen_lem_idl(options, idl_ext)
      return if IDL.has_production?(:lem_idl)
      IDL::CCMX11.lem_output_file(options[:idlfile], options, idl_ext)
      lem_idl_file = GenFile.new(options[:lem_output_file])

      IDL.push_production(
          :lem_idl,
          ::IDL::CCMX11::LemExecutor::IDLWriter.new(lem_idl_file, options))
    end

    #################################################################
    # component combi switches

    # This method drives 2 input processing passes:
    # 1. the current (main) pass processing the base IDL file passed on the command line
    #    - during this pass the following generators (productions) are scheduled
    #       I) xxx_svnt.* generation (component context&executor locator)
    #      II) xxxE.idl (component LEM)
    # 2. processing the xxxE.idl file generated in the first pass
    #    - during this pass the following generators (productions) are scheduled:
    #       I) xxxEC.* generation (component lem stubs)
    #      II) export header for xxxEC code (optional; depends on -Gxhlst / -Gxhex / -Gxhsv)
    #
    def self.gen_component_complete(options, idl_ext)
      # reset; do this only once
      options[:gen_comp_complete] = false
      # generate LEM idl later on this pass
      options[:gen_lem] = true
      # generate component servant later on this pass
      options[:gen_component_servant] = true
      # set this for derived backends/facets to detect
      options[:gen_comp_complete_scheduled] = true

      # Check the command line options regarding export macros. Set the correct
      # macros if a base_export_macro/include is defined and the corresponding -GxhXX
      check_executor_export_params(options)
      check_servant_export_params(options)

      # generate lem stub exports if either executor or servant exports are specified
      options.gen_export_lem_stub ||= options.gen_export_ex || options.gen_export_svnt
      self.compile_lem_idl(options, idl_ext)
    end

    # This method drives 2 input processing passes:
    # 1. the current (main) pass processing the base IDL file passed on the command line
    #    - during this pass the following generators (productions) are scheduled
    #      II) xxxE.idl (component LEM)
    # 2. processing the xxxE.idl file generated in the first pass
    #    - during this pass the following generators (productions) are scheduled:
    #       I) xxxEC.* generation (component lem stubs)
    #      II) export header for xxxEC code (optional; depends on -Gxhlst / -Gxhst)
    #
    def self.gen_lem_gen(options, idl_ext)
      options[:gen_lem] = true
      options[:gen_lem_gen] = false

      # if not set explicitly but -Gxhst is than assume -Gxhlst is as well
      options.gen_export_lem_stub ||= options.gen_export_st
      # if not set explicitly but -Xst is than assume -Xlst is as well
      options.export_lem_stub ||= options.export_st
      self.compile_lem_idl(options, idl_ext)
    end

    #################################################################
    # component part generation

    # schedule the generation (production) of the Component Executor code
    # (header and source file)
    def self.gen_component_executor(options, idl_ext)
      return if IDL.has_production?(:comp_exec_header)
      unless options[:impl_outputdir].nil?
        options[:comp_exec_outputdir] = options[:impl_outputdir]
      else
        options[:comp_exec_outputdir] = options.outputdir unless options[:comp_exec_outputdir]
      end
      options[:comp_exec_output_hdr] = File.join(options[:comp_exec_outputdir], File.basename(options[:idlfile], idl_ext) + options[:comp_exec_pfx])
      options[:comp_exec_output_src] = options[:comp_exec_output_hdr] + options.src_ext
      options[:comp_exec_output_hdr] += options.hdr_ext

      check_executor_export_params(options) # TODO : remove this |, nil, true)  # force checks/init since exports are implicitly enabled

      if options[:suppress_regen]
        comp_exec_h = GenFile.new(options[:comp_exec_output_hdr], :regenerate => false)
        comp_exec_src = GenFile.new(options[:comp_exec_output_src], :regenerate => false)
      else
        comp_exec_h = GenFile.new(options[:comp_exec_output_hdr], :regenerate => true, :regen_keep_header => true)
        comp_exec_src = GenFile.new(options[:comp_exec_output_src], :regenerate => true, :regen_keep_header => true)
      end

      IDL.push_production(
          :comp_exec_header,
          ::IDL::CCMX11::ComponentExecutor::HeaderWriter.new(comp_exec_h, options))
      IDL.push_production(
          :comp_exec_source,
          ::IDL::CCMX11::ComponentExecutor::SourceWriter.new(comp_exec_src, options))
    end

    # schedule the generation (production) of a templated Connector Executor
    # implementation (header and source file)
    def self.gen_templated_connector_impl(options, idl_ext)
      return if IDL.has_production?(:templated_conn_impl_header)
      options[:conn_exec_outputdir] = options.outputdir unless options[:conn_exec_outputdir]
      options[:conn_exec_output_hdr] = File.join(options[:conn_exec_outputdir], File.basename(options[:idlfile], idl_ext) + options[:conn_exec_pfx])
      options[:conn_exec_output_src] = options[:conn_exec_output_hdr] + options.src_ext
      options[:conn_exec_output_hdr] += options.hdr_ext

      conn_exec_h = GenFile.new(options[:conn_exec_output_hdr])
      conn_exec_src = GenFile.new(options[:conn_exec_output_src])

      IDL.push_production(
          :templated_conn_impl_header,
          ::IDL::CCMX11::TemplatedConnectorImplHeaderWriter.new(conn_exec_h, options))
      IDL.push_production(
          :templated_conn_impl_source,
          ::IDL::CCMX11::TemplatedConnectorImplSourceWriter.new(conn_exec_src, options))
    end

    # schedule the generation (production) of a Facet or Component Servant
    # implementation (header and source)
    def self.gen_svnt_facets_or_components(options, idl_ext, facet=true)
      # for generating facet svnt's and component svnt's the same writer is used.
      # only the output_dir may differ .
      #svnt files
      if facet
        options[:svntcomp_output] = File.join(options[:conn_outputdir], File.basename(options[:idlfile], idl_ext) +
                                    options[:svnt_impl_pfx])
      else
        options[:svntcomp_output] = File.join(options[:svntcomp_outputdir], File.basename(options[:idlfile], idl_ext) +
                                    options[:svnt_impl_pfx])
      end

      options[:svntcomp_output_src] = options[:svntcomp_output] + options.src_ext
      options[:svntcomp_output_h] = options[:svntcomp_output] + options.hdr_ext

      check_servant_export_params(options)

      svntc_h = GenFile.new(options[:svntcomp_output_h])
      svntc_src = GenFile.new(options[:svntcomp_output_src])

      IDL.push_production(
          :comp_svnt_header,
          ::IDL::CCMX11::SvntComponent::HeaderWriter.new(svntc_h, options))
      IDL.push_production(
          :comp_svnt_source,
          ::IDL::CCMX11::SvntComponent::SourceWriter.new(svntc_src, options))
    end

    # schedule the generation (production) of a Component Servant
    # implementation (header and source)
    def self.gen_component_servant(options, idl_ext)
      return if IDL.has_production?(:comp_svnt_header)
      # generate component servants (xxx_svnt.{h,cpp})
      options[:svntcomp_outputdir] = options.outputdir unless options[:svntcomp_outputdir]
      gen_svnt_facets_or_components(options, idl_ext, false)
    end

  end # CCMX11

end # IDL

# config modules
Dir.glob(File.join(File.dirname(__FILE__), 'config', '*.rb')).each do |f|
  require File.join('ridlbe', 'ccmx11', 'config', File.basename(f, '.*'))
end

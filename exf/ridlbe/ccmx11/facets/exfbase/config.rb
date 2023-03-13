#--------------------------------------------------------------------
# @file    config.rb
# @author  Martin Corino
#
# @brief   RIDL backend facet configuration for ExF base
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------


module IDL

  module CCMX11

    module ExFBase
      COPYRIGHT = "Copyright (c) 2007-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
      TITLE = 'RIDL AXCIOMA ExF Base Facet'.freeze

      ## Configure facet
      #
      Backend::Facet.configure('exfbase', File.dirname(__FILE__), TITLE, COPYRIGHT, {major: 0, minor: 1, release: 1}) do |fctcfg|

        def self.add_extended_options(ol)
          ol.for_switch '-G{generation options}', :type => String, :separator => true do |swcfg|
            swcfg.modify_group :exf_group,
              :params => {
                'ExF' => { :option_name => :gen_exf_support,
                           :description => "-GExF\t\t\tGenerate support for the AXCIOMA Execution Framework (not generated by default)" }
              }
          end
        end # add_extended_options

        # setup backend option handling
        #
        fctcfg.on_setup do |optlist, ridl_params|
          ridl_params.gen_exf_support = false
          ExFBase.add_extended_options(optlist)
        end

        # process input / generate code
        # arguments:
        #   in parser - parser object with full AST from parsed source
        #   in options - initialized option hash
        #
        fctcfg.on_process_input do |parser, options|

        end # fctcfg.on_process_input
      end # configure facet

    end  # ExF4Base

  end # CCMX11

end # IDL

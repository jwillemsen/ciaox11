#--------------------------------------------------------------------
# @file    udttraits_extensions.rb
# @author  Martin Corino
#
# @brief   DDS4NDDS extensions for udt traits generation
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module IDL
  module CCMX11
    module DDSX11
      module NDDS
        module UserDefinedTypeTraitsWriterExt
          def self.configure_extension(writer)
            IDL.log(3, 'Configuring DDS4NDDS UserDefinedTypeTraitsWriterExt extension')
            # make writer look for templates in ndds folder first
            writer.template_root = File.join(writer.template_root, 'ndds')
          end
        end
      end # NDDS
    end # DDSX11
  end # CCMX11
end # IDL

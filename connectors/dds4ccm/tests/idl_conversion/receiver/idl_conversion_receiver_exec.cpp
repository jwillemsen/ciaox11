// -*- C++ -*-
/**
 * @file    idl_conversion_receiver_exec.cpp
 * @author  Marcel Smit
 *
 * @brief   Receiver component implementation of the IDL conversion test.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : idl_conversion_receiver_impl.cpp[Header]

#include "idl_conversion_receiver_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl[user_includes]
#include "dds4ccm/logger/dds4ccm_testlog.h"
//@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl[user_global_impl]

namespace IDL_Conversion_Test_Receiver_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl[user_namespace_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : info_out_data_listener_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[ctor]
  info_out_data_listener_exec_i::info_out_data_listener_exec_i (
      IDL::traits<IDL_Conversion_Test::CCM_Receiver_Context>::ref_type context,
      std::atomic_ulong &samples_received)
    : context_ (std::move (context))
    , samples_received_ (samples_received)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[ctor]

  info_out_data_listener_exec_i::~info_out_data_listener_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]
  void
  info_out_data_listener_exec_i::check_datum (
    const ::Example::IDLConversionMessage& datum)
  {
    /// Check b_57 [Example::B57 (std::vector < std::string>)]
    uint16_t c = 0;
    for (const std::string &val : datum.b_57 ())
    {
      const std::string expected ("VALUE_"+std::to_string (datum.iteration() + c));
      if (val != expected)
      {
        if (!val.empty ())
        {
          if (val.back() == 0)
          {
            DDS4CCM_TEST_ERROR << "Receiver check - ERROR: last character of "
              << "datum.b_57[" << c << "] is 0"  << std::endl;
          }
        }
        DDS4CCM_TEST_ERROR << "Receiver check - ERROR: unexpected value for "
          << "datum.b_57[" << c << "]: expected <" << expected << "> - got <"
          << val << ">" << std::endl;
      }
      ++c;
    }
  }
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i[user_private_ops]


  /** Operations and attributes from info_out_data_listener */

  void
  info_out_data_listener_exec_i::on_one_data (
      const ::Example::IDLConversionMessage& datum,
      const ::CCM_DDS::ReadInfo& info)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
    X11_UNUSED_ARG(info);

    ++this->samples_received_;
    this->check_datum (datum);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i::on_one_data[_datum_info]
  }

  void
  info_out_data_listener_exec_i::on_many_data (
      const ::Example::IDLConversionMessageSeq& data,
      const ::CCM_DDS::ReadInfoSeq& infos)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
    X11_UNUSED_ARG(data);
    X11_UNUSED_ARG(infos);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_data_listener_exec_i::on_many_data[_data_infos]
  }
  /**
   * Facet Executor Implementation Class : info_out_status_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[ctor]
  info_out_status_exec_i::info_out_status_exec_i (
    IDL::traits<IDL_Conversion_Test::CCM_Receiver_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[ctor]

  info_out_status_exec_i::~info_out_status_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i[user_private_ops]


  /** Operations and attributes from info_out_status */

  void
  info_out_status_exec_i::on_requested_deadline_missed (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::RequestedDeadlineMissedStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i::on_requested_deadline_missed[_the_reader_status]
  }

  void
  info_out_status_exec_i::on_sample_lost (
      IDL::traits<::DDS::DataReader>::ref_type the_reader,
      const ::DDS::SampleLostStatus& status)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
    X11_UNUSED_ARG(the_reader);
    X11_UNUSED_ARG(status);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::info_out_status_exec_i::on_sample_lost[_the_reader_status]
  }

  /**
   * Component Executor Implementation Class : Receiver_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ctor]
  Receiver_exec_i::Receiver_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ctor]

  Receiver_exec_i::~Receiver_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[user_private_ops]

  /** Session component operations */
  void Receiver_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
    DDS4CCM_TEST_DEBUG << "Receiver_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[configuration_complete]
  }

  void Receiver_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
    IDL::traits<::CCM_DDS::DataListenerControl>::ref_type lc =
      this->context_->get_connection_info_out_data_control ();

    if (!lc)
    {
      DDS4CCM_TEST_ERROR << "Error:  Listener control receptacle is null!"
        << std::endl;
      throw ::CORBA::INTERNAL ();
    }
    lc->mode (::CCM_DDS::ListenerMode::ONE_BY_ONE);
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ccm_activate]
  }

  void Receiver_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
    if (this->samples_received_ != 300)
    {
      DDS4CCM_TEST_ERROR << "ERROR: Receiver_exec_i::ccm_passivate - "
        << "Unexpected number of samples received. Expected <300> - received <"
        << this->samples_received_ << ">." << std::endl;
    }
    else
    {
      DDS4CCM_TEST_DEBUG << "Receiver_exec_i::ccm_passivate - OK: "
        "<" << this->samples_received_ << "> samples received" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ccm_passivate]
  }

  void Receiver_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[ccm_remove]
  }

  IDL::traits<::Example::IDLConversionTestConnector::CCM_Listener>::ref_type
  Receiver_exec_i::get_info_out_data_listener ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
    if (!this->info_out_data_listener_)
      {
        this->info_out_data_listener_ = CORBA::make_reference <info_out_data_listener_exec_i> (
          this->context_, this->samples_received_);
      }
    return this->info_out_data_listener_;
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[get_info_out_data_listener]
  }

  IDL::traits<::CCM_DDS::CCM_PortStatusListener>::ref_type
  Receiver_exec_i::get_info_out_status ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[get_info_out_status]
    if (!this->info_out_status_)
      {
        this->info_out_status_ = CORBA::make_reference <info_out_status_exec_i> (this->context_);
      }
    return this->info_out_status_;
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[get_info_out_status]
  }

  /// Operations from Components::SessionComponent
  void
  Receiver_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
    this->context_ = IDL::traits<IDL_Conversion_Test::CCM_Receiver_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i[set_session_context]
  }


  //@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl[user_namespace_end_impl]

} // namespace IDL_Conversion_Test_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : IDL_Conversion_Test_Receiver_Impl[factory]
extern "C" void
create_IDL_Conversion_Test_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <IDL_Conversion_Test_Receiver_Impl::Receiver_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : IDL_Conversion_Test_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : idl_conversion_receiver_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-

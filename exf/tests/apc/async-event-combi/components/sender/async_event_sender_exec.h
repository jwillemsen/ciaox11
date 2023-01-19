// -*- C++ -*-
/**
 * @file    async_event_sender_exec.h
 * @author  Marijke Hengstmengel
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef __RIDL_ASYNC_EVENT_SENDER_EXEC_H_IEJCIBEJ_INCLUDED__
#define __RIDL_ASYNC_EVENT_SENDER_EXEC_H_IEJCIBEJ_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : async_event_sender_impl.h[Header]

#pragma once

#include "async_event_senderEC.h"

#include /**/ "async_event_sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : async_event_sender_impl.h[user_includes]
#include "ace/Task.h"
//@@{__RIDL_REGEN_MARKER__} - END : async_event_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : async_event_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : async_event_sender_impl.h[user_global_decl]

#include "helloAC.h"

/// Namespace for implementation of Hello::Sender component
namespace Hello_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_decl]
  /// Worker thread for asynchronous invocations
  class asynch_foo_generator final : public ACE_Task_Base
  {
  public:
    asynch_foo_generator() = default;
    void set_context(IDL::traits<Hello::CCM_Sender_Context>::ref_type context);
    int svc() override;

  private:
    IDL::traits<Hello::CCM_Sender_Context>::ref_type ciao_context_;
  };
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_decl]


  /// Executor implementation class for connector_status facet
  class connector_status_exec_i final
    : public IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::connector_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    connector_status_exec_i (
        IDL::traits< ::Hello::CCM_Sender_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::connector_status_exec_i[ctor]

    /// Destructor
    ~connector_status_exec_i () override;

    /** @name Operations from ::CCM_DDS::CCM_ConnectorStatusListener */
    //@{

    void
    on_inconsistent_topic (
        IDL::traits< ::DDS::Topic>::ref_type the_topic,
        const ::DDS::InconsistentTopicStatus& status) override;

    void
    on_requested_incompatible_qos (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedIncompatibleQosStatus& status) override;

    void
    on_sample_rejected (
        IDL::traits< ::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleRejectedStatus& status) override;

    void
    on_offered_deadline_missed (
        IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
        const ::DDS::OfferedDeadlineMissedStatus& status) override;

    void
    on_offered_incompatible_qos (
        IDL::traits< ::DDS::DataWriter>::ref_type the_writer,
        const ::DDS::OfferedIncompatibleQosStatus& status) override;

    void
    on_unexpected_status (
        IDL::traits< ::DDS::Entity>::ref_type the_entity,
        ::DDS::StatusKind status_kind) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::connector_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::connector_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::Hello::CCM_Sender_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::connector_status_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::connector_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::connector_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::connector_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits< ::Hello::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    ~Sender_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the connector_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::ref_type get_connector_status () override;
    //@}

    /** @name Supported attributes. */
    //@{

    /// Attribute rate
    uint16_t rate () override;
    void rate (uint16_t rate) override;

    /// Attribute iterations
    uint16_t iterations () override;
    void iterations (uint16_t iterations) override;

    /// Attribute keys
    uint16_t keys () override;
    void keys (uint16_t keys) override;
    //@}

    /** @name Session component operations */
    //@{

    /// Setter for container context for this component
    /// @param[in] ctx Component context
    void set_session_context (IDL::traits<Components::SessionContext>::ref_type ctx) override;

    /// Component state change method to configuration_complete state
    void configuration_complete () override;

    /// Component state change method to activated state
    void ccm_activate () override;

    /// Component state change method to passivated state
    void ccm_passivate () override;

    /// Component state change method to removed state
    void ccm_remove () override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_public_ops]
    void tick ();
    void cancel_timer ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::Hello::CCM_Sender_Context>::ref_type context_;

    /** @name Component attributes. */
    //@{
    /// Class member storing value of rate attribute
    uint16_t rate_{};
    /// Class member storing value of iterations attribute
    uint16_t iterations_{};
    /// Class member storing value of keys attribute
    uint16_t keys_{};
    //@}

    /** @name Component facets. */
    //@{
    IDL::traits< ::CCM_DDS::CCM_ConnectorStatusListener>::ref_type connector_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_members]
    asynch_foo_generator asynch_foo_gen_;
    ::DDS::InstanceHandle_t instance_handle_ { ::DDS::HANDLE_NIL };
    Hello::ShapeType square_ {"GREEN", 25, 25, 24};
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Sender_exec_i(const Sender_exec_i&) = delete;
    Sender_exec_i(Sender_exec_i&&) = delete;
    Sender_exec_i& operator=(const Sender_exec_i&) = delete;
    Sender_exec_i& operator=(Sender_exec_i&&) = delete;
    //@}
  };
  /// AMI4CCM reply handler implementation class
  class AMI4CCM_MyFooReplyHandler_run_my_foo_i final
    :public IDL::traits< Hello::AMI4CCM_MyFooReplyHandler>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]
    AMI4CCM_MyFooReplyHandler_run_my_foo_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]

    ~AMI4CCM_MyFooReplyHandler_run_my_foo_i () override;

    void foo (
        int32_t ami_return_val,
        const std::string& answer) override;

    void foo_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;
    void hello (
        int32_t answer) override;

    void hello_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;


    void get_rw_attrib(int16_t _rw_attrib) override;
    void get_rw_attrib_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    void set_rw_attrib() override;
    void set_rw_attrib_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    void get_ro_attrib(int16_t _ro_attrib) override;
    void get_ro_attrib_excep (IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder) override;

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
    //@}
  private:
    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_end_decl]

} // namespace Hello_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[factory]
extern "C" ASYNC_EVENT_SENDER_EXEC_Export  void
create_Hello_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : async_event_sender_impl.h[Footer]

#endif /* __RIDL_ASYNC_EVENT_SENDER_EXEC_H_IEJCIBEJ_INCLUDED__ */

// Your footer (code) here
// -*- END -*-
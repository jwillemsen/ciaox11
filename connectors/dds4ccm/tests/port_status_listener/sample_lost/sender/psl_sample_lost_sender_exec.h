// -*- C++ -*-
/**
 * @file    psl_sample_lost_sender_exec.h
 * @author  Marcel Smit
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_PSL_SAMPLE_LOST_SENDER_EXEC_H_EDACJABH_INCLUDED__
#define __RIDL_PSL_SAMPLE_LOST_SENDER_EXEC_H_EDACJABH_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : psl_sample_lost_sender_impl.h[Header]

#pragma once

#include "psl_sample_lost_senderEC.h"

#include /**/ "sender_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : psl_sample_lost_sender_impl.h[user_includes]
//@@{__RIDL_REGEN_MARKER__} - END : psl_sample_lost_sender_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : psl_sample_lost_sender_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : psl_sample_lost_sender_impl.h[user_global_decl]

/// Namespace for implementation of PSL_SampleLostTest::Sender component
namespace PSL_SampleLostTest_Sender_Impl
{
  /// Forward declarations
  class Sender_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl[user_namespace_decl]


  /// Executor implementation class for connector_status facet
  class connector_status_exec_i final
    : public IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    connector_status_exec_i (
        IDL::traits<PSL_SampleLostTest::CCM_Sender_Context>::ref_type context,
        IDL::traits<PSL_SampleLostTest::CCM_Sender>::weak_ref_type component_executor);
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[ctor]

    /// Destructor
    ~connector_status_exec_i () override;

    /** @name Operations from ::CCM_DDS::CCM_ConnectorStatusListener */
    //@{

    void
    on_inconsistent_topic (
        IDL::traits<::DDS::Topic>::ref_type the_topic,
        const ::DDS::InconsistentTopicStatus& status) override;

    void
    on_requested_incompatible_qos (
        IDL::traits<::DDS::DataReader>::ref_type the_reader,
        const ::DDS::RequestedIncompatibleQosStatus& status) override;

    void
    on_sample_rejected (
        IDL::traits<::DDS::DataReader>::ref_type the_reader,
        const ::DDS::SampleRejectedStatus& status) override;

    void
    on_offered_deadline_missed (
        IDL::traits<::DDS::DataWriter>::ref_type the_writer,
        const ::DDS::OfferedDeadlineMissedStatus& status) override;

    void
    on_offered_incompatible_qos (
        IDL::traits<::DDS::DataWriter>::ref_type the_writer,
        const ::DDS::OfferedIncompatibleQosStatus& status) override;

    void
    on_unexpected_status (
        IDL::traits<::DDS::Entity>::ref_type the_entity,
        ::DDS::StatusKind status_kind) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits<::PSL_SampleLostTest::CCM_Sender_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[user_members]
    bool started_ {};

    IDL::traits<PSL_SampleLostTest::CCM_Sender>::weak_ref_type component_executor_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::connector_status_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Sender_exec_i
  class Sender_exec_i final
    : public virtual IDL::traits<::PSL_SampleLostTest::CCM_Sender>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[ctor]
    /// Constructor
    Sender_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[ctor]
    /// Destructor
    ~Sender_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the connector_status facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::ref_type get_connector_status () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[user_public_ops]
    void start_publishing ();
    void tick ();
    void check_status ();
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits<::PSL_SampleLostTest::CCM_Sender_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits<::CCM_DDS::CCM_ConnectorStatusListener>::ref_type connector_status_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[user_members]
    //long ticker_id_ { -1 };
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_;
    IDL::traits<CCM_TT::TT_Timer>::ref_type tm_activate_;
    IDL::traits<CCM_TT::TT_Scheduler>::ref_type tt_s;
    bool already_publishing_ {};

    int32_t iteration_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl::Sender_exec_i[user_private_ops]
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

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl[user_namespace_end_decl]

} // namespace PSL_SampleLostTest_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : PSL_SampleLostTest_Sender_Impl[factory]
extern "C" SENDER_EXEC_Export  void
create_PSL_SampleLostTest_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : PSL_SampleLostTest_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : psl_sample_lost_sender_impl.h[Footer]

#endif /* __RIDL_PSL_SAMPLE_LOST_SENDER_EXEC_H_EDACJABH_INCLUDED__ */

// Your footer (code) here
// -*- END -*-

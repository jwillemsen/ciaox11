// -*- C++ -*-
/**
 * @file    uses_s_m_receiver_exec.h
 * @author  Marijke Hengstmengel
 *
 * @brief   receiver of ami4ccm test with combination of uses multiple and simplex
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#ifndef __RIDL_USES_S_M_RECEIVER_EXEC_H_IICCCEEF_INCLUDED__
#define __RIDL_USES_S_M_RECEIVER_EXEC_H_IICCCEEF_INCLUDED__

//@@{__RIDL_REGEN_MARKER__} - HEADER_END : uses_s_m_receiver_impl.h[Header]

#pragma once

#include "uses_s_m_receiverEC.h"

#include /**/ "uses_s_m_receiver_exec_export.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : uses_s_m_receiver_impl.h[user_includes]
// Your includes here
//@@{__RIDL_REGEN_MARKER__} - END : uses_s_m_receiver_impl.h[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : uses_s_m_receiver_impl.h[user_global_decl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : uses_s_m_receiver_impl.h[user_global_decl]

/// Namespace for implementation of UsesSM::Receiver component
namespace UsesSM_Receiver_Impl
{
  /// Forward declarations
  class Receiver_exec_i;

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl[user_namespace_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl[user_namespace_decl]


  /// Executor implementation class for do_my_one facet
  class do_my_one_exec_i final
    : public IDL::traits< ::UsesSM::CCM_One>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_one_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    do_my_one_exec_i (
        IDL::traits< UsesSM::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_one_exec_i[ctor]

    /// Destructor
    ~do_my_one_exec_i () override;

    /** @name Operations from ::UsesSM::CCM_One */
    //@{

    int32_t
    foo (
        const std::string& in_str,
        int32_t cmd,
        std::string& answer) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_one_exec_i[user_public_ops]
    inline
    uint32_t get_nr_received ()
    {
      return this->nr_of_one_received_;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_one_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::UsesSM::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_one_exec_i[user_members]
    uint32_t nr_of_one_received_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_one_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_one_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_one_exec_i[user_private_ops]
    //@}
  };

  /// Executor implementation class for do_my_two facet
  class do_my_two_exec_i final
    : public IDL::traits< ::UsesSM::CCM_Two>::base_type
  {
  public:

    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_two_exec_i[ctor]
    /// Constructor
    /// @param[in] context Component context
    do_my_two_exec_i (
        IDL::traits< UsesSM::CCM_Receiver_Context>::ref_type context);
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_two_exec_i[ctor]

    /// Destructor
    ~do_my_two_exec_i () override;

    /** @name Operations from ::UsesSM::CCM_Two */
    //@{

    void
    bar (
        int32_t cmd,
        std::string& answer) override;
    //@}

    /** @name User defined public operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_two_exec_i[user_public_ops]
    uint32_t get_nr_received ()
    {
      return this->nr_of_two_received_;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_two_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance. Used for all middleware communication.
    IDL::traits< ::UsesSM::CCM_Receiver_Context>::ref_type context_;

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_two_exec_i[user_members]
     uint32_t nr_of_two_received_ {};
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_two_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::do_my_two_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::do_my_two_exec_i[user_private_ops]
    //@}
  };

  /// Component Executor Implementation Class : Receiver_exec_i
  class Receiver_exec_i final
    : public virtual IDL::traits< ::UsesSM::CCM_Receiver>::base_type
  {
  public:
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[ctor]
    /// Constructor
    Receiver_exec_i ();
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[ctor]
    /// Destructor
    ~Receiver_exec_i () override;

    /** @name Component port operations. */
    //@{

    /// Factory method and getter for the do_my_one facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::UsesSM::CCM_One>::ref_type get_do_my_one () override;
    /// Factory method and getter for the do_my_two facet
    /// @return existing instance of facet if one exists, else creates one
    IDL::traits< ::UsesSM::CCM_Two>::ref_type get_do_my_two () override;
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
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[user_public_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[user_public_ops]
    //@}

  private:
    /// Context for component instance.
    IDL::traits< ::UsesSM::CCM_Receiver_Context>::ref_type context_;

    /** @name Component facets. */
    //@{
    IDL::traits< ::UsesSM::CCM_One>::ref_type do_my_one_;
    IDL::traits< ::UsesSM::CCM_Two>::ref_type do_my_two_;
    //@}

    /** @name User defined members. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[user_members]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[user_members]
    //@}

    /** @name User defined private operations. */
    //@{
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl::Receiver_exec_i[user_private_ops]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl::Receiver_exec_i[user_private_ops]
    //@}

  private:
    /** @name Illegal to be called. Deleted explicitly to let the compiler detect any violation */
    //@{
    Receiver_exec_i(const Receiver_exec_i&) = delete;
    Receiver_exec_i(Receiver_exec_i&&) = delete;
    Receiver_exec_i& operator=(const Receiver_exec_i&) = delete;
    Receiver_exec_i& operator=(Receiver_exec_i&&) = delete;
    //@}
  };

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl[user_namespace_end_decl]
  //@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl[user_namespace_end_decl]

} // namespace UsesSM_Receiver_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : UsesSM_Receiver_Impl[factory]
extern "C" USES_S_M_RECEIVER_EXEC_Export  void
create_UsesSM_Receiver_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component);
//@@{__RIDL_REGEN_MARKER__} - END : UsesSM_Receiver_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : uses_s_m_receiver_impl.h[Footer]

#endif /* __RIDL_USES_S_M_RECEIVER_EXEC_H_IICCCEEF_INCLUDED__ */

// Your footer (code) here
// -*- END -*-

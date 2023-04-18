// -*- C++ -*-
/**
 * @file    hello_sender_exec.cpp
 * @author  Marijke Hengstmengel
 *
 * @brief   Sender component exec
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
//@@{__RIDL_REGEN_MARKER__} - HEADER_END : hello_sender_impl.cpp[Header]

#include "hello_sender_exec.h"

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_includes]
#include "ciaox11/logger/log.h"
#include "ciaox11/testlib/ciaox11_testlog.h"
#include <thread>
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_includes]

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_global_impl]
// Your declarations here
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_global_impl]

namespace Hello_Sender_Impl
{
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_impl]
  void HandleException (
      int32_t id,
      const std::string& error_string,
      const std::string& func)
  {
    CIAOX11_TEST_INFO << "Sender:\t->HandleException id:  "
                      << id << " error_string: " << error_string
                      << "func: " << func << std::endl;
    if (id != 42)
      {
        CIAOX11_TEST_ERROR << "ERROR exception " << func
                           << ":\tReceived unexpected ID <"
                           << id << "> received" << std::endl;
      }
    else if (error_string != "Hello world")
      {
      CIAOX11_TEST_ERROR <<"ERROR exception  " << func
                         << ":\tReceived unexpected error string <"
                         <<  error_string << "> in except handler." << std::endl;
      }
  }

  void HandleException (
      IDL::traits<::CCM_AMI::ExceptionHolder>::ref_type excep_holder,
      const std::string& func)
  {
    CIAOX11_TEST_INFO << "Sender:\t->HandleException "
                      << "func: " << func << std::endl;

    if (!excep_holder)
    {
      CIAOX11_TEST_ERROR << "HandleException - ERROR - received null exception holder " << std::endl;
    }

    try
    {
      excep_holder->raise_exception ();
    }
    catch (const Hello::InternalError& ex)
    {
      CIAOX11_TEST_INFO << "Sender: Caught the correct except type : "
                        << ex.id() << " , " <<  ex.error_string() << std::endl;
      HandleException (ex.id(), ex.error_string(), func);
    }
    catch (const std::exception& e)
    {
      CIAOX11_TEST_ERROR << "HandleException - ERROR - unexpected exception caught: "
                         << e << std::endl;
    }
  }
  //============================================================
  // Worker thread for asynchronous invocations for MyFoo
  //============================================================
  void
  asynch_foo_generator::set_context(
     IDL::traits<Hello::CCM_Sender_Context>::ref_type context)
  {
    this->context_ = IDL::traits<Hello::CCM_Sender_Context>::narrow (std::move(context));
  }

  int asynch_foo_generator::svc()
  {
    try
    {
      std::this_thread::sleep_for (std::chrono::seconds (3));
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                        << std::endl;

      IDL::traits<::Hello::AMI4CCM_MyFoo>::ref_type my_foo_ami_  =
         context_->get_connection_sendc_run_my_foo();

      if (!my_foo_ami_)
      {
        CIAOX11_TEST_INFO << "Sender:\t->get_connection_sendc_run_my_foo "
                          << "returns null" << std::endl;
        return 1;
      }
        IDL::traits<Hello::AMI4CCM_MyFooReplyHandler>::ref_type cb =
           CORBA::make_reference<AMI4CCM_MyFooReplyHandler_run_my_foo_i> (this->comp_exec_);

      my_foo_ami_->sendc_foo (cb,"Do something asynchronous");
      my_foo_ami_->sendc_foo (cb,"");
      my_foo_ami_->sendc_hello (cb);
      my_foo_ami_->sendc_get_rw_attrib(cb);
      my_foo_ami_->sendc_get_rw_attrib(cb);
      my_foo_ami_->sendc_set_rw_attrib(cb, 15);
      my_foo_ami_->sendc_set_rw_attrib(cb, 0);
      my_foo_ami_->sendc_get_ro_attrib(cb);
      my_foo_ami_->sendc_get_ro_attrib(cb);
      my_foo_ami_->sendc_hello (cb);

      CIAOX11_TEST_INFO << "Sender (ASYNCH) :\tInvoked Asynchronous calls" << std::endl;
    }
    catch (const CORBA::Exception& ex)
    {
      CIAOX11_TEST_PANIC << "Sender (ASYNCH) :\tCAUGHT CORBA EXCEPTION [" << ex << "]" << std::endl;
    }
    catch (const std::exception& ex)
    {
      CIAOX11_TEST_PANIC << "Sender (ASYNCH) :\tCAUGHT EXCEPTION [" << ex << "]" << std::endl;
    }
    catch (...)
    {
      CIAOX11_TEST_PANIC << "Sender (ASYNCH) :\tCAUGHT UNKNOWN EXCEPTION" << std::endl;
    }
    return 0;
  }

  //============================================================
  // Worker thread for synchronous invocations for MyFoo
  //============================================================
  void
  synch_foo_generator::set_context(
     IDL::traits<Hello::CCM_Sender_Context>::ref_type context)
  {
    this->context_ = IDL::traits<Hello::CCM_Sender_Context>::narrow (std::move(context));
  }
  int synch_foo_generator::svc ()
  {
    try
    {
      std::this_thread::sleep_for (std::chrono::seconds (3));
      CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo " << std::endl;
      IDL::traits<Hello::MyFoo>::ref_type my_foo_ =
          this->context_->get_connection_run_my_foo();
      if (!my_foo_)
      {
        CIAOX11_TEST_INFO << "Sender:\t->get_connection_run_my_foo "
                          << "returns null" << std::endl;
      }

      try {
        //run synch call
        int32_t answer {};
        my_foo_->hello (answer);
        CIAOX11_TEST_INFO << "Sender:\tsynch hello <" << answer << ">" << std::endl;
      }
      catch (const Hello::InternalError&) {
        CIAOX11_TEST_INFO << "Sender:\tsynch hello get expected exception "
                         << std::endl;
      }

      try {
        my_foo_->rw_attrib(15);
        int16_t const ret  = my_foo_->ro_attrib();
        CIAOX11_TEST_INFO << "Sender:\tsynch get ro_attrib <" << ret << ">" << std::endl;
      }
      catch (const Hello::InternalError&) {
        CIAOX11_TEST_INFO << "Sender:\tsynch ro_attrib get expected exception "
                         << std::endl;
      }

      try {
        //run synch call
        int32_t answer {};
        my_foo_->hello (answer);
        CIAOX11_TEST_INFO << "Sender:\tsynch hello <" << answer << ">" << std::endl;
      }
      catch (const Hello::InternalError&) {
        CIAOX11_TEST_INFO << "Sender:\tsynch hello get expected exception "
                         << std::endl;
      }
    }
    catch (const CORBA::Exception& ex)
    {
      CIAOX11_TEST_PANIC << "Sender (SYNCH) :\tCAUGHT EXCEPTION [" << ex << "]" << std::endl;
    }
    catch (const std::exception& ex)
    {
      CIAOX11_TEST_PANIC << "Sender (SYNCH) :\tCAUGHT EXCEPTION [" << ex << "]" << std::endl;
    }
    catch (...)
    {
      CIAOX11_TEST_PANIC << "Sender (SYNCH) :\tCAUGHT UNKNOWN EXCEPTION" << std::endl;
    }

    return 0;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_impl]

  /**
   * Facet Executor Implementation Class : do_control_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_control_exec_i[ctor]
  do_control_exec_i::do_control_exec_i (
    IDL::traits<Hello::CCM_Sender_Context>::ref_type context,
    IDL::traits<Hello::CCM_Sender>::weak_ref_type comp_exec)
    : context_ (std::move (context))
    , comp_exec_ (comp_exec)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_control_exec_i[ctor]

  do_control_exec_i::~do_control_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_control_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_control_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_control_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_control_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_control_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_control_exec_i[user_private_ops]


  /** Operations and attributes from do_control */

  void
  do_control_exec_i::start ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_control_exec_i::start[void]
    CIAOX11_TEST_INFO << "do_control_exec_i::start" << std::endl;
    auto cex = IDL::traits<Sender_exec_i>::narrow (this->comp_exec_.lock ());
    if (cex)
      cex->start ();
    else
    {
      CIAOX11_TEST_ERROR << "Sender:\tdo_control_exec_i::start - failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_control_exec_i::start[void]
  }

  void
  do_control_exec_i::shutdown ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_control_exec_i::shutdown[void]
    CIAOX11_TEST_INFO << "do_control_exec_i::shutdown" << std::endl;
    auto cex = IDL::traits<Sender_exec_i>::narrow (this->comp_exec_.lock ());
    if (cex)
      cex->stop ();
    else
    {
      CIAOX11_TEST_ERROR << "Sender:\tdo_control_exec_i::shutdown - failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_control_exec_i::shutdown[void]
  }
  /**
   * Facet Executor Implementation Class : do_my_foo_exec_i
   */

  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_my_foo_exec_i[ctor]
  do_my_foo_exec_i::do_my_foo_exec_i (
    IDL::traits<Hello::CCM_Sender_Context>::ref_type context)
    : context_ (std::move (context))
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_my_foo_exec_i[ctor]

  do_my_foo_exec_i::~do_my_foo_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_my_foo_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_my_foo_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_my_foo_exec_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_my_foo_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_my_foo_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_my_foo_exec_i[user_private_ops]


  /** Operations and attributes from do_my_foo */

  int32_t
  do_my_foo_exec_i::foo (
      const std::string& in_str,
      std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_my_foo_exec_i::foo[_in_str_answer]
    CIAOX11_TEST_INFO << "Sender:\tdo_my_foo_exec_i::foo(" << in_str << ")" << std::endl;
    answer = "ciao bambina!";
    ++this->foo_calls_;
    return 0;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_my_foo_exec_i::foo[_in_str_answer]
  }

  void
  do_my_foo_exec_i::hello (
      int32_t& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_my_foo_exec_i::hello[_answer]
    CIAOX11_TEST_INFO << "Sender:\tdo_my_foo_exec_i::hello()" << std::endl;
    answer = 101;
    ++this->hello_calls_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_my_foo_exec_i::hello[_answer]
  }

  int16_t
  do_my_foo_exec_i::rw_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_my_foo_exec_i::rw_attrib[getter]
    return this->rw_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_my_foo_exec_i::rw_attrib[getter]
  }

  void
  do_my_foo_exec_i::rw_attrib (
      int16_t rw_attrib)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_my_foo_exec_i::rw_attrib[setter]
    this->rw_attrib_ = rw_attrib;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_my_foo_exec_i::rw_attrib[setter]
  }

  int16_t
  do_my_foo_exec_i::ro_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::do_my_foo_exec_i::ro_attrib[getter]
    return this->ro_attrib_;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::do_my_foo_exec_i::ro_attrib[getter]
  }

  /**
   * Component Executor Implementation Class : Sender_exec_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ctor]
  Sender_exec_i::Sender_exec_i ()
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ctor]

  Sender_exec_i::~Sender_exec_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_public_ops]
  void Sender_exec_i::start ()
  {
    CIAOX11_TEST_INFO << "Sender_exec_i::start()" << std::endl;
    this->synch_foo_gen_.set_context(this->context_);
    this->synch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
    this->asynch_foo_gen_.set_context(this->context_);
    this->asynch_foo_gen_.set_comp_exec (IDL::traits<Hello::CCM_Sender>::narrow (this->_lock()));
    this->asynch_foo_gen_.activate (THR_NEW_LWP | THR_JOINABLE, 1);
  }

  void Sender_exec_i::stop ()
  {
    CIAOX11_TEST_INFO << "Sender_exec_i::stop()" << std::endl;
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[user_private_ops]

  /** Session component operations */
  void Sender_exec_i::configuration_complete ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[configuration_complete]
    CIAOX11_TEST_INFO << "Sender_exec_i::configuration_complete" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[configuration_complete]
  }

  void Sender_exec_i::ccm_activate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
    CIAOX11_TEST_INFO << "Sender_exec_i::ccm_activate." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_activate]
  }

  void Sender_exec_i::ccm_passivate ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
    CIAOX11_TEST_INFO << "Sender_exec_i::ccm_passivate." << std::endl;

    CIAOX11_TEST_INFO << "Sender_exec_i::ccm_passivate - waiting on worker threads" << std::endl;

    // Wait on the worker threads to have finished
    this->synch_foo_gen_.wait ();
    this->asynch_foo_gen_.wait ();

    if (this->do_my_foo_)
    {
      auto do_my_foo_exec =
          IDL::traits<do_my_foo_exec_i>::narrow (this->do_my_foo_);
      if (do_my_foo_exec->foo_calls () > 0 && do_my_foo_exec->hello_calls () > 0 && asyn_replies () > 0)
      {
        CIAOX11_TEST_INFO << "Sender_exec_i::ccm_passivate - SUCCESS" << std::endl;
        return;
      }
    }

    CIAOX11_TEST_ERROR << "Sender_exec_i::ccm_passivate - FAILED" << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_passivate]
  }

  void Sender_exec_i::ccm_remove ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[ccm_remove]
    CIAOX11_TEST_INFO << "Sender_exec_i::ccm_remove." << std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[ccm_remove]
  }

  IDL::traits<::Hello::CCM_Control>::ref_type
  Sender_exec_i::get_do_control ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[get_do_control]
  if (!this->do_control_)
  {
    this->do_control_ =
        CORBA::make_reference <do_control_exec_i> (
            this->context_,
            IDL::traits<Hello::CCM_Sender>::narrow (this->_lock()));
  }
  return this->do_control_;
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[get_do_control]
  }

  IDL::traits<::Hello::CCM_MyFoo>::ref_type
  Sender_exec_i::get_do_my_foo ()
  {
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[get_do_my_foo]
  if (!this->do_my_foo_)
  {
    this->do_my_foo_ = CORBA::make_reference <do_my_foo_exec_i> (this->context_);
  }
  return this->do_my_foo_;
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[get_do_my_foo]
  }

  /// Operations from Components::SessionComponent
  void
  Sender_exec_i::set_session_context (
    IDL::traits<Components::SessionContext>::ref_type ctx)
  {
    // Setting the context of this component.
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::Sender_exec_i[set_session_context]
    CIAOX11_TEST_INFO << "Sender_exec_i::set_session_context." << std::endl;
    this->context_ = IDL::traits<Hello::CCM_Sender_Context>::narrow (std::move(ctx));
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::Sender_exec_i[set_session_context]
  }

  /**
   * AMI4CCM ReplyHandler Implementation Class : AMI4CCM_MyFooReplyHandler_run_my_foo_i
   */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::AMI4CCM_MyFooReplyHandler_run_my_foo_i (IDL::traits<Hello::CCM_Sender>::weak_ref_type comp_exec)
    : comp_exec_ (comp_exec)
  {
  }
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[ctor]

  AMI4CCM_MyFooReplyHandler_run_my_foo_i::~AMI4CCM_MyFooReplyHandler_run_my_foo_i ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
    // Your code here
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[dtor]
  }

  /** User defined public operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_public_ops]

  /** User defined private operations. */
  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]
  // Your code here
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[user_private_ops]

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::foo (
    int32_t ami_return_val,
    const std::string& answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo]
    CIAOX11_TEST_INFO << "Sender:\tAMI4CCM_MyFooReplyHandler_run_my_foo_i::foo "
                      << " answer: " << answer
                      << " return_val " << ami_return_val <<std::endl;
    auto cex = IDL::traits<Sender_exec_i>::narrow (this->comp_exec_.lock ());
    if (cex)
      cex->add_asyn_reply ();
    else
    {
      CIAOX11_TEST_ERROR << "Sender:\tAMI4CCM_MyFooReplyHandler_run_my_foo_i::foo - failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::foo_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo_excep]
    HandleException (excep_holder, "foo");
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[foo_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello (
    int32_t answer)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello]
    CIAOX11_TEST_INFO << "Sender:\tAMI4CCM_MyFooReplyHandler_run_my_foo_i::hello "
                      << " answer: " << answer <<std::endl;
    auto cex = IDL::traits<Sender_exec_i>::narrow (this->comp_exec_.lock ());
    if (cex)
      cex->add_asyn_reply ();
    else
    {
      CIAOX11_TEST_ERROR << "Sender:\tAMI4CCM_MyFooReplyHandler_run_my_foo_i::foo - failed to lock component executor" << std::endl;
    }
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::hello_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello_excep]
    HandleException (excep_holder, "hello");
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[hello_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib]
    CIAOX11_TEST_INFO << "Sender:\tAMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib "
                      << " ami_return_val: " << ami_return_val <<std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_excep]
    HandleException (excep_holder, "get_rw_attrib");
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib ()
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib]
    CIAOX11_TEST_INFO << "Sender:\tAMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib "
                      <<std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::set_rw_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_excep]
    HandleException (excep_holder, "set_rw_attribo");
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[set_rw_attrib_excep]
  }

  void
  AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib (
    int16_t ami_return_val)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib]
    CIAOX11_TEST_INFO << "Sender:\tAMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib "
                      << " ami_return_val: " << ami_return_val <<std::endl;
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib]
  }

  void AMI4CCM_MyFooReplyHandler_run_my_foo_i::get_ro_attrib_excep (
    IDL::traits<CCM_AMI::ExceptionHolder>::ref_type excep_holder)
  {
    //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_excep]
    HandleException (excep_holder, "get_ro_attrib");
    //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl::AMI4CCM_MyFooReplyHandler_run_my_foo_i[get_ro_attrib_excep]
  }



  //@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[user_namespace_end_impl]
  //@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[user_namespace_end_impl]

} // namespace Hello_Sender_Impl

//@@{__RIDL_REGEN_MARKER__} - BEGIN : Hello_Sender_Impl[factory]
extern "C" void
create_Hello_Sender_Impl (
  IDL::traits<Components::EnterpriseComponent>::ref_type& component)
{
  component = CORBA::make_reference <Hello_Sender_Impl::Sender_exec_i> ();
}
//@@{__RIDL_REGEN_MARKER__} - END : Hello_Sender_Impl[factory]
//@@{__RIDL_REGEN_MARKER__} - BEGIN : hello_sender_impl.cpp[Footer]
// Your footer (code) here
// -*- END -*-

/**
 * ****  Code generated by the RIDL Compiler ****
 * RIDL has been developed by:
 *        Remedy IT Expertise BV
 *        The Netherlands
 *        https://www.remedy.nl
 */
#ifndef __RIDL_PSDD_RECEIVER_LEM_STUB_EXPORT_H_GFACDCGA_EXPORT_INCLUDED__
#define __RIDL_PSDD_RECEIVER_LEM_STUB_EXPORT_H_GFACDCGA_EXPORT_INCLUDED__

#include /**/ "ace/config-all.h"

#include /**/ "tao/x11/versionx11.h"

#if TAOX11_MAJOR_VERSION != 1 || TAOX11_MINOR_VERSION != 8 || TAOX11_MICRO_VERSION != 0
#error This file was generated with another RIDL C++11 backend version (1.8.0). Please re-generate.
#endif

#if !defined (PSDD_RECEIVER_LEM_STUB_HAS_DLL)
# if defined (ACE_AS_STATIC_LIBS)
#  define PSDD_RECEIVER_LEM_STUB_HAS_DLL 0
# else
#  define PSDD_RECEIVER_LEM_STUB_HAS_DLL 1
# endif /* ACE_AS_STATIC_LIBS */
#endif /* !PSDD_RECEIVER_LEM_STUB_HAS_DLL */

#if PSDD_RECEIVER_LEM_STUB_HAS_DLL == 1
#  if defined (PSDD_RECEIVER_LEM_STUB_BUILD_DLL)
#    define PSDD_RECEIVER_LEM_STUB_Export ACE_Proper_Export_Flag
#    define PSDD_RECEIVER_LEM_STUB_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define PSDD_RECEIVER_LEM_STUB_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* PSDD_RECEIVER_LEM_STUB_BUILD_DLL */
#    define PSDD_RECEIVER_LEM_STUB_Export ACE_Proper_Import_Flag
#    define PSDD_RECEIVER_LEM_STUB_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define PSDD_RECEIVER_LEM_STUB_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* PSDD_RECEIVER_LEM_STUB_BUILD_DLL */
#else /* PSDD_RECEIVER_LEM_STUB_HAS_DLL == 1 */
#  define PSDD_RECEIVER_LEM_STUB_Export
#  define PSDD_RECEIVER_LEM_STUB_SINGLETON_DECLARATION(T)
#  define PSDD_RECEIVER_LEM_STUB_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* PSDD_RECEIVER_LEM_STUB_HAS_DLL == 1 */

#endif /* __RIDL_PSDD_RECEIVER_LEM_STUB_EXPORT_H_GFACDCGA_EXPORT_INCLUDED__ */

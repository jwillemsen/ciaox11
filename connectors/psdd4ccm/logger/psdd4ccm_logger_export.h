/**
 * @file    psdd4ccm_logger_export.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef PSDD4CCM_LOGGER_EXPORT_H
#define PSDD4CCM_LOGGER_EXPORT_H

#include "tao/x11/base/taox11_export_macros.h"

#if defined (TAOX11_AS_STATIC_LIBS) && !defined (PSDD4CCM_LOGGER_HAS_DLL)
#  define PSDD4CCM_LOGGER_HAS_DLL 0
#endif /* TAOX11_AS_STATIC_LIBS && PSDD4CCM_LOGGER_HAS_DLL */

#if !defined (PSDD4CCM_LOGGER_HAS_DLL)
#  define PSDD4CCM_LOGGER_HAS_DLL 1
#endif /* ! PSDD4CCM_LOGGER_HAS_DLL */

#if defined (PSDD4CCM_LOGGER_HAS_DLL) && (PSDD4CCM_LOGGER_HAS_DLL == 1)
#  if defined (PSDD4CCM_LOGGER_BUILD_DLL)
#    define PSDD4CCM_Logger_Export TAOX11_Proper_Export_Flag
#    define PSDD4CCM_LOGGER_SINGLETON_DECLARATION(T) TAOX11_EXPORT_SINGLETON_DECLARATION (T)
#    define PSDD4CCM_LOGGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) TAOX11_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* PSDD4CCM_LOGGER_BUILD_DLL */
#    define PSDD4CCM_Logger_Export TAOX11_Proper_Import_Flag
#    define PSDD4CCM_LOGGER_SINGLETON_DECLARATION(T) TAOX11_IMPORT_SINGLETON_DECLARATION (T)
#    define PSDD4CCM_LOGGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) TAOX11_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* PSDD4CCM_LOGGER_BUILD_DLL */
#else /* PSDD4CCM_LOGGER_HAS_DLL == 1 */
#  define PSDD4CCM_Logger_Export
#  define PSDD4CCM_LOGGER_SINGLETON_DECLARATION(T)
#  define PSDD4CCM_LOGGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* PSDD4CCM_LOGGER_HAS_DLL == 1 */

#endif /* PSDD4CCM_LOGGER_EXPORT_H */


#ifndef ANYLIB_GLOBAL_HPP
#define ANYLIB_GLOBAL_HPP

#include <QtCore/qglobal.h>

#if defined(ANY_LIBRARY)
#  define ANY_EXPORT Q_DECL_EXPORT
#else
#  define ANY_EXPORT Q_DECL_IMPORT
#endif

#endif

#ifndef NAMEOF_GLOBAL_H
#define NAMEOF_GLOBAL_H


#include <QtCore/qglobal.h>

#if defined(NAMEOF_LIBRARY)
#  define NAMEOF_EXPORT Q_DECL_EXPORT
#else
#  define NAMEOF_EXPORT Q_DECL_IMPORT
#endif


#endif // NAMEOF_GLOBAL_H

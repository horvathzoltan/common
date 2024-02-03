#ifndef NAMEOF_GLOBAL_H
#define NAMEOF_GLOBAL_H


#include <QtCore/qglobal.h>

#if defined(COM_NAMEOF_LIBRARY)
#  define COM_NAMEOF_EXPORT Q_DECL_EXPORT
#else
#  define COM_NAMEOF_EXPORT Q_DECL_IMPORT
#endif


#endif // NAMEOF_GLOBAL_H

#ifndef COM_INIHELPER_GLOBAL_H
#define COM_INIHELPER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COM_INIHELPER_LIBRARY)
#  define COM_INIHELPERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define COM_INIHELPERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // INIHELPER_GLOBAL_H

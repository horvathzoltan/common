#ifndef INIHELPER_GLOBAL_H
#define INIHELPER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(INIHELPER_LIBRARY)
#  define INIHELPERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define INIHELPERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // INIHELPER_GLOBAL_H
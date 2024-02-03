#ifndef COM_LOGGER_GLOBAL_H
#define COM_LOGGER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COM_LOGGER_LIBRARY)
#  define COM_LOGGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define COM_LOGGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LOGGER_GLOBAL_H

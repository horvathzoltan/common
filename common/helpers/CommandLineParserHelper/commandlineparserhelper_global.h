#ifndef COM_COMMANDLINEPARSERHELPER_GLOBAL_H
#define COM_COMMANDLINEPARSERHELPER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COM_COMMANDLINEPARSERHELPER_LIBRARY)
#  define COM_COMMANDLINEPARSERHELPER_EXPORT Q_DECL_EXPORT
#else
#  define COM_COMMANDLINEPARSERHELPER_EXPORT Q_DECL_IMPORT
#endif

#endif // COMMANDLINEPARSERHELPER_GLOBAL_H

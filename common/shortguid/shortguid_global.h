#ifndef COM_SHORTGUID_GLOBAL_H
#define COM_SHORTGUID_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COM_SHORTGUID_LIBRARY)
#  define COM_SHORTGUIDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define COM_SHORTGUIDSHARED_EXPORT Q_DECL_IMPORT
#endif


#endif // SHORTGUID_GLOBAL_H

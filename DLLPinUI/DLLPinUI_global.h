#ifndef DLLPINUI_GLOBAL_H
#define DLLPINUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLLPINUI_LIBRARY)
#  define DLLPINUI_EXPORT Q_DECL_EXPORT
#else
#  define DLLPINUI_EXPORT Q_DECL_IMPORT
#endif

#endif // DLLPINUI_GLOBAL_H

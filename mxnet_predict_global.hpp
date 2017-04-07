#ifndef MXNET_PREDICT_GLOBAL_H
#define MXNET_PREDICT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MXNET_PREDICT_LIBRARY)
#  define MXNET_PREDICTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MXNET_PREDICTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MXNET_PREDICT_GLOBAL_H

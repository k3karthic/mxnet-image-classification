#ifndef MXNETIMAGE_H
#define MXNETIMAGE_H

#include <mxnet/c_predict_api.h>
#include <opencv2/opencv.hpp>
#include <QDir>
#include <QString>
#include <vector>

#include "mxnet_predict_global.hpp"

class MXNET_PREDICTSHARED_EXPORT MyImage {
public:
    MyImage(): DEFAULT_MEAN(117.0) {}
    std::vector<mx_float> processImage(QString path);

    static const int width = 224;
    static const int height = 224;
    static const int channels = 3;
    static const int size = width * height * channels;
private:
    const QDir dir;
    const mx_float DEFAULT_MEAN;
};

#endif // MXNETIMAGE_H

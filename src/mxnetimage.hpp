#ifndef MXNETIMAGE_H
#define MXNETIMAGE_H

#include <QDir>
#include <QString>
#include <mxnet/c_predict_api.h>
#include <opencv/cv.hpp>
#include <vector>

#include "mxnet_predict_global.hpp"

class MXNET_PREDICTSHARED_EXPORT MyImage {
public:
  MyImage() {}
  std::vector<mx_float> processImage(QString path);

  static const int width = 224;
  static const int height = 224;
  static const int channels = 3;
  static const int size = width * height * channels;

private:
  const QDir dir;
};

#endif // MXNETIMAGE_H

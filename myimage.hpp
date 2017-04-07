#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <mxnet/c_predict_api.h>
#include <opencv2/opencv.hpp>
#include <QString>

class MyImage {
public:
    MyImage();
    void loadImage(QString path);

    const int width;
    const int height;
    const int channels;
private:
    cv::Mat image;
    const mx_float DEFAULT_MEAN;
};

#endif // IMAGE_HPP

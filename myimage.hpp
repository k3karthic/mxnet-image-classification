#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <mxnet/c_predict_api.h>
#include <opencv2/opencv.hpp>
#include <QString>
#include <vector>

class MyImage {
public:
    MyImage();
    void loadImage(QString path);
    std::vector<mx_float> asVector();

    static const int width = 224;
    static const int height = 224;
    static const int channels = 3;
    static const int size = width * height * channels;
private:
    cv::Mat image;
    const mx_float DEFAULT_MEAN;
};

#endif // IMAGE_HPP

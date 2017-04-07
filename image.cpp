#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QDir>
#include <QString>
#include <QtGlobal>
#include <vector>

#include "myimage.hpp"

//
// Helper Functions
//

//
// Implementation
//

MyImage::MyImage(): DEFAULT_MEAN(117.0) {}

void MyImage::loadImage(QString relPath) {
    QDir dir;
    auto path = dir.toNativeSeparators(dir.absoluteFilePath(relPath));
    auto im_ori = cv::imread(path.toUtf8().constData(), cv::IMREAD_COLOR);

    if (im_ori.empty()) {
        qFatal("Unable to open image file.");
        assert(false);
    }

    cv::Mat im;
    resize(im_ori, im, cv::Size(this->width, this->height));

    this->image = im;
}

std::vector<mx_float> MyImage::asVector() {
    auto result = std::vector<mx_float>(MyImage::size);
    mx_float* ptr_image_r = result.data();
    mx_float* ptr_image_g = result.data() + size / 3;
    mx_float* ptr_image_b = result.data() + size / 3 * 2;

    for (int i = 0; i < this->image.rows; i++) {
        uchar* data = this->image.ptr<uchar>(i);

        for (int j = 0; j < this->image.cols; j++) {
            *ptr_image_g++ = static_cast<mx_float>(*data++) - this->DEFAULT_MEAN;
            *ptr_image_b++ = static_cast<mx_float>(*data++) - this->DEFAULT_MEAN;
            *ptr_image_r++ = static_cast<mx_float>(*data++) - this->DEFAULT_MEAN;
        }
    }

    return result;
}

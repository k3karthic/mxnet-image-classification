#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QDir>
#include <QString>
#include <QtGlobal>
#include <vector>

#include "mxnetimage.hpp"

//
// Implementation
//

std::vector<mx_float> MyImage::processImage(QString relPath) {
    auto path = this->dir.toNativeSeparators(this->dir.absoluteFilePath(relPath));
    auto im_ori = cv::imread(path.toUtf8().constData(), cv::IMREAD_COLOR);

    if (im_ori.empty()) {
        qFatal("Unable to open image file.");
        assert(false);
    }

    cv::Mat im;
    resize(im_ori, im, cv::Size(this->width, this->height));

    auto result = std::vector<mx_float>(MyImage::size);

    mx_float* ptr_image_r = result.data();
    mx_float* ptr_image_g = result.data() + size / 3;
    mx_float* ptr_image_b = result.data() + size / 3 * 2;

    for (int i = 0; i < im.rows; i++) {
        uchar* data = im.ptr<uchar>(i);

        for (int j = 0; j < im.cols; j++) {
            *ptr_image_g++ = static_cast<mx_float>(*data++) - this->DEFAULT_MEAN;
            *ptr_image_b++ = static_cast<mx_float>(*data++) - this->DEFAULT_MEAN;
            *ptr_image_r++ = static_cast<mx_float>(*data++) - this->DEFAULT_MEAN;
        }
    }

    return result;
}

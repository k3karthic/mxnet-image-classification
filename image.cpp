#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QDir>
#include <QString>
#include <QtGlobal>

#include "myimage.hpp"

//
// Helper Functions
//

//
// Implementation
//

MyImage::MyImage(): DEFAULT_MEAN(117.0), width(224), height(224), channels(3) {}

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
    im = im - this->DEFAULT_MEAN;

    this->image = im;
}

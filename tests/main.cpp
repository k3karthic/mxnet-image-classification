#include <QtDebug>
#include <QtGlobal>

#include <mxnetpredict.hpp>
#include <mxnetimage.hpp>

int main(int argc, char *argv[])
{
    MyImage im;
    auto im_data = im.processImage("sample.jpg");

    MXNetPredict p("model", DevType::cpu, 0);
    auto result = p.getPredictions(im_data, 5);

    for (int j = 0; j < static_cast<int>(result.size()); j++) {
        auto x = result[j];
        std::cout << QString::number(std::get<float>(x), 'g', 2).toUtf8().constData() << " " << std::get<QString>(x).toUtf8().constData();
    }

    return 0;
}

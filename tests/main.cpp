#include <QtDebug>
#include <QtGlobal>
#include <iostream>

#include <mxnetimage.hpp>
#include <mxnetpredict.hpp>

int main(int argc, char *argv[]) {
  MyImage im;

  MXNetPredict p("model", DevType::cpu, 0);
  p.loadModel();

  auto im_data = im.processImage("samples/cat.jpg");
  auto result = p.getPredictions(im_data, 5);

  for (int j = 0; j < static_cast<int>(result.size()); j++) {
    auto x = result[j];
    std::cout
        << QString::number(std::get<float>(x), 'g', 2).toUtf8().constData()
        << " " << std::get<QString>(x).toUtf8().constData();
  }

  std::cout << "\n";

  im_data = im.processImage("samples/pug.jpg");
  result = p.getPredictions(im_data, 5);

  for (int j = 0; j < static_cast<int>(result.size()); j++) {
    auto x = result[j];
    std::cout
        << QString::number(std::get<float>(x), 'g', 2).toUtf8().constData()
        << " " << std::get<QString>(x).toUtf8().constData();
  }

  return 0;
}

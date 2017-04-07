#include <QtDebug>
#include <QtGlobal>

#include "myimage.hpp"
#include "predictor.hpp"

int main(int argc, char *argv[])
{
    MyImage im;
    im.loadImage("sample.jpg");

    Predictor p("model", DevType::cpu, 0, im);

    return 0;
}

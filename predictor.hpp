#ifndef PREDICTOR_HPP
#define PREDICTOR_HPP

#include <mxnet/c_predict_api.h>
#include <QByteArray>
#include <QString>
#include <QVector>

#include <myimage.hpp>

enum class DevType { cpu, gpu };

class Predictor {
public:
    Predictor(QString pathPrefix, DevType dt, int dev_id);
    ~Predictor();
    void getPredictions(MyImage im);
private:
    PredictorHandle handle;
};

#endif // PREDICTOR_HPP

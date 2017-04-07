#ifndef PREDICTOR_HPP
#define PREDICTOR_HPP

#include <mxnet/c_predict_api.h>
#include <QByteArray>
#include <QString>
#include <vector>

#include <myimage.hpp>

enum class DevType { cpu, gpu };

class Predictor {
public:
    Predictor(QString pathPrefix, DevType dt, int dev_id);
    std::vector<std::pair<float,QString>> getPredictions(std::vector<mx_float> image_data, int n);
private:
    QByteArray symbolFile;
    QByteArray paramFile;
    std::vector<QString> synsets;
    int dev_type;
    int dev_id;
    mx_uint num_input_nodes;
    char** input_keys;
    mx_uint input_shape_indptr[2];
    mx_uint input_shape_data[4];
};

#endif // PREDICTOR_HPP

#ifndef MXNETPREDICT_H
#define MXNETPREDICT_H

#include <mxnet/c_predict_api.h>
#include <QByteArray>
#include <QString>
#include <vector>

#include "mxnet_predict_global.hpp"
#include "mxnetimage.hpp"

enum class DevType { cpu, gpu };

class MXNET_PREDICTSHARED_EXPORT MXNetPredict
{
public:
    MXNetPredict(QString pathPrefix, DevType dt, int dev_id);
    std::vector<std::pair<float,QString>> getPredictions(std::vector<mx_float> image_data, int n);
private:
    QByteArray symbolFile;
    QByteArray paramFile;
    std::vector<QString> synsets;
    int dev_type;
    int dev_id;
};

#endif // MXNETPREDICT_H

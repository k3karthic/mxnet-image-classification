#ifndef PREDICTOR_HPP
#define PREDICTOR_HPP

#include <QByteArray>
#include <QString>
#include <QVector>

#include "myimage.hpp"

enum class DevType { cpu, gpu };

class Predictor {
public:
    Predictor(QString pathPrefix, DevType dt, int dev_id, MyImage im);
private:
    int dev_type;
    int dev_id;
    QByteArray symbolFile;
    QByteArray paramFile;
    QVector<QString> synsets;
};

#endif // PREDICTOR_HPP

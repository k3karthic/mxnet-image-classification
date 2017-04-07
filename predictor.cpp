#include <cassert>
#include <mxnet/c_predict_api.h>
#include <QDir>
#include <QFile>
#include <QString>
#include <QtGlobal>
#include <QVector>

#include "myimage.hpp"
#include "predictor.hpp"

//
// Helper Functions
//

QByteArray readBinary(const char* name, QString path) {
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) {
        qFatal("Could not open file: " + *name);
        assert(false);
    }

    return file.readAll();
}

QVector<QString> readSynsets(QString path) {
    QFile file(path);
    QVector<QString> result;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal("Could not open synset file");
        assert(false);
    }

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        result.append(QString::fromUtf8(line.data()));
    }

    return result;
}

//
// Implementation
//

Predictor::Predictor(QString pathPrefix, DevType dt, int dev_id, MyImage im) {
    auto symbolName = "Inception-BN-symbol.json";
    auto paramName = "Inception-BN-0126.params";

    QDir dir(pathPrefix);
    auto symbolPath = dir.absoluteFilePath(symbolName);
    auto paramsPath = dir.absoluteFilePath(paramName);
    auto synsetPath = dir.absoluteFilePath("synset.txt");

    auto dev_type = 1;
    if (dt == DevType::gpu) {
        dev_type = 2;
    }

    auto symbolFile = readBinary(symbolName, symbolPath);
    auto paramFile = readBinary(paramName, paramsPath);
    auto synsets = readSynsets(synsetPath);

    mx_uint num_input_nodes = 1;  // 1 for feedforward
    const char* input_key[1] = {"data"};
    const char** input_keys = input_key;
    const mx_uint input_shape_indptr[2] = { 0, 4 };
    const mx_uint input_shape_data[4] = { 1,
                                        static_cast<mx_uint>(im.channels),
                                        static_cast<mx_uint>(im.width),
                                        static_cast<mx_uint>(im.height) };

    PredictorHandle pred_hnd = 0;

    auto result = MXPredCreate(
                    symbolFile.constData(),
                paramFile.constData(),
                static_cast<size_t> (paramFile.length()),
                dev_type,
                dev_id,
                num_input_nodes,
                input_keys,
                input_shape_indptr,
                input_shape_data,
                &pred_hnd
                );
}

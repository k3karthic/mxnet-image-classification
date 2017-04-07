#include <cassert>
#include <mxnet/c_predict_api.h>
#include <QDir>
#include <QFile>
#include <QString>
#include <QtGlobal>
#include <vector>

#include "mxnetimage.hpp"
#include "mxnetpredict.hpp"

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

std::vector<QString> readSynsets(QString path) {
    QFile file(path);
    std::vector<QString> result;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal("Could not open synset file");
        assert(false);
    }

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        auto lineS = QString::fromUtf8(line.data());
        lineS.remove(0, 10);
        result.push_back(lineS);
    }

    return result;
}

//
// Implementation
//

MXNetPredict::MXNetPredict(QString pathPrefix, DevType dt, int dev_id) {
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

    this->symbolFile = symbolFile;
    this->paramFile = paramFile;
    this->synsets = synsets;
    this->dev_type = dev_type;
    this->dev_id = dev_id;
}

std::vector<std::pair<float,QString>> MXNetPredict::getPredictions(std::vector<mx_float> image_data, int n) {
    mx_uint num_input_nodes = 1;  // 1 for feedforward
    const char* input_key[1] = {"data"};
    const char** input_keys = input_key;
    const mx_uint input_shape_indptr[2] = { 0, 4 };
    const mx_uint input_shape_data[4] = { 1,
                                        static_cast<mx_uint>(MyImage::channels),
                                        static_cast<mx_uint>(MyImage::width),
                                        static_cast<mx_uint>(MyImage::height) };
    PredictorHandle handle = 0;

    MXPredCreate(
                this->symbolFile.constData(),
                this->paramFile.constData(),
                static_cast<size_t> (this->paramFile.length()),
                this->dev_type,
                this->dev_id,
                num_input_nodes,
                input_keys,
                input_shape_indptr,
                input_shape_data,
                &handle
                );

    assert(handle);

    mx_uint output_index = 0;
    mx_uint *shape = 0;
    mx_uint shape_len;

    MXPredSetInput(handle, "data", image_data.data(), MyImage::size);
    MXPredForward(handle);
    MXPredGetOutputShape(handle, output_index, &shape, &shape_len);

    size_t size = 1;
    for (mx_uint i = 0; i < shape_len; ++i) {
        size *= shape[i];
    }

    std::vector<float> data(size);

    MXPredGetOutput(handle, output_index, &(data[0]), size);
    MXPredFree(handle);

    auto result = std::vector<std::pair<float,QString>>(n);

    for ( int i = 0; i < static_cast<int>(data.size()); i++ ) {
        auto val = data[i];

        for (int j = 0; j < static_cast<int>(result.size()); j++) {
            if (val > std::get<float>(result[j])) {
                result[j] = std::make_pair(val, this->synsets[i]);
                break;
            }
        }
    }

    return result;
}

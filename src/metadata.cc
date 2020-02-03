//
// Created by Shlomi Nissan on 2/2/20.
//

#include "metadata.h"

#include <fstream>

using std::fstream;

void Metadata::Write(const Node* node) {
    // TODO: write node
}

void Metadata::Save(const string &path) {
    writer.EndObject();

    std::ofstream file(path);
    file << buffer.GetString();
    if (!file.good()) {
        throw std::runtime_error("Unable to write metadata to file " + path);
    }
}

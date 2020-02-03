//
// Created by Shlomi Nissan on 2/2/20.
//

#include "metadata.h"

#include <fstream>

using std::fstream;

void Metadata::Write(const Node* node) {
    writer.StartObject();

    writer.Key("name");
    writer.String(node->bitmap->path());

    writer.Key("x");
    writer.Int(node->x);

    writer.Key("y");
    writer.Int(node->y);

    writer.Key("width");
    writer.Int(node->bitmap->width());

    writer.Key("height");
    writer.Int(node->bitmap->height());

    writer.EndObject();
}

void Metadata::Save(const string &path) {
    writer.EndArray();
    writer.EndObject();

    std::ofstream file(path);
    file << buffer.GetString();
    if (!file.good()) {
        throw std::runtime_error("Unable to write metadata to file " + path);
    }
}

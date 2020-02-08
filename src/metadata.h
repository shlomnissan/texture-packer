//
// Created by Shlomi Nissan on 2/2/20.
//

#ifndef SRC_METADATA_H_
#define SRC_METADATA_H_

#include <string>

#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include "node.h"

using std::string;
using rapidjson::StringBuffer;
using rapidjson::PrettyWriter;

class Metadata {
public:
    Metadata() : writer(buffer) {
        writer.StartObject();
        writer.Key("sprites");
        writer.StartArray();
    }

    void Write(const Node* node);
    void Save(const string& filename);

private:
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer;
};

#endif //SRC_METADATA_H_

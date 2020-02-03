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

class Metadata {
public:
    void Write(const Node& node);
};

#endif //SRC_METADATA_H_

// Copyright 2020 Betamark Pty Ltd.
// Author: Shlomi Nissan

#include <iostream>
#include <string>
#include <fstream>
#include "gflags/gflags.h"

#include "packer.h"

DEFINE_string(i, "", "text file input");
DEFINE_string(o, "spritesheet", "output filename");

DEFINE_validator(i, [](const char *flag, const std::string& value) -> bool {
    if (value[0] == '\0') {
        // input file wasn't provided
        std::cerr << "You must provide a text file input\n";
        return false;
    }
    return true;
});

void start_packing() {
    Packer packer;

    // open text file
    std::fstream file { FLAGS_i };
    if (file.fail()) {
        throw std::runtime_error("Unable to open text file " + FLAGS_i);
    }

    // read file and load bitmaps
    std::string buffer;
    while (std::getline(file, buffer)) {
        packer.AddBitmap(std::move(Bitmap(buffer)));
    }

    // generate texture map
    packer.Pack();

    // export files 
    packer.Export(FLAGS_o);
}

int main(int argc, char* argv[]) {
    gflags::SetUsageMessage("texture_packer -i [text file input] -o[output file name]");
    gflags::SetVersionString("1.0.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    start_packing();

    gflags::ShutDownCommandLineFlags();

    return EXIT_SUCCESS;
}

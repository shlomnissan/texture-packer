// Copyright 2020 Betamark Pty Ltd.
// Author: Shlomi Nissan

#include <iostream>
#include <string>
#include <fstream>
#include "gflags/gflags.h"

#include "packer.h"

void show_tip() {
    std::cout << "[Usage]\n"
              << "\ttexture_packer FILE_LIST [-i input text file] [-o output file]\n";
}

void create_bitmap_move_to_pack(Packer* packer_ptr, const std::string& src) {
    Packer& packer = *packer_ptr;
    Bitmap bitmap { src };
    packer.AddBitmap(std::move(bitmap));
}

void load_bitmaps_from_text_file(Packer* packer_ptr, const std::string& src) {
    std::fstream file { src };
    if (file.fail()) {
        throw std::runtime_error("Unable to open text file " + src);
    }
    std::string buffer;
    while (std::getline(file, buffer)) {
        create_bitmap_move_to_pack(packer_ptr, buffer);
    }
}

void process_arguments(int argc, char* argv[]) {
    auto failed { false };
    std::string filename { "spritesheet" };  // Init with default filename
    Packer packer;

    try {
        for (int i = 0; i < argc; ++i) {
            auto value{argv[i]};
            if (value[0] == '-') {
                switch (std::tolower(value[1])) {
                    case 'o':  // [-o: output] override default filename
                        filename = argv[++i];
                        break;
                    case 'i': // [-i: input] load bitmaps from text file
                        load_bitmaps_from_text_file(&packer, argv[++i]);
                        break;
                }
            } else {
                // If there's no flag, assume image src file
                create_bitmap_move_to_pack(&packer, argv[i]);
            }
        }
    } catch (const std::runtime_error& e) {
        failed = true;
        std::cerr << e.what() << '\n';
    }

    if (failed) {
        std::cerr << "Failed to open file(s)\n";
        return;
    }

    if (packer.size() == 0) {
        std::cerr << "No textures to pack\n\n";
        show_tip();
        return;
    }

    packer.Pack();
    packer.Export(filename);
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        show_tip();
    } else if (argc >= 2) {
        process_arguments(--argc, ++argv);
    }

    return EXIT_SUCCESS;
}

//
// Created by Shlomi Nissan on 1/24/20.
//

#include <iostream>
#include <string>

#include "packer.h"

void show_tip() {
    std::cout << "[Usage]\n"
              << "\ttexture_packer FILE_LIST [-o output file]\n";
}

void process_arguments(int argc, char* argv[]) {
    bool failed = false;
    std::string filename { "spritesheet" };  // default filename
    Packer packer;

    for (int i = 0; i < argc; ++i) {
        auto value = argv[i];
        if (value[0] == '-') {
            switch (std::tolower(value[1])) {
                case 'o':
                    // override filename
                    filename = argv[++i];
                    break;
            }
        } else {
            try {
                // create bitmaps and move them to the packer
                Bitmap bitmap { argv[i] };
                packer.AddBitmap(std::move(bitmap));
            } catch (std::runtime_error& e) {
                failed = true;
                std::cerr << e.what() << '\n';
            }
        }
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

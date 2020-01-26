//
// Created by Shlomi Nissan on 1/24/20.
//

#include <iostream>
#include <string>

#include "bitmap.h"

void show_tip() {
    std::cout << "[Usage]\n" << "\ttexture_packer FILE_LIST [-o output file]\n";
}

void process_arguments(int argc, char* argv[]) {
    std::string filename { "spritesheet" };
    bool failed = false;

    for (int i = 0; i < argc; ++i) {
        auto value = argv[i];
        if (value[0] == '-') {
            switch(std::tolower(value[1])) {
                case 'o':
                    filename = argv[++i];
                    break;
            }
        } else {
            try {
                Bitmap bitmap { argv[i] };
                // TODO: move bitmap to packer
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

    // TODO: check that more than one bitmap is selected
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        show_tip();
    } else if (argc >= 2) {
        process_arguments(--argc, ++argv);
    }

    return EXIT_SUCCESS;
}

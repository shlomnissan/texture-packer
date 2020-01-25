//
// Created by Shlomi Nissan on 1/24/20.
//

#include <iostream>

void show_tip() {
    std::cout << "[Usage]\n" << "\ttexture_packer FILE_LIST [-o output file]\n";
}

void process_arguments(int argc, char* argv[]) {
    for (int i = 0; i < argc; ++i) {
        auto value = argv[i];
        if (value[0] == '-') {
            switch(std::tolower(value[1])) {
                case 'o':
                    auto filename = argv[++i];
                    std::cout << "Filename: " << filename << '\n';
                    break;
            }
        } else {
            std::cout << "Sprite: " << argv[i] << '\n';
        }
    }

    // TODO: check that more than one bitmap is selected
    // TODO: check the file exists
    // TODO: if name isn't set, set default

}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        show_tip();
    } else if (argc >= 2) {
        process_arguments(--argc, ++argv);
    }

    return EXIT_SUCCESS;
}

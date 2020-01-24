//
// Created by Shlomi Nissan on 1/24/20.
//

#include <iostream>

void show_tip() {
    std::cout << "[Usage]\n" << "\tframepacker FILE_LIST [-o output file]\n";
}

void process_arguments() {
    // Process inputs
    // Get output file name
    // Verify input
    // Instantiate the packer class
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        show_tip();
    } else if (argc >= 2) {
        process_arguments();
    }

    return EXIT_SUCCESS;
}

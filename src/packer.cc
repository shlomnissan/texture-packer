//
// Created by Shlomi Nissan on 1/25/20.
//

#include "packer.h"

#include <algorithm>

void Packer::Pack() {
    std::sort(bitmaps.begin(), bitmaps.end());
}

void Packer::Export(string_view filename) {

}

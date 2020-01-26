//
// Created by Shlomi Nissan on 1/25/20.
//

#ifndef SRC_PACKER_PACKER_H_
#define SRC_PACKER_PACKER_H_

#include <vector>

#include "bitmap.h"

using std::vector;

class Packer {
public:
    Packer() = default;

    void AddBitmap(Bitmap&& bitmap) {
        bitmaps.emplace_back(std::move(bitmap));
    }

    int size() const {
        return bitmaps.size();
    }
private:
    vector<Bitmap> bitmaps {};
};

#endif //SRC_PACKER_PACKER_H_

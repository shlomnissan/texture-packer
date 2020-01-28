//
// Created by Shlomi Nissan on 1/25/20.
//

#ifndef SRC_PACKER_H_
#define SRC_PACKER_H_

#include <vector>
#include <string_view>
#include <utility>

#include "bitmap.h"
#include "node.h"

using std::vector;
using std::string_view;

class Packer {
public:
    Packer() = default;

    void AddBitmap(Bitmap&& bitmap) {
        bitmaps.emplace_back(std::move(bitmap));
    }

    int size() const {
        return bitmaps.size();
    }

    void Pack();
    void Export(string_view filename);

private:
    vector<Bitmap> bitmaps {};

    Node* FindNode(Node* root, int width, int height);
    void SplitNode(Node* node, int width, int height);
};

#endif //SRC_PACKER_H_

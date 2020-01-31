// Copyright 2020 Betamark Pty Ltd.
// Author: Shlomi Nissan

#ifndef SRC_PACKER_H_
#define SRC_PACKER_H_

#include <vector>
#include <string_view>
#include <utility>
#include <memory>

#include "bitmap.h"
#include "node.h"

using std::vector;
using std::string_view;
using std::unique_ptr;

class Packer {
public:
    Packer() = default;

    void AddBitmap(Bitmap&& bitmap) {
        bitmaps_.emplace_back(std::move(bitmap));
    }

    int size() const { return bitmaps_.size(); }

    void Pack();
    void Export(string_view filename);

private:
    vector<Bitmap> bitmaps_ {};
    unique_ptr<Bitmap> spritesheet_;

    Node* FindNode(const unique_ptr<Node>& root, int width, int height);
    void SplitNode(Node *node, Bitmap* bitmap);
    void Draw(Node* node);
};

#endif //SRC_PACKER_H_

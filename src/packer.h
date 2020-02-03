// Copyright 2020 Betamark Pty Ltd.
// Author: Shlomi Nissan

#ifndef SRC_PACKER_H_
#define SRC_PACKER_H_

#include <vector>
#include <utility>
#include <memory>
#include <string>

#include "bitmap.h"
#include "node.h"

using std::vector;
using std::unique_ptr;
using std::string;

class Packer {
public:
    Packer() = default;

    void AddBitmap(Bitmap&& bitmap) {
        bitmaps_.emplace_back(std::move(bitmap));
    }

    int size() const { return bitmaps_.size(); }

    void Pack();
    void Export(const string& filename);

private:
    vector<Bitmap> bitmaps_ {};
    unique_ptr<Bitmap> spritesheet_;

    Node* FindNode(const unique_ptr<Node>& root, int width, int height);
    Node* SplitNode(Node *node, int width, int height);

    Node* GrowNode(unique_ptr<Node>* root_ptr, int width, int height);
    Node* GrowRight(unique_ptr<Node>* root_ptr, int width, int height);
    Node* GrowDown(unique_ptr<Node>* root_ptr, int width, int height);

    void GenerateTextureMap(Node* node);
    void GenerateMetadata(Node* node);
};

#endif //SRC_PACKER_H_

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
#include "metadata.h"

using std::vector;
using std::unique_ptr;
using std::string;

class Packer {
public:
    int size() const { return bitmaps_.size(); }

    void Pack();
    void Export(const string& filename);
    void AddBitmap(Bitmap&& bitmap);

private:
    vector<Bitmap> bitmaps_ {};
    unique_ptr<Bitmap> spritesheet_;
    unique_ptr<Node> root_;
    Metadata metadata_;

    Node* FindNode(const unique_ptr<Node>& root, int width, int height);
    Node* SplitNode(Node *node, int width, int height);

    Node* GrowNode(int width, int height);
    Node* GrowRight(int width, int height);
    Node* GrowDown(int width, int height);

    void GenerateTextureMap(Node* node);
};

#endif //SRC_PACKER_H_

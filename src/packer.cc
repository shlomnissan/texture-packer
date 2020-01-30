// Copyright 2020 Betamark Pty Ltd.
// Author: Shlomi Nissan

#include "packer.h"

#include <algorithm>

using std::make_unique;

const unsigned kPlaceholderWidth = 128;
const unsigned kPlaceholderHeight = 64;
const unsigned kDefaultBPP = 32;

void Packer::Pack() {
    // Sort by max-side descending
    std::sort(bitmaps.begin(), bitmaps.end(),
            [](const Bitmap& a, const Bitmap& b) -> bool {
        return std::max(a.get_width(), a.get_height())
             > std::max(b.get_width(), b.get_height());
    });

    // Create empty root node
    auto root = make_unique<Node>(0, 0, kPlaceholderWidth, kPlaceholderHeight);

    // Generate texture map tree
    for (int i = 0; i < bitmaps.size(); ++i) {
        auto node = FindNode(root, bitmaps[i].get_width(),
                                   bitmaps[i].get_height());
        if (node) {
            SplitNode(node, &bitmaps[i]);
        }
    }

    // Create a blank sprite-sheet
    spritesheet = std::make_unique<Bitmap>(kPlaceholderWidth,
                                           kPlaceholderHeight,
                                           kDefaultBPP);

    Draw(root.get());
}

void Packer::Export(string_view filename) {
    spritesheet->Save("atlas.png");
}

void Packer::Draw(Node *node) {
    if (node == nullptr) {
        return;
    }

    if (node->bitmap != nullptr) {
        spritesheet->Paste(node->x, node->y, *node->bitmap);
    }

    Draw(node->right.get());
    Draw(node->down.get());
}

Node* Packer::FindNode(const unique_ptr<Node>& root, int width, int height) {
    if (root->bitmap) {
        auto right = FindNode(root->right, width, height);
        if (right) return right;
        return FindNode(root->down, width, height);
    } else if (width <= root->width && height <= root->height) {
        return root.get();
    } else {
        return nullptr;
    }
}

void Packer::SplitNode(Node *node, Bitmap* bitmap_ptr) {
    node->bitmap = bitmap_ptr;
    auto width = bitmap_ptr->get_width();
    auto height = bitmap_ptr->get_height();

    // Create right node
    node->right = std::make_unique<Node>(
            node->x + width,
            node->y,
            node->width - width,
            height);

    // Create bottom node
    node->down = std::make_unique<Node>(
            node->x,
            node->y + height,
            width,
            node->height - height);
}

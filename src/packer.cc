// Copyright 2020 Betamark Pty Ltd.
// Author: Shlomi Nissan

#include "packer.h"

#include <algorithm>
#include <iostream>

using std::make_unique;

const unsigned kDefaultBPP = 32;

void Packer::Pack() {
    // Sort by max-side descending

    std::sort(bitmaps_.begin(), bitmaps_.end(),
              [](const Bitmap& a, const Bitmap& b) -> bool {
        return std::max(a.width(), a.height())
             > std::max(b.width(), b.height());
    });

    // Create empty root node, sized to fit first bitmap
    auto root = make_unique<Node>(0, 0,
            bitmaps_.front().width(),
            bitmaps_.front().height());

    // Generate texture map tree
    for (int i = 0; i < bitmaps_.size(); ++i) {
        auto width = bitmaps_[i].width();
        auto height = bitmaps_[i].height();

        auto node = FindNode(root, width, height);

        if (node) {
            std::cout << "Split node\n";
            node = SplitNode(node, width, height);
        } else {
            std::cout << "Grow node\n";
            node = GrowNode(root.get(), width, height);
        }

        // Assign bitmap ptr to node
        node->bitmap = &bitmaps_[i];
    }

    // TODO: init empty spritesheet

    //GenerateTextureMap(root.get());
    //GenerateMetadata(root.get());
}

void Packer::Export(string_view filename) {
    spritesheet_->Save("atlas.png");
}

void Packer::GenerateTextureMap(Node *node) {
    if (node == nullptr) {
        return;
    }

    if (node->bitmap != nullptr) {
        spritesheet_->Paste(node->x, node->y, *node->bitmap);
    }
    GenerateTextureMap(node->right.get());
    GenerateTextureMap(node->down.get());
}

void Packer::GenerateMetadata(Node *node) {
    // TODO: Generate metadata
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

Node* Packer::SplitNode(Node *node, int width, int height) {
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

    return node;
}

Node *Packer::GrowRight(Node *root, int width, int height) {
    auto newRoot = std::make_unique<Node>
            (0, 0, root->width + width, root->height);

    newRoot->bitmap = root->bitmap;
    newRoot->right = std::make_unique<Node>
            (root->width, 0, width, root->height);

    newRoot->down = unique_ptr<Node>(root);

    // Override the root pointer
    root = newRoot.get();

    if (auto node = FindNode(newRoot, width, height)) {
        return SplitNode(node, width, height);
    }

    return nullptr;
}

Node *Packer::GrowDown(Node *root, int width, int height) {
    auto newRoot = std::make_unique<Node>
            (0, 0, root->width, root->height + height);

    newRoot->bitmap = root->bitmap;
    newRoot->down = std::make_unique<Node>
            (0, root->height, root->width, height);
    newRoot->right = unique_ptr<Node>(root);

    // Override the root pointer
    root = newRoot.get();

    if (auto node = FindNode(newRoot, width, height)) {
        return SplitNode(node, width, height);
    }

    return nullptr;
}

Node* Packer::GrowNode(Node *root, int width, int height) {
    auto can_grow_right = height <= root->height;
    auto can_grow_down = width <= root->width;

    auto should_grow_right = can_grow_right && root->height >= (root->width + width);
    auto should_grow_down = can_grow_down && root->width >= (root->height + height);

    if (should_grow_right) return GrowRight(root, width, height);
    if (should_grow_down) return GrowDown(root, width, height);
    if (can_grow_right) return GrowRight(root, width, height);
    if (can_grow_down) return GrowDown(root, width, height);

    return nullptr;
}

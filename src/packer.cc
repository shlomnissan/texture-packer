// Copyright 2020 Betamark Pty Ltd.
// Author: Shlomi Nissan

#include "packer.h"

#include <algorithm>

#include "rectangle.h"

using std::make_unique;

void Packer::Pack() {
    // Sort by max-side descending
    Rectangle::SortMaxSide compare_max_side;
    std::stable_sort(bitmaps_.begin(), bitmaps_.end(), compare_max_side);

    // Create empty root node, sized to fit first bitmap
    root_ = make_unique<Node>(0, 0,
        bitmaps_.front().width(),
        bitmaps_.front().height());

    // Generate texture map tree
    for (int i = 0; i < bitmaps_.size(); ++i) {
        auto width = bitmaps_[i].width();
        auto height = bitmaps_[i].height();

        auto node = FindNode(root_, width, height);

        if (node) {
            node = SplitNode(node, width, height);
        } else {
            node = GrowNode(width, height);
        }

        // Assign bitmap ptr to node
        node->bitmap = &bitmaps_[i];
    }

    spritesheet_ = std::make_unique<Bitmap>
            (root_->width, root_->height, /* bpp = */ 32);
}

void Packer::Export(const string& filename) {
    GenerateTextureMap(root_.get());
    spritesheet_->Save(filename + ".png");
    metadata_.Save(filename + ".json");
}

void Packer::AddBitmap(Bitmap &&bitmap) {
    bitmaps_.emplace_back(std::move(bitmap));
}

void Packer::GenerateTextureMap(Node *node) {
    if (node == nullptr) {
        return;
    }

    if (node->used && node->bitmap != nullptr) {
        // Save image
        spritesheet_->Paste(node->x, node->y, *node->bitmap);
        metadata_.Write(node);
    }

    GenerateTextureMap(node->right.get());
    GenerateTextureMap(node->down.get());
}

Node* Packer::FindNode(const unique_ptr<Node>& root, int width, int height) {
    if (root->used) {
        if (auto right = FindNode(root->right, width, height)) {
            return right;
        }
        return FindNode(root->down, width, height);
    } else if (width <= root->width && height <= root->height) {
        return root.get();
    } else {
        return nullptr;
    }
}

Node* Packer::SplitNode(Node *node, int width, int height) {
    node->used = true;

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

Node *Packer::GrowRight(int width, int height) {
    auto newRoot = std::make_unique<Node>
            (0, 0, root_->width + width, root_->height);

    newRoot->used = true;
    newRoot->right = std::make_unique<Node>
            (root_->width, 0, width, root_->height);

    newRoot->down = std::move(root_);

    // Override the root pointer
    root_ = std::move(newRoot);

    if (auto node = FindNode(root_, width, height)) {
        return SplitNode(node, width, height);
    }

    return nullptr;
}

Node *Packer::GrowDown(int width, int height) {
    auto newRoot = std::make_unique<Node>
            (0, 0, root_->width, root_->height + height);

    newRoot->used = true;
    newRoot->down = std::make_unique<Node>
            (0, root_->height, root_->width, height);
    newRoot->right = std::move(root_);

    // Override the root pointer
    root_ = std::move(newRoot);

    if (auto node = FindNode(root_, width, height)) {
        return SplitNode(node, width, height);
    }

    return nullptr;
}

Node* Packer::GrowNode(int width, int height) {
    auto can_grow_right = height <= root_->height;
    auto can_grow_down = width <= root_->width;

    auto should_grow_right =
            can_grow_right && root_->height >= (root_->width + width);
    auto should_grow_down =
            can_grow_down && root_->width >= (root_->height + height);

    if (should_grow_right) return GrowRight(width, height);
    if (should_grow_down) return GrowDown(width, height);
    if (can_grow_right) return GrowRight(width, height);
    if (can_grow_down) return GrowDown(width, height);

    return nullptr;
}

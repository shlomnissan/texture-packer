//
// Created by Shlomi Nissan on 1/25/20.
//

#include "packer.h"

#include <algorithm>

void Packer::Pack() {
    // sort by max-side descending
    std::sort(bitmaps.begin(), bitmaps.end(),
            [](const Bitmap& a, const Bitmap& b) -> bool {
        return std::max(a.get_width(), a.get_height())
             > std::max(b.get_width(), b.get_height());
    });

    // create empty root node
    auto root = new Node(0, 0, 128, 64);

    // generate texture map tree
    for (const auto& bitmap : bitmaps) {
        auto node = FindNode(root, bitmap.get_width(),
                                   bitmap.get_height());
        if (node) {
            SplitNode(node, bitmap.get_width(),
                            bitmap.get_height());
        }
    }

    // traverse texture tree
}

void Packer::Export(string_view filename) {

}

Node* Packer::FindNode(Node *root, int width, int height) {
    if (root->used) {
        auto right = FindNode(root->right, width, height);
        if (right) return right;
        return FindNode(root->down, width, height);
    } else if (width <= root->width && height <= root->height) {
        return root;
    } else {
        return nullptr;
    }
}

void Packer::SplitNode(Node *node, int width, int height) {
    node->used = true;
    node->right = new Node(node->x + width,
                           node->y,
                           node->width - width,
                           height);
    node->down = new Node(node->x,
                          node->y + height,
                          width,
                          node->height - height);
}

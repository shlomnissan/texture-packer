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
    for (int i = 0; i < bitmaps.size(); ++i) {
        auto node = FindNode(root, bitmaps[i].get_width(),
                                   bitmaps[i].get_height());
        if (node) {
            SplitNode(node, &bitmaps[i]);
        }
    }

    // traverse texture tree
}

void Packer::Export(string_view filename) {

}

Node* Packer::FindNode(Node *root, int width, int height) {
    if (root->bitmap) {
        auto right = FindNode(root->right, width, height);
        if (right) return right;
        return FindNode(root->down, width, height);
    } else if (width <= root->width && height <= root->height) {
        return root;
    } else {
        return nullptr;
    }
}

void Packer::SplitNode(Node *node, Bitmap* bitmap_ptr) {
    node->bitmap = bitmap_ptr;
    auto width = bitmap_ptr->get_width();
    auto height = bitmap_ptr->get_height();

    // create right node
    node->right = new Node(node->x + width,
                           node->y,
                           node->width - width,
                           height);

    // create down node
    node->down = new Node(node->x,
                          node->y + height,
                          width,
                          node->height - height);
}

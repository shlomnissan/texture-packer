//
// Created by Shlomi Nissan on 1/25/20.
//

#ifndef SRC_NODE_
#define SRC_NODE_

#include "bitmap.h"

struct Node {
    int x, y;
    int width, height;
    bool used = false;

    Node* right = nullptr;
    Node* down = nullptr;

    Node(int x, int y, int w, int h)
        : x(x), y(y), width(w), height(h) {}
};

#endif  // SRC_NODE_
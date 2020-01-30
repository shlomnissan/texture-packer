// Copyright 2020 Betamark Pty Ltd.
// Author: Shlomi Nissan

#ifndef SRC_NODE_
#define SRC_NODE_

#include <memory>

#include "bitmap.h"

using std::unique_ptr;

struct Node {
    int x, y;
    int width, height;

    Bitmap* bitmap = nullptr;
    unique_ptr<Node> right;
    unique_ptr<Node> down;

    Node(int x, int y, int w, int h)
        : x(x), y(y), width(w), height(h) {}
};

#endif  // SRC_NODE_
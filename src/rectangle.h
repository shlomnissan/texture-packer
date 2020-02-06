//
// Created by Shlomi Nissan on 2/6/20.
//

#ifndef SRC_RECTANGLE_H_
#define SRC_RECTANGLE_H_

#include <algorithm>

class Rectangle {
public:
    Rectangle() = default;

    Rectangle(unsigned width, unsigned height)
            : width_(width), height_(height) {}

    unsigned width() const { return width_; }
    unsigned height() const { return height_; }
    unsigned area() const { return width_ * height_; }
    unsigned max_side() const { return std::max(width_, height_); }

    class SortMaxSide {
    public:
        bool operator() (const Rectangle& lhs, const Rectangle& rhs) {
            return lhs.max_side() > rhs.max_side();
        }
    };

protected:
    unsigned width_;
    unsigned height_;
};

#endif  //SRC_RECTANGLE_H_

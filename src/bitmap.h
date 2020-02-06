// Copyright 2020 Betamark Pty Ltd.
// Author: Shlomi Nissan

#ifndef SRC_BITMAP_H_
#define SRC_BITMAP_H_

#include <string>
#include <string_view>
#include <algorithm>

#include <FreeImage.h>

#include "rectangle.h"

using std::string;
using std::string_view;

class Bitmap : public Rectangle {
public:
    explicit Bitmap(string_view source);
    Bitmap(unsigned width, unsigned height, unsigned bpp);
    Bitmap(Bitmap&& rhs) noexcept;
    Bitmap(const Bitmap& rhs) = delete;  // Delete copy constructor

    Bitmap& operator=(Bitmap&& rhs);
    Bitmap& operator=(const Bitmap& rhs) = delete;  // Delete copy assignment

    const char* path() const { return path_.c_str(); }
    FIBITMAP* data() const { return bitmap_; }

    bool LoadBitmap(string_view path);
    bool Paste(unsigned x, unsigned y, const Bitmap& bmp);
    void Save(string_view path);

    ~Bitmap();

private:
    string path_;
    FIBITMAP* bitmap_ {nullptr };
};

#endif  // SRC_BITMAP_H_

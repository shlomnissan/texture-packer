// Copyright 2020 Betamark Pty Ltd.
// Author: Shlomi Nissan

#ifndef SRC_BITMAP_H_
#define SRC_BITMAP_H_

#include <string>
#include <string_view>
#include <algorithm>

#include <FreeImage.h>

using std::string;
using std::string_view;

class Bitmap {
public:
    explicit Bitmap(string_view source);
    Bitmap(int width, int height, int bpp);
    Bitmap(Bitmap&& rhs);
    Bitmap(const Bitmap& rhs) = delete;  // Delete copy constructor

    Bitmap& operator=(Bitmap&& rhs);
    Bitmap& operator=(const Bitmap& rhs) = delete;  // Delete copy assignment

    unsigned width() const { return width_; }
    unsigned height() const { return height_; }
    const char* path() const { return path_.c_str(); }
    FIBITMAP* data() const { return bitmap_; }

    bool LoadBitmap(string_view path);
    bool Paste(int x, int y, const Bitmap& bmp);
    void Save(string_view path);

    ~Bitmap();

private:
    unsigned width_ {0 };
    unsigned height_ {0 };

    string path_;

    FIBITMAP* bitmap_ {nullptr };
};

#endif  // SRC_BITMAP_H_

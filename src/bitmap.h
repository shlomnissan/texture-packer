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



    unsigned get_width() const { return width; }
    unsigned get_height() const { return height; }
    FIBITMAP* data() const { return bitmap; }
    const char* get_path() const { return path.c_str(); }

    bool LoadBitmap(string_view path);
    bool Paste(int x, int y, const Bitmap& bmp);
    void Save(string_view path);

    ~Bitmap();

private:
    unsigned width { 0 };
    unsigned height { 0 };

    string path;

    FIBITMAP* bitmap { nullptr };
};

#endif  // SRC_BITMAP_H_

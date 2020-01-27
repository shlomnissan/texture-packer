//
// Created by Shlomi Nissan on 1/24/20.
//

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
    Bitmap(Bitmap&& rhs);

    Bitmap& operator=(Bitmap&& rhs);

    bool operator<(const Bitmap& rhs) {
        return std::max(width, height) > std::max(rhs.width, rhs.height);
    }

    Bitmap(const Bitmap& rhs) = delete;
    Bitmap& operator=(const Bitmap& rhs) = delete;

    unsigned get_width() const { return width; }
    unsigned get_height() const { return height; }
    const char* get_path() const { return path.c_str(); }

    bool LoadBitmap(string_view path);
    void Save(string_view path);

    ~Bitmap();

private:
    unsigned width { 0 };
    unsigned height { 0 };

    string path;

    FIBITMAP* bitmap { nullptr };
};

#endif  // SRC_BITMAP_H_

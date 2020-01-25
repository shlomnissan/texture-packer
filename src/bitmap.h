//
// Created by Shlomi Nissan on 1/24/20.
//

#ifndef SRC_BITMAP_H_
#define SRC_BITMAP_H_

#include <string>
#include <string_view>

#include <FreeImage.h>

using std::string;
using std::string_view;

class Bitmap {
public:
    Bitmap(string_view source);

    unsigned width() const { return w; }
    unsigned height() const { return h; }
    const char* src() const { return path.c_str(); }

    bool LoadBitmap(string_view path);
    void Save(string_view path);

    ~Bitmap();
private:
    unsigned w { 0 };
    unsigned h { 0 };

    string path;

    FIBITMAP* bitmap { nullptr };
};

#endif  // SRC_BITMAP_H_

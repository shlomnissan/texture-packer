//
// Created by Shlomi Nissan on 1/24/20.
//

#ifndef SRC_FREE_IMAGE_H_
#define SRC_FREE_IMAGE_H_

#include <string>
#include <string_view>

#include <FreeImage.h>

using std::string;
using std::string_view;

class FreeImage {
public:
    FreeImage(): bitmap(nullptr), path(""), w(0), h(0) {}

    unsigned width() const { return w; }
    unsigned height() const { return h; }
    const char* src() const { return path.c_str(); }

    bool LoadBitmap(string_view path);
    void Save(string_view path);

    ~FreeImage();
private:
    FIBITMAP* bitmap;
    string path;
    unsigned w;
    unsigned h;
};

#endif  // SRC_FREE_IMAGE_H_

//
// Created by Shlomi Nissan on 1/24/20.
//

#ifndef TEXTURE_PACKER_FREE_IMAGE_H_
#define TEXTURE_PACKER_FREE_IMAGE_H_

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

    ~FreeImage();
private:
    FIBITMAP* bitmap;
    string path;
    unsigned w;
    unsigned h;
};

#endif //TEXTURE_PACKER_FREE_IMAGE_H_

//
// Created by Shlomi Nissan on 1/24/20.
//

#include "bitmap.h"

#include <iostream>

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

Bitmap::Bitmap(string_view source) : path(source.data()) {
    if (!fs::exists(path)) {
        throw std::runtime_error("Can't open file " + path);
    }
    LoadBitmap(path);
}

Bitmap::Bitmap(Bitmap &&rhs) {
    bitmap = rhs.bitmap;
    path = rhs.path;
    w = rhs.w;
    h = rhs.h;

    rhs.bitmap = nullptr;
    rhs.path = "";
    rhs.w = 0; rhs.h = 0;
}

bool Bitmap::LoadBitmap(string_view src) {
    path = src;

    FREE_IMAGE_FORMAT fif { FreeImage_GetFIFFromFilename(path.data()) };
    if (fif != FIF_UNKNOWN) {
        bitmap = FreeImage_Load(fif, path.data());
        w = FreeImage_GetWidth(bitmap);
        h = FreeImage_GetHeight(bitmap);

        return true;
    }

    return false;
}

void Bitmap::Save(string_view path) {
    FreeImage_Save(FIF_PNG, bitmap, path.data());
}

Bitmap::~Bitmap() {
    if (!bitmap) return;

    FreeImage_Unload(bitmap);
    bitmap = nullptr;
}

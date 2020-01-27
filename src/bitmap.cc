//
// Created by Shlomi Nissan on 1/24/20.
//

#include "bitmap.h"

#include <experimental/filesystem>

#include <iostream>

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
    width = rhs.width;
    height = rhs.height;

    rhs.bitmap = nullptr;
    rhs.path = "";
    rhs.width = 0; rhs.height = 0;
}

Bitmap &Bitmap::operator=(Bitmap &&rhs) {
    if (this != &rhs) {
        FreeImage_Unload(bitmap);
        bitmap = rhs.bitmap;
        path = rhs.path;
        width = rhs.width;
        height = rhs.height;

        rhs.bitmap = nullptr;
        rhs.path = "";
        rhs.width = 0; rhs.height = 0;
    }
    return *this;
}

bool Bitmap::LoadBitmap(string_view src) {
    path = src;

    FREE_IMAGE_FORMAT fif { FreeImage_GetFIFFromFilename(path.data()) };
    if (fif != FIF_UNKNOWN) {
        bitmap = FreeImage_Load(fif, path.data());
        width = FreeImage_GetWidth(bitmap);
        height = FreeImage_GetHeight(bitmap);

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

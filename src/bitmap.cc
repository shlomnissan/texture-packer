// Copyright 2020 Betamark Pty Ltd.
// Author: Shlomi Nissan

#include "bitmap.h"

#include <experimental/filesystem>

#include <iostream>

namespace fs = std::experimental::filesystem;

Bitmap::Bitmap(string_view source) : path_(source.data()) {
    if (!fs::exists(path_)) {
        throw std::runtime_error("Can't open file " + path_);
    }
    LoadBitmap(path_);
}

Bitmap::Bitmap(int width, int height, int bpp)
    : width_(width),
      height_(height),
      bitmap_(FreeImage_Allocate(width, height, bpp)) {}

Bitmap::Bitmap(Bitmap &&rhs) noexcept {
    bitmap_ = rhs.bitmap_;
    path_ = rhs.path_;
    width_ = rhs.width_;
    height_ = rhs.height_;

    rhs.bitmap_ = nullptr;
    rhs.path_ = "";
    rhs.width_ = 0; rhs.height_ = 0;
}

Bitmap &Bitmap::operator=(Bitmap &&rhs) {
    if (this != &rhs) {
        FreeImage_Unload(bitmap_);
        bitmap_ = rhs.bitmap_;
        path_ = rhs.path_;
        width_ = rhs.width_;
        height_ = rhs.height_;

        rhs.bitmap_ = nullptr;
        rhs.path_ = "";
        rhs.width_ = 0; rhs.height_ = 0;
    }
    return *this;
}

bool Bitmap::LoadBitmap(string_view src) {
    path_ = src;

    FREE_IMAGE_FORMAT fif { FreeImage_GetFIFFromFilename(path_.data()) };
    if (fif != FIF_UNKNOWN) {
        bitmap_ = FreeImage_Load(fif, path_.data());
        width_ = FreeImage_GetWidth(bitmap_);
        height_ = FreeImage_GetHeight(bitmap_);

        return true;
    }

    return false;
}

bool Bitmap::Paste(int x, int y, const Bitmap &bmp) {
    return FreeImage_Paste(bitmap_, bmp.data(), x, y, /* alpha = */ 255);
}

void Bitmap::Save(string_view path) {
    FreeImage_Save(FIF_PNG, bitmap_, path.data());
}

Bitmap::~Bitmap() {
    if (!bitmap_) return;

    FreeImage_Unload(bitmap_);
    bitmap_ = nullptr;
}

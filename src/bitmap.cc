// Copyright 2020 Betamark Pty Ltd.
// Author: Shlomi Nissan

#include "bitmap.h"

#include <filesystem>
#include <iostream>
#include <utility>

namespace fs = std::filesystem;

Bitmap::Bitmap(string_view source) : path_(source.data()) {
    if (!fs::exists(path_)) {
        throw std::runtime_error("Can't open file " + path_);
    }
    LoadBitmap(path_);
}

Bitmap::Bitmap(unsigned width, unsigned height, unsigned bpp)
    : bitmap_(FreeImage_Allocate(width, height, bpp)) {
      width_ = width;
      height_ = height;
}

Bitmap::Bitmap(Bitmap &&rhs) noexcept
    : bitmap_(std::exchange(rhs.bitmap_, nullptr)),
      path_(std::move(rhs.path_)) {
      width_ = rhs.width_;
      height_ = rhs.height_;
}

Bitmap &Bitmap::operator=(Bitmap &&rhs) {
    if (this != &rhs) {
        if (bitmap_) {
            FreeImage_Unload(bitmap_);
        }
        bitmap_ = std::exchange(rhs.bitmap_, nullptr);
        path_ = std::move(rhs.path_);
        width_ = rhs.width_;
        height_ = rhs.height_;
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

bool Bitmap::Paste(unsigned x, unsigned y, const Bitmap &bmp) {
    return FreeImage_Paste(bitmap_, bmp.data(), x, y, /* alpha = */ 255);
}

void Bitmap::Save(string_view path) {
    FreeImage_Save(FIF_PNG, bitmap_, path.data());
}

Bitmap::~Bitmap() {
    if (!bitmap_) return;

    FreeImage_Unload(bitmap_);
}

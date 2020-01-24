//
// Created by Shlomi Nissan on 1/24/20.
//

#include <iostream>

#include "free_image.h"

bool FreeImage::LoadBitmap(string_view src) {
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

FreeImage::~FreeImage() {
    if (!bitmap) return;

    FreeImage_Unload(bitmap);
    bitmap = nullptr;
}

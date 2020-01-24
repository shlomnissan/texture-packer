//
// Created by Shlomi Nissan on 1/24/20.
//

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

void FreeImage::Save(string_view path) {
    FreeImage_Save(FIF_PNG, bitmap, path.data());
}

FreeImage::~FreeImage() {
    if (!bitmap) return;

    FreeImage_Unload(bitmap);
    bitmap = nullptr;
}

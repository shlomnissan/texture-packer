//
// Created by Shlomi Nissan on 1/24/20.
//

#include "bitmap.h"

Bitmap::Bitmap(string_view source) : path(source.data()) {
    // TODO: throw if file doesn't exist
    // std::filesystem::exists("helloworld.txt");
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

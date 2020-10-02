#pragma once

#include <vector>

namespace gum {

struct Image {
    std::vector<unsigned char> pixels;
    unsigned int width;
    unsigned int height;
};

Image load_bmp(const char* fileName);

}

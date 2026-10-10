#include "fast/resource/type/Texture.h"

#include <atomic>

namespace Fast {
namespace {
std::atomic<uint64_t> gTextureIdentityCounter{ 0 };
} // namespace

Texture::Texture() : Resource(std::shared_ptr<Ship::ResourceInitData>()) {
}

uint64_t Texture::NextIdentity() {
    return ++gTextureIdentityCounter;
}

uint8_t* Texture::GetPointer() {
    return ImageData;
}

size_t Texture::GetPointerSize() {
    return ImageDataSize;
}

Texture::~Texture() {
    if (ImageData != nullptr && !mImageBuffer) {
        delete[] ImageData;
    }
}
} // namespace Fast

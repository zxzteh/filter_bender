#include "utils.h"

std::vector<uint8_t> qByteArrayToVector(const QByteArray& byteArray)
{
    const uint8_t* data = reinterpret_cast<const uint8_t*>(byteArray.data());
    size_t size = byteArray.size();
    return std::vector<uint8_t>(data, data + size);
}

#include "color.h"

namespace {

template<typename T>
T Clamp(const float unclamped, const T max) {
    if (unclamped < 0)
        return 0;
    if (unclamped > 1)
        return max;
    return std::round(unclamped * max);
}

}

namespace RT {

ColorClamped8Bit Color::Clamp8Bit() const {
    const unsigned int MAX_VALUE = 255;

    return ColorClamped8Bit({
        Clamp<unsigned int>(this->Red(), MAX_VALUE),
        Clamp<unsigned int>(this->Green(), MAX_VALUE),
        Clamp<unsigned int>(this->Blue(), MAX_VALUE),
    });
}

}

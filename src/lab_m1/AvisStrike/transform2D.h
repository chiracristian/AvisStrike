#pragma once

#include "utils/glm_utils.h"

namespace transf2D
{
    // Translate
    inline glm::mat3 translate(float translateX, float translateY)
    {
        return glm::mat3(       1.f,        0.f, 0.f,
                                0.f,        1.f, 0.f,
                         translateX, translateY, 1.f);
    }

    // Scale
    inline glm::mat3 scale(float scaleX, float scaleY)
    {
        return glm::mat3(scaleX,    0.f, 0.f,
                            0.f, scaleY, 0.f,
                            0.f,    0.f, 1.f);
    }

    // Rotate counterclockwise
    inline glm::mat3 rotate(float radians)
    {
        float sine = std::sin(radians);
        float cosine = std::cos(radians);

        return glm::mat3(cosine,   sine, 0.f,
                          -sine, cosine, 0.f,
                            0.f,    0.f, 1.f);
    }

    // Flip an object horizontally across the origin
    inline glm::mat3 flipHorizontal()
    {
        return scale(-1.f, 1.f);
    }
}   // namespace transform2D

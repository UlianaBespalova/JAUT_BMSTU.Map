#ifndef BMSTU_MAP_CORE_GEOMETRY_HPP
#define BMSTU_MAP_CORE_GEOMETRY_HPP

#include "utils.hpp"

namespace Core {
    namespace Geometry {
        typedef double geometry_t;

        struct Vector2 {
            geometry_t x, y;

            Vector2(geometry_t X, geometry_t Y) : x(X), y(Y) { }
            Vector2() : Vector2(0, 0) { }
        };

        typedef Vector2 Point;

        inline void from_json(const json &j, Vector2 &v)
        {
            j.at(0).get_to(v.x);
            j.at(1).get_to(v.y);
        }
    }
}


#endif //BMSTU_MAP_CORE_GEOMETRY_HPP

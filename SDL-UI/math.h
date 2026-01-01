#ifndef __MATH_H__
#define __MATH_H__


namespace GUI
{
    namespace math
    {
        class vector2D
        {
            public:
                float x,y;

            public:
                vector2D() {}
                vector2D(const float& X, const float& Y) : x(X) , y(Y) {}
                vector2D(const vector2D& other) : x(other.x), y(other.y) {}
        };
    };
};

#endif
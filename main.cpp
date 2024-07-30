#include <iostream>
#include "vector_math.h"
#include "matrix_transformations.h",
#include <string>
#include "ppm.h"

int main()
{
    PPM ppm {256};
    Vector v{0,100};
    Matrix m{rotation('z',30,3)};
    for (int iter {0}; iter < 12; ++iter)
    {
        ppm(static_cast<int>(v(0))+127,static_cast<int>(v(1))+127) = "0 0 0";
        v = m*v;
    }
    ppm.save("yey");
    return 0;
}

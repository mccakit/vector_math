#include <iostream>
#include "vector_math.h"
#include "matrix_transformations.h",
#include <string>
#include "ppm.h"

int main()
{
    PPM ppm {256};
    Vector v{0,100,0,1};
    const Matrix rotate{rotation('z',30,4)};
    const Matrix move{translation(127,127,0)};
    const Matrix combined{move*rotate};
    const Matrix inv_move{inverse(move)};
    for (int iter {0}; iter < 12; ++iter)
    {
        v = combined*v;
        ppm(static_cast<int>(v(0)),static_cast<int>(v(1))) = "0 0 0";
        v = inv_move*v;
    }
    ppm.save("yey");
    return 0;
}

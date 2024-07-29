#include <iostream>
#include "vector_math.h"

int main()
{
    Matrix A{{3,3,-4,6},{-9,8,4,5},{7,2,4,-1},{3,-9,1,1}};
    Matrix B{{8,3,7,6},{2,-1,0,-2},{2,7,5,0},{2,0,4,5}};
    Matrix C {A*B};
    std::cout << A << std::endl;
    std::cout << C*inverse(B) << std::endl;
    return 0;
}

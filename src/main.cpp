#include <iostream>
#include "matrix.h"

using std::cout;
using std::endl;

int main()
{
    Matrix myMatrix {{4,8,3,10},{11,13,9,3},{4,4,7,2},{7,2,12,3}};
    cout << myMatrix.get_determinant() << endl;
    return 0;
}
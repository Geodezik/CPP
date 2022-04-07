#include "directions.hpp"

int wants_to(int number, int N, int direction)
{
    switch(direction) {
        case UL:
            if((number > N - 1) && (number % N != 0))
                return number - N - 1;
            break;
        case U:
            if(number > N - 1)
                return number - N;
            break;
        case UR:
            if((number > N - 1) && (number % N != N - 1))
                return number - N + 1;
            break;
        case L:
            if(number % N != 0)
                return number - 1;
            break;
        case R:
            if(number % N != N - 1)
                return number + 1;
            break;
        case DL:
            if((number % N != 0) && (number < N*(N-1)))
                return number + N - 1;
            break;
        case D:
            if(number < N*(N-1))
                return number + N;
            break;
        case DR:
            if((number % N != N - 1) && (number < N*(N-1)))
                return number + N + 1;
            break;
    }
    return number;        
}

int opposite_direction(int direction)
{
    switch(direction) {
        case UL:
            return DR;
        case U:
            return D;
        case UR:
            return DL;
        case L:
            return R;
        case R:
            return L;
        case DL:
            return UR;
        case D:
            return U;
        case DR:
            return UL;
    }

    return R;
}
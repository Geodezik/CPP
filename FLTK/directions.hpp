#ifndef DIRECTIONS_H
#define DIRECTIONS_H

// DO NOT CHANGE!!!!!!!!!!!!!!!!!!
enum {
    UL,
    U,
    UR,
    L,
    R,
    DL,
    D,
    DR
};

int wants_to(int number, int N, int direction);
int opposite_direction(int direction);

#endif
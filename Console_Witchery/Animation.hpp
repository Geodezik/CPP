#ifndef ANIMATION_H
#define ANIMATION_H

#include "array.hpp"
#include <iostream>

namespace Animation {
    enum params {
        H = 50,
        W = 150
    };
    class Phase;
    class AnimatedImage;
};

class Animation::Phase
{
    int minphase;
    int maxphase;
    int curphase;
    bool up;

public:
    Phase(int Min, int Max): minphase(Min), maxphase(Max), curphase(0) {}

    operator int()
    {
        return curphase;
    }

    int getValue();

    void next();

    bool inc();
};

class Animation::AnimatedImage
{
    Array<const char**> images;
    int xsize;
    int ysize;
    Phase phase;
    bool up;

public:
    AnimatedImage(int x, int y, int frames): xsize(x), ysize(y), phase(0, frames - 1), up(true), images() {}; 

    void addImage(const char **img);

    const char **getImage();

    int getx();

    int gety();

    void next();
};

#include "Animation.cpp"

#endif
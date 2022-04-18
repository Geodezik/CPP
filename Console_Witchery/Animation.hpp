#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <vector>

namespace Animation {
    enum params {
        H = 50,
        W = 150
    };
    class Phase;
    class AnimatedImage;
};

//example for Phase(-1, 2): 0 1 2 1 0 -1 0 1 2 1 0 -1 0...
class Animation::Phase
{
    int minphase;
    int maxphase;
    int curphase;
    bool up;

public:
    Phase(int Min, int Max): minphase(Min), maxphase(Max), curphase(0) {}
    int getValue();
    int getmin();
    int getmax();
    void next();
    void inverse();
    bool inc();

    operator int()
    {
        return curphase;
    }

    Phase operator=(int val)
    {
        curphase = val;
        return *this;
    }
};

class Animation::AnimatedImage
{
    std::vector<const char**> images;
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

#endif
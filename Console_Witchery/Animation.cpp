#include "Animation.hpp"
#include <iostream>

using namespace Animation;

int Phase::getValue()
{
    return curphase;
}

int Phase::getmin()
{
    return minphase;
}

int Phase::getmax()
{
    return maxphase;
}

int AnimatedImage::getx()
{
    return xsize;
}

int AnimatedImage::gety()
{
    return ysize;
}

void Phase::next()
{
    if(up)
        curphase++;
    else
        curphase--;

    if(curphase > maxphase) {
        up = false;
        curphase -= 2;
        return;
    }

    if(curphase < minphase) {
        up = true;
        curphase += 2;
        return;
    }
}

void Phase::inverse()
{
    up = !up;
}

bool Phase::inc()
{
    return up;
}

void AnimatedImage::addImage(const char **img)
{
    images.push_back(img);
}

const char **AnimatedImage::getImage()
{
    return images[phase];
}

void AnimatedImage::next()
{
    phase.next();
}
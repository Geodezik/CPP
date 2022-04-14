#include "Animation.hpp"
#include <iostream>

using namespace Animation;

int Phase::getValue()
{
    return curphase;
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

bool Phase::inc()
{
    return up;
}

void AnimatedImage::addImage(const char **img)
{
    images.insertAtEnd(img);
}

const char **AnimatedImage::getImage()
{
    std::cout << "CUR PHASE IS " << (int) phase << std::endl;
    return images[phase];
}

void AnimatedImage::next()
{
    phase.next();
}
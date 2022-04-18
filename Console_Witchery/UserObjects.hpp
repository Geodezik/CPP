#ifndef USER_OBJ_H
#define USER_OBJ_H

#include "Animation.hpp"
#include "AnimatedObjects.hpp"

namespace UserObjects {
    class Witch; //part of figure
    class Broom; //part of figure
    class WitchAndBroom; //figure

    class Triangle; //part of figure
    class Rectangle; //part of figure
    class SpruceTree; //figure

    class MoonPart; //part of figure
    class Moon; //figure

    class FallingStarPart; //part of figure
    class FallingStar; //figure
};

using namespace UserObjects;

class UserObjects::Witch: public DrawnWithPasting
{
public:
    Witch(int x_shift, int y_shift, Animation::AnimatedImage *image);

    virtual void move();
};

class UserObjects::Broom: public DrawnWithPasting
{
private:
    //Witch and broom are easier to draw with pasting
    virtual void draw(char (&drawing)[Animation::H][Animation::W]) {}
public:
    Broom(int x_shift, int y_shift, Animation::AnimatedImage *image);

    virtual void move();
};

class UserObjects::WitchAndBroom: public Figure
{
public:
    WitchAndBroom(int x_start = 0, int y_start = 0);

    virtual void draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh);

    virtual void move();

    virtual ~WitchAndBroom() {}
};

class UserObjects::Triangle: public DrawnWithoutPasting
{
public:
    Triangle(int x_shift, int y_shift);

    virtual void draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh);

    virtual void move();
};

class UserObjects::Rectangle: public DrawnWithoutPasting
{
public:
    Rectangle(int x_shift, int y_shift);

    virtual void draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh);

    virtual void move();
};

class UserObjects::SpruceTree: public Figure
{
public:
    SpruceTree(int x_start = 0, int y_start = 0);

    virtual void draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh);

    virtual void move();

    virtual ~SpruceTree() {}
};

class UserObjects::MoonPart: public DrawnWithPasting
{
private:
    //Moon is easier to draw with pasting
    virtual void draw(char (&drawing)[Animation::H][Animation::W]) {}
public:
    MoonPart(int x_shift, int y_shift, Animation::AnimatedImage *image);
    void switch_img()
    {
        if(*phases[0] == 20)
            next_image();
    }
    virtual void move() {};
};

class UserObjects::Moon: public Figure
{
public:
    Moon(int x_start = 0, int y_start = 0);

    virtual void draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh);

    virtual void move();

    virtual ~Moon() {}
};

class UserObjects::FallingStarPart: public DrawnWithPasting
{
private:
    //Star is easier to draw with pasting
    virtual void draw(char (&drawing)[Animation::H][Animation::W]) {}
public:
    FallingStarPart(int x_shift, int y_shift, Animation::AnimatedImage *image);
    void switch_img();
    virtual void move() {};
};

class UserObjects::FallingStar: public Figure
{
public:
    FallingStar(int x_start = 0, int y_start = 0);
    virtual void draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh);
    virtual void move();
    virtual ~FallingStar() {}
};


#endif
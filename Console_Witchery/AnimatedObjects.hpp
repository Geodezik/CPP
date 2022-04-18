#ifndef ANIMATED_OBJ_H
#define ANIMATED_OBJ_H

#include <iostream>
#include <vector>
#include "Animation.hpp"

namespace AnimatedObjects {
    class FigurePart;
    class DrawnWithPasting;
    class DrawnWithoutPasting;
    class Figure;
};

using namespace AnimatedObjects;

class AnimatedObjects::Figure
{
protected:
    int x;
    int y;
    std::vector<FigurePart*> parts;

public:
    Figure(int x_, int y_): x(x_), y(y_), parts(std::vector<FigurePart*>()) {}

    virtual void draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh) = 0;
    virtual void move() = 0;

    virtual ~Figure();
};

class AnimatedObjects::FigurePart: public Figure
{
protected:
    std::vector<Animation::Phase*> phases;
    Animation::AnimatedImage *img;

public:
    FigurePart(int x_shift, int y_shift, Animation::AnimatedImage *image = nullptr): Figure(x_shift, y_shift), img(image) {}

    void update_phases();

    void randomize_phases(int threshold = 0);

    int get_img_x()
    {
        return img->getx();
    }

    int get_img_y()
    {
        return img->gety();
    }

    void next_image()
    {
        img->next();
    }

    virtual ~FigurePart();
};

class AnimatedObjects::DrawnWithPasting: public FigurePart
{
private:
    //Witch and broom are easier to draw with pasting
    virtual void draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh) {}
public:
    DrawnWithPasting(int x_shift, int y_shift, Animation::AnimatedImage *image): FigurePart(x_shift, y_shift, image) {}
    void paste_image(char (&drawing)[Animation::H][Animation::W], int x_size_of_drawing_area, int y_size_of_drawing_area, int x, int y);
};

class AnimatedObjects::DrawnWithoutPasting: public FigurePart
{
public:
    DrawnWithoutPasting(int x_shift, int y_shift): FigurePart(x_shift, y_shift, nullptr) {}
};

#endif
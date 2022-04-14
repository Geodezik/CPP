#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include "array.hpp"
#include "Animation.hpp"
#include "images_collection.hpp"

//animated_art + draw/redraw methods + shift_of_coords + (maybe) next?
namespace PiecesOfArt {
    class FigurePart;
    class Witch;
    class Broom;
    class Figure;
    class WitchAndBroom;
};

using namespace PiecesOfArt;

class PiecesOfArt::FigurePart
{
protected:
    int delta_x;
    int delta_y;
    Array<Animation::Phase*> phases;
    Animation::AnimatedImage *img;

    void update_phases()
    {
        for(int i = 0; i < phases.getLength(); i++)
            phases[i]->next();
    }

public:
    FigurePart(int x_shift, int y_shift, AnimatedImage *image): delta_x(x_shift), delta_y(y_shift), img(image) {}

    virtual void adjust_deltas() = 0;

    void draw_part(char (&drawing)[Animation::H][Animation::W], const char **image, int xlen, int ylen, int x, int y)
    {
        //std::cout << "HERE" << std::endl;
        for(int i = 0; i < xlen; i++) {
            for(int j = 0; j < ylen; j++) {
                if(((x + delta_x + i) / Animation::H) || ((y + delta_y + j) / Animation::W) || (x + delta_x + i < 0) || (y + delta_y + j < 0))
                    continue;
                if(image[i][j] == ' ')
                    continue;
                drawing[(x + delta_x + i) % Animation::H][(y + delta_y + j) % Animation::W] = image[i][j];
            }
        }

        update_phases();
        adjust_deltas();
    }

    virtual ~FigurePart()
    {
        for(int i = 0; i < phases.getLength(); i++)
            delete phases[i];
        delete img;
    }

    friend Figure;
    friend WitchAndBroom;
};

class PiecesOfArt::Witch: public FigurePart
{
public:
    Witch(int x_shift, int y_shift, AnimatedImage *image): FigurePart(x_shift, y_shift, image)
    {
        phases.insertAtEnd(new Phase(-4, 4));
        phases.insertAtEnd(new Phase(-4, 4));
    }

    virtual void adjust_deltas()
    {
        delta_x += *phases[0] / (4 - 1);
        delta_y += *phases[1] / 4;
    }
};

class PiecesOfArt::Broom: public FigurePart
{
public:
    Broom(int x_shift, int y_shift, AnimatedImage *image): FigurePart(x_shift, y_shift, image)
    {
        phases.insertAtEnd(new Phase(-4, 4));
        phases.insertAtEnd(new Phase(-4, 4));
    }

    virtual void adjust_deltas()
    {
        delta_x += *phases[0] / (4 - 1);
        delta_y -= *phases[1] / 4;
    }
};

class PiecesOfArt::Figure
{
protected:
    int x;
    int y;
    Array<FigurePart*> parts;

public:
    Figure(int x_, int y_): x(x_), y(y_), parts(Array<FigurePart*>()) {}

    virtual void draw(char (&drawing)[Animation::H][Animation::W], int x, int y) = 0;
    //virtual void move() = 0;

    virtual ~Figure()
    {
        for(int i = 0; i < parts.getLength(); i++)
            delete parts[i];
    }
};

void Figure::draw(char (&drawing)[Animation::H][Animation::W], int x, int y)
{
    for(int i = 0; i < parts.getLength(); i++) {
        parts[i]->draw_part(drawing, parts[i]->img->getImage(), parts[i]->img->getx(), parts[i]->img->gety(), x, y);
        parts[i]->img->next();
    }
}

class PiecesOfArt::WitchAndBroom: public Figure
{
public:
    WitchAndBroom(int x_start = 0, int y_start = 0): Figure(x_start, y_start)
    {
        Animation::AnimatedImage *broom = new AnimatedImage(20, 100, 6);
        for(int i = 0; i < 6; i++)
            broom->addImage(images_collection::brooms[i]);
        parts.insertAtEnd(new Broom(23, 0, broom));

        Animation::AnimatedImage *witch = new AnimatedImage(46, 100, 8);
        for(int i = 0; i < 8; i++)
            witch->addImage(images_collection::witches[i]);
        parts.insertAtEnd(new Witch(0, 0, witch));

        //std::cout << "HERE" << std::endl;
    }

    virtual void draw(char (&drawing)[Animation::H][Animation::W], int x, int y)
    {
        Figure::draw(drawing, x, y);
    }

    virtual ~WitchAndBroom() {}
};

#endif
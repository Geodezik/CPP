#include "AnimatedObjects.hpp"

using namespace AnimatedObjects;

void FigurePart::update_phases()
{
    for(int i = 0; i < phases.size(); i++)
        phases[i]->next();
}

void FigurePart::randomize_phases(int threshold)
{   
    for(int i = 0; i < phases.size(); i++) {
        int delta = phases[i]->getmax() - phases[i]->getmin();
        int ranphase = phases[i]->getmax() - rand() % (delta + 1) - threshold;
        if(ranphase < phases[i]->getmin())
            ranphase = phases[i]->getmin();
        *phases[i] = ranphase;
    }
}

void DrawnWithPasting::paste_image(char (&drawing)[Animation::H][Animation::W], int x_size_of_drawing_area, int y_size_of_drawing_area, int x, int y)
{
    const char **image = img->getImage();
    for(int i = 0; i < x_size_of_drawing_area; i++) {
        for(int j = 0; j < y_size_of_drawing_area; j++) {
            if(((x + this->x + i) / Animation::H) || ((y + this->y + j) / Animation::W) || (x + this->x + i < 0) || (y + this->y + j < 0))
                continue;
            if(image[i][j] == ' ')
                continue;
            drawing[(x + this->x + i) % Animation::H][(y + this->y + j) % Animation::W] = image[i][j];
        }
    }

    update_phases();
}

FigurePart::~FigurePart()
{
    for(int i = 0; i < phases.size(); i++)
        delete phases[i];
    delete img;
}

Figure::~Figure()
{
    for(int i = 0; i < parts.size(); i++)
        delete parts[i];
}
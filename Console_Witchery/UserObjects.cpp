#include "UserObjects.hpp"
#include "images_collection.hpp"

Witch::Witch(int x_shift, int y_shift, Animation::AnimatedImage *image): DrawnWithPasting(x_shift, y_shift, image)
{
    phases.push_back(new Animation::Phase(-4, 4));
    phases.push_back(new Animation::Phase(-4, 4));
}

void Witch::move()
{
    x += *phases[0] / (4 - 1);
    y += *phases[1] / 4;
}

Broom::Broom(int x_shift, int y_shift, Animation::AnimatedImage *image): DrawnWithPasting(x_shift, y_shift, image)
{
    phases.push_back(new Animation::Phase(-4, 4));
    phases.push_back(new Animation::Phase(-4, 4));
}

void Broom::move()
{
    x += *phases[0] / (4 - 1);
    y -= *phases[1] / 4;
}

WitchAndBroom::WitchAndBroom(int x_start, int y_start): Figure(x_start, y_start)
{
    Animation::AnimatedImage *broom = new Animation::AnimatedImage(20, 100, 6);
    for(int i = 0; i < 6; i++)
        broom->addImage(images_collection::brooms[i]);
    parts.push_back(new Broom(23, 0, broom));

    Animation::AnimatedImage *witch = new Animation::AnimatedImage(46, 100, 8);
    for(int i = 0; i < 8; i++)
        witch->addImage(images_collection::witches[i]);
    parts.push_back(new Witch(0, 0, witch));
}

void WitchAndBroom::draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh)
{
    for(int i = 0; i < parts.size(); i++) {
        DrawnWithPasting *obj = dynamic_cast<DrawnWithPasting*>(parts[i]);
        obj->paste_image(drawing, parts[i]->get_img_x(), parts[i]->get_img_y(), x + xh, y + yh);
        parts[i]->next_image();
    }
}

void WitchAndBroom::move()
{
    for(int i = 0; i < parts.size(); i++)
        parts[i]->move();
}

Triangle::Triangle(int x_shift, int y_shift): DrawnWithoutPasting(x_shift, y_shift)
{
    phases.push_back(new Animation::Phase(-15, 15));
    phases[0]->inverse();
    phases.push_back(new Animation::Phase(-15, 15));
}

void Triangle::draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh)
{
    for(int i = x + xh; i < x + xh + 15; i++) {
        int delta = i - x - xh;
        int center = y + yh;
        for(int j = center - delta ; j <= center + delta; j++) {
            if((i / Animation::H) || (j / Animation::W) || (i < 0) || (j < 0))
                continue;
            if((j == center - delta) || (j == center + delta) || (i == x + xh + 15 - 1))
                drawing[i][j] = '&';
            else
                drawing[i][j] = '*';
        }
    }
}

void Triangle::move()
{
    y += (*phases[0] == 13);
    y -= (*phases[1] == -4);
    phases[0]->next();
    phases[1]->next();
}

Rectangle::Rectangle(int x_shift, int y_shift): DrawnWithoutPasting(x_shift, y_shift) {}

void Rectangle::draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh)
{
    for(int i = x + xh; i < x + xh + 5; i++) {
        for(int j = y + yh; j < y + yh + 5; j++) {
            if((i / Animation::H) || (j / Animation::W) || (i < 0) || (j < 0))
                continue;
            drawing[i][j] = '*';
        }
    }
}

void Rectangle::move() {}

SpruceTree::SpruceTree(int x_start, int y_start): Figure(x_start, y_start)
{
    int randseed;
    FILE *f = fopen("/dev/urandom", "r");
    if (!fread(&randseed, sizeof(int), 1, f))
        exit(0);
    srand(randseed);
    fclose(f);

    parts.push_back(new Triangle(24, 0));
    parts[0]->randomize_phases();
    parts.push_back(new Triangle(12, 0));
    parts[1]->randomize_phases();
    parts.push_back(new Triangle(0, 0));
    parts[2]->randomize_phases();
    parts.push_back(new Rectangle(39, -2));
}

void SpruceTree::draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh)
{
    for(int i = 0; i < parts.size(); i++)
        parts[i]->draw(drawing, x + xh, y + yh);
}

void SpruceTree::move()
{
    y++;
    if(y > Animation::W + 15)
        y = -15;
    for(int i = 0; i < parts.size(); i++)
        parts[i]->move();
}

MoonPart::MoonPart(int x_shift, int y_shift, Animation::AnimatedImage *image): DrawnWithPasting(x_shift, y_shift, image)
{
    phases.push_back(new Animation::Phase(0, 25));
}

Moon::Moon(int x_start, int y_start): Figure(x_start, y_start)
{
    Animation::AnimatedImage *moon_img = new Animation::AnimatedImage(21, 55, 2);
    for(int i = 0; i < 2; i++)
        moon_img->addImage(images_collection::moons[i]);
    parts.push_back(new MoonPart(0, 0, moon_img));
}

void Moon::draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh)
{
    DrawnWithPasting *obj = dynamic_cast<DrawnWithPasting*>(parts[0]);
    obj->paste_image(drawing, parts[0]->get_img_x(), parts[0]->get_img_y(), x + xh, y + yh);

    MoonPart *moonpart = dynamic_cast<MoonPart*>(parts[0]);
    moonpart->switch_img();
}

void Moon::move()
{
    parts[0]->move();
}

FallingStarPart::FallingStarPart(int x_shift, int y_shift, Animation::AnimatedImage *image): DrawnWithPasting(x_shift, y_shift, image)
{
    phases.push_back(new Animation::Phase(0, 50));
}

void FallingStarPart::switch_img()
{
    if(*phases[0] > 46)
        next_image();
    if((*phases[0] == 46) && !phases[0]->inc()) {
        for(int i = 0; i < 7; i++)
            next_image();
    }
    
}

FallingStar::FallingStar(int x_start, int y_start): Figure(x_start, y_start)
{
    Animation::AnimatedImage *star_img = new Animation::AnimatedImage(5, 10, 8);
    for(int i = 0; i < 9; i++)
        star_img->addImage(images_collection::falling_stars[i]);
    parts.push_back(new FallingStarPart(0, 0, star_img));

    int randseed;
    FILE *f = fopen("/dev/urandom", "r");
    if (!fread(&randseed, sizeof(int), 1, f))
        exit(0);
    srand(randseed);
    fclose(f);

    parts[0]->randomize_phases(10);
}

void FallingStar::draw(char (&drawing)[Animation::H][Animation::W], int xh, int yh)
{
    DrawnWithPasting *obj = dynamic_cast<DrawnWithPasting*>(parts[0]);
    obj->paste_image(drawing, parts[0]->get_img_x(), parts[0]->get_img_y(), x + xh, y + yh);

    FallingStarPart *starpart = dynamic_cast<FallingStarPart*>(parts[0]);
    starpart->switch_img();
}

void FallingStar::move()
{
    parts[0]->move();
}
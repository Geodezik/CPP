#ifndef STAGE_H
#define STAGE_H

#include "array.hpp"
#include "settings.hpp"
#include "cell.hpp"

class Stage
{
    Array<Cell*> *stage;
    Choice *settings;
    int n;
    int seed;
public:
    Stage(Array<Fl_Button*> &buttons, int N, Choice *settings, int s);
    void set_settings(Choice *new_settings);
    Array<Cell*> *empty_stage();
    void step();
    Array<Cell*> &get_stage();
    int get_n();
    Choice *get_settings();
    ~Stage();
    static void clear_board(Fl_Widget *, void *user);
};

#endif
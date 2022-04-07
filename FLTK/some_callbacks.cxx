#include "some_callbacks.hpp"

void Empty::empty_callback(Fl_Widget *w, void *user)
{
    Callback_config *conf = (Callback_config*) user;

    switch(conf->settings->get_mode()) {
        case 0: {
                delete (stage->get_stage())[conf->number];
                (stage->get_stage())[conf->number] = new Balloon(conf->button, conf->number, R);
                (stage->get_stage())[conf->number]->cell_button->image(Balloon::get_image());
                break;
        }
        case 1: {
                delete (stage->get_stage())[conf->number];
                (stage->get_stage())[conf->number] = new Bubble(conf->button, conf->number, R);
                (stage->get_stage())[conf->number]->cell_button->image(Bubble::get_image());
                break;
        }
        default: {
            delete (stage->get_stage())[conf->number];
            (stage->get_stage())[conf->number] = new Empty(conf->button, conf->number);
            ErrorScreen error;
            error.show();
        }
    }
    delete conf;
}

void Balloon::balloon_callback(Fl_Widget *w, void *user)
{
    Callback_config *conf = (Callback_config*) user;

    switch(conf->settings->get_mode()) {
        case 2: {
                delete (stage->get_stage())[conf->number];
                (stage->get_stage())[conf->number] = new Empty(conf->button, conf->number);
                (stage->get_stage())[conf->number]->cell_button->image(0);
                break;
        }
        default:
            delete (stage->get_stage())[conf->number];
            (stage->get_stage())[conf->number] = new Balloon(conf->button, conf->number, R);
            ErrorScreen error;
            error.show();
    }

    delete conf;
}

void Bubble::bubble_callback(Fl_Widget *w, void *user)
{
    Callback_config *conf = (Callback_config*) user;

    switch(conf->settings->get_mode()) {
        case 3: {
                delete (stage->get_stage())[conf->number];
                (stage->get_stage())[conf->number] = new Empty(conf->button, conf->number);
                (stage->get_stage())[conf->number]->cell_button->image(0);
                break;
        }
        default:
            delete (stage->get_stage())[conf->number];
            (stage->get_stage())[conf->number] = new Bubble(conf->button, conf->number, R);
            ErrorScreen error;
            error.show();
    }

    delete conf;
}

void exit_callback(Fl_Widget *, void *user)
{
    exit(0);
}

void Stage::clear_board(Fl_Widget *, void *user)
{
    Stage *stage = (Stage*) user;
    int k = stage->n;

    for(int i = 0; i < k*k; i++){
        if((*stage->stage)[i])
            (*stage->stage)[i]->kill_preset();
        Cell *p = new Empty((*stage->stage)[i]->get_button(), i);
        p->get_button()->image(0);
        p->get_button()->redraw();
        if((*stage->stage)[i])
            delete (*stage->stage)[i];
        (*stage->stage)[i] = p;
    }
}

void step_callback(Fl_Widget *, void *user)
{
    Stage *stage = (Stage*) user;
    stage->step();
}
#ifndef APP_H
#define APP_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.H>
#include <iostream>
#include "settings.hpp"
#include "stage.hpp"
#include "array.hpp"
#include "some_callbacks.hpp"

class App
{
    Array<Fl_Button*> buttons;
    Fl_Window *win;
    Fl_JPEG_Image* balloon_img;
    Fl_JPEG_Image* bubble_img;
    Fl_JPEG_Image* logo;
    Stage *stage;
    Choice *settings;
    Fl_Button *quit_button;
    Fl_Button *clear_button;
    Fl_Button *nextstep_button;

public:
    App(int N, int seed, float resize_by);
    void run();
    ~App();
};

#endif
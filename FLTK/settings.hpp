#ifndef SETTINGS_H
#define SETTINGS_H
#include <FL/Fl_Radio_Round_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Image.H>

enum {
    default_win_w = 750,
    default_win_h = 750
};

class Choice
{
    Fl_Radio_Round_Button *rb[4];
    Fl_Check_Button *random_button;
    int mode;
public:
    Choice(int win_w, int win_h);
    int get_mode();
    bool get_check();
    ~Choice();
};

class ErrorScreen
{
    Fl_Window *win;
    Fl_Box *box;
    int w;
    int h;
public:
    ErrorScreen(int width = default_win_w, int height = default_win_h): win(nullptr), box(nullptr), w(width/2), h(height/2) {}
    void show();
};

struct Callback_config
{
    int number;
    Choice *settings;
    Fl_Button *button;
};

Fl_JPEG_Image *resize(Fl_JPEG_Image *img, int button_w, int button_h);

#endif
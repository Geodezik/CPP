#include "settings.hpp"

Choice::Choice(int win_w, int win_h)
{
    rb[0] = new Fl_Radio_Round_Button(win_w/16, win_h/16, win_w/6, win_h/16, "Add balloon");
    rb[1] = new Fl_Radio_Round_Button(win_w/16 + 12*win_w/16 / 3, win_h/16, win_w/6, win_h/16, "Add bubble");
    rb[2] = new Fl_Radio_Round_Button(win_w/16 + 12*win_w/16 * 2/3, win_h/16, win_w/6, win_h/16, "Take balloon");
    rb[3] = new Fl_Radio_Round_Button(win_w/16 + 12*win_w/16, win_h/16, win_w/6, win_h/16, "Burst bubble");
    
    random_button = new Fl_Check_Button(3*win_w/4, 0, win_w/4, win_h/16, "FULL RANDOM MODE \n(IGNORE SEED)");
    random_button->color2(FL_RED);
}

int Choice::get_mode()
{
    int i;
    for(i = 0; i < 4; i++) {
        if(rb[i]->value()) {
            break;
        }
    }
    return i;
}

bool Choice::get_check()
{
    return random_button->value();
}

Choice::~Choice()
{
    for(int i = 0; i < 4; i++) {
        delete rb[i];
    }
    delete random_button;
}

void ErrorScreen::show()
{
    win = new Fl_Window(w, h, "ERROR");
    win->color(FL_WHITE);
    box = new Fl_Box(0, 0, w, h, "INCORRECT OPTION!!!");
    box->labelcolor(FL_BLACK);

    win->end();
    win->show();
}

Fl_JPEG_Image *resize(Fl_JPEG_Image *img, int button_w, int button_h)
{
    if (img->w() > button_w || img->h() > button_h) {
        Fl_Image *temp;
        if (img->w() > img->h()) {
            temp = img->copy(button_w, button_h * img->h() / img->w());
        } else {
            temp = img->copy(button_w * img->w() / img->h(), button_h);
        }
        delete img;
        img = (Fl_JPEG_Image *) temp;
    }

    return img;
}
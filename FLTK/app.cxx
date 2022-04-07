#include "app.hpp"

App::App(int N, int seed, float resize_by)
{
    int win_h = default_win_h * resize_by;
    int win_w = default_win_w * resize_by;

    win = new Fl_Window(win_w, win_h, "Bubbles VS Balloons");

    settings = new Choice(win_w, win_h);

    balloon_img = new Fl_JPEG_Image("./images/balloon.jpg");
    if(!balloon_img) {
        std::cerr << "Error: ./images/balloon.jpg not found" << std::endl;
        exit(-1);
    }
    bubble_img = new Fl_JPEG_Image("./images/bubble.jpg");
    if(!bubble_img) {
        std::cerr << "Error: ./images/bubble.jpg not found" << std::endl;
        exit(-1);
    }
    logo = new Fl_JPEG_Image("./images/logo.jpg");
    if(!logo) {
        std::cerr << "Error: ./images/logo.jpg not found" << std::endl;
        exit(-1);
    }

    balloon_img = resize(balloon_img, win_w / N, 3*win_h /4 / N);
    bubble_img = resize(bubble_img, win_w / N, 3*win_h /4 / N);
    win->icon(logo);
    win->color(FL_CYAN);
    Balloon::set_image(balloon_img);
    Bubble::set_image(bubble_img);
    
    buttons = Array<Fl_Button*>();
    for(int i = 0; i < N*N; i++) {
        buttons.insertAtEnd(new Fl_Button(win_w * (i%N) / N, win_h / 8 + (3*win_h)*(i/N)/(4*N), win_w/N, 3*win_h/(4*N)));
        buttons[i]->color(FL_CYAN);
        buttons[i]->color2(FL_BLUE);
    }

    stage = new Stage(buttons, N, settings, seed);

    clear_button = new Fl_Button(0, 0, 3*win_w/4, win_h/16, "CLEAR BOARD");
    clear_button->color(FL_MAGENTA);
    clear_button->callback(Stage::clear_board, stage);

    nextstep_button = new Fl_Button(0, 7*win_h/8, win_w/2, win_h/8, "Next step");
    nextstep_button->callback(step_callback, stage);
    nextstep_button->color(FL_GREEN);

    quit_button = new Fl_Button(win_w/2, 7*win_h/8, win_w/2, win_h/8, "Quit");
    quit_button->callback(exit_callback, stage);
    quit_button->color(FL_RED);

    win->end();
    win->show();
}

void App::run()
{
    Fl::run();
}

App::~App()
{
    int k = stage->get_n();
    for(int i = 0; i < k*k; i++)
        delete buttons[i];
    delete win;
    delete balloon_img;
    delete bubble_img;
    delete logo;
    //...
}
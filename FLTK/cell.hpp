#ifndef CELL_H
#define CELL_H
#include "settings.hpp"
#include "array.hpp"
#include "directions.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_JPEG_Image.H>
#include <time.h>
#include <chrono>
#include <thread>

class Stage;
class Bubble;
class Empty;
class Balloon;
class Round;

class Cell
{
protected:
    static Stage *stage;
    static Choice *settings;
    static Array<int> *table_of_applicants;
    Callback_config *preset;
    int number;
    bool moved;
    Fl_Button *cell_button;
public:
    Cell();
    Cell(Fl_Button *b, int i);
    virtual void decide(int seed, Choice *settings, bool second_iter = false) = 0;
    virtual bool can_be_moved(Array<Cell*> *stage, Array<int> *graph, int number, int N, bool alternative) = 0;
    virtual void move(Array<Cell*> *stage, Array<Cell*> *new_stage, int number, int N, bool second_iter = false) = 0;
    virtual bool is_empty() = 0;
    virtual void kill_bubble(Array<Cell*> *stage, Array<Cell*> *new_stage, Array<int> *new_table, int N) = 0;
    static void clear_table(int n);
    static void set_settings(Choice *new_settings);
    static void set_stage(Stage *new_stage);
    static Array<int> *get_table();
    static void set_table(Array<int> *new_table);
    void kill_preset();
    Fl_Button *get_button();
    virtual ~Cell() {}
    friend Round;
    friend Empty;
    friend Balloon;
    friend Bubble;
};

class Empty: public Cell
{
public:
    static void empty_callback(Fl_Widget *w, void *user);

    Empty();
    Empty(Fl_Button *b, int i);

    virtual void decide(int seed, Choice *settings, bool second_iter);
    virtual void move(Array<Cell*> *stage, Array<Cell*> *new_stage, int number, int N, bool second_iter);
    virtual bool can_be_moved(Array<Cell*> *stage, Array<int> *graph, int number, int N, bool alternative);
    virtual bool is_empty();
    virtual void kill_bubble(Array<Cell*> *stage, Array<Cell*> *new_stage, Array<int> *new_table, int N);
    virtual ~Empty();
};

class Round: public Cell
{
protected:
    int direction;
public:
    Round();
    Round(Fl_Button *b, int i, int dir);
    virtual void decide(int seed, Choice *settings, bool second_iter);
    virtual bool can_be_moved(Array<Cell*> *stage, Array<int> *graph, int number, int N, bool alternative) = 0;
    virtual void move(Array<Cell*> *stage, Array<Cell*> *new_stage, int number, int N, bool second_iter) {}
    virtual bool is_empty();
    virtual void kill_bubble(Array<Cell*> *stage, Array<Cell*> *new_stage, Array<int> *new_table, int N) = 0;
    virtual ~Round() {}
};

class Balloon: public Round
{
    static Fl_JPEG_Image *img;
public:
    Balloon();
    Balloon(Fl_Button *b, int i, int dir);
    static void balloon_callback(Fl_Widget *w, void *user);
    static void set_image(Fl_JPEG_Image *image);
    static Fl_JPEG_Image *get_image();
    virtual void move(Array<Cell*> *stage, Array<Cell*> *new_stage, int number, int N, bool second_iter);
    virtual bool can_be_moved(Array<Cell*> *stage, Array<int> *graph, int number, int N, bool alternative);
    virtual void kill_bubble(Array<Cell*> *stage, Array<Cell*> *new_stage, Array<int> *new_table, int N);
    virtual ~Balloon() {}
};

class Bubble: public Round
{
    static Fl_JPEG_Image *img;
public:
    Bubble();
    Bubble(Fl_Button *b, int i, int dir);
    static void bubble_callback(Fl_Widget *w, void *user);
    static void set_image(Fl_JPEG_Image *image);
    static Fl_JPEG_Image *get_image();
    virtual void move(Array<Cell*> *stage, Array<Cell*> *new_stage, int number, int N, bool second_iter);
    virtual bool can_be_moved(Array<Cell*> *stage, Array<int> *graph, int number, int N, bool alternative);
    virtual void kill_bubble(Array<Cell*> *stage, Array<Cell*> *new_stage, Array<int> *new_table, int N);
    virtual ~Bubble() {}
};
#endif
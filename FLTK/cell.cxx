#include "cell.hpp"

Cell::Cell() {}

Cell::Cell(Fl_Button *b, int i)
{
    cell_button = b;
    number = i;
    preset = nullptr;
    moved = false;
};

void Cell::clear_table(int n)
{
    if(!table_of_applicants) {
        table_of_applicants = new Array<int>(n*n);
    }

    for(int i = 0; i < n*n; i++) {
        (*table_of_applicants)[i] = 0;
    }
}

void Cell::set_settings(Choice *new_settings)
{
    if(settings && (settings != new_settings)) {
        delete settings;
    }
    settings = new_settings;
}

void Cell::set_stage(Stage *new_stage)
{
    stage = new_stage;
}

Array<int> *Cell::get_table()
{
    return table_of_applicants;
}

void Cell::set_table(Array<int> *new_table)
{
    if(table_of_applicants)
        delete table_of_applicants;
    table_of_applicants = new_table;
}

void Cell::kill_preset()
{
    if(preset)
        delete preset;
    preset = nullptr;
}

Fl_Button *Cell::get_button()
{
    return cell_button;
}

Empty::Empty() {}

Empty::Empty(Fl_Button *b, int i): Cell(b, i)
{
    Callback_config *conf = new Callback_config;
    conf->number = number;
    conf->settings = settings;
    conf->button = cell_button;
    preset = conf;
    cell_button->callback(empty_callback, conf);
}

void Empty::decide(int seed, Choice *settings, bool second_iter = false)
{
    moved = false;
}

void Empty::move(Array<Cell*> *stage, Array<Cell*> *new_stage, int number, int N, bool second_iter = false) {}

bool Empty::can_be_moved(Array<Cell*> *stage, Array<int> *graph, int number, int N, bool alternative)
{
    return true;
}

bool Empty::is_empty()
{
    return true;
}

void Empty::kill_bubble(Array<Cell*> *stage, Array<Cell*> *new_stage, Array<int> *new_table, int N)
{
    kill_preset();
    (*new_stage)[number] = new Empty(cell_button, number);
}

Empty::~Empty() {};

Round::Round() {}

Round::Round(Fl_Button *b, int i, int dir): Cell(b, i), direction(dir) {}

bool Round::is_empty()
{
    return false;
}

Balloon::Balloon() {}

Balloon::Balloon(Fl_Button *b, int i, int dir): Round(b, i, dir)
{
    Callback_config *conf = new Callback_config;
    conf->number = number;
    conf->settings = settings;
    conf->button = cell_button;
    preset = conf;
    cell_button->callback(balloon_callback, conf);
}

void Balloon::set_image(Fl_JPEG_Image *image)
{
    img = image;
}

Fl_JPEG_Image *Balloon::get_image()
{
    return img;
}

void Balloon::move(Array<Cell*> *stage, Array<Cell*> *new_stage, int number, int N, bool second_iter = false)
{
    int to = wants_to(number, N, direction);

    if(second_iter) {
        if(moved) {
            //std::cout << "Im already moved" << std::endl;
            (*stage)[number]->kill_preset();
            (*new_stage)[number] = new Balloon(cell_button, number, direction);
            (*new_stage)[number]->moved = true;
            return;
        }
    }

    Array<int> *graph = new Array<int>;
    delete graph;
    graph = new Array<int>;

    if(can_be_moved(stage, graph, number, N, second_iter)) {
        (*stage)[to]->kill_preset();
        if(second_iter) {
            if((*new_stage)[to])
                delete (*new_stage)[to];
        }
        (*new_stage)[to] = new Balloon((*stage)[to]->cell_button, to, direction);
        (*new_stage)[to]->moved = true;
        if(!(*new_stage)[number]) {
            (*stage)[number]->cell_button->image(0);
            (*stage)[number]->cell_button->redraw();
        }
        (*stage)[to]->cell_button->image(Balloon::get_image());
        (*stage)[to]->cell_button->redraw();
    } else {
        (*stage)[number]->kill_preset();
        if((*table_of_applicants)[to] >= 2) {
            (*new_stage)[number] = new Balloon(cell_button, number, opposite_direction(direction));
            (*new_stage)[number]->moved = false;
        }
        else if (to == number) {
            (*new_stage)[number] = new Balloon(cell_button, number, direction);
            (*new_stage)[number]->moved = true;
        }
        else {
            (*new_stage)[number] = new Balloon(cell_button, number, opposite_direction(direction));
            (*new_stage)[number]->moved = false;
        }
        cell_button->image(Balloon::get_image());
        cell_button->redraw();
    }
    
    delete graph;
}

bool Balloon::can_be_moved(Array<Cell*> *stage, Array<int> *graph, int number, int N, bool alternative)
{
    if(alternative) {
        if(moved)
            return false;
    }

    for(int i = 0; i < graph->getLength(); i++) {
        if((*graph)[i] == number) {
            if(i)
                return false;
            else 
                return true;
        }
    }

    graph->insertAtEnd(number);

    int to = wants_to(number, N, direction);
    if((*table_of_applicants)[to] > 1)
        return false;
    if(to == number)
        return false;
    if((*stage)[to]->is_empty())
        return true;
    
    return (*stage)[to]->can_be_moved(stage, graph, to, N, alternative);
}

Bubble::Bubble() {}

Bubble::Bubble(Fl_Button *b, int i, int dir): Round(b, i, dir)
{
    Callback_config *conf = new Callback_config;
    conf->number = number;
    conf->settings = settings;
    conf->button = cell_button;
    preset = conf;
    cell_button->callback(bubble_callback, conf);
}

void Bubble::set_image(Fl_JPEG_Image *image)
{
    img = image;
}

Fl_JPEG_Image *Bubble::get_image()
{
    return img;
}

void Bubble::move(Array<Cell*> *stage, Array<Cell*> *new_stage, int number, int N, bool second_iter = false)
{
    int to = wants_to(number, N, direction);

    if(second_iter) {
        if(moved) {
            if((*new_stage)[number])
                return;
            (*stage)[number]->kill_preset();
            (*new_stage)[number] = new Bubble(cell_button, number, direction);
            (*new_stage)[number]->moved = true;
            return;
        }
    }

    //std::cout << "BUBBLE " << number << " WANTS TO " << to << std::endl;
    Array<int> *graph = new Array<int>;
    
    if(can_be_moved(stage, graph, number, N, second_iter)) {
        (*stage)[to]->kill_preset();
        (*new_stage)[to] = new Bubble((*stage)[to]->cell_button, to, direction);
        (*new_stage)[to]->moved = true;
        if(!(*new_stage)[number]) {
            (*stage)[number]->cell_button->image(0);
            (*stage)[number]->cell_button->redraw();
        }
        (*stage)[to]->cell_button->image(Bubble::get_image());
        (*stage)[to]->cell_button->redraw();
    } else {
        (*stage)[number]->kill_preset();
        (*new_stage)[number] = new Bubble(cell_button, number, direction);
        (*new_stage)[number]->moved = true;
        cell_button->image(Bubble::get_image());
        cell_button->redraw();
    }
    
    delete graph;
}

bool Bubble::can_be_moved(Array<Cell*> *stage, Array<int> *graph, int number, int N, bool alternative)
{
    if(alternative)
        return true;

    for(int i = 0; i < graph->getLength(); i++) {
        if((*graph)[i] == number) {
            if(i)
                return false;
            else
                return true;
        }
    }

    graph->insertAtEnd(number);

    int to = wants_to(number, N, direction);
    if((*table_of_applicants)[to] > 1)
        return false;
    if(to == number)
        return false;
    if((*stage)[to]->is_empty())
        return true;
    
    return can_be_moved(stage, graph, to, N, alternative);
}

Choice *Cell::settings = nullptr;
Stage *Cell::stage = nullptr;
Array<int> *Cell::table_of_applicants = nullptr;
Fl_JPEG_Image *Bubble::img = nullptr;
Fl_JPEG_Image *Balloon::img = nullptr;
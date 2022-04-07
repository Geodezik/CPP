#include "stage.hpp"
#include <iostream>

Stage::Stage(Array<Fl_Button*> &buttons, int N, Choice *settings, int s)
{
    n = N;
    seed = s;
    srand(seed);
    Cell::set_settings(settings);
    stage = new Array<Cell*>(n*n);
    this->settings = settings;
    for(int i = 0; i < N*N; i++) {
        buttons[i]->image(0);
        buttons[i]->redraw();
        (*stage)[i] = new Empty(buttons[i], i);
    }
    Cell::set_stage(this);
}

void Stage::set_settings(Choice *new_settings)
{
    (*stage)[0]->set_settings(new_settings);
}

Array<Cell*> *Stage::empty_stage()
{
    Array<Cell*> *new_stage = new Array<Cell*>(n*n);
    for(int i = 0; i < n*n; i++) {
        (*new_stage)[i] = nullptr;
    }
    return new_stage;
}

void Stage::step()
{
    (*stage)[0]->clear_table(n*n);
    for(int i = 0; i < n*n; i++)
        (*stage)[i]->decide(seed, settings);

    Array<Cell*> *new_stage = empty_stage();
    Array<int> *new_table = (*stage)[0]->get_table()->copy();
    for(int i = 0; i < n*n; i++)
        (*stage)[i]->kill_bubble(stage, new_stage, new_table, n);
    (*stage)[0]->set_table(new_table);

    for(int i = 0; i < n*n; i++)
        delete (*stage)[i];
    delete stage;
    stage = new_stage;
    
    new_stage = empty_stage();
    for(int i = 0; i < n*n; i++) {
        (*stage)[i]->move(stage, new_stage, i, n);
    }
    
    for(int i = 0; i < n*n; i++) {
        if(!(*new_stage)[i]) {
            (*stage)[i]->kill_preset();
            (*new_stage)[i] = new Empty((*stage)[i]->get_button(), i);
        }
    }

    for(int i = 0; i < n*n; i++) {
        delete (*stage)[i];
    }
    delete stage;
    stage = new_stage;
    
    //2nd IRERATION
    
    new_table = new Array<int>(n*n);
    for(int i = 0; i < n*n; i++)
        (*new_table)[i] = 0;
    (*stage)[0]->set_table(new_table);
    for(int i = 0; i < n*n; i++)
        (*stage)[i]->decide(seed, settings, true);

    new_stage = empty_stage();
    for(int i = 0; i < n*n; i++) 
        (*stage)[i]->move(stage, new_stage, i, n, true);
    

    for(int i = 0; i < n*n; i++) {
        if(!(*new_stage)[i]) {
            (*stage)[i]->kill_preset();
            (*new_stage)[i] = new Empty((*stage)[i]->get_button(), i);
        }
    }

    for(int i = 0; i < n*n; i++) 
        delete (*stage)[i];
    delete stage;
    stage = new_stage;

    //3rd iteration

    new_table = new Array<int>(n*n);
    for(int i = 0; i < n*n; i++)
        (*new_table)[i] = 0;
    (*stage)[0]->set_table(new_table);
    for(int i = 0; i < n*n; i++)
        (*stage)[i]->decide(seed, settings, true);

    new_stage = empty_stage();
    for(int i = 0; i < n*n; i++) {
        (*stage)[i]->move(stage, new_stage, i, n, true);
    }

    for(int i = 0; i < n*n; i++) {
        if(!(*new_stage)[i]) {
            (*stage)[i]->kill_preset();
            (*new_stage)[i] = new Empty((*stage)[i]->get_button(), i);
        }
    }

    for(int i = 0; i < n*n; i++) {
        delete (*stage)[i];
    }
    delete stage;
    stage = new_stage;

    (*stage)[0]->set_table(nullptr);
}

Array<Cell*> &Stage::get_stage()
{
    return *stage;
}

int Stage::get_n()
{
    return n;
}

Choice *Stage::get_settings()
{
    return settings;
}

Stage::~Stage()
{   
    delete stage;
}

void Round::decide(int seed, Choice *settings, bool second_iter)
{
    int N = stage->get_n();
    if(moved && second_iter) {
        (*table_of_applicants)[number]++;
        return;
    }
    moved = false;

    if(!second_iter) {
        if(!settings->get_check()) {
            direction = rand() % 8;
            //std::cout << direction << std::endl;
        } else {
            int altseed;
            FILE *f = fopen("/dev/urandom", "r");
            if (!fread(&altseed, sizeof(int), 1, f))
                exit(0);
            srand(altseed);
            fclose(f);
            direction = rand() % 8;
        }
    }

    switch(direction) {
        case UL:
            if((number > N - 1) && (number % N != 0))
                (*table_of_applicants)[number - N - 1]++;
            else
                (*table_of_applicants)[number]++;
            break;
        case U:
            if(number > N - 1)
                (*table_of_applicants)[number - N]++;
            else
                (*table_of_applicants)[number]++;
            break;
        case UR:
            if((number > N - 1) && (number % N != N-1))
                (*table_of_applicants)[number - N + 1]++;
            else
                (*table_of_applicants)[number]++;
            break;
        case L:
            if(number % N != 0)
                (*table_of_applicants)[number - 1]++;
            else
                (*table_of_applicants)[number]++;
            break;
        case R:
            if(number % N != N - 1)
                (*table_of_applicants)[number + 1]++;
            else
                (*table_of_applicants)[number]++;
            break;
        case DL:
            if((number < N*(N-1)) && (number % N != 0))
                (*table_of_applicants)[number + N - 1]++;
            else
                (*table_of_applicants)[number]++;
            break;
        case D:
            if(number < N*(N-1))
                (*table_of_applicants)[number + N]++;
            else
                (*table_of_applicants)[number]++;
            break;
        case DR:
            if((number < N*(N-1)) && (number % N != N - 1))
                (*table_of_applicants)[number + N + 1]++;
            else
                (*table_of_applicants)[number]++;
            break;
    }
}

void Balloon::kill_bubble(Array<Cell*> *stage, Array<Cell*> *new_stage, Array<int> *new_table, int N)
{
    kill_preset();
    (*new_stage)[number] = new Balloon(cell_button, number, direction);
}

void Bubble::kill_bubble(Array<Cell*> *stage, Array<Cell*> *new_stage, Array<int> *new_table, int N)
{
    int to = wants_to(number, N, direction);

    Array<int> *graph = new Array<int>;
    if(((*table_of_applicants)[number] > 1) || ((!can_be_moved(stage, graph, number, N, false)) && (number != to))) {
        kill_preset();
        (*new_stage)[number] = new Empty(cell_button, number);
        cell_button->image(0);
        cell_button->redraw();
        (*new_table)[to]--;
    } else {
        kill_preset();
        (*new_stage)[number] = new Bubble(cell_button, number, direction);
    }
    delete graph;
}
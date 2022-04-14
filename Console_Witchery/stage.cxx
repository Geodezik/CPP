#ifndef STAGE_H
#define STAGE_H

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <atomic>
#include "array.hpp"
#include "Animation.hpp"
#include "Figure.hpp"
#include "images_collection.hpp"

namespace correctquit {
    std::atomic<bool> quit(false); //sigflag
    void sighandler(int);
}

//Ctrl+C case handler. All the destructors will be called correctly.
void correctquit::sighandler(int)
{
    correctquit::quit.store(true);
}

namespace stagespace {
    class Stage;
    void set_empty(char (&drawing)[Animation::H][Animation::W]);
    void print(char (&drawing)[Animation::H][Animation::W]);
}

void stagespace::set_empty(char (&drawing)[Animation::H][Animation::W])
{
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            drawing[i][j] = ' ';
        }
    }
}

void stagespace::print(char (&drawing)[Animation::H][Animation::W])
{
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            std::cout << drawing[i][j];
        }
        std::cout << std::endl;
    }
}

// + phase
class Stage
{
    Array<Figure*> objects;
    char drawing[Animation::H][Animation::W];
    struct sigaction *sa;
    int time;
public:
    Stage()
    {
        sa = new struct sigaction;
        sa->sa_handler = correctquit::sighandler;
        sigfillset(&sa->sa_mask);
        sigaction(SIGINT, sa, NULL);

        time = Animation::W;

        objects.insertAtEnd(new WitchAndBroom());
    }

    void run()
    {
        while(true) {
            stagespace::set_empty(drawing);
            objects[0]->draw(drawing, 3, time);
            stagespace::print(drawing);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            system("clear");

            time--;
            if(time < -100)
                time = Animation::W;

            if (correctquit::quit.load()) break;
        }   
    }

    ~Stage()
    {
        for(int i = 0; i < objects.getLength(); i++)
            delete objects[i];
        
        delete sa;
    }
};

#endif
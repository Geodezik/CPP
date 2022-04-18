#ifndef STAGE_H
#define STAGE_H

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <thread>

#include "Animation.hpp"
#include "AnimatedObjects.hpp"
#include "UserObjects.hpp"

#define STAGE_X 0
#define STAGE_Y 0

namespace stagespace {
    class Stage;
    void set_empty(char (&drawing)[Animation::H][Animation::W]);
    void print(char (&drawing)[Animation::H][Animation::W]);
};

using namespace stagespace;

class stagespace::Stage
{
    std::vector<Figure*> objects;
    char drawing[Animation::H][Animation::W];
    struct sigaction *sa;
    static bool quit;
public:

    Stage();
    static void setquit(bool val);
    void run();
    void prepare_for_magic();
    ~Stage();
};

#endif
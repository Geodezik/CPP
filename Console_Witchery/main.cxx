#include "Figure.hpp"
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <signal.h>
#include <unistd.h>
#include <atomic>
#include <cstring>

#include "stage.cxx"

int main()
{
    Stage stage;
    stage.run();

    return 0;
}
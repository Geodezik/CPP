#include "array.hpp"
#include "directions.hpp"
#include "settings.hpp"
#include "cell.hpp"
#include "stage.hpp"
#include "some_callbacks.hpp"
#include "app.hpp"
#include <iostream>

int main(int argv, char **argc)
{
    try {
        if(argv < 4) {
            throw("Error: not enough arguments (seed - N number (NxN buttons) - multiplier)");
        } else if (argv > 4)
            std::cerr << "Warning: last " << argv - 4 << " arguments will be ignored" << std::endl;

        int seed = atoi(argc[1]);
        int N = atoi(argc[2]);
        double resize_by = atof(argc[3]);

        if(N < 1)
            throw("Error: incorrect first argument (number of buttons)");
        else if(N >= 150)
            throw("Error: handling that many buttons is highly unrecommended");
        else if (N > 75)
            std::cerr << "Warning: many buttons can lead to undefined behaviour due to FLTK bugs" << std::endl;

        if(!seed)
            std::cerr << "Warning: incorrect second argument. Seed was set to 0 instead" << std::endl;

        if (resize_by <= 0)
            throw("Error: incorrect third argument (winsize multiplier)");
        else if(resize_by >= 3)
            std::cerr << "Warning: the window is too huge (" << N*default_win_w << " by " << N*default_win_h << ")" << std::endl;

        App app(N, seed, resize_by);
        app.run();

    } catch(char const *msg) {
        std::cerr << msg << std::endl;
        return -1;
    }

    return 0;
}
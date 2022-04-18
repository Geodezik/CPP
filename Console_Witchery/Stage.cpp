#include "Stage.hpp"

//sigflag init
bool Stage::quit = false;

//Ctrl+C case handler. All the destructors will be called correctly.
static void sighandler(int)
{
    Stage::setquit(true);
}

void stagespace::set_empty(char (&drawing)[Animation::H][Animation::W])
{
    for(int i = 0; i < Animation::H; i++) {
        for(int j = 0; j < Animation::W; j++) {
            drawing[i][j] = ' ';
        }
    }

    //some decorative stars at random places
    //I tried to use rand() but then the result is too unpredictable
    drawing[4][3] = '*';
    drawing[8][5] = '*';
    drawing[12][6] = '*';
    drawing[2][17] = '*';
    drawing[7][25] = '*';
    drawing[7][75] = '*';
    drawing[1][77] = '*';
    drawing[7][90] = '*';
    drawing[10][100] = '*';
}

void stagespace::print(char (&drawing)[Animation::H][Animation::W])
{
    for(int i = 0; i < Animation::H; i++) {
        for(int j = 0; j < Animation::W; j++) {
            std::cout << drawing[i][j];
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

Stage::Stage()
{
    Stage::setquit(false);

    sa = new struct sigaction;
    sa->sa_handler = sighandler;
    sigfillset(&sa->sa_mask);
    sigaction(SIGINT, sa, NULL);

    objects.push_back(new Moon(0, 5*Animation::W/9));
    objects.push_back(new FallingStar(0, 80));
    objects.push_back(new FallingStar(5, 10));
    objects.push_back(new SpruceTree(0, -15));
    objects.push_back(new WitchAndBroom(3, 10));
}

void Stage::setquit(bool val)
{
    quit = val;
}

void Stage::prepare_for_magic()
{
    system("clear");
    for(int i = 5; i > 0; i--) {
        std::cout << "Full screen is recommended. \033[1m\033[91mMagical things\033[0m will happen right here in " << i << " seconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        system("clear");
    }
}

void Stage::run()
{
    prepare_for_magic();
    while(true) {
        stagespace::set_empty(drawing);

        for(int i = 0; i < objects.size(); i ++) {
            objects[i]->draw(drawing, STAGE_X, STAGE_Y);
            objects[i]->move();
        }

        std::cout << std::endl;
        stagespace::print(drawing);

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        system("clear");

        if (quit) break;
    }   
}

Stage::~Stage()
{
    for(int i = 0; i < objects.size(); i++)
        delete objects[i];
    
    delete sa;
}
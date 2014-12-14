#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Controllers\State.h"
#include "Utils\Exception.h"
#include "Utils\Window.h"

class Game {
    public: 
        static Game& get();

        void start();

        Util::Window& getWindow();

    private: 
        Game();
        ~Game();

        Controller::State* getState();
        void setState(Controller::State* const newState);
    
        Util::Window* _window;
        Controller::State* _state;

    public:
        friend class Controller::State::Initialization;
        friend class Controller::State::Shutdown;
};

#endif
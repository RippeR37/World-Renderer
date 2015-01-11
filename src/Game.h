#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Controllers\State.h"

#include <Utils\Exception.h>
#include <Utils\Window.h>

#include <vector>

class Game {
    public: 
        static Game& get();

        void start();

        void setArguments(int argumentCount, char* arguments[]);

        const std::string& getArgument(int id) const;
        const std::vector<std::string>& getArguments() const;
        Util::Window& getWindow();

    private: 
        Game();
        ~Game();

        Controller::State* getState();
        void setState(Controller::State* const newState);
    
        Util::Window* _window;
        Controller::State* _state;
        std::vector<std::string> _arguments;

    public:
        friend class Controller::State::Initialization;
        friend class Controller::State::Shutdown;
};

#endif
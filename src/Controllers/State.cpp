#include "State.h"
#include "States.h"
#include "../Game.h"

namespace Controller {

    State::State() {
        next = this;
    }

    State::~State() {
        next = nullptr;
    }

    void State::handleInput() {
        if(shouldSkip())
            return;

        if(glfwWindowShouldClose(Game::get().getWindow().getHandle()))
            changeTo(Controller::States::get().shutdown);
    }

    State* State::getNext() {
        return next;
    }

    void State::changeTo(State* nextState) {
        next = nextState;
    }
    
    bool State::shouldSkip() {
        return (getNext() != this);
    }

    const State* const State::Quit = nullptr;

}
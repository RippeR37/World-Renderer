#include "Game.h"
#include "Controllers/States.h"

#include <iostream>

Game::Game() {
    setState(Controller::States::get().initialization);
}

Game::~Game() {
    delete _window;
}

Game& Game::get() {
    static Game instance;
    return instance;
}

void Game::start() {
    while(getState() != Controller::State::Quit) {
        getWindow().update();

        getState()->handleInput();
        getState()->update(getWindow().getFrameTime());
        getState()->render();

        setState(getState()->getNext());
    }
}

Util::Window& Game::getWindow() {
    return *_window;
}

Controller::State* Game::getState() {
    return _state;
}

void Game::setState(Controller::State* const newState) {
    if(getState() != newState) {

        if(getState() != nullptr) 
            getState()->onUnload();

        _state = newState;

        if(getState() != nullptr)
            getState()->onLoad();

    }
}
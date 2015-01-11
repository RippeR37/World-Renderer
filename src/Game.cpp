#include "Game.h"
#include "Controllers/States.h"

#include <iostream>

Game::Game() {
    setArguments(0, nullptr);
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

void Game::setArguments(int argumentCount, char* arguments[]) {
    _arguments.resize(argumentCount);

    for(int i = 0; i < argumentCount; ++i)
        _arguments[i] = std::string(arguments[i]);
}

const std::string& Game::getArgument(int id) const {
    if(id < _arguments.size())
        return _arguments[id];
}

const std::vector<std::string>& Game::getArguments() const {
    return _arguments;
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
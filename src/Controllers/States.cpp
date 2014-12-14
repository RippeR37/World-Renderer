#include "States.h"

namespace Controller {

    States::States() {
        initialization = new Controller::State::Initialization;
        shutdown = new Controller::State::Shutdown;

        gameplay = nullptr;
    }

    States::~States() {
        delete initialization;
        delete shutdown;
        
        delete gameplay;
    }

    States& States::get() {
        static States instance;
        return instance;
    }

    void States::initialize() {
        if(gameplay == nullptr) 
            gameplay = new Controller::State::Gameplay;
    }

}
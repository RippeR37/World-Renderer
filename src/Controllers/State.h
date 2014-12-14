#ifndef CONTROLLER_STATE_H_INCLUDED
#define CONTROLLER_STATE_H_INCLUDED

namespace Controller {

    class State {
        public:
            State();
            virtual ~State();

            virtual void update(const double frameTime) = 0;
            virtual void render() = 0;
            virtual void onLoad() = 0;
            virtual void onUnload() = 0;
            
            virtual void handleInput();

            State* getNext();

        protected:
            void changeTo(State* nextState);
            bool shouldSkip();
            State* next;

        public:
            static const State* const Quit;

            class Initialization;
            class Shutdown;
            
            class Gameplay;
    };

}

#include "States/Initialization.h"
#include "States/Shutdown.h"

#include "States/Gameplay.h"

#endif
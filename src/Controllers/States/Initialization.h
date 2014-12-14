#ifndef CONTROLLER_STATE_INITIALIZATION_H_INCLUDED
#define CONTROLLER_STATE_INITIALIZATION_H_INCLUDED

#include "../State.h"

namespace Controller {

    class State::Initialization : public State {
        public:
            void update(const double frameTime);
            void render();

            void onLoad();
            void onUnload();

        private:
            void openWindow();
            void setRandomSeed();
            void initializeStates();
    };

}

#endif
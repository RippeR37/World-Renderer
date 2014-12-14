#ifndef CONTROLLER_STATE_SHUTDOWN_H_INCLUDED
#define CONTROLLER_STATE_SHUTDOWN_H_INCLUDED

#include "../State.h"

namespace Controller {

    class State::Shutdown : public State {
        public:
            void update(const double frameTime);
            void render();

            void onLoad();
            void onUnload();

        private:
            void closeWindow();
            void terminateLibraries();
    };

}

#endif
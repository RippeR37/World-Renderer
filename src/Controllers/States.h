#ifndef CONTROLLER_STATES_H_INCLUDED
#define CONTROLLER_STATES_H_INCLUDED

#include "State.h"

namespace Controller {

    class States {
        public:
            static States& get();

            void initialize();

            State::Initialization* initialization;
            State::Shutdown* shutdown;

            State::Gameplay* gameplay;

        private:
            States();
            ~States();

    };

}

#endif
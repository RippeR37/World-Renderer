#ifndef CONTROLLER_STATE_GAMEPLAY_H_INCLUDED
#define CONTROLLER_STATE_GAMEPLAY_H_INCLUDED

#include "../State.h"
#include "../MapController.h"

#include "../../Models/Map.h"

#include "../../Views/ViewSector.h"
#include "../../Views/ViewWireframe2D.h"

#include "../../Utils/GL+/Pipeline.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Controller {

    class State::Gameplay : public State {
        public:
            Gameplay();

            void update(const double frameTime);
            void render();

            void onLoad();
            void onUnload();

            static void handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void handleMouseWheel(GLFWwindow* window, double x, double y);
            static void handleMouseMovement(GLFWwindow* window, double x, double y);

        public:
            const MapController& getMapController() const;

        private:
            bool isEnd() const;

        private:
            MapController _mapController;

        private:
            Model::Map _map;

        private:
            View::ViewSector _viewSector;
            View::ViewWireframe2D _viewWireframe2D;
    };

}

#endif
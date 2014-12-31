#ifndef CONTROLLER_STATE_GAMEPLAY_H_INCLUDED
#define CONTROLLER_STATE_GAMEPLAY_H_INCLUDED

#include "../State.h"
#include "../LockedCamera.h"
#include "../MapController.h"

#include "../../Models/Map.h"

#include "../../Views/ViewSector2D.h"
#include "../../Views/ViewSector3D.h"
#include "../../Views/ViewWireframe2D.h"
#include "../../Views/ViewWireframe3D.h"

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
            LockedCamera& getCamera();
            const MapController& getMapController() const;
            const Model::Map& getMap() const;

            GL::Pipeline& getPipeline();

        private:
            bool isEnd() const;
            bool isMode2D() const;

            void setMode2D(bool flag);

        private:
            bool _isMode2D;

            LockedCamera _camera;
            MapController _mapController;

            GL::Pipeline _pipeline;

        private:
            Model::Map _map;

        private:
            View::ViewSector2D _viewSector2D;
            View::ViewSector3D _viewSector3D;
            View::ViewWireframe2D _viewWireframe2D;
            View::ViewWireframe3D _viewWireframe3D;
    };

}

#endif
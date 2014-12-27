#include "Gameplay.h"
#include "../States.h"
#include "../../Game.h"
#include "../../Utils/TimeLoop.h"

#include <GLFW/glfw3.h>

#include <iostream>

namespace Controller {

    State::Gameplay::Gameplay()  {

    }

    void State::Gameplay::update(double frameTime) {
        static const double timeStep = 0.001;

        if(shouldSkip())
            return;
        
        Util::TimeLoop::semiFixed(frameTime, timeStep, [&, this](double deltaTime) { 
            _mapController.update(deltaTime);
        });
    }

    void State::Gameplay::render() {
        if(shouldSkip())
            return;
        
        Game::get().getWindow().getContext().clearBuffers(GL::Context::BufferMask::Color);

        for(int i = 0; i < _map.getSectors().size(); ++i)
            _viewSector.render(_map.getSectors()[i]);

        _viewWireframe2D.render();
    }

    void State::Gameplay::onLoad() {
        changeTo(this);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glfwSetKeyCallback(Game::get().getWindow().getHandle(), handleKeyboard);
        glfwSetScrollCallback(Game::get().getWindow().getHandle(), handleMouseWheel);
        glfwSetCursorPosCallback(Game::get().getWindow().getHandle(), handleMouseMovement);

        Game::get().getWindow().getContext().setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

        _map.init();
        _viewSector.init(_map.getSectors().front());
        _viewWireframe2D.init();
    }

    void State::Gameplay::onUnload() {
        glfwSetKeyCallback(Game::get().getWindow().getHandle(), nullptr);
        glfwSetScrollCallback(Game::get().getWindow().getHandle(), nullptr);
        glfwSetCursorPosCallback(Game::get().getWindow().getHandle(), nullptr);
    }

    void State::Gameplay::handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
        static State::Gameplay& thisState = *States::get().gameplay;

        if(action == GLFW_PRESS) {
            switch(key) {
                case GLFW_KEY_ESCAPE:
                    thisState.changeTo(States::get().shutdown);
                    break;

                default:
                    break;
            }

        }
    }
    
    void State::Gameplay::handleMouseWheel(GLFWwindow* window, double x, double y) {
        static State::Gameplay& thisState = *States::get().gameplay;

        if(y > 0)
            thisState._mapController.zoomIn();
        else if(y < 0)
            thisState._mapController.zoomOut();
    }

    void State::Gameplay::handleMouseMovement(GLFWwindow* window, double x, double y) {
        static State::Gameplay& thisState = *States::get().gameplay;
        static glm::dvec2 cursorPosLast;
        static glm::dvec2 cursorPosNow;
        static glm::vec2 cursorMovement;
        static bool pressedLast = false;
        
        cursorPosNow = glm::dvec2(x, y);

        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            if(pressedLast) {
                cursorMovement = cursorPosNow - cursorPosLast;
                cursorMovement.y = -cursorMovement.y;

                cursorMovement.x *= 0.0025f * (1.0f / thisState._mapController.getZoom());
                cursorMovement.y *= (0.01f / 3.0f) * (1.0f / thisState._mapController.getZoom());

                cursorMovement *= (4.0f / 3.0f);

                thisState._mapController.move(cursorMovement);
            }
            pressedLast = true;

        } else {
            pressedLast = false;

        }

        cursorPosLast = cursorPosNow;
    }

    const MapController& State::Gameplay::getMapController() const {
        return _mapController;
    }

    bool State::Gameplay::isEnd() const {
        return false;
    };

}

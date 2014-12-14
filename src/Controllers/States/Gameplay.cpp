#include "Gameplay.h"
#include "../States.h"
#include "../../Game.h"
#include "../../Utils/TimeLoop.h"

#include <GLFW/glfw3.h>

namespace Controller {

    State::Gameplay::Gameplay()  {

    }

    void State::Gameplay::update(double frameTime) {
        static const double timeStep = 0.001;

        if(shouldSkip())
            return;
        
        Util::TimeLoop::semiFixed(frameTime, timeStep, [&, this](double deltaTime) { 
            
        });
    }

    void State::Gameplay::render() {
        if(shouldSkip())
            return;
        
        Game::get().getWindow().getContext().clearBuffers(GL::Context::BufferMask::Color);
    }

    void State::Gameplay::onLoad() {
        changeTo(this);

        glfwSetInputMode(Game::get().getWindow().getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetKeyCallback(Game::get().getWindow().getHandle(), handleKeyboard);

        Game::get().getWindow().getContext().setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    }

    void State::Gameplay::onUnload() {
        glfwSetInputMode(Game::get().getWindow().getHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetKeyCallback(Game::get().getWindow().getHandle(), nullptr);
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

    bool State::Gameplay::isEnd() const {
        return false;
    };

}

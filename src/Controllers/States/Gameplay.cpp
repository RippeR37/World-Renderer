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

        _viewHeightSector.render(_heightSector);
    }

    void State::Gameplay::onLoad() {
        changeTo(this);
        glfwSetKeyCallback(Game::get().getWindow().getHandle(), handleKeyboard);
        Game::get().getWindow().getContext().setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

        loadHeightMaps();
        _viewHeightSector.init(_heightSector);
    }

    void State::Gameplay::onUnload() {
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

    void State::Gameplay::loadHeightMaps() {
        _heightSector.loadData("assets/heightmaps/N50E016.hgt");
    }

    bool State::Gameplay::isEnd() const {
        return false;
    };

}

#include "Shutdown.h"
#include "../../Game.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Controller {

    void State::Shutdown::update(double frameTime) {
        // do nothing
    }

    void State::Shutdown::render() {
        // do nothing
    }

    void State::Shutdown::onLoad() {
        State::changeTo(nullptr);
    }

    void State::Shutdown::onUnload() {
        closeWindow();
        terminateLibraries();
    }

    void State::Shutdown::closeWindow() {
        Game::get().getWindow().destroy();
    }

    void State::Shutdown::terminateLibraries() {
        glfwTerminate();
    }

}

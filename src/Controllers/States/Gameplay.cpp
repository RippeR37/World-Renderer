#include "Gameplay.h"
#include "../States.h"
#include "../../Game.h"

#include <Utils/TimeLoop.h>

#include <GLFW/glfw3.h>

#include <iostream>

namespace Controller {

    State::Gameplay::Gameplay()  {
        setMode2D(true);
    }

    State::Gameplay::~Gameplay() {

    }

    void State::Gameplay::update(double frameTime) {
        static const double timeStep = 0.001;

        if(shouldSkip())
            return;
        
        Util::TimeLoop::semiFixed(frameTime, timeStep, [&, this](double deltaTime) {
            if(isMode2D())
                _mapController.update(deltaTime);
            else
                _camera.update(deltaTime);
        });
    }

    void State::Gameplay::render() {
        if(shouldSkip())
            return;
        
        Game::get().getWindow().getContext().clearBuffers(GL::Context::BufferMask::Color_Depth);

        if(isMode2D()) {

            for(auto& sector : _map.getSectors())
                _viewSector2D.render(sector);

            _viewWireframe2D.render();
        
        } else {

            _pipeline.getStack().pushMatrix(_camera.getMatrix());
                _pipeline.getStack().rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

                _viewSector3D.resetTrianglesCount();

                for(auto& sector : _map.getSectors())
                    _viewSector3D.render(sector);

                _viewWireframe3D.render();

            _pipeline.getStack().popMatrix();
        }
    }

    void State::Gameplay::onLoad() {
        changeTo(this);

        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthFunc(GL_LEQUAL);

        glfwSetCursorPos(Game::get().getWindow().getHandle(), 400.0, 300.0);

        glfwSetKeyCallback(Game::get().getWindow().getHandle(), handleKeyboard);
        glfwSetScrollCallback(Game::get().getWindow().getHandle(), handleMouseWheel);
        glfwSetCursorPosCallback(Game::get().getWindow().getHandle(), handleMouseMovement);

        Game::get().getWindow().getContext().setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

        _pipeline.setProjection(60.0f, 4.0f/3.0f, 0.1f, 10 * 1000.0f);

        _map.init();
        _viewWireframe2D.init();
        _viewWireframe3D.init();
        _viewSector2D.init(_map.getSectors().front());
        _viewSector3D.init(_map.getSectors().front());

        Game::get().getWindow().setCountingFPS(true);
        Game::get().getWindow().setFPSRefreshRate(0.05);
        Game::get().getWindow().setFPSCountCallback([&, this](int fps) {
            std::string newTitle = std::string(" | FPS: ") + std::to_string(fps);

            if(this->isMode2D() == false)
                newTitle += 
                    std::string(" | LoD: ") + std::to_string(this->_viewSector3D.getLoD()) +
                    std::string(" (factor: ") + std::to_string(this->_viewSector3D.getLoDFactor()) +
                    std::string(" , auto: ") + std::string(this->_viewSector3D.isAutoLoD() ? "true" : "false") + ")" +
                    std::string(" | Triangles: ") + std::to_string(this->_viewSector3D.getTrianglesCount());

            if(this->isMode2D() == false) {
                if(this->_viewSector3D.isAutoLoD()) {
                    if(fps < 100) {
                        this->_viewSector3D.decreaseLoD();

                        if(fps < 60)
                            this->_viewSector3D.decreaseLoD();

                    } else if(fps > 160) {
                        this->_viewSector3D.increaseLoD();
                    }
                }
            }

            Game::get().getWindow().appendTitle(newTitle);
        });
    }

    void State::Gameplay::onUnload() {
        Game::get().getWindow().setCountingFPS(false);
        Game::get().getWindow().setFPSCountCallback(nullptr);

        glfwSetKeyCallback(Game::get().getWindow().getHandle(), nullptr);
        glfwSetScrollCallback(Game::get().getWindow().getHandle(), nullptr);
        glfwSetCursorPosCallback(Game::get().getWindow().getHandle(), nullptr);

        glfwSetInputMode(Game::get().getWindow().getHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        
        glDisable(GL_BLEND);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
    }

    void State::Gameplay::handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
        static State::Gameplay& thisState = *States::get().gameplay;

        if(action == GLFW_PRESS) {
            switch(key) {
                case GLFW_KEY_ESCAPE:
                    thisState.changeTo(States::get().shutdown);
                    break;

                case GLFW_KEY_TAB:
                    if(thisState.isMode2D()) {
                        glEnable(GL_DEPTH_TEST);
                        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        glfwSetInputMode(Game::get().getWindow().getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                        thisState.setMode2D(false);

                    } else {
                        glDisable(GL_DEPTH_TEST);
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        glfwSetInputMode(Game::get().getWindow().getHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                        thisState.setMode2D(true);
                    }

                    glfwSetCursorPos(window, 400.0, 300.0);
                    break;

                case GLFW_KEY_0:
                    if(thisState.isMode2D() == false) { thisState._viewSector3D.setAutoLoD(true); }
                    break;
                    
                case GLFW_KEY_1:
                    if(thisState.isMode2D() == false) { thisState._viewSector3D.setLoD(1); thisState._viewSector3D.setAutoLoD(false); }
                    break;
                    
                case GLFW_KEY_2:
                    if(thisState.isMode2D() == false) { thisState._viewSector3D.setLoD(2); thisState._viewSector3D.setAutoLoD(false); }
                    break;
                    
                case GLFW_KEY_3:
                    if(thisState.isMode2D() == false) { thisState._viewSector3D.setLoD(4); thisState._viewSector3D.setAutoLoD(false); }
                    break;
                    
                case GLFW_KEY_4:
                    if(thisState.isMode2D() == false) { thisState._viewSector3D.setLoD(6); thisState._viewSector3D.setAutoLoD(false); }
                    break;
                    
                case GLFW_KEY_5:
                    if(thisState.isMode2D() == false) { thisState._viewSector3D.setLoD(9); thisState._viewSector3D.setAutoLoD(false); }
                    break;
                    
                case GLFW_KEY_6:
                    if(thisState.isMode2D() == false) { thisState._viewSector3D.setLoD(12); thisState._viewSector3D.setAutoLoD(false); }
                    break;
                    
                case GLFW_KEY_7:
                    if(thisState.isMode2D() == false) { thisState._viewSector3D.setLoD(15); thisState._viewSector3D.setAutoLoD(false); }
                    break;
                    
                case GLFW_KEY_8:
                    if(thisState.isMode2D() == false) { thisState._viewSector3D.setLoD(18); thisState._viewSector3D.setAutoLoD(false); }
                    break;
                    
                case GLFW_KEY_9:
                    if(thisState.isMode2D() == false) { thisState._viewSector3D.setLoD(22); thisState._viewSector3D.setAutoLoD(false); }
                    break;

                

                default:
                    break;
            }

        }
        
        if(thisState.isMode2D() == false)
            thisState.getCamera().updateKeyboard(key, scancode, action, mods);
    }
    
    void State::Gameplay::handleMouseWheel(GLFWwindow* window, double x, double y) {
        static State::Gameplay& thisState = *States::get().gameplay;

        if(thisState.isMode2D()) {

            if(y > 0)
                thisState._mapController.zoomIn();
            else if(y < 0)
                thisState._mapController.zoomOut();

        } else {
        
            thisState.getCamera().updateMouseWheel(x, y);

        }
    }

    void State::Gameplay::handleMouseMovement(GLFWwindow* window, double x, double y) {
        static State::Gameplay& thisState = *States::get().gameplay;
        static glm::dvec2 cursorPosLast;
        static glm::dvec2 cursorPosNow;
        static glm::vec2 cursorMovement;
        static bool pressedLast = false;
        static double centerX = Game::get().getWindow().getWidth()  / 2.0;
        static double centerY = Game::get().getWindow().getHeight() / 2.0;
        static double dx;
        static double dy;
        

        if(thisState.isMode2D()) {
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

        } else {
            dx = x - centerX;
            dy = y - centerY;

            thisState.getCamera().updateMouse(static_cast<int>(dx), static_cast<int>(dy));
            glfwSetCursorPos(window, centerX, centerY);
        }
    }

    
    FlyCamera& State::Gameplay::getCamera() {
        return _camera;
    }

    const MapController& State::Gameplay::getMapController() const {
        return _mapController;
    }

    const Model::Map& State::Gameplay::getMap() const {
        return _map;
    }

    GL::Pipeline& State::Gameplay::getPipeline() {
        return _pipeline;
    }

    bool State::Gameplay::isEnd() const {
        return false;
    };

    bool State::Gameplay::isMode2D() const {
        return _isMode2D;
    }

    void State::Gameplay::setMode2D(bool flag) {
        _isMode2D = flag;
    }

}
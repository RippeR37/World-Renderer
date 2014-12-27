#include "MapController.h"
#include "../Game.h"

namespace Controller {

    MapController::MapController() {
        setZoom(1.0f);
        setPosition(glm::vec2(0.0f));
    }

    MapController::~MapController() {

    }

    void MapController::update(double deltaTime) {
        GLFWwindow* windowHandle = Game::get().getWindow().getHandle();

        static const float moveSpeed = 0.5f;

        if(glfwGetKey(windowHandle, GLFW_KEY_UP) == GLFW_PRESS)
            _position.y -= moveSpeed * (1.0f / _zoomLevel) * static_cast<float>(deltaTime);

        else if(glfwGetKey(windowHandle, GLFW_KEY_DOWN) == GLFW_PRESS)
            _position.y += moveSpeed * (1.0f / _zoomLevel) * static_cast<float>(deltaTime);
        

        if(glfwGetKey(windowHandle, GLFW_KEY_RIGHT) == GLFW_PRESS)
            _position.x -= moveSpeed * (1.0f / _zoomLevel) * static_cast<float>(deltaTime);

        else if(glfwGetKey(windowHandle, GLFW_KEY_LEFT) == GLFW_PRESS)
            _position.x += moveSpeed * (1.0f / _zoomLevel) * static_cast<float>(deltaTime);
    }

    void MapController::zoomIn() {
        setZoom(getZoom() * 1.125f);
    }

    void MapController::zoomOut() {
        setZoom(getZoom() * (1.0f / 1.125f));
    }
            
    void MapController::moveX(float offset) {
        _position.x += offset;
    }

    void MapController::moveY(float offset) {
        _position.y += offset;
    }
    
    void MapController::move(const glm::vec2& offset) {
        _position += offset;
    }

    void MapController::setZoom(float level) {
        _zoomLevel = level;
    }

    void MapController::setPositionX(float x) {
        _position.x  = x;
    }

    void MapController::setPositionY(float y) {
        _position.y = y;
    }

    void MapController::setPosition(float x, float y) {
        setPosition(glm::vec2(x, y));
    }

    void MapController::setPosition(const glm::vec2& position) {
        _position = position;
    }
    
    float MapController::getZoom() const {
        return _zoomLevel;
    }

    const glm::vec2& MapController::getPosition() const {
        return _position;
    }

}
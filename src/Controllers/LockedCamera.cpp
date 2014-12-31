#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "LockedCamera.h"
#include "../Game.h"
#include "../Controllers/States.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace Controller {

    LockedCamera::LockedCamera() : Camera() {
        static const float EARTH_RADIUS = 6371.0f;
        _position = glm::vec3(0.0f, 0.0f, 2.0f * EARTH_RADIUS);

        _mouseSpeed = 0.003f;
        _fovAngle = 60.0f;

        _angleX = 3.14f;
    }

    LockedCamera::~LockedCamera() {

    }

    void LockedCamera::update(double deltaTime) {
        static const float EARTH_RADIUS = 6371.0f;
        GLFWwindow* window = Game::get().getWindow().getHandle();

        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            _speed = (glm::length(_position) - EARTH_RADIUS) /  1.5f;
        else
            _speed = (glm::length(_position) - EARTH_RADIUS) / 15.0f;

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            _position += _direction * static_cast<float>(deltaTime * _speed);
        
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            _position -= _direction * static_cast<float>(deltaTime * _speed);
        
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            _position += _right * static_cast<float>(deltaTime * _speed);

        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            _position -= _right * static_cast<float>(deltaTime * _speed);

        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            _position += _up * static_cast<float>(deltaTime * _speed);

        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            _position -= _up * static_cast<float>(deltaTime * _speed);



        _direction = glm::vec3(std::cos(_angleY) * std::sin(_angleX), std::sin(_angleY), std::cos(_angleY) * cos(_angleX));
        _right     = glm::vec3(std::sin(_angleX - 3.14f/2.0f), 0, std::cos(_angleX - 3.14f/2.0f));
        _up        = glm::cross(_right, _direction);


        _matrix = glm::lookAt(_position, _position + _direction, _up);
    }

    void LockedCamera::updateMouse(double x, double y) {
        _angleX -= static_cast<float>(x) * _mouseSpeed;
        _angleY -= static_cast<float>(y) * _mouseSpeed;
    }
    
    void LockedCamera::updateKeyboard(int key, int scancode, int action, int mods) {
        // This camera is not affected by keyboard

        return;
    }

    void LockedCamera::updateMouseWheel(double x, double y) {
        _fovAngle += static_cast<float>(y) * 2.0f;

        if(_fovAngle < 15.0f)
            _fovAngle = 15.0f;

        else if(_fovAngle > 121.0f)
            _fovAngle = 121.0f;

        resetProjection();
    }

    void LockedCamera::resetProjection() {
        _projectionMatrix = glm::perspective(glm::radians(_fovAngle), 4.0f/3.0f, 0.1f, 10000.0f);

        Controller::States::get().gameplay->getPipeline().setProjection(_projectionMatrix);
    }
    
    void LockedCamera::resetAngles() {
        _angleX = 0;
        _angleY = 0;
    }

    float LockedCamera::getAngleX() const {
        return _angleX;
    }

    float LockedCamera::getAngleY() const {
        return _angleY;
    }

    const glm::vec2  LockedCamera::getPos2D() const {
        return glm::vec2(_position[0], _position[2]);
    }

    const glm::vec3& LockedCamera::getPos3D() const {
        return _position;
    }

    const glm::mat4& LockedCamera::getMatrix() const {
        return _matrix;
    }

}
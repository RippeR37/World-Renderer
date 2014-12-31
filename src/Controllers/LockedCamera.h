#ifndef CONTROLLER_LOCKEDCAMERA_H_INCLUDED
#define CONTROLLER_LOCKEDCAMERA_H_INCLUDED

#include "Camera.h"

#include <glm/glm.hpp>

namespace Controller {

    class LockedCamera : public Camera {
        public:
            LockedCamera();
            ~LockedCamera();

            void update(double deltaTime);
            void updateMouse(double x, double y);
            void updateKeyboard(int key, int scancode, int action, int mods);
            void updateMouseWheel(double x, double y);

            void resetProjection();
            void resetAngles();

            float getAngleX() const;
            float getAngleY() const;
            const glm::vec2  getPos2D() const;
            const glm::vec3& getPos3D() const;
            const glm::mat4& getMatrix() const;

        private:

            float _fovAngle;
            float _speed;
            float _angleX;
            float _angleY;
            float _mouseSpeed;
    };

}

#endif
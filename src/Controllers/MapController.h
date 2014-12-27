#ifndef CONTROLLERS_MAPCONTROLLER_H_INCLUDED
#define CONTROLLERS_MAPCONTROLLER_H_INCLUDED

#include <glm/vec2.hpp>

namespace Controller {

    class MapController {
        public:
            MapController();
            ~MapController();

            void update(double deltaTime);

            void zoomIn();
            void zoomOut();
            
            void moveX(float offset);
            void moveY(float offset);
            void move(const glm::vec2& offset);

            void setZoom(float level);
            void setPositionX(float x);
            void setPositionY(float y);
            void setPosition(float x, float y);
            void setPosition(const glm::vec2& position);

            float getZoom() const;
            const glm::vec2& getPosition() const;

        private:
            float _zoomLevel;
            glm::vec2 _position;
    };

}


#endif
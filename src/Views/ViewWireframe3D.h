#ifndef VIEW_WIREFRAME_3D_H_INCLUDED
#define VIEW_WIREFRAME_3D_H_INCLUDED

#include "ExtendedView.h"
#include "../Models/Sector.h"

#include <glm/vec4.hpp>

namespace View {

    class ViewWireframe3D : public ExtendedView<void> {
        public:
            ViewWireframe3D();
            ~ViewWireframe3D();

            void render();

            static glm::vec4 getSphereVertex(int angleX, int angleY);
            static glm::vec4 getSphereVertex(float angleX, float angleY);

        private:
            void setVertexData();

    };

}

#endif
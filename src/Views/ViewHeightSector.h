#ifndef VIEW_HEIGHT_SECTOR_H_INCLUDED
#define VIEW_HEIGHT_SECTOR_H_INCLUDED

#include "ExtendedView.h"
#include "../Models/HeightSector.h"

#include <glm/vec4.hpp>

namespace View {

    class ViewHeightSector : public ExtendedView<Model::HeightSector> {
        public:
            ViewHeightSector();
            ~ViewHeightSector();

            void render(const Model::HeightSector& heightSector);

        private:
            void setVertexData(const Model::HeightSector& heightSector);

            glm::vec4 getColor(short int height);

    };

}

#endif
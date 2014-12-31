#ifndef VIEW_SECTOR_2D_H_INCLUDED
#define VIEW_SECTOR_2D_H_INCLUDED

#include "ExtendedView.h"
#include "../Models/Sector.h"

#include <glm/vec4.hpp>

namespace View {

    class ViewSector2D : public ExtendedView<Model::Sector> {
        public:
            ViewSector2D();
            ~ViewSector2D();

            void render(const Model::Sector& sector);

        private:
            void setVertexData(const Model::Sector& sector);

    };

}

#endif
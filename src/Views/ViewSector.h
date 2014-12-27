#ifndef VIEW_SECTOR_H_INCLUDED
#define VIEW_SECTOR_H_INCLUDED

#include "ExtendedView.h"
#include "../Models/Sector.h"

#include <glm/vec4.hpp>

namespace View {

    class ViewSector : public ExtendedView<Model::Sector> {
        public:
            ViewSector();
            ~ViewSector();

            void render(const Model::Sector& sector);

        private:
            void setVertexData(const Model::Sector& sector);

    };

}

#endif
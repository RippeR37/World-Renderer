#ifndef VIEW_SECTOR3D_H_INCLUDED
#define VIEW_SECTOR3D_H_INCLUDED

#include "ExtendedView.h"
#include "../Models/Sector.h"

#include <glm/vec4.hpp>

namespace View {

    class ViewSector3D : public ExtendedView<Model::Sector> {
        public:
            ViewSector3D();
            ~ViewSector3D();

            void render(const Model::Sector& sector);

        private:
            void setVertexData(const Model::Sector& sector);

    };

}

#endif
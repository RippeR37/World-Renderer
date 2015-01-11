#ifndef VIEW_SECTOR_3D_H_INCLUDED
#define VIEW_SECTOR_3D_H_INCLUDED

#include "ExtendedView.h"
#include "../Models/Sector.h"
#include "../Models/QTree.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace View {

    class ViewSector3D : public ExtendedView<Model::Sector> {
        private:
            struct NodeData {
                glm::uvec2 size;
                glm::uvec2 position;

                unsigned int drawCount;
                unsigned int drawOffset;
            };


        public:
            ViewSector3D();
            ~ViewSector3D();

            void render(const Model::Sector& sector);

            const bool isAutoLoD() const;
            const unsigned int getLoD() const;
            const float getLoDFactor() const;

            void setAutoLoD(bool flag);
            void setLoD(unsigned int level);

            void increaseLoD();
            void decreaseLoD();

        private:
            void setVertexData(const Model::Sector& sector);
            
            void setLoDFactor(float factor);
            glm::vec3 getVertexOnSphere(const glm::vec2& angle, const glm::vec2& offset);

            bool _isAutoLoD;
            unsigned int _lod;
            float _lodFactor;
            GL::VertexBuffer _ibo;
            Model::QTree<NodeData> _tree;
    };

}

#endif
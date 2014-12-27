#include "ViewSector3D.h"
#include "../Controllers/MapController.h"
#include "../Controllers/States.h"

#include <glm/glm.hpp>

namespace View {

    ViewSector3D::ViewSector3D() {
        _program.load(
            GL::Shader("assets/shaders/sector3D.vs", GL::Shader::Type::VertexShader),
            GL::Shader("assets/shaders/sector3D.fs", GL::Shader::Type::FragmentShader)
        );
    }

    ViewSector3D::~ViewSector3D() {

    }

    void ViewSector3D::render(const Model::Sector& sector) {
        sector.getTexture().bind();

        _program.use();
        _program["mapCoords"].setVec(glm::vec2(sector.getLongtitude(), sector.getLatitude()));
        _program["dataTexture"].setSampler(0);

            _vao.bind();
            _vao.drawArrays();
            _vao.unbind();

        _program.unbind();

        sector.getTexture().unbind();
    }

    void ViewSector3D::setVertexData(const Model::Sector& sector) {
        GL::VertexBuffer::Data vertexData;
        std::vector<glm::vec2> vertices;

        {
            float x1, x2;
            float y1, y2;

            float width  = static_cast<float>(sector.getHeightMap()[0].size());
            float height = static_cast<float>(sector.getHeightMap().size());

            for(int y = 0; y < height - 1; ++y) {
                for(int x = 0; x < width - 1; ++x) {

                    x1 = static_cast<float>(x)   / width;
                    x2 = static_cast<float>(x+1) / width;
                    y1 = static_cast<float>(y)   / height;
                    y2 = static_cast<float>(y+1) / height;

                    vertices.push_back(glm::vec2(x1, y1));
                    vertices.push_back(glm::vec2(x1, y2));
                    vertices.push_back(glm::vec2(x2, y1));
                    
                    vertices.push_back(glm::vec2(x2, y1));
                    vertices.push_back(glm::vec2(x1, y2));
                    vertices.push_back(glm::vec2(x2, y2));
                }
            }
        }

        // VertexData
        vertexData.data = (GLvoid*)&vertices[0];
        vertexData.size = vertices.size() * sizeof(vertices[0]);
        vertexData.pointers.push_back(GL::VertexAttrib(0, 2, GL_FLOAT, 0, 0));
        
        // VBO
        _vbo.bind();
        _vbo.setData(vertexData);
        _vbo.unbind();

        // VAO
        _vao.attachVBO(&_vbo);
        _vao.setDrawCount(vertices.size());
        _vao.setDrawTarget(GL::VertexArray::DrawTarget::Triangles);
    }

}
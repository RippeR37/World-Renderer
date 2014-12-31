#include "ViewSector3D.h"
#include "../Controllers/MapController.h"
#include "../Controllers/States.h"

#include <glm/glm.hpp>

#include <iostream>

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
        static Controller::State::Gameplay& gameplay = *Controller::States::get().gameplay;
        
        
        gameplay.getPipeline().getStack().pushMatrix();

            sector.getTexture().bind();

            _program.use();
            _program["MVP"].setMatrix(gameplay.getPipeline().getMVP());
            _program["mapCoords"].setVec(glm::vec2(sector.getLongtitude(), sector.getLatitude()));
            _program["dataTexture"].setSampler(0);

                _vao.bind();
                _vao.drawArrays();
                _vao.unbind();

            _program.unbind();

            sector.getTexture().unbind();

        gameplay.getPipeline().getStack().popMatrix();
    }

    void ViewSector3D::setVertexData(const Model::Sector& sector) {
        GL::VertexBuffer::Data vertexData;
        std::vector<glm::vec2> vertices;

        {
            float width  = 1201.0f;
            float height = 1201.0f; 
            float fX, fY;

            for(int y = 0; y < 1201.0f; ++y) {
                fY = static_cast<float>(y);

                for(int x = 0; x < 1201.0f; ++x) {
                    fX = static_cast<float>(x);

                    vertices.push_back(glm::vec2(fX / width, fY / height));
                    vertices.push_back(glm::vec2((fX + 1.0f) / width, fY / height));
                    vertices.push_back(glm::vec2(fX / width, (fY + 1.0f) / height));
                    
                    vertices.push_back(glm::vec2(fX / width, (fY + 1.0f) / height));
                    vertices.push_back(glm::vec2((fX + 1.0f) / width, fY / height));
                    vertices.push_back(glm::vec2((fX + 1.0f) / width, (fY + 1.0f) / height));
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
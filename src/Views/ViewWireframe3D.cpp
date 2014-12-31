#include "ViewWireframe3D.h"
#include "../Controllers/MapController.h"
#include "../Controllers/States.h"

#include <glm/glm.hpp>

namespace View {

    ViewWireframe3D::ViewWireframe3D() {
        _program.load(
            GL::Shader("assets/shaders/wireframe3D.vs", GL::Shader::Type::VertexShader),
            GL::Shader("assets/shaders/wireframe3D.fs", GL::Shader::Type::FragmentShader)
        );
    }

    ViewWireframe3D::~ViewWireframe3D() {

    }

    void ViewWireframe3D::render() {
        static Controller::State::Gameplay& gameplay = *Controller::States::get().gameplay;
        
        gameplay.getPipeline().getStack().pushMatrix();
            
            _program.use();
            _program["MVP"].setMatrix(gameplay.getPipeline().getMVP());

                _vao.bind();
                _vao.drawArrays();
                _vao.unbind();

            _program.unbind();

        gameplay.getPipeline().getStack().popMatrix();
    }

    glm::vec4 ViewWireframe3D::getSphereVertex(int angleX, int angleY) {
        return getSphereVertex(static_cast<float>(angleX), static_cast<float>(angleY));
    }

    glm::vec4 ViewWireframe3D::getSphereVertex(float angleX, float angleY) {
        static const float EARTH_RADIUS = 6371.0f;
        float phi   = glm::radians(angleX);
        float theta = glm::radians(angleY);

        return glm::vec4(
            EARTH_RADIUS * std::cos(theta) * std::cos(phi),
            EARTH_RADIUS * std::cos(theta) * std::sin(phi),
            EARTH_RADIUS * std::sin(theta),
            1.0f
        );
    }

    void ViewWireframe3D::setVertexData() {
        GL::VertexBuffer::Data vertexData;
        std::vector<glm::vec4> vertices;

        
        {
            const Model::Map& map = Controller::States::get().gameplay->getMap();
            int advance = 1;

            for(int y = -80; y < 80; y += advance) {
                for(int x = -180; x < 180; x += advance) {

                    bool sectorLoaded = false;
                    for(auto& sector : map.getSectors()) {
                        if(sector.getLongtitude() == x && sector.getLatitude() == y) {
                            sectorLoaded = true;
                            break;
                        }
                    }
                    
                    if(sectorLoaded)
                        continue;

                    vertices.push_back(getSphereVertex(          x,           y));
                    vertices.push_back(getSphereVertex(x + advance,           y));
                    vertices.push_back(getSphereVertex(          x, y + advance));
                    
                    vertices.push_back(getSphereVertex(          x, y + advance));
                    vertices.push_back(getSphereVertex(x + advance,           y));
                    vertices.push_back(getSphereVertex(x + advance, y + advance));
                }
            }
        }


        // VertexData
        vertexData.data = (GLvoid*)&vertices[0];
        vertexData.size = vertices.size() * sizeof(vertices[0]);
        vertexData.pointers.push_back(GL::VertexAttrib(0, 4, GL_FLOAT, 0, 0));
        
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
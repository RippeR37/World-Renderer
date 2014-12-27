#include "ViewSector.h"
#include "../Controllers/MapController.h"
#include "../Controllers/States.h"

#include <glm/glm.hpp>

namespace View {

    ViewSector::ViewSector() {
        _program.load(
            GL::Shader("assets/shaders/sector.vs", GL::Shader::Type::VertexShader),
            GL::Shader("assets/shaders/sector.fs", GL::Shader::Type::FragmentShader)
        );
    }

    ViewSector::~ViewSector() {

    }

    void ViewSector::render(const Model::Sector& sector) {
        const Controller::MapController& mapController = Controller::States::get().gameplay->getMapController();
        glm::vec2 mapOffset;
        
        mapOffset = 
            mapController.getPosition() +
            glm::vec2(sector.getLongtitude(), sector.getLatitude());

        sector.getTexture().bind();

        _program.use();
        _program["zoomLevel"].set(mapController.getZoom());
        _program["mapOffset"].setVec(mapOffset);
        _program["mapCoords"].setVec(glm::vec2(sector.getLongtitude(), sector.getLatitude()));
        _program["dataTexture"].setSampler(0);

            _vao.bind();
            _vao.drawArrays();
            _vao.unbind();

        _program.unbind();

        sector.getTexture().unbind();
    }

    void ViewSector::setVertexData(const Model::Sector& sector) {
        GL::VertexBuffer::Data vertexData;
        std::vector<glm::vec4> vertices;

        {
            vertices.push_back(glm::vec4(0.0f, 0.0f,    0.0f, 1.0f));
            vertices.push_back(glm::vec4(0.0f, 1.0f,    0.0f, 0.0f));
            vertices.push_back(glm::vec4(1.0f, 0.0f,    1.0f, 1.0f));
                    
            vertices.push_back(glm::vec4(1.0f, 0.0f,    1.0f, 1.0f));
            vertices.push_back(glm::vec4(0.0f, 1.0f,    0.0f, 0.0f));
            vertices.push_back(glm::vec4(1.0f, 1.0f,    1.0f, 0.0f));
        }

        // VertexData
        vertexData.data = (GLvoid*)&vertices[0];
        vertexData.size = vertices.size() * sizeof(vertices[0]);
        vertexData.pointers.push_back(GL::VertexAttrib(0, 2, GL_FLOAT, sizeof(glm::vec4), 0));
        vertexData.pointers.push_back(GL::VertexAttrib(1, 2, GL_FLOAT, sizeof(glm::vec4), (GLvoid*)sizeof(glm::vec2)));
        
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
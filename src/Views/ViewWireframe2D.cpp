#include "ViewWireframe2D.h"
#include "../Controllers/MapController.h"
#include "../Controllers/States.h"

namespace View {

    ViewWireframe2D::ViewWireframe2D() {
        _program.load(
            GL::Shader("assets/shaders/wireframe2D.vs", GL::Shader::Type::VertexShader),
            GL::Shader("assets/shaders/wireframe2D.fs", GL::Shader::Type::FragmentShader)
        );
    }

    ViewWireframe2D::~ViewWireframe2D() {

    }

    void ViewWireframe2D::render() {
        const Controller::MapController& mapController = Controller::States::get().gameplay->getMapController();

        _program.use();
        _program["zoomLevel"].set(mapController.getZoom());
        _program["mapOffset"].setVec(mapController.getPosition());

            _vao.bind();
            _vao.drawArrays();
            _vao.unbind();

        _program.unbind();
    }

    void ViewWireframe2D::setVertexData() {
        GL::VertexBuffer::Data vertexData;
        std::vector<glm::vec2> vertices;

        {
            for(int y = -70; y < 70; ++y) {
                for(int x = -180; x < 180; ++x) {
                    float x1 = static_cast<float>(x);
                    float y1 = static_cast<float>(y);
                    float x2 = static_cast<float>(x + 1);
                    float y2 = static_cast<float>(y + 1);

                    vertices.push_back(glm::vec2(std::cos(glm::radians(y1)) * x1, y1));    // lewa
                    vertices.push_back(glm::vec2(std::cos(glm::radians(y2)) * x1, y2));    // 

                    vertices.push_back(glm::vec2(std::cos(glm::radians(y2)) * x1, y2));    // gora
                    vertices.push_back(glm::vec2(std::cos(glm::radians(y2)) * x2, y2));

                    vertices.push_back(glm::vec2(std::cos(glm::radians(y1)) * x2, y1));    // prawa
                    vertices.push_back(glm::vec2(std::cos(glm::radians(y2)) * x2, y2));

                    vertices.push_back(glm::vec2(std::cos(glm::radians(y1)) * x1, y1));    // dol
                    vertices.push_back(glm::vec2(std::cos(glm::radians(y1)) * x2, y1));
                }
            }
        }

        // VertexData
        vertexData.data = (GLvoid*)&vertices[0];
        vertexData.size = vertices.size() * sizeof(vertices[0]);
        vertexData.pointers.push_back(GL::VertexAttrib(0, 2, GL_FLOAT, sizeof(glm::vec4), 0));
        
        // VBO
        _vbo.bind();
        _vbo.setData(vertexData);
        _vbo.unbind();

        // VAO
        _vao.attachVBO(&_vbo);
        _vao.setDrawCount(vertices.size());
        _vao.setDrawTarget(GL::VertexArray::DrawTarget::Lines);
    }

}
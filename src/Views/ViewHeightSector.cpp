#include "ViewHeightSector.h"

#include <glm/vec4.hpp>

namespace View {

    ViewHeightSector::ViewHeightSector() {
        _program.load(
            GL::Shader("assets/shaders/heightSector.vs", GL::Shader::Type::VertexShader),
            GL::Shader("assets/shaders/heightSector.fs", GL::Shader::Type::FragmentShader)
        );
    }

    ViewHeightSector::~ViewHeightSector() {

    }

    void ViewHeightSector::render(const Model::HeightSector& heightSector) {
        _program.use();
            
            _vao.bind();
            _vao.drawArrays();
            _vao.unbind();

        _program.unbind();
    }

    void ViewHeightSector::setVertexData(const Model::HeightSector& heightSector) {
        GL::VertexBuffer::Data vertexData;
        std::vector<glm::vec4> vertices;
        glm::vec4 color;

        {
            for(unsigned int y = 0; y < heightSector.getHeightMap().size(); ++y) {
                for(unsigned int x = 0; x < heightSector.getHeightMap()[y].size(); ++x) {

                    color = getColor(heightSector.getHeight(x, y));

                    vertices.push_back(glm::vec4(       x,        y, 0.0f, 1.0f)); vertices.push_back(glm::vec4(color));
                    vertices.push_back(glm::vec4(x + 1.0f,        y, 0.0f, 1.0f)); vertices.push_back(glm::vec4(color));
                    vertices.push_back(glm::vec4(       x, y + 1.0f, 0.0f, 1.0f)); vertices.push_back(glm::vec4(color));
                }
            }
        }

        // VertexData
        vertexData.data = &vertices[0];
        vertexData.size = vertices.size() * sizeof(vertices[0]);
        vertexData.pointers.push_back(GL::VertexAttrib(0, 4, GL_FLOAT, sizeof(glm::vec4) * 2, 0));
        vertexData.pointers.push_back(GL::VertexAttrib(1, 4, GL_FLOAT, sizeof(glm::vec4) * 2, (GLvoid*)sizeof(glm::vec4)));

        // VBO
        _vbo.bind();
        _vbo.setData(vertexData);
        _vbo.unbind();

        // VAO
        _vao.attachVBO(&_vbo);
        _vao.setDrawCount(vertices.size() / 2);
        _vao.setDrawTarget(GL::VertexArray::DrawTarget::Triangles);
    }

    glm::vec4 ViewHeightSector::getColor(short int height) {
        glm::vec4 color;

        if (height < 0)   
            color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

        else if (height < 500)
            color = glm::vec4(0.0f, height/500.0f, 0.0f, 1.0f);

        else if (height < 1000)
            color = glm::vec4(height/500.0f - 1.0f, 1.0f, 0.0f, 1.0f);

        else if (height < 2000)
            color = glm::vec4(1.0f, 2.0f - height/1000.0f, 0.0f, 1.0f);

        else
            color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        return color;
    }

}
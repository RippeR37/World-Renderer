#include "ViewSector3D.h"
#include "../Controllers/MapController.h"
#include "../Controllers/States.h"

#include <glm/glm.hpp>

#define GLM_FORCE_RADIANS
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>
#include <queue>

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
        static Controller::FlyCamera& camera = gameplay.getCamera();
        static glm::vec3 cameraPosition;
        static glm::vec2 sectorPosition;
        static glm::vec2 nodeOffset;

        std::queue<Model::QTree<NodeData>*> queue;
        Model::QTree<NodeData>* thisNode;
        float distToCamera;

        cameraPosition = glm::rotate(camera.getPos3D(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        sectorPosition = glm::vec2(sector.getLongtitude(), sector.getLatitude());
        
        gameplay.getPipeline().getStack().pushMatrix();

            sector.getTexture().bind();

            _program.use();
            _program["MVP"].setMatrix(gameplay.getPipeline().getMVP());
            _program["mapCoords"].setVec(sectorPosition);
            _program["dataTexture"].setSampler(0);
                
                int countDraw = 0;

                _vao.bind();

                    queue.push(&_tree);
                    while(queue.empty() == false) {
                        thisNode = queue.front();

                        nodeOffset = (glm::vec2(thisNode->data.position) + glm::vec2(thisNode->data.size) * (0.5f)) * (1.0f / 1201.0f);
                        
                        distToCamera = glm::distance(
                            cameraPosition,
                            getVertexOnSphere(sectorPosition, nodeOffset)
                        );
                        
                        if(distToCamera > thisNode->data.size.x * 2.0f || thisNode->child[0] == nullptr) {
                            ++countDraw;
                            glDrawElements(GL_TRIANGLES, thisNode->data.drawCount, GL_UNSIGNED_INT, (GLvoid*)thisNode->data.drawOffset);

                        } else {
                            for(int i = 0; i < 4; ++i)
                                queue.push(thisNode->child[i]);
                        }

                        queue.pop();
                    }
                    
                _vao.unbind();

            _program.unbind();

            sector.getTexture().unbind();

        gameplay.getPipeline().getStack().popMatrix();
    }

    void ViewSector3D::setVertexData(const Model::Sector& sector) {
        GL::VertexBuffer::Data vertexData;
        std::vector<glm::vec2> vertices;
        std::vector<GLuint> indices;

        
        // VBO data
        {
            float fX, fY;

            for(int y = 0; y < 1201; ++y) {
                fY = static_cast<float>(y);

                for(int x = 0; x < 1201; ++x) {
                    fX = static_cast<float>(x);

                    vertices.push_back(glm::vec2(fX / 1200.0f, fY / 1200.0f));
                }
            }
        }

        // IBO data
        {
            std::queue<Model::QTree<NodeData>*> queue;
            unsigned int x1, x2;
            unsigned int y1, y2;

            queue.push(&_tree);
            _tree.data.size     = glm::uvec2(1201);
            _tree.data.position = glm::uvec2(0);
            
            while(queue.empty() == false) {
                Model::QTree<NodeData>* thisNode = queue.front();
                
                if(thisNode != nullptr) {
                    thisNode->data.drawOffset = indices.size() * sizeof(unsigned int);

                    x1 = thisNode->data.position.x;
                    y1 = thisNode->data.position.y;

                    x2 = (x1 + thisNode->data.size.x < _tree.data.size.x ) ? 
                          x1 + thisNode->data.size.x : _tree.data.size.x - 1;

                    y2 = (y1 + thisNode->data.size.y < _tree.data.size.y ) ? 
                          y1 + thisNode->data.size.y : _tree.data.size.y - 1;

                    indices.push_back(y1 * 1201 + x1);
                    indices.push_back(y1 * 1201 + x2);
                    indices.push_back(y2 * 1201 + x1);

                    indices.push_back(y2 * 1201 + x1);
                    indices.push_back(y1 * 1201 + x2);
                    indices.push_back(y2 * 1201 + x2);

                    thisNode->data.drawCount = 6;

                    if(thisNode->data.size.x > 1 || thisNode->data.size.y > 1) {
                        unsigned int thisWidth  = thisNode->data.size.x;
                        unsigned int thisHeight = thisNode->data.size.y;
                        unsigned int halfWidth  = thisNode->data.size.x / 2;
                        unsigned int halfHeight = thisNode->data.size.y / 2;

                        thisNode->child[0] = new Model::QTree<NodeData>();      //     ID
                        thisNode->child[1] = new Model::QTree<NodeData>();      // 2        3
                        thisNode->child[2] = new Model::QTree<NodeData>();      //    this   
                        thisNode->child[3] = new Model::QTree<NodeData>();      // 0        1

                        thisNode->child[0]->data.size = glm::uvec2(halfWidth,                          halfHeight);
                        thisNode->child[1]->data.size = glm::uvec2(thisWidth - halfWidth,              halfHeight);
                        thisNode->child[2]->data.size = glm::uvec2(halfWidth,             thisHeight - halfHeight);
                        thisNode->child[3]->data.size = glm::uvec2(thisWidth - halfWidth, thisHeight - halfHeight);

                        thisNode->child[0]->data.position = glm::uvec2(            x1,              y1);
                        thisNode->child[1]->data.position = glm::uvec2(x1 + halfWidth,              y1);
                        thisNode->child[2]->data.position = glm::uvec2(            x1, y1 + halfHeight);
                        thisNode->child[3]->data.position = glm::uvec2(x1 + halfWidth, y1 + halfHeight);

                        for(int i = 0; i < 4; ++i) {
                            thisNode->child[i]->parent = thisNode;
                            queue.push(thisNode->child[i]);
                        }
                    }
                }
                
                queue.pop();
            }
        }

        // VertexData
        vertexData.data = (GLvoid*)&vertices[0];
        vertexData.size = vertices.size() * sizeof(vertices[0]);
        vertexData.pointers.push_back(GL::VertexAttrib(0, 2, GL_FLOAT, 0, 0));
        
        // VBO setting
        _vbo.bind();
        _vbo.setData(vertexData);
        _vbo.unbind();
        
        // IBO setting
        _ibo.setTarget(GL::VertexBuffer::Target::ElementArray);
        _ibo.setUsage(GL::VertexBuffer::Usage::StaticDraw);
        _ibo.bind();
        _ibo.setData(indices);
        _ibo.unbind();

        // VAO setting
        _vao.attachVBO(&_vbo);
        _vao.setDrawCount(vertices.size());
        _vao.setDrawTarget(GL::VertexArray::DrawTarget::Triangles);

        // Attach IBO to VAO
        _vao.bind();
        _ibo.bind();
        _vao.unbind();
    }
    
    glm::vec3 ViewSector3D::getVertexOnSphere(const glm::vec2& angle, const glm::vec2& offset) {
        static const float EARTH_RADIUS = 6371.0f;
        float phi   = glm::radians(angle.x + offset.x);
        float theta = glm::radians(angle.y + offset.y);

        return glm::vec3(
            EARTH_RADIUS * std::cos(theta) * std::cos(phi),
            EARTH_RADIUS * std::cos(theta) * std::sin(phi),
            EARTH_RADIUS * std::sin(theta)
        );
    }

}
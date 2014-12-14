#ifndef UTIL_WINDOW_H_INCLUDED
#define UTIL_WINDOW_H_INCLUDED

#include "Exception.h"
#include "GL+/Context.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <string>

namespace Util {
    
    class Window {
        public:
            Window();
            ~Window();
            
            bool create() throw(Util::Exception::FatalError);
            void update();
            void destroy();
            
            void setSize(unsigned int width, unsigned int height);
            void setSize(glm::uvec2 size);
            void setTitle(std::string title);
            void appendTitle(std::string text);
            
            const unsigned int getWidth() const;
            const unsigned int getHeight() const;
            const glm::uvec2& getSize() const;
            const std::string& getTitle() const;

            const bool isCreated() const;
            const double getFrameTime() const;
            GLFWwindow* getHandle();
            GL::Context& getContext();

        private:
            void setHints();
            void setContext();

            static void initializeGLFW() throw(Util::Exception::FatalError);
            static void initializeGLEW() throw(Util::Exception::FatalError);
            
            glm::uvec2 _size;
            double _frameTime;
            std::string _title;
            GLFWwindow* _handle;
            GL::Context _context;
    };

}

#endif
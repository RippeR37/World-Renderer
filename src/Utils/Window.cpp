#include "Window.h"

namespace Util {

    Window::Window() {
        _handle = nullptr;

        // Default options
        _size  = glm::uvec2(640, 480);
        _title = std::string("Title");
    }

    Window::~Window() {
        destroy();
    }

    bool Window::create() {
        if(isCreated())
            destroy();

        Window::initializeGLFW();

        setHints();

        _handle = glfwCreateWindow(getWidth(), getHeight(), _title.c_str(), nullptr, nullptr);

        setContext();

        Window::initializeGLEW();

        return isCreated();
    }

    void Window::update() {
        static double lastFrame = glfwGetTime();
        static double thisFrame;

        thisFrame  = glfwGetTime();
        _frameTime = thisFrame - lastFrame;
        lastFrame  = thisFrame;
        
        glfwSwapBuffers(_handle);
        glfwPollEvents();
    }

    void Window::destroy() {
        if(isCreated()) {
            glfwDestroyWindow(_handle);
            _handle = nullptr;
        }
    }

    void Window::setSize(unsigned int width, unsigned int height) {
        setSize(glm::uvec2(width, height));
    }

    void Window::setSize(glm::uvec2 size) {
        _size = size;

        if(isCreated())
            glfwSetWindowSize(_handle, getWidth(), getHeight());
    }

    void Window::setTitle(std::string title) {
        _title = title;

        if(isCreated())
            glfwSetWindowTitle(_handle, _title.c_str());
    }
    
    void Window::appendTitle(std::string text) {
        std::string appendedTitle = getTitle() + text;

        if(isCreated())
            glfwSetWindowTitle(_handle, appendedTitle.c_str());
    }

    const unsigned int Window::getWidth() const {
        return _size.x;
    }

    const unsigned int Window::getHeight() const {
        return _size.y;
    }

    const glm::uvec2& Window::getSize() const {
        return _size;
    }
    const std::string& Window::getTitle() const {
        return _title;
    }

    const bool Window::isCreated() const {
        return (_handle != nullptr);
    }

    const double Window::getFrameTime() const {
        return _frameTime;
    }

    GLFWwindow* Window::getHandle() {
        return _handle;
    }

    GL::Context& Window::getContext() {
        return _context;
    }

    void Window::setHints() {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }

    void Window::setContext() {
        glfwMakeContextCurrent(_handle);
        getContext().makeActive(this);
    }

    void Window::initializeGLFW() {
        static bool initialized = false;

        if(initialized == false) {
            initialized = true;

            if(glfwInit() == false)
                throw Util::Exception::FatalError(std::string("Failed to initialize GLFW library."));
        }
    }

    void Window::initializeGLEW() {
        static bool initialized = false;

        if(initialized == false) {
            initialized = true;
            glewExperimental = GL_TRUE;

            if(glewInit() != GLEW_OK)
                throw Util::Exception::FatalError(std::string("Failed to initialize GLEW library."));
        }
    }

}
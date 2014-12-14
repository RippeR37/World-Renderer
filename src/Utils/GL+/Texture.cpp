#include "Texture.h"

namespace GL {
    
    Texture::Texture() {
        create();
    }

    Texture::Texture(const Util::Image& image, Target target, Format format) {
        Texture();

        load(image, target, format);
    }

    Texture::Texture(const std::string& path, Target target, Format format) {
        Texture();

        Util::Image image(path, Util::Image::Format::BMP);
        load(image, target, format);
    }
    
    Texture::Texture(Texture&& texture) {
        create();

        std::swap(_isAlpha, texture._isAlpha);
        std::swap(_width, texture._width);
        std::swap(_height, texture._height);
        std::swap(_target, texture._target);
        std::swap(_textureID, texture._textureID);
    }

    Texture::~Texture() {
        destroy();
    }

    Texture& Texture::operator=(Texture&& texture) {
        std::swap(_isAlpha, texture._isAlpha);
        std::swap(_width, texture._width);
        std::swap(_height, texture._height);
        std::swap(_target, texture._target);
        std::swap(_textureID, texture._textureID);
    }

    void Texture::bind() const {
        glBindTexture(static_cast<GLenum>(getTarget()), getID());
    }

    void Texture::unbind() const {
        glBindTexture(static_cast<GLenum>(getTarget()), 0);
    }

    void Texture::load(const Util::Image& image, Target target, Format format) {
        setTarget(target);
        bind();
        assingData(image, format);
        setParameters();
        generateMipmap();
        unbind();
    }

    bool Texture::isAlpha() const {
        return _isAlpha;
    }

    unsigned int Texture::getWidth() const {
        return _width;
    }

    unsigned int Texture::getHeight() const {
        return _height;
    }

    Texture::Target Texture::getTarget() const {
        return _target;
    }

    GLuint Texture::getID() const {
        return _textureID;
    }

    void Texture::create() {
        glGenTextures(1, &_textureID);
    }

    void Texture::destroy() {
        glDeleteTextures(1, &_textureID);
    }
    
    void Texture::setTarget(Target target) {
        _target = target;
    }

    void Texture::assingData(const Util::Image& image, const Format format) {
        Texture::Format internalFormat;
        Texture::Format storageFormat;

        if(format == Format::DefaultFormat) {
            switch(image.getBits()) {
                case 24: 
                    internalFormat = Format::RGB;
                    storageFormat = Format::BGR;
                    break;

                case 32:
                    internalFormat = Format::RGBA;
                    storageFormat = Format::BGRA;
                    break;

                default:
                    throw Util::Exception::FatalError("Could not determine texture's color profile");
                    break;
            }
        } else {
            internalFormat = format;
            storageFormat = format;
        }

        glTexImage2D(static_cast<GLenum>(getTarget()), 
                     0, static_cast<GLint>(internalFormat), 
                     image.getWidth(), 
                     image.getHeight(), 
                     0, static_cast<GLenum>(storageFormat),
                     GL_UNSIGNED_BYTE, 
                     image.getData());
    }

    void Texture::setParameters() {
        glTexParameteri(static_cast<GLenum>(getTarget()), GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(static_cast<GLenum>(getTarget()), GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(static_cast<GLenum>(getTarget()), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(static_cast<GLenum>(getTarget()), GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }

    void Texture::generateMipmap() {
        glGenerateMipmap(static_cast<GLenum>(getTarget()));
    }

}
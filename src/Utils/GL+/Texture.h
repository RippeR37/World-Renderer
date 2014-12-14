#ifndef UTILS_GL_TEXTURE_H_INCLUDED
#define UTILS_GL_TEXTURE_H_INCLUDED

#include "../Image.h"
#include "../Exception.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace GL {

    class Texture {
        public:
            enum class Target {
                Tex1D = GL_TEXTURE_1D,
                Tex2D = GL_TEXTURE_2D, 
                Tex3D = GL_TEXTURE_3D, 
                Tex1DArray = GL_TEXTURE_1D_ARRAY, 
                Tex2DArray = GL_TEXTURE_2D_ARRAY, 
                TexRectangle = GL_TEXTURE_RECTANGLE, 
                TexCubeMap = GL_TEXTURE_CUBE_MAP, 
                TexCubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY, 
                TexBuffer = GL_TEXTURE_BUFFER, 
                Tex2DMS = GL_TEXTURE_2D_MULTISAMPLE, 
                Tex2DMSArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
            };

            enum class Format {
                RED = GL_RED,
                RG  = GL_RG,
                RGB = GL_RGB,
                BGR = GL_BGR,
                RGBA = GL_RGBA,
                BGRA = GL_BGRA,
                REDInt = GL_RED_INTEGER,
                RGInt  = GL_RG_INTEGER,
                RGBInt = GL_RGB_INTEGER,
                BGRInt = GL_BGR_INTEGER,
                RGBAInt = GL_RGBA_INTEGER,
                BGRAInt = GL_BGRA_INTEGER,
                StencilIndex = GL_STENCIL_INDEX,
                DepthStencil = GL_DEPTH_STENCIL,
                DepthComponent = GL_DEPTH_COMPONENT,
                DefaultFormat,
            };

        public:
            Texture();
            Texture(const Util::Image& image, Target target = Target::Tex2D, Format format = Format::DefaultFormat);
            Texture(const std::string& path, Target target = Target::Tex2D, Format format = Format::DefaultFormat);
            Texture(Texture&& texture);
            ~Texture();

            Texture& operator=(Texture&& texture);

            void bind() const;
            void unbind() const;
            void load(const Util::Image& image, Target target, Format format);

            bool isAlpha() const;
            unsigned int getWidth() const;
            unsigned int getHeight() const;
            Target getTarget() const;
            GLuint getID() const;

        private:
            Texture& operator=(const Texture&);
            Texture(const Texture&);

            void create();
            void destroy();
            void setTarget(Target target);
            void assingData(const Util::Image& image, const Format format) throw(Util::Exception::FatalError);
            void setParameters();
            void generateMipmap();

            bool _isAlpha;
            unsigned int _width;
            unsigned int _height;
            Target _target;
            GLuint _textureID;
    };

}

#endif
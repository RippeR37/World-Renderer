#include "Sector.h"

#include <Utils/Exception.h>
#include <Utils/File.h>

#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdio>

namespace Model {
    
    Sector::Sector() {
        setLatitude(0);
        setLongtitude(0);

        _mapSize = 1201;

        resize(_mapSize);
    }
    
    Sector::Sector(Sector&& sector) : _heightMap(std::move(sector._heightMap)), _texture(std::move(sector._texture)) {
        std::swap(_latitude, sector._latitude);
        std::swap(_longitude, sector._longitude);
        std::swap(_mapSize, sector._mapSize);
    }

    Sector& Sector::operator=(Sector&& sector) {
        _heightMap = std::move(sector._heightMap);
        _texture = std::move(sector._texture);

        std::swap(_latitude, sector._latitude);
        std::swap(_longitude, sector._longitude);
        std::swap(_mapSize, sector._mapSize);

        return *this;
    }
    
    void Sector::clear() {
        _heightMap.clear();
    }

    void Sector::loadData(const std::string& filePath) {
        std::ifstream fileStream;
        std::vector<short int> texData;
        short int height;

        std::cerr << "Loading sector " << Util::File::getFilenameExtensionless(filePath) << "... ";

        fileStream.open(filePath, std::ifstream::binary | std::ifstream::in);

        if(fileStream == false)
            throw new Util::Exception::FatalError(std::string("Unable to load heightmap from file: ") + filePath);

        for(int y = _mapSize - 1; y >= 0; y--) {
            for(int x = 0; x < _mapSize; ++x) {
                fileStream.read(reinterpret_cast<char*>(&height), sizeof(height));

                _heightMap[y][x] = swapEndiannes(height);
                texData.push_back(_heightMap[y][x]);
            }
        }
        
        fileStream.close();
        
        parseLocation(Util::File::getFilenameExtensionless(filePath));

        /**
         * Texture
         */
        glPixelStorei(GL_UNPACK_ALIGNMENT, 2);

        std::list<std::pair<GLenum, GLint>> parameters;
        parameters.push_back(std::make_pair<GLenum, GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        parameters.push_back(std::make_pair<GLenum, GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        _texture.setTarget(GL::Texture::Target::Tex2D);
        _texture.setFormat(GL::Texture::Format::RED);
        _texture.setInternalFromat(GL::Texture::InternalFormat::R16);
        _texture.bind();
            _texture.setData2D(1201, 1201, GL_SHORT, &texData[0]);
            _texture.setParameters();
            _texture.setParametersI(parameters);
            _texture.generateMipmap();
        _texture.unbind();

        std::cout << "done." << std::endl;
    }

    int Sector::getLatitude() const {
        return _latitude;
    }

    int Sector::getLongtitude() const {
        return _longitude;
    }

    short int Sector::getHeight(unsigned int x, unsigned int y) const {
        return _heightMap[y][x];
    }

    const Sector::HeightMap& Sector::getHeightMap() const {
        return _heightMap;
    }
    
    const GL::Texture& Sector::getTexture() const {
        return _texture;
    }

    void Sector::resize(unsigned int size) {
        _heightMap.resize(size);
        
        for(int y = 0; y < size; ++y)
            _heightMap[y].resize(size);
    }

    void Sector::setLatitude(int value) {
        _latitude = value;
    }

    void Sector::setLongtitude(int value) {
        _longitude = value;
    }

    void Sector::parseLocation(const std::string& fileName) {
        char xDir, yDir;
        int x, y;

        sscanf(fileName.c_str(), "%c%d%c%d", &yDir, &y, &xDir, &x);

        if(xDir == 'W' || xDir == 'w')
            x = -x;

        if(yDir == 'S' || yDir == 's')
            y = -y;

        setLatitude(y);
        setLongtitude(x);
    }

    short int Sector::swapEndiannes(short int value) {
        static union {
            int16_t value;
            int8_t  byte[2];
        } eUnion;

        eUnion.value = value;
        std::swap(eUnion.byte[0], eUnion.byte[1]);
        
        return eUnion.value;
    }

}
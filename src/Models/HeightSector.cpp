#include "HeightSector.h"
#include "../Utils/Exception.h"

#include <iostream>
#include <fstream>
#include <cstdint>

namespace Model {
    
    HeightSector::HeightSector() {
        setLatitude(0);
        setLongtitude(0);

        _mapSize = 1201;

        resize(_mapSize);
    }

    HeightSector::~HeightSector() {

    }

    void HeightSector::loadData(const std::string& filePath) {
        std::ifstream fileStream;
        short int height;
        
        fileStream.open(filePath, std::ifstream::binary | std::ifstream::in);

        if(fileStream == false)
            throw new Util::Exception::FatalError(std::string("Unable to load heightmap from file: ") + filePath);

        for(unsigned int y = 0; y < _mapSize; ++y) {
            for(unsigned int x = 0; x < _mapSize; ++x) {
                fileStream.read(reinterpret_cast<char*>(&height), sizeof(height));

                _heightMap[_mapSize - y - 1][x] = swapEndiannes(height); //invert to 
            }
        }
        
        fileStream.close();
    }

    int HeightSector::getLatitude() const {
        return _latitude;
    }

    int HeightSector::getLongtitude() const {
        return _longitude;
    }

    short int HeightSector::getHeight(unsigned int x, unsigned int y) const {
        return _heightMap[y][x];
    }

    const HeightSector::HeightMap& HeightSector::getHeightMap() const {
        return _heightMap;
    }

    void HeightSector::resize(unsigned int size) {
        _heightMap.resize(size);
        
        for(int y = 0; y < size; ++y)
            _heightMap[y].resize(size);
    }

    void HeightSector::setLatitude(int value) {
        _latitude = value;
    }

    void HeightSector::setLongtitude(int value) {
        _longitude = value;
    }

    short int HeightSector::swapEndiannes(short int value) {
        static union {
            int16_t value;
            int8_t byte[2];
        } eUnion;

        eUnion.value = value;
        std::swap(eUnion.byte[0], eUnion.byte[1]);
        
        return eUnion.value;
    }

}
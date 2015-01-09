#ifndef MODEL_SECTOR_H_INCLUDED
#define MODEL_SECTOR_H_INCLUDED

#include <Utils/GL+/Texture.h>

#include <string>
#include <vector>

namespace Model {

    class Sector {
        public:
            typedef std::vector<std::vector<short int>> HeightMap;

        public:
            Sector();
            ~Sector();

            Sector(Sector&& sector);

            void clear();
            void loadData(const std::string& filePath);

            int getLatitude() const;
            int getLongtitude() const;
            short int getHeight(unsigned int x, unsigned int y) const;
            const HeightMap& getHeightMap() const;
            const GL::Texture& getTexture() const;

        private:
            void resize(unsigned int size);

            void setLatitude(int value);
            void setLongtitude(int value);

            void parseLocation(const std::string& fileName);

            short int swapEndiannes(short int value);

            int _latitude;
            int _longitude;
            unsigned int _mapSize;
            HeightMap _heightMap;
            GL::Texture _texture;
    };

}

#endif
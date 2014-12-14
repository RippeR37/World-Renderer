#ifndef MODEL_HEIGHT_SECTOR_H_INCLUDED
#define MODEL_HEIGHT_SECTOR_H_INCLUDED

#include <string>
#include <vector>

namespace Model {
    
    class HeightSector {
        public:
            typedef std::vector<std::vector<short int>> HeightMap;

        public:
            HeightSector();
            ~HeightSector();

            void loadData(const std::string& filePath);

            int getLatitude() const;
            int getLongtitude() const;
            short int getHeight(unsigned int x, unsigned int y) const;
            const HeightMap& getHeightMap() const;

        private:
            void resize(unsigned int size);

            void setLatitude(int value);
            void setLongtitude(int value);

            short int swapEndiannes(short int value);

            int _latitude;
            int _longitude;
            unsigned int _mapSize;
            HeightMap _heightMap;
    };

}

#endif
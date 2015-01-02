#include "Map.h"

namespace Model {

    Map::Map() {

    }

    Map::~Map() {

    }

    void Map::init() {
        glm::ivec2 start = glm::ivec2(14, 49);
        glm::ivec2 stop  = glm::ivec2(23, 54);

        for(int y = start.y; y <= stop.y; ++y) {
            for(int x = start.x; x <= stop.x; ++x) {

                addSector(x, y);

            }
        }
    }

    void Map::addSector(int x, int y) {
        std::string xDir, yDir;
        std::string loadPath;

        if(x >= 0) xDir = 'E';
        else       xDir = 'W';

        if(y >= 0) yDir = 'N';
        else       yDir = 'S';

        x = std::abs(x);
        y = std::abs(y);
        
        if(x < 10)  xDir = xDir + "0";
        if(x < 100) xDir = xDir + "0";
        if(y < 10)  yDir = yDir + "0";
        
        loadPath = 
            "assets/heightmaps/" +
            yDir + std::to_string(y) + 
            xDir + std::to_string(x) + 
            ".hgt";

        _sectors.emplace_back();
        _sectors.back().loadData(loadPath);
    }

    const std::vector<Sector>& Map::getSectors() const {
        return _sectors;
    }

}
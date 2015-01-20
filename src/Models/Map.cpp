#include "Map.h"
#include "../Game.h"

#include <algorithm>
#include <iostream>

namespace Model {

    Map::Map() {

    }

    Map::Map(Map&& map) : _sectors(std::move(map._sectors)) {
        
    }

    Map& Map::operator=(Map&& map) {
        _sectors = std::move(map._sectors);
        return *this;
    }

    void Map::init() {
        const std::vector<std::string>& arguments = Game::get().getArguments();
        std::vector<glm::ivec2> sectorsToLoad;
        std::vector<std::string> sectorsToLoadStr;

        for(int i = 1; i < arguments.size(); ++i) {
            if(arguments[i][0] == '-' && (i + 4) < arguments.size()) {
                if(arguments[i][1] == 'r') {

                    glm::ivec2 from;
                    glm::ivec2 to;

                    from.x = std::stoi(arguments[i+1]);
                    from.y = std::stoi(arguments[i+2]);
                    to.x = std::stoi(arguments[i+3]);
                    to.y = std::stoi(arguments[i+4]);

                    for(int y = from.y; y <= to.y; ++y) {
                        for(int x = from.x; x <= to.x; ++x) {
                            sectorsToLoad.push_back(glm::ivec2(x, y));
                        }
                    }

                    i+= 4;

                } else if(arguments[i][1] == 't') {
                    std::cerr << "Undefined behaviour: range-to argument found before range-from! Ignoring..." << std::endl;

                } else {
                    std::cerr << "Unrecognized argument: '" << arguments[i] << "'" << std::endl;

                }
            } else if(arguments[i][0] == 'N' || arguments[i][0] == 'n' || arguments[i][0] == 'S' || arguments[i][0] == 's') {
                sectorsToLoadStr.push_back(arguments[i]);

            } else {
                std::cerr << "Unrecognized argument: '" << arguments[i] << "'" << std::endl;
            }
        }

        int sectorsLoaded = 0;
        int sectorsAll = sectorsToLoad.size() + sectorsToLoadStr.size();
        for(int i = 0; i < sectorsToLoad.size(); ++i) {
            Game::get().getWindow().update();
            Game::get().getWindow().appendTitle(
                std::string(" | Loading: ") + 
                std::to_string(100 * sectorsLoaded / sectorsAll) + 
                "%"
            );

            addSector(sectorsToLoad[i].x, sectorsToLoad[i].y);
            sectorsLoaded += 1;
        }

        for(int i = 0; i < sectorsToLoadStr.size(); ++i) {
            Game::get().getWindow().update();
            Game::get().getWindow().appendTitle(
                std::string(" | Loading: ") + 
                std::to_string(100 * sectorsLoaded / sectorsAll) + 
                "%"
            );

            addSector(sectorsToLoadStr[i]);
            sectorsLoaded += 1;
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

    void Map::addSector(const std::string& file) {
        std::string loadPath;
        std::string fileName = file;
        std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);

        loadPath =
            "assets/heightmaps/" +
            file +
            ".hgt";

        _sectors.emplace_back();
        _sectors.back().loadData(loadPath);
    }

    const std::vector<Sector>& Map::getSectors() const {
        return _sectors;
    }

}
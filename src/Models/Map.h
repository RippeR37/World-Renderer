#ifndef MODEL_MAP_H_INCLUDED
#define MODEL_MAP_H_INCLUDED

#include "Sector.h"

#include <atomic>
#include <vector>

namespace Model {

    class Map {
        public:
            Map();
            Map(Map&& map);

            Map& operator=(Map&& map);

            void init();
            void addSector(int x, int y);
            void addSector(const std::string& file);

            const std::vector<Sector>& getSectors() const;

        private:
            std::vector<Sector> _sectors;

    };

}

#endif
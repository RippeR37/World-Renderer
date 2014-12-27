#ifndef MODEL_MAP_H_INCLUDED
#define MODEL_MAP_H_INCLUDED

#include "Sector.h"

#include <vector>

namespace Model {

    class Map {
        public:
            Map();
            ~Map();

            void init();
            void addSector(int x, int y);

            const std::vector<Sector>& getSectors() const;

        private:
            std::vector<Sector> _sectors;

    };

}

#endif
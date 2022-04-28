#ifndef MMAZE_JOUEUR_HPP
#define MMAZE_JOUEUR_HPP

#include "direction.hpp"

namespace MMaze {
    class joueur {

        public:
            joueur(Direction _peutDeplacerA);
            Direction getPeutDeplacerA();

        private:
            Direction peutDeplacerA;
 
    };
}

#endif

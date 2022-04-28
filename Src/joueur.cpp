#include "joueur.hpp"


namespace MMaze {

    joueur::joueur(Direction _peutDeplacerA) :
        peutDeplacerA(_peutDeplacerA)
    {}

    Direction joueur::getPeutDeplacerA(){
        return peutDeplacerA;
    }

}

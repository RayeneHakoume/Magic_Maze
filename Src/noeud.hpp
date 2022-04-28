#ifndef MMAZE_NOEUD_HPP
#define MMAZE_NOEUD_HPP

#include "case.hpp"
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

namespace MMaze {

    class Noeud {
        public:
            //Noeud(Case* _caseDuNoeud);
            Noeud(int _caseDuNoeud, int _id);
            Noeud(MMaze::Noeud* _n);

            void ajouterUnVoisin(Direction d, Noeud* n);
            
            vector<Noeud*> getTabVoisins(int direction);
            vector<Noeud*> getTabVoisins(Direction d);
            Noeud* getTabVoisins(int direction,int j);
            Noeud* getTabVoisins(Direction d,int j);

            //Case* getcaseDuNoeud();
            int getIndex();
            int getId();

            bool estUnVoisin(Noeud* n);
            Direction VoisinDirection(Noeud *n);

            void affichage();
                
        private :

        //Case* caseDuNoeud;
        int id;
        int caseDuNoeud;
        vector <Noeud*> tab_voisins[4];

        //tab_voisins[0] tout les élément assecible en Bas à partir de la case du Noeud
        //tab_voisins[1] tout les élément assecible a Droite à partir de la case du Noeud
        //tab_voisins[2] tout les élément assecible en Haut à partir de la case du Noeud
        //tab_voisins[3] tout les élément assecible a Gauche à partir de la case du Noeud

    } ;
}
#endif
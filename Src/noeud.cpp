#include "noeud.hpp"

namespace MMaze {

/*	
Noeud::Noeud(Case* _caseDuNoeud) :
    caseDuNoeud(_caseDuNoeud),
{}
*/
    Noeud::Noeud(int _caseDuNoeud, int _id) :
        id(_id),
        caseDuNoeud (_caseDuNoeud)
    {}

    Noeud::Noeud(Noeud* _n) :
        caseDuNoeud (_n->getIndex())
    {
        unsigned int i, j ;
        for(i = 0 ; i<4 ; i++){
            for(j = 0 ; j < _n->getTabVoisins(i).size(); j++)
            tab_voisins[i][j] = _n->getTabVoisins(i,j);
        }
    }

    vector<Noeud*> Noeud::getTabVoisins(int direction){
        return tab_voisins[direction];
    }

    vector<Noeud*> Noeud::getTabVoisins(Direction d){
        if(d == MMaze::Direction::BAS) return tab_voisins[0];
        else if(d == MMaze::Direction::DROITE) return tab_voisins[1];
        else if(d == MMaze::Direction::HAUT) return tab_voisins[2];
        else if(d == MMaze::Direction::GAUCHE) return tab_voisins[3];
        return tab_voisins[(int) d];   
    }


    Noeud* Noeud::getTabVoisins(int direction,int j){
        return tab_voisins[direction][j];
    }

    Noeud* Noeud::getTabVoisins(Direction d,int j){
        if(d == MMaze::Direction::BAS) return tab_voisins[0][j];
        else if(d == MMaze::Direction::DROITE) return tab_voisins[1][j];
        else if(d == MMaze::Direction::HAUT) return tab_voisins[2][j];
        else if(d == MMaze::Direction::GAUCHE) return tab_voisins[3][j];
        return tab_voisins[(int) d][j];
    }


    int Noeud::getIndex(){
        return caseDuNoeud;
    }

    int Noeud::getId(){
        return id;
    }

   /* graph non-orientée
    void Noeud::ajouterUnVoisin(Direction d, Noeud* n ) {
        if(!estUnVoisin(n)){
            Noeud* p = this;
            if(d == MMaze::Direction::GAUCHE) {
                tab_voisins[0].emplace_back(n);
                n->tab_voisins[1].emplace_back(p);
            }    
            else if(d == MMaze::Direction::DROITE) {
                tab_voisins[1].emplace_back(n);
                n->tab_voisins[0].emplace_back(p);
            }
            else if(d == MMaze::Direction::HAUT) {
                tab_voisins[2].emplace_back(n);
                n->tab_voisins[3].emplace_back(p);
            }
            else if(d == MMaze::Direction::BAS) {
                tab_voisins[3].emplace_back(n);
                n->tab_voisins[2].emplace_back(p);
            }
        }
    }  
    */

   //graph orientée
    void Noeud::ajouterUnVoisin(Direction d, Noeud* n ) {
        if(d == MMaze::Direction::BAS) {
            tab_voisins[0].emplace_back(n);
        }
        else if(d == MMaze::Direction::DROITE) {
            tab_voisins[1].emplace_back(n);
        }
        else if(d == MMaze::Direction::HAUT) {
            tab_voisins[2].emplace_back(n);
        }
        else if(d == MMaze::Direction::GAUCHE) {
            tab_voisins[3].emplace_back(n);
        }    

    }  

    bool Noeud::estUnVoisin(Noeud* n){
        unsigned int i,j;
        for(i = 0; i< 4; i++){
            for(j = 0; j< tab_voisins[i].size(); j++){
                if(n == tab_voisins[i][j]) return true;
            }
        }
        return false;
    }

    Direction Noeud::VoisinDirection(Noeud *n){
        unsigned i,j;
        for(i = 0; i< 4; i++){
            for(j = 0; j< tab_voisins[i].size(); j++){
                if(n == tab_voisins[i][j]) {
                    if(i == 0)  return Direction::BAS;
                    else if(i == 1) return Direction::DROITE;
                    else if(i == 2) return Direction::HAUT;
                    else if(i == 3) return Direction::GAUCHE;
                }
            }
        }
        return Direction::HAUT;
    }


    void Noeud::affichage(){
        unsigned int i,j;
        for(i=0;i<4;i++){
            if(i == 0) cout<<"BAS    : ";
            if(i == 1) cout<<"DROITE : ";
            if(i == 2) cout<<"HAUT   : ";
            if(i == 3) cout<<"GAUCHE : ";

            for(j=0;j<tab_voisins[i].size();j++){
                cout<<tab_voisins[i][j]->caseDuNoeud<<"("<<tab_voisins[i][j]->id<<")"<<" --> ";
            }
            cout<<endl;
        }
        cout<<endl;
    }


} //end of namespace MMaze

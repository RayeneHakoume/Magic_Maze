#ifndef MMAZE_PLATEAU_HPP
#define MMAZE_PLATEAU_HPP

#include "tuile.hpp"
#include "graph.hpp"

#include "joueur.hpp"
#include "pion.hpp"

#include <vector>

namespace MMaze {
  const unsigned int nbJoueur = 4;

  class plateau {
      public:
        plateau();
        int ajouterTuile(int CasePorteFranchi, int colonne, int ligne);
        bool aTouverCaseSiteDecouvert();

        void jouer();
        bool gagner();


      public:
        vector <tuile> tab_tuile ; 
        vector <Graph> tab_graph ; 

        //tab[0] = objectif Jaune // tab[1] = objectif vert // tab[2] == objectif orange //tab[3] = objectif violet
        //bool tabCaseSiteDecouvert[8];
        //Noeud ou se trouve CaseSiteDecouvert
        Noeud* tabNoeudSiteDecouvert[8];

        //les objectifs et les sorties à placer (ou rien)
        Melangeur <int> melSite;
        vector <joueur> joueurs;
        unsigned int nbPion;
        vector <Pion> pions;

        
  };

}

#endif

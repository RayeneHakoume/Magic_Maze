#ifndef MMAZE_TUILES_HPP
#define MMAZE_TUILES_HPP

#include "melangeur.hpp"
#include "UnionFind.hpp"
#include "case.hpp"
#include "mur.hpp"

#include <iostream>
#include <assert.h>
//#include <stdlib.h> // pour srand() et rand()
//#include <time.h> // pour time()   

namespace MMaze {
  const unsigned int MAX_NB_MURS = 24 ;
  const unsigned int MAX_NB_CASES = 16 ;

  class tuile {

    public :
    //construteur
      tuile(unsigned int _ligne, unsigned int _colonne, bool _estDepart, unsigned int site=0);
      

      bool getTabMurs(unsigned int i);
      int gettabCasePossedeObjet(unsigned int i) ; 
      
      unsigned int getLigne();
      unsigned int getColonne();
      void initialisation_depart();
      void placerPionDepart(UnionFind &uf);
      void placerPorteDepart();

      void initialisation_stantard(unsigned int site);
      void placerSiteStantard(unsigned int site,std::vector <int> &objImportant);

      void placerMur(UnionFind &uf, std::vector <int> objImportant);
      void placerBoutique();

      //renvoie vrai quand toute les cases importes de la tuile est accessible
      bool estOk(UnionFind uf, std::vector <int> objImportant);

      void tournerTuile(unsigned int CasePorte);

    private :
    //unsigned int ligne, colonne;
      unsigned int ligne, colonne;
    //booléan qui dit si la tuile est une tuile de depart (true) ou classique (false)
      bool estDepart;
      //tableau de taille 24 de booléan : true si le mur present ou pas 
      bool tabMurs[MAX_NB_MURS] ;
      //tableau de taille 16 d'entier positif : indique sur case l'objet 
      //0 si la case ne comporte pas d'objet
      unsigned int tabCasePossedeObjet[MAX_NB_CASES] ; 
      
      std::vector <int> CaseobjImportant;
  } ;
}
#endif

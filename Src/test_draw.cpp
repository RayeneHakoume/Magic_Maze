#include "draw.hpp"
#include "tuile.hpp"
#include <iostream>

using namespace std;

using namespace MMaze ;

int main() {


  //srand((unsigned int)time(NULL));
  //MelangeurOptions::imprevisible();
  PadPlateau pad ;
  //pad.pl.ajouterTuile(2,10,10);
  //pad.ajouter_tuile(9,10);
  //pad.emplacement.push_back(9);
  //pad.emplacement.push_back(10);
  pad.miseAJour();

  //pad.miseAJour();

  //pad.ajouter_tuile(0,0) ;
  
  //pad.ajouter_boutique(0,0,Case(0)) ;
  //pad.ajouter_sortie(0,0, Case(15), Couleur::JAUNE) ;
  //pad.ajouter_mur(0,0,Mur(Case(0), Case(1))) ;
  //pad.ajouter_mur(0,0,Mur(Case(0), Case(4))) ;
  //pad.ajouter_porte(0,0, Case(11), Couleur::JAUNE) ;

  //pad.ajouter_tuile(0,1) ; //enleve la porte jaune

  //pad.ajouter_sortie(0,1, Case(0), Couleur::VIOLET) ;
  //pad.ajouter_porte(0,1, Case(4), Couleur::AUCUNE) ;
  //pad.ajouter_porte(0,1, Case(11), Couleur::VIOLET) ;
  //pad.ajouter_porte(0,1, Case(13), Couleur::VERT) ;
  //pad.ajouter_mur(0,1, Mur(Case(4), Case(5))) ;
  //pad.ajouter_mur(0,1, Mur(Case(4), Case(8))) ;

/*
  pad.ajouter_tuile(1,0) ;
  pad.ajouter_porte(1,0,Case(11), Couleur::AUCUNE) ;
  pad.ajouter_vortex(1,0,Case(6), Couleur::JAUNE) ;

  pad.ajouter_tuile(1,1) ;
  pad.ajouter_porte(1,1,Case(2), Couleur::AUCUNE) ;
  pad.ajouter_porte(1,1,Case(4), Couleur::JAUNE) ;

  pad.placer_joueur(0,0,Case(5),Couleur::JAUNE) ;
  pad.placer_joueur(0,0,Case(6),Couleur::VERT) ;
  pad.placer_joueur(0,0,Case(9),Couleur::VIOLET) ;
  pad.placer_joueur(0,0,Case(10),Couleur::ORANGE) ;
 */
#ifndef NO_CAIRO
  //pad.dessiner("/tmp/plateau.svg") ;
  //pad.dessiner("/tmp/plateau.png") ;
#endif

  std::cout << pad << std::endl ;

  //pad.save("/tmp/pad.json") ;

  //PadPlateau cpy ;
  //cpy.load("/tmp/pad.json") ;
  //std::cout << cpy << std::endl ;

  //for(int i=0 ; i<pad.m_murs.size();i++){
  //  cout<< i << endl ;
  //}
  

  return 0 ;
}

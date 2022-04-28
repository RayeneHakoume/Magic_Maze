#include "noeud.hpp"
#include "graph.hpp"
#include "tuile.hpp"
#include "plateau.hpp"
#include "draw.hpp"

#include <iostream>

using namespace std;

using namespace MMaze ;


int main() {

  //------------VERIFICATION DE NOEUD------------------------------
  //on verifie surtout que la fonction ajouterUnVoisin fonctionne
  Case c0(0);
  Case c1(1);
  Case c2(2);
  Case c3(3);
  Case c4(4);
  /*
  Noeud n0(&c0);
  Noeud n1(&c1);
  Noeud n2(&c2);
  Noeud n3(&c3);
  Noeud n4(&c4);

  Noeud n0(0);
  Noeud n1(1);
  Noeud n2(2);
  Noeud n3(3);
  Noeud n4(4);

  n0.ajouterUnVoisin(MMaze::Direction::GAUCHE, &n1);

  if(n0.estUnVoisin(&n1)) cout<<"ok"<<endl;
  if(n1.estUnVoisin(&n0)) cout<<"ok"<<endl;

  if(n1.estUnVoisin(&n2)) cout<<"probleme"<<endl;
  
  cout<<"le voisin de gauche de n0 est : "<<n0.getTabVoisins(0,0)->getIndexCaseDuNoeud()<<endl;
  cout<<"taille de n0.tab_voisins[0] (gauche) : "<<n0.getTabVoisins(0).size()<<endl;
  cout<<"taille de n0.tab_voisins[1] (droite) : "<<n0.getTabVoisins(1).size()<<endl;
  
  n0.ajouterUnVoisin(MMaze::Direction::GAUCHE, &n2);
  n0.ajouterUnVoisin(MMaze::Direction::DROITE, &n3);
  cout<<endl<<"affichage de n0"<<endl;
  n0.affichage();
  cout<<endl<<"affichage de n1"<<endl;
  n1.affichage();
  cout<<endl<<"affichage de n2"<<endl;
  n2.affichage();
  cout<<endl<<"affichage de n3"<<endl;
  n3.affichage();
  cout<<endl<<"affichage de n4"<<endl;
  n4.affichage();
  */
    //------------VERIFICATION DE GRAPHE------------------------------
  /*
  PadPlateau pad ;
  std::cout << pad << std::endl ;

  tuile* tui = &(pad.pl.tab_tuile[0]);
  Graph gph(tui, 0);
  //  for(int i=0 ; i<16; i++){
  //  cout<<"Case "<<i<<" : "<<endl;
  //  gph.tabNoeuds[i].affichage();
  //}

  vector <Noeud*> chemin ;

  
  chemin = (gph.parcours_en_largeur(&gph.tabNoeuds[2], &gph.tabNoeuds[8]));
  cout<<endl;
  for(unsigned int i =0; i<chemin.size();i++){
    cout<<i<<" : ";
    if(chemin[i] != nullptr) cout<<chemin[i]->getIndexCaseDuNoeud()<<" ";
    cout<<endl;
  }
  

  vector<pair<Noeud*,Direction>> route = gph.plus_court_chemin(&gph.tabNoeuds[2], &gph.tabNoeuds[4]);
  for(unsigned int i =0; i<route.size();i++){
    cout<<"< "<<route[i].first->getIndex()<<" , ";
    if(route[i].second == Direction::BAS) cout<<"BAS "<<"> "<<endl;
    if(route[i].second == Direction::HAUT) cout<<"HAUT "<<"> "<<endl;
    if(route[i].second == Direction::GAUCHE) cout<<"GAUCHE "<<"> "<<endl;
    if(route[i].second == Direction::DROITE) cout<<"DROITE "<<endl;

  }

  cout<<endl;
  cout<<"cou"<<endl;
  Direction d = opposee(Direction::GAUCHE);
  if(d==Direction::BAS) cout<<"bas"<<endl;
  if(d==Direction::HAUT) cout<<"HAUT"<<endl;
  if(d==Direction::GAUCHE) cout<<"GAUCHE"<<endl;
  if(d==Direction::DROITE) cout<<"bas"<<endl;

  //cout<<endl;

  
  for(int i=0 ; i<16; i++){
    cout<<"Case "<<i<<" : "<<endl;
    gph.tabNoeuds[i].affichage();
  }
  */

    //------------VERIFICATION DE LA FONCTION FUSION GRAPHE------------------------------
    
  PadPlateau pad ;
  pad.pl.ajouterTuile(2,10,10);
  pad.ajouter_tuile(10,11);
  pad.emplacement.push_back(10);
  pad.emplacement.push_back(11);
  pad.miseAJour();

  std::cout << pad << std::endl ;

  tuile* tui0 = &(pad.pl.tab_tuile[0]);
  tuile* tui1 = &(pad.pl.tab_tuile[1]);

  Graph gph0(tui0, 0);
  Graph gph1(tui1, 1);

  gph0.fusionGraph(&gph1,10,10,10,11);

    cout<<"Case "<<8<<" : "<<endl;
    gph0.getNoeud(8)->affichage();
    cout<<endl;
    cout<<"Case "<<9<<" : "<<endl;
    gph0.getNoeud(9)->affichage();
    cout<<endl;
    cout<<"Case "<<10<<" : "<<endl;
    gph0.getNoeud(10)->affichage();
    cout<<endl;
    cout<<"Case "<<11<<" : "<<endl;
    gph0.getNoeud(11)->affichage();

}

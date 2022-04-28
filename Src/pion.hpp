#ifndef MMAZE_PION_HPP
#define MMAZE_PION_HPP

#include "noeud.hpp"
#include "graph.hpp"

namespace MMaze {

enum CouleurPion {JAUNE, VERT, ORANGE, VIOLET};


class Pion {

	public :
		//constructeur par couleur et pointeur sur un noeud
		Pion(unsigned int _c, Noeud* _NoeudPion,Graph* _GraphPion);
	
		CouleurPion getCp();
		Noeud* getNoeudPion();	
		Graph* getGraphPion();
			
		void setNoeud(Noeud* _NoeudPion);			
		void deplacerPion(Noeud* _NoeudPion, vector <Graph> tabg);


    	void chemin_porte_plus_proche();
		void chemin_objectif(Noeud* n);
		void chemin_sorti(Noeud* n);


	public :
		//1 = JAUNE // 2 = VERT // 3 = ORANGE // 4 = VIOLET //
		CouleurPion cp;
		Noeud* NoeudPion;
		Graph* GraphPion;

		vector<pair<Noeud*,Direction>> chemin ;
		
		bool estRechercheObjectif;
		bool estRechercheSortie;
		bool aTrouverObjectif;

} ;

} //end of namespace MMaze

#endif



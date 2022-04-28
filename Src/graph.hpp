#ifndef LIFAP6_GRAPH_HPP_
#define LIFAP6_GRAPH_HPP_

#include "tuile.hpp"
#include "noeud.hpp"
#include <vector>
#include <queue>
#include <cassert>

namespace MMaze {

class Graph {
	public:
	Graph(tuile* _tuileGraph, int _id);
	vector <Noeud> getTabNoeud();
	Noeud* getNoeud(unsigned int i);
    int getId();
	tuile* getTuileGraph();

	vector<Noeud*>  parcours_en_largeur(Noeud* depart, Noeud* arrivee);
	vector<pair<Noeud*,Direction>> parcours_en_largeur_d(Noeud* depart, Noeud* arrivee);
    vector<pair<Noeud*,Direction>> plus_court_chemin(Noeud* depart, Noeud* arrivee);
    void fusionGraph(Graph *g, int ligne1, int colonne1, int ligne2, int colonne2);


    private:
	int id;
	vector <Noeud> tabNoeuds;
	tuile* tuileGraph;
	} ;
}

#endif

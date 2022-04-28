#include "pion.hpp"

namespace MMaze {

	Pion::Pion( unsigned int _c, Noeud* _NoeudPion, Graph* _GraphPion) :
		NoeudPion (_NoeudPion) ,
		GraphPion(_GraphPion),
		estRechercheObjectif(false), estRechercheSortie(false),
		aTrouverObjectif(false)
	{
		if(_c == 1) cp = CouleurPion::JAUNE ;
		if(_c == 2) cp = CouleurPion::VERT ;
		if(_c == 3) cp = CouleurPion::ORANGE ;
		if(_c == 4) cp = CouleurPion::VIOLET ;
	}

	CouleurPion Pion::getCp(){
		return cp;
	}	
	
	Graph* getGraphPion;

	Noeud* Pion::getNoeudPion(){
		return NoeudPion;
	}

	Graph*  Pion::getGraphPion(){
		return GraphPion;
	}



	void Pion::setNoeud(Noeud* _NoeudPion){
		NoeudPion = _NoeudPion;
	}

	void Pion::deplacerPion(Noeud* _NoeudPion, vector <Graph> tabg){
		setNoeud(_NoeudPion);
		GraphPion = &tabg[_NoeudPion->getId()] ;
	}

	
    void Pion::chemin_porte_plus_proche(){
        int couleurPorte;
        if (cp == CouleurPion::JAUNE) couleurPorte = 31;
        else if (cp == CouleurPion::VERT) couleurPorte = 32;
        else if (cp == CouleurPion::ORANGE) couleurPorte = 33;
        else if (cp == CouleurPion::VIOLET) couleurPorte = 34;

        if( GraphPion->getTuileGraph()->gettabCasePossedeObjet(2) == couleurPorte ){
            chemin = GraphPion->plus_court_chemin(NoeudPion, (GraphPion->getNoeud(2)));
        }
        else if( GraphPion->getTuileGraph()->gettabCasePossedeObjet(4) == couleurPorte ){
            chemin = GraphPion->plus_court_chemin(NoeudPion, (GraphPion->getNoeud(4)));
        }
        else if( GraphPion->getTuileGraph()->gettabCasePossedeObjet(11) == couleurPorte ){
            chemin = GraphPion->plus_court_chemin(NoeudPion, (GraphPion->getNoeud(11)));
        }
        
        else{
            chemin = GraphPion->plus_court_chemin(NoeudPion, (GraphPion->getNoeud(13)));
        }
    }

	void Pion::chemin_objectif(Noeud* n){

	}

	void Pion::chemin_sorti(Noeud* n){

	}	

}

 //end of namespace MMaze


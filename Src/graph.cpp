#include "graph.hpp"

namespace MMaze {

    Graph::Graph(tuile* _tuileGraph, int _id) :
        id(_id),
        tuileGraph (_tuileGraph)
    {
        unsigned int i=0,j=0;
        for(i=0 ; i< MAX_NB_CASES; i++){
            //Noeud n(i, (_id*MAX_NB_CASES+i) );
            Noeud n(i, _id );
            tabNoeuds.push_back( n ) ;
        }
        for(i=0 ; i< MAX_NB_CASES ; i++){

            for(j=0 ; j< 4; j++){
                try{
                    MMaze::Case c(i);

                    MMaze::Case v = c.voisine((Direction) j);
                    bool pasDeMur = true;
                    Mur m(c,v);
                    
                    if(_tuileGraph->getTabMurs(m.index())) pasDeMur=false;
                    else pasDeMur=true;
    
                    if(_tuileGraph->gettabCasePossedeObjet(v.index()) != 10 && pasDeMur ){
                        tabNoeuds[i].ajouterUnVoisin((Direction) j, &tabNoeuds[v.index()]  );

                        Case vv = v.voisine((Direction) j);
                        Mur mm(v,vv);
                        if(_tuileGraph->getTabMurs(mm.index())) pasDeMur=false;
                        else pasDeMur=true;
                        if(_tuileGraph->gettabCasePossedeObjet(vv.index()) != 10 && pasDeMur ){
                            tabNoeuds[i].ajouterUnVoisin((Direction) j, &tabNoeuds[vv.index()] );

                            Case vvv = vv.voisine((Direction) j);
                            Mur mmm(vv,vvv);
                            if(_tuileGraph->getTabMurs(mmm.index())) pasDeMur=false;
                            else pasDeMur=true;
                            if(_tuileGraph->gettabCasePossedeObjet(vvv.index()) != 10 && pasDeMur ){
                                tabNoeuds[i].ajouterUnVoisin((Direction) j, &tabNoeuds[vvv.index()] );
                            }
                        }                  
                    }
                } catch (std::exception& e) {}

            }            
        }
    }

    vector <Noeud> Graph::getTabNoeud(){
        return tabNoeuds;
    }

    Noeud* Graph::getNoeud(unsigned int i){
        return  &tabNoeuds[i];
    }

    int Graph::getId(){
        return  id;
    }

    tuile*  Graph::getTuileGraph(){
        return tuileGraph ;
    }


	vector<Noeud*> Graph::parcours_en_largeur(Noeud* depart, Noeud* arrivee){
        assert(tuileGraph->gettabCasePossedeObjet(depart->getIndex()) != 10 ) ;
        assert(tuileGraph->gettabCasePossedeObjet(arrivee->getIndex()) != 10 ) ;
            
        queue<Noeud*> FIFO;    
        vector<Noeud*> predecesseur;    
        for(unsigned int i=0; i<tabNoeuds.size(); i++){
            predecesseur.push_back(nullptr);
        }
        FIFO.push(depart);
        while( predecesseur[arrivee->getIndex()] == nullptr ){

            for(int i=0;i<4;i++){
                for(unsigned int j=0; j<FIFO.front()->getTabVoisins(i).size();j++){
                    //si le noeud trouvé n'a pas été visité
                    //on le met sur la liste d'attente + on ajoute son predecesseur
                    Noeud *vois = FIFO.front()->getTabVoisins((MMaze::Direction) i, j);
                    if( predecesseur[vois->getIndex()] == nullptr){
                        FIFO.push(vois);
                        predecesseur[vois->getIndex()] = FIFO.front();                        
                    }
                }
            }
            FIFO.pop();
        }  
        return predecesseur;     
    }

    vector<pair<Noeud*,Direction>> Graph::plus_court_chemin(Noeud* depart, Noeud* arrivee){
        
        vector <Noeud*> predec ;
        vector<pair<Noeud*,MMaze::Direction>> chemin;
        predec = parcours_en_largeur(depart, arrivee);
        Noeud *tmp = arrivee;

        while(tmp != depart ){
            chemin.push_back ( make_pair( tmp, this->tabNoeuds[predec[tmp->getIndex()]->getIndex()].VoisinDirection( tmp)   ) );
            tmp = predec[tmp->getIndex()] ;
        }        
        return chemin;
    }

    void Graph::fusionGraph(Graph *g, int ligne1, int colonne1, int ligne2, int colonne2){

        unsigned int porteG, porteAG , i;
        int j;
        Direction d;

        //on le fusion avec une tuile à GAUCHE // 4 --> 11
        if(ligne1 == ligne2 && colonne1 == (colonne2 +1) ){
            
            porteG = 4 ;
            porteAG = 11 ;
            d = Direction::GAUCHE;
            j = porteG + 1 ;
            while(tabNoeuds[porteG].estUnVoisin(&tabNoeuds[j]) ){
                tabNoeuds[j].ajouterUnVoisin(d, &(g->tabNoeuds[porteAG])) ;    
                for(i = 0 ; i< g->tabNoeuds[porteAG].getTabVoisins(d).size() ; i++  ){
                    tabNoeuds[j].ajouterUnVoisin(d,(g->tabNoeuds[porteAG].getTabVoisins(d,i) )) ;
                }
                j++;
            }
        }

        //on le fusion avec une tuile à DROITE //  11 --> 4
        else if(ligne1 == ligne2 && colonne1 == (colonne2 -1) ){
            porteG = 11 ;
            porteAG = 4 ;
            d = Direction::DROITE;
            j = porteG - 1 ;
            while(tabNoeuds[porteG].estUnVoisin(&tabNoeuds[j]) ){
                tabNoeuds[j].ajouterUnVoisin(d, &(g->tabNoeuds[porteAG])) ;    
                for(i = 0 ; i< g->tabNoeuds[porteAG].getTabVoisins(d).size() ; i++  ){
                    tabNoeuds[j].ajouterUnVoisin(d,(g->tabNoeuds[porteAG].getTabVoisins(d,i) )) ;
                }
                j--;
            }
        }

        //on le fusion avec une tuile en HAUT // 2 --> 13
        else if(ligne1 == (ligne2+1) && colonne1 == colonne2 ){

            porteG = 2 ;
            porteAG = 13 ;
            d = Direction::HAUT;
            j = porteG + 4  ;
            while(tabNoeuds[porteG].estUnVoisin(&tabNoeuds[j]) ){
                tabNoeuds[j].ajouterUnVoisin(d, &(g->tabNoeuds[porteAG])) ;    
                for(i = 0 ; i< g->tabNoeuds[porteAG].getTabVoisins(d).size() ; i++  ){
                    tabNoeuds[j].ajouterUnVoisin(d,(g->tabNoeuds[porteAG].getTabVoisins(d,i) )) ;
                }
                j += 4;
            }
        }

        //on le fusion avec une tuile en BAS // 13 --> 2
        else if(ligne1 == (ligne2-1) && colonne1 == colonne2 ){
            porteG = 13 ;
            porteAG = 2 ;
            d = Direction::BAS;
            j = porteG - 4  ;
            while(tabNoeuds[porteG].estUnVoisin(&tabNoeuds[j])){
                tabNoeuds[j].ajouterUnVoisin(d, &(g->tabNoeuds[porteAG])) ;    
                for(i = 0 ; i< g->tabNoeuds[porteAG].getTabVoisins(d).size() ; i++  ){
                    tabNoeuds[j].ajouterUnVoisin(d,(g->tabNoeuds[porteAG].getTabVoisins(d,i) )) ;
                }
                j -= 4;
            }
        }
        tabNoeuds[porteG].ajouterUnVoisin(d, &(g->tabNoeuds[porteAG])) ;    
        for(i = 0 ; i< g->tabNoeuds[porteAG].getTabVoisins(d).size() ; i++  ){
            tabNoeuds[porteG].ajouterUnVoisin(d, (g->tabNoeuds[porteAG].getTabVoisins(d,i))) ;
        }

    }

}

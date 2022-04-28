#include "plateau.hpp"
#include <iostream>
using namespace std;

namespace MMaze {

    plateau::plateau() :
    //au debut de la partie on a 4 pions
        nbPion(4)
    {
        //on initialise aléatoirement dans quelle direction chaque joueur va pouvoir dirigier les pions
        Melangeur <Direction> md;
        md.inserer(Direction::BAS);
        md.inserer(Direction::DROITE);
        md.inserer(Direction::HAUT);
        md.inserer(Direction::GAUCHE);

        for(unsigned int i=0; i<nbJoueur; i++){
            joueurs.emplace_back(md.retirer());
        }

        //on initialise dans melSite tout les objectifs et les sorties a placer 
        //+ on rajoute aléatoirement un nb de tuile qui n'aura rien à trouver
        melSite.inserer(41);
        melSite.inserer(42);
        melSite.inserer(43);
        melSite.inserer(44);

        melSite.inserer(51);
        melSite.inserer(52);
        melSite.inserer(53);
        melSite.inserer(54);

        unsigned int mini = 5;
        unsigned int maxi = 10;
        unsigned int nbtuileSansRien = (rand() % (maxi - mini + 1)) + mini;
        for(unsigned int i=0; i< nbtuileSansRien; i++){
            melSite.inserer(0);
        }

        tuile tmp(20,20,true);
        
        //on ajoute la tuile de départ dans le plateau + son graphe correspondant
        tab_tuile.push_back(tmp);
        tab_graph.emplace_back(&tmp, 0);

        //on initialise les couleurs ansi que la case de départ de chaque pion
        for(unsigned int i=0; i< MAX_NB_CASES; i++){
            unsigned objet = tmp.gettabCasePossedeObjet(i);
            if(objet >20 && objet < 24) {
                if(objet == 21){
                    pions.emplace_back(1, tab_graph[0].getNoeud(i) , &tab_graph[0]);
                }
                else if(objet == 22){
                    pions.emplace_back(2, tab_graph[0].getNoeud(i) , &tab_graph[0]);
                }
                else if(objet == 23){
                    pions.emplace_back(3, tab_graph[0].getNoeud(i) , &tab_graph[0]);
                }
                else if(objet == 24){
                    pions.emplace_back(4, tab_graph[0].getNoeud(i) , &tab_graph[0]);
                }
            }
        } 

        for(unsigned int i=0; i< 8; i++){
            tabNoeudSiteDecouvert[i] = nullptr;
        }
    }

    bool plateau::aTouverCaseSiteDecouvert(){
        for(unsigned int i = 0 ; i < 8 ; i++ )
            if(tabNoeudSiteDecouvert[i] == nullptr) return false;
        return true;
    }


    //en théorie la fonction jouer devrait fonctionner 
    //mais pas encore tester
    void plateau::jouer(){    
        while(!gagner()){
            unsigned int i,j;
            for(i = 0; i<nbPion ; i++){
                if(pions[i].chemin.size() == 0){
                //DANS UN PREMIER TEMPS ON REGARDE SUR QUELLE CASE EST LE PION
                    
                    //s'il est sur son objectif on met aTrouverObjectif à vrai
                    unsigned int tmp = pions[i].NoeudPion->getIndex();
                    unsigned int tmp2 = pions[i].GraphPion->getTuileGraph()->gettabCasePossedeObjet( tmp);
                    
                    if( tmp2 == 41 && pions[i].getCp() == CouleurPion::JAUNE){
                        pions[i].aTrouverObjectif = true;
                    }
                    else if( tmp2 == 42 && pions[i].getCp() == CouleurPion::VERT){
                        pions[i].aTrouverObjectif = true;

                    }
                    else if( tmp2 == 43 && pions[i].getCp() == CouleurPion::ORANGE){
                        pions[i].aTrouverObjectif = true;

                    }
                    else if( tmp2 == 44 && pions[i].getCp() == CouleurPion::VIOLET){
                        pions[i].aTrouverObjectif = true;
                    }

                    //s'il est sur sa sortie on supprime le pion du tableau
                    if( tmp2 == 51 && pions[i].getCp() == CouleurPion::JAUNE){
                        pions.erase(pions.begin()+i);
                    }
                    else if( tmp2 == 52 && pions[i].getCp() == CouleurPion::VERT){
                        pions.erase(pions.begin()+i);

                    }
                    else if( tmp2 == 53 && pions[i].getCp() == CouleurPion::ORANGE){
                        pions.erase(pions.begin()+i);

                    }
                    else if( tmp2 == 54 && pions[i].getCp() == CouleurPion::VIOLET){
                        pions.erase(pions.begin()+i);
                    }

                    //s'il est sur une porte on rajoute une tuile
                    //+ on fait la fusion des graphes
                    if( (tmp2 == 30) || (tmp2 == 31 && pions[i].getCp() == CouleurPion::JAUNE) ||
                        (tmp2 == 32 && pions[i].getCp() == CouleurPion::VERT) ||  (tmp2 == 33 && pions[i].getCp() == CouleurPion::ORANGE) ||
                         (tmp2 == 34 && pions[i].getCp() == CouleurPion::VIOLET) ) {
                            
                        unsigned int l = pions[i].getGraphPion()->getTuileGraph()->getLigne();
                        unsigned int c = pions[i].getGraphPion()->getTuileGraph()->getColonne();

                        //on rajoute une tuile en HAUT
                        int obj ;
                        if(tmp == 2){
                            obj = ajouterTuile(2, l , c);
                        }

                        //on rajoute une tuile à GAUCHE
                        if(tmp == 4){
                            obj = ajouterTuile(4, l , c);

                        }

                        //on rajoute une tuile à DROITE
                        if(tmp == 11){
                            obj = ajouterTuile(11, l , c);
                        }

                        //on rajoute une tuile en BAS
                        if(tmp == 13){
                            obj = ajouterTuile(13, l , c);

                        }

                        unsigned int l2 = tab_graph[(tab_graph.size()-1)].getTuileGraph()->getLigne();
                        unsigned int c2 = tab_graph[(tab_graph.size()-1)].getTuileGraph()->getColonne();;

                        pions[i].getGraphPion()->fusionGraph(&tab_graph[(tab_graph.size()-1)],l,c,l2,c2  );
                         tab_graph[(tab_graph.size()-1)].fusionGraph( pions[i].getGraphPion(),l2,c2,l,c);

                        //si l'objet de la tuile qu'on a ajouté est un objectif ou une sortie on le rajoute a tabNoeudSiteDecouvert
                        if(obj != 0){                        
                            Graph* g = &tab_graph[(tab_graph.size()-1)];
                            unsigned int k =0;
                            while( (g->getTuileGraph()->gettabCasePossedeObjet(k) != obj) && k<MAX_NB_CASES ){
                                k++;
                            }
                            Noeud *n = g->getNoeud(i);
                            if(obj == 41) tabNoeudSiteDecouvert[0] = n;
                            else if(obj == 42) tabNoeudSiteDecouvert[1] = n;
                            else if(obj == 43) tabNoeudSiteDecouvert[2] = n;
                            else if(obj == 44) tabNoeudSiteDecouvert[3] = n;
                            else if(obj == 51) tabNoeudSiteDecouvert[4] = n;
                            else if(obj == 52) tabNoeudSiteDecouvert[5] = n;
                            else if(obj == 53) tabNoeudSiteDecouvert[6] = n;
                            else if(obj == 54) tabNoeudSiteDecouvert[7] = n;
                        }
                    }

                }

                //DANS UN SECOND TEMPS ON ESSAIE DE DETERMINER LE CHEMIN QU'IL DOIT PARCOURS LE PION

                    //si il reste des CaseSite à decouvrir, il recherche la porte la plus proche
                    if(!aTouverCaseSiteDecouvert()){
                        pions[i].chemin_porte_plus_proche();
                    }

                    //si il reste des CaseSiteD à  été decouvrir, il recherche son objectif
                    else if( !(pions[i].aTrouverObjectif)){
                        if(pions[i].getCp() == CouleurPion::JAUNE) pions[i].chemin_objectif(tabNoeudSiteDecouvert[0]);
                        else if(pions[i].getCp() == CouleurPion::VERT) pions[i].chemin_objectif(tabNoeudSiteDecouvert[1]);
                        else if(pions[i].getCp() == CouleurPion::ORANGE) pions[i].chemin_objectif(tabNoeudSiteDecouvert[2]);
                        else pions[i].chemin_objectif(tabNoeudSiteDecouvert[3]);
                    }

                    //sinon il recherche sa sortie
                    else{
                        if(pions[i].getCp() == CouleurPion::JAUNE) pions[i].chemin_objectif(tabNoeudSiteDecouvert[4]);
                        else if(pions[i].getCp() == CouleurPion::VERT) pions[i].chemin_objectif(tabNoeudSiteDecouvert[5]);
                        else if(pions[i].getCp() == CouleurPion::ORANGE) pions[i].chemin_objectif(tabNoeudSiteDecouvert[6]);
                        else pions[i].chemin_objectif(tabNoeudSiteDecouvert[7]);
                    }
                }
            
            //ET ENFIN DANS UN TROISIEME TEMPS ON FAIT JOUER LES JOUEURS
                for(i = 0 ; i<nbJoueur ; i++){
                    for(j = 0 ; j<nbPion ; j++){
                        while(joueurs[i].getPeutDeplacerA() == pions[j].chemin[0].second )
                        {
                            pions[j].deplacerPion(pions[j].chemin[0].first, tab_graph);
                            pions[j].chemin.erase(pions[j].chemin.begin());
                        }
                    }
                }
        }
    }
       
    int plateau::ajouterTuile(int CasePorteFranchi, int colonne, int ligne){
        if(melSite.taille() != 0){
            int c , l;
            int objet = melSite.retirer();
            if(CasePorteFranchi == 2){
                tuile tmp( (ligne-1),colonne, false, objet );
                tab_tuile.push_back(tmp);
            }
            else{
                if(CasePorteFranchi == 4){
                    c = colonne - 1;
                    l = ligne;
                }
            else if(CasePorteFranchi == 11){
                c = colonne + 1;
                l = ligne;
            }
            else if(CasePorteFranchi == 13){
                    c = colonne;
                    l = ligne + 1;
            }

            tuile tmp(l , c , false, objet);
                tab_tuile.push_back(tmp );
                tab_tuile[tab_tuile.size()-1].tournerTuile(CasePorteFranchi);                

            }
            
            return objet;
        }
        else return -1;
    }

    bool plateau::gagner(){
        if( nbPion == 0) return true; 
        return false;
    }


}

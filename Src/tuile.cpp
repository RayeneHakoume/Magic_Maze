#include "tuile.hpp"
  
using namespace std;
namespace MMaze {

    tuile::tuile(unsigned int _ligne, unsigned int _colonne, bool _estDepart, unsigned int site) :
        ligne(_ligne),
        colonne (_colonne),
        estDepart(_estDepart)
    {
        //on verifie que si tuile de départ pas de site
        assert( (_estDepart==true && site==0) || (_estDepart==false) );
        assert( site>=0 );

        unsigned int i;
        //dans chaque case on met le site à 0
        for(i = 0 ; i< MAX_NB_CASES ; i++ ){
            tabCasePossedeObjet[i] = 0;
        }
        //dans chaque case on met tout les murs
        for(i = 0 ; i< MAX_NB_MURS ; i++ ){
            tabMurs[i] = true;
        }
        if(estDepart) initialisation_depart() ;
        //on met l'objet qu'on doit rajouter dans une tuile stantard
        else initialisation_stantard(site);
    }

    unsigned int  tuile::getLigne(){
        return ligne;
    }
    unsigned int  tuile::getColonne(){
        return colonne;
    }

    bool tuile::getTabMurs(unsigned int i){
        return tabMurs[i];
    }

    int tuile::gettabCasePossedeObjet(unsigned int i){
        return tabCasePossedeObjet[i];
    }

    void tuile::initialisation_depart() {

        UnionFind uf(MAX_NB_CASES);
        std::vector <int> caseObjImportant;

        //on place les joueurs
        placerPionDepart(uf);

        //on met les joueurs dans objImportant
        caseObjImportant.push_back(5);
        caseObjImportant.push_back(6);
        caseObjImportant.push_back(9);
        caseObjImportant.push_back(10);

        //on place les portes
        placerPorteDepart();
        //on met les portes dans objImportant
        caseObjImportant.push_back(2);
        caseObjImportant.push_back(4);
        caseObjImportant.push_back(11);
        caseObjImportant.push_back(13);

        //dans le melangeur on met tout les numeros des murs
        placerMur(uf, caseObjImportant);

        //on retire aléatoirement un mur jusqu'à qu'on peut accèder à toutes les portes
        placerBoutique();
    }

    void tuile::placerMur(UnionFind &uf, std::vector <int> objImportant){
        //dans le melangeur on met tout les numeros des murs
        Melangeur <int> mel;
        for(unsigned int i = 0 ; i < MAX_NB_MURS ; i++) mel.inserer(i);

        //ensuite on abbat des murs au hasard si les Cases Voisines du mur ne sont pas dans le même ensemble 
        do{
            int indexMur = mel.retirer();
            MMaze::Mur m(indexMur);
            MMaze::Case case1 = m[0];
            MMaze::Case case2 = m[1];

            int indiceCase1 = case1.index();
            int indiceCase2 = case2.index();

            int racine1 = uf.getParentFinal(indiceCase1);
            int racine2 = uf.getParentFinal(indiceCase2);

            if ( ! (uf.estDansUnMemeEnsemble(racine1,racine2)) ){
                tabMurs[indexMur] = false;

                uf.lieeDeuxEnsemble(racine1,racine2);
            }
        }while(!estOk(uf,objImportant));
        mel.vider();
    }
    
//Vérifie si les objets importants sont dans le meme ensemble ou pas

    bool tuile::estOk(UnionFind uf, std::vector <int> objImportant){
        unsigned int taille = objImportant.size();
        for(unsigned int i=1 ; i< taille ; i++){
            if( ! uf.estDansUnMemeEnsemble(objImportant[0], objImportant[i] ) ) {
            return false;
            }
        }
        return true;
    }

    void tuile::placerBoutique(){
        unsigned int j, i=0,nbAcc = 0;
        
        while(i< MAX_NB_CASES){
            //Par case on compte le nombre de mur a côté qui sont abattu (= acces a d'autres cases /nbAcc)
            Case c(i);
            nbAcc = 0 ;
            for(j = 0; j < 4; ++j) {
                try{
                    Case v = c.voisine((Direction) j) ;
                    Mur m(c,v);
                    if(! tabMurs[m.index()] ) nbAcc++;
                } catch (exception &e) {}
           }
           //si nbAcc à 0 ou 1 caseé + pas d'objet sur la case on crée une boutique et on recommance dès le début
           if(tabCasePossedeObjet[i] == 0 && nbAcc  < 2){
                tabCasePossedeObjet[i] = 10;
               for(j = 0; j < 4; ++j) {
                    try{
                        Case v = c.voisine((Direction) j) ;
                        Mur m(c,v);

                        tabMurs[m.index()] = true;
                    } catch (exception &e) {}
                }
                i=0;
           }
           //sinon on passe à la case suivante
           else{
                i++;
           }

        }

        //on enleve les murs entre les boutique
        for(i=0 ; i< MAX_NB_CASES ; i++){
            Case c(i); 
            if(tabCasePossedeObjet[i] == 10) {
                for(j = 0; j < 4; ++j) {
                    try{
                        Case v = c.voisine((Direction) j) ;
                        Mur m(c,v);
                        if( tabCasePossedeObjet[v.index()] == 10) tabMurs[m.index()] = false;
                    } catch (exception &e) {}
                }
            }           
        }

    }

    void tuile::placerPionDepart(UnionFind &uf){
        Melangeur <int> mel;

        int i;
        // DEPART_JAUNE = 21, DEPART_VERTE = 22, DEPART_ORANGE = 23, DEPART_VIOLETTE = 24,
        for(i = 21 ; i< 25 ; i++ ){
            mel.inserer(i);
        }
        //on place aléatoirement sur les cases 5,6,9,10 les pions de départ
        tabCasePossedeObjet[5] = mel.retirer()  ;
        tabCasePossedeObjet[6] = mel.retirer()  ;
        tabCasePossedeObjet[9] = mel.retirer()  ;
        tabCasePossedeObjet[10] = mel.retirer()  ;

        //on retire les murs 6, 7, 18, 19 (les murs du milieu pour le départ)
        tabMurs[5] = false ;
        tabMurs[6] = false ;
        tabMurs[17] = false ;
        tabMurs[18] = false ;
        
        uf.setParent(6,5);
        uf.setParent(9,5);
        uf.setParent(10,5);
        
    }

    void tuile::placerPorteDepart(){
        int i;
        Melangeur <int> mel;
        //PORTE_JAUNE = 31 / PORTE_VERTE = 32 /PORTE_ORANGE = 33, PORTE_VIOLETTE = 34
         for(i = 31 ; i< 35 ; i++ ){
            mel.inserer(i);
        }

        //on place aléatoirement sur les cases 2,4,11,13 les 4 portes
        tabCasePossedeObjet[2] = mel.retirer() ;
        tabCasePossedeObjet[4] = mel.retirer() ;
        tabCasePossedeObjet[11] = mel.retirer() ;
        tabCasePossedeObjet[13] = mel.retirer() ;
    }
 
    void tuile::initialisation_stantard(unsigned int site) {
        assert( (site==0) || (site>39 && site<45) || (site>49 && site<55) );
        UnionFind uf(MAX_NB_CASES);    
        vector <int> objImportant;
        placerSiteStantard(site,objImportant) ;
        placerMur(uf,objImportant);
        placerBoutique();
    }

    void tuile::placerSiteStantard(unsigned int site, std::vector <int> &objImportant) {

    //DANS UN PREMIR TEMPS ON PLACE LES PORTES 
        int i;
        //on determine le nombre aléatoire de porte
        int mini = 1;
        int maxi = 3;
        int nbPorte = (rand() % (maxi - mini + 1)) + mini;

        Melangeur <int> melCouleurPorte ;
        Melangeur <int> melPlace ;
        
        //Par convention la case 13 possède toujours une porte classique
        //(où tout le monde peut passer (PORTE = 30))
        tabCasePossedeObjet[13] = 30;
        objImportant.push_back(13);

        //on mélange les cases 2,4,11 pour apres y placer les portes de couleur aléatoire
        melPlace.inserer(2);
        melPlace.inserer(4);
        melPlace.inserer(11);

        //on mélange les portes
        //PORTE_JAUNE = 31, PORTE_VERTE = 32, PORTE_ORANGE = 33, PORTE_VIOLETTE = 34,
        for(i = 31 ; i< 35 ; i++ ){
            melCouleurPorte.inserer(i);
        }

        //on place aléatoirement les places + les couleurs
        for(i = 0 ; i < nbPorte ; i++){
            int place = melPlace.retirer();
            tabCasePossedeObjet[place] =  melCouleurPorte.retirer();
            objImportant.push_back(place);
        }
        //on retire du mélangeur ce qui n'ont pas pu être placé
        melPlace.vider();
        melCouleurPorte.vider();

    //DANS UN SECOND TEMPS ON PLACE SOIT LA SORTIE / SOIT L'OBJECTIF
        mini = 0;
        maxi = 15;
        int tmp;
        //si on place l'objectif OBJECTIF = 40, OBJECTIF_JAUNE = 41,
        //OBJECTIF_VERT = 42, OBJECTIF_ORANGE = 43, OBJECTIF_VIOLET = 44,
        if( site>39 && site<45 ){
            do{
                //srand((unsigned int)time(NULL));
                tmp = (rand() % (maxi - mini + 1)) + mini;
            } while (tabCasePossedeObjet[tmp] != 0) ;
            tabCasePossedeObjet[tmp] = site;
            objImportant.push_back(tmp);
        }
        //si on place la sortie SORTIE = 40, SORTIE_JAUNE = 41,
        //SORTIE_VERT = 42, SORTIE_ORANGE = 43, SORTIE_VIOLET = 44,
        else if (site>49 && site<55){
            Melangeur <int> numCase;
            for(i = 0 ; i < 5 ; i++) numCase.inserer(i);
            for(i = 12 ; i < 16 ; i++) numCase.inserer(i);
            numCase.inserer(4);
            numCase.inserer(7);
            numCase.inserer(8);
            numCase.inserer(11);
            do{
                tmp = numCase.retirer();
            } while (tabCasePossedeObjet[tmp] != 0) ;
            tabCasePossedeObjet[tmp]=site;
            objImportant.push_back(tmp);
            numCase.vider();
        }
    }

    void tuile::tournerTuile(unsigned int CasePorte){
        assert(CasePorte<15);
        unsigned int rotation, i;
        unsigned int tabObjetTmp[MAX_NB_CASES];
        unsigned int tabMurTmp[MAX_NB_MURS];

        if(CasePorte == 11) rotation = 3;
        if(CasePorte == 13) rotation = 2;
        if(CasePorte == 4) rotation = 1;

        //cases
        for(i = 0 ; i < MAX_NB_CASES ; i++){
            Case caseI(i);
            Case caseRot(caseI.tourne(rotation));

            tabObjetTmp[caseRot.index()] = tabCasePossedeObjet[i];
        }
        
        for(i = 0 ; i < MAX_NB_CASES ; i++){
            tabCasePossedeObjet[i] = tabObjetTmp[i] ;
        }

        //murs
        for(i = 0 ; i < MAX_NB_MURS ; i++){
            Mur murI(i);
            Mur murRot(murI.tourne(rotation));

            tabMurTmp[murRot.index()] = tabMurs[i];
        }
        
        for(i = 0 ; i < MAX_NB_MURS ; i++){
            tabMurs[i] = tabMurTmp[i] ;
        }

      }

}

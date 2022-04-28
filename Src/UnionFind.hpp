#ifndef LIFAP6_UNION_FIND_HPP_
#define LIFAP6_UNION_FIND_HPP_

#include <vector>

class UnionFind{

    public :
    UnionFind(int _nombre);
    int getParent(int i);
    void setParent(int i,int valeur);
    int getParentFinal(int i);

    //bool estParentde(int i, int nb);
    void rajouterUnParent(int valeur);
    bool estDansUnMemeEnsemble(int nb1, int nb2);
    void lieeDeuxEnsemble(int nb1, int nb2);
    void afficher();


    private :
    int nombre;
    std::vector <int> parent;
};

#endif
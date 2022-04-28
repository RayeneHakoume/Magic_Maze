#include "UnionFind.hpp"
#include <iostream>
using namespace std;

UnionFind::UnionFind(int _nombre){
    nombre = _nombre;
    for(int i=0;i<nombre;i++){
        parent.push_back(i);
    }
}
int UnionFind::getParent(int i){
    return parent[i];
}

int UnionFind::getParentFinal(int i){
    
    int parent1 = getParent(i);
    while(getParent(parent1) !=  parent1){
        parent1= getParent(parent1);
    }
    return parent1;
}

void UnionFind::setParent(int i,int valeur){
    parent[i] = valeur;
}

bool UnionFind::estDansUnMemeEnsemble(int nb1, int nb2){
    

    int parent1 = getParentFinal(nb1);
    int parent2 = getParentFinal(nb2);

    return (parent1 == parent2) ;
}

void UnionFind::lieeDeuxEnsemble(int nb1, int nb2){

    int parentFinal1 = getParentFinal(nb1);
    int parentFinal2 = getParentFinal(nb2);

    setParent(parentFinal1, parentFinal2);
}

void UnionFind::afficher(){
    cout<<"[ ";
    for(int i=0;i< nombre;i++){
        cout<<parent[i]<<" ";
    }
    cout<<"] \n";
}

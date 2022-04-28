#include <map>
#include <iostream>
#include <vector>

struct Noeud {
  Noeud(int a) : i(a) {} ;
  int i ;
} ;

int main() {

  std::vector<Noeud*> tab ;
  for(int i = 0; i < 20; ++i) {
    tab.push_back(new Noeud(i)) ;
  }
  
  //associe un entier a un Noeud*
  std::map<Noeud*, int> m ;

  for(int i = 0; i < 20; ++i) {
    m[tab[i]] = 100 + i ;
  }

  for(int i = 0; i < 20; ++i) {
    std::cout << m[tab[i]] << std::endl ;
  }

  if(m.find(nullptr) == m.end()) {
    std::cout << "pas la" << std::endl ;
  } else {
    std::cout << "la" << std::endl ;
  }

  if(m.find(tab[12]) == m.end()) {
    std::cout << "pas la" << std::endl ;
  } else {
    std::cout << "la" << std::endl ;
  }
  
  return 0 ;
}

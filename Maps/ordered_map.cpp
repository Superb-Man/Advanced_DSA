#include"ordered_map.h"


int main() {
    ordered_map<std::string, int> h;
    RBT<std::string,int> rbt ;
    RBT<int,int> rbt2 ;
    
    for(int i = 0 ; i < 20 ; i++) {
        h.insert("abc"+to_string(i),i) ;
        rbt.insert("abc"+to_string(i),i) ;
        rbt2.insert(i,i) ;
    }
    std::cout  << "Order of the key " << rbt2.get_order(5) << '\n' ;

    h.insert("abc0",76) ;

    std::cout << h["abc1"] <<'\n' ;
    ++h["abc1"] ;
    std::cout << h.get("abc1") <<'\n' ;
    --h["abc1"] ;
    

    std::cout << h.get("abc1") <<'\n' ;
    h.remove("abc") ;

    h.remove("hsfj") ;


    std::cout << (h.search("abc0") ? "Found" : "Not Found") << '\n' ;
    h.print();

    h.clear() ;
    h.clear() ;
}
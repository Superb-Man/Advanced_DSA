#include "hash.h"

int main() {
    HashMap<std::string, int> h;
    // RBT<std::string,int> rbt ;

    for(int i = 0 ; i < 20 ; i++) {
        h.insert("abc"+to_string(i),i) ;
        // rbt.insert("abc"+to_string(i),i) ;
    }
    // rbt.print() ;

    std::cout << h["abc1"] <<'\n' ;
    ++h["abc1"] ;
    std::cout << h.get("abc1") <<'\n' ;
    --h["abc1"] ;
    
    // h.remove("adczxc") ;

    std::cout << h.get("abc1") <<'\n' ;
    h.remove("abc1") ;

    h.remove("hsfj") ;
    h.print() ;

    std::cout << (h.search("abc0") ? "Found" : "Not Found") << '\n' ;
    h.clear() ;
    h.clear() ;



}
#include "hash.h"

int main() {
    HashMap<std::string, int> h;

    for(int i = 0 ; i < 20 ; i++) {
        h.insert("abc"+to_string(i),i) ;
    }

    std::cout << h["abc1"] <<'\n' ;
    ++h["abc1"] ;
    std::cout << h.get("abc1") <<'\n' ;
    --h["abc1"] ;
    
    // h.remove("adczxc") ;

    std::cout << h.get("abc1") <<'\n' ;
    h.remove("abc") ;

    h.remove("hsfj") ;
    // h.print() ;

    std::cout << (h.search("abc1") ? "Found" : "Not Found") << '\n' ;
    h.clear() ;
    h.clear() ;



}
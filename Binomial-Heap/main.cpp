#include"binomialHeap.h"
#include<random>

int main() {
    long long int n ;
    // std::cin >> n ;
    binomialHeap bh, bh2 ;
    long long int arr[6] ;
    for(long long int i = 0 ; i < 6 ; i++) {
        arr[i] = (rand()+100) % 100 ;
        std::cout << arr[i] << " " ;
    }
    std::cout << std::endl ;
    for(long long int i = 0 ; i < 6 ; i++) {
        bh.insert(arr[i]) ;    
    }

    long long int m ;
    // std::cin >> m ;
    // bh.decrease(m,2) ;
    // bh.print() ;
    bh.decrease(arr[3],arr[3]-10) ;

    bh.remove(arr[0]) ;



    for(long long int i = 0 ; i < 5 ; i++) {
        std::cout << bh.removeMin() << " " ;    
    }
}


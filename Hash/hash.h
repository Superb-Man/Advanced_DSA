#include<iostream>
#include<math.h>
#include<cstring>
#include<sstream>
#include "RBT.h"

typedef long long int ll ;
const ll MIN = -1e18 ;

ll hashValue(std:: string s) {
    const ll p = 31;
    const ll m = 1e9 + 9;
    ll hash_value = 0;
    ll p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow + m) % m;
        p_pow = (p_pow * p + m) % m;
    }

    return hash_value;
}

ll hashValue2(std :: string s){
    ll hash=5381 ;
    for( ll i = 0; i < s.size() ; i++){
        hash = ((hash<<5)+hash) + s[i] ;
    }
    return hash ;
}


template <typename T>
std::string to_string(const T& obj) {
    std::ostringstream oss;
    oss << obj;
    return oss.str();
}

// Specialization for types that do not have a direct stream insertion operator (<<) defined
template <>
std::string to_string(const std::string& obj) {
    return obj;
}


template<typename T,typename K>
class HashMap{
    
    RBT<T,K> *__hashTable ;
    ll n ;
public:
    HashMap(ll n = 10) {
        this->n  = n ;
        __hashTable = new RBT<T,K>[n] ;
        for(ll i = 0 ; i < n ; i++) __hashTable[i] = RBT<T,K>() ;
    }

    void insert(T key, K value) {
        ll hash = (hashValue(to_string(key)) + n)  % n ;
        std::cout << "Hash Value : " << hash << std::endl ;
        if(__hashTable[hash].find(key)) {
            __hashTable[hash].remove(key) ;
        }
        __hashTable[hash].insert(key,value) ;
    }

    void remove(T key) {
        ll hash = (hashValue(to_string(key)) + n)  % n ;
        __hashTable[hash].remove(key) ;
    }

    bool search(T key) {
        // return ((searchNode(s) != nullptr) ? true : false) ;
        ll hash = (hashValue(to_string(key)) + n)  % n ;
        return __hashTable[hash].find(key) ;
    }

    void clear(){
        for(ll i = 0 ; i < n ; i++) {
            __hashTable[i].clear() ;
        }
    }
    K& get(T key) {
        ll hash = (hashValue(to_string(key)) + n)  % n ;
        return __hashTable[hash].find_helper(key)->value ;
    }

    // i want to use [T]++ , [T]-- , overload
    K& operator [](T key) {
        return get(key) ;
    }  

    void print() {
        for(ll i = 0 ; i < n ; i++) {
            std::cout << "Bucket " << i << '\n' ;
            __hashTable[i].print(__hashTable[i].getRoot()) ;
            std::cout << std::endl ;
        }
    }

    template<typename U = K>
    typename std::enable_if<std::is_arithmetic<U>::value, void>::type
    operator++(T key) {
        insert(key, get(key) + 1);
    }

    template<typename U = K>
    typename std::enable_if<std::is_arithmetic<U>::value, void>::type
    operator--(T key) {
        insert(key, get(key) - 1);
    }
    RBT<T,K> begin() {
        return __hashTable[0] ;
    }
    RBT<T,K> end() {
        return __hashTable[n-1] ;
    } 




    ~HashMap() {
        //check if already clear called
        clear() ;
        std::cout << "Destructor called" << std::endl ;

        // delete [] __hashTable ;
    }

};
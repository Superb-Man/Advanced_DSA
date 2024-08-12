#include<iostream>
#include<math.h>
#include<cstring>
#include<sstream>
#include "RBT.h"
#include "map.h"

typedef long long int ll ;


template<typename T,typename K>
class ordered_map :public Map<T,K> {
    RBT<T,K>  tree ;

public:

    ordered_map() {
        //
    }

    void insert(T key, K value) {
        node<T,K>* temp = tree.find(key) ;
        if(temp) {
            temp->value = value ;
        } else {
            tree.insert(key,value) ;
        }

    }

    void remove(T key) {
        tree.remove(key) ;
    }

    bool search(T key) {
        return tree.find(key) ? true : false ;
    }

    void clear() {
        tree.clear() ;
    }

    K& get(T key) {
        return tree.find(key)->value ;
    }

    void print() {
        tree.print() ;
    }

    K& operator [](T key) {
        return get(key) ;
    }



    template<typename U = K>    
    typename std::enable_if<std::is_arithmetic<U>::value, void>::type
    operator++(T key) {
        //1 to update value
        node<T,K>* temp = tree.find(key) ;
        if(temp) {
            temp->value++ ;
        }
    }

    template<typename U = K>
    typename std::enable_if<std::is_arithmetic<U>::value, void>::type
    operator--(T key) {
        //1 to update value
        node<T,K>* temp = tree.find(key) ;
        if(temp) {
            temp->value-- ;
        }
    }

    //begin and end iterators
    typename node<T,K>::iterator begin() {
        return tree.begini() ;
    }

    typename node<T,K>::iterator end() {
        return tree.endi() ;
    }

    int get_order(T key) {
        return tree.get_order(key) ;
    }

    ~ordered_map() {
        tree.clear() ;
    }
} ;



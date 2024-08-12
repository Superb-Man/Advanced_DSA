#ifndef Map_h
#define Map_h

template<typename T,typename K>
class Map{

public:
    virtual void insert(T key, K value) = 0 ;
    virtual void remove(T key) = 0 ;
    virtual bool search(T key) = 0 ;
    virtual void clear() = 0 ;
    virtual K& get(T key) = 0 ;
    virtual void print() = 0 ;
    virtual K& operator [](T key) = 0 ;
    
    template<typename U = K>    
    typename std::enable_if<std::is_arithmetic<U>::value, void>::type
    operator++(T key) {

    }

    template<typename U = K>
    typename std::enable_if<std::is_arithmetic<U>::value, void>::type
    operator--(T key) {
        
    }

    virtual ~Map() {}
} ;

#endif
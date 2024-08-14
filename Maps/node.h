#include<stack>
#define RIGHT 1
#define LEFT 0

template <typename T,typename K>
struct node {
    node<T,K>* left ;
    node<T,K>* right ;
    node<T,K>* parent ;
    T key ;
    K value ;
    int color ;
    int nodes_count ; // number of nodes in the subtree rooted at this node

    node() {
        left = right = parent = NULL ;
    }
    node(T key,K value) {
        this->key = key ;
        this->value = value ;
        left = right = parent = NULL ;
        nodes_count = 0 ;
    }

    struct iterator {

        std::stack<node<T,K>*> st ;
        node* curr =nullptr ;

        iterator(node<T,K>* root) {
            if(root == NULL) return ;
            curr = root ;
            st.push(curr) ;
        }

        bool operator!=(const iterator& it) const{
            return curr != it.curr ;
        }

        node& operator*() {
            return *curr ;
        }

        iterator& operator++(int) {
            // will implement later
        }

        node* operator->() {
            return curr ;
        }


    };



} ;
#include<iostream>
#include<vector>
#include<cstring>

using namespace std ;
template <typename T,typename K>
struct node {
    node<T,K>* left ;
    node<T,K>* right ;
    node<T,K>* parent ;
    T key ;
    K value ;
    int color ;
    int nodes_count ;

    node() {
        left = right = parent = NULL ;
        nodes_count = 0 ;
    }
    node(T key,K value) {
        this->key = key ;
        this->value = value ;
        left = right = parent = NULL ;
        nodes_count = 0 ;
    }

} ;

template <typename T,typename K>
class RBT{
    node<T,K>* root ;
    node<T,K>* NIL ;

    //Slide + Cormen

    int color(node<T,K>* x) {
        if(x == NULL || x == NIL) return 0 ;
        else return x->color ;
    }

    void left_rotate(node<T,K>* x) {
        node<T,K>* y = x->right ;
        x->right = y->left ;
        if(y->left != NIL)  y->left->parent = x ;
        y->parent = x->parent ;
        if(x->parent == NIL)
            root = y ;
        else if(x == x->parent->left)
            x->parent->left = y ;
        else x->parent->right = y ;
        int yleft = y->left->nodes_count ;
        y->left = x ;
        x->parent = y ;
        int cnt  = x->nodes_count ;
        x->nodes_count = x->nodes_count - y->nodes_count + yleft  ;
        y->nodes_count = cnt ;
    }

    void right_rotate(node<T,K>* x) {
        node<T,K>* y = x->left ;
        x->left = y->right ;
        if(y->right != NIL) y->right->parent = x ;
        y->parent = x->parent ;
        if(x->parent == NIL)
            root = y ;
        else if(x == x->parent->right)
            x->parent->right = y ;
        else x->parent->left = y ;
        int yright = y->right->nodes_count ;
        y->right = x ;
        x->parent = y ;
        int cnt  = x->nodes_count ;
        x->nodes_count = x->nodes_count - y->nodes_count + yright  ;
        y->nodes_count = cnt ;
    }

    void insert_Fix_Up (node<T,K>* z) {
        while(color(z->parent)) {
            if(z->parent == z->parent->parent->left) {
                node<T,K>* y = z->parent->parent->right ; //y is the uncle
                if(color(y)) {
                    z->parent->color = 0 ;
                    y->color = 0 ;
                    z->parent->parent->color = 1 ;
                    z = z->parent->parent ;
                }
                else {
                    if(z == z->parent->right) {
                        z = z->parent ;
                        left_rotate(z) ;
                    }
                    z->parent->color = 0 ;
                    z->parent->parent->color = 1 ;
                    right_rotate(z->parent->parent) ;
                }
            }
            else{
                node<T,K>* y = z->parent->parent->left ; //y is the uncle
                if(color(y)) {
                    z->parent->color = 0 ;
                    y->color = 0 ;
                    if(y == NIL) {}
                    z->parent->parent->color = 1 ;
                    z = z->parent->parent ;
                }
                else {
                    if(z == z->parent->left) {
                        z = z->parent ;
                        right_rotate(z) ;
                    }
                    z->parent->color = 0 ;
                    z->parent->parent->color = 1 ;
                    left_rotate(z->parent->parent) ;
                }

            }
            if(z == root) break ;
        }

        root->color = 0 ;
        root->parent = NIL ;

    }

    node<T,K>* insert_helper(T key,K value) {
        node<T,K>* y = NIL ;
        node<T,K>* x = root ;
        if(find(key) == true) return NULL ;
        node<T,K>* z = new node<T,K>(key,value) ;
        z->right = z->left = NIL ;
        while(x != NIL) {
            y = x ;
            x->nodes_count++ ;
            if(z->key < x->key) {
                x = x->left ;
            }
            else if (z->key > x->key) {
                x = x->right ;
            }
        }
        //cout <<"Insert successful"<<endl;

        z->parent = y ;
        z->nodes_count = 1 ;
        if (y == NIL) {
            root = z ;
        }
        else if(z->key < y->key) {
            y->left = z ;
        }
        else y->right = z ;
        z->color = 1 ;
        insert_Fix_Up(z) ;

        return z ;
    }

    node<T,K>* getMin(node<T,K>* x , int param = 0) {
        x = x->right ;
        while(x->left != NIL) {
            x = x->left ;
        }

        return x ;
    }

    bool delete_helper(T key) {
        node<T,K>* z = find_helper(key) ;
        node<T,K>* y = z ;
        node<T,K>* x = NIL ;
        if(z == NULL) {
            //cout <<"No elements \n" ;
            return false ;
        }
        if(z->left == NIL || z->right == NIL){
            y = z ;
            node<T,K>* t = y ;
            while(t!=NIL) {
                t = t->parent ;
                if(t != NIL) t->nodes_count-- ;
            }
            //cout <<"HERE" <<y->key<<endl;
        }
        else{
            y = getMin(z) ;
            node<T,K>* t = y ;
            while(t!=NIL) {
                t = t->parent ;
                if(t != NIL) t->nodes_count-- ;
            }
        }

        if(y->left != NIL)   x = y->left ;
        else  x = y->right ;

        x->parent = y->parent ;
        if(y->parent == NIL) root = x ;

        else if( y == y->parent->left)
            y->parent->left = x ;
        else
            y->parent->right = x ;

        swap(y->key,z->key) ;
        swap(y->value,z->value) ;
        if(color(y) == 0) delete_Fix_Up(x) ;

        delete y ;

        return true ;


    }

    void delete_Fix_Up(node<T,K>* x) {
        while (!color(x) && root != x) {
            if(x == x->parent->left) {
                node<T,K>* w = x->parent->right ;
                if(color(w)) {
                    w->color = 0 ;
                    x->parent->color = 1 ;
                    left_rotate(x->parent) ;
                    w = x->parent->right ;
                }
                if(color(w->left) == 0 && color(w->right) == 0) {
                    w->color = 1 ;
                    x = x->parent ;
                }

                else {
                    if(color(w->right) == 0) {
                        w->left->color = 0 ;
                        w->color = 1 ;
                        right_rotate(w) ;
                        w = x->parent ;
                    }
                    w->color = x->parent->color ;
                    x->parent->color = 0 ;
                    w->right->color = 0 ;
                    left_rotate(x->parent) ;
                    x = root ;
                }
            }
            else {
                node<T,K>* w = x->parent->left ;
                if(color(w)) {
                    w->color = 0 ;
                    x->parent->color = 1 ;
                    right_rotate(x->parent) ;
                    w = x->parent->left ;
                }
                if(color(w->right) == 0 && color(w->left) == 0) {
                    w->color = 1 ;
                    x = x->parent ;
                }

                else {
                    if(color(w->left) == 0) {
                        w->right->color = 0 ;
                        w->color = 1 ;
                        left_rotate(w) ;
                        w = x->parent ;
                    }
                    w->color = x->parent->color ;
                    x->parent->color = 0 ;
                    w->left->color = 0 ;
                    right_rotate(x->parent) ;
                    x = root ;
                }

            }
        }
        x->color  = 0 ;

    }
    void removeSubTree(node<T,K>* _root){
        if(_root == NIL ) return ;
        removeSubTree(_root->left) ;
        removeSubTree(_root->right) ;

        //deleting nodes
        delete _root ;
    }


public :
    RBT() {
        NIL = new node<T,K> ;
        NIL->parent = NIL->left = NIL->right = NULL ;
        NIL->color = 0 ;
        root = NIL ;
    }

    bool insert(T key,K value) {
        node<T,K>* nod = insert_helper(key,value) ;
        if(nod != NULL) return true ;
        else return false ;
    }
    bool remove(T key) {
        return delete_helper(key) ;
    }
    void inorder(node<T,K>* temp,vector<T,K>& vec) {
        if(temp != NIL){
            inorder(temp->left , vec);
            vec.push_back(temp->key) ;
        //cout << "--> " << temp->key << "<" << temp->color << ">";
            inorder(temp->right, vec);
        }
    }
    void preorder(node<T,K>* temp) {
        if(temp == NIL){ return; }
        cout << "--> " << temp->key << "<" << temp->color << ">";
        preorder(temp->left);
        preorder(temp->right);
    }
    
    node<T,K>* find_helper(T key) {
        node<T,K>* temp = root ;
        while (true)
        {
            if (temp == NIL) return NULL ;
            if(key < temp->key)   temp = temp->left ;
            else if(key > temp->key)  temp = temp->right ;
            else return temp ;
        }

    }
    bool find(T key) {
        return (find_helper(key) != NULL ? true : false) ;
    }

    int less(T key){
        node<T,K>* temp = root ;
        int cnt = 0 ;
        //int xx = 0 ;
        NIL->nodes_count = 0 ;
        while(temp != NIL) {
            if(key > temp->key){
                cnt+=temp->left->nodes_count + 1  ;
                temp = temp->right ;
            }
            else if(key <= temp->key) {
                temp = temp->left ;
            }
        }

        return cnt  ;
    }

    void preorder() {preorder(root) ;}

    int inorder(T key){
        vector<T>vec ;
        inorder(root,vec) ;
        int cnt  = 0 ;
        for(int i = 0 ; i < vec.size() ; i++) {
            if(key > vec[i]) cnt++ ;
        }

        return cnt ;
    }

    //getroot
    node<T,K>* getRoot() {
        return root ;
    }

    void clear() {
        removeSubTree(root) ;
        root = NIL ;
    }

    void print(node<T,K>* temp,std::string space="",std::string type ="root") {
        if(temp == NIL) return ;
        std::cout << space << temp->key << "," << temp->value << " {" << type << "}" <<std::endl ;
        space+=" " ;
        print(temp->left,space,"left") ;
        print(temp->right,space,"right") ;
    }

    ~RBT() {
        removeSubTree(root) ;
        delete NIL ;
    }
} ;
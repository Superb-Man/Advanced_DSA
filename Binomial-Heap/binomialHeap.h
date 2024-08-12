// implementation of binomial heap
#include<iostream>
#include<math.h>
#include<cstring>
#include<sstream>

#define MAX 1e18 
#define MIN -1e18 

struct binomialHeapNode {
    long long int key ;
    long long int degree ;
    binomialHeapNode *child ;
    binomialHeapNode *sibling ;
    binomialHeapNode *parent ;

    binomialHeapNode(long long int key) {
        this->key = key ;
        degree = 0 ;
        child = sibling = parent = nullptr ;
    }
} ;

class binomialHeap {
    binomialHeapNode *head ;
    long long int size ;

    binomialHeapNode* mergeTrees(binomialHeapNode* h1, binomialHeapNode* h2) {
        // Initialize the head of the merged tree list
        binomialHeapNode* head = nullptr;
        binomialHeapNode* temp = nullptr;

        if (!h1) return h2;
        if (!h2) return h1;

        if (h1->degree <= h2->degree) { // h1 has smaller degree
            head = h1;
            h1 = h1->sibling;
        } 
        else { // h2 has smaller degree
            head = h2;
            h2 = h2->sibling;
        }

        temp = head;

        // Merge the remaining nodes
        while (h1 && h2) { 
            if (h1->degree <= h2->degree) {
                temp->sibling = h1;
                h1 = h1->sibling;
            } else {
                temp->sibling = h2;
                h2 = h2->sibling;
            }
            temp = temp->sibling;
        }

        if (h1) {
            temp->sibling = h1;
        } 
        else if (h2) {
            temp->sibling = h2;
        }

        return head;
    }


    /**
     * @brief Link two binomial trees
     * BINOMIAL-LINK (y, z)
     * p[y] ← z
     * sibling[y] ← child[z]
     * child[z] ← y
     * degree[z] ← degree[z] + 1
     * @param h1 
     * @param h2 
     */

    void makeLink(binomialHeapNode* h1,binomialHeapNode* h2) {
        h1->parent = h2 ; //p[y] <- z
        h1->sibling = h2->child ; //sibling[y] <- child[z]
        h2->child = h1 ; //child[z] <- y
        h2->degree++ ; //degree[z] <- degree[z] + 1
    }

    /**
     * @brief Union two binomial heaps
     *  H <- MAKE-BINOMIAL-HEAP()
     * head[H] <- B INOMIAL-HEAP-MERGE (head[H1], head[H2] )
     * x <- NIL
     * y <- head[H]
     * z <- y->sibling
     * while z != NIL
     * do if degree[y] != degree[z] or (z->sibling != NIL and z->sibling->degree == degree[y])
     * then x <- y
     * y <- z
     * else if key[y] <= key[z]
     * then sibling[y] <- sibling[z]
     * B INOMIAL-LINK (z, y)
     * else if x = NIL
     * then head[H] <- z
     * else sibling[x] <- z
     * BINOMIAL-LINK (y, z)
     * y <- z
     * z <- sibling[z]
     * if x = NIL
     * then head[H] <- y
     * else sibling[x] <- y
     * return H
     * @param h1 
     * @param h2 
     * @return binomialHeapNode* 
     */
 

    binomialHeapNode* unionHeap(binomialHeapNode *h1,binomialHeapNode *h2) {

        binomialHeapNode* head = mergeTrees(h1,h2) ; //H -> Bionomial-Heap-Merge(H1 U H2)

        if(head == nullptr) return head ; //if head[H] = NIL then return H

        binomialHeapNode *prev = nullptr ; // prev-x <- NIL
        binomialHeapNode *curr = head ; // x <- head[H]
        binomialHeapNode *next = curr->sibling ; // next-x <- sibling[x]


        while(next != nullptr) { //while next-x != NIL
            if(curr->degree != next->degree || (next->sibling != nullptr && next->sibling->degree == curr->degree)) { 
                prev = curr ; //prev-x <- x
                curr = next ; //x <- next-x
            } 
            else {  //
                if(curr->key <= next->key) {
                    curr->sibling = next->sibling ; //sibling[x] <- sibling[next-x]
                    makeLink(next,curr) ; //Binomial-Link(next-x,x)
                } else {
                    if(prev == nullptr) 
                        head = next ; //head[H] <- next-x
                    else 
                        prev->sibling = next ; //sibling[prev-x] <- next-x

                    makeLink(curr,next) ;
                    curr = next ; //x <- next-x
                }
            }
            next = curr->sibling ; //next-x <- sibling[x]
        }
        return head ;
    }


    binomialHeapNode* findMin() {
        binomialHeapNode *minNode = nullptr ;
        binomialHeapNode *curr = head ;
        long long int minVal = MAX ;
        while(curr != nullptr) {
            if(curr->key < minVal) {
                minVal = curr->key ;
                minNode = curr ;
            }
            curr = curr->sibling ;
        }
        return minNode ;
    }


    /**
     * @brief Remove the node with minimum key from the binomial heap
     * BINOMIAL-HEAP-EXTRACT-MIN (H )
     * find the root x with the minimum key in the root list of H ,
     * and remove x from the root list of H
     * H ← MAKE-BINOMIAL-HEAP ()
     * reverse the order of the linked list of x’s children,
     * and set head[H'] to polong long int to the head of the resulting list
     * H ← B INOMIAL-HEAP-UNION (H, H' )
     * return x
     * @return binomialHeapNode* 
     */

    binomialHeapNode* removeMinNode() {
        //finding the root x with the minimum key in the root list of H
        binomialHeapNode *prevX ;
        binomialHeapNode *minNode = nullptr ;
        binomialHeapNode *curr = head ;
        binomialHeapNode *prev = nullptr ;

        long long int minVal = MAX ;
        while(curr != nullptr) {
            if(curr->key < minVal) {
                minVal = curr->key ;
                minNode = curr ;
                prevX = prev ;
            }
            prev = curr ;
            curr = curr->sibling ;
        } 

        if(minNode == nullptr) return nullptr ;

        //removing x from the root list of H
        if(prevX == nullptr) head = minNode->sibling ;
        else prevX->sibling = minNode->sibling ;

        //reverse the order of the linked list of x's children
        binomialHeapNode *child = minNode->child ;
        binomialHeapNode *childPrev = nullptr ;
        binomialHeapNode *childNext = nullptr ;
        while(child != nullptr) {
            childNext = child->sibling ;
            child->sibling = childPrev ;
            child->parent = nullptr ;
            childPrev = child ;
            child = childNext ;
        }

        //set head[H'] to point to the head of the resulting list

        head = unionHeap(head,childPrev) ;
        return minNode ;

    }
    

    void print(binomialHeapNode *head) {
        binomialHeapNode *curr = head ;
        std::cout << "Binomial Heap: " ;
        while(curr != nullptr) {
            std::cout << curr->key << " " ;
            print(curr->child) ;
            curr = curr->sibling ;
        }
    }

public:
    binomialHeap() {
        head = nullptr ;
        size = 0 ;
    }

    binomialHeap(const binomialHeap &bh) {
        head = bh.head ;
        size = bh.size ;
    }

    void insert(long long int key) {
        binomialHeapNode *node = new binomialHeapNode(key) ;
        head = unionHeap(head,node) ;
        size++ ;
    }

    /**
     * @brief Decrease the key of a node in the binomial heap
     * BINOMIAL-HEAP-DECREASE-KEY (H, x, k)
     * if k > key[x]
     * then error “new key is greater than current key”
     * key[x] <- k
     * y <- x
     * z <- p[y]
     * while z != NIL and key[y] < key[z]
     * do exchange key[y] <-> key[z]
     * If y and z have satellite fields, exchange them, too.
     * y <- z
     * z <- p[y]
     * @param oldVal 
     * @param newVal 
     */

    void decrease(long long int oldVal,long long int newVal) {
        binomialHeapNode *curr = head ;
        while(curr != nullptr) {

            //decreaseKey operation
            if(curr->key == oldVal) { //finding the node with oldVal
                curr->key = newVal ; //key[x] <- k
                binomialHeapNode *parent = curr->parent ;
                while(parent != nullptr && curr->key < parent->key) { //while z != NIL and key[y] < key[z]
                    std::swap(curr->key,parent->key) ; //exchange key[y] <-> key[z]
                    curr = parent ; //y <- z
                    parent = curr->parent ; //z <- p[y]
                }
                break ;
            }
            curr = curr->sibling ;
        }
    }


    void remove(long long int key) {
        decrease(key,MIN) ;
        removeMin() ;
        
    }

    long long int removeMin() {
        binomialHeapNode *minNode = removeMinNode() ;
        if(minNode == nullptr) return MIN ;
        size-- ;
        long long int minVal = minNode->key ;
        // delete minNode ;
        return minVal ;
    }

    long long int getMin() {
        binomialHeapNode *minNode = findMin() ;
        return minNode->key ;
    }

    void print() {
        print(head) ;
    }

    long long int getSize() {
        return size ;
    }

    void clear() {
        if(head == nullptr) return ;
        binomialHeapNode *curr = head ;
        binomialHeapNode *next = nullptr ;
        while(curr != nullptr) {
            next = curr->sibling ;
            delete curr ;
            curr = next ;
        }
        head = nullptr ;
        size = 0 ;
    }

    ~binomialHeap() {
        clear() ;
    }

};


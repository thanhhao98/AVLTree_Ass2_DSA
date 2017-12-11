#include <iostream>
using namespace std;

template <class T>
struct AVLNode{
    T data;
    AVLNode<T> *_pLeft, *_pRight;
    int status;
    AVLNode<T>(T &a) : data(a), _pLeft(NULL), _pRight(NULL), status(0){}
};

template <class T>
class AVLTree{
private:
    AVLNode<T> *_pRoot;
public:
    AVLTree<T>(): _pRoot(NULL){};
    AVLTree<T>(T &a);
    ~AVLTree<T>(){destroy(_pRoot);}
    AVLNode<T>* getRoot();
    bool insert(T &a){return insert(this->_pRoot, a); }
    bool remove(T &a){return remove(this->_pRoot, a); }
protected:
    bool insert(AVLNode<T>* &pR, T &a);
    bool remove(AVLNode<T>* &pR, T &a);
    void rotLeft(AVLNode<T>* &pR);
    void rotRight(AVLNode<T>* &pR);
    void rotLR(AVLNode<T>* &pR);
    void rotRL(AVLNode<T>* &pR);
    
    bool balanceLeft(AVLNode<T>* &pR);
    bool balanceRight(AVLNode<T>* &pR);    

};

template <class T>
bool AVLTree<T>::insert(AVLNode<T>* &pR, T &a){
    if(pR==NULL){
        AVLNode<T> *newNode = new AVLNode<T>(a);
        pR = newNode;
        return true;
    } else if(pR->data > a){
        if(this->insert(pR->_pLeft, a)){
            if(pR->status==0){
                pR->status = -1;
                return true;
            } else if(pR->status==1){
                pR->status = 0;
                return false;
            } else {

            }
        } else {
            return false;
        }
    } else if(pR->data < a){
        if(this->insert(pR->_pRight, a)){
            if(pR->status == 0){
                pR->status = -1;
                return true;
            } else if(pR->status==1){
                pR->status = 0;
                return false;
            } else{

            }
        } else {
            return false;
        }

    } else {
        return false;
    }
}




int main(){




    return 0;
}
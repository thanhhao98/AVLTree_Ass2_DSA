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
    AVLNode<T>* &getRoot(){return _pRoot;};
    bool insert(T a){return insert(this->_pRoot, a); }
    bool remove(T a){return remove(this->_pRoot, a); }
protected:
    bool insert(AVLNode<T>* &pR, T a);
    bool remove(AVLNode<T>* &pR, T a);

    void roteLeft(AVLNode<T>* &pR);
    void roteRight(AVLNode<T>* &pR);
    void roteLR(AVLNode<T>* &pR);
    void roteRL(AVLNode<T>* &pR);
    
    bool balanceLeft(AVLNode<T>* &pR);
    bool balanceRight(AVLNode<T>* &pR);    
    bool balanceLR(AVLNode<T>* &pR);
    bool balanceRL(AVLNode<T>* &pR);

};


template <class T>
void AVLTree<T>::roteRight(AVLNode<T>* &pR){
    AVLNode<T> *tempNode = pR;
    pR = pR->_pLeft;
    tempNode->_pLeft = pR->_pRight;
    pR->_pRight = tempNode;
}

template <class T>
void AVLTree<T>::roteLeft(AVLNode<T>* &pR){
    AVLNode<T> *tempNode = pR;
    pR = pR->_pRight;
    tempNode->_pRight = pR->_pLeft;
    pR->_pLeft = tempNode;
}

template <class T>
void AVLTree<T>::roteLR(AVLNode<T>* &pR){
    roteLeft(pR->_pLeft);
    roteRight(pR);
}

template <class  T>
void AVLTree<T>::roteRL(AVLNode<T>* &pR){
    roteRight(pR->_pRight);
    roteLeft(pR);
}

template <class T>
bool AVLTree<T>::balanceLeft(AVLNode<T>* &pR){
    pR->status=pR->_pRight->status=0;
    return true;
}

template <class T>
bool AVLTree<T>::balanceRight(AVLNode<T>* &pR){
    pR->status=pR->_pLeft->status=0;
    return true;
}

template <class T>
bool AVLTree<T>::balanceLR(AVLNode<T>* &pR){
    if(pR->status==0){
        pR->_pLeft->status=pR->_pRight->status=0;
    } else if(pR->status==-1){
        pR->status=pR->_pLeft->status=0;
        pR->_pRight->status=1;
    } else {
        pR->status=pR->_pRight->status=0;
        pR->_pLeft->status=-1;
    }
    return true;

}

template <class T>
bool AVLTree<T>::balanceRL(AVLNode<T>* &pR){
    if(pR->status==0){
        pR->_pLeft->status=0;
        pR->_pRight->status=0;
    } else if(pR->status==-1){
        pR->status=0;
        pR->_pLeft->status=0;
        pR->_pRight->status=1;
    } else {
        pR->status=0;
        pR->_pLeft->status=-1;
        pR->_pRight->status=0;
    }
    return true;
}

template <class T>
bool AVLTree<T>::insert(AVLNode<T>* &pR, T a){
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
                if(pR->_pLeft->status == 0){
                    return false;
                } else if(pR->_pLeft->status == -1){
                    roteRight(pR);
                    balanceLeft(pR);
                    return false;
                } else {
                    roteLR(pR);
                    balanceLR(pR);
                    return false;
                }
            }
        } else {
            return false;
        }
    } else if(pR->data < a){
        if(this->insert(pR->_pRight, a)){
            if(pR->status == 0){
                pR->status = 1;
                return true;
            } else if(pR->status==-1){
                pR->status = 0;
                return false;
            } else{
                if(pR->_pRight->status==0){
                    return false;
                } else if(pR->_pRight->status==1){
                    roteLeft(pR);
                    balanceRight(pR);
                    return false;
                } else {
                    roteRL(pR);
                    balanceRL(pR);
                    return false;
                }
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

// RR false


int main(){
    AVLTree<int> *root = new AVLTree<int>();
    root->insert(50);
    root->insert(30);
    root->insert(80);
    root->insert(100);   
    root->insert(60);  
    root->insert(70);
    cout << root->getRoot()->data << endl;
    cout << root->getRoot()->_pLeft->data << endl;
    cout << root->getRoot()->_pRight->data << endl;
    cout << root->getRoot()->_pRight->_pRight->data << endl;
    cout << root->getRoot()->_pLeft->_pLeft->data << endl;
    cout << root->getRoot()->_pRight->_pLeft->data << endl;


    cout << "###################################################################" << endl;

    cout << root->getRoot()->status << endl;
    cout << root->getRoot()->_pLeft->status << endl;
    cout << root->getRoot()->_pRight->status << endl;
    cout << root->getRoot()->_pRight->_pRight->status << endl;
    cout << root->getRoot()->_pLeft->_pLeft->status << endl;
    cout << root->getRoot()->_pRight->_pLeft->status << endl;
    




    return 0;
}
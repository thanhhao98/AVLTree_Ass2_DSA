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
    if(pR->status==-1){
        pR->status=pR->_pRight->status=0;
        return true;
    } else if(pR->status==0){
        pR->status=1;
        pR->_pRight->status = -1;
        return false;
    } else {
        return false;
    }
}

template <class T>
bool AVLTree<T>::balanceRight(AVLNode<T>* &pR){
    if(pR->status==1){
        pR->status=pR->_pLeft->status=0;
        return true;
    } else if(pR->status==0){
        pR->status=-1;
        pR->_pLeft->status=1;
        return false;
    } else {
        return false;
    }
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
        pR->_pLeft->status=pR->_pRight->status=0;
    } else if(pR->status==-1){
        pR->status = pR->_pLeft->status=0;
        pR->_pRight->status=1;
    } else {
        pR->status = pR->_pRight->status=0;
        pR->_pLeft->status=-1;
    }
    return true;
}

template <class T>
bool AVLTree<T>::insert(AVLNode<T>* &pR, T a){
    if(!pR){
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
                    return !balanceLeft(pR);
                } else {
                    roteLR(pR);
                    return !balanceLR(pR);
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
                    return !balanceRight(pR);
                } else {
                    roteRL(pR);
                    return !balanceRL(pR);
                }
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

template <class T>
bool AVLTree<T>::remove(AVLNode<T>* &pR, T a){
    if(!pR){
        return false;
    } else if(pR->data>a){
        if(this->remove(pR->_pLeft,a)){
            if(pR->status==0){
                pR->status=1;
                return false;
            } else if(pR->status==-1){
                pR->status=0;
                return true;
            } else {
                if(pR->_pRight->status==-1){
                    roteRL(pR);
                    return balanceRL(pR);
                } else {
                    roteLeft(pR);
                    return balanceRight(pR);
                }
            }
        } else {
            return false;
        }
    } else if(pR->data<a) {
        if(this->remove(pR->_pRight,a)){
            if(pR->status==0){
                pR->status=-1;
                return false;
            } else if(pR->status==1){
                pR->status=0;
                return true;
            } else {
                if(pR->_pLeft->status==1){
                    roteLR(pR);
                    return balanceLR(pR);
                } else {
                    roteRight(pR);
                    return balanceLeft(pR);
                }
            }
        } else {
            return false;
        }
    } else if(pR->data==a) {
        if(!pR->_pLeft&&!pR->_pRight){
            pR=NULL;
        } else if(!pR->_pLeft){
            pR=pR->_pRight;
        } else if(!pR->_pRight){
            pR=pR->_pLeft;
        } else {
            AVLNode<T> *temp = pR->_pRight;
            while(temp->_pLeft){
                temp=temp->_pLeft;
            }
            temp->_pLeft = pR->_pLeft;
            pR->data = temp->data;
            if(this->remove(pR->_pRight,pR->data)){
                if(pR->status==0){
                    pR->status=-1;
                    return false;
                } else if(pR->status==1){
                    pR->status=0;
                    return true;
                } else {
                    if(pR->_pLeft->status==1){
                        roteLR(pR);
                        return balanceLR(pR);
                    } else {
                        roteRight(pR);
                        return balanceLeft(pR);
                    }
                }
            } else {
                return false;
            }
        }
    }
}


int main(){    




    return 0;
}
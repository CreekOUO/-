#pragma once
#include<iostream>
using namespace std;
//我的root是開頭節點，它的lefeChild才是樹root
template <typename T>
struct  tbTreeNode {
	T data;
	bool rbit;      //=1,rchild正常指標;=0,引線
	bool lbit;
    tbTreeNode* lchild; //筆記:C++可省struct
	tbTreeNode* rchild;
};

template <typename T>
class TbinTree {
private:
    tbTreeNode<T>* root, * ptr, * newnode;

public:
    TbinTree() {//一直報錯所以寫裡面了
        root = newtbintree();
        root->lchild = root;
        root->rchild = root;
        root->lbit = 0;
        root->rbit = 1;
    }
    tbTreeNode<T>* getRoot();
    tbTreeNode<T>* newtbintree();

    // 插入節點
    void insert(T value);
    void insertRight(tbTreeNode<T>* nodeParent, tbTreeNode<T>* node);
    void insertLeft(tbTreeNode<T>* nodeParent, tbTreeNode<T>* node);

    void deleteNode(T value);// 刪除節點

    //找上一點和下一點
    tbTreeNode<T>* insucc(tbTreeNode<T>* node);
    tbTreeNode<T>* inpred(tbTreeNode<T>* node);
    // in-order 拜訪順序
    void inOrderTraversal(tbTreeNode<T>* rootT);
    // 查找排名
    int findRank(int k);

    //我以為書上的方法是錯的，為了2子樹delete寫的，但沒用了
    tbTreeNode<T>* RightSamall(tbTreeNode<T>* node) {
        if (!node || !node->right || root->rbit) {//node沒有右子樹，但會用到這函式的2子樹delete，一定會有但做一下保險
            return nullptr;
        }
        tbTreeNode<T>* current = node->rchild;
        while (current && !current->lbit) {
            current = current->lchild;
        }
        return current;
    }
    tbTreeNode<T>* LeftLarge(tbTreeNode<T>* node) {
        if (!root || !root->left || root->isLeftThread) {
            return nullptr;
        }
        tbTreeNode<T>* current = node->lchild;
        while (current && !current->rbit) {
            current = current->rchild;
        }
        return current;
    }

};
template <typename T>
tbTreeNode<T>* TbinTree<T>::getRoot() {
    return root;
}
template <typename T>
tbTreeNode<T>* TbinTree<T>::newtbintree() {
    tbTreeNode<T>* temp;
    temp = new tbTreeNode<T>;
    temp->lchild = NULL;
    temp->rchild = NULL;
    return temp;
}
template <typename T>
void TbinTree<T>::insert(T value) {//mermer:書上我解讀這邊時我還在煩惱插入的地方是實線怎麼辦，仔細想想沒有指定插入本來就是左小又大一直往下加吧?

    newnode = newtbintree();
    newnode->data = value;
    if (root->lchild == root) {//如果樹是空的，直接將新節點作為左子節點插入
        insertLeft(root, newnode);
       
    }
    else {
        ptr = root->lchild;
        while (ptr->data != newnode->data) {         //找到相同的值，表示該值已存在於樹中
            if (newnode->data < ptr->data) {         //如果newnode->data小於目前節點ptr->data，表示應插入左節點
                if (ptr->lbit == 0) {                //lbit == 0，左子節點空的，可以直接插入新節點。
                    insertLeft(ptr, newnode);
                    break;
                }
                else
                    ptr = ptr->lchild;               //目前節點移動到下一個左節點，繼續找
            }
            else if (newnode->data > ptr->data) {//如果newnode->data大於目前節點ptr->data，表示應插入右節點
                if (ptr->rbit == 0) {
                    insertRight(ptr, newnode);
                    break;
                }
                else
                    ptr = ptr->rchild;
            }
        }
        if (ptr->data == newnode->data) {
            cout << "this node existed \n";
            return;
        }
    }
}

template <typename T>
void TbinTree<T>::insertRight(tbTreeNode<T>* nodeParent, tbTreeNode<T>* node) {//父節點的右子節點
    tbTreeNode<T>* w;
    node->rchild = nodeParent->rchild;   //原父節點的右子節點and線屬性變插入點的
    node->rbit = nodeParent->rbit;
    node->lchild = nodeParent;  //插入右邊時上個點就是Parent，把左數設為Parent 引線=0
    node->lbit = 0;
    nodeParent->rchild = node;
    nodeParent->rbit = 1;
    if (node->rbit == 1) {//右邊底下還有Tree
        w = insucc(node); //是他的下一個
        w->lchild = node; //我有想如果有指東西的話就不能覆蓋，但我用的是左小右大加入值，插入值都會被放到最後。我覺得好像沒有寫的必要但書上寫了
    }
}
template <typename T>
void TbinTree<T>::insertLeft(tbTreeNode<T>* nodeParent, tbTreeNode<T>* node) {
    tbTreeNode<T>* w;
    node->lchild = nodeParent->lchild;
    node->lbit = nodeParent->lbit;
    node->rchild = nodeParent;
    node->rbit = 0;
    nodeParent->lchild = node;
    nodeParent->lbit = 1;
    if (node->lbit == 1) {//如果左下還有樹
        w = inpred(node);
        w->rchild = node;

    }
}
template <typename T>
void TbinTree<T>::deleteNode(T value) {
    tbTreeNode<T>* ptrParent;
    tbTreeNode<T>* ptrPred, * ptrSucc;
    if (root->lchild == root) {//從root->lchild才開始放資料
        cout << "no data\n";
        return;
    }
    ptr = root->lchild;
    while (ptr->data != value) {
        ptrParent = ptr;
        if (value < ptr->data) {
            if (ptr->lbit == 1)
                ptr = ptr->lchild;
            else  //已經沒樹找找不到   
                break;

        }
        else if (value > ptr->data) {
            if (ptr->rchild == 1)
                ptr = ptr->rchild;
            else
                break;
        }
    }
    if (ptr->data != value) {//最後找完結果不是要刪除的值
        cout << "not found\n";
        return;
    }
    cout << ptr->data << " delete\n";
    //刪除葉節點
    if (ptr->lbit == 0 && ptr->rbit == 0) {
        if (ptrParent == root) {//刪除第一個節點
            ptrParent->lchild = root;
            ptrParent->lbit = 0;
        }
        else if (ptr->data < ptrParent->data) {//左
            ptrParent->lchild = ptr->lchild;
            ptrParent->lbit = 0;
        }
        else {//右
            ptrParent->rchild = ptr->rchild;
            ptrParent->rbit = 0;
        }
        delete(ptr);
    }
    //刪除節點左右都有子節點
    //我在這卡了半天我在理解時以為書上方法寫錯了自己想了好久，後來發現方法是對的但ptr->lchild我的參考書中統一插在Parent右子數，所以我加上判斷ptr左右ptr->lchild插在哪
    else if (ptr->lbit == 1 && ptr->rbit == 1) {
        ptrPred = inpred(ptr);
        ptrPred->rchild = ptr->rchild;
        ptrPred->rbit = ptr->rbit;
        if (ptrParent->lchild == ptr) { //Ptr在左邊
            ptrParent->lchild = ptr->lchild;  
        }   
        else if (ptrParent->rchild == ptr) {//Ptr在右邊
            ptrParent->rchild = ptr->lchild;  
        }
        delete(ptr);
    }
    
    //刪除點一個子節點
    else {
        tbTreeNode<T>* p = predecessor(ptr);
        tbTreeNode<T>* s = successor(ptr);
        if (ptrParent == root) {//刪除root(資料的root)
            if (ptr->lbit == 1) {
                ptrPred = inpred(ptr);
                root->lchild = ptr->lchild;
                ptrPred->rchild = root;//只有左樹，最後一個點是root(不是我程式裡的開頭節點root)，把root刪掉前一個點就是最後
            }
            else {
                ptrSucc = insucc(ptr);
                root->lchild = ptr->rchild;
                ptrSucc->lchild = root;//只有右樹，第一個點是root，把root刪掉下一個點就是最前
            } 
        }
        else {//不是root
            if (ptr->data < ptrParent->data) {//ptr在Parent左邊
                if (ptr->rbit == 1 && ptr->lbit == 0) {//只有右邊節點
                  
                    /*ptr->rchild->lchild = ptr->lchild;//這裡ptr->rchild->lchild如果有值不是會被覆蓋嗎?爛書
                    ptr->rchild->lbit = ptr->lbit;*/

                    ptrParent->lchild = ptr->rchild;
                    ptrParent->lbit = ptr->rbit;
                    s->lchild = ptr->lchild;
                    s->lbit = ptr->lbit;
                }
                else if (ptr->rbit == 0 && ptr->lbit == 1) {//只有左邊節點                    
                    ptrParent->lchild = ptr->lchild;
                    ptrParent->lbit = ptr->lbit;
                    p->rchild = ptr->rchild;
                    p->rbit = ptr->rbit;
                }
            }
            else {//ptr在Parent右邊
                if (ptr->rbit == 1 && ptr->lbit == 0) {//只有右邊節點
                    ptrParent->rchild = ptr->rchild;
                    ptrParent->rbit = ptr->rbit;
                    s->lchild = ptrParent;
                    s->lbit = ptr->lbit;
                }
                else if (ptr->rbit == 0 && ptr->lbit == 1) {//只有左邊節點
                    ptrParent->rchild = ptr->lchild;
                    ptrParent->rbit = ptr->lbit;
                    p->rchild = ptr->rchild;
                    p->rbit = ptr->rbit;
                }
            }
            delete(ptr);
        } 
    }

}

template <typename T>
tbTreeNode<T>*  TbinTree<T>::insucc(tbTreeNode<T>* node) {//
    tbTreeNode<T>* succ;

    succ = node->rchild;
    if (node->rbit==1)//當右樹底下有點往下找最左的
        while (succ->lbit == 1)
            succ = succ->lchild;
    return succ;       
}
template <typename T>
tbTreeNode<T>* TbinTree<T>::inpred(tbTreeNode<T>* node) {
    tbTreeNode<T>* pred;
    pred = node->lchild;
    if (node->rbit==1)
    while (pred->rbit == 1)
        pred = pred->rchild;
    return pred;
}
template <typename T>
void TbinTree<T>::inOrderTraversal(tbTreeNode<T>* node) {
    if (node->lchild == root) {//第一個點
        cout << "no data\n";return;
    }
    cout << "Inorder Traversal:\n";
    ptr = root;
    do {
        ptr = insucc(ptr);
        if (ptr != root)
            cout << " " << ptr->data << " 左連結的節點:" << ptr->lchild <<"連結屬性:" << (ptr->lbit ? "實線" : "引線") << "右連結的節點"<< ptr->rchild<<"連結屬性:" << (ptr->lbit ? "實線" : "引線")<<endl;
    } while (ptr != root);//最後點指到root
    cout << "\n";
}
template <typename T>
int  TbinTree<T>::findRank(int k) {

}
/*
參考:
資料結構C++第五版 6.5 這本書沒用程式漏洞一堆 很多問題都沒處理到
Template(看完這個我學到我程式為麼報錯那麼多，寫那麼多遍T只是為了一行T data而已)
https://www.bilibili.com/video/BV1Dk4y1j7oj/?spm_id_from=333.788.videopod.episodes&vd_source=ac1d6aa37c1fba71af697a9e7cda0df2&p=54
刪除2子樹的點
https://www.youtube.com/watch?v=8elxCZtozuI
C++文件操作
https://stackoverflow.com/questions/61096184/how-to-split-the-elements-of-a-text-file-in-c
https://aprilyang.home.blog/2020/04/17/stringstream-to-read-int-from-a-string/
*/



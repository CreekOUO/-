#pragma once
#include<iostream>
using namespace std;
//�ڪ�root�O�}�Y�`�I�A����lefeChild�~�O��root
template <typename T>
struct  tbTreeNode {
	T data;
	bool rbit;      //=1,rchild���`����;=0,�޽u
	bool lbit;
    tbTreeNode* lchild; //���O:C++�i��struct
	tbTreeNode* rchild;
};

template <typename T>
class TbinTree {
private:
    tbTreeNode<T>* root, * ptr, * newnode;

public:
    TbinTree() {//�@�������ҥH�g�̭��F
        root = newtbintree();
        root->lchild = root;
        root->rchild = root;
        root->lbit = 0;
        root->rbit = 1;
    }
    tbTreeNode<T>* getRoot();
    tbTreeNode<T>* newtbintree();

    // ���J�`�I
    void insert(T value);
    void insertRight(tbTreeNode<T>* nodeParent, tbTreeNode<T>* node);
    void insertLeft(tbTreeNode<T>* nodeParent, tbTreeNode<T>* node);

    void deleteNode(T value);// �R���`�I

    //��W�@�I�M�U�@�I
    tbTreeNode<T>* insucc(tbTreeNode<T>* node);
    tbTreeNode<T>* inpred(tbTreeNode<T>* node);
    // in-order ���X����
    void inOrderTraversal(tbTreeNode<T>* rootT);
    // �d��ƦW
    int findRank(int k);

    //�ڥH���ѤW����k�O�����A���F2�l��delete�g���A���S�ΤF
    tbTreeNode<T>* RightSamall(tbTreeNode<T>* node) {
        if (!node || !node->right || root->rbit) {//node�S���k�l��A���|�Ψ�o�禡��2�l��delete�A�@�w�|�������@�U�O�I
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
void TbinTree<T>::insert(T value) {//mermer:�ѤW�ڸ�Ū�o��ɧ��٦b�дo���J���a��O��u����A�J�ӷQ�Q�S�����w���J���ӴN�O���p�S�j�@�����U�[�a?

    newnode = newtbintree();
    newnode->data = value;
    if (root->lchild == root) {//�p�G��O�Ū��A�����N�s�`�I�@�����l�`�I���J
        insertLeft(root, newnode);
       
    }
    else {
        ptr = root->lchild;
        while (ptr->data != newnode->data) {         //���ۦP���ȡA��ܸӭȤw�s�b���
            if (newnode->data < ptr->data) {         //�p�Gnewnode->data�p��ثe�`�Iptr->data�A��������J���`�I
                if (ptr->lbit == 0) {                //lbit == 0�A���l�`�I�Ū��A�i�H�������J�s�`�I�C
                    insertLeft(ptr, newnode);
                    break;
                }
                else
                    ptr = ptr->lchild;               //�ثe�`�I���ʨ�U�@�ӥ��`�I�A�~���
            }
            else if (newnode->data > ptr->data) {//�p�Gnewnode->data�j��ثe�`�Iptr->data�A��������J�k�`�I
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
void TbinTree<T>::insertRight(tbTreeNode<T>* nodeParent, tbTreeNode<T>* node) {//���`�I���k�l�`�I
    tbTreeNode<T>* w;
    node->rchild = nodeParent->rchild;   //����`�I���k�l�`�Iand�u�ݩ��ܴ��J�I��
    node->rbit = nodeParent->rbit;
    node->lchild = nodeParent;  //���J�k��ɤW���I�N�OParent�A�⥪�Ƴ]��Parent �޽u=0
    node->lbit = 0;
    nodeParent->rchild = node;
    nodeParent->rbit = 1;
    if (node->rbit == 1) {//�k�䩳�U�٦�Tree
        w = insucc(node); //�O�L���U�@��
        w->lchild = node; //�ڦ��Q�p�G�����F�誺�ܴN�����л\�A���ڥΪ��O���p�k�j�[�J�ȡA���J�ȳ��|�Q���̫�C��ı�o�n���S���g�����n���ѤW�g�F
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
    if (node->lbit == 1) {//�p�G���U�٦���
        w = inpred(node);
        w->rchild = node;

    }
}
template <typename T>
void TbinTree<T>::deleteNode(T value) {
    tbTreeNode<T>* ptrParent;
    tbTreeNode<T>* ptrPred, * ptrSucc;
    if (root->lchild == root) {//�qroot->lchild�~�}�l����
        cout << "no data\n";
        return;
    }
    ptr = root->lchild;
    while (ptr->data != value) {
        ptrParent = ptr;
        if (value < ptr->data) {
            if (ptr->lbit == 1)
                ptr = ptr->lchild;
            else  //�w�g�S���䤣��   
                break;

        }
        else if (value > ptr->data) {
            if (ptr->rchild == 1)
                ptr = ptr->rchild;
            else
                break;
        }
    }
    if (ptr->data != value) {//�̫�䧹���G���O�n�R������
        cout << "not found\n";
        return;
    }
    cout << ptr->data << " delete\n";
    //�R�����`�I
    if (ptr->lbit == 0 && ptr->rbit == 0) {
        if (ptrParent == root) {//�R���Ĥ@�Ӹ`�I
            ptrParent->lchild = root;
            ptrParent->lbit = 0;
        }
        else if (ptr->data < ptrParent->data) {//��
            ptrParent->lchild = ptr->lchild;
            ptrParent->lbit = 0;
        }
        else {//�k
            ptrParent->rchild = ptr->rchild;
            ptrParent->rbit = 0;
        }
        delete(ptr);
    }
    //�R���`�I���k�����l�`�I
    //�ڦb�o�d�F�b�ѧڦb�z�ѮɥH���ѤW��k�g���F�ۤv�Q�F�n�[�A��ӵo�{��k�O�諸��ptr->lchild�ڪ��ѦҮѤ��Τ@���bParent�k�l�ơA�ҥH�ڥ[�W�P�_ptr���kptr->lchild���b��
    else if (ptr->lbit == 1 && ptr->rbit == 1) {
        ptrPred = inpred(ptr);
        ptrPred->rchild = ptr->rchild;
        ptrPred->rbit = ptr->rbit;
        if (ptrParent->lchild == ptr) { //Ptr�b����
            ptrParent->lchild = ptr->lchild;  
        }   
        else if (ptrParent->rchild == ptr) {//Ptr�b�k��
            ptrParent->rchild = ptr->lchild;  
        }
        delete(ptr);
    }
    
    //�R���I�@�Ӥl�`�I
    else {
        tbTreeNode<T>* p = predecessor(ptr);
        tbTreeNode<T>* s = successor(ptr);
        if (ptrParent == root) {//�R��root(��ƪ�root)
            if (ptr->lbit == 1) {
                ptrPred = inpred(ptr);
                root->lchild = ptr->lchild;
                ptrPred->rchild = root;//�u������A�̫�@���I�Oroot(���O�ڵ{���̪��}�Y�`�Iroot)�A��root�R���e�@���I�N�O�̫�
            }
            else {
                ptrSucc = insucc(ptr);
                root->lchild = ptr->rchild;
                ptrSucc->lchild = root;//�u���k��A�Ĥ@���I�Oroot�A��root�R���U�@���I�N�O�̫e
            } 
        }
        else {//���Oroot
            if (ptr->data < ptrParent->data) {//ptr�bParent����
                if (ptr->rbit == 1 && ptr->lbit == 0) {//�u���k��`�I
                  
                    /*ptr->rchild->lchild = ptr->lchild;//�o��ptr->rchild->lchild�p�G���Ȥ��O�|�Q�л\��?���
                    ptr->rchild->lbit = ptr->lbit;*/

                    ptrParent->lchild = ptr->rchild;
                    ptrParent->lbit = ptr->rbit;
                    s->lchild = ptr->lchild;
                    s->lbit = ptr->lbit;
                }
                else if (ptr->rbit == 0 && ptr->lbit == 1) {//�u������`�I                    
                    ptrParent->lchild = ptr->lchild;
                    ptrParent->lbit = ptr->lbit;
                    p->rchild = ptr->rchild;
                    p->rbit = ptr->rbit;
                }
            }
            else {//ptr�bParent�k��
                if (ptr->rbit == 1 && ptr->lbit == 0) {//�u���k��`�I
                    ptrParent->rchild = ptr->rchild;
                    ptrParent->rbit = ptr->rbit;
                    s->lchild = ptrParent;
                    s->lbit = ptr->lbit;
                }
                else if (ptr->rbit == 0 && ptr->lbit == 1) {//�u������`�I
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
    if (node->rbit==1)//��k�𩳤U���I���U��̥���
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
    if (node->lchild == root) {//�Ĥ@���I
        cout << "no data\n";return;
    }
    cout << "Inorder Traversal:\n";
    ptr = root;
    do {
        ptr = insucc(ptr);
        if (ptr != root)
            cout << " " << ptr->data << " ���s�����`�I:" << ptr->lchild <<"�s���ݩ�:" << (ptr->lbit ? "��u" : "�޽u") << "�k�s�����`�I"<< ptr->rchild<<"�s���ݩ�:" << (ptr->lbit ? "��u" : "�޽u")<<endl;
    } while (ptr != root);//�̫��I����root
    cout << "\n";
}
template <typename T>
int  TbinTree<T>::findRank(int k) {

}
/*
�Ѧ�:
��Ƶ��cC++�Ĥ��� 6.5 �o���ѨS�ε{���|�}�@�� �ܦh���D���S�B�z��
Template(�ݧ��o�ӧھǨ�ڵ{�������������h�A�g����h�MT�u�O���F�@��T data�Ӥw)
https://www.bilibili.com/video/BV1Dk4y1j7oj/?spm_id_from=333.788.videopod.episodes&vd_source=ac1d6aa37c1fba71af697a9e7cda0df2&p=54
�R��2�l���I
https://www.youtube.com/watch?v=8elxCZtozuI
C++���ާ@
https://stackoverflow.com/questions/61096184/how-to-split-the-elements-of-a-text-file-in-c
https://aprilyang.home.blog/2020/04/17/stringstream-to-read-int-from-a-string/
*/





#ifndef AVL_H
#define AVL_H
#include "TreeNode.h"
#include "OldArray.h"
#include <cstddef>
#include "library.h"
#include <math.h>
#include <iostream>
/*-----------------------------------------------------------------*/
typedef enum{
    LL,
    RR,
    RL,
    LR,
    V
}TypeOfRotate;

typedef enum{
    EXSISTINGKEY,
    UNEXSISTINGKEY
}AVLresult;
template<class Key,class Value>
class AVL{

    Node<Key,Value>* r;//the root of the tree
    Node<Key,Value>* min_node;
    Node<Key,Value>* max_node;
    int size;


    public:

            /*constructor*/
            AVL():r(nullptr),min_node(nullptr),max_node(nullptr),size(0){}
            /*destructor*/
            ~AVL()=default;
            /*copyconstructor*/
            AVL(const AVL& avl)=default;



            /*---------------------RotatingTheNode------------------------------*/
            /*Node<Key,Value>* typeOfRotating(Node<Key,Value>* node);
            Node<Key,Value>* LLRotate(Node<Key,Value>* node_need_rotating);
            Node<Key,Value>* RRRotate(Node<Key,Value>* node_need_rotating);
            Node<Key,Value>* LRRotate(Node<Key,Value>* node_need_rotating);
            Node<Key,Value>* RLRotate(Node<Key,Value>* node_need_rotating);
            void doSuitableRotating(Node<Key,Value>* node_in_path);*/






            /*--------------------InsertNode-------------------------------------*/
            //we need to find the last node where we have to add the new node
            /*Node<Key,Value>* findTheFatherOfTheNewNode(Node<Key,Value>* first_node,Key key);//before doing balance and it is the last node in the path
            Node<Key,Value>* insrtNodeAndbalancing(Key key,Value value);*/



            /*--------------------removeNode-------------------------------------*/
            /*void removeNode(Key key_to_remove);
            void removeNodeWithNoSons(Node<Key,Value>* node);
            void removeNodeWithOneSons(Node<Key,Value>* node);
            void removeNodeWithTowSons(Node<Key,Value>* node);
            */

            /*---------------------Destroy--------------------------------*/
            void TreeDestroy(){
                if(!r){
                    return;
                }
                deleteNodes(r);
                r=NULL;
            }





            /*--------------------------------------------------------------*/
            /*void updateMinNodeInTree();*/





/*Node<Key,Value>* findNodeNeedtoRotate(Node<Key,Value>* node);///return Null
Node<Key,Value>* findNode(Node<Key,Value>* root,Key key);*/

/*----------------------------------------------------------------------------------------------------------*/
    Node<Key,Value>* GetRoot(){
        return r;
    }
    void updateSize(int s){
        size=s;
    }
    int Getsize(){
        return size;
    }
    Node<Key,Value>* GetMinNode(){
        return min_node;
    }
    Node<Key,Value>* GetMaxNode(){

        return max_node;
    }

/*---------------------RotatingTheNode------------------------------*/

    TypeOfRotate typeOfRotating(Node<Key,Value>* father){///reach this function if we need to rotate
        int bf_l=0;
        int bf_r=0;
        if(father->GetLeftChild()){
        Node<Key,Value>* left_child=father->GetLeftChild();
        bf_l=left_child->GetNodeBf();
        }else{
             bf_l=-1;
        }
        if(father->GetRightChild()){
        Node<Key,Value>* right_child=father->GetRightChild();
            bf_r=right_child->GetNodeBf();
        }else{
            bf_r=-1;
        }
        int bf_f=father->GetNodeBf();
        if(bf_f==-2 && bf_r==1){
            return RL;
        }
        if(bf_f==-2 && bf_r<=0){
            return RR;
        }
        if(bf_f==2 && bf_l==-1){
            return LR;
        }
        if(bf_f==2 && bf_l>=0){
            return LL;
        }
        return V;

    }




    Node<Key,Value>* LLRotate(Node<Key,Value>* node_need_rotating){
        Node<Key,Value>* B=node_need_rotating;
        Node<Key,Value>* BF=B->GetNodeFather();
        Node<Key,Value>* A=B->GetLeftChild();
        Node<Key,Value>* AR=A->GetRightChild();
        B->updateLeftChild(AR);
        if(!BF){
            A->updateFather(NULL);
            r=A;
        }else{
            bool state =leftOrRightChild(B);//b is right child of his father
            if(state){
                BF->updateRightChild(A);
            }else{
                BF->updateLeftChild(A);
            }
        }
        A->updateRightChild(B);
        /*-----------updateDataOfEachNode---------*/
        B->updateData();
        A->updateData();

        return (A);
    }




    Node<Key,Value>* RRRotate(Node<Key,Value>* node_need_rotating){
        Node<Key,Value>* B=node_need_rotating;
        Node<Key,Value>* BF=B->GetNodeFather();
        Node<Key,Value>* A=B->GetRightChild();
        Node<Key,Value>* AL=A->GetLeftChild();
        B->updateRightChild(AL);
        if(!BF){
            A->updateFather(NULL);
            r=A;
        }else{
            bool state =leftOrRightChild(B);//b is right child of his father
            if(state){
                BF->updateRightChild(A);
            }else{
                BF->updateLeftChild(A);
            }
        }
        A->updateLeftChild(B);
        /*-----------updateDataOfEachNode---------*/

        B->updateData();
        A->updateData();
        return (A);
    }




    Node<Key,Value>* LRRotate(Node<Key,Value>* node_need_rotating){
        Node<Key,Value>* B_node=node_need_rotating->GetLeftChild();
        RRRotate(B_node);
        Node<Key,Value>* new_father=LLRotate( node_need_rotating);
        return (new_father);
    }




    Node<Key,Value>* RLRotate(Node<Key,Value>* node_need_rotating){
        Node<Key,Value>* B_node=node_need_rotating->GetRightChild();
        LLRotate(B_node);
        Node<Key,Value>* new_father=RRRotate( node_need_rotating);
        return (new_father);
    }




    void doSuitableRotating(Node<Key,Value>* node_in_path){
        if(!node_in_path){
            return;
        }
        Node<Key,Value>* node_need_to_rotate=findNodeNeedtoRotate(node_in_path);///firstupdatedata
        if(!node_need_to_rotate){
            return;
        }
        Node<Key,Value>* new_node_in_path=NULL;
        TypeOfRotate rotate_type=typeOfRotating( node_need_to_rotate);
        if(rotate_type==LL){
            new_node_in_path=LLRotate(node_need_to_rotate);

        }else if(rotate_type==LR){
             new_node_in_path=LRRotate(node_need_to_rotate);

        }else if(rotate_type==RR){
             new_node_in_path=RRRotate(node_need_to_rotate);

        }else{
             new_node_in_path=RLRotate(node_need_to_rotate);
        }
        if(!new_node_in_path){
            return;
        }
        node_need_to_rotate->updateData();
        doSuitableRotating(new_node_in_path);
        return;
    }

    /*-----------------------------------------------------------------------------*/




    Node<Key,Value>* findNodeNeedtoRotate(Node<Key,Value>* node){
        if(!node){
            return NULL;
        }
        node->updateData();
        int bf=node->GetNodeBf();
        if(bf==2 || bf==-2){
            return node;
        }
        return findNodeNeedtoRotate(node->GetNodeFather());
    }




    StatusType insrtNodeAndbalancing(Key key,Value value){
        Node<Key,Value>* new_node=new Node<Key,Value>(key,value);
        if(!new_node){
            return ALLOCATION_ERROR;
        }
        if(!r){
            r=new_node;
            updateMinNodeInTree();
            updateMaxNodeInTree();
            size++;
            return SUCCESS ;
        }
        Node<Key,Value>* node=findNode(r,key);
        if(node){
            delete new_node;
            return FAILURE;
        }
        Node<Key,Value>* last_node=findTheFatherOfTheNewNode(r,key);
        Key key_of_last_node=last_node->getKey();
        if(key>key_of_last_node){
            last_node->updateRightChild(new_node);
        }
        if(key<key_of_last_node){
            last_node->updateLeftChild(new_node) ;
        }
        doSuitableRotating(new_node);
        updateMinNodeInTree();
        updateMaxNodeInTree();
        size++;
        return SUCCESS;
    }




    Node<Key,Value>* findNode(Node<Key,Value>* node,Key k){
        if(node==nullptr){
            return NULL;
        }
        Key current_key=node->getKey();
        if(k==current_key){
            return node;
        }
        if(current_key>k){
            return findNode(node->GetLeftChild(),k);

        }
        if(current_key<k){
            return findNode(node->GetRightChild(),k);
        }
        return NULL;
    }



    /*--------------------removeNode-------------------------------------*/

        void removeNode(Key key_to_remove,Node<Key,Value>* root=NULL){
            Node<Key,Value>* node=NULL;
            if(!root){
                node=findNode(r,key_to_remove);
                if(!node){
                    return ;
                }
            }else{
                node=findNode(root,key_to_remove);
                if(!node){
                    return ;
                }
            }
            if(node->GetLeftChild() && node->GetRightChild() ){
                removeNodeWithTowSons(node);
                return;
            }else if(node->GetLeftChild() || node->GetRightChild()){
                removeNodeWithOneSons(node);
            }else{
                removeNodeWithNoSons(node);

            }
            size--;
        }




        void removeNodeWithNoSons(Node<Key,Value>* node){
            Node<Key,Value>* father=node->GetNodeFather();
            if(!father){
                r=NULL;
                min_node=NULL;
                max_node=NULL;
                delete node;
            }else{
                bool state=leftOrRightChild(node);
                if(state){//rightChild
                    father->updateRightChild(NULL);
                    delete node;
                }else{
                    father->updateLeftChild(NULL);
                    delete node;
                }
                doSuitableRotating(father);
                updateMinNodeInTree();
                updateMaxNodeInTree();

            }


        }




        void removeNodeWithOneSons(Node<Key,Value>* node){
            Node<Key,Value>* father=node->GetNodeFather();
            Node<Key,Value>* child=NULL;
            if(!father){
                if(node->GetRightChild()){
                    child=node->GetRightChild();
                    child->updateFather(NULL);
                    delete node;
                    r=child;
                }else{
                    child=node->GetLeftChild();
                    child->updateFather(NULL);
                    delete node;
                    r=child;
                }
            }else{
                 if(node->GetRightChild()){
                    child=node->GetRightChild();
                    bool state=leftOrRightChild(node);
                    if(state){////right
                        father->updateRightChild(child);
                        child->updateFather(father);
                        delete node;
                    }else{
                        father->updateLeftChild(child);
                        child->updateFather(father);
                        delete node;
                    }
                }else{
                    child=node->GetLeftChild();
                    bool state=leftOrRightChild(node);
                    if(state){////right
                        father->updateRightChild(child);
                        child->updateFather(father);
                        delete node;
                    }else{//left
                        father->updateLeftChild(child);
                        child->updateFather(father);
                        delete node;
                    }
                }
                doSuitableRotating(father);

            }
            updateMinNodeInTree();
            updateMaxNodeInTree();
        }



        void removeNodeWithTowSons(Node<Key,Value>* node){
            Node<Key,Value>* right_child=node->GetRightChild();
            Node<Key,Value>* alternative_node=RightThenLeftToTheEnd(node);
            Key k=alternative_node->getKey();
            Value v=alternative_node->getValue();
            node->updateKey(k);
            node->updateValue(v);
            removeNode(k,right_child);
        }

         void removeNodeComplex(Key key_to_remove,Node<Key,Value>* root=NULL,Array<Node<Key,Value>*>*curr_array=NULL){
            Node<Key,Value>* node=NULL;
            if(!root){
                node=findNode(r,key_to_remove);
                if(!node){
                    return ;
                }
            }else{
                node=findNode(root,key_to_remove);
                if(!node){
                    return ;
                }
            }
            if(node->GetLeftChild() && node->GetRightChild() ){
                removeNodeWithTowSonsComplex(node,curr_array);
              //  if(key_to_remove.getType()==72&&key_to_remove.getModel()==1){std::cout<<"hhuljijli";}

                return;
            }else if(node->GetLeftChild() || node->GetRightChild()){
                removeNodeWithOneSons(node);
            }else{
                removeNodeWithNoSons(node);

            }
            size--;
        }




        void removeNodeWithNoSonsComplex(Node<Key,Value>* node){
            Node<Key,Value>* father=node->GetNodeFather();
            if(!father){
                r=NULL;
                min_node=NULL;
                max_node=NULL;
                delete node;
            }else{
                bool state=leftOrRightChild(node);
                if(state){//rightChild
                    father->updateRightChild(NULL);
                    delete node;
                }else{
                    father->updateLeftChild(NULL);
                    delete node;
                }
                doSuitableRotating(father);
                updateMinNodeInTree();
                updateMaxNodeInTree();

            }


        }




        void removeNodeWithOneSonsComplex(Node<Key,Value>* node){
            Node<Key,Value>* father=node->GetNodeFather();
            Node<Key,Value>* child=NULL;
            if(!father){
                if(node->GetRightChild()){
                    child=node->GetRightChild();
                    child->updateFather(NULL);
                    delete node;
                    r=child;
                }else{
                    child=node->GetLeftChild();
                    child->updateFather(NULL);
                    delete node;
                    r=child;
                }
            }else{
                 if(node->GetRightChild()){
                    child=node->GetRightChild();
                    bool state=leftOrRightChild(node);
                    if(state){////right
                        father->updateRightChild(child);
                        child->updateFather(father);
                        delete node;
                    }else{
                        father->updateLeftChild(child);
                        child->updateFather(father);
                        delete node;
                    }
                }else{
                    child=node->GetLeftChild();
                    bool state=leftOrRightChild(node);
                    if(state){////right
                        father->updateRightChild(child);
                        child->updateFather(father);
                        delete node;
                    }else{//left
                        father->updateLeftChild(child);
                        child->updateFather(father);
                        delete node;
                    }
                }
                doSuitableRotating(father);

            }
            updateMinNodeInTree();
            updateMaxNodeInTree();
        }



        void removeNodeWithTowSonsComplex(Node<Key,Value>* node,Array<Node<Key,Value>*>* curr_array){
            Node<Key,Value>* right_child=node->GetRightChild();
            Node<Key,Value>* alternative_node=RightThenLeftToTheEnd(node);
            Key k=alternative_node->getKey();
            Value v=alternative_node->getValue();
            node->updateKey(k);
            node->updateValue(v);
            if(curr_array)
            {
              //  if(node->getKey().getModel()==1 &&this->Getsize()==4){std::cout<<"yahoo";}
             // (curr_array->operator[](k.getModel()))->getFirst();
                curr_array->operator[](k.getModel())=node;
             //   (curr_array->operator[](k.getModel()))->updateKey(k);
             //  (curr_array->operator[](k.getModel()))->updateKey(k);
             //  (curr_array->operator[](k.getModel()))->updateValue(v);
            }
            removeNodeComplex(k,right_child,curr_array);


        }




    /*--------------------DestroyTree----------------------------------*/

    void updateMinNodeInTree(){
        min_node=GetMin(r);
    }
    void updateMaxNodeInTree(){
        max_node=GetMax(r);

    }

    /*--------------------build complete Tree----------------------------------*/


    class deleteLeafs{
        int leafs_to_delete;
        public:
        deleteLeafs(int leafs):leafs_to_delete(leafs){}

        void DeleteLeafs(Node<Key,Value>* root){
            if(!root){
                return;
            }

            if(root->isLeaf() && leafs_to_delete){
                Node<Key,Value>* father=root->GetNodeFather();
                 Node<Key,Value>* Left_son=father->GetLeftChild();
                if(root==Left_son){
                    father->updateLeftChild(nullptr);
                }else{
                    father->updateRightChild(nullptr);
                }
                delete root;
                leafs_to_delete--;
                return;
               }
            DeleteLeafs(root->GetRightChild());
            DeleteLeafs(root->GetLeftChild());
        }

    };



    Node<Key,Value>* build(int h){
        Node<Key,Value>* root=new Node<Key,Value>();
        if(!root){
            return NULL;
        }
        if(!h){
            return root;
        }
        root->updateLeftChild(build(h-1));
        root->updateRightChild(build(h-1));
        return root;
    }
    class UpdateKeyAndValue{
        int number;
        int value;

            public:
            UpdateKeyAndValue(int num,int value):number(num),value(value){}

            void updateKeyAndValue(Node<Key,Value>* node){
                if(!node){
                    return ;
                }
                updateKeyAndValue(node->GetRightChild());
                node->updateKey(number);
                node->updateValue(value);
                number--;
                updateKeyAndValue(node->GetLeftChild());
            }
    };
    StatusType constructCompleteTree(int size,int value){

        int h=(int)ceil(log2(size+1))-1;
        int complete_size=(int)pow(2,h+1)-1;
        int need_to_delete=complete_size-size;
        r=build(h);
        if(!r){
            return ALLOCATION_ERROR;
        }
        if(need_to_delete){
            deleteLeafs deleted=deleteLeafs(need_to_delete);
            deleted.DeleteLeafs(r);
        }
        UpdateKeyAndValue update=UpdateKeyAndValue(size-1,value);
        update.updateKeyAndValue(r);
        updatebfsAndHeghits(r);
        updateMinNodeInTree();
        updateMaxNodeInTree();
        updateSize(size);
        return SUCCESS;
    }
    void updatebfsAndHeghits(Node<Key,Value>* node){
        if(!node){
            return;
        }
        updatebfsAndHeghits(node->GetLeftChild());
        updatebfsAndHeghits(node->GetRightChild());
        node->updateData();
    }
    void DeleteWhole(Node<Key,Value>*root_node)
{
        if (!root_node) {
            return;
        }
        DeleteWhole(root_node->GetLeftChild());
        DeleteWhole(root_node->GetRightChild());
        delete root_node;

}

     void DeleteComplexWhole(Node<Key,Value>*root_node)
{
        if (!root_node) {
            return;
        }
        DeleteComplexWhole(root_node->GetLeftChild());
        DeleteComplexWhole(root_node->GetRightChild());
        delete root_node->getValue();
        delete root_node;


}





};

#endif









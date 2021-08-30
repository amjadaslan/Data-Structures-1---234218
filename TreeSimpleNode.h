
#ifndef Tree_NODE_H
#define Tree_NODE_H
#include <cstddef>
#include <typeinfo>
template<class Key,class Value>
class TreeSimpleNode{
    Key key;
    Value value;
    int bf;
    int node_height;
    TreeSimpleNode<Key,Value>* father;
    TreeSimpleNode<Key,Value>* the_left_child;
    TreeSimpleNode<Key,Value>* the_right_child;

    public:


        /*---------------------------Constructor-----------------------*/
       TreeSimpleNode<Key,Value>(Key key,Value value):key(key),value(value),father(nullptr),the_left_child(nullptr),the_right_child(nullptr)
        {
            bf=0;
            node_height=0;

        }
        TreeSimpleNode<Key,Value>():father(nullptr),the_left_child(nullptr),the_right_child(nullptr)
        {
            bf=0;
            node_height=0;
        }





        /*-----------------------------------Get-----------------------*/
        TreeSimpleNode<Key,Value>* GetLeftChild(){

            return the_left_child;
        }
        TreeSimpleNode<Key,Value>* GetRightChild(){
            return the_right_child;
        }
        TreeSimpleNode<Key,Value>* GetNodeFather(){
            return father;
        }
        int GetNodeBf(){
            return bf;
        }
        Key getKey(){
            return key;
        }
        Value getValue(){
            return value;
        }
        int height(){
            return node_height;
        }
        bool isLeaf(){
        if(!the_left_child && !the_right_child){
            return true;
        }
        return false;
    }


        /*-----------------------Update----------------------------------*/
        void updateFather(Node<Key,Value>* new_node){
            father=new_node;
        }
        void updateLeftChild(Node<Key,Value>* new_node){
            the_left_child=new_node;
            if(new_node){
                new_node->updateFather(this);
            }
        }
        void updateRightChild(Node<Key,Value>* new_node){
            the_right_child=new_node;
            if(new_node){
                new_node->updateFather(this);
            }
        }
        void updateKey(Key new_key){
            key=new_key;
        }
        void updateValue(Value new_value){
            //beware to not delete twice
            value=new_value;
        }

/*
        bool isALeaf(){
            if(!the_left_child && !the_right_child){
                return true;
            }
            return false;
        }
        bool ifLeftSon(){
            if(the_left_child){
                return true;
            }else{
                return false
            }
        }
        bool ifRightSon(){
            if(the_right_child){
                return true;
            }else{
                return false
            }
        }
        */


        void updateheight(){
            if(the_right_child && the_left_child ){
                int R_height=the_right_child->height();
                int L_height=the_left_child->height();
                if(R_height>=L_height){
                    node_height= R_height+1;
                    return ;
                }else{
                    node_height= L_height+1;
                    return ;
                }
            }else if(the_right_child){
                int R_height=the_right_child->height();
                node_height= R_height+1;
                return ;
            }else if(the_left_child){
                int L_height=the_left_child->height();
                node_height= L_height+1;
                return ;
            }else{
                node_height=0;
                return ;
            }
        }



        void updateBf(){
            if(the_right_child && the_left_child ){
                int R_height=the_right_child->height();
                int L_height=the_left_child->height();
                bf=L_height-R_height;
                return;
            }else if(the_right_child){
                int R_height=the_right_child->height();
                bf=-1-R_height;
                return ;
            }else if(the_left_child){
                int L_height=the_left_child->height();
                bf= L_height+1;
                return ;
            }else{
                bf=0;
                return ;
            }
        }



        void updateData(){
            updateheight();
            updateBf();
        }

        void updateValue()
        {
            value=nullptr;
        }





};
template<class Key,class Value>
   TreeSimpleNode<Key,Value>* RightThenLeftToTheEnd(TreeSimpleNode<Key,Value>* node){
       return LeftToTheEnd(node->GetRightChild());
   }

template<class Key,class Value>
   TreeSimpleNode<Key,Value>* LeftToTheEnd(TreeSimpleNode<Key,Value>* node){
       if(!(node->GetLeftChild())){
           return node;
       }
       return LeftToTheEnd(node->GetLeftChild()) ;
    }


template<class Key,class Value>
    TreeSimpleNode<Key,Value>* GetMin(TreeSimpleNode<Key,Value>* root){
            if(!(root->GetLeftChild())){
                return root;
            }
            return GetMin(root->GetLeftChild());
}
template<class Key,class Value>
    TreeSimpleNode<Key,Value>* GetMax(TreeSimpleNode<Key,Value>* root){
            if(!(root->GetRightChild())){
                return root;
            }
            return GetMax(root->GetRightChild());
}


template<class Key,class Value>
    void deleteNodes(TreeSimpleNode<Key,Value>* root){
        if(!root){
            return;
        }
        TreeSimpleNode<Key,Value>*  Left=root->GetLeftChild();
        TreeSimpleNode<Key,Value>*  Right=root->GetRightChild();
        deleteNodes(Left);
        deleteNodes(Right);
        delete root;
    }



template<class Key,class Value>
    bool leftOrRightChild(TreeSimpleNode<Key,Value>* child){
        TreeSimpleNode<Key,Value>* father=child->GetNodeFather();
        TreeSimpleNode<Key,Value>* L=father->GetLeftChild();
        Key key_1=child->getKey();
        if(L){
            Key key_2=L->getKey();
            if(key_1==key_2){
                return false;
            }
        }
        return true;
    }











template<class Key,class Value>
    TreeSimpleNode<Key,Value>* findTheFatherOfTheNewNode(TreeSimpleNode<Key,Value>* node,Key key){
        if(!node){
            return NULL;
        }
        if(node->getKey()>key){
            if(node->GetLeftChild()){
                return findTheFatherOfTheNewNode(node->GetLeftChild(),key);
            }else{
                return node;
            }
        }
        if(node->getKey()<key){
            if(node->GetRightChild()){
                return findTheFatherOfTheNewNode(node->GetRightChild(),key);
            }else{
                return node;
            }
        }
    return NULL;
    }


#endif


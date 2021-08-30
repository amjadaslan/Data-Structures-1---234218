

#ifndef _Doubly_List_Node
#define _Doubly_List_Node

//key=int
//val=Array<int>*

template<class key, class value>
class ListNode{
    key K;
    value Value;
    ListNode<key,value>* next;
    ListNode<key,value>* previous;

    public:

        ListNode<key,value>():next(nullptr),previous(nullptr){}
        ListNode<key,value>(key k,value v):K(k),Value(v),next(nullptr),previous(nullptr){}

        ListNode<key,value>(key k):K(k),next(nullptr),previous(nullptr){}
        /*----------------------------------------------------*/

       ~ListNode() {};

        ListNode<key,value>* GetNext(){
            return next;
        }

        ListNode<key,value>* GetPrevious(){
            return previous;
        }

        key GetKey(){
            return K;
        }
        value GetValue(){
            return Value;
        }

        void changNext(ListNode<key,value>* New){
            next=New;
        }
        void updateValue(value V){
            Value=V;
        }

        void updateKey(key Key){
            K=Key;
        }

        void changPrevious(ListNode<key,value>* New){

            previous=New;
        }



};
#endif




#ifndef LIST_H
#define LIST_H
#include "DoublyListNode.h"
#include "library.h"
#include <cstddef>


template<class key, class value>
class List{
    ListNode<key,value>* head;
    ListNode<key,value>* tail;
    int list_size;


    public:

    List<key,value>():head(nullptr),tail(nullptr),list_size(0){}

    ~List()
    {

    }


    ListNode<key,value>* GetHead(){
        return head;
    }
    ListNode<key,value>* GetTail(){
        return tail;
    }

    void removeListNode(ListNode<key,value>* node_to_delete){
        if(!node_to_delete->GetNext()&& !node_to_delete->GetPrevious()){
            delete node_to_delete;
            head=nullptr;
            tail=nullptr;
            list_size--;
            return;
        }
        ListNode<key,value>* previous=node_to_delete->GetPrevious();
        ListNode<key,value>* next=node_to_delete->GetNext();
        if(!next){
            removeTail(node_to_delete);
            return;
        }
        if(!previous){
            removeHead(node_to_delete);
            return;
        }
        next->changPrevious(previous);
        previous->changNext(next);
        delete node_to_delete;
        list_size--;
    }
    void updateHeadToNext(){
        if(head){
            head=head->GetNext();
            list_size--;
        }
    }


    void removeHead(ListNode<key,value>* Node_head){

        head=Node_head->GetNext();
        if(head!=nullptr)
        {
            head->changPrevious(nullptr);
        }
        delete Node_head;
        list_size--;
    }


    void removeTail(ListNode<key,value>* Node_tail){
        tail=Node_tail->GetPrevious();

        if(tail!=nullptr)
        {
             tail->changNext(nullptr);
        }

        delete Node_tail;
        list_size--;
    }



    ListNode<key, value>* addToList(ListNode<key,value>* node,ListNode<key,value>* Node_to_add){
            ListNode<key,value>* next=node->GetNext();
            node->changNext(Node_to_add);
            next->changPrevious(Node_to_add);
            Node_to_add->changNext(next);
            Node_to_add->changPrevious(node);
            list_size++;
            return Node_to_add;

    }


    ListNode<key, value>* addToHead(ListNode<key,value>* Node_head){
        if(!head){
            head=Node_head;
            tail=Node_head;
            list_size++;
            return Node_head;
        }
        Node_head->changNext(head);
        head->changPrevious(Node_head);
        head=Node_head;
        list_size++;
        return Node_head;
    }


    ListNode<key, value>*  addToTail(ListNode<key,value>* Node_tail){
        if(!tail){
            tail=Node_tail;
            head=Node_tail;
	Node_tail->changPrevious(nullptr);
	Node_tail->changNext(nullptr);
            list_size++;
            return Node_tail;
        }
        Node_tail->changPrevious(tail);
        tail->changNext(Node_tail);
        tail=Node_tail;
        list_size++;
        return Node_tail ;
    }



    ListNode<key, value>* find (key K)
    {
        ListNode<key,value>* temp=this->GetHead();
        while (temp!=nullptr)
        {
            if(K==temp->GetKey())
            {
                return temp;
            }
            temp=temp->GetNext();
        }
        return temp;
    }


    void DestroyList(ListNode<key, value> *head_list){
        if(!head_list){
            return;
        }
        DestroyList(head_list->GetNext());
        delete head_list;
    }
    int GetListSize()
    {
        return list_size;
    }




};
#endif


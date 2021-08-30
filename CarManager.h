
#ifndef CARMANAGER_H
#define CARMANAGER_H




#include "OldAvl.h"
#include <cstddef>
#include "library.h"
#include <iostream>
#include "DoublyList.h"
#include "OldArray.h"
#include "BestTripleKey.h"
#include "WorstTripleKey.h"
#include "NodeInfo.h"




class carManager{
    /*---------------------------feild---------------------*/
   // HashTable<int,Array<int>*>* mainhash;
  //  AVL<TripleKey,int>* views_tree;
    AVL<int,NodeInfo*>* containsZeroTree;
    AVL<int,NodeInfo*>* AllgradedTree;
    AVL<WorstTripleKey,int>* sellsTree;
    AVL<BestTripleKey,int>* gradesTree;
    int num_of_all_models;
    /*
    Courses* tree_of_courses;
    ListOfViewes* list_of_viewes;
    int size_ALL;
*/
    public:
        friend class NodeInfo;//no need
    /*---------------------------construcre---------------------*/
    /*
    courseManager():mainhash(nullptr),views_tree(nullptr)
    {
        mainhash=new HashTable<int,Array<int>*>();
        views_tree=new AVL<TripleKey,int>();
    }
    */
    carManager();


    //remove ds from parameters

    StatusType addCarType (int typeID, int numOfModels);

    StatusType removeCarType(int typeID);

    StatusType sellCar(int typeID, int modelID);

    StatusType makeComplaint(int typeID, int modelID, int t);

    StatusType getBestSellerModelByType(int typeID, int * modelID);

    StatusType getWorstModels(int numOfModels, int *types, int *models);

    void Quit();

    void GetWorst(AVL<int,NodeInfo*>* containzerosTree, AVL<BestTripleKey,int>* gradesTree,int numOfModels,int*types,int*models);

    void inorderRightCourses(Node<int,NodeInfo*>* min,int* courses,int* classes,int* i,int sizeOfArray);

    void inorderRightClasses(Node<int,int>* min ,int* courses,int* classes,int* i,int sizeOfArray);

    void inorderReverseClasses(Node<int,int>* min ,int* types,int* models,int* i,int numOfModels);

    void inorderReverseCourses(Node<int,NodeInfo*>* min ,int* types,int* models,int* i,int numOfModels);

    void inorderRightGraded(Node<BestTripleKey,int>* min ,Node<BestTripleKey,int>**stopped_node,bool*stopped,
                         int* courses,int* classes,int* i,int sizeOfArray,Node<int,NodeInfo*>* min_node_tree);

    void inorderGraded(Node<BestTripleKey,int>* min ,Node<BestTripleKey,int>**stopped_node,
                       bool*stopped,int* types,int* models,int* i,int numOfModels,Node<int,NodeInfo*>* min_node_tree);


/*
    StatusType addCourse(int courseID){

        if(courseID<=0 ){
            return INVALID_INPUT;
        }
        HASH_RESULTS res=mainhash->Insert(courseID);

        if(res==HASH_NULL_ARGUMENT)
        {
            return ALLOCATION_ERROR;
        }
        if(res==HASH_ITEM_ALREADY_EXISTS)
        {
            return FAILURE;
        }
        return SUCCESS;
    }

    StatusType RemoveCourse(int courseID){
        if(courseID<=0){
            return INVALID_INPUT;
        }
        HASH_RESULTS resu=HASH_SUCCESS;
        HASH_RESULTS *res=&resu;

        mainhash->Find(courseID,res);
        if(*res==HASH_ITEM_DOESNT_EXIST)
        {
            return FAILURE;
        }

        mainhash->Delete(courseID,views_tree);
        return SUCCESS;
    }
    StatusType AddClass(int courseID, int* classID){
        if(courseID<=0)
        {
            return INVALID_INPUT;
        }
         HASH_RESULTS resu=HASH_SUCCESS;
         HASH_RESULTS* res=&resu;

        Array<int>* curr_val=(mainhash->Find(courseID,res));
        if(*res==HASH_ITEM_DOESNT_EXIST)
        {
            return FAILURE;
        }

      //  return SUCCESS;
        (curr_val)->addNewClass();
      //  std::cout<<curr_val->getElementsNum();

        (*classID)=((curr_val)->getTop())-1;
        return SUCCESS;

    }
    StatusType WatchClass(int courseID,int classID,int time){
        if(courseID<=0 || classID<0 || time<=0 ){
            return INVALID_INPUT;
        }
        HASH_RESULTS ress=HASH_SUCCESS;
        HASH_RESULTS *res=&ress;
        Array<int>* curr_val=(mainhash->Find(courseID,res));
        if(*res==HASH_ITEM_DOESNT_EXIST)
        {
            return FAILURE;
        }
        int maxi=classID+1;
        if(maxi>(curr_val)->getTop())
        {
            return INVALID_INPUT;
        }

        TripleKey old_key((curr_val)->getViewsByPos(classID),courseID,classID);
        if((curr_val)->getViewsByPos(classID))
        {
            views_tree->removeNode(old_key);
        }

        (curr_val)->updateViewsByPos(classID,time);

        TripleKey new_key((curr_val)->getViewsByPos(classID),courseID,classID);
        int va=1;
        views_tree->insrtNodeAndbalancing(new_key,va);
        return SUCCESS;
    }
    StatusType TimeViewed(int courseID,int classID,int* timeViewed){
         if(courseID<=0 || classID<0  ){
            return INVALID_INPUT;
        }
        HASH_RESULTS ress=HASH_SUCCESS;
        HASH_RESULTS* res=&ress;
        Array<int>* curr_val=(mainhash->Find(courseID,res));
        if(*res==HASH_ITEM_DOESNT_EXIST)
        {
            return FAILURE;
        }
        int maxi=classID+1;
        if(maxi>(curr_val)->getTop())
        {
            return INVALID_INPUT;
        }
        *timeViewed=(curr_val)->getViewsByPos(classID);
        return SUCCESS;
    }
    StatusType GetIthWatchedClass(int i, int* courseID, int* classID)
    {
        int vie=1;
        int*view=&vie;
        int rank=views_tree->Getsize()+1-i;
        if(i<=0)
        {
            return INVALID_INPUT;
        }
        if(rank<=0)
        {
            return FAILURE;
        }
        Node<TripleKey,int>* tmp=views_tree->GetRoot();
        return views_tree->find_i_biggest_views(tmp,rank,courseID,classID,view);
    }
*/

};




#endif



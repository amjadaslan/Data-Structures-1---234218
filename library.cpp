


#include "library.h"
#include "CarManager.h"
#include "OldAvl.h"
#include <cstdio>
void *Init(){
    auto DS =new carManager();
    return (void*)DS;
}
 StatusType AddCarType (void *DS, int typeID, int numOfModels)//
 {

     if(!DS)
     {
         return INVALID_INPUT;
     }
     return ((carManager*)DS)->addCarType(typeID,numOfModels);
 }

StatusType RemoveCarType(void *DS, int typeID)
{

    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((carManager*)DS)->removeCarType(typeID);
}

StatusType SellCar(void*DS,int typeID, int modelID)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((carManager*)DS)->sellCar(typeID,modelID);
}

StatusType MakeComplaint(void*DS,int typeID, int modelID, int t)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((carManager*)DS)->makeComplaint(typeID,modelID,t);
}

StatusType GetBestSellerModelByType(void *DS, int typeID, int * modelID)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((carManager*)DS)->getBestSellerModelByType(typeID,modelID);
}

StatusType GetWorstModels(void *DS, int numOfModels, int *types, int *models)
{
    if(!DS)
    {
        return INVALID_INPUT;

    }
    return ((carManager*)DS)->getWorstModels(numOfModels,types,models);
}

/*
StatusType AddCourse (void *DS, int courseID){
    if(!DS){
        return INVALID_INPUT;
    }
    return ((courseManager*)DS)->addCourse(courseID);
}

StatusType RemoveCourse(void *DS, int courseID){
    if(!DS){
        return INVALID_INPUT;
    }
    return ((courseManager*)DS)->RemoveCourse(courseID);
}
StatusType AddClass(void* DS, int courseID, int* classID)
{
    if(!DS){
        return INVALID_INPUT;
    }
    return ((courseManager*)DS)->AddClass(courseID,classID);
}
StatusType WatchClass(void *DS, int courseID, int classID, int time){
    if(!DS){
        return INVALID_INPUT;
    }
    return ((courseManager*)DS)->WatchClass(courseID,classID,time);
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed){
    if(!DS){
        return INVALID_INPUT;
    }
    return ((courseManager*)DS)->TimeViewed(courseID,classID,timeViewed);
}
StatusType GetIthWatchedClass(void* DS, int i, int* courseID, int* classID){
    if(!DS){
        return INVALID_INPUT;
    }
    return ((courseManager*)DS)->GetIthWatchedClass(i,courseID,classID);
}
*/
void Quit(void** DS){
    if(!DS || !*DS){
        return;
    }
    ((carManager*)*DS)->Quit();
    delete (carManager*)*DS;
    *DS=NULL;
}

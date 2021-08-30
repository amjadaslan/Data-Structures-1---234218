
#ifndef Node_INFO_H_
#define Node_INFO_H_
#include "DoublyList.h"
//#include "CarManager.h"
#include "OldArray.h"
#include "BestTripleKey.h"
#include "TreeNode.h"
#include "WorstTripleKey.h"
#include "DoublyList.h"
#include "DoublyListNode.h"
#include "OldAvl.h"



//class carManager;

class NodeInfo
{
    int size_of_arrays;
    Array<Node<BestTripleKey,int>*>* ptrs_to_gradesTree;
    Array<Node<WorstTripleKey,int>*>* ptrs_to_sellsTree;
    AVL<WorstTripleKey,int>* ownSellsTree;
    AVL<int,int>* ownZeroGradesTree;

public:

    NodeInfo(int size_of_arrays,int typeID);
    ~NodeInfo();
    int getArraySize();
    AVL<WorstTripleKey,int>* getOwnSellsTree();
    AVL<int,int>* getOwnZerosGrade();
     void updateSellsInfo(int typeID,int modelID,AVL<WorstTripleKey,int>* BigsellsTree);
      bool updateGradesInfo(int typeID,int modelID,AVL<BestTripleKey,int>* big_grades_tree,
                            int tree_number,int points,int*alter_grade,int*alter_type,int*alter_model);
      int getNumofSells(int model);
    Array<Node<BestTripleKey,int>*>* get_ptrs_to_grades();
    Array<Node<WorstTripleKey,int>*>* get_ptrs_to_sells();



































        };
    //missing a copy ctor and  a op=






#endif // Node_INFO_H_

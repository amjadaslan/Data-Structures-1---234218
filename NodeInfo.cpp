#include "NodeInfo.h"
#include <cassert>
    NodeInfo::NodeInfo(int size_of_arrays,int typeID): size_of_arrays(size_of_arrays),ptrs_to_gradesTree(new Array<Node<BestTripleKey,int>*>(size_of_arrays)),
    ptrs_to_sellsTree(new Array<Node<WorstTripleKey,int>*>(size_of_arrays)),
    ownSellsTree(new AVL<WorstTripleKey,int>()),ownZeroGradesTree(new AVL<int,int>())
    {


        for(int i=0;i<size_of_arrays;i++)
        {
            ptrs_to_gradesTree->operator[](i)=nullptr;
            ptrs_to_sellsTree->operator[](i)=nullptr;
        }


        ownZeroGradesTree->constructCompleteTree(size_of_arrays,typeID);// on purpose !!!!!!!!!!!!!



    }
    NodeInfo::~NodeInfo()
    {


       delete ptrs_to_gradesTree;
        delete ptrs_to_sellsTree;


         Node<WorstTripleKey,int>* root=ownSellsTree->GetRoot();
         ownSellsTree->DeleteWhole(root);
         delete ownSellsTree;

        Node<int,int>* root2=ownZeroGradesTree->GetRoot();
         ownZeroGradesTree->DeleteWhole(root2);
        delete ownZeroGradesTree;

    /*
        zeroesGradesList->DestroyList(zeroesGradesList->GetHead());
        zeroesSellsList->DestroyList(zeroesSellsList->GetHead());
         delete ptrs_to_gradesList;
         delete ptrs_to_sellsList;
    */
    }
    int NodeInfo::getArraySize()
    {
        return size_of_arrays;
    }

    AVL<WorstTripleKey,int>* NodeInfo::getOwnSellsTree()
    {
        return ownSellsTree;
    }

    AVL<int,int>* NodeInfo::getOwnZerosGrade()
    {
        return ownZeroGradesTree;
    }
    int NodeInfo::getNumofSells(int model)
    {
        return ((ptrs_to_sellsTree->operator[](model))->getKey()).getSells();
    }
    Array<Node<BestTripleKey,int>*>* NodeInfo::get_ptrs_to_grades()
    {
        return ptrs_to_gradesTree;
    }
    Array<Node<WorstTripleKey,int>*>* NodeInfo::get_ptrs_to_sells()
    {
        return ptrs_to_sellsTree;
    }




 void NodeInfo::updateSellsInfo(int typeID,int modelID,AVL<WorstTripleKey,int>* BigsellsTree)
    {

        Node<WorstTripleKey,int>* curr_sells=ptrs_to_sellsTree->operator[](modelID);

        if(curr_sells==nullptr)
        {


            WorstTripleKey curr_sells_key(1,typeID,modelID);

            (BigsellsTree)->insrtNodeAndbalancing(curr_sells_key,0);
        /*
            if(typeID==3)
            {
                std::cout<<((BigsellsTree->GetRoot())->getKey()).getFirst();
                std::cout<<((BigsellsTree->GetRoot())->getKey()).getType();
                std::cout<<((BigsellsTree->GetRoot())->getKey()).getModel();
                std::cout<<(((BigsellsTree->GetRoot())->GetRightChild())->getKey()).getFirst();
                std::cout<<(((BigsellsTree->GetRoot())->GetRightChild())->getKey()).getType();
                std::cout<<(((BigsellsTree->GetRoot())->GetRightChild())->getKey()).getModel();
                 std::cout<<(((BigsellsTree->GetRoot())->GetLeftChild())->getKey()).getFirst();
                std::cout<<(((BigsellsTree->GetRoot())->GetLeftChild())->getKey()).getType();
                std::cout<<(((BigsellsTree->GetRoot())->GetLeftChild())->getKey()).getModel();

                std::cout<<BigsellsTree->Getsize();
                return;

            }
            */
            ownSellsTree->insrtNodeAndbalancing(curr_sells_key,0);

            Node<WorstTripleKey,int>* new_sells_node=(BigsellsTree)->findNode(BigsellsTree->GetRoot(),curr_sells_key);

            ptrs_to_sellsTree->operator[](modelID)=new_sells_node;

        }
        else
        {

            int curr_num_sells=(curr_sells->getKey()).getSells();
            curr_num_sells++;
            WorstTripleKey new_worst_key(curr_num_sells,typeID,modelID);

           (BigsellsTree)->removeNode(curr_sells->getKey(),(BigsellsTree)->GetRoot());
	WorstTripleKey old_worst_key(curr_num_sells-1,typeID,modelID);
           ownSellsTree->removeNode(old_worst_key,(ownSellsTree)->GetRoot());
           ptrs_to_sellsTree->operator[](modelID)=nullptr;

            (BigsellsTree)->insrtNodeAndbalancing(new_worst_key,0);
            ownSellsTree->insrtNodeAndbalancing(new_worst_key,0);
            Node<WorstTripleKey,int>* new_sells_node=(BigsellsTree)->findNode(BigsellsTree->GetRoot(),new_worst_key);

            ptrs_to_sellsTree->operator[](modelID)=new_sells_node;

        }
    }

    bool NodeInfo::updateGradesInfo(int typeID,int modelID
                                    ,AVL<BestTripleKey,int>* big_grades_tree,int tree_number,int points,int*alter_grade,int*alter_type,int*alter_model)
    {
    int curr_grade=0;
    Node<BestTripleKey,int>* curr_node=nullptr;
    if(ptrs_to_gradesTree->operator[](modelID))
    {


       curr_node=ptrs_to_gradesTree->operator[](modelID);
        BestTripleKey cuur_key=curr_node->getKey();
        curr_grade= cuur_key.getGrade();
    }


    if(curr_grade==0)
    {
        //we are in tree 1

        curr_grade+=points;
        BestTripleKey new_key(curr_grade,typeID,modelID);
        (big_grades_tree)->insrtNodeAndbalancing(new_key,0);
        Node<BestTripleKey,int>* new_grades_node=(big_grades_tree)->findNode(big_grades_tree->GetRoot(),new_key);
        ptrs_to_gradesTree->operator[](modelID)=new_grades_node;
        ownZeroGradesTree->removeNode(modelID,ownZeroGradesTree->GetRoot());

        if(ownZeroGradesTree->Getsize()==0)
        {

            return true; //move to 2
        }
        return false;



    }
    if(curr_grade!=0)
    {

        curr_grade+=points;
        if(curr_grade!=0)
        {   Node<BestTripleKey,int>* new_grades_node=(big_grades_tree)->findNode(big_grades_tree->GetRoot(),BestTripleKey(curr_grade-points,typeID,modelID));

            Node<BestTripleKey,int>* alternative_node=nullptr;
            if(new_grades_node->GetRightChild())
            {alternative_node=RightThenLeftToTheEnd(new_grades_node);}
            if(alternative_node)
            {
                BestTripleKey alter_key=alternative_node->getKey();
               *alter_grade=alter_key.getGrade();
               *alter_type=alter_key.getType();
               *alter_model=alter_key.getModel();
            }

            BestTripleKey new_key(curr_grade,typeID,modelID);
            (big_grades_tree)->removeNode(BestTripleKey(curr_grade-points,typeID,modelID),(big_grades_tree)->GetRoot());
            (big_grades_tree)->insrtNodeAndbalancing(new_key,0);
            Node<BestTripleKey,int>* new_grades_node2=(big_grades_tree)->findNode(big_grades_tree->GetRoot(),new_key);
            ptrs_to_gradesTree->operator[](modelID)=new_grades_node2;
            /*
            if(curr_grade==2)
        {
            std::cout<<big_grades_tree->Getsize()<<"\n";
            std::cout<<((big_grades_tree->GetRoot())->getKey()).getGrade()<<" ";
            std::cout<<((big_grades_tree->GetRoot())->getKey()).getType()<<" ";
            std::cout<<((big_grades_tree->GetRoot())->getKey()).getModel()<<" "<<"\n";
            std::cout<<(((big_grades_tree->GetRoot())->GetLeftChild())->getKey()).getGrade()<<" ";
            std::cout<<(((big_grades_tree->GetRoot())->GetLeftChild())->getKey()).getType()<<" ";
            std::cout<<(((big_grades_tree->GetRoot())->GetLeftChild())->getKey()).getModel()<<" "<<"\n";
            std::cout<<(((big_grades_tree->GetRoot())->GetRightChild())->getKey()).getGrade()<<" ";
            std::cout<<(((big_grades_tree->GetRoot())->GetRightChild())->getKey()).getType()<<" ";
            std::cout<<(((big_grades_tree->GetRoot())->GetRightChild())->getKey()).getModel()<<" "<<"\n";
             std::cout<<((((big_grades_tree->GetRoot())->GetLeftChild())->GetRightChild())->getKey()).getGrade()<<" ";
            std::cout<<((((big_grades_tree->GetRoot())->GetLeftChild())->GetRightChild())->getKey()).getType()<<" ";
            std::cout<<((((big_grades_tree->GetRoot())->GetLeftChild())->GetRightChild())->getKey()).getModel()<<" "<<"\n";
            std::cout<<((((big_grades_tree->GetRoot())->GetRightChild())->GetRightChild())->getKey()).getGrade()<<" ";
            std::cout<<((((big_grades_tree->GetRoot())->GetRightChild())->GetRightChild())->getKey()).getType()<<" ";
            std::cout<<((((big_grades_tree->GetRoot())->GetRightChild())->GetRightChild())->getKey()).getModel()<<" "<<"\n";



        }
        */
            return false;//???


        }
        else if(curr_grade==0)
        {
            //found is 1 or 2
                 Node<BestTripleKey,int>* new_grades_node=(big_grades_tree)->findNode(big_grades_tree->GetRoot(),
                                                                                      BestTripleKey(curr_grade-points,typeID,modelID));
            Node<BestTripleKey,int>* alternative_node=nullptr;
            if(new_grades_node->GetRightChild())
            {alternative_node=RightThenLeftToTheEnd(new_grades_node);}
            if(alternative_node)
            {
                BestTripleKey alter_key=alternative_node->getKey();
               *alter_grade=alter_key.getGrade();
               *alter_type=alter_key.getType();
               *alter_model=alter_key.getModel();
            }
                (big_grades_tree)->removeNode(BestTripleKey(curr_grade-points,typeID,modelID),(big_grades_tree)->GetRoot());
                ptrs_to_gradesTree->operator[](modelID)=nullptr;//important
                ownZeroGradesTree->insrtNodeAndbalancing(modelID,typeID);// it should not contain it beforhand
                if(tree_number==2)
                {
                    //swap trees
                    return true;
                }
                return false;

        }

    }
    return false;

}


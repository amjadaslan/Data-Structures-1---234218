
#include "CarManager.h"
#include <cassert>


    carManager::carManager():containsZeroTree(nullptr),AllgradedTree(nullptr),sellsTree(nullptr),gradesTree(nullptr),num_of_all_models(0)
    {
        containsZeroTree=new AVL<int,NodeInfo*>();
        AllgradedTree=new AVL<int,NodeInfo*>();
        sellsTree=new AVL<WorstTripleKey,int>();
        gradesTree=new AVL<BestTripleKey,int>();
    }


    StatusType carManager::addCarType (int typeID, int numOfModels)
    {
	 if(typeID<=0 || numOfModels<=0)
        {
            return INVALID_INPUT;
        }
        NodeInfo* new_info=new NodeInfo(numOfModels,typeID);
        if(new_info==nullptr)
        {
            return ALLOCATION_ERROR;
        }

        if(containsZeroTree->findNode(containsZeroTree->GetRoot(), typeID)!=nullptr)
        {
            delete new_info;
            return FAILURE;
        }
        if(AllgradedTree->findNode(AllgradedTree->GetRoot(), typeID)!=nullptr)
        {
            delete new_info;
            return FAILURE;
        }
        containsZeroTree->insrtNodeAndbalancing(typeID,new_info);
        num_of_all_models+=numOfModels;
        return SUCCESS;

    }
    StatusType carManager::removeCarType(int typeID)
    {

        if(typeID<=0)
        {
            return INVALID_INPUT;
        }
        int tree_num=0;
        AVL<int,NodeInfo*>* myWhole=nullptr;
         if(containsZeroTree->findNode(containsZeroTree->GetRoot(), typeID)!=nullptr)
         {
             tree_num=1;
            myWhole=containsZeroTree;
         }
         else if(AllgradedTree->findNode(AllgradedTree->GetRoot(), typeID)!=nullptr)
         {
             tree_num=2;
            myWhole=AllgradedTree;
         }
        if(tree_num==1 || tree_num==2)
        {

            Node<int,NodeInfo*>*found_node=myWhole->findNode(myWhole->GetRoot(), typeID);
            NodeInfo*new_info=found_node->getValue();
            num_of_all_models-=new_info->getArraySize();

            for(int i=0;i<new_info->getArraySize();i++)
            {
                Node<WorstTripleKey,int>* curr=(new_info->get_ptrs_to_sells())->operator[](i);
                if(curr!=nullptr)
                {
                    Node<WorstTripleKey,int>* alternative=nullptr;
                    WorstTripleKey alter_key(-1,-1,-1);
                    if(curr->GetRightChild())
                    {
                        alternative=RightThenLeftToTheEnd(curr);
                        alter_key=alternative->getKey();

                    }
                    sellsTree->removeNode(curr->getKey(),sellsTree->GetRoot());
                    if(alternative)
                    {
                        alternative=sellsTree->findNode(sellsTree->GetRoot(),alter_key);
                        int alter_type=alter_key.getType();
                        Node<int ,NodeInfo*>* alter_node=containsZeroTree->findNode(containsZeroTree->GetRoot(),alter_type);
                        if(alter_node==nullptr)
                        {
                            alter_node=AllgradedTree->findNode(AllgradedTree->GetRoot(),alter_type);
                        }
                        NodeInfo* alter_val=alter_node->getValue();
                        Array<Node<WorstTripleKey,int>*>* alter_ptrs_to_sells= alter_val->get_ptrs_to_sells();
                        alternative=sellsTree->findNode(sellsTree->GetRoot(),alter_key);
                        alter_ptrs_to_sells->operator[](alter_key.getModel())=alternative;
                    }

                }
            }

            for(int i=0;i<new_info->getArraySize();i++)
            {

                Node<BestTripleKey,int>* curr2=(new_info->get_ptrs_to_grades())->operator[](i);
                if(curr2!=nullptr)
                {
                    Node<BestTripleKey,int>* alternative2=nullptr;
                    BestTripleKey alter2_key(-1,-1,-1);
                    if(curr2->GetRightChild())
                    {
                        alternative2=RightThenLeftToTheEnd(curr2);
                        alter2_key=alternative2->getKey();
                    }
                    gradesTree->removeNode(curr2->getKey(),gradesTree->GetRoot());
                    if(alternative2)
                    {
                        alternative2=gradesTree->findNode(gradesTree->GetRoot(),alter2_key);
                        int alter2_type=alter2_key.getType();
                        Node<int ,NodeInfo*>* alter_node2=containsZeroTree->findNode(containsZeroTree->GetRoot(),alter2_type);
                        if(alter_node2==nullptr)
                        {
                            alter_node2=AllgradedTree->findNode(AllgradedTree->GetRoot(),alter2_type);
                        }
                        NodeInfo* alter2_val=alter_node2->getValue();
                        Array<Node<BestTripleKey,int>*>* alter_ptrs_to_grade= alter2_val->get_ptrs_to_grades();
                        alternative2=gradesTree->findNode(gradesTree->GetRoot(),alter2_key);
                        alter_ptrs_to_grade->operator[](alter2_key.getModel())=alternative2;
                    }
                }
            }









                delete new_info;
                myWhole->removeNode(typeID,myWhole->GetRoot());
                //  delete found_node;
                return SUCCESS;



            }






        return FAILURE;
    }
    StatusType carManager::sellCar(int typeID, int modelID)
    {

        int x=-1;
        int y=-1;
        int z=-1;
        if( typeID <=0 || modelID<0)
        {
            return INVALID_INPUT;
        }
        AVL<int,NodeInfo*>* MyTree=nullptr;
        AVL<int,NodeInfo*>* TheotherTree=nullptr;
        Node<int,NodeInfo*>* found_node=containsZeroTree->findNode(containsZeroTree->GetRoot(),typeID);
        NodeInfo*new_info=nullptr;
        if(found_node)
        {
            MyTree=containsZeroTree;
            TheotherTree=AllgradedTree;
        }
        if(found_node==nullptr)
        {
           found_node=AllgradedTree->findNode(AllgradedTree->GetRoot(),typeID);
           if(found_node)
           {
               MyTree=AllgradedTree;
               TheotherTree=containsZeroTree;
           }
           else{return FAILURE;}
        }


            new_info=found_node->getValue();//make sure it gets the original
            if(new_info->getArraySize()<=modelID)
            {
                return FAILURE;
            }
            //update sells part
            NodeInfo* found_node_value=found_node->getValue();
            int curr_sells=0;
            if(((found_node_value->get_ptrs_to_sells())->operator[](modelID)))
            {
                curr_sells+=(((found_node_value->get_ptrs_to_sells())->operator[](modelID))->getKey()).getSells();
            }
            Node<WorstTripleKey,int>* alter_node=nullptr;
            WorstTripleKey alter_sell_key(-1,-1,-1);
            int alter_sells=-1;
            int alter_type=-1;
            int alter_model=-1;
            if(curr_sells!=0)
            {
                alter_node=sellsTree->findNode(sellsTree->GetRoot(),WorstTripleKey(curr_sells,typeID,modelID));
                if(alter_node->GetRightChild())
                {
                    alter_node=RightThenLeftToTheEnd(alter_node);//might cause trouble!
                    alter_sells=(alter_node->getKey()).getSells();
                    alter_type=(alter_node->getKey()).getType();
                    alter_model=(alter_node->getKey()).getModel();
                }
                else{alter_node=nullptr;}
            }
            new_info->updateSellsInfo(typeID,modelID,sellsTree);
            if(alter_sells!=-1)
            {
                        alter_sell_key=WorstTripleKey(alter_sells,alter_type,alter_model);
                        alter_node=sellsTree->findNode(sellsTree->GetRoot(),alter_sell_key);
                        Node<int ,NodeInfo*>* contain_alter_node=MyTree->findNode(MyTree->GetRoot(),alter_type);
                        if(contain_alter_node==nullptr)
                        {
                            contain_alter_node=TheotherTree->findNode(TheotherTree->GetRoot(),alter_type);
                        }
	  
                        NodeInfo* alter_val=contain_alter_node->getValue();
                        Array<Node<WorstTripleKey,int>*>* alter_ptrs_to_sells= alter_val->get_ptrs_to_sells();
                        alter_node=sellsTree->findNode(sellsTree->GetRoot(),alter_sell_key);
                        alter_ptrs_to_sells->operator[](alter_sell_key.getModel())=alter_node;


            }


	int param=2;
            if (MyTree==containsZeroTree){param=1;}
            if(new_info->updateGradesInfo(typeID,modelID,gradesTree,param,10,&x,&y,&z))
            {

                if(y!=-1)
                {

                    BestTripleKey should_fix(x,y,z);
                    Node<int,NodeInfo*>* found_node=MyTree->findNode(MyTree->GetRoot(),y);
 		if(found_node==nullptr)
                    {
                        found_node=TheotherTree->findNode(TheotherTree->GetRoot(),y);
                    }
                    NodeInfo*new_info=found_node->getValue();
                    (new_info->get_ptrs_to_grades())->operator[](z)=gradesTree->findNode(gradesTree->GetRoot(),should_fix);
                }

                Node<int,NodeInfo*>* need_to_delete=
                (MyTree)->findNode((MyTree)->GetRoot(),typeID);
                NodeInfo* the_copied_value=need_to_delete->getValue();
                need_to_delete->updateValue();
                assert(the_copied_value!=nullptr);
                MyTree->removeNode(typeID,MyTree->GetRoot());//maybe_needs_to Ds->
                TheotherTree->insrtNodeAndbalancing(typeID,the_copied_value);

            }
             if(y!=-1)
                {
                   // Node<int,NodeInfo*>* found_node11=containsZeroTree->findNode(containsZeroTree->GetRoot(),3);
                  //  NodeInfo*new_info11=found_node11->getValue();
                  //  assert( (new_info11->get_ptrs_to_grades())->operator[](4)==nullptr);
                    BestTripleKey should_fix(x,y,z);
                    Node<int,NodeInfo*>* found_node=MyTree->findNode(MyTree->GetRoot(),y);
 		if(found_node==nullptr)
                    {
                        found_node=TheotherTree->findNode(TheotherTree->GetRoot(),y);
                    }
                    NodeInfo*new_info=found_node->getValue();
                    (new_info->get_ptrs_to_grades())->operator[](z)=gradesTree->findNode(gradesTree->GetRoot(),should_fix);

                }
            /*
            if(typeID==73 && modelID==1)
            {
                if(gradesTree->Getsize()==4)
                {
                std::cout<<((gradesTree->GetRoot())->getKey()).getGrade()<<"\n";
                std::cout<<((gradesTree->GetRoot())->getKey()).getType()<<"\n";
                std::cout<<((gradesTree->GetRoot())->getKey()).getModel()<<"\n";
                 std::cout<<(((gradesTree->GetRoot())->GetRightChild())->getKey()).getGrade()<<"\n";
                 std::cout<<(((gradesTree->GetRoot())->GetRightChild())->getKey()).getType()<<"\n";
                 std::cout<<(((gradesTree->GetRoot())->GetRightChild())->getKey()).getModel()<<"\n";
                  std::cout<<(((gradesTree->GetRoot())->GetLeftChild())->getKey()).getGrade()<<"\n";
                 std::cout<<(((gradesTree->GetRoot())->GetLeftChild())->getKey()).getType()<<"\n";
                 std::cout<<(((gradesTree->GetRoot())->GetLeftChild())->getKey()).getModel()<<"\n";
                 std::cout<<((((gradesTree->GetRoot())->GetRightChild())->GetRightChild())->getKey()).getGrade()<<"\n";
                 std::cout<<((((gradesTree->GetRoot())->GetRightChild())->GetRightChild())->getKey()).getType()<<"\n";
                 std::cout<<((((gradesTree->GetRoot())->GetRightChild())->GetRightChild())->getKey()).getModel()<<"\n";



                  Node<int,NodeInfo*>* found_node1=containsZeroTree->findNode(containsZeroTree->GetRoot(),70);
                    NodeInfo*new_info1=found_node1->getValue();//make sure it gets the original
                    std::cout<<(((new_info1->get_ptrs_to_grades())->operator[](1))->getKey()).getGrade();

                    Node<int,NodeInfo*>* found_node2=containsZeroTree->findNode(containsZeroTree->GetRoot(),71);
                    NodeInfo*new_info2=found_node2->getValue();//make sure it gets the original
                    std::cout<<(((new_info2->get_ptrs_to_grades())->operator[](1))->getKey()).getGrade();

                    Node<int,NodeInfo*>* found_node3=containsZeroTree->findNode(containsZeroTree->GetRoot(),72);
                    NodeInfo*new_info3=found_node3->getValue();//make sure it gets the original
                    std::cout<<(((new_info3->get_ptrs_to_grades())->operator[](1))->getKey()).getGrade();

                    Node<int,NodeInfo*>* found_node4=containsZeroTree->findNode(containsZeroTree->GetRoot(),73);
                    NodeInfo*new_info4=found_node4->getValue();//make sure it gets the original
                    std::cout<<(((new_info4->get_ptrs_to_grades())->operator[](1))->getKey()).getGrade();
                }
             //   std::cout<<gradesTree->Getsize()<<"\n";


            }
            */


          //  if(typeID==70||typeID==71||typeID==72||typeID==73)
          //  std::cout<<(((new_info->get_ptrs_to_grades())->operator[](1))->getKey()).getType()<<"kkkk";



            return SUCCESS;




        //element not found in neither trees
    }


    StatusType carManager::makeComplaint(int typeID, int modelID, int t)
    //beware of allgraded/containszero
    {
    /*
        if(t==12)
        {
            std::cout<<gradesTree->Getsize()<<"\n";
            std::cout<<((gradesTree->GetRoot())->getKey()).getGrade()<<" ";
            std::cout<<((gradesTree->GetRoot())->getKey()).getType()<<" ";
            std::cout<<((gradesTree->GetRoot())->getKey()).getModel()<<" "<<"\n";
            std::cout<<(((gradesTree->GetRoot())->GetLeftChild())->getKey()).getGrade()<<" ";
            std::cout<<(((gradesTree->GetRoot())->GetLeftChild())->getKey()).getType()<<" ";
            std::cout<<(((gradesTree->GetRoot())->GetLeftChild())->getKey()).getModel()<<" "<<"\n";
            std::cout<<(((gradesTree->GetRoot())->GetRightChild())->getKey()).getGrade()<<" ";
            std::cout<<(((gradesTree->GetRoot())->GetRightChild())->getKey()).getType()<<" ";
            std::cout<<(((gradesTree->GetRoot())->GetRightChild())->getKey()).getModel()<<" "<<"\n";
             std::cout<<((((gradesTree->GetRoot())->GetLeftChild())->GetLeftChild())->getKey()).getGrade()<<" ";
            std::cout<<((((gradesTree->GetRoot())->GetLeftChild())->GetLeftChild())->getKey()).getType()<<" ";
            std::cout<<((((gradesTree->GetRoot())->GetLeftChild())->GetLeftChild())->getKey()).getModel()<<" "<<"\n";
            std::cout<<((((gradesTree->GetRoot())->GetRightChild())->GetRightChild())->getKey()).getGrade()<<" ";
            std::cout<<((((gradesTree->GetRoot())->GetRightChild())->GetRightChild())->getKey()).getType()<<" ";
            std::cout<<((((gradesTree->GetRoot())->GetRightChild())->GetRightChild())->getKey()).getModel()<<" "<<"\n";



        }*/

        if(typeID <=0 || modelID<0)
        {
            return INVALID_INPUT;
        }
        Node<int,NodeInfo*>* found_node=containsZeroTree->findNode(containsZeroTree->GetRoot(),typeID);
        NodeInfo*new_info=nullptr;
        if(found_node)
        {
            new_info=found_node->getValue();//make sure it gets the original
            if(new_info->getArraySize()<=modelID)
            {
                return FAILURE;
            }
            int x=-1;
            int y=-1;
            int z=-1;
            if(new_info->updateGradesInfo(typeID,modelID,gradesTree,1,-100/t,&x,&y,&z))
            {
                if(y!=-1)
                {

                    BestTripleKey should_fix(x,y,z);
                    Node<int,NodeInfo*>* found_node=containsZeroTree->findNode(containsZeroTree->GetRoot(),y);
	       if(found_node==nullptr)
                    {
                        found_node=AllgradedTree->findNode(AllgradedTree->GetRoot(),y);
                    }
                    NodeInfo*new_info=found_node->getValue();
                    (new_info->get_ptrs_to_grades())->operator[](z)=gradesTree->findNode(gradesTree->GetRoot(),should_fix);
                }
                Node<int,NodeInfo*>* need_to_delete=
                (containsZeroTree)->findNode((containsZeroTree)->GetRoot(),typeID);
                NodeInfo* the_copied_value=need_to_delete->getValue();
                need_to_delete->updateValue();
                assert(the_copied_value!=nullptr);
                containsZeroTree->removeNode(typeID,containsZeroTree->GetRoot());//maybe_needs_to Ds->
                AllgradedTree->insrtNodeAndbalancing(typeID,the_copied_value);

            }

                if(y!=-1)
                {
                    BestTripleKey should_fix(x,y,z);
                    Node<int,NodeInfo*>* found_node=containsZeroTree->findNode(containsZeroTree->GetRoot(),y);
 	      if(found_node==nullptr)
                    {
                        found_node=AllgradedTree->findNode(AllgradedTree->GetRoot(),y);
                    }
                    NodeInfo*new_info=found_node->getValue();
                    (new_info->get_ptrs_to_grades())->operator[](z)=gradesTree->findNode(gradesTree->GetRoot(),should_fix);
                }

           return SUCCESS;

        }

        found_node=AllgradedTree->findNode(AllgradedTree->GetRoot(),typeID);
        if(found_node)
        {
            int a=-1;
            int b=-1;
            int c=-1;
            new_info=found_node->getValue();
            if(new_info->getArraySize()<=modelID)
            {
                return FAILURE;
            }
             if(new_info->updateGradesInfo(typeID,modelID,gradesTree,2,-100/t,&a,&b,&c))//1
            {
                if(b!=-1)
                {
                    BestTripleKey should_fix(a,b,c);
                    Node<int,NodeInfo*>* found_node=AllgradedTree->findNode(AllgradedTree->GetRoot(),b);
	       if(found_node==nullptr)
                    {
                        found_node=containsZeroTree->findNode(containsZeroTree->GetRoot(),b);
                    }
                    NodeInfo*new_info=found_node->getValue();
                    (new_info->get_ptrs_to_grades())->operator[](c)=gradesTree->findNode(gradesTree->GetRoot(),should_fix);
                }
                Node<int,NodeInfo*>* need_to_delete=
                (AllgradedTree)->findNode((AllgradedTree)->GetRoot(),typeID);
                NodeInfo* the_copied_value=need_to_delete->getValue();
              //  Node<int,NodeInfo*>* new_element=new Node<int,NodeInfo*>(typeID,the_copied_value);
                need_to_delete->updateValue();
              //  assert(new_element->getValue()!=nullptr);
                assert(the_copied_value!=nullptr);
                AllgradedTree->removeNode(typeID,AllgradedTree->GetRoot());//maybe_needs_to Ds->
                containsZeroTree->insrtNodeAndbalancing(typeID,the_copied_value);
            }
            if(b!=-1)
                {
                    BestTripleKey should_fix(a,b,c);
                    Node<int,NodeInfo*>* found_node=AllgradedTree->findNode(AllgradedTree->GetRoot(),b);
	      if(found_node==nullptr)
                    {
                        found_node=containsZeroTree->findNode(containsZeroTree->GetRoot(),b);
                    }
                    NodeInfo*new_info=found_node->getValue();
                    (new_info->get_ptrs_to_grades())->operator[](c)=gradesTree->findNode(gradesTree->GetRoot(),should_fix);
                }


            return SUCCESS;
        }

        return FAILURE;//element not found in neither trees
    }
    StatusType carManager::getBestSellerModelByType(int typeID, int * modelID)
    {
        //don't forget to update max , min node in the completed tree!
        //remove ds from parameters later
        if(typeID<0)
        {
            return INVALID_INPUT;
        }
        if(typeID==0)
        {
            AVL<int,NodeInfo*>* first_tree=containsZeroTree;
            AVL<int,NodeInfo*>* second_tree=AllgradedTree;
            if(first_tree->Getsize()==0 && second_tree->Getsize()==0)
            {
                return FAILURE;
            }
            Node<WorstTripleKey,int>* max_node=sellsTree->GetMaxNode();
            /*
            std::cout<<((sellsTree->GetMaxNode())->getKey()).getModel()<<"\n";
            std::cout<<((sellsTree->GetMaxNode())->getKey()).getType()<<"\n";
            std::cout<<((sellsTree->GetMaxNode())->getKey()).getSells()<<"\n";
            */
            if(max_node==nullptr)
            {
                assert(sellsTree->Getsize()==0);
                *modelID=0;
                return SUCCESS;
            }
            WorstTripleKey max_node_key=max_node->getKey();
            int result=max_node_key.getModel();
            *modelID=result;
            return SUCCESS;

        }
        Node<int,NodeInfo*>* curr_node=containsZeroTree->findNode(containsZeroTree->GetRoot(),typeID);
        NodeInfo* curr_node_value=nullptr;
        AVL<WorstTripleKey,int>* explicit_sells=nullptr;
        Node<WorstTripleKey,int>* max_node=nullptr;
        if(curr_node==nullptr)
        {
            curr_node=AllgradedTree->findNode(AllgradedTree->GetRoot(),typeID);
        }
        if(curr_node!=nullptr)
        {
            curr_node_value=curr_node->getValue();
            explicit_sells=curr_node_value->getOwnSellsTree();
            if(explicit_sells->Getsize()==0)
            {
                *modelID=0;
                return SUCCESS;
            }
            max_node=explicit_sells->GetMaxNode();
            WorstTripleKey max_node_key=max_node->getKey();
            *modelID=max_node_key.getModel();
            return SUCCESS;

        }
        //type_id is invalid!
        return FAILURE;


    }

    StatusType carManager::getWorstModels(int numOfModels, int *types, int *models)
    {


        if(numOfModels<=0)
        {
            return INVALID_INPUT;
        }
        if(num_of_all_models<numOfModels)
        {
            return FAILURE;
        }
            /*
            std::cout<<gradesTree->Getsize()<<"\n";
            std::cout<<((gradesTree->GetRoot())->getKey()).getGrade()<<" ";
            std::cout<<((gradesTree->GetRoot())->getKey()).getType()<<" ";
            std::cout<<((gradesTree->GetRoot())->getKey()).getModel()<<" "<<"\n";
            std::cout<<(((gradesTree->GetRoot())->GetLeftChild())->getKey()).getGrade()<<" ";
            std::cout<<(((gradesTree->GetRoot())->GetLeftChild())->getKey()).getType()<<" ";
            std::cout<<(((gradesTree->GetRoot())->GetLeftChild())->getKey()).getModel()<<" "<<"\n";
            std::cout<<(((gradesTree->GetRoot())->GetRightChild())->getKey()).getGrade()<<" ";
            std::cout<<(((gradesTree->GetRoot())->GetRightChild())->getKey()).getType()<<" ";
            std::cout<<(((gradesTree->GetRoot())->GetRightChild())->getKey()).getModel()<<" "<<"\n";
            std::cout<<((((gradesTree->GetRoot())->GetLeftChild())->GetRightChild())->getKey()).getGrade()<<" ";
            std::cout<<((((gradesTree->GetRoot())->GetLeftChild())->GetRightChild())->getKey()).getType()<<" ";
            std::cout<<((((gradesTree->GetRoot())->GetLeftChild())->GetRightChild())->getKey()).getModel()<<" "<<"\n";
            std::cout<<((((gradesTree->GetRoot())->GetRightChild())->GetRightChild())->getKey()).getGrade()<<" ";
            std::cout<<((((gradesTree->GetRoot())->GetRightChild())->GetRightChild())->getKey()).getType()<<" ";
            std::cout<<((((gradesTree->GetRoot())->GetRightChild())->GetRightChild())->getKey()).getModel()<<" "<<"\n";
            */

        GetWorst(containsZeroTree,gradesTree,numOfModels,types,models);
        return SUCCESS;
    }

    //third
void carManager::inorderRightCourses(Node<int,NodeInfo*>* min,int* courses,int* classes,int* i,int sizeOfArray){
if(!min){
    return;
}
inorderRightCourses(min->GetLeftChild(),courses,classes,i,sizeOfArray);
if(*i>=sizeOfArray){
    return;
}
NodeInfo* min_node_info=min->getValue();
AVL<int,int>*small_avl=min_node_info->getOwnZerosGrade();
Node<int,int>* min_in_small_tree=small_avl->GetMinNode();
inorderReverseClasses(min_in_small_tree , courses,classes, i,sizeOfArray);
inorderRightCourses(min->GetRightChild(),courses,classes,i,sizeOfArray);
}


//fourth
 void carManager::inorderRightClasses(Node<int,int>* min ,int* courses,int* classes,int* i,int sizeOfArray){
        if(!min){
            return;
        }
        inorderRightClasses(min->GetLeftChild(),courses,classes,i,sizeOfArray);
        if(*i>=sizeOfArray){
            return;
        }
        courses[*i]=min->getValue();
        classes[*i]=min->getKey();
        (*i)++;
        inorderRightClasses(min->GetRightChild(),courses,classes,i,sizeOfArray);
     }

    //second
void carManager::inorderReverseClasses(Node<int,int>* min ,int* types,int* models,int* i,int numOfModels){
        if(!min){
            return;
        }
        if(*i>=numOfModels){
            return;
        }
        types[*i]=min->getValue();
        models[*i]=min->getKey();
        (*i)++;
       inorderRightClasses(min->GetRightChild(),types,models,i,numOfModels);
       inorderReverseClasses(min->GetNodeFather(),types,models,i,numOfModels);
    }

//first
void carManager::inorderReverseCourses(Node<int,NodeInfo*>* min ,int* types,int* models,int* i,int numOfModels){
if(!min){
    return;
}
if(*i>=numOfModels){
    return;
}
NodeInfo* min_node_info=min->getValue();
AVL<int,int>*small_avl=min_node_info->getOwnZerosGrade();
Node<int,int>* min_in_small_tree=small_avl->GetMinNode();

inorderReverseClasses(min_in_small_tree,types, models,i, numOfModels);
inorderRightCourses(min->GetRightChild(),types, models,i, numOfModels);
inorderReverseCourses(min->GetNodeFather(),types,models,i,numOfModels);
}

//sixth
 void carManager::inorderRightGraded(Node<BestTripleKey,int>* min ,Node<BestTripleKey,int>**stopped_node,bool*stopped,
                                     int* courses,int* classes,int* i,int sizeOfArray,Node<int,NodeInfo*>* min_node_tree){
        if(!min){
            return;
        }
        inorderRightGraded(min->GetLeftChild(),stopped_node,stopped,courses,classes,i,sizeOfArray,min_node_tree);
        if(*i>=sizeOfArray){
            return;
        }
        int my_grade=(min->getKey()).getGrade();
        int my_type=(min->getKey()).getType();
        int my_model=(min->getKey()).getModel();
        if(my_grade>0)
        {
            if((*stopped)==false)
            {
                 inorderReverseCourses(min_node_tree,courses,classes,i,sizeOfArray);
                *stopped_node=min;
                *(*stopped_node)=*min;
                *stopped=true;
              //  return;
            }
        }
        if(*i>=sizeOfArray){
            return;
        }
        courses[*i]=my_type;
        classes[*i]=my_model;
        (*i)++;
        inorderRightGraded(min->GetRightChild(),stopped_node,stopped,courses,classes,i,sizeOfArray,min_node_tree);
     }
//fifth
void carManager::inorderGraded(Node<BestTripleKey,int>* min ,Node<BestTripleKey,int>**stopped_node,
                               bool*stopped,int* types,int* models,int* i,int numOfModels,Node<int,NodeInfo*>* min_node_tree){

        if(!min){
            return;
        }
        if(*i>=numOfModels){
            return;
        }
        int my_grade=(min->getKey()).getGrade();
        int my_type=(min->getKey()).getType();
        int my_model=(min->getKey()).getModel();
        if(my_grade>0)
        {

            if((*stopped)==false)
            {
                inorderReverseCourses(min_node_tree,types,models,i,numOfModels);
                *stopped_node=min;
                *(*stopped_node)=*min;
                *stopped=true;
              //  return;
            }
        }
        if(*i>=numOfModels){
            return;
        }
        types[*i]=my_type;
        models[*i]=my_model;
        (*i)++;
       inorderRightGraded(min->GetRightChild(),stopped_node,stopped,types,models,i,numOfModels,min_node_tree);
       inorderGraded(min->GetNodeFather(),stopped_node,stopped,types,models,i,numOfModels,min_node_tree);
    }

 void carManager::GetWorst(AVL<int,NodeInfo*>* containzerosTree, AVL<BestTripleKey,int>* gradesTree,int numOfModels,int*types,int*models)
 {
    /*std::cout<< containzerosTree->Getsize()<<"first";
     std::cout<<gradesTree->Getsize()<<"second";
     return;*/
      int i=0;
      bool stopped=false;
      bool stopped2=true;
      Node<BestTripleKey,int>* stopped_node=nullptr;
      Node<int,NodeInfo*>* min_node_tree=containzerosTree->GetMinNode();
      Node<BestTripleKey,int>* min_graded_element=gradesTree->GetMinNode();
     /* std::cout<<(min_graded_element->getKey()).getGrade()<<"\n";
      std::cout<<(min_graded_element->getKey()).getType()<<"\n";
      std::cout<<(min_graded_element->getKey()).getModel()<<"\n";*/


       // while(i<sizeOfArray){


            inorderGraded(min_graded_element,&stopped_node,&stopped,types,models,&i,numOfModels,containzerosTree->GetMinNode());

            // i is updated?
           // assert(stopped_node);
            if(i<numOfModels)
            inorderReverseCourses(min_node_tree,types,models,&i,numOfModels);//this is for the zeros

            //std::cout<<(stopped_node->getKey()).getType();
            if(i<numOfModels)
            inorderGraded(stopped_node,&stopped_node,&stopped2,types,models,&i,numOfModels,containzerosTree->GetMinNode());


            assert(i==numOfModels);







            /*
            head=head->GetNext();
            if(head){
            TreeinTree* tree=head->GetValue();
            min=tree->getMin();
            }else{
                return;
            }
            */
    //    }
        return;


}




    void carManager::Quit(){


     Node<int,NodeInfo*>* root1=containsZeroTree->GetRoot();
            containsZeroTree->DeleteComplexWhole(root1);
     delete containsZeroTree;

    Node<int,NodeInfo*>* root2=AllgradedTree->GetRoot();
            AllgradedTree->DeleteComplexWhole(root2);
        delete AllgradedTree;

    Node<WorstTripleKey,int>* root3=sellsTree->GetRoot();
            sellsTree->DeleteWhole(root3);
        delete sellsTree;

    Node<BestTripleKey,int>* root4=gradesTree->GetRoot();
            gradesTree->DeleteWhole(root4);
        delete gradesTree;

    }

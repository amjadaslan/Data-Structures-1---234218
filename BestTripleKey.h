

#ifndef Best_Triple_h
#define Best_Triple_h





class BestTripleKey
{
    int grade;
    int type_id;
    int model_id;
    public:
        BestTripleKey(int grade,int type_id,int model_id):
            grade(grade),type_id(type_id),model_id(model_id)
        {

        }
        int getGrade()
        {
            return grade;
        }
        int getType()
        {
            return type_id;
        }
        int getModel()
        {
            return model_id;
        }
        int getFirst()
        {
            return grade;
        }
        void updateFirst(int g)
        {
            grade=g;
        }
        void updateSecond(int type)
        {
            type_id=type;
        }
        void updateThird(int model)
        {
            model_id=model;
        }
        void updateKey(BestTripleKey c)
        {
            grade=c.grade;
            type_id=c.type_id;
            model_id=c.model_id;
        }
        BestTripleKey& operator=(BestTripleKey c){
            grade=c.grade;
            type_id=c.type_id;
            model_id=c.model_id;
            return *this;
        }
/*
        BestTripleKey(const BestTripleKey& c)
        {
            grade=8734;
            type_id=8734856;
            model_id=0;
        }
        */

        //BE CAREFUL TO SIGN
friend bool operator<(BestTripleKey tk1, BestTripleKey tk2){
    if(tk1.getGrade()<tk2.getGrade())
    {
        return true;
    }
    if(tk1.getGrade()>tk2.getGrade())
    {
        return false;
    }
    if(tk1.getType()<tk2.getType())
    {
        return true;
    }
    if(tk1.getType()>tk2.getType())
    {
        return false;
    }
    if(tk1.getModel()<tk2.getModel())
    {
        return true;
    }
    else{return false;}
}
friend bool operator>(BestTripleKey tk1, BestTripleKey tk2){
    if(tk1.getGrade()>tk2.getGrade())
    {
        return true;
    }
    if(tk1.getGrade()<tk2.getGrade())
    {
        return false;
    }
    if(tk1.getType()>tk2.getType())
    {
        return true;
    }
    if(tk1.getType()<tk2.getType())
    {
        return false;
    }
    if(tk1.getModel()>tk2.getModel())
    {
        return true;
    }
    else{return false;}
}
friend bool operator==(BestTripleKey tk1, BestTripleKey tk2){
    if(tk1.getGrade()!=tk2.getGrade())
    {
        return false;
    }

    if(tk1.getType()!=tk2.getType())
    {
        return false;
    }

    if(tk1.getModel()!=tk2.getModel())
    {
        return false;
    }
    else{return true;}
}


};

















#endif // Triple_h



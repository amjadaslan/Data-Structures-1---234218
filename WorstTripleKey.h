


#ifndef Worst_Triple_h
#define Worst_Triple_h





class WorstTripleKey
{
    int sells;
    int type_id;
    int model_id;
    public:
        WorstTripleKey(int sells,int type_id,int model_id):
            sells(sells),type_id(type_id),model_id(model_id)
        {

        }
        int getSells()
        {
            return sells;
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
            return sells;
        }
          void updateFirst(int g)
        {
            sells=g;
        }
        void updateSecond(int type)
        {
            type_id=type;
        }
        void updateThird(int model)
        {
            model_id=model;
        }
           void updateKey(WorstTripleKey c)
        {
            sells=c.sells;
            type_id=c.type_id;
            model_id=c.model_id;
        }
        WorstTripleKey& operator=(WorstTripleKey c){
            sells=c.sells;
            type_id=c.type_id;
            model_id=c.model_id;
            return *this;
        }
        //BE CAREFUL TO SIGN
friend bool operator<(WorstTripleKey tk1, WorstTripleKey tk2){
    if(tk1.getSells()<tk2.getSells())
    {
        return true;
    }
    if(tk1.getSells()>tk2.getSells())
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
friend bool operator>(WorstTripleKey tk1, WorstTripleKey tk2){
    if(tk1.getSells()>tk2.getSells())
    {
        return true;
    }
    if(tk1.getSells()<tk2.getSells())
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
friend bool operator==(WorstTripleKey tk1, WorstTripleKey tk2){
    if(tk1.getSells()!=tk2.getSells())
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

#endif


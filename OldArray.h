
#ifndef HELPER_ARRAY_H_
#define HELPER_ARRAY_H_

#include <iostream>


template <class T>
 class Array
 {
     private:

     int array_size;
     T*new_array;
     int top;

     public:

     Array(int array_size);
     ~Array();
     Array(const Array& a):

        new_array(new T[a.array_size]),
         array_size(a.array_size),
         top(a.top)
         {
             for(int i=0;i<array_size;i++)
             {
                 new_array[i]=a.new_array[i];
             }
         }

     Array<T>& operator=(const Array<T>& a)
     {

        if(this==&a)
        {
            return *this;
        }

        delete [] new_array;
        new_array=new T[a.array_size];
        top=a.top;//////////////////////////////////////
        array_size=a.array_size;
        for(int i=0;i<array_size;i++)
        {
            new_array[i]=(a.new_array)[i];
        }
        return *this;
     }
     T& operator[](int index)const;
     T*begin();
     T*end();
     void resizeArray();
     void updateTop();
     void update(const Array<T>& new_table);
     int getTop()const
     {
         return top;
     }
     int getArraysize()
     {
         return array_size;
     }
     void addNewClass()
     {

         new_array[top]=0;

        top++;
        this->resizeArray();
     }
     T getViewsByPos(int i)
     {
         return new_array[i];
     }
     void updateViewsByPos(int pos,int views)
     {
         new_array[pos]+=views;
     }
     T* getNewArray()const
     {
         return new_array;
     }

 };


template<class T>
Array<T>::Array(int array_size):array_size(array_size),new_array(new T[array_size]()),top(0)
{

}
template<class T>
Array<T>::~Array()
{
    delete [] new_array;
}
template<class T>
T& Array<T>::operator[](int index)const
{
    return new_array[index];
}
template<class T>
T* Array<T>::begin()
{
         return new_array;
}
template<class T>
T* Array<T>::end()
{
         return new_array+array_size;
}

template<class T>
void Array<T>::resizeArray()
{
    if(array_size==(top+1))
    {
        T*big_array=new T[array_size*2]();
        for(int i=0;i<top;i++)
        {
            big_array[i]=new_array[i];
        }
        delete [] new_array;
        array_size*=2;
        new_array=big_array;

    }
}

template<class T>
void Array<T>::updateTop()
{
    top++;
}


#endif // HELPER_ARRAY_H_





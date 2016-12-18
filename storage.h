#ifndef STORAGE_H
#define STORAGE_H


#include <iostream>
#include <string>


template<class T>
class Storage
{
protected:
    T* array;
    int size;
    int count;
public:
    Storage(int n=10);
    Storage(const Storage& copy);
    ~Storage();
    void clear();
    T Delete(int n);
    bool Delete(const T &object);
    Storage& operator=(const Storage& copy);
    T& operator[](int i);
    void Add(const T &object);
    int Get_count() const
    {
        return count;
    }
    int Get_size() const
    {
        return size;
    }

private:
    void Resize();

};

template<class T>
class Ex_storage :public Storage<T>
{
public:
    Storage<T> selected_items;
    Ex_storage(int n =10):Storage<T>(n)
    {

    }

};


template<class T>
Storage<T>::Storage(int n)  //n=10 by default
{
    array = new T[n];
    count = 0;
    size = n;
}

template<class T>
Storage<T>::Storage(const Storage& copy)
{
    array = new T[copy.size];
    size = copy.size;
    count = 0;
//    count = copy.count;
    for (int i = 0; i < copy.count; ++i)
    {
        this->Add(copy.array[i]);
    }
}

template<class T>
Storage<T>::~Storage()
{
    if (array != nullptr)
        delete[] array;
}

template<class T>
void Storage<T>::clear()
{
   count = 0;
}

template<class T>
T Storage<T>::Delete(int n)
{
    if ((n < 0) || (n >= count))
    {
        throw;
    }
    T ptr = array[n];

    if (n == count-1)
    {
        --count;
        return ptr;
    }

    for (int i = n; i < count - 1; ++i)
    {
        array[i] = array[i + 1];
    }

    --count;
    return ptr;

}

template <class T>
bool Storage<T>::Delete(const T &object)
{
    for (int i = 0; i<count ; i++)
    {
        if(array[i] == object)
        {
            this->Delete(i);
            return true;
        }
    }
    return false;
}

template<class T>
Storage<T> & Storage<T>::operator=(const Storage& copy)
{
    if (array != nullptr)
        delete[] array;
    array = new T[copy.size];
    size = copy.size;
    count = copy.count;
    for(int i = 0; i< count; ++i)
    {
        array[i] = copy.array[i];
    }
    return *this;
}

template<class T>
T& Storage<T>::operator[](int i)
{
    if ((i < count) || (i >= 0))
        return array[i];
    else
        throw;
}

template<class T>
void Storage<T>::Add(const T& object)
{
    if (count == size)
        Resize();
    array[count] = object;
    ++count;

}

template<class T>
void Storage<T>::Resize()
{
    T *temp = new T[size*2];
    for (int i = 0; i < count; ++i)
    {
        temp[i] = array[i];
    }
    delete[] array;
    array = temp;
    size *= 2;
}
#endif // STORAGE_H



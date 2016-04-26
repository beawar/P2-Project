#ifndef VETTORE_H
#define VETTORE_H

#include "iterator.h"
#include <stddef.h>

template <class T>
class Vettore
{
    friend class Iterator<T>;
private:
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef size_t size_type;

    pointer array;
    unsigned int dim;
    unsigned int _size;

    static pointer copia (const Vettore&);
    static pointer ridimensiona (pointer, int);
    static bool confronta (const Vettore &, const Vettore &);

public:
    typedef Iterator<value_type, true> const_iterator;
    typedef Iterator<value_type, false> iterator;

    explicit Vettore();
    Vettore(size_type, const_reference);
    Vettore(size_type);

    Vettore(const Vettore&);
    ~Vettore();
    Vettore& operator =(const Vettore&);

    size_type size () const;
    size_type capacity () const;

    bool operator ==(const Vettore&)const;
    bool operator !=(const Vettore&)const;
    bool operator <(const Vettore&)const;
    bool operator <=(const Vettore&) const;
    bool operator >(const Vettore&) const;
    bool operator >=(const Vettore&) const;

    bool empty () const;

    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    iterator insert(iterator, const_reference);
    void insert (iterator, size_type, const_reference);
    iterator erase(iterator);
    iterator erase(iterator, iterator);
    void erase (const_reference);
    void clear();

    void push_back (const_reference);
    void pop_back ();

    reference at(int) const;
    reference operator [](const int&) const;
    reference operator *() const;

};

//implementazione metodi template <class T> class Vettore

template <class T>
typename Vettore<T>::pointer Vettore<T>::copia(const Vettore<T>&v){
    T* aux = new T[v.dim];
    for(int i=0; i<v.size(); ++i){
        aux[i] = v.array[i];
    }
    return aux;
}

template <class T>
typename Vettore<T>::pointer Vettore<T>::ridimensiona(pointer a, int d){
    T* aux = new T[d];
    for(int i=0; i<d; ++i){
        aux[i] = a[i];
    }
    delete [] a;
    return aux;
}

template<class T>
bool Vettore<T>::confronta(const Vettore<T>& a, const Vettore<T>& b){
    if(!a.array && !b.array){
        return true;
    }
    else if(a.size() != b.size()){
        return false;
    }
    else{
        for(int i=0; i<a.size(); ++i){
            if(a[i] != b[i]){
                return false;
            }
        }
        return true;
    }
}

template <class T>
Vettore<T>::Vettore()
    :array(0), dim(0), _size(0) {}

template <class T>
Vettore<T>::Vettore(size_type n, const_reference t)
    :array(new T[n]), _size(0), dim(0){
    if(n>0){
        dim = 1;
        _size = 1;
        array[0] = t;
    }
    for(int i=1; i<n; ++i){
        push_back(t);
    }
}

template<class T>
Vettore<T>::Vettore(size_type n)
    :array(new T[n]), _size(0), dim(n) {}

template <class T>
Vettore<T>::Vettore(const Vettore<T>& v){
    array = copia(v);
    dim = v.dim;
    _size = v._size;
}

template <class T>
Vettore<T>::~Vettore(){
    delete [] array;
}

template <class T>
Vettore<T>& Vettore<T>::operator =(const Vettore<T>& v){
    if(this != &v){
        delete [] array;
        dim = v.dim;
        _size = v._size;
        array = copia(v);
    }
    return *this;
}

template <class T>
typename Vettore<T>::size_type Vettore<T>::size() const{
    return _size;
}

template<class T>
typename Vettore<T>::size_type Vettore<T>::capacity() const{
    return dim;
}

template<class T>
bool Vettore<T>::operator ==(const Vettore<T>& v) const{
    return confronta(*this, v);
}

template<class T>
bool Vettore<T>::operator !=(const Vettore<T>& v) const{
    return !confronta(*this, v);
}

template<class T>
bool Vettore<T>::operator <(const Vettore<T>& v) const{
    if(!v.array){
        return false;
    }
    else if(!array){
        return true;
    }
    else if(size() < v.size()){
        return true;
    }
    else if(size() > v.size()){
        return false;
    }
    else{
        for(int i=0; i<size(); ++i){
            if(array[i] > v.array[i]){
                return false;
            }
        }
        return true;
    }
}

template <class T>
bool Vettore<T>::operator <=(const Vettore<T>& v) const{
    return operator <(v) || operator ==(v);
}

template<class T>
bool Vettore<T>::operator >(const Vettore<T> & v) const{
    return !operator <=(v);
}

template<class T>
bool Vettore<T>::operator >=(const Vettore<T>& v) const{
    return !operator <(v);
}

template <class T>
bool Vettore<T>::empty() const{
    return size()==0;
}

template <class T>
typename Vettore<T>::iterator Vettore<T>::begin() const{

    iterator iaux(array);
    return iaux;
}

template <class T>
typename Vettore<T>::iterator Vettore<T>::end() const{
    pointer paux = &array[size()];
    iterator iaux(paux);
    return iaux;
}

template <class T>
typename Vettore<T>::const_iterator Vettore<T>::cbegin() const{
    pointer paux = &array;
    const_iterator iaux(paux);
    return iaux;
}

template <class T>
typename Vettore<T>::const_iterator Vettore<T>::cend() const{
    pointer paux = &array[size()];
    const_iterator iaux(paux);
    return iaux;
}
template <class T>
typename Vettore<T>::iterator Vettore<T>::insert(iterator it, const_reference x){
    for(iterator i=end(); i>it; --i){
        if(dim==size()){
            array = ridimensiona(array, dim*2);
            dim*=2;
        }
        *i = *(--i);
    }
    *it=x;
    return it;
}

template <class T>
void Vettore<T>::insert(iterator it, size_type n, const_reference x){
    for(int i=0; i<n; ++i){
        it = insert(it, x);
    }
}

template <class T>
typename Vettore<T>::iterator Vettore<T>::erase(iterator it){
    for(iterator i=it; i<end(); ++i){
        **i = **(++i);
    }
    pop_back();
    return it;
}

template <class T>
typename Vettore<T>::iterator Vettore<T>::erase(Vettore<T>::iterator from, Vettore<T>::iterator to){
    for(iterator it=from; it<to;){
        it=erase(it);
    }
    return to;
}

template <class T>
void Vettore<T>::erase(const_reference t){
    iterator it=begin();
    while(it<end()){
        if(*it==t){
            it = erase(it);
        }
        else{
            ++it;
        }
    }
}

template <class T>
void Vettore<T>::clear(){
    iterator temp = erase(begin(), end());
}

template <class T>
void Vettore<T>::push_back(const_reference t){
    if(dim == size()){
        array = ridimensiona(array, dim*2);
        dim=dim*2;
    }
    array[size()] = t;
    ++_size;
}

template <class T>
void Vettore<T>::pop_back(){
    T* temp = &array[size()-1];
    --_size;
    delete temp;
}

template <class T>
typename Vettore<T>::reference Vettore<T>::at (int i) const{
    return array[i];
}
template <class T>
typename Vettore<T>::reference Vettore<T>::operator [](const int& i) const{
    return array[i];
}

template <class T>
typename Vettore<T>::reference Vettore<T>::operator *() const{
    return *array;
}


#endif // VETTORE_H

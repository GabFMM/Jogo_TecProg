#pragma once
#include "Elemento.h"
#include <iostream>  

template<typename T>
class Lista
{
private:
    Elemento<T>* head;
    Elemento<T>* tail;

public:
    Lista() : head(nullptr), tail(nullptr) {}

    ~Lista()
    {
        Elemento<T>* atual = head;
        while (atual) {
            Elemento<T>* prox = atual->GetNext();
            delete atual;  // Libera a memória alocada
            atual = prox;
        }
        head = tail = nullptr;
    }

    void insert_front(T* pTipo);
    void insert_back(T* pTipo);
    void remove_front();
    void remove_back();

    Elemento<T>* getHead() const { return head; }
    Elemento<T>* getTail() const { return tail; }
    void setHead(Elemento<T>* elem) { if (elem) head = elem; }
    void setTail(Elemento<T>* elem) { if (elem) tail = elem; }

    Elemento<T>* operator[](int i);
};

// Inserção no início da lista
template<typename T>
void Lista<T>::insert_front(T* pTipo)
{
    if (pTipo != nullptr)
    {
        Elemento<T>* novoElem = new Elemento<T>();
        novoElem->setInfo(pTipo);
        if (getHead() == nullptr)
        {
            setHead(novoElem);
            setTail(novoElem);
        }
        else
        {
            novoElem->setNext(head);
            head->setPrev(novoElem);
            setHead(novoElem);
        }
    }
    else
    {
        std::cout << "Ponteiro Inválido" << std::endl;
    }
}

// Inserção no final da lista
template<typename T>
void Lista<T>::insert_back(T* pTipo)
{
    if (pTipo != nullptr)
    {
        Elemento<T>* novoElem = new Elemento<T>();
        novoElem->setInfo(pTipo);
        if (getTail() == nullptr)
        {
            setHead(novoElem);
            setTail(novoElem);
        }
        else
        {
            novoElem->setPrev(tail);
            tail->setNext(novoElem);
            setTail(novoElem);
        }
    }
    else
    {
        std::cout << "Ponteiro Inválido" << std::endl;
    }
}

// Remover o primeiro elemento
template<typename T>
void Lista<T>::remove_front()
{
    if (head == nullptr)
    {
        std::cout << "Não há o que remover" << std::endl;
    }
    else
    {
        Elemento<T>* aux = head;
        setHead(head->GetNext());
        if (head != nullptr)
        {
            head->setPrev(nullptr);
        }
        delete aux;
    }
}

// Remover o último elemento
template<typename T>
void Lista<T>::remove_back()
{
    if (tail == nullptr)
    {
        std::cout << "Não há o que remover" << std::endl;
    }
    else
    {
        Elemento<T>* aux = tail;
        setTail(tail->GetPrev());
        if (tail != nullptr)
        {
            tail->setNext(nullptr);
        }
        delete aux;
    }
}


template<typename T>
Elemento<T>* Lista<T>::operator[](int i)
{
    if (i < 0) return nullptr;  // Índice negativo retorna nullptr

    Elemento<T>* aux = getHead();
    int cont = 0;

    
    while (cont < i)
    {
        if (aux == nullptr)  
        {
            std::cout << "Índice fora dos limites!" << std::endl;
            return nullptr;
        }

        aux = aux->GetNext();
        cont++;
    }

    return aux;
}

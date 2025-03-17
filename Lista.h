#pragma once
#include <iostream>

namespace Listas {

    template <typename T>
    class ListaElementar {
    public:
      /////////////////////////////////////////// Classe Elemento ////////////////////////////////////////////////////
        class Elemento {
        private:
            T* pInfo;
            Elemento* next;
            Elemento* prev;

        public:
            Elemento() : pInfo(nullptr), next(nullptr), prev(nullptr) {}
            ~Elemento() 
            {
                if (pInfo) 
                {
                    delete pInfo;  
                    pInfo = nullptr;
                }
            }

            Elemento* GetNext() const { return next; }
            Elemento* GetPrev() const { return prev; }
            T* getInfo() const { return pInfo; }

            void setNext(Elemento* pNext) { next = pNext; }
            void setPrev(Elemento* pPrev) { prev = pPrev; }
            void setInfo(T* pInf) { pInfo = pInf; }
            
        };
        /////////////////////////////////////////////Classe Iterator//////////////////////////////////////////////
        class Iterator 
        {
        private:
            Elemento* current;

        public:
            Iterator(Elemento* start) : current(start) {}
            ~Iterator(){}

            bool hasPNext() const { return current != nullptr; }
            T* Atual() 
            {
                if (!current) 
                {
                    std::cerr << "Fim da lista atingido!" << std::endl;
                    return nullptr;
                }

                T* info = current->getInfo();
                current = current->GetNext();
                return info;
            }
        };

        ////////////////////////////////////////////ListaElementar/////////////////////////////////////////////////////
        ListaElementar() : head(nullptr), tail(nullptr), size(0) {}

        ~ListaElementar() { limpar(); }

        void insert_front(T* pTipo);
        void insert_back(T* pTipo);
        void remove_front();
        void remove_back();
        int getSize() const { return size; }
        void limpar();

        Elemento* getHead() const { return head; }
        Elemento* getTail() const { return tail; }
        void setHead(Elemento* elem) { head = elem; }
        void setTail(Elemento* elem) { tail = elem; }

        void operator--() { if (size > 0) size--; }
        Elemento* operator[](int i);

        //Retorna um iterador no começo da lista
        Iterator* getIterator()const { return new Iterator(head); }

    private:
        Elemento* head;
        Elemento* tail;
        int size;
    };

    // Implementação dos métodos
    template<typename T>
    void ListaElementar<T>::insert_front(T* pTipo) {
        if (!pTipo) {
            std::cerr << "Ponteiro inválido na inserção!" << std::endl;
            return;
        }

        Elemento* novoElem = new Elemento();
        novoElem->setInfo(pTipo);

        if (!head) 
        {
            head = tail = novoElem;
        }
        else 
        {
            novoElem->setNext(head);
            head->setPrev(novoElem);
            head = novoElem;
        }
        size++;
    }

    template<typename T>
    void ListaElementar<T>::insert_back(T* pTipo) {
        if (!pTipo) {
            std::cerr << "Ponteiro inválido na inserção!" << std::endl;
            return;
        }

        Elemento* novoElem = new Elemento();
        novoElem->setInfo(pTipo);

        if (!tail) {
            head = tail = novoElem;
        }
        else {
            novoElem->setPrev(tail);
            tail->setNext(novoElem);
            tail = novoElem;
        }
        size++;
    }

    template<typename T>
    void ListaElementar<T>::remove_front() {
        if (!head) {
            std::cerr << "A lista está vazia. Não há elementos para remover!" << std::endl;
            return;
        }

        Elemento* aux = head;
        head = head->GetNext();

        if (head) {
            head->setPrev(nullptr);
        }
        else {
            tail = nullptr; // Lista ficou vazia
        }

        delete aux;
        size--;
    }

    template<typename T>
    void ListaElementar<T>::remove_back() {
        if (!tail) {
            std::cerr << "A lista está vazia. Não há elementos para remover!" << std::endl;
            return;
        }

        Elemento* aux = tail;
        tail = tail->GetPrev();

        if (tail) {
            tail->setNext(nullptr);
        }
        else {
            head = nullptr; // Lista ficou vazia
        }

        delete aux;
        size--;
    }

    template<typename T>
    void ListaElementar<T>::limpar() 
    {
        Elemento* atual = head;
        while (atual) 
        {
            Elemento* prox = atual->GetNext();
            delete atual;
            atual = nullptr;
            atual = prox;
        }
        head = tail = nullptr;
        size = 0;
    }

    template<typename T>
    typename ListaElementar<T>::Elemento* ListaElementar<T>::operator[](int i) {
        
        if (i < 0 || i >= size) {
            std::cerr << "Índice fora dos limites!" << std::endl;
            return nullptr;
        }

        Elemento* aux = head;
        int cont = 0;

        while (cont < i) {
            aux = aux->GetNext();
            cont++;
        } 

        return aux;
    }

} // namespace Listas

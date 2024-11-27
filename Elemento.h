#pragma once

template<typename TIPO>
class Elemento
{
private:
    TIPO* pInfo;                      
    Elemento<TIPO>* next;             
    Elemento<TIPO>* prev;             

public:
    Elemento() : pInfo(nullptr), next(nullptr), prev(nullptr) {}

    ~Elemento() {
        if (pInfo != nullptr) {
            delete pInfo;  
        }
    }

    
    Elemento<TIPO>* GetNext() const { return next; }
    Elemento<TIPO>* GetPrev() const { return prev; }
    TIPO* getInfo() const { return pInfo; }

    void setNext(Elemento<TIPO>* pNext) { next = pNext; }
    void setPrev(Elemento<TIPO>* pPrev) { prev = pPrev; }
    void setInfo(TIPO* pInf) { pInfo = pInf; }
};

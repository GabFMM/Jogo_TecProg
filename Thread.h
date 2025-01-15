#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <stdexcept>
using namespace std;

class ThreadCPP
{
private:
    thread _thread;

    static mutex _mutex;

protected:
    static void* runThread(void* pthread);
    virtual void run() = 0;
    void printError(const string& msg)const;

public:
    ThreadCPP();
    ~ThreadCPP();
    void start();
    void yield();
    void join();

    void lockMutex();
    void unlockMutex();

};
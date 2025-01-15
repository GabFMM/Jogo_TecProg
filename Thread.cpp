#include "Thread.h"

mutex ThreadCPP::_mutex;

void* ThreadCPP::runThread(void* pthread)
{
    ThreadCPP* Th = static_cast<ThreadCPP*>(pthread);

    if (Th == nullptr)
    {
        cerr << "Erro, thread Falhou\n\n ";
    }
    else
    {
        Th->run();
    }
    return 0;

}

void ThreadCPP::printError(const string& msg) const
{
    cerr << "Erro " << msg << endl;
}

ThreadCPP::ThreadCPP()
{
}

ThreadCPP::~ThreadCPP()
{
    join();
}

void ThreadCPP::start()
{
    try
    {
        _thread = thread(ThreadCPP::runThread, this);
    }
    catch (const std::exception& e)
    {
        printError("Falha ao criar a thread: " + std::string(e.what()));
    }

}

void ThreadCPP::yield()
{
    this_thread::yield();
}

void ThreadCPP::join()
{
    if (_thread.joinable())
    {
        _thread.join();
    }
}

void ThreadCPP::lockMutex()
{
    ThreadCPP::_mutex.lock();
}

void ThreadCPP::unlockMutex()
{
    ThreadCPP::_mutex.unlock();
}

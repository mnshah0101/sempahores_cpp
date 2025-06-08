
#include <semaphore.h>
#include <iostream>
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>


class RWLock
{
public:
    RWLock() : readCount_(0)
    {
        sem_init(&writelock, 0, 1);
        sem_init(&rmutex_, 0, 1);
    }

    ~RWLock()
    {
        sem_destroy(&writelock);
        sem_destroy(&rmutex_);
    }
    void acquireReadLock() {

        sem_wait(&rmutex_);
        readCount_++;
        if (readCount_  == 1){
            sem_wait(&writelock);
        }

        sem_post(&rmutex_);
    };


    void releaseReadLock(){
        sem_wait(&rmutex_);
        readCount_--;
        if (readCount_ == 0){

            sem_post(&writelock);
        }

        sem_post(&rmutex_);
        
        };

        void acquireWriteLock() {

            sem_wait(&writelock);

        };
        void releaseWriteLock() {
            sem_post(&writelock);

        };

    private:
        sem_t writelock;
        sem_t rmutex_;  // basic lock
        int readCount_; // number of active readers
};



int loops;
int value = 0;
RWLock lock;

void reader()
{
    for (int i = 0; i < loops; ++i)
    {
        lock.acquireReadLock();
        std::cout << "read  " << value << "\n";
        lock.releaseReadLock();
    }
}

void writer()
{
    for (int i = 0; i < loops; ++i)
    {
        lock.acquireWriteLock();
        ++value;
        std::cout << "write " << value << "\n";
        lock.releaseWriteLock();
    }
}

int main(int argc, char *argv[])
{
    assert(argc == 4);
    int numReaders = std::stoi(argv[1]);
    int numWriters = std::stoi(argv[2]);
    loops = std::stoi(argv[3]);

    std::cout << "begin\n";

    std::vector<std::thread> readers, writers;
    readers.reserve(numReaders);
    writers.reserve(numWriters);

    for (int i = 0; i < numReaders; ++i)
        readers.emplace_back(reader);
    for (int i = 0; i < numWriters; ++i)
        writers.emplace_back(writer);

    for (auto &t : readers)
        t.join();
    for (auto &t : writers)
        t.join();

    std::cout << "end: value " << value << "\n";
    return 0;
}

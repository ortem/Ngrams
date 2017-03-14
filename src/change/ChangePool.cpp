#include "ChangePool.h"

ChangePool::ChangePool(HashTable *tree)
{
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < CHANGE_THREAD_NUM; i++) {
        pthread_cond_init(&finished[i], NULL);

        threads[i].setTree(tree);
        threads[i].setMutexAndCond(&this->mutex, &this->finished[i]);
    }
}

void ChangePool::add(const char *str, int length, int num)
{
    int i = 0;
    while (true) {
        if (threads[i].isEmpty) {
            threads[i].isAdd = true;
            threads[i].str = str;
            threads[i].length = length;
            threads[i].num = num;
            //cout << "addition given to " << i << endl;
            threads[i].signal();
            break;
        }
        i = (i + 1) % CHANGE_THREAD_NUM;
    }
}

void ChangePool::remove(const char *str, int length, int num)
{
    int i = 0;
    while (true) {
        if (threads[i].isEmpty) {
            threads[i].isAdd = false;
            threads[i].str = str;
            threads[i].length = length;
            threads[i].num = num;
            //cout << "deletion given to " << i << endl;
            threads[i].signal();
            break;
        }
        i = (i + 1) % CHANGE_THREAD_NUM;
    }
}

void ChangePool::wait()
{
    for (int i = 0; i < CHANGE_THREAD_NUM; i++)
        while (!threads[i].isEmpty)
            pthread_cond_wait(&finished[i], &mutex);
}
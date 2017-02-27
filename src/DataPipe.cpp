//
// Created by opot on 27.02.17.
//

#include "DataPipe.h"


DataPipe::DataPipe(){
    wait = new std::queue<Query>();
    current = new std::queue<Query>();
    pthread_cond_init(&queue_state, NULL);
    pthread_mutex_init(&queue_mutex, NULL);
}


Query DataPipe::next() {
    if(current->empty()){
        pthread_mutex_lock(&queue_mutex);
        pthread_cond_wait(&queue_state, &queue_mutex);
        std::queue<Query> *buf = wait;
        wait = current;
        current = buf;
        pthread_mutex_unlock(&queue_mutex);
    }

    Query res = current->front();
    current->pop();
    return res;
}

void DataPipe::add(std::string &str){
    pthread_mutex_lock(&queue_mutex);
    wait->push({1, str});
    pthread_cond_signal(&queue_state);
    pthread_mutex_unlock(&queue_mutex);
}

void DataPipe::remove(std::string &str){
    pthread_mutex_lock(&queue_mutex);
    wait->push({-1, str});
    pthread_cond_signal(&queue_state);
    pthread_mutex_unlock(&queue_mutex);
}

void DataPipe::process(std::string &text){
    pthread_mutex_lock(&queue_mutex);
    wait->push({0, text});
    pthread_cond_signal(&queue_state);
    pthread_mutex_unlock(&queue_mutex);
}
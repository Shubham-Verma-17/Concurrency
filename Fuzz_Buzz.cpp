#include<bits/stdc++.h>
using namespace std;

pthread_mutex_t mtx;
pthread_cond_t cv;

int max_value=30;
int current=1;

void* print_fuzz(void*data){
    while(current<max_value){
        pthread_mutex_lock(&mtx);
        
        while(current%3!=0 || current%5==0){
            pthread_cond_wait(&cv,&mtx);
        }
        
        cout<<"fuzz"<<endl;
        current++;
        pthread_cond_broadcast(&cv);
        pthread_mutex_unlock(&mtx);
    }
    
    return NULL;
}

void* print_buzz(void*data){
    while(current<max_value){
        pthread_mutex_lock(&mtx);
        
        while(current%3==0 || current%5!=0){
            pthread_cond_wait(&cv,&mtx);
        }
        
        cout<<"buzz"<<endl;
        current++;
        pthread_cond_broadcast(&cv);
        pthread_mutex_unlock(&mtx);
    }
    
    return NULL;
}

void* print_fuzzbuzz(void*data){
    while(current<max_value){
        pthread_mutex_lock(&mtx);
        
        while(current%3!=0 || current%5!=0){
            pthread_cond_wait(&cv,&mtx);
        }
        
        cout<<"fuzzbuzz"<<endl;
        current++;
        pthread_cond_broadcast(&cv);
        pthread_mutex_unlock(&mtx);
    }
    
    return NULL;
}

void* print_normal(void*data){
    while(current<max_value){
        pthread_mutex_lock(&mtx);
        
        while(current%3==0 || current%5==0){
            pthread_cond_wait(&cv,&mtx);
        }
        
        cout<<current<<endl;
        current++;
        pthread_cond_broadcast(&cv);
        pthread_mutex_unlock(&mtx);
    }
    
    return NULL;
}


int main(){
    pthread_mutex_init(&mtx,NULL);
    pthread_cond_init(&cv,NULL);
    
    pthread_t t1,t2,t3,t4;
    
    pthread_create(&t1,NULL,print_fuzz,NULL);
    pthread_create(&t2,NULL,print_buzz,NULL);
    pthread_create(&t3,NULL,print_fuzzbuzz,NULL);
    pthread_create(&t4,NULL,print_normal,NULL);
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv);

    return 0;
}

#include<bits/stdc++.h>
using namespace std;

int max_value=40;
int current=1;

pthread_mutex_t mtx;
pthread_cond_t cv;

void* print_even(void* data){
    while(current<max_value){
        pthread_mutex_lock(&mtx);

        while(current%2==1){
            pthread_cond_wait(&cv,&mtx);
        }

        cout<<"Even : "<<current<<endl;
        current++;
        pthread_cond_signal(&cv);

        pthread_mutex_unlock(&mtx);
    }
    
    return NULL;
}

void* print_odd(void* data){
    while(current<max_value){
        pthread_mutex_lock(&mtx);

        while(current%2==0){
            pthread_cond_wait(&cv,&mtx);
        }

        cout<<"Odd : "<<current<<endl;
        current++;
        pthread_cond_signal(&cv);

        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}


int main(){
    pthread_mutex_init(&mtx,NULL);
    pthread_cond_init(&cv,NULL);

    pthread_t t1,t2;

    pthread_create(&t1, NULL, print_even, NULL);
    pthread_create(&t2, NULL, print_odd, NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv);

    return 0;
}

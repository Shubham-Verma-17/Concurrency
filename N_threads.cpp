#include<bits/stdc++.h>
using namespace std;

pthread_mutex_t mtx;
pthread_cond_t cv;

int max_value=30;
int current=1;
int N=5;

void* print(void* data){
    int val=*(int*)(data);
    
    while(current<=max_value){
        pthread_mutex_lock(&mtx);
        
        while(((current-1)%N) != val){
            pthread_cond_wait(&cv,&mtx);
        }
        
        if(current>max_value){
            pthread_cond_broadcast(&cv);
            pthread_mutex_unlock(&mtx);
            continue;
        }
        
        
        cout<<val+1<<" Thread : "<<current<<endl;
        current++;
        
        pthread_cond_broadcast(&cv);
        pthread_mutex_unlock(&mtx);
    }
    
    return NULL;
}

int main(){
    pthread_mutex_init(&mtx,NULL);
    pthread_cond_init(&cv,NULL);
    
    vector<int>thread_id(N);
    for(int i=0;i<N;i++){
        thread_id[i]=i;
    }
    
    pthread_t threads[N];
    
    for(int i=0;i<N;i++){
        pthread_create(&threads[i],NULL,print,&thread_id[i]);
    }
    
    for(int i=0;i<N;i++){
        pthread_join(threads[i],NULL);
    }
    
    
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv);

    return 0;
}

#include <stdio.h>

void thread1();
void thread2();

int lock = 0;

void thread1(){
    printf("1\n");
}

void thread2(){
    printf("2\n");
}

int main(){
    int i=0;
    while(i<20){
    if(lock == 0){
        thread1();
        lock+=1;
    }
    if(lock == 1){
        thread2();
        lock-=1;
    }
    i++;
    }
}

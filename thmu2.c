#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;
pthread_mutex_t lockVar;	// mutex thread lockVar
pthread_t tid[2];	// thread ids
int balance = 400;
/*
	This function increases the current balance by the amount passed in the function as an argument
*/
void* incBal(void *arg) {
	pthread_mutex_lock(&lockVar);	// locking
	int *bal = (int *)arg;
	balance += *bal;
	cout<<"Balance added by: "<<*bal<<endl;
	cout<<"New balance is: "<<balance<<endl;
	pthread_mutex_unlock(&lockVar);	// unlocking
	pthread_exit(NULL);
}
/*
	This function decreases the current balance by the amount passed in the function as an argument
*/
void* decBal(void *arg) {
	// showBal(arg);
	pthread_mutex_lock(&lockVar);	// locking
	int *bal = (int *)arg;
	if(balance >= *bal)
		balance -= *bal;
	cout<<"Balance deducted by: "<<*bal<<endl;
	cout<<"New balance is: "<<balance<<endl;
	pthread_mutex_unlock(&lockVar);	// unlocking
	pthread_exit(NULL);
}

int main() {
	int i = 0;
	int nBal = 1000, aBal = 400;
	//pthread_mutex_init(&lockVar, NULL);
	pthread_create(&(tid[i]), NULL, &incBal, &nBal);   // creating thread  
	i++;
	pthread_create(&(tid[i]), NULL, &decBal, &aBal);   // creating thread 2
	pthread_join(tid[0], NULL); // joining 1
	pthread_join(tid[1], NULL); // joining 2
	pthread_mutex_destroy(&lockVar);   // destroying lockVar
	return 0;
}


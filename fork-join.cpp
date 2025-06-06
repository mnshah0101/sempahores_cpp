#include <iostream>
#include <thread>
#include <semaphore>

std::counting_semaphore<2> sem(0);


void *child(void * arg){
	std::cout<< "HELLO FROM CHILD" << '\n';

	sem.release();

	return NULL;
}

int main(){

	std::cout << "HELLO FROM PARENT" << '\n';

	std::thread t1(child, nullptr);
	

	sem.acquire();
	
	std::cout << "PARENT ENDED" << '\n';

}


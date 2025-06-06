#include <iostream>
#include <thread>
#include <semaphore>



std::counting_semaphore<2> sem2(0);
std::counting_semaphore<2> sem1(0);

void funcOne(void *arg){

	std::cout <<"Before F1 \n";
	sem2.release();
	sem1.acquire();

	std::cout <<"rendevous f1 \n";

	sem1.release();
		
	
	

	
	

}

void funcTwo(void * arg){
	std::cout << "Before f2 \n";

	sem1.release();
	sem2.acquire();

	std::cout << "rendevous f2 \n";

	sem2.release();



}



	int main(){
		std::thread thread1(funcOne, nullptr);
		std::thread thread2(funcTwo, nullptr);

		thread1.join();
		thread2.join();

	};
 

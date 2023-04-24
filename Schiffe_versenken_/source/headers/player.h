#pragma once
//#include <iostream>
//#include <vector>
//#include <string>
//#include <vector>
//#include <random>
#include "global.h"
#include "Draw.h"
//#include "computer.h"
#include "Player1.h"
namespace battleships {
	class Player : public Player1 {
	private:


		friend class Draw;
		friend class Compare;
		friend int main();
	public:
		void make_move(Draw&, Player1&, int&, int&, bool, bool, bool, std::vector<std::vector<bool>>&) override;
		void placeships(Draw&, HANDLE&) override;
		Player(Draw&);
		Player(Draw&, int);
		//void movemaker(int&, int&, int, Draw&);
		//void hitmanager(int&, int&, int, Draw&);
	};
}

/*
	#include <chrono>
	long long GetCurrentTimeMillis() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
			).count();
	}

	// A sample function to simulate the time spent on deciding a move
	void DoSomething() {
		for (int i = 1; i <= 1000000000; ++i) {
				// do nothing
		}
	}


	Get the start time

	// Do something
	DoSomething();

	// Get the end time
	long long start = GetCurrentTimeMillis();
	long long end = GetCurrentTimeMillis();

	// Calculate the time spent
	long long timeSpent = end - start;

	// Output the time spent
	std::cout << "Time spent: " << timeSpent << " ms\n";

	return 0;
*/



//	#include <iostream>
//	#include <memory>
//	
//	class MyClass {
//	public:
//		std::weak_ptr<MyClass> weak_ptr_;
//	
//		~MyClass() {
//			std::cout << "MyClass object destroyed." << std::endl;
//		}
//	};
//
//	int main() {
//		std::shared_ptr<MyClass> shared_ptr1 = std::make_shared<MyClass>();
//		std::weak_ptr<MyClass> weak_ptr1 = shared_ptr1;
//	
//		std::cout << "weak_ptr1 use count: " << weak_ptr1.use_count() << std::endl; // prints 1
//		{
//			std::shared_ptr<MyClass> shared_ptr2 = weak_ptr1.lock();
//			if (shared_ptr2) {
//				std::cout << "shared_ptr2 use count: " << shared_ptr2.use_count() << std::endl; // prints 2
//			}
//		}
//		std::cout << "weak_ptr1 use count: " << weak_ptr1.use_count() << std::endl; // prints 1
//	
//		shared_ptr1->weak_ptr_ = weak_ptr1;
//	
//		return 0;
//	}
//In this example, we first create a shared_ptr to a MyClass object, and then we create a weak_ptr to that same object.
//We then check the use count of the weak_ptr, which should be 1 since it's the only weak_ptr pointing to the object.
//We then create another shared_ptr from the weak_ptr using the lock() method, which creates a new shared_ptr pointing
//to the same object if the object is still alive.We check the use count of this shared_ptr, which should be 2 since both
//the original shared_ptr and this new shared_ptr point to the same object.
//We then create a new scope and destroy the second shared_ptr, which should decrement the use count of the object to 1.
//Finally, we assign the weak_ptr to a member variable of the MyClass object.This allows the MyClass object to keep track 
//of the weak_ptr, and it can use it to create a new shared_ptr to itself if necessary.



//
//  main.cpp
//  Prt
//
//  Created by Михаил Фокин on 04.11.2021.
//

#include <iostream>
#include "Ptr.h"
#include "SPrt.h"

int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Hello, World!\n";
	//Ptr<int> int_ptr(new int(12));
	SPtr<int> int_sptr(new int(23));
	SPtr<int> int_sptr_two(int_sptr);
	SPtr<int> int_sptr_three(new int(21));
	int_sptr = int_sptr_three;
	std::cout << *int_sptr << std::endl;
	
	return 0;
}

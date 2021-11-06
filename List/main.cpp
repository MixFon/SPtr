//
//  main.cpp
//  List
//
//  Created by Михаил Фокин on 06.11.2021.
//

#include <iostream>
#include "List.h"
#include <gtest.h>
#include <gtest/gtest.h>

int main(int argc, const char * argv[]) {
	List<int> newList;
	{
		List<int> list;
		list.addNode(11);
		list.addNode(22);
		list.addNode(33);
		list.addNode(44);
		list.printNodes();
		newList = list.getCopy();
		std::cout << list.getSize() << std::endl;
	}
	newList.printNodes();
	return 0;
}

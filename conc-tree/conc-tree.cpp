#include <iostream>

#include "ConcTree.h"
#include "ConcVector.h"

int main() {
	ConcVector<int> vector;

	vector.insert(10);
	vector.insert(20);
	vector.insert(60);

	ConcTree<int> t1{};
	t1.insert(10);
	t1.insert(20);
	t1.insert(30);

	std::cout << "T1" << std::endl;

	t1.print_inorder();

	std::cout << std::endl;

	ConcTree<int> t2{};
	t2.insert(40);
	t2.insert(50);
	t2.insert(60);

	std::cout << "T2" << std::endl;

	t2.print_inorder();

	std::cout << std::endl;

	t1.concatenate(t2);

	std::cout << "T1 ~ T2" << std::endl;

	t1.print_inorder();

	return EXIT_SUCCESS;
}

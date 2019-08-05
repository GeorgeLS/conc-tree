#include <iostream>
#include <vector>
#include "ConcTree.h"
#include "ScopedTimer.h"
#include "ConcVector.h"

constexpr size_t number_of_elements = 100000000U;

void test_conc_tree_int()
{
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
}

void test_std_vector_insert()
{
	std::vector<int> vector(100000);
	MEASURE_FUNCTION();
	for (size_t i = 0U; i != number_of_elements; ++i)
	{
		vector.push_back(i);
	}
}

void test_conc_vector_insert()
{
	ConcVector<int> vector(100000);
	MEASURE_FUNCTION();
	for (size_t i = 0U; i != number_of_elements; ++i)
	{
		vector.insert(i);
	}
}


int main()
{	
	std::cout << "Number of elements: " << number_of_elements << std::endl << std::endl;
	test_conc_vector_insert();
	test_std_vector_insert();

	getchar();
	return EXIT_SUCCESS;
}

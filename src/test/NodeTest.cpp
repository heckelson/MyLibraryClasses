
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include "../node/Node.h"

BOOST_AUTO_TEST_SUITE(Node_Tests);

BOOST_AUTO_TEST_CASE(Throws_at_set_child_self) {
	/* Node should throw if you set itself as a child, since this would cause */
	BOOST_CHECK_THROW({
		Node<double> node;
		node.set_left(&node);

	}, std::runtime_error);

	BOOST_CHECK_THROW({
		Node<double> node;
		node.set_right(&node);

	}, std::runtime_error);
}

BOOST_AUTO_TEST_CASE(Holds_the_data) {
	Node<double> node;
	double test_value = 2.5;

	node.set_data(&test_value);

	BOOST_CHECK_EQUAL(test_value, node.get());

}

BOOST_AUTO_TEST_CASE(Can_create_inorder_vector) {
	Node<double> root, left_child, right_child;
	double root_val, left_child_val, right_child_val;

	root_val = 1.0;
	left_child_val = 2.0;
	right_child_val = 3.0;

	root.set_data(&root_val);
	left_child.set_data(&left_child_val);
	right_child.set_data(&right_child_val);

	root.set_left(&left_child);
	root.set_right(&right_child);

	Vector<double> comparison;
	comparison.push_back(root_val);
	comparison.push_back(left_child_val);
	comparison.push_back(right_child_val);

	std::cout << "test" << std::endl;

	BOOST_CHECK_EQUAL(root.get_vector(), comparison);
}

BOOST_AUTO_TEST_SUITE_END();

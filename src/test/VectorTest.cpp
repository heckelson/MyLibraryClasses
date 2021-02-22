
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../vector/Vector.h"

#include <stdexcept>
#include <iostream>

BOOST_AUTO_TEST_SUITE(Vector_Tests)

BOOST_AUTO_TEST_CASE (Vector_empty_has_vector_size_0) {
	/* Create an empty vector. It should have size 0. */
	Vector<double> vec;
	BOOST_CHECK_EQUAL(0, vec.get_size());
}

BOOST_AUTO_TEST_CASE (Vectors_change_size_correctly) {
	Vector<double> vec;
	double test_value = 2.5;

	/* If you add one, the size should increase by one. */
	vec.push_back(test_value);
	BOOST_CHECK_EQUAL(1, vec.get_size());

	/* If you remove one, the size should decrease by one. */
	vec.remove(test_value);
	BOOST_CHECK_EQUAL(0, vec.get_size());

	/* Add a value 10 times. The size should be 10. */
	for (int i = 0; i < 10; i++) {
		vec.push_back(test_value);
	}
	BOOST_CHECK_EQUAL(10, vec.get_size());

	/* Size should be 9 now since 10-1=9. */
	vec.remove(test_value);
	BOOST_CHECK_EQUAL(9, vec.get_size());

	/* Size should be 0 again. */
	vec.remove_all(test_value);
	BOOST_CHECK_EQUAL(0, vec.get_size());
}

BOOST_AUTO_TEST_CASE (Vector_throws_at_illegal_access) {
	/* Vectors should throw if you access an illegal index. */
	BOOST_CHECK_THROW({
		Vector<int> vec;
		vec.at(0);

	}, std::runtime_error);
}

BOOST_AUTO_TEST_CASE(Vector_clear) {
	/* After invocation of clear(), the vector should have size 0. */
	Vector<int> vec;
	vec.push_back(1);
	vec.clear();

	/* Size should be 0 now. */
	BOOST_CHECK_EQUAL(0, vec.get_size());

	/* No elements should be accessible anymore. */
	BOOST_CHECK_THROW({
		vec.at(0);
	}, std::runtime_error);
}

BOOST_AUTO_TEST_CASE(Vector_operator_equals_works) {
	Vector<double> vec1 = {1,2,3}, vec2 = {1,2,3};
	BOOST_CHECK_EQUAL(vec1, vec2);





}


BOOST_AUTO_TEST_SUITE_END()

#include "doctest.h"
#include "sources/MagicalContainer.hpp"

using namespace ariel;

TEST_CASE("Create MagicalContainer and Add/Remove elements")
{
	MagicalContainer container;
    CHECK(container.size() == 0);

    container.addElement(1);
    CHECK(container.size() == 1);

    container.addElement(2);
    CHECK(container.size() == 2);

    container.removeElement(2);
    CHECK(container.size() == 1);
}

TEST_CASE("AscendingIterator Order (begin/end, Dereference and Pre-increment)")
{
	MagicalContainer container;
    container.addElement(4);
    container.addElement(3);
    container.addElement(2);
    container.addElement(1);

    MagicalContainer::AscendingIterator ascending_iterator(container);

    CHECK(ascending_iterator == ascending_iterator.begin());

	CHECK(*ascending_iterator == 1);
	++ascending_iterator;
	CHECK(*ascending_iterator == 2);
	++ascending_iterator;
	CHECK(*ascending_iterator == 3);
	++ascending_iterator;
    CHECK(*ascending_iterator == 4);
	++ascending_iterator;

	CHECK(ascending_iterator == ascending_iterator.end());
}

TEST_CASE("SideCrossIterator Order (begin/end, Dereference and Pre-increment)")
{
	MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);
    container.addElement(4);
    container.addElement(5);

    MagicalContainer::SideCrossIterator side_cross_iterator(container);

    CHECK(side_cross_iterator == side_cross_iterator.begin());

	CHECK(*side_cross_iterator == 1);
	++side_cross_iterator;
	CHECK(*side_cross_iterator == 5);
	++side_cross_iterator;
    CHECK(*side_cross_iterator == 2);
	++side_cross_iterator;
    CHECK(*side_cross_iterator == 4);
	++side_cross_iterator;
    CHECK(*side_cross_iterator == 3);
	++side_cross_iterator;

	CHECK(side_cross_iterator == side_cross_iterator.end());
}

TEST_CASE("PrimeIterator Order (begin/end, Dereference and Pre-increment)")
{
	MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);
    container.addElement(4);
    container.addElement(5);

    MagicalContainer::PrimeIterator prime_iterator(container);

    CHECK(prime_iterator == prime_iterator.begin());

	CHECK(*prime_iterator == 2);
	++prime_iterator;
	CHECK(*prime_iterator == 3);
	++prime_iterator;
    CHECK(*prime_iterator == 5);
	++prime_iterator;

	CHECK(prime_iterator == prime_iterator.end());
}

TEST_CASE("AscendingIterator Comparison")
{
	MagicalContainer container;
    container.addElement(4);
    container.addElement(3);
    container.addElement(2);
    container.addElement(1);

    MagicalContainer::AscendingIterator ascending_iterator1(container);
    MagicalContainer::AscendingIterator ascending_iterator2(container);

    CHECK(ascending_iterator1 == ascending_iterator2);

    ++ascending_iterator2;

    CHECK(ascending_iterator1 != ascending_iterator2);
    CHECK(ascending_iterator1 < ascending_iterator2);
    CHECK(ascending_iterator2 > ascending_iterator1);
}

TEST_CASE("SideCrossIterator Comparison")
{
	MagicalContainer container;
    container.addElement(4);
    container.addElement(3);
    container.addElement(2);
    container.addElement(1);

    MagicalContainer::SideCrossIterator side_cross_iterator1(container);
    MagicalContainer::SideCrossIterator side_cross_iterator2(container);

    CHECK(side_cross_iterator1 == side_cross_iterator2);

    ++side_cross_iterator2;

    CHECK(side_cross_iterator1 != side_cross_iterator2);
    CHECK(side_cross_iterator1 < side_cross_iterator2);
    CHECK(side_cross_iterator2 > side_cross_iterator1);
}

TEST_CASE("PrimeIterator Comparison")
{
	MagicalContainer container;
    container.addElement(4);
    container.addElement(3);
    container.addElement(2);
    container.addElement(1);

    MagicalContainer::PrimeIterator prime_iterator1(container);
    MagicalContainer::PrimeIterator prime_iterator2(container);

    CHECK(prime_iterator1 == prime_iterator2);

    ++prime_iterator2;

    CHECK(prime_iterator1 != prime_iterator2);
    CHECK(prime_iterator1 < prime_iterator2);
    CHECK(prime_iterator2 > prime_iterator1);
}
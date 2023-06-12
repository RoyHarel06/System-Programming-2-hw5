#include "MagicalContainer.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>

using namespace std;

namespace ariel
{
    // -------------------- Magical Container --------------------

    MagicalContainer::MagicalContainer() {}

    void MagicalContainer::addElement(int element) {     
        if (elements.insert(element).second == false)
            return;

        auto element_itr = find(elements.begin(), elements.end(), element);

        // Ascending order:

        auto it = lower_bound(ascending_order.begin(), ascending_order.end(), &(*element_itr),
            [](const int *a, const int *b) -> bool {
                return *a < *b;
            });
        ascending_order.insert(it, &(*element_itr));

        // Sidecross order:

        side_cross_order.clear();

        size_t end = ascending_order.size() - 1;
        for (size_t i = 0; i < ascending_order.size()/2; i++)
        {
            side_cross_order.push_back(ascending_order.at(i));
            side_cross_order.push_back(ascending_order.at(end-i));
        }
        
        if (ascending_order.size() % 2 == 1)
            side_cross_order.push_back(ascending_order.at(ascending_order.size()/2));

        // Prime order:

        if (isPrime(element)) {
            auto it = lower_bound(primes.begin(), primes.end(), &(*element_itr), 
                [](const int *a, const int *b) -> bool {
                    return *a < *b;
                });
            primes.insert(it, &(*element_itr));
        }
    }

    void MagicalContainer::removeElement(int element) {
        auto element_index = find(elements.begin(), elements.end(), element);
        if (element_index == elements.end())
            throw runtime_error("Element not in container!");

        auto element_itr = find(elements.begin(), elements.end(), element);

        // Ascending order:

        auto it = find(ascending_order.begin(), ascending_order.end(), &(*element_itr));
        if (it != ascending_order.end())
            ascending_order.erase(it);

        // Sidecross order:

        side_cross_order.clear();

        size_t end = ascending_order.size() - 1;
        for (size_t i = 0; i < ascending_order.size()/2; i++)
        {
            side_cross_order.push_back(ascending_order.at(i));
            side_cross_order.push_back(ascending_order.at(end-i));
        }
        
        if (ascending_order.size() % 2 == 1)
            side_cross_order.push_back(ascending_order.at(ascending_order.size()/2));

        // Prime order:

        if (isPrime(element)) {
            auto it = find(primes.begin(), primes.end(), &(*element_itr));
            if (it != primes.end())
                primes.erase(it);
        }

        elements.erase(element_index);
    }

    int MagicalContainer::size() const {
        return elements.size();
    }

    bool MagicalContainer::isPrime(int num) const {
        if (num <= 1)
            return false;

        for (int i = 2; i <= sqrt(num); ++i) {
            if (num % i == 0)
                return false;
        }

        return true;
    }

    // -------------------- Ascending Iterator --------------------

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container) : container(&container), index(0) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other) {
        if (container != other.container)
		    throw runtime_error("Different containers!");

        container = other.container;
        index = other.index;
    }

    MagicalContainer::AscendingIterator::~AscendingIterator() {}

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
        if (this != &other)
        {
            if (container != other.container)
		        throw runtime_error("Different containers!");

            container = other.container;
            index = other.index;
        }

        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
        if (container != other.container)
            throw runtime_error("Different containers!");

        return index == other.index;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
        return !(*this == other);
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
        if (container != other.container)
            throw runtime_error("Different containers!");

        return index < other.index;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
        return !(*this < other) && (*this != other);
    }

    int MagicalContainer::AscendingIterator::operator*() const {
        if (container == nullptr)
            throw runtime_error("No container!");

        if (container->ascending_order.size() <= index)
            throw runtime_error("Iterator out of bounds!");

        return *(container->ascending_order.at(index));
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
        if (container == nullptr)
            throw runtime_error("No container!");

        if (container->ascending_order.size() <= index)
            throw runtime_error("Iterator out of bounds!");

        ++index;
        return *this;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return AscendingIterator(*container);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        AscendingIterator end(*container);
        for (int i = 0; i < container->ascending_order.size(); i++)
            ++end;

        return end;
    }

    // -------------------- SideCross Iterator --------------------

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container) : container(&container), index(0) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other) {
        if (container != other.container)
		    throw runtime_error("Different containers!");

        container = other.container;
        index = other.index;
    }

    MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
        if (this != &other)
        {
            if (container != other.container)
		        throw runtime_error("Different containers!");

            container = other.container;
            index = other.index;
        }

        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
        if (container != other.container)
            throw runtime_error("Different containers!");

        return index == other.index;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
        if (container != other.container)
            throw runtime_error("Different containers!");

        return index < other.index;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
        return !(*this < other) && (*this != other);
    }

    int MagicalContainer::SideCrossIterator::operator*() const {
        if (container == nullptr)
            throw runtime_error("No container!");

        if (container->side_cross_order.size() <= index)
            throw runtime_error("Iterator out of bounds!");

        return *(container->side_cross_order.at(index));
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        if (container == nullptr)
            throw runtime_error("No container!");

        if (container->side_cross_order.size() <= index)
            throw runtime_error("Iterator out of bounds!");

        ++index;
        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return SideCrossIterator(*container);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        SideCrossIterator end(*container);
        for (int i = 0; i < container->side_cross_order.size(); i++)
            ++end;

        return end;
    }

    // -------------------- Prime Iterator --------------------

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container) : container(&container), index(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other) {
        if (container != other.container)
		    throw runtime_error("Different containers!");

        container = other.container;
        index = other.index;
    }

    MagicalContainer::PrimeIterator::~PrimeIterator() {}

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
        if (this != &other)
        {
            if (container != other.container)
		        throw runtime_error("Different containers!");

            container = other.container;
            index = other.index;
        }

        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
        if (container != other.container)
            throw runtime_error("Different containers!");

        return index == other.index;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
        if (container != other.container)
            throw runtime_error("Different containers!");

        return index < other.index;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
        return !(*this < other) && (*this != other);
    }

    int MagicalContainer::PrimeIterator::operator*() const {
        if (container == nullptr)
            throw runtime_error("No container!");

        if (container->primes.size() <= index)
            throw runtime_error("Iterator out of bounds!");

        return *(container->primes.at(index));
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
        if (container == nullptr)
            throw runtime_error("No container!");

        if (container->primes.size() <= index)
            throw runtime_error("Iterator out of bounds!");

        ++index;
        return *this;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return PrimeIterator(*container);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        PrimeIterator end(*container);
        for (int i = 0; i < container->primes.size(); i++)
            ++end;

        return end;
    }
}
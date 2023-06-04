#include <vector>

using namespace std;

namespace ariel
{
	class MagicalContainer
	{
		private:
			vector<int> elements;
			vector<const int*> ascending_order;
			vector<const int*> primes;
			vector<const int*> side_cross_order;
			bool isPrime(int num) const;

		public:
			MagicalContainer();
			void addElement(int element);
			void removeElement(int element);
			int size() const;

		class AscendingIterator
		{
			private:
				MagicalContainer& container;
				int index;

			public:
				// Constructors:
				AscendingIterator(MagicalContainer& container);
				AscendingIterator(const AscendingIterator& other);

				// Destructor:
				~AscendingIterator();

				// Assignment operator:
				AscendingIterator& operator=(const AscendingIterator& other);

				// Comparison operators:
				bool operator==(const AscendingIterator& other) const;
				bool operator!=(const AscendingIterator& other) const;
				bool operator<(const AscendingIterator& other) const;
				bool operator>(const AscendingIterator& other) const;

				// Dereference operator:
				int operator*() const;

				// Pre-increment operator:
				AscendingIterator& operator++();

				// Beginning and Ending of Iterator:
				AscendingIterator begin();
				AscendingIterator end();
    	};

		class SideCrossIterator
		{
			private:
				MagicalContainer& container;
				int index;

			public:
				// Constructors:
				SideCrossIterator(MagicalContainer& container);
				SideCrossIterator(const SideCrossIterator& other);

				// Destructor:
				~SideCrossIterator();

				// Assignment operator:
				SideCrossIterator& operator=(const SideCrossIterator& other);

				// Comparison operators:
				bool operator==(const SideCrossIterator& other) const;
				bool operator!=(const SideCrossIterator& other) const;
				bool operator<(const SideCrossIterator& other) const;
				bool operator>(const SideCrossIterator& other) const;

				// Dereference operator:
				int operator*() const;

				// Pre-increment operator:
				SideCrossIterator& operator++();

				// Beginning and Ending of Iterator:
				SideCrossIterator begin();
				SideCrossIterator end();
    	};

		class PrimeIterator
		{
			private:
				MagicalContainer& container;
				int index;

			public:
				// Constructors:
				PrimeIterator(MagicalContainer& container);
				PrimeIterator(const PrimeIterator& other);

				// Destructor:
				~PrimeIterator();

				// Assignment operator:
				PrimeIterator& operator=(const PrimeIterator& other);

				// Comparison operators:
				bool operator==(const PrimeIterator& other) const;
				bool operator!=(const PrimeIterator& other) const;
				bool operator<(const PrimeIterator& other) const;
				bool operator>(const PrimeIterator& other) const;

				// Dereference operator:
				int operator*() const;

				// Pre-increment operator:
				PrimeIterator& operator++();

				// Beginning and Ending of Iterator:
				PrimeIterator begin();
				PrimeIterator end();
    	};
    };
}
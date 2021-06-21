#pragma once
#include <iostream>
#include <fstream>
#include "Serializable.h"
#include <vector>

namespace elec
{
	class Counter
	{
	public:
		Counter() = default;
		Counter(const Counter& other) = delete;
		Counter(std::istream& in);

	public:
		Counter& operator=(const Counter& other) = delete;

	public:
		//adds one at a specific index
		void addOne(int index);
		//manually increase the vector size
		void increaseSize();
		//return the number at the specific index
		int get(int index) const;
		//return the sum of all the values in the counter
		int	getTotal() const;
		//return the size of the counter
		int size() const;
		//return the ratio in percentage between a specific index and the sum of all the indexes
		float getRatioInPercentage(int index);

		void save(std::ostream& out) const;

		void load(std::istream& in);

		void resize(int newSize);

	private:
		std::vector<int> _vector;
	};
}
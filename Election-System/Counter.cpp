#include "Counter.h"

#include <iostream>

namespace elec
{
	Counter::Counter(std::istream& in)
	{
		load(in);
	}

	void Counter::increaseSize()
	{
		_vector.resize(_vector.size() + 1);
	}

	int Counter::get(int index) const
	{
		return _vector[index];
	}

	int Counter::getTotal() const
	{
		int count = 0;
		for (int num : _vector)
			count += num;
		return count;
	}

	int Counter::size() const
	{
		return _vector.size();
	}

	float Counter::getRatioInPercentage(int index)
	{
		return (get(index) / static_cast<float>(getTotal())) * 100;
	}

	void Counter::save(std::ostream& out) const
	{
		int size = _vector.size();
		out.write(rcastccp(&size), sizeof(size));
		
		for (int num : _vector) {
			out.write(rcastccp(&num), sizeof(num));
		}

		if(!out.good())
			throw std::exception("Error: bad writing to file");
	}

	void Counter::load(std::istream& in)
	{
		int size;
		in.read(rcastcp(&size), sizeof(size));

		for (int i = 0; i < size; ++i)
		{
			int num;
			in.read(rcastcp(&num), sizeof(num));
			_vector.push_back(num);
		}

		if (!in.good())
			throw std::exception("Error: bad reading to file");
	}

	void Counter::resize(int newSize)
	{
		_vector.resize(newSize);
	}

	void Counter::addOne(int index)
	{
		++_vector[index];
	}
}
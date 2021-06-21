#include "Date.h"

#include <iostream>
#include <exception>

namespace elec
{
	Date::Date(int day, int month, int year)
		: _day(day), _month(month), _year(year)
	{
		if (day < 1 || day > 31 ||
			month < 1 || month > 12 ||
			year < 1)
		{
			throw std::invalid_argument("Error: invalid date format");
		}
	}

	Date::Date(const Date& other) : Date(other._day, other._month, other._year) {}

	void Date::setDay(int val)
	{
		if (val < 1 || val > 31)
			throw std::invalid_argument("Error: invalid day");
		else
			_day = val;
	}

	void Date::setMonth(int val)
	{
		if (val < 1 || val > 12)
			throw std::invalid_argument("Error: invalid month");
		else
			_month = val;
	}

	void Date::setYear(int val)
	{
		if (val < 1)
			throw std::invalid_argument("Error: invalid year");
		else
			_year = val;
	}

	std::ostream& operator<<(std::ostream& os, const Date& other)
	{
		os << other._day << '/' << other._month << '/' << other._year;
		return os;
	}

	void operator>>(std::istream& is, Date& other)
	{
		is >> other._day >> other._month >> other._year;
	}

	void Date::save(std::ostream& out) const
	{
		out.write(rcastccp(&_day), sizeof(_day));
		out.write(rcastccp(&_month), sizeof(_month));
		out.write(rcastccp(&_year), sizeof(_year));
	
		if (!out.good())
			throw std::exception("Error: bad writing");
	}

	void Date::load(std::istream& in)
	{
		in.read(rcastcp(&_day), sizeof(_day));
		in.read(rcastcp(&_month), sizeof(_month));
		in.read(rcastcp(&_year), sizeof(_year));

		if (!in.good())
			throw std::exception("Error: bad reading");
	}
}
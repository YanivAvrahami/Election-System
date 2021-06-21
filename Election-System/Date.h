#pragma once
#include "Serializable.h"
#include <iostream>
#include <fstream>

namespace elec
{
	class Date
	{
	public:
		Date() = default;
		Date(int day, int month, int year);
		Date(const Date& other);
		Date(std::istream& in) { load(in); }
				
		void setDay(int val);
		void setMonth(int val);
		void setYear(int val);

	public:
		friend std::ostream& operator<<(std::ostream& os, const Date& other);
		friend void operator>>(std::istream& is, Date& other);

	public:
		int getYear() const { return _year; }
		void save(std::ostream& out) const;
		void load(std::istream& in);

	private:
		int _day;
		int _month;
		int _year;
	};
}
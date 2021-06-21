#pragma once

#include <iostream>
#include <vector>

#define rcastccp reinterpret_cast<const char*>
#define rcastcp reinterpret_cast<char*>

class Serializable
{
public:
	Serializable() = default;

public:
	virtual void save(std::ostream& out) const = 0;
	virtual void load(std::istream& in) = 0;
};
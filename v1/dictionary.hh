#pragma once

#include "string_view.hh"

#include <unordered_set>
#include <string>

class SimpleDictionary
{
public:
	template<typename Collection>
	explicit SimpleDictionary(const Collection& words) :
		_container(words.cbegin(), words.cend())
	{}

	bool in_dictionary(string_view word) const
	{
		return _container.find(std::string{word}) != _container.end();
	}

private:
	std::unordered_set<std::string> _container;
};

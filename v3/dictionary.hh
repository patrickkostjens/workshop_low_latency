#pragma once

#include "string_view.hh"
#include "hashtable.hh"

#include <string>

class SimpleDictionary
{
public:
	template<typename Collection>
	explicit SimpleDictionary(const Collection& words) :
		_container(words)
	{}

	bool in_dictionary(string_view word) const
	{
		return _container.contains(word);
	}

private:
	Hashtable _container;
};

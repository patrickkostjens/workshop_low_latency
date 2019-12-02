#pragma once

#include "string_view.hh"

#include <vector>

class Hashtable
{
public:
	template<typename Collection>
	explicit Hashtable(const Collection& words)
	{
		std::size_t hashSize = 1;
		while (hashSize <= words.size())
		{
			hashSize <<= 1;
		}

		hashTable_.resize(hashSize);

		for(const std::string& s : words)
		{
			insert(s);
		}
		size_ = words.size();
	}

	bool contains(string_view word) const
	{
		auto hash = std::hash<string_view>()(word);

		auto idx = hash & (hashTable_.size()-1);
		std::size_t attempts = 0;

		while (attempts < size_)
		{
			const Entry& entry = hashTable_[idx];

			if (!entry.string)
				return false;

			if(entry.hash == hash && *entry.string == word)
				return true;

			idx = next(idx);
			attempts++;
		}
		return false;
	}

public:

	void insert(const std::string& s)
	{
		string_view sv(s);
		auto hash = std::hash<string_view>()(sv);
		auto idx = hash & (hashTable_.size()-1);

		while(true)
		{
			Entry& entry = hashTable_[idx];
			if (entry.string)
			{
				idx = next(idx);
			}
			else
			{
				entry.string = &s;
				entry.hash = hash;
				break;
			}
		}
	}

	std::size_t next(std::size_t idx) const { return (idx + 1) % hashTable_.size(); }

	struct Entry
	{
		std::size_t hash;
		const std::string* string = nullptr;
	};

	std::vector<Entry> hashTable_;
	std::size_t size_ = 0;

};

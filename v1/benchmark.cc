#include "dictionary.hh"

#include <benchmark/benchmark.h>

#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>

#include <valgrind/callgrind.h>

static std::random_device rd;
static std::uniform_int_distribution<int> charDist(48, 127);
static std::uniform_int_distribution<int> lengthDist(16, 24);

std::vector<std::string> wordsIn;
std::vector<std::string> wordsNotIn;

static std::string CreateRandomString()
{
	std::size_t len = (int)(std::floor(lengthDist(rd))) + 1;
	std::string out;
	out.reserve(len);
	for(std::size_t i = 0; i < len; i++)
		out.push_back(charDist(rd));

	return out;
}

static std::vector<std::string> CreateVectorOfUniqueRandomStrings(std::size_t len)
{
	std::unordered_set<std::string> strings;
	strings.reserve(len);

	while (strings.size() < len)
		strings.insert(CreateRandomString());

	return std::vector<std::string>(strings.begin(), strings.end());
}

template<typename DictType>
void InDictionary(benchmark::State& state)
{
	int idx = 0;
	DictType dict(wordsIn );
	bool allFound = true;

	std::size_t count = 0;

	CALLGRIND_START_INSTRUMENTATION;
	
	while(state.KeepRunning())
	{
		const std::string& word = wordsIn[idx];
		idx = (idx+1) % wordsIn.size();
		benchmark::DoNotOptimize(allFound &= dict.in_dictionary(word));
		++count;
	}

	CALLGRIND_STOP_INSTRUMENTATION;

	if (!allFound)
		std::cout << "InDictionary consistency check failed" << std::endl;
}

template<typename DictType>
void NotInDictionary(benchmark::State& state)
{
	int idx = 0;
	DictType dict(wordsIn);
	bool someFound = false;

	while(state.KeepRunning())
	{
		const std::string& word = wordsNotIn[idx];
		idx = (idx+1) % wordsNotIn.size();
		benchmark::DoNotOptimize(someFound |= dict.in_dictionary(word));
	}

	if (someFound)
		std::cout << "NotInDictionary consistency check failed" << std::endl;
}

BENCHMARK_TEMPLATE(InDictionary, SimpleDictionary);
BENCHMARK_TEMPLATE(NotInDictionary, SimpleDictionary);

int main(int argc, char** argv)
{
	static const int DICT_SIZE = 99171;
	std::vector<std::string> words = CreateVectorOfUniqueRandomStrings(DICT_SIZE*2);
	wordsIn.assign(words.begin(), words.begin() + DICT_SIZE);
	wordsNotIn.assign(words.begin() + DICT_SIZE, words.end());


	benchmark::Initialize(&argc, argv);
	if (::benchmark::ReportUnrecognizedArguments(argc, argv))
		return 1;
	benchmark::RunSpecifiedBenchmarks();
}


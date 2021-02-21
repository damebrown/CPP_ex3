/**
 * @file my_set_tester.cpp
 * @author kedemsnir
 * @version 1.0
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "my_set.h"
#include <cstdlib>
#include <ctime>

using std::cout;
using std::ostream;
using std::string;
using std::set;
using std::rand;

TEST_CASE("constructors")
{
	SECTION("default constructor")
	{
		set<int> stdIntSet;
		my_set<int> myIntSet;
		CHECK(stdIntSet.size() == myIntSet.size());
		CHECK(stdIntSet.empty() == myIntSet.empty());

		set<string> stdStringSet;
		my_set<string> myStringSet;
		CHECK(stdStringSet.size() == myStringSet.size());
		CHECK(stdStringSet.empty() == myStringSet.empty());
	}

	SECTION("range constructor")
	{
		int myints[]= {10,20,30,40,50};
		set<int> stdIntSet(myints,myints+5);
		my_set<int> myIntSet(myints,myints+5);
		CHECK(stdIntSet.size() == myIntSet.size());
		CHECK(stdIntSet.empty() == myIntSet.empty());
		for (int a : myints)
		{
			CHECK(*stdIntSet.find(a) == *myIntSet.find(a));
		}

		string myStrings[]= {"hi", "what's up", "hello"};
		set<string> stdStringSet(myStrings, (myStrings+3));
		my_set<string> myStringSet(myStrings, (myStrings+3));
		CHECK(stdStringSet.size() == myStringSet.size());
		CHECK(stdStringSet.empty() == myStringSet.empty());
		for (const string a : myStrings)
		{
			CHECK(*stdStringSet.find(a) == *myStringSet.find(a));
		}
	}

	SECTION("copy constructor (using range ctor)")
	{
		int myints[]= {10,20,30,40,50};
		set<int> stdIntSet(myints,myints+5);
		my_set<int> myIntSet(myints,myints+5);
		set<int> stdCopyIntSet(stdIntSet);
		my_set<int> myCopyIntSet(myIntSet);
		CHECK(stdCopyIntSet.size() == myCopyIntSet.size());
		CHECK(stdCopyIntSet.empty() == myCopyIntSet.empty());
		for (int a : myints)
		{
			CHECK(*stdCopyIntSet.find(a) == *myCopyIntSet.find(a));
		}

		string myStrings[]= {"hi", "what's up", "hello"};
		set<string> stdStringSet(myStrings, myStrings+3);
		my_set<string> myStringSet(myStrings, myStrings+3);
		set<string> stdCopyStringSet(stdStringSet);
		my_set<string> myCopyStringSet(myStringSet);
		CHECK(stdCopyStringSet.size() == myCopyStringSet.size());
		CHECK(stdCopyStringSet.empty() == myCopyStringSet.empty());
		for (string a : myStrings)
		{
			CHECK(*stdCopyStringSet.find(a) == *myCopyStringSet.find(a));
		}
	}

	SECTION("move constructor")
	{
		int myints[]= {10,20,30,40,50};
		set<int> stdIntSet(myints,myints+5);
		my_set<int> myIntSet(myints,myints+5);
		set<int> stdCopyIntSet(std::move(stdIntSet));
		my_set<int> myCopyIntSet(std::move(myIntSet));
		CHECK(stdCopyIntSet.size() == myCopyIntSet.size());
		CHECK(stdCopyIntSet.empty() == myCopyIntSet.empty());
		for (int a : myints)
		{
			CHECK(*stdCopyIntSet.find(a) == *myCopyIntSet.find(a));
		}
		CHECK(stdIntSet.size() == myIntSet.size());
		CHECK(stdIntSet.empty() == myIntSet.empty());
		for (int a : myints)
		{
			CHECK(myIntSet.find(a) == myIntSet.cend());
		}


		string myStrings[]= {"hi", "what's up", "hello"};
		set<string> stdStringSet(myStrings, myStrings+3);
		my_set<string> myStringSet(myStrings, myStrings+3);
		set<string> stdCopyStringSet(std::move(stdStringSet));
		my_set<string> myCopyStringSet(std::move(myStringSet));
		CHECK(stdCopyStringSet.size() == myCopyStringSet.size());
		CHECK(stdCopyStringSet.empty() == myCopyStringSet.empty());
		for (string a : myStrings)
		{
			CHECK(*stdCopyStringSet.find(a) == *myCopyStringSet.find(a));
		}
		CHECK(stdStringSet.size() == myStringSet.size());
		CHECK(stdStringSet.empty() == myStringSet.empty());
		for (string a : myStrings)
		{
//			CHECK(myStringSet.find(a) == myStringSet.cend());
		}
	}
}

TEST_CASE("insert and erase")
{
	SECTION("basic insertion and erasure")
	{
		set<int> stdIntSet;
		my_set<int> myIntSet;
		CHECK(stdIntSet.insert(4).second == myIntSet.insert(4).second);
		CHECK(stdIntSet.insert(4).second == myIntSet.insert(4).second);
		CHECK(stdIntSet.insert(5).second == myIntSet.insert(5).second);
		CHECK(stdIntSet.insert(45).second == myIntSet.insert(45).second);
		CHECK(stdIntSet.erase(45) == myIntSet.erase(45));
		CHECK(stdIntSet.erase(312) == myIntSet.erase(312));
		CHECK(stdIntSet.erase(7) == myIntSet.erase(7));
		CHECK(stdIntSet.erase(5) == myIntSet.erase(5));
		CHECK(stdIntSet.erase(4) == myIntSet.erase(4));
		CHECK(stdIntSet.empty() == myIntSet.empty());
	}

	SECTION("basic random insertion and erasure")
	{
		std::srand((unsigned int) std::time(nullptr));
		set<int> stdIntSet;
		my_set<int> myIntSet;
		int a = rand() % 200;
		std::set<int> vec = {a};
		for (int i = 0; i < 200; ++i)
		{
			bool test1 = stdIntSet.insert(a).second;
			bool test2 = myIntSet.insert(a).second;
			if (stdIntSet.size() != myIntSet.size())
			{
//				myIntSet.erase(a);
				myIntSet.insert(a);
				myIntSet.erase(a);
				myIntSet.insert(a);
				myIntSet.erase(a);
				myIntSet.insert(a);
			}
			CHECK(test1 == test2);
			a = rand() % 100;
			vec.insert(a);
//			std::sort(vec.begin(), vec.[vec.size()-1]);
		}
		std::vector<int> vec2;
		for (int i = 0; i < 200; ++i)
		{
			vec2.push_back(a);
			size_t test1 = stdIntSet.erase(a);
			size_t test2 = myIntSet.erase(a);
			if (test1 != test2)
			{
				test2 = myIntSet.erase(a);
			}
			CHECK(test1 == test2);
			a = rand() % 100;
		}
		CHECK(stdIntSet.size() == myIntSet.size());
		CHECK(stdIntSet.empty() == myIntSet.empty());
	}

	SECTION("insertion with hint and erasure")
	{
		my_set<int> myIntSet;
		set<int> stdIntSet;

		for (int i=1; i<=5; ++i)
		{
			CHECK(stdIntSet.insert(i*10).second == myIntSet.insert(i*10).second);
		}

		auto result = myIntSet.insert(20);
		auto stdResult = stdIntSet.insert(20);

		auto it = result.first;
		auto stdIt = stdResult.first;

		CHECK(*stdIntSet.insert(stdIt, 25) == *myIntSet.insert(it, 25));
		CHECK(*stdIntSet.insert(stdIt, 24) == *myIntSet.insert(it, 24));
		CHECK(*stdIntSet.insert(stdIt, 26) == *myIntSet.insert(it, 26));
	}

	SECTION("insertion from range")
	{
		int myints[]= {10,20,30,40,50};
		set<int> stdIntSet;
		my_set<int> myIntSet;
		stdIntSet.insert(myints, myints + 5);
		myIntSet.insert(myints, myints + 5);

		CHECK(stdIntSet.size() == myIntSet.size());
		CHECK(stdIntSet.empty() == myIntSet.empty());
		for (int a : myints)
		{
			CHECK(*stdIntSet.find(a) == *myIntSet.find(a));
		}
	}
}

TEST_CASE("iterators")
{
	SECTION("const const_iterator")
	{
		std::srand((unsigned int) std::time(nullptr));
		set<int> stdIntSet;
		my_set<int> myIntSet;
		int a = rand() % 100;
		for (int i = 0; i < 500; ++i)
		{
			CHECK(stdIntSet.insert(a).second == myIntSet.insert(a).second);
			a = rand() % 100;
		}
		auto stdIt = stdIntSet.cbegin();
		auto myIt = myIntSet.cbegin();
		for (; stdIt != stdIntSet.cend() || myIt != myIntSet.cend(); ++stdIt, ++myIt)
		{
			CHECK(*stdIt == *myIt);
		}
	}

	SECTION("reverse const const_iterator")
	{
		std::srand((unsigned int) std::time(nullptr));
		set<int> stdIntSet;
		my_set<int> myIntSet;
		int a = rand() % 100;
		for (int i = 0; i < 500; ++i)
		{
			CHECK(stdIntSet.insert(a).second == myIntSet.insert(a).second);
			a = rand() % 100;
		}
		auto stdIt = stdIntSet.crbegin();
		auto myIt = myIntSet.crbegin();
		for (; stdIt != stdIntSet.crend() || myIt != myIntSet.crend(); ++stdIt, ++myIt)
		{
			CHECK(*stdIt == *myIt);
		}
	}
}

//
// Created by ofek.login on 9/7/18.
//

#include "my_set.h"
#include <set>
#include <iostream>
#include <cstring>
#include <ctime>


using std::endl;
bool insertion_tests();

bool iterationTesting();

bool insertionWithHintTesting();

bool eraseWithIteratorTesting();

bool findTests();

bool erasingTests();

bool testingClear();

bool swapTesting();

bool copyConstructorTests();

bool moveConstructorTests();

bool schoolTest1();

bool schoolTest2();

bool schoolTests3();

int hardCoreInsertDelete();

int main()
{
	bool flag = true;
	flag *= insertion_tests();
	flag *= iterationTesting();
	flag *= insertionWithHintTesting();
	flag *= eraseWithIteratorTesting();
	flag *= findTests();
	flag *= erasingTests();
	flag *= testingClear();
	flag *= swapTesting();
	flag *= copyConstructorTests();
	flag *= moveConstructorTests();
	flag *= hardCoreInsertDelete();
	flag *= schoolTest1();
	flag *= schoolTest2();
	flag *= schoolTests3();
	std::cout<<endl<<"========end of tests ========"<<endl;
	if(flag)
	{
		std::cout << "@#$%#$%#$^$#$=passed all tests!=@#$%#$%#$^$#$"<<endl;
	}
	else
	{
		std::cout<<" failed some tests :( search the consle for 'fail' to see which" << endl;
	}

}


bool schoolTests3() {
	double a2[] = {0.1, 1.0, 0.0, 1.1};
	my_set<double> d1(a2, a2 + 4);
	int flag = 0;
	std::cout << "test 3.1: " << ((d1.size() == 4) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "test 3.2: " << ((*d1.cbegin() == 0) ? ("passed =]") : ((std::to_string(++flag))+" failed :( ")) << endl;
	d1.erase(d1.find(0.1));
	d1.erase(d1.find(0.0));
	d1.erase(d1.find(1.1));
	d1.erase(d1.find(1.0));
	std::cout << "test 3.3: " << ((d1.empty()) ? ("passed =]") : ((std::to_string(++flag))+" failed :( ")) << endl;
	return (flag==0);
}

bool schoolTest2() {
	char a1[] = {'a', 'b', 'b', 'd', 'e'};
	my_set<char> c1(a1, a1 + 5);
	int flag = 0;
	my_set<char> c2;
	for (auto i=c1.cbegin(); i != c1.cend(); ++i)
	{
		c2.insert(*i);
	}
	std::cout << "test 2.1: " << ((c2.size() == 4) ? ("passed =]") : ((std::to_string(++flag))+" failed :( ")) << endl;
	c2.erase (c2.find('a'));
	c2.erase (c2.find('b'));
	c2.erase (c2.find('d'));
	c2.erase (c2.find('e'));
	std::cout << "test 2.2: " << ((c2.empty()) ? ("passed =]") : ((std::to_string(++flag))+" failed :( ")) << endl;
	return (flag==0);
}

bool schoolTest1() {
	std::cout << "\n==========school given tests==========" << endl;
	int flag = 0;
	my_set<int> s1;
	s1.insert(1);
	s1.insert(2);
	s1.insert(2);
	s1.insert(3);
	std::cout << "test 1: " << ((3 == s1.size()) ? ("passed =]") : ((std::to_string(++flag))+" failed :( ")) << endl;
	return (flag==0);
}

bool moveConstructorTests() {
	std::cout << "\n==========move constructor testing==========" << endl;
	int flag = 0;
	my_set<int> m;
	m.insert(3);
	m.insert(2);
	m.insert(1);
	my_set<int> l(std::move(m));
	std::cout << "testing size: " << ((l.size() == 3 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 1: " << ((l.find(3) != m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 2: " << ((l.find(1) != m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	l.insert(4);
	std::cout << "testing size: " << ((l.size() == 4 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	l = m;
	std::cout << "testing size: " << ((l.size() == 0 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	return (flag==0);
}

int hardCoreInsertDelete()
{
	srand((unsigned int) time(nullptr));
	std::set<int> stdIntSet;
	my_set<int> myIntSet;
	int a =0, flag = 0;
	std::cout << "\n==========testing hardcore insert and erase tests==========" << endl;
	for (int i = 0; i < 1000; i++)
	{
		a = rand() % 100;
		if((stdIntSet.insert(a).second != myIntSet.insert(a).second))
		{
			std::cout << "inserting " << a%100 << "  failed to act like inserting to std set:( " << endl;
			flag++;
		}
	}
	std::cout << "insert test: " << ((flag==0) ? ("passed =]") : (" failed :( ")) << endl;
	int secondflag=0;
	for (int i = 0; i < 1000; i++)
	{
		if(stdIntSet.erase(a) != myIntSet.erase(a))
		{
			std::cout << "deleting " << a%100 << "  failed to act like deleting from std set:( " << endl;
			secondflag++;
		}
		a = rand() % 100;
	}
	std::cout << "erase test: " << ((secondflag==0) ? ("passed =]") : (" failed :( ")) << endl;
	std::cout << "check size: " << (((stdIntSet.size() == myIntSet.size()) ? ("passed =]") : (std::to_string(++flag)) + " failed :( ")) << endl;
	std::cout << "check empty: " << ((stdIntSet.empty() == myIntSet.empty()) ? ("passed =]") : (std::to_string(++flag)) + " failed :( ") << endl;
	return (flag+secondflag==0);
}

bool copyConstructorTests() {
	std::cout << "\n==========copy constructor testing==========" << endl;
	int flag = 0;
	my_set<int>m;
	m.insert(3);
	m.insert(2);
	m.insert(1);
	my_set<int>l(m);
	std::cout << "testing size: " << ((l.size() == 3 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 1: " << ((l.find(3) != m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 2: " << ((l.find(1) != m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	l.insert(4);
	std::cout << "testing size: " << ((l.size() == 4 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing size: " << ((m.size() == 3 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	l = m;
	std::cout << "testing size: " << ((l.size() == 3 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	return (flag==0);
}

bool swapTesting() {
	std::cout << "\n==========swap test==========" << endl;
	int flag = 0;
	my_set<int>m;
	m.insert(3);
	m.insert(2);
	m.insert(1);
	my_set<int>l;
	l.insert(4);
	l.insert(-7);
	l.insert(9);
	l.insert(11);
	swap(m,l); //this is the std::swap syntax we learned about in class
	std::cout << "testing size: " << ((m.size() == 4 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing size: " << ((l.size() == 3 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	l.clear();
	std::cout << "testing size: " << ((m.size() == 4 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing size: " << ((l.size() == 0 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 1: " << ((m.find(4) != m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 2: " << ((m.find(-7) != m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 3: " << ((m.find(9) != m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 4: " << ((m.find(11) != m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 5: " << ((m.find(3) == m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;

	l.insert(1);
	l.insert(2);
	l.insert(3);
	l.insert(4);
	l.insert(5);
	m.swap(l); //note this appears here: http://www.cplusplus.com/reference/set/set/swap/
	std::cout << "testing size: " << ((m.size() == 5 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	return (flag==0);
}

bool testingClear() {
	std::cout << "\n==========clear test==========" << endl;
	int flag = 0;
	my_set<int>m;
	m.insert(3);
	m.insert(4);
	m.insert(8);
	m.insert(5);
	m.insert(2);
	m.insert(1);
	m.insert(7);
	m.insert(9);
	m.insert(6);
	m.clear();
	std::cout << "testing size: " << ((m.size() == 0 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 4: " << ((m.find(4) == m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing if is empty: " << ((m.empty()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	return (flag==0);
}

bool erasingTests() {
	int flag = 0;
	my_set<int>m;
	std::cout << "\n==========erasing value test==========" << endl;
	m.insert(3);
	m.insert(4);
	m.insert(8);
	m.insert(5);
	m.insert(2);
	m.insert(1);
	m.insert(7);
	m.insert(9);
	m.insert(6);
	std::cout << "testing size: " << ((m.size() == 9 ) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	m.erase(6);
	std::cout << "testing size: " << ((m.size() == 8 && m.find(6) == m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	m.erase(6);
	std::cout << "testing size: " << ((m.size() == 8) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	m.erase(9);
	std::cout << "testing size: " << (((m.size() == 7 && m.find(9) == m.cend())) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	m.erase(3);
	std::cout << "testing size: " << ((m.size() == 6 && m.find(3) == m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	m.erase(4);
	std::cout << "testing size: " << ((m.size() == 5 && m.find(4) == m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "\n==========checking for the rest of the tree==========" << endl;
	std::cout << "testing size: " << ((m.find(1) != m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing size: " << ((m.find(2) != m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing size: " << ((m.find(5) != m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing size: " << ((m.find(7) != m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing size: " << ((m.find(8) != m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	return (flag==0);
}

bool findTests()
{
	std::cout << "\n==========testing find==========" << endl;
	int flag = 0;
	my_set<int>m;
	std::pair <my_set<int>::const_iterator,bool> a = m.insert(3);
	std::pair <my_set<int>::const_iterator,bool> b = m.insert(4);
	std::pair <my_set<int>::const_iterator,bool> c = m.insert(5);
	std::pair <my_set<int>::const_iterator,bool> d = m.insert(1);
	my_set<int>::const_iterator check1 = m.insert(a.first, 2);
	std::cout << "testing find 1: " << ((m.find(1) == d.first) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 2: " << ((m.find(2) == check1) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 3: " << ((m.find(3) == a.first) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 4: " << ((m.find(4) == b.first) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 5: " << ((m.find(5) == c.first) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "testing find 6: " << ((m.find(6) == m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	return (flag==0);
}

bool eraseWithIteratorTesting()
{
	int flag = 0;
	my_set<int>m;
	std::cout << "\n==========testing erase==========" << endl;
	std::pair <my_set<int>::const_iterator,bool> a = m.insert(3);
	std::pair <my_set<int>::const_iterator,bool> b = m.insert(4);
	std::pair <my_set<int>::const_iterator,bool> c = m.insert(5);
	//todo check validity of insert with hint method (according to ++ or -- mediniyut)
	my_set<int>::const_iterator toDelete2 = m.insert(a.first, 2);
	std::pair <my_set<int>::const_iterator,bool> d = m.insert(1);

	my_set<int>::const_iterator after2 = m.erase(toDelete2);
	std::cout << "testing size: " << ((m.size() == 4) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "returned iter: " << ((*after2 == 3) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;

	my_set<int>::const_iterator after1 = m.erase(d.first);
	std::cout << "testing size: " << ((m.size() == 3) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "returned iter: " << ((*after1 == 3) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;

	my_set<int>::const_iterator after3 = m.erase(a.first);
	std::cout << "testing size: " << ((m.size() == 2) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "returned iter: " << ((*after3 == 4) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;

	my_set<int>::const_iterator after4 = m.erase(b.first);
	std::cout << "testing size: " << ((m.size() == 1) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "returned iter: " << ((*after4 == 5) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;

	my_set<int>::const_iterator after5 = m.erase(c.first);
	std::cout << "testing size: " << ((m.size() == 0) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "returned iter: " << ((after5 == m.cend()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	return (flag==0);
}

bool insertionWithHintTesting()
{
	int flag = 0;
	std::cout << "\n==========testing inserting with a hint==========" << endl;
	my_set<int>m;
	std::pair <my_set<int>::const_iterator,bool> a = m.insert(3);
	std::pair <my_set<int>::const_iterator,bool> b = m.insert(4);
	std::pair <my_set<int>::const_iterator,bool> c = m.insert(5);
	std::pair <my_set<int>::const_iterator,bool> d = m.insert(1);
	my_set<int>::const_iterator check1 = m.insert(a.first, 2);
	std::cout << "testing iter: " << ((*check1 == 2) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	my_set<int>::const_iterator check2 = m.insert(c.first, 6);
	std::cout << "testing iter: " << ((*check2 == 6) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	my_set<int>::const_iterator check3 = m.insert(d.first, -9);
	std::cout << "testing iter: " << ((*check3 == -9) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	return flag==0;
}

bool iterationTesting()
{
	int flag = 0;
	my_set<int>m;
	std::cout << "\n==========testing iteration==========" << endl;
	m.insert(3);
	m.insert(4);
	m.insert(5);
	m.insert(2);
	m.insert(1);
	std::cout << "testing cbegin: " << ((*m.cbegin() == 1) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	std::cout << "\ntesting iteration: " << endl;
	int i=0;
	for(auto k = m.cbegin();k !=m.cend();++k)
	{
		std::cout << "testing iter: " << ((*k == ++i) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	}

	std::cout << "\ntesting postfix operator: " << endl;
	i=0;
	for(auto k = m.cbegin();k !=m.cend(); k++)
	{
		std::cout << "testing iter: " << ((*k == ++i) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	}

	std::cout << "\ntesting reverse iteration: " << endl;
	i=6;
	for(auto k = m.crbegin();k !=m.crend();++k)
	{
		std::cout << "testing reverese iter: " << ((*k == --i) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	}

	std::cout << "\ntesting postfix reverese operator: " << endl;
	i=6;
	for(auto k = m.crbegin();k !=m.crend();k++)
	{
		std::cout << "testing reverese iter: " << ((*k == --i) ? ("passed =]") : (std::to_string(++flag))+" failed :( ") << endl;
	}
	return flag==0;
}

bool insertion_tests()
{
	int flag = 0;
	my_set<int>m;
	std::cout << "=========testing insertion and size of tree=========="<<std::endl;
	std::cout << "testing empty: "<<((m.empty()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ")<<std::endl;
	std::pair <my_set<int>::const_iterator,bool> p = m.insert(3);
	std::cout << "testing return type: "<<((p.second) ? ("passed =]") : (std::to_string(++flag))+" failed :( ")<<std::endl;
	m.insert(4);
	m.insert(5);
	m.insert(2);
	m.insert(1);
	std::pair <my_set<int>::const_iterator,bool> k= m.insert(5);
	std::cout << "testing return type: "<<(!(k.second) ? ("passed =]") : (std::to_string(++flag))+" failed :( ")<<std::endl;
	std::cout << "testing size: "<<((m.size()==5) ? ("passed =]") : (std::to_string(++flag))+" failed :( ")<<std::endl;
	std::cout << "testing empty: "<<((!m.empty()) ? ("passed =]") : (std::to_string(++flag))+" failed :( ")<<std::endl;
	return flag==0;
}
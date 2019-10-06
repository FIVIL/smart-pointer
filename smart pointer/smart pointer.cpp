// smart pointer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include <typeinfo>
#define IN "in"
using namespace std;

template <class T>
class SmartPointerObject {
	T* value;
	int references;
public:
	void start() {
		value = new T;
		references = 0;
	}
	void set(T in) {
		*value = in;
		references++;
	}
	void reset(T in) {
		*value = in;
	}
	~SmartPointerObject()
	{
		references--;
		if (references == 0) {
			cout << "object with value: " << *value << " is cleard." << endl;
			delete(value);
		}
	}
	void operator=(SmartPointerObject<T> v) {
		//cout << "in" << endl;
		*value = v->value;
		references++;
	}
	int existance() {
		return references;
	}
	T get() {
		return *value;
	}
	T* getp() {
		return value;
	}

	void show() {
		cout << *value;
	}
	void morerefrence() {
		references++;
	}
};

template<class T>
class SmartPointerReference {
	SmartPointerObject<T>* sm;
public:
	void proc() {
		sm = new SmartPointerObject<T>;
		if (sm->existance() == 0)sm->start();
	}
	void proc(T v) {
		sm = new SmartPointerObject<T>;
		if (sm->existance() == 0)sm->start();
		sm->set(v);
	}
	void set(T v) {
		sm->reset(v);
	}
	void operator=(T p) {
		set(p);
	}
	T* addres() {
		return sm->getp();
	}

	void operator=(SmartPointerReference<T>& p) {
		//cout << IN << IN;
		if (sm == nullptr) {
			sm = p.sm;
			sm->morerefrence();
		}
		else {
			sm->~SmartPointerObject();
			//cout << sm->existance() << endl;
			if (sm->existance() > 0) {
				sm = p.sm;
				sm->morerefrence();
			}
			else {
				//cout << "if";
				delete(sm);
				sm = p.sm;
				sm->morerefrence();

			}
		}
	}
	T* operator ->() {
		return sm->getp();
	}
	T& operator *() {
		return *sm->getp();
	}
	static SmartPointerReference<T> newSmartPointer(T in) {
		SmartPointerReference<T> p;
		p.proc(in);
		p.sm->morerefrence();
		return p;
	}
	~SmartPointerReference()
	{
		sm->~SmartPointerObject();
		//cout << sm->existance() << endl;
		if (sm->existance() > 0) {
			sm = NULL;
		}
		else {
			//cout << "if";
			delete(sm);

		}
	}

	friend ostream& operator<<(ostream& os, SmartPointerReference<T>& p)
	{
		os << p.sm->get();
		return os;
	}

	int getr() {
		return sm->existance();
	}
};
void foo() {
	SmartPointerReference<int> sr1;
	sr1.proc(5);
}

int main()
{
	cout << "test automatic destructor at the end of function call:" << endl;
	foo();
	SmartPointerReference<int> sr1 = SmartPointerReference<int>::newSmartPointer(5);
	SmartPointerReference<int> sr2 = SmartPointerReference<int>::newSmartPointer(7);
	SmartPointerReference<int> sr3 = SmartPointerReference<int>::newSmartPointer(9);
	SmartPointerReference<string> sr4 = SmartPointerReference<string>::newSmartPointer("abcde");
	cout << "addres test:" << endl << sr1.addres() << endl;
	cout << "test -> operator: " << endl << "the value of string is: " << sr4 << " and the lenth of string is: " << sr4->length() << endl;
	cout << "test * operator:\n" << *sr1 << endl << "test = operator(reference assignment):" << endl;
	cout << sr1 << " " << sr2 << " " << sr3 << endl;
	cout << sr1.getr() << " " << sr2.getr() << " " << sr3.getr() << endl;
	sr1 = sr2;
	cout << sr1 << " " << sr2 << " " << sr3 << endl;
	cout << sr1.getr() << " " << sr2.getr() << " " << sr3.getr() << endl;
	sr2 = sr3;
	cout << sr1 << " " << sr2 << " " << sr3 << endl;
	cout << sr1.getr() << " " << sr2.getr() << " " << sr3.getr() << endl;
	sr1 = sr3;
	cout << sr1 << " " << sr2 << " " << sr3 << endl;
	cout << sr1.getr() << " " << sr2.getr() << " " << sr3.getr() << endl;
	cout << "test = operator(value assignment):" << endl;
	sr1 = 5;
	cout << sr1 << " " << sr2 << " " << sr3 << endl;
	cout << sr1.getr() << " " << sr2.getr() << " " << sr3.getr() << endl;
	int z;
	cin >> z;
	return 0;
}
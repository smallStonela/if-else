#pragma once

//
// Created by tom on 8/23/20.
//
#include <iostream>
using namespace std;

class Base
{
public:
	virtual ~Base() {}
	virtual std::string op() = 0;
};

//if has three memb

class Member1 : public Base
{
public:
	Member1(string name);
	virtual ~Member1();
public:
	virtual string op() override;
};

class Member2 : public Base
{
public:
	Member2(string name);
	virtual ~Member2();
public:
	virtual string op() override;
};

class Member3 : public Base
{
public:
	Member3(string name);
	virtual ~Member3();
public:
	virtual string op() override;
};



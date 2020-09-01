#pragma once

//变长参数实例 __VA_ARGS__ 替换省略号代表的字符串
#include <stdio.h>
#include <iostream>
#include <assert.h>
using namespace std;
#define LOG(...){\
	fprintf(stderr,"File: %s ,Func: %s ,Line: %d\t",__FILE__,__FUNCTION__,__LINE__);\
	fprintf(stderr,__VA_ARGS__);\
	fprintf(stderr,"\n");\
}


//（1）noexcept作为操作符noexcept(expression)，noexcept操作符不对expression求值。
	//若expression含有至少一个下列潜在求值的构造则结果为false：
	//[1] 调用没有指定不抛出异常的任意类型函数，除非它是常量表达式。
	//[2] throw表达式。
	//[3] 目标类型是引用类型，且转换时需要运行时检查的dynamic_cast表达式。
	//[4] 参数类型是多态类类型的typeid表达式。
//void test() { }
//void test_noexcept() noexcept(true) { }
//void test_noexcept_false() noexcept(false) { }
//cout << noexcept(test()) << endl;                       // false
//cout << noexcept(test_noexcept()) << endl;              // true
//cout << noexcept(test_noexcept_false()) << endl;        // false
//cout << noexcept(throw) << endl;                        // false

//Test test;
//Base& base = test;
//cout << noexcept(dynamic_cast<Test&>(base)) << endl;     // false
//cout << noexcept(typeid(base)) << endl;                  // false

//noexcept做操作符，应用于模板
//该函数是否是一个noexcept的函数取决于T()是否会抛出异常，
//第二个noexcept就是一个noexcept操作符，当其参数是一个有可能抛出异常的表达式的时候，其返回值为false，反之为true

template<class T>
void fun_template()noexcept(noexcept(T())) { throw 1; }

class Base0
{
public:
	void f() {}
};

class Base1 :public Base0
{
public:
	~Base1()noexcept(true) { }
};

class Log :public Base0
{
public:
	Log() {}

	//noexcept做模板
	~Log() noexcept(false) { }

	void LLog();
	void func_assert();

	void func_(int i, double j) throw(int, double);
	void func_throw();

	//方法一，仅添加一个noexcept修饰符，在抛出异常时,调用std::terminate中断程序执行，noexcept默认为noexcept(true)
	//比基于异常机制的throw()在效率上会高一些。这是因为异常机制会带来一些额外开销，
	void func_no_exce() noexcept;

	//方法二，添加一个noexcept修饰符和常量表达式（值为true，说明不会抛出异常；反之，则可能会抛出异常），在抛出异常时,调用std::terminate中断程序执行
	void func_no_exce(int val) noexcept(false);

	void fun_test_template();

};

void Log::LLog()
{
	LOG("Msg:%s", "I am error");
}

void Log::func_assert()
{
	// #error需要和ifdef 配合使用，判断某些特定条件
#ifdef _COMMPP
	std::cout << "all right!" << std::endl;
#else
//#error "this is error";
#endif

	//断言是在运行期进行验证，适用于Debug调试使用
	assert(sizeof(int) == 8);

	//静态断言编译阶段就可以验证
	//static_assert(sizeof(int) == 8, "This is Error!");
	static_assert(sizeof(int) == 4, "64-bit code generation is not supported.");
}

//动态异常声明，表明函数可能抛出的异常
void Log::func_(int i, double j) throw(int, double)
{
	int k = 0;
	k = j;

	if (i == 0)
	{
		throw i;                                    //除数为0，抛出异常
	}
	if (j == 0)
	{
		throw j;                                    //除数为0，抛出异常
	}
	int p = k / j;
}

void Log::func_throw()
{
	try
	{
		//func_(0,1.00);
		func_(1, 0.00);
	}
	catch (int)
	{
		printf("function first param is zero");
	}
	catch (double)
	{
		printf("function second param is zero");
	}
}


void Log::func_no_exce() noexcept
{
	throw 1;
}

void Log::func_no_exce(int val) noexcept(false)
{
	throw 1;
}

void Log::fun_test_template()
{
	cout << noexcept(Log()) << endl;
	cout << noexcept(Base1()) << endl;
	try
	{
		fun_template<Log>();
	}
	catch (...)
	{
		cout << "throw fun_template Log" << endl;   //// throw
	}

	try
	{
		fun_template<Base1>();   // terminate
	}
	catch (...)
	{
		cout << "throw fun_template Base1" << endl;
	}
}

//快速初始化成员变量
class InitVal 
{
public:
	InitVal(); 
	InitVal(int val_1, int val_2);
	InitVal(int val) :val1(val), val2(val){}
	
	~InitVal() {}
private:
	//普通成员就地初始化
	int val0 = 0;
	//普通成员变量
	int val1, val2;
	//静态成员变量
	static long val3;
	//静态常量成员
	static const long val4=0;
	//使用花括号就地初始化
	string b{ "hello" };
};
 long InitVal::val3 = 0;

 //构造函数体内初始化
 InitVal::InitVal()
 {
	 val1 = 0;
	 val2 = 0;
 }
 //构造函数初始化列表
InitVal::InitVal(int val_1, int val_2):val1(val_1), val2(val_2)
{
}


//友元 friend  扩展的友元
//声明一个类为另外一个类的友元时，不再需要使用class关键字
//声明友元类时，甚至可以使用类的别名。

class Car;
typedef Car BC;

class BYD 
{
	friend class Car; //C98标准、C++11标准
};

class ChangAn 
{
	friend Car;	//C++11标准
};

class JILi 
{
	//使用别名
	friend BC;//C++11标准
};

//为类模板声明友元			//C++11标准
template <typename T>
class BenChiCar 
{
	friend T;
};

//BenChiCar<Car> bc;
////int的友元声明会被忽略
//BenChiCar<int> bc;
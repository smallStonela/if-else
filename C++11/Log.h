#pragma once

//�䳤����ʵ�� __VA_ARGS__ �滻ʡ�ԺŴ�����ַ���
#include <stdio.h>
#include <iostream>
#include <assert.h>
using namespace std;
#define LOG(...){\
	fprintf(stderr,"File: %s ,Func: %s ,Line: %d\t",__FILE__,__FUNCTION__,__LINE__);\
	fprintf(stderr,__VA_ARGS__);\
	fprintf(stderr,"\n");\
}


//��1��noexcept��Ϊ������noexcept(expression)��noexcept����������expression��ֵ��
	//��expression��������һ������Ǳ����ֵ�Ĺ�������Ϊfalse��
	//[1] ����û��ָ�����׳��쳣���������ͺ������������ǳ������ʽ��
	//[2] throw���ʽ��
	//[3] Ŀ���������������ͣ���ת��ʱ��Ҫ����ʱ����dynamic_cast���ʽ��
	//[4] ���������Ƕ�̬�����͵�typeid���ʽ��
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

//noexcept����������Ӧ����ģ��
//�ú����Ƿ���һ��noexcept�ĺ���ȡ����T()�Ƿ���׳��쳣��
//�ڶ���noexcept����һ��noexcept�����������������һ���п����׳��쳣�ı��ʽ��ʱ���䷵��ֵΪfalse����֮Ϊtrue

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

	//noexcept��ģ��
	~Log() noexcept(false) { }

	void LLog();
	void func_assert();

	void func_(int i, double j) throw(int, double);
	void func_throw();

	//����һ�������һ��noexcept���η������׳��쳣ʱ,����std::terminate�жϳ���ִ�У�noexceptĬ��Ϊnoexcept(true)
	//�Ȼ����쳣���Ƶ�throw()��Ч���ϻ��һЩ��������Ϊ�쳣���ƻ����һЩ���⿪����
	void func_no_exce() noexcept;

	//�����������һ��noexcept���η��ͳ������ʽ��ֵΪtrue��˵�������׳��쳣����֮������ܻ��׳��쳣�������׳��쳣ʱ,����std::terminate�жϳ���ִ��
	void func_no_exce(int val) noexcept(false);

	void fun_test_template();

};

void Log::LLog()
{
	LOG("Msg:%s", "I am error");
}

void Log::func_assert()
{
	// #error��Ҫ��ifdef ���ʹ�ã��ж�ĳЩ�ض�����
#ifdef _COMMPP
	std::cout << "all right!" << std::endl;
#else
//#error "this is error";
#endif

	//�������������ڽ�����֤��������Debug����ʹ��
	assert(sizeof(int) == 8);

	//��̬���Ա���׶ξͿ�����֤
	//static_assert(sizeof(int) == 8, "This is Error!");
	static_assert(sizeof(int) == 4, "64-bit code generation is not supported.");
}

//��̬�쳣�������������������׳����쳣
void Log::func_(int i, double j) throw(int, double)
{
	int k = 0;
	k = j;

	if (i == 0)
	{
		throw i;                                    //����Ϊ0���׳��쳣
	}
	if (j == 0)
	{
		throw j;                                    //����Ϊ0���׳��쳣
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

//���ٳ�ʼ����Ա����
class InitVal 
{
public:
	InitVal(); 
	InitVal(int val_1, int val_2);
	InitVal(int val) :val1(val), val2(val){}
	
	~InitVal() {}
private:
	//��ͨ��Ա�͵س�ʼ��
	int val0 = 0;
	//��ͨ��Ա����
	int val1, val2;
	//��̬��Ա����
	static long val3;
	//��̬������Ա
	static const long val4=0;
	//ʹ�û����ž͵س�ʼ��
	string b{ "hello" };
};
 long InitVal::val3 = 0;

 //���캯�����ڳ�ʼ��
 InitVal::InitVal()
 {
	 val1 = 0;
	 val2 = 0;
 }
 //���캯����ʼ���б�
InitVal::InitVal(int val_1, int val_2):val1(val_1), val2(val_2)
{
}


//��Ԫ friend  ��չ����Ԫ
//����һ����Ϊ����һ�������Ԫʱ��������Ҫʹ��class�ؼ���
//������Ԫ��ʱ����������ʹ����ı�����

class Car;
typedef Car BC;

class BYD 
{
	friend class Car; //C98��׼��C++11��׼
};

class ChangAn 
{
	friend Car;	//C++11��׼
};

class JILi 
{
	//ʹ�ñ���
	friend BC;//C++11��׼
};

//Ϊ��ģ��������Ԫ			//C++11��׼
template <typename T>
class BenChiCar 
{
	friend T;
};

//BenChiCar<Car> bc;
////int����Ԫ�����ᱻ����
//BenChiCar<int> bc;
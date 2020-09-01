// C++11.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "Log.h"
#include "TemplateCls.h"
#include "Base.h"
#include "MembFactory.h"
#include <string>
using namespace std;

//声明方式
//template <typename T1,typename T2....> 应用于函数头
//template <class T1,class T2....>	应用于类头
//调用方式
//Func(a,b); 自动类型推导，类型要相同
//Func<T1,T2....>(a,b)显示类型调用

void mySwap(int &a, int &b)
{
	cout << __FUNCTION__ << endl;
	int t;
	t = a;
	a = b;
	b = t;

	cout << "a="<<a<<",b="<<b << endl;
}

template <typename T>
void mySwap(T &a, T&b)
{
	cout << __FUNCTION__ <<"typename" << endl;
	T t;
	t = a;
	a = b;
	b = t;
	cout << "a=" << a << ",b=" << b << endl;
}

//template <typename T>
//T mySwap(T &a, T&b)
//{
//	cout << __FUNCTION__ << "typename" << endl;
//	T t;
//	t = a;
//	a = b;
//	b = t;
//	cout << "a=" << a << ",b=" << b << endl;
//	retunr t;
//}


#if 0
//函数模板做参数
template <typename T1,typename T2>
void sortArray(T1 *a,T2 num) 
{
	T1 tmp;
	int i, j;
	for (i = 0; i < num; i++) 
	{
		for (j = i + 1; j < num; j++) 
		{
			if (a[i] <a[j]) 
			{
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}
}

template<class T>
void PrintArr(T* a,int num) 
{
	int i = 0;
	for (; i < num; i++) 
	{
		cout << a[i] << "";
	}
}
#endif
int main()
{
    std::cout << "Hello World!\n"; 
	//Log log;
	//log.LLog();	
	//log.func_throw();
	//try
	//{
	//	log.func_no_exce(); //不抛异常 
	//	//log.func_no_exce(0); //抛出异常，被catch捕获
	//}
	//catch (...)
	//{
	//	std::cout << "func_no_exce!\n";
	//}
	//log.fun_test_template();


	//int a = 1, b = 2;
	////当普通函数和函数模板重载时，如果隐式调用，编译器会优先普通函数
	//mySwap(a, b);//自动类型推导

	//mySwap<>(a, b);//显示类型调用
	//mySwap<int>(a, b);//显示类型调用
	//cout << "a=" << a << ",b=" << b << endl;

	
	JudgeRole judgeRole;
	judgeRole.InitializeRole();
	string meb1 = judgeRole.Judge("Member1");
	string meb2 = judgeRole.Judge("Member2");
	string meb3 = judgeRole.Judge("Member3");

	std::cout << meb1 << std::endl;
	std::cout << meb2 << std::endl;
	std::cout << meb3 << std::endl;



#if 0
	char arr[] = "ddadeeettttt";
	int num = strlen(arr);

	cout << "排序之前:" << "";
	PrintArr<char>(arr,num);

	sortArray<char,int>(arr, num); //显示类型调用

	cout << "排序之后:" << "";
	PrintArr(arr, num);
#endif

}

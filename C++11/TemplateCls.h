#pragma once
#include <iostream>
using namespace std;


	class TemplateCls
	{
	public:
		TemplateCls();
		~TemplateCls();

	public:
		template <typename T>
		void swap(T &a, T&b);
	};



	//减少if-elese语法的冗余做法

	class InterBase
	{
	public:
		virtual void process() = 0;
	};

	class Base11 :public InterBase
	{
	public:
		Base11() {}
		virtual ~Base11() {}
	public:
		void process() override
		{
			cout << __FUNCTION__ << ",process is called" << endl;
		}

	};

	class Base2 :public InterBase
	{
	public:
		Base2() {}
		virtual ~Base2() {}
	public:
		void process() override
		{
			cout << __FUNCTION__ << ",process is called" << endl;
		}
	};

	enum EnumObj
	{
		Base1 = 0,
		BASE2,
		BASE3,
		BASE4
	};

	class MatchObj
	{
	private:
		MatchObj() {}
		MatchObj(MatchObj&) {}
		~MatchObj() {}
		static MatchObj *m_Obj;
	public:
		EnumObj e_obj;
	public:
		static MatchObj* getInstance()
		{
			if (m_Obj == nullptr)
			{
				m_Obj = new MatchObj();
			}
			return m_Obj;
		}

		InterBase* Match(EnumObj obj)
		{
			InterBase* b_BaseObj = nullptr;
			switch (obj)
			{
			case Base1:
				b_BaseObj = new Base11();
				break;
			case BASE2:
				b_BaseObj = new Base2();
				break;
			case BASE3:
				//b_BaseObj = new Base3();
				break;
			case BASE4:
				//b_BaseObj = new Base4();
				break;
			default:
				break;
			}
			return b_BaseObj;
		}
	};



#pragma once

#include <iostream>
#include <map>
#include "Base.h"
using namespace std;
class MembFactory
{
private:
	MembFactory();
	virtual ~MembFactory();
	//jin zhi copy constructor // 禁止外部拷贝和赋值操作
	MembFactory(const MembFactory& mb);
	const MembFactory &operator=(const MembFactory& mb);
public:
	// 保存注册过的角色，key:角色名称 , value:角色指针对象
	std::map<std::string, Base *> m_RoleRegistry;
	static MembFactory* instance;
public:
	static MembFactory* GetInstance();

	static void FreeInstance();
public:
	void RegisterMemb(const std::string& name, Base* registrar);
	Base* GetMemb(const std::string& name);
};

class JudgeRole
{
public:
	std::string Judge(const std::string &roleName)
	{
		return MembFactory::GetInstance()->GetMemb(roleName)->op();
	}

	void InitializeRole() // 初始化角色到工厂
	{
		static bool bInitialized = false;
		if (bInitialized == false)
		{
			// 注册系统管理员
			MembFactory::GetInstance()->RegisterMemb("Member1", new Member1("Member1"));
			// 注册订单管理员
			MembFactory::GetInstance()->RegisterMemb("Member2", new Member2("Member2"));
			// 注册普通用户
			MembFactory::GetInstance()->RegisterMemb("Member3", new Member3("Member3"));
			bInitialized = true;
		}
	}

};
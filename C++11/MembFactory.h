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
	//jin zhi copy constructor // ��ֹ�ⲿ�����͸�ֵ����
	MembFactory(const MembFactory& mb);
	const MembFactory &operator=(const MembFactory& mb);
public:
	// ����ע����Ľ�ɫ��key:��ɫ���� , value:��ɫָ�����
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

	void InitializeRole() // ��ʼ����ɫ������
	{
		static bool bInitialized = false;
		if (bInitialized == false)
		{
			// ע��ϵͳ����Ա
			MembFactory::GetInstance()->RegisterMemb("Member1", new Member1("Member1"));
			// ע�ᶩ������Ա
			MembFactory::GetInstance()->RegisterMemb("Member2", new Member2("Member2"));
			// ע����ͨ�û�
			MembFactory::GetInstance()->RegisterMemb("Member3", new Member3("Member3"));
			bInitialized = true;
		}
	}

};
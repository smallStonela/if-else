#include "pch.h"
#include "MembFactory.h"

MembFactory* MembFactory::instance = new MembFactory();

MembFactory::MembFactory()
{
}


MembFactory::~MembFactory()
{
}

MembFactory* MembFactory::GetInstance()
{
	return instance;
}
void MembFactory::FreeInstance()
{
	delete instance;
	instance = nullptr;
}

void MembFactory::RegisterMemb(const std::string& name, Base* registrar)
{
	m_RoleRegistry[name] = registrar;
	std::cout << "register size" << m_RoleRegistry.size() << std::endl;
}
Base* MembFactory::GetMemb(const std::string& name)
{
	std::map<std::string, Base*>::iterator it;
	// ��map�ҵ��Ѿ�ע����Ľ�ɫ�������ؽ�ɫָ�����
	it = m_RoleRegistry.find(name);
	if (it != m_RoleRegistry.end())
	{
		return it->second;
	}
	return nullptr; // δע��ý�ɫ���򷵻ؿ�ָ��
}




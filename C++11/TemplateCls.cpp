#include "pch.h"
#include "TemplateCls.h"

MatchObj* MatchObj::m_Obj = nullptr;

TemplateCls::TemplateCls()
{
}


TemplateCls::~TemplateCls()
{
}


template <typename T>
void TemplateCls::swap(T &a, T&b)
{
	T t;
	t = a;
	a = b;
	b = t;
}

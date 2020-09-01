#pragma once

/**********
	容器部分主要由头文件<vector>, <list>, <deque>, <set>, <map>, <stack> 和<queue>组成。
	对于常用的一些容器和容器适配器（可以看作由其它容器实现的容器），可以通过下表总结

	1.序列容器--->元素都有固定位置和顺序，取决于插入时间和地点
		vector、deque、list  
	2.关联式容器--->元素位置取决于特定的排序规则
		set、multiset、map、multimap
	数据结构：
		--------------------------------------------------------------------------------------------|
		|数据结构					|	描述												 |	实现头文件	|
		|向量(vector)			|	连续存储的元素	<vector>							 |				|
		|列表(list)				|	由节点组成的双向链表，每个结点包含着一个元素				 |	<list>		|
		|双队列(deque)			|	连续存储的指向不同元素的指针所组成的数组				 | 	<deque>		|
		|集合(set)				|	由节点组成的红黑树，每个节点都包含着一个元素，			 |	<set>		|
		|						|	节点之间以某种作用于元素对的谓词排列，没有两个			 |				|
		|						|	不同的元素能够拥有相同的次序							 |				|
		|多重集合(multiset)		|	允许存在两个次序相等的元素的集合						 |	<set>		|
		|栈(stack)				|	后进先出的值的排列									 |	<stack>		|
		|队列(queue)				|	先进先出的执的排列									 |	<queue>		|
		|优先队列(priority_queue)	|	元素的次序是由作用于所存储的值对上的某种谓词决定的的一种队列 |	<queue>		|
		|映射(map)				|	由{键，值}对组成的集合，以某种作用于键对上的谓词排列		 |	<map>		|
		|多重映射(multimap)		|	允许键对有相等的次序的映射							 |	<map>		|
		---------------------------------------------------------------------------------------------
	3.迭代器
		头文件<utility>,<iterator>和<memory>


**********/
#include <iostream>
using namespace std;
class Container
{
public:
	virtual ~Container() {}
public:
	virtual int process() = 0;
};

class MVector : public Container 
{
public:
	MVector();
	virtual ~MVector();
public:
	virtual int process() override;
};


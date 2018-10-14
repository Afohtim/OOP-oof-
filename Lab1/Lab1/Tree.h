#pragma once
#include<iostream>


template<typename TValue>
struct TNode
{
	explicit TNode( TValue value) : value(value) {};
	unsigned key;
	TValue value;
};

template<typename TValue>
class Tree
{
private:
public:
	Tree() {};
	virtual ~Tree() {};

};
#pragma once
#include "keyhouse.h"
//��Ϸ�п��ܳ���һЩ����
class Tool
{
public:
	virtual void draw() {};
};

class hpmp_bar :public Tool
{
public:
	hpmp_bar(int,int,int*,int*);
	void draw() override;

private:
	int max_hp;
	int max_mp;

	int* hp;
	int* mp;
};


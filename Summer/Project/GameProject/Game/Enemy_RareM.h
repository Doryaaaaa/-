#pragma once
#include "../Base/Base.h"

class Enemy_RareM : public Base {
private:
	int m_cnt;
	int flag;
public:
	Enemy_RareM();
	void Update();
};


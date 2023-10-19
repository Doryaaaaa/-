#pragma once
#include "../Base/Base.h"

class Field : public Base {
private:
	//画像オブジェクト
	CImage m_img;
public:
	//コンストラクタ
	Field();
	//描画
	void Draw();
};

#pragma once
#include "../Base/Base.h"

class Field : public Base {
private:
	//�摜�I�u�W�F�N�g
	CImage m_img;
public:
	//�R���X�g���N�^
	Field();
	//�`��
	void Draw();
};

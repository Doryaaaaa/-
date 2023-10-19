#include "Title.h"
#include "../Game/Game.h"

Title::Title() :Base(eType_Scene),
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
    m_img = COPY_RESOURCE("Title", CImage);
}

Title::~Title()
{
    //�S�ẴI�u�W�F�N�g��j��
    Base::KillAll();
    //�Q�[���V�[����
    Base::Add(new Game());
}

void Title::Update()
{
    //�{�^���P�Ń^�C�g���j��
    if (PUSH(CInput::eButton1)) {
        SetKill();
    }
}

char textdate[][512] = {
    "�����ł�",
    "����ɂ��́I",
    "�������Ă��ł����H",
};

void Title::Draw()
{
    m_img.Draw();
    int index = 0;
    m_title_text.Draw(0,64,1, 1, 1, textdate[index]);
    m_img.SetPos(700, 440);
}

#include "Title.h"
#include "../Game/Game.h"

Title::Title() :Base(eType_Scene),
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
    m_img = COPY_RESOURCE("Title", CImage);
}

Title::~Title()
{
    //全てのオブジェクトを破棄
    Base::KillAll();
    //ゲームシーンへ
    Base::Add(new Game());
}

void Title::Update()
{
    //ボタン１でタイトル破棄
    if (PUSH(CInput::eButton1)) {
        SetKill();
    }
}

char textdate[][512] = {
    "初見です",
    "こんにちは！",
    "今何してるんですか？",
};

void Title::Draw()
{
    m_img.Draw();
    int index = 0;
    m_title_text.Draw(0,64,1, 1, 1, textdate[index]);
    m_img.SetPos(700, 440);
}

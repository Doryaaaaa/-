#include "UI.h"
#include "GameData.h"
#include "Player.h"
UI::UI() : Base(eType_UI) {
	m_img = COPY_RESOURCE("UI", CImage);
}

void UI::Draw() {
	int score = GameData::s_score;
	for (int i = 0; i < 8; i++, score /= 10) {
		int s = score % 10;
		m_img.SetRect(64 * s, 0, 64 * s + 64, 64);
		m_img.SetSize(55, 55);
		m_img.SetPos(220 - 32 * i, 3);
		m_img.Draw();
	}
	Base* Player = Base::FindObject(eType_Player);
	if (Player == nullptr) {
		//ゲームオーバーの表示
		m_img.SetRect(0, 64, 0 + 512, 128 + 0);
		m_img.SetSize(512, 64);
		m_img.SetPos(700, 440);
		m_img.Draw();
	}
}
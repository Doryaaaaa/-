#include "Slash.h"

Slash::Slash(const CVector2D& pos, bool flip, int type, int attack_no) :Base(type) {
	//画像複製
	m_img = COPY_RESOURCE("Effect_Slash", CImage);
	//反転フラグ設定
	m_flip = flip;
	//座標設定
	m_pos = pos;
	//表示サイズ設定
	m_img.SetSize(64, 64);
	//中心位置設定
	m_img.SetCenter(32, 32);
	//当たり判定用矩形
	m_rect = CRect(-32, -32, 32, 32);
	//再生アニメーション設定（非ループ）
	m_img.ChangeAnimation(0, false);
	//攻撃番号
	m_attack_no = attack_no;
}

void Slash::Update() {
	//アニメーション更新
	m_img.UpdateAnimation();
	//アニメーション終了チェック
	if (m_img.CheckAnimationEnd()) {
		//エフェクトを削除
		SetKill();
	}
}

void Slash::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	//DrawRect();
}
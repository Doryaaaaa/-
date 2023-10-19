#include "Game.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyM1.h"
#include "EnemyM2.h"
#include "Enemy_Rare.h"
#include "Enemy_RareM.h"
#include "UI.h"
#include "../Title/Title.h"

Game::Game() :Base(eType_Scene) {
	Base::Add(new Player(CVector2D(1000, 500), false));
	Base::Add(new EnemyM1());
	Base::Add(new EnemyM2());
	Base::Add(new Enemy_RareM());
	Base::Add(new Field);
	Base::Add(new UI);
}

Game::~Game() {
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�^�C�g���V�[����
	Base::Add(new Title());
}

void Game::Update() {
	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}

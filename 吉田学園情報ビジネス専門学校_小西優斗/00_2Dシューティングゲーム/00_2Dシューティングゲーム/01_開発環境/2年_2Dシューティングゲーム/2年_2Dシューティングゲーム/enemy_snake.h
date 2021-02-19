#ifndef _ENEMY_SNAKE_H_
#define _ENEMY_SNAKE_H_
//=============================================================================
//
// �X�l�[�N�G�l�~�[�N���X�w�b�_�[ [enemy_snake.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"

//=============================================================================
// �G�l�~�[�N���X
//=============================================================================
class CEnemySnake : public CEnemy
{
public:
	CEnemySnake(TYPE Priority = TYPE_ENEMY);	// �R���X�g���N�^
	~CEnemySnake();							// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	void MoveUpdate(void);										// �΂߈ړ��̏���
	void BulletUpdate(void);									// �e�̍X�V����

	static CEnemySnake * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype);				// �G�l�~�[����
private:
	int m_nSwitchCounter;			// �X�C�b�`�̃J�E���^�[
	bool m_bSnakeSwitch;			// �X�C�b�`�̃t���O
};

#endif
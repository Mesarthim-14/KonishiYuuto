#ifndef _ENEMY_THROUGH_H_
#define _ENEMY_THROUGH_H_
//=============================================================================
//
// �^�������e��łG�l�~�[�N���X�w�b�_�[ [enemy_through.h]
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
class CEnemyThrough : public CEnemy
{
public:
	CEnemyThrough(TYPE Priority = TYPE_ENEMY);	// �R���X�g���N�^
	~CEnemyThrough();							// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	void MoveUpdate(void);											// �΂߈ړ��̏���
	void BulletUpdate(void);										// �e�̍X�V

	static CEnemyThrough * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype);				// �G�l�~�[����

private:
	int m_nStopCounter;		// �~�܂��Ă��鎞�Ԃ̃J�E���g
	int m_nContinueInter;	// �e�̏o��Ԋu
	int m_nBulletNum;		// �e�̃J�E���^�[
	bool m_bTwo_Sides;		// �^�������e��łG�̃t���O
};

#endif
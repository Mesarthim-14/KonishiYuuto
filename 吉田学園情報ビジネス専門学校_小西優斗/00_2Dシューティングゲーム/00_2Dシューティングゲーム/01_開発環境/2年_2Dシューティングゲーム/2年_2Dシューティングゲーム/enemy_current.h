#ifndef _ENEMY_CURRENT_H_
#define _ENEMY_CURRENT_H_
//=============================================================================
//
// ���@�Ǐ]�e��łG�l�~�[�N���X�w�b�_�[ [enemy_current.h]
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
class CEnemyCurrent : public CEnemy
{
public:
	CEnemyCurrent(TYPE Priority = TYPE_ENEMY);	// �R���X�g���N�^
	~CEnemyCurrent();							// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	void MoveUpdate(void);											// �΂߈ړ��̏���
	void BulletUpdate(void);										// �e�̍X�V
	
	static CEnemyCurrent * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype);				// �G�l�~�[����
private:
	int m_nContinueInter;		// �e�̏o��Ԋu
	int m_nBulletNum;			// �e�̃J�E���^�[
};

#endif
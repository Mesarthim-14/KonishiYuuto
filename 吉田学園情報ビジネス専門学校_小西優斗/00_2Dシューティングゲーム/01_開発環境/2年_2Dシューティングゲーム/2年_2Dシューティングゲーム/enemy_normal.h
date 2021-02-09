#ifndef _ENEMY_NORMAL_H_
#define _ENEMY_NORMAL_H_
//=============================================================================
//
// �ʏ�G�l�~�[�N���X�w�b�_�[ [enemy_normal.h]
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
class CEnemyNormal : public CEnemy
{
public:
	CEnemyNormal(TYPE Priority = TYPE_ENEMY);	// �R���X�g���N�^
	~CEnemyNormal();							// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	void MoveUpdate(void);										// �΂߈ړ��̏���
	void BulletUpdate(void);									// �e�̍X�V����

	static CEnemyNormal * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype);				// �G�l�~�[����
private:

};

#endif
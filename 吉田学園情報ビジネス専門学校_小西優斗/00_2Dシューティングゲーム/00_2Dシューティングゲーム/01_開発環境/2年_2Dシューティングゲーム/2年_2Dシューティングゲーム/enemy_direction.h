#ifndef _ENEMY_DIRECTION_H_
#define _ENEMY_DIRECTION_H_
//=============================================================================
//
// �����]���̓G�G�l�~�[�N���X�w�b�_�[ [enemy_direction.h]
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
class CEnemyDirection : public CEnemy
{
public:
	CEnemyDirection(TYPE Priority = TYPE_ENEMY);	// �R���X�g���N�^
	~CEnemyDirection();							// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	void MoveUpdate(void);										// �΂߈ړ��̏���
	void BulletUpdate(void);									// �e�̍X�V����

	static CEnemyDirection * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type,
		COLOR_TYPE Ctype, ENEMY_TYPE Etype, int nNumber);				// �G�l�~�[����
private:
	int m_nDirection;			// ���E�̔ԍ�
};

#endif
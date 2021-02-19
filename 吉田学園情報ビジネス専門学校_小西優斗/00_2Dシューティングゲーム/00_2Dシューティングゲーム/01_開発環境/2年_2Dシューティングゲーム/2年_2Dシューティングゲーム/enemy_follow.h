#ifndef _ENEMY_FOLLOW_H_
#define _ENEMY_FOLLOW_H_
//=============================================================================
//
// �Ǐ]�G�l�~�[�N���X�w�b�_�[ [enemy_follow.h]
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
class CEnemyFollow : public CEnemy
{
public:
	CEnemyFollow(TYPE Priority = TYPE_ENEMY);	// �R���X�g���N�^
	~CEnemyFollow();							// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	void MoveUpdate(void);										// �΂߈ړ��̏���
	void BulletUpdate(void);									// �e�̍X�V����
	void Appearance(void);

	static CEnemyFollow * Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype);				// �G�l�~�[����
private:
	int m_nFollowCounter;	// �Ǐ]�܂ł̎���
	int m_nSubNum;			// ���Z�l
	int m_nSubNumber;		// �����x�̒l
	bool m_bFlashFlag;		// �_�Ńt���O
	bool m_bFollowFlag;		// �Ǐ]�̃t���O
};

#endif
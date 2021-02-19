#ifndef _ENEMY_CIRCLE_H_
#define _ENEMY_CIRCLE_H_
//=============================================================================
//
// �T�[�N���G�l�~�[�N���X�w�b�_�[ [enemy_circle.h]
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
class CEnemyCircle : public CEnemy
{
public:
	CEnemyCircle(TYPE Priority = TYPE_ENEMY);	// �R���X�g���N�^
	~CEnemyCircle();							// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	void MoveUpdate(void);										// �΂߈ړ��̏���
	void BulletUpdate(void);									// �e�̍X�V����

	static CEnemyCircle * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype, float fRadius, float fTheta);				// �G�l�~�[����

	void SetRotation(float fRadius, float fTheta);
private:
	D3DXVECTOR3 m_center;					// ��ʂ̒��S
	float m_fRadius;						// ���a
	float m_fAddRadius;						// ���a���Z��
	float m_fTheta;							// �p�x
	float m_fOmega;							// �p�x���Z��
	float m_fRadiusNum;						// ���a�̒l

};

#endif
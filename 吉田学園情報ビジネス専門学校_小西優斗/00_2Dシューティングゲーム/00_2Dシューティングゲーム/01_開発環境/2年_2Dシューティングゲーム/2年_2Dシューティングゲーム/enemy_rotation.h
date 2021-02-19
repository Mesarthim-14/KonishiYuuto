#ifndef _ENEMY_ROTATION_H_
#define _ENEMY_ROTATION_H_
//=============================================================================
//
// ��]�G�l�~�[�N���X�w�b�_�[ [enemy_rotation.h]
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
class CEnemyRotation : public CEnemy
{
public:
	CEnemyRotation(TYPE Priority = TYPE_ENEMY);	// �R���X�g���N�^
	~CEnemyRotation();							// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	void MoveUpdate(void);											// �΂߈ړ��̏���
	void BulletUpdate(void);										// �e�̍X�V����

	void SetRotation(float fRadius, float fTheta);					// �p�x�̐ݒ�

	static CEnemyRotation * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype,
		float fRadius, float fTheta);				// �G�l�~�[����
private:
	D3DXVECTOR3 m_BaseSize;					// ���̃T�C�Y
	float m_fRadius;						// ���a
	float m_fAddRadius;						// ���a���Z��
	float m_fTheta;							// �p�x
	float m_fOmega;							// �p�x���Z��
	float m_fRadiusNum;						// ���a�̒l
	float m_fScale;							// �k���p�ϐ�
	float m_fScaleNum;						// �k����

};

#endif
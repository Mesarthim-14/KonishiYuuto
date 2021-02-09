#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// �L�����N�^�[����  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �L�����N�^�[�̃N���X
//=============================================================================
class CCharacter : public CScene2D
{
public:
	typedef enum
	{
		// �L�����N�^�[�̏��
		STATE_NONE = 0,		// �����l
		STATE_NORMAL,		// �ʏ���
		STATE_REVIVE,		// ������
		STATE_LASER,		// ���[�U�[���ˎ�
		STATE_DAMAGE,		// �_���[�W���
		STATE_MAX
	}STATE;

	CCharacter(TYPE Priority = TYPE_PLAYER);	// �R���X�g���N�^
	virtual ~CCharacter();						// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	virtual void Uninit();												// �I������
	virtual void Update();												// �X�V����
	virtual void Draw();												// �`�揈��

	// Set�֐�
	void SetLife(int nLife);					// ���C�t�̐ݒ�
	void HitDamage(int nLife);					// �_���[�W����
	void SetState(STATE state);					// ��Ԃ̐ݒ�

	// Get�֐�
	int GetLife(void) { return m_nLife; }		// ���C�t�̏��
	STATE GetState(void) { return m_state; }	// ��Ԃ̏��

	// �������z�֐�
	virtual void Death(void) = 0;				// ���񂾂Ƃ��̏���
	virtual void UpdateState(void) = 0;			// ��Ԃ̍X�V����

private:
	STATE m_state;							// �L�����N�^�[�̏��
	int m_nLife;							// �̗�
	int m_nAttack;							// �U����
	int m_nSpeed;							// �ړ���
};
#endif
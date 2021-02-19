#ifndef _SHOCK_H_
#define _SHOCK_H_
//=============================================================================
//
// �Ռ��N���X�w�b�_�[ [shock.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene2d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_SHOCK			(256)		// �Ռ��̍ő吔
#define SHOCK_SIZE_X		(70)		// �Ռ��̉���
#define SHOCK_SIZE_Y		(70)		// �Ռ��̏c��
#define SHOCK_ANIM_SPEED	(5)			// �Ռ��̑���
#define SHOCK_ANIM_PATTERN	(8)			// �Ռ��e�N�X�`���̃p�^�[����

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// �����N���X
//=============================================================================
class CShock : public CScene2D
{
public:
	typedef enum
	{
		COLOR_TYPE_NONE = 0,
		COLOR_TYPE_WHITE,
		COLOR_TYPE_BLACK,
		COLOR_TYPE_MAX
	}COLOR_TYPE;

	CShock();			// �R���X�g���N�^
	~CShock();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);			// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��

	static CShock * Create(												// �|���S������
		D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype);

	void SetShock(COLOR_TYPE Ctype);									// �ړ��ʐݒ�
	void SizeUp(void);													// �T�C�Y�A�b�v
	void UpdateInvisible(void);											// �����ɂȂ鏈��
private:
	D3DXVECTOR3 m_Pos;			// ���W
	D3DXVECTOR3 m_move;			// �ړ�
	D3DXVECTOR3 m_size;			// �T�C�Y
	COLOR_TYPE m_Ctype;
	float m_fScaleNumber;		// �X�P�[���̊g���
	float m_fScaleNum;			// �X�P�[���̊g���
	int m_nSubAlpha;			// �����x�̌��Z�p
	int m_nSubAlphaNum;			// �����x���Z�l
};

#endif
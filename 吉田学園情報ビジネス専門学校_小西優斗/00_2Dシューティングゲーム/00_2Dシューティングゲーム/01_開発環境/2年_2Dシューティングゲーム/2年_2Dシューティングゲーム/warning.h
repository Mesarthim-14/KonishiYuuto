#ifndef _WARNING_H_
#define _WARNING_H_
//=============================================================================
//
// �x���N���X�w�b�_�[	[warning.h]
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
#define WARNING_SIZE_X			(460.0f)	// �T�C�Y
#define WARNING_SIZE_Y			(110.0f)	// �T�C�Y

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// �^�C�g��Bg�N���X
//=============================================================================
class CWarning : public CScene2D
{
public:
	CWarning();				// �R���X�g���N�^
	~CWarning();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);					// ����������
	void Uninit(void);															// �I������
	void Update(void);															// �X�V����
	void Draw(void);															// �`�揈��

	static CWarning * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// �|���S������
	void ScaleDown(void);														// �k���̏���
	void FlashPolygon(void);													// �|���S���̓_��
private:
	D3DXVECTOR3 m_Pos;												// ���W
	D3DXVECTOR3 m_move;												// �ړ���
	D3DXVECTOR3 m_size;												// �T�C�Y
	float m_fScale;													// �k���p�ϐ�
	float m_fScaleNum;												// �k����
	int m_nFlashFlame;												// �_�ł̃t���[��
	int m_nSubNumber;												// �J���[���Z
	int m_nSubNum;													// �J���[�̌��Z��
};

#endif
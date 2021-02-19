#ifndef _RESULTBG_H_
#define _RESULTBG_H_
//=============================================================================
//
// ���U���g�w�i�N���X�w�b�_�[ [resultbg.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene2d.h"

//=============================================================================
// �^�C�g��Bg�N���X
//=============================================================================
class CResultBg : public CScene2D
{
public:
	CResultBg();			// �R���X�g���N�^
	~CResultBg();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CResultBg * Create(D3DXVECTOR3 pos,					// �|���S������
		D3DXVECTOR3 size, TYPE type);

private:
	D3DXVECTOR3 m_Pos;												// ���W
	D3DXVECTOR3 m_move;												// �ړ���
};

#endif
//=============================================================================
//
// ���[�U�[�N���X [laser.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "laser.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "sound.h"
#include "scene.h"
#include "flash.h"
#include "enemy.h"
#include "explosion.h"
#include "boss.h"
#include "bullet.h"
#include "game.h"
#include "muzzle_flash.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define LASER_DAMAGE		(2)		// �_���[�W

//=============================================================================
// �C���X�^���X����
//=============================================================================
CLaser * CLaser::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
	D3DXVECTOR3 size, TYPE type, LASER_COLOR Ctype)
{
	// �C���X�^���X����
	CLaser *pLaser = new CLaser;

	if (pLaser != NULL)
	{
		// ����������
		pLaser->Init(pos, size, type);			// ���������
		pLaser->SetInfo(move, size);			// ���ݒ�
		pLaser->SetColor(Ctype);				// �F�̐ݒ�
		pLaser->InitColor();					// �F�̏�����
		pLaser->InitScroll(2, -0.03f);			// �X�N���[�����ݒ�
		pLaser->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_LASER));	// �e�N�X�`���ݒ�
	}

	return pLaser;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLaser::CLaser() : CScene2D(TYPE_LASER)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Ctype = LASER_COLOR_NONE;
	m_pVtxBuff = NULL;
	m_bUse = true;
	m_PolygonPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PolygonSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PolygonTop = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLaser::~CLaser()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLaser::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);
	m_Pos = pos;

	return S_OK;
}

//=============================================================================
// �J���[�̐ݒ�
//=============================================================================
void CLaser::InitColor(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �F�̐ݒ�
	switch (m_Ctype)
	{
		// �����Ƃ�
	case LASER_COLOR_WHITE:

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�����_�̐F	�����x255
		break;

		// �����Ƃ�
	case LASER_COLOR_BLACK:
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// �E�����_�̐F	�����x255
		break;
	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void CLaser::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLaser::Update(void)
{
	// 2D�|���S���X�V����
	CScene2D::Update();

	// ���݂̈ʒu���擾
	m_Pos = GetPos();

	// ���[�U�[�𓮂�������
	LaserUpdate();

	// �摜�̃X�N���[��
	UpdateScroll();

	// �G�Ƃ̓����蔻��
	Collision();

	// Scene2D�ɍ��W��n��
	SetPos(m_Pos);


	// ���[�U�[�̏����󂯎��
	CPlayer *pPlayer = CGame::GetPlayer();
	bool bUse = pPlayer->GetUseLaser();

	// �g���ĂȂ��Ƃ�
	if (bUse == false)
	{
		// �I������
		DisappearLaser();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLaser::Draw(void)
{
	// 2D�|���S���`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �J���[�ݒ�
//=============================================================================
void CLaser::SetColor(LASER_COLOR Ctype)
{
	m_Ctype = Ctype;
}

//=============================================
// �e�̐ݒ�
//=============================================
void CLaser::SetInfo(D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	// �ϐ��ɑ��
	m_move = move;
	m_Size = size;
}

//=============================================================================
// ���[�U�[�̍X�V
//=============================================================================
void CLaser::LaserUpdate(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �v���C���[�̏��擾
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 ShotPos = D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y - 50.0f, 0.0f);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (0.0f <= pVtx[0].pos.y)
	{
		m_Pos += m_move;
	}

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((ShotPos.x - m_Size.x / 2), m_Pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((ShotPos.x + m_Size.x / 2), m_Pos.y , 0.0f);
	pVtx[2].pos = D3DXVECTOR3((ShotPos.x - m_Size.x / 2), ShotPos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((ShotPos.x + m_Size.x / 2), ShotPos.y, 0.0f);

	// �|���S���̍��W
	m_PolygonPos = D3DXVECTOR3((pVtx[0].pos.x + pVtx[1].pos.x) / 2, (pVtx[0].pos.y + pVtx[2].pos.y) / 2, 0.0f);

	// �|���S���̃T�C�Y�ݒ�
	m_PolygonSize = D3DXVECTOR3(m_Size.x, (ShotPos.y - pVtx[0].pos.y) / 2, 0.0f);

	// ��[�̍��W
	if (pVtx[0].pos.y <= ShotPos.y)
	{
		m_PolygonTop = D3DXVECTOR3(m_PolygonPos.x, pVtx[0].pos.y + 50.0f, 0.0f);
	}
	else
	{
		m_PolygonTop = D3DXVECTOR3(ShotPos.x, ShotPos.y + 50.0f, 0.0f);
	
	}

	// ���[�U�[������
	FlashCreate(D3DXVECTOR3(ShotPos), CFlash::FLASH_TYPE_SHOT);

	// ���[�U�[������
	FlashCreate(D3DXVECTOR3(m_PolygonTop), CFlash::FLASH_TYPE_TOP);

	// // ���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}

//=============================================================================
// ���[�U�[�������鏈��
//=============================================================================
void CLaser::DisappearLaser(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		CScene *pScene = NULL;

		if (pScene == NULL)
		{
			// �V�[�����擾
			pScene = CScene::GetTop(nCount);

			while (pScene)
			{
				CScene *pSceneNext = pScene->GetNext();

				TYPE type = pScene->GetType();

				CScene2D *pScene2D = (CScene2D*)pScene;

				if (pScene2D != NULL)
				{
					// �^�[�Q�b�g�̏��m��
					CScene::TYPE type = pScene->GetType();

					if (type == TYPE_PLAYER)
					{
						D3DXVECTOR3 ShotPos = pScene2D->GetPos();

						// ���_����ݒ�
						VERTEX_2D *pVtx;

						LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

						// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
						pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

						if (0.0f <= pVtx[0].pos.y)
						{
							m_Pos += m_move;
						}

						// �T�C�Y������������
						m_Size.x -= 2.5f;

						// ���_���W�̐ݒ�
						pVtx[0].pos = D3DXVECTOR3((ShotPos.x - m_Size.x / 2), m_Pos.y, 0.0f);
						pVtx[1].pos = D3DXVECTOR3((ShotPos.x + m_Size.x / 2), m_Pos.y, 0.0f);
						pVtx[2].pos = D3DXVECTOR3((ShotPos.x - m_Size.x / 2), ShotPos.y, 0.0f);
						pVtx[3].pos = D3DXVECTOR3((ShotPos.x + m_Size.x / 2), ShotPos.y, 0.0f);

						// �|���S���̍��W
						m_PolygonPos = D3DXVECTOR3((pVtx[0].pos.x + pVtx[1].pos.x) / 2, (pVtx[0].pos.y + pVtx[2].pos.y) / 2, 0.0f);
						m_PolygonSize = D3DXVECTOR3(m_Size.x, (ShotPos.y - pVtx[0].pos.y) / 2, 0.0f);

						// ��[�̍��W
						if (pVtx[0].pos.y <= ShotPos.y)
						{
							m_PolygonTop = D3DXVECTOR3(m_PolygonPos.x, pVtx[0].pos.y + 50.0f, 0.0f);
						}
						else
						{
							m_PolygonTop = D3DXVECTOR3(ShotPos.x, ShotPos.y + 50.0f, 0.0f);

						}

						// ���[�U�[������
						FlashCreate(D3DXVECTOR3(ShotPos), CFlash::FLASH_TYPE_SHOT);

						// ���[�U�[������
						FlashCreate(D3DXVECTOR3(m_PolygonTop), CFlash::FLASH_TYPE_TOP);

						// // ���_�o�b�t�@���A�����b�N
						pVtxBuff->Unlock();

						if (m_Size.x <= 0)
						{
							m_Size.x = 0.0f;
							return;
						}
					}
				}
				pScene = pSceneNext;
			}
		}
	}
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CLaser::Collision(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		CScene *pScene = NULL;
		if (pScene == NULL)
		{
			// �V�[�����擾
			pScene = CScene::GetTop(nCount);

			while (pScene)
			{
				CScene *pSceneNext = pScene->GetNext();

				TYPE type = pScene->GetType();

				CScene2D *pScene2D = (CScene2D*)pScene;

				if (pScene2D != NULL)
				{
					// �^�[�Q�b�g�̏��m��
					CScene::TYPE type = pScene->GetType();

					// �G�l�~�[�̎�
					if (type == TYPE_ENEMY)
					{
						// �G�l�~�[�̏��擾
						CEnemy *pEnemy = (CEnemy*)pScene2D;
						D3DXVECTOR3 TargetPos = pEnemy->GetPos();
						D3DXVECTOR3 TargetSize = pEnemy->GetSize();

						// ���_����ݒ�
						VERTEX_2D *pVtx;

						LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

						// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
						pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

						if (TargetPos.x - TargetSize.x / 2 < m_PolygonPos.x + m_PolygonSize.x / 2 &&
							TargetPos.x + TargetSize.x / 2 > m_PolygonPos.x - m_PolygonSize.x / 2 &&
							TargetPos.y - TargetSize.y / 2 < (m_PolygonPos.y + m_PolygonSize.y / 2) + 50.0f &&
							TargetPos.y + TargetSize.y / 2 > (m_PolygonPos.y - m_PolygonSize.y / 2) - 50.0f)
						{
							// �v�G�l�~�[�Ƀ_���[�W��^����
							pEnemy->HitDamage(LASER_DAMAGE);
						}

						// // ���_�o�b�t�@���A�����b�N
						pVtxBuff->Unlock();

					}
					else if (type == TYPE_BOSS)
					{
						// �{�X�̏��擾
						CBoss *pBoss = (CBoss*)pScene2D;
						D3DXVECTOR3 TargetPos = pBoss->GetPos();
						D3DXVECTOR3 TargetSize = pBoss->GetSize();

						// ���_����ݒ�
						VERTEX_2D *pVtx;

						LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

						// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
						pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

						if (TargetPos.x - TargetSize.x / 2 < m_PolygonPos.x + m_PolygonSize.x / 2 &&
							TargetPos.x + TargetSize.x / 2 > m_PolygonPos.x - m_PolygonSize.x / 2 &&
							TargetPos.y + TargetSize.y / 2 > m_PolygonTop.y - 50.0f)
						{
							// ���������ꏊ�ɍ��W��߂�
							m_Pos.y = TargetPos.y + TargetSize.y / 2;
							m_Pos.y -= m_move.y;

							// �{�X�Ƀ_���[�W��^����
							pBoss->HitBossDamage(LASER_DAMAGE);

						}

						// // ���_�o�b�t�@���A�����b�N
						pVtxBuff->Unlock();

					}
					else if (type == TYPE_BULLET)
					{
						// �e�̏��擾
						CBullet *pBullet = (CBullet*)pScene2D;
						D3DXVECTOR3 TargetPos = pBullet->GetPos();
						D3DXVECTOR3 TargetSize = pBullet->GetSize();

						// ���_����ݒ�
						VERTEX_2D *pVtx;

						LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

						// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
						pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

						if (TargetPos.x - TargetSize.x / 2 < m_PolygonPos.x + m_PolygonSize.x / 2 &&
							TargetPos.x + TargetSize.x / 2 > m_PolygonPos.x - m_PolygonSize.x / 2 &&
							TargetPos.y - TargetSize.y / 2 < (m_PolygonPos.y + m_PolygonSize.y / 2) + 100.0f &&
							TargetPos.y + TargetSize.y / 2 > (m_PolygonPos.y - m_PolygonSize.y / 2) - 50.0f)
						{
							// �����蔻�菈��
							{
								// �e������
								pBullet->Uninit();

							}
						}
					}
				}
				pScene = pSceneNext;
			}
		}

	}
	return false;
}

//=============================================================================
// ���[�U�[���̐���
//=============================================================================
void CLaser::FlashCreate(D3DXVECTOR3 pos, CFlash::FLASH_TYPE Ftype)
{
	// �F�̎��
	switch (m_Ctype)
	{
		// ���̎�
	case LASER_COLOR_WHITE:

			for (int nCntFlash = 0; nCntFlash < FLASH_NUM; nCntFlash++)
			{
				// �t���b�V������
				CFlash::Create(pos, D3DXVECTOR3(FLASH_SIZE_X, FLASH_SIZE_Y, 0.0f), TYPE_EXPLOSION, CFlash::FLASH_COLOR_WHITE, Ftype, 5);
			}
		break;

		// �����Ƃ�
	case LASER_COLOR_BLACK:

			for (int nCntFlash = 0; nCntFlash < FLASH_NUM; nCntFlash++)
			{
				// �t���b�V������
				CFlash::Create(pos, D3DXVECTOR3(FLASH_SIZE_X, FLASH_SIZE_Y, 0.0f), 
					TYPE_EXPLOSION, CFlash::FLASH_COLOR_BLACK, Ftype, 5);
		}
	}
}

//=============================================================================
// �T�C�Y�̏��
//=============================================================================
D3DXVECTOR3 CLaser::GetSize(void)
{
	return m_Size;
}

//=============================================================================
// ��[�̏��
//=============================================================================
D3DXVECTOR3 CLaser::GetTop(void)
{
	return m_PolygonTop;
}
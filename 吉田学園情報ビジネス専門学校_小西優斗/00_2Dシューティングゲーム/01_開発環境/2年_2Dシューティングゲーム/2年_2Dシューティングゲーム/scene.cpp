//=============================================================================
//
// �|���S���̐ݒ� [scene.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"
#include "renderer.h"
#include "scene2d.h"

//=============================================================================
// static������
//=============================================================================
CScene *CScene::m_apScene[MAX_OBJECT] = {};
CScene *CScene::m_pTop[TYPE_MAX] = {};
CScene *CScene::m_pCur[TYPE_MAX] = {};
int CScene::m_nNumAll = 0;
int CScene::m_nNumEnemy = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(TYPE Priority)
{
	// �����o�ϐ�������
	m_nID = 0;
	m_type = Priority;
	m_bDeath = false;

	// �g�b�v�ɂȂɂ������ĂȂ�������
	if (m_pTop[Priority] == NULL)
	{
		m_pTop[Priority] = this;
	}

	if (m_pCur[Priority] == NULL)
	{
		// ���݂̂�擾
		m_pCur[Priority] = this;
	}

	m_pCur[Priority]->m_pNext = this;

	// �O�̂���
	if (m_pCur[Priority] == this)
	{
		m_pPrev = NULL;
	}
	else
	{
		m_pPrev = m_pCur[Priority];
	}

	// ���݂̂�擾
	m_pCur[Priority] = this;
	m_pNext = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_pTop[nCount] != NULL)
		{
			CScene *pScene = m_pTop[nCount];

			do
			{
				CScene *pSceneCur = pScene->m_pNext;

				// ���S�t���O���Ȃ��Ƃ�
				if (pScene->m_bDeath != true)
				{
					// �X�V����
					pScene->Update();
				}
				pScene = pSceneCur;

			} while (pScene != NULL);
		}
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_pTop[nCount] != NULL)
		{
			CScene *pScene = m_pTop[nCount];

			do
			{
				CScene *pSceneCur = pScene->m_pNext;

				if (pScene->m_bDeath == true)
				{
					// ���S�t���O�̏���
					pScene->DeathRelease();
				}

				pScene = pSceneCur;

			} while (pScene != NULL);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_pTop[nCount] != NULL)
		{
			CScene *pScene = m_pTop[nCount];
			do
			{
				CScene *pSceneCur = pScene->m_pNext;

				// ���S�t���O���Ȃ���
				if (pScene->m_bDeath != true)
				{
					pScene->Draw();
				}

				pScene = pSceneCur;

			} while (pScene != NULL);
		}
	}
}

//=============================================================================
// �S�Ẵ����[�X
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];
		while (pScene != NULL)
		{
			CScene *pCurScene = pScene->m_pNext;

			if (nCount != TYPE_FADE)
			{
				pScene->Uninit();
			}

			pScene = pCurScene;
		}
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_pTop[nCount] != NULL)
		{
			CScene *pScene = m_pTop[nCount];
			do
			{
				CScene *pSceneCur = pScene->m_pNext;

				if (pScene->m_bDeath == true)
				{
					if (nCount != TYPE_FADE)
					{
						pScene->DeathRelease();
					}
				}

				pScene = pSceneCur;

			} while (pScene != NULL);
		}
	}

	// �G�l�~�[�̑��������Z�b�g
	m_nNumEnemy = 0;
}

//=============================================================================
// �P�������[�X
//=============================================================================
void CScene::Release()
{
	// ���S�t���O
	m_bDeath = true;
}

//=============================================================================
// �^�C�v�ݒ�
//=============================================================================
void CScene::SetType(TYPE type)
{
	m_type = type;
}

//=============================================================================
// �G�l�~�[�̃J�E���g�֐�
//=============================================================================
void CScene::CountEnemy()
{
	m_nNumEnemy++;
}

//=============================================================================
// ���S�t���O����������̃����[�X
//=============================================================================
void CScene::DeathRelease(void)
{
	// �ʒu�����炷
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		// �擪��������
		if (m_pTop[nCount] == this)
		{
			// �擪�����̃I�u�W�F�N�g�ɂ���
			m_pTop[nCount] = m_pNext;
		}

		// �Ōゾ������
		if (m_pCur[nCount] == this)
		{
			// �Ō�����̑O�̃I�u�W�F�N�g�ɂ���
			m_pCur[nCount] = m_pPrev;
		}

		if (m_pPrev != NULL)
		{
			m_pPrev->m_pNext = m_pNext;
		}
		if (m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;
		}
	}

	// �G�l�~�[�������猸�Z
	if (m_type == TYPE_ENEMY)
	{
		m_nNumEnemy--;
	}

	delete this;
}

//=============================================================================
// �G�l�~�[�̐����
//=============================================================================
int CScene::GetEnemyNum(void)
{
	return m_nNumEnemy;
}

//=============================================================================
// ��ނ̏��
//=============================================================================
CScene::TYPE CScene::GetType(void)
{
	return m_type;
}

//=============================================================================
// �V�[������Ԃ�
//=============================================================================
CScene * CScene::GetTop(int nCount)
{
	return m_pTop[nCount];
}

//=============================================================================
// ���̃V�[�����
//=============================================================================
CScene * CScene::GetNext(void)
{
	return m_pNext;
}
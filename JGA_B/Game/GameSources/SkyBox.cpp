#include "stdafx.h"
#include "Project.h"
namespace basecross
{
	void SkyBox::OnCreate()
	{
		auto& app = App::GetApp();

		// �X�J�C�{�b�N�X�p�̃e�N�X�`���������Ă���t�H���_���w�肷��
		auto ptrTexturePath = app->GetDataDirWString() + L"Textures/";
		



		// ���_�J���[�͂��ׂĔ�
		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f);

		// �{�b�N�X�́u�p�v�ɂ����钸�_�̍��W�������܂Ƃ߂Ă���
		const vector<Vec3> positions{
		 { -0.5f, +0.5f, +0.5f }, // 0
		 { +0.5f, +0.5f, +0.5f }, // 1
		 { -0.5f, -0.5f, +0.5f }, // 2
		 { +0.5f, -0.5f, +0.5f }, // 3

		 { -0.5f, +0.5f, -0.5f }, // 4
		 { +0.5f, +0.5f, -0.5f }, // 5
		 { -0.5f, -0.5f, -0.5f }, // 6
		 { +0.5f, -0.5f, -0.5f }  // 7
		};
		// ���_�̍��W����ׂāu�ʁv�����
		vector<vector<Vec3>> positionsArray = {
		 { positions[0], positions[1], positions[2], positions[3] }, // ����
		 { positions[1], positions[5], positions[3], positions[7] }, // �E��
		 { positions[5], positions[4], positions[7], positions[6] }, // ��O
		 { positions[4], positions[0], positions[6], positions[2] }, // ����
		 { positions[4], positions[5], positions[0], positions[1] }, // ��
		 { positions[2], positions[3], positions[6], positions[7] }  // ��
		};
		vector<uint16_t> indices = {
		 0, 1, 2,
		 2, 1, 3
		};
		// �ʂ̐�(6��)�������[�v
		int textureIndex = 0;
		auto gm = GameManager::GetGM();
		auto sceneName = gm->GetSceneName();
		if (sceneName == L"StageSelect") {
			for (auto vPos : positionsArray) {
				// �ʂ��`�����钸�_�f�[�^���쐬
				vector<VertexPositionColorTexture> vertices = {
				 { vPos[0], white,{ 0.0f, 0.0f } },
				 { vPos[1], white,{ 1.0f, 0.0f } },
				 { vPos[2], white,{ 0.0f, 1.0f } },
				 { vPos[3], white,{ 1.0f, 1.0f } }
				};
				// �ʂ��I�u�W�F�N�g�Ƃ��Đ�������
				auto plane = ObjectFactory::Create<GameObject>(GetStage());

				// �ʂɂ̓h���[�R���|�[�l���g�����āA�|���S���ƃe�N�X�`����K�p����
				auto drawComp = plane->AddComponent<PCTStaticDraw>();
				drawComp->CreateOriginalMesh<VertexPositionColorTexture>(vertices, indices);
				drawComp->SetOriginalMeshUse(true);

					drawComp->SetTextureResource(m_textureKeys[textureIndex++]); // �t�H���_����ǂݍ��񂾃e�N�X�`�������ԂɓK�p

				// �X�J�C�{�b�N�X�͉\�Ȍ���傫������
					auto ptrTrans = plane->GetComponent<Transform>();
					const float scale = 707.0f;
					ptrTrans->SetScale(Vec3(scale));

					planes.push_back(plane);
			}
		}
		else if (sceneName == L"GameStage") {
			textureIndex = 6;
			for (auto vPos : positionsArray) {
				// �ʂ��`�����钸�_�f�[�^���쐬
				vector<VertexPositionColorTexture> vertices = {
				 { vPos[0], white,{ 0.0f, 0.0f } },
				 { vPos[1], white,{ 1.0f, 0.0f } },
				 { vPos[2], white,{ 0.0f, 1.0f } },
				 { vPos[3], white,{ 1.0f, 1.0f } }
				};
				// �ʂ��I�u�W�F�N�g�Ƃ��Đ�������
				auto plane = ObjectFactory::Create<GameObject>(GetStage());

				// �ʂɂ̓h���[�R���|�[�l���g�����āA�|���S���ƃe�N�X�`����K�p����
				auto drawComp = plane->AddComponent<PCTStaticDraw>();
				drawComp->CreateOriginalMesh<VertexPositionColorTexture>(vertices, indices);
				drawComp->SetOriginalMeshUse(true);
				drawComp->SetTextureResource(m_textureKeys[textureIndex++]); // �t�H���_����ǂݍ��񂾃e�N�X�`�������ԂɓK�p
				
				// �X�J�C�{�b�N�X�͉\�Ȍ���傫������
				auto ptrTrans = plane->GetComponent<Transform>();
				const float scale = 707.0f;
				ptrTrans->SetScale(Vec3(scale));

				planes.push_back(plane);
			}
		}
	}
	void SkyBox::OnUpdate2()
	{
		// �X�J�C�{�b�N�X�̒��S�̓J�����̍��W�Ɠ����ɂ��Ă����Ȃ��Ƙc��Ō����Ă��܂�

		// �J�����̍��W���擾����
		auto ptrCamera = GetStage()->GetView()->GetTargetCamera();
		auto ptrCameraEye = ptrCamera->GetEye();

		// �S�Ă̖ʂɃJ�����̍��W��K�p����
		for (auto plane : planes) {
			auto transComp = plane->GetComponent<Transform>();
			transComp->SetPosition(ptrCameraEye);
		}
	}

	void SkyBox::OnDraw()
	{
		// �S�Ă̖ʂ�`�悷��
		for (auto plane : planes) {
			plane->OnDraw();
		}
	}
}
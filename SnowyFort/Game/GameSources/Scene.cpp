
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	
	void Scene::OnCreate(){
		try {
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PlaySounds();
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage"); // �f�o�b�O�p�V�[���J��(ToWaitStage) ToTitleStage
		}
		catch (...) {
			throw;
		}
	}

	//BGM�Đ�
	void Scene::PlaySounds() {
		wstring strSound;
		wstring dataDir;
		App::GetApp()->GetAssetsDirectory(dataDir);

		strSound = dataDir + L"Sound\\" + L"Title_BGM.wav";
		App::GetApp()->RegisterWav(L"TITLE_BGM", strSound);
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToWaitStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			SetClearColor(Col4(0.0f, 0.0f, 0.0f, 1.0f));
			ResetActiveStage<WaitStage>();
		}
		else if (event->m_MsgStr == L"ToGameStage") {
			SetClearColor(Col4(0.6f, 0.6f, 0.7f, 1.0f));
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToTitleStage") {
			if (m_IsPlayBGM != true) {
				m_IsPlayBGM = true;
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"TITLE_BGM", XAUDIO2_LOOP_INFINITE, 1.0);
			}
			SetClearColor(Col4(0.0f, 0.0f, 0.0f, 1.0f));
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToResultStage") {
			SetClearColor(Col4(0.0f, 0.0f, 0.0f, 1.0f));
			ResetActiveStage<ResultStage>();
		}
	}

}
//end basecross

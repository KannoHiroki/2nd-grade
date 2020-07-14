
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
	void Scene::CreateResourses() {
		wstring dataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetDataDirectory(dataDir);
		//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
		//App::GetApp()->GetDataDirectory(dataDir);
		wstring strTexture = dataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = dataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = dataDir + L"Wall.png";
		App::GetApp()->RegisterTexture(L"WALL_TX", strTexture);
		strTexture = dataDir + L"grass.png";
		App::GetApp()->RegisterTexture(L"GRASS_TX", strTexture);
		strTexture = dataDir + L"Blue.png";
		App::GetApp()->RegisterTexture(L"BLUE_TX", strTexture);
		strTexture = dataDir + L"Ground.png";
		App::GetApp()->RegisterTexture(L"SOIL_TX", strTexture);
		strTexture = dataDir + L"fire.png";
		App::GetApp()->RegisterTexture(L"FIRE_TX", strTexture);
		strTexture = dataDir + L"CircleGrass.png";
		App::GetApp()->RegisterTexture(L"CIRCLEGRASS_TX", strTexture);
		strTexture = dataDir + L"Red.png";
		App::GetApp()->RegisterTexture(L"RED_TX", strTexture);
		strTexture = dataDir + L"wait.png";
		App::GetApp()->RegisterTexture(L"WAIT_TX", strTexture);
		strTexture = dataDir + L"HP.png";
		App::GetApp()->RegisterTexture(L"HP_TX", strTexture);
		strTexture = dataDir + L"HP_Frame.png";
		App::GetApp()->RegisterTexture(L"HPFRAME_TX", strTexture);
		strTexture = dataDir + L"Character_Icon.png";
		App::GetApp()->RegisterTexture(L"CHARAICON_TX", strTexture);
		//�~�j�}�b�v�i���j�̃e�N�X�`��
		strTexture = dataDir + L"MiniMap.jpg";
		App::GetApp()->RegisterTexture(L"MINIMAP_TX", strTexture);
		//�N���x����\��UI
		strTexture = dataDir + L"UI_Ryokuka3.png";
		App::GetApp()->RegisterTexture(L"EROSION_TX", strTexture);
		//������UI
		strTexture = dataDir + L"Numbers.png";
		App::GetApp()->RegisterTexture(L"NUMBERS_TX", strTexture);
		//�N���x����\��UI�́Z
		strTexture = dataDir + L"UI_Maru.png";
		App::GetApp()->RegisterTexture(L"UI_MARU_TX", strTexture);
		//�X�e�Z���̘f���̃e�N�X�`��
		strTexture = dataDir + L"Tx_Earth.png";
		App::GetApp()->RegisterTexture(L"EARTH_TX", strTexture);
		strTexture = dataDir + L"Tx_Earth2.png";
		App::GetApp()->RegisterTexture(L"EARTH2_TX", strTexture);
		strTexture = dataDir + L"Tx_Earth3.png";
		App::GetApp()->RegisterTexture(L"EARTH3_TX", strTexture);
		strTexture = dataDir + L"Tx_Earth4.png";
		App::GetApp()->RegisterTexture(L"EARTH4_TX", strTexture);
		strTexture = dataDir + L"Tx_Earth5.png";
		App::GetApp()->RegisterTexture(L"EARTH5_TX", strTexture);
		strTexture = dataDir + L"Tx_Earth6.png";
		App::GetApp()->RegisterTexture(L"EARTH6_TX", strTexture);
		//��t�̃e�N�X�`��
		strTexture = dataDir + L"Tx_Sapling.png";
		App::GetApp()->RegisterTexture(L"WAKABA_TX", strTexture);
		//�؂̃e�N�X�`��
		strTexture = dataDir + L"Tx_Wood.png";
		App::GetApp()->RegisterTexture(L"WOOD_TX", strTexture);
		strTexture = dataDir + L"Tx_Wood2.png";
		App::GetApp()->RegisterTexture(L"WOOD2_TX", strTexture);

		//�t���ς̃e�N�X�`��
		strTexture = dataDir + L"Tx_Branch.png";
		App::GetApp()->RegisterTexture(L"LEAF_TX", strTexture);
		//�����o���̃e�N�X�`��
		strTexture = dataDir + L"hukidasi.png";
		App::GetApp()->RegisterTexture(L"CALLOUT_TX", strTexture);

		//�Q�[���I�����Ɏg��UI�̃e�N�X�`��
		strTexture = dataDir + L"Retry.png";
		App::GetApp()->RegisterTexture(L"RETRY_TX", strTexture);
		strTexture = dataDir + L"StageSelect.png";
		App::GetApp()->RegisterTexture(L"STAGESELECT_TX", strTexture);
		strTexture = dataDir + L"GameOver.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);
		strTexture = dataDir + L"GameClear.png";
		App::GetApp()->RegisterTexture(L"CLEAR_TX", strTexture);

		strTexture = dataDir + L"areaA.png";
		App::GetApp()->RegisterTexture(L"AREA_A_TX", strTexture);
		strTexture = dataDir + L"areaB.png";
		App::GetApp()->RegisterTexture(L"AREA_B_TX", strTexture);

		strTexture = dataDir + L"serekuto1.png";
		App::GetApp()->RegisterTexture(L"NORMALPLANET_TX", strTexture);
		strTexture = dataDir + L"serekuto2.png";
		App::GetApp()->RegisterTexture(L"DRYPLANET_TX", strTexture);
		strTexture = dataDir + L"serekuto3.png";
		App::GetApp()->RegisterTexture(L"POLLUTIONPLANET_TX", strTexture);
		strTexture = dataDir + L"serekuto4.png";
		App::GetApp()->RegisterTexture(L"HOTPLANET_TX", strTexture);
		strTexture = dataDir + L"serekuto5.png";
		App::GetApp()->RegisterTexture(L"COLDPLANET_TX", strTexture);
		strTexture = dataDir + L"serekuto6.png";
		App::GetApp()->RegisterTexture(L"MACHINEPLANET_TX", strTexture);

		strTexture = dataDir + L"lockStar.png";
		App::GetApp()->RegisterTexture(L"LOCK_TX", strTexture);
		strTexture = dataDir + L"SE_URL.png";
		App::GetApp()->RegisterTexture(L"CREGIT_TX", strTexture);

	//--------------------------------------------------------------------------------------
	//	�V�[���J��
	//--------------------------------------------------------------------------------------
		//�X�^�[�g��ʂ̃e�N�X�`��
		strTexture = dataDir + L"titleRogo.png";
		App::GetApp()->RegisterTexture(L"STARTSCENE_TX", strTexture);
		//�u�{�^�������Ăˁv�̂���
		strTexture = dataDir + L"press_any_button.png";
		App::GetApp()->RegisterTexture(L"PRESSANYBUTTON_TX", strTexture);
		//�X�e�[�W�Z���N�g�̖��
		strTexture = dataDir + L"yazirusi.png";
		App::GetApp()->RegisterTexture(L"YAZIRUSI_TX", strTexture);
		//�^�C�g�����S
		//strTexture = dataDir + L"TitleLogo.png";
		//App::GetApp()->RegisterTexture(L"TITLELOGO_TX", strTexture);
		//�Z���N�g��ʂ̃e�N�X�`��
		strTexture = dataDir + L"select.png";
		App::GetApp()->RegisterTexture(L"SELECTSCENE_TX", strTexture);
		//�Q�[���I�[�o�[��ʂ̃e�N�X�`��
		strTexture = dataDir + L"GameOver.jpg";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);
		//�Q�[���N���A��ʂ̃e�N�X�`��
		strTexture = dataDir + L"gameclear.jpg";
		App::GetApp()->RegisterTexture(L"GAMECLEAR_TX", strTexture);
		//�t�F�[�h�p���w�i
		strTexture = dataDir + L"Fade.png";
		App::GetApp()->RegisterTexture(L"FADE_TX", strTexture);
	//--------------------------------------------------------------------------------------
	//	�X�L��
	//--------------------------------------------------------------------------------------
		//�X�L���{�^���iA�j�̃e�N�X�`��
		strTexture = dataDir + L"A_Button_UI.png";
		App::GetApp()->RegisterTexture(L"SKILL_A_TX", strTexture);
	
		//�X�L���{�^���iB�j�̃e�N�X�`��
		strTexture = dataDir + L"B_Button_UI.png";
		App::GetApp()->RegisterTexture(L"SKILL_B_TX", strTexture);
	
		//�X�L���{�^���iX�j�̃e�N�X�`��
		strTexture = dataDir + L"X_Button_UI.png";
		App::GetApp()->RegisterTexture(L"SKILL_X_TX", strTexture);
		
		//�X�L���{�^���iY�j�̃e�N�X�`��
		strTexture = dataDir + L"Y_Button_UI.png";
		App::GetApp()->RegisterTexture(L"SKILL_Y_TX", strTexture);
	
	//--------------------------------------------------------------------------------------
	//	���f��
	//--------------------------------------------------------------------------------------
		strTexture = dataDir + L"Tx_player2.png";
		App::GetApp()->RegisterTexture(L"PLAYER_TX", strTexture);
		// ���f���f�[�^�ǂݍ���
		auto ModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"PlayerUeru.bmf");
		App::GetApp()->RegisterResource(L"PLAYER_MESH", ModelMesh);
		//��t�̃��f��
		ModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"Wakaba.bmf");
		App::GetApp()->RegisterResource(L"WAKABA_MESH", ModelMesh);
		//�؂̃��f��
		ModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"Wood_LV2.bmf");
		App::GetApp()->RegisterResource(L"WOODLV2_MESH", ModelMesh);
		ModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"Wood_LV3.bmf");
		App::GetApp()->RegisterResource(L"WOODLV3_MESH", ModelMesh);
		ModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"Wood_LV4.bmf");
		App::GetApp()->RegisterResource(L"WOODLV4_MESH", ModelMesh);
		//�؂ɂ������Ă�t���ς̃��f��
		ModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"Leaf_LV2.bmf");
		App::GetApp()->RegisterResource(L"LEAFLV2_MESH", ModelMesh);
		ModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"Leaf_LV3.bmf");
		App::GetApp()->RegisterResource(L"LEAFLV3_MESH", ModelMesh);
		ModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"Leaf_LV4.bmf");
		App::GetApp()->RegisterResource(L"LEAFLV4_MESH", ModelMesh);
		//�S�������̉Ƃ̃��f��
		ModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"House_ver2.bmf");
		App::GetApp()->RegisterResource(L"HOUSE_MESH", ModelMesh);

		strTexture = dataDir + L"Tx_House3.png";
		App::GetApp()->RegisterTexture(L"HOUSE_TX", strTexture);


		ModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"Gobiln_Animetion2.bmf");
		App::GetApp()->RegisterResource(L"GOBLINLONGDIS_MESH", ModelMesh);
		ModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"GoblinSword_Animaition.bmf");
		App::GetApp()->RegisterResource(L"GOBLINSWORD_MESH", ModelMesh);
		//ModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"Aroow.bmf");
		//App::GetApp()->RegisterResource(L"ARROW_MESH", ModelMesh);
		strTexture = dataDir + L"Tx_Goblin.png";
		App::GetApp()->RegisterTexture(L"GOBLIN_TX", strTexture);
		//strTexture = dataDir + L"A.png";
		//App::GetApp()->RegisterTexture(L"GOBLIN_TX", strTexture);
		ModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"Sword_Animaition.bmf");
		App::GetApp()->RegisterResource(L"SWORD_MESH", ModelMesh);

		strTexture = dataDir + L"Tx_Sword.png";
		App::GetApp()->RegisterTexture(L"SWORD_TX", strTexture);

		ModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"Fence2.bmf");
		App::GetApp()->RegisterResource(L"FENCE_MESH", ModelMesh);

		strTexture = dataDir + L"Tx_Fence2.png";
		App::GetApp()->RegisterTexture(L"FENCE_TX", strTexture);

		//�Y
		ModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"kui.bmf");
		App::GetApp()->RegisterResource(L"HANG_MESH", ModelMesh);

		strTexture = dataDir + L"Tx_Sityu.png";
		App::GetApp()->RegisterTexture(L"HANG_TX", strTexture);
	//--------------------------------------------------------------------------------------
	//	Sound
	//--------------------------------------------------------------------------------------
		wstring strSound;
		strSound = dataDir + L"Sound\\" + L"fantasy02.wav";
		App::GetApp()->RegisterWav(L"FANTASY02_WAV", strSound);
		strSound = dataDir + L"Sound\\" + L"GameScene.wav";
		App::GetApp()->RegisterWav(L"GAMESCENE_WAV", strSound);
		strSound = dataDir + L"Sound\\" + L"nuru.wav";
		App::GetApp()->RegisterWav(L"�h��_WAV", strSound);
		strSound = dataDir + L"Sound\\" + L"binta.wav";
		App::GetApp()->RegisterWav(L"����2_WAV", strSound);
		strSound = dataDir + L"Sound\\" + L"naguru.wav";
		App::GetApp()->RegisterWav(L"����_WAV", strSound);
		strSound = dataDir + L"Sound\\" + L"plant.wav";
		App::GetApp()->RegisterWav(L"�h��2_WAV", strSound);
		strSound = dataDir + L"Sound\\" + L"bunanomorinimauyuki.wav";
		App::GetApp()->RegisterWav(L"TITLE_WAV", strSound);
		strSound = dataDir + L"Sound\\" + L"solarisnoame.wav";
		App::GetApp()->RegisterWav(L"STAGESELECT_WAV", strSound);
		strSound = dataDir + L"Sound\\" + L"ClearScene.wav";
		App::GetApp()->RegisterWav(L"CLEAR_WAV", strSound);
		strSound = dataDir + L"Sound\\" + L"GameOver.wav";
		App::GetApp()->RegisterWav(L"GAMEOVER_WAV", strSound);


	//--------------------------------------------------------------------------------------
	//	SE
	//--------------------------------------------------------------------------------------
		wstring strSE;
		strSE = dataDir + L"SE\\" + L"Attack_Sound_1.wav";
		App::GetApp()->RegisterWav(L"Attack1", strSE);
		strSE = dataDir + L"SE\\" + L"Attack_2.wav";
		App::GetApp()->RegisterWav(L"Attack2", strSE);
		strSE = dataDir + L"SE\\" + L"Walk_Sound.wav";
		App::GetApp()->RegisterWav(L"Walk", strSE);
		strSE = dataDir + L"SE\\" + L"Decision.wav";
		App::GetApp()->RegisterWav(L"Decision", strSE);
		strSE = dataDir + L"SE\\" + L"Stage_Select.wav";
		App::GetApp()->RegisterWav(L"Select", strSE);
		strSE = dataDir + L"SE\\" + L"Landing.wav";
		App::GetApp()->RegisterWav(L"Landing", strSE);
		strSE = dataDir + L"SE\\" + L"Player_Damage1.wav";
		App::GetApp()->RegisterWav(L"PlayerDamage", strSE);
		strSE = dataDir + L"SE\\" + L"Game_Clear.wav";
		App::GetApp()->RegisterWav(L"Clear", strSE);
		strSE = dataDir + L"SE\\" + L"Game_Clear.wav";
		App::GetApp()->RegisterWav(L"Clear", strSE);
		strSE = dataDir + L"SE\\" + L"Advent_Sound.wav";
		App::GetApp()->RegisterWav(L"Advent", strSE);
		strSE = dataDir + L"SE\\" + L"Level_Up_Sound.wav";
		App::GetApp()->RegisterWav(L"LavelUP", strSE);
		strSE = dataDir + L"SE\\" + L"Plant_Sound.wav";
		App::GetApp()->RegisterWav(L"Plant", strSE);
		strSE = dataDir + L"SE\\" + L"Fence.wav";
		App::GetApp()->RegisterWav(L"Sak", strSE);
		strSE = dataDir + L"SE\\" + L"NonStage.wav";
		App::GetApp()->RegisterWav(L"NONSTAGE", strSE);
	//--------------------------------------------------------------------------------------
	//	SkyBox
	//--------------------------------------------------------------------------------------

		//strTexture = dataDir + L"scaled1.bmp";
		//App::GetApp()->RegisterTexture(L"scaled1", strTexture);
		//strTexture = dataDir + L"scaled2.bmp";
		//App::GetApp()->RegisterTexture(L"scaled2", strTexture);
		//strTexture = dataDir + L"scaled3.bmp";
		//App::GetApp()->RegisterTexture(L"scaled3", strTexture);
		//strTexture = dataDir + L"scaled4.bmp";
		//App::GetApp()->RegisterTexture(L"scaled4", strTexture);
		//strTexture = dataDir + L"scaled5.bmp";
		//App::GetApp()->RegisterTexture(L"scaled5", strTexture);
		//strTexture = dataDir + L"scaled6.bmp";
		//App::GetApp()->RegisterTexture(L"scaled6", strTexture);
		//strTexture = dataDir + L"scaled7.bmp";
		//App::GetApp()->RegisterTexture(L"scaled7", strTexture);
		//strTexture = dataDir + L"scaled8.bmp";
		//App::GetApp()->RegisterTexture(L"scaled8", strTexture);
		//strTexture = dataDir + L"scaled.bmp";
		//App::GetApp()->RegisterTexture(L"scaled", strTexture);
		//strTexture = dataDir + L"scaled.bmp";
		//App::GetApp()->RegisterTexture(L"scaled", strTexture);
		//strTexture = dataDir + L"scaled.bmp";
		//App::GetApp()->RegisterTexture(L"scaled", strTexture);
		wstring dataDirr;
		App::GetApp()->GetDataDirectory(dataDirr);
		for (int i = 0; i < 12; i++) {
			strTexture = dataDirr+L"Textures\\" + L"scaled" + Util::IntToWStr(i + 1) + L".bmp";
			App::GetApp()->RegisterTexture(L"SkyBox_TX" + Util::IntToWStr(i + 1),strTexture);
		}
	}

	void Scene::OnCreate(){
		SetClearColor(Col4(130.0f / 255.0f, 140.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
		try {
			//���\�[�X�쐬
			CreateResourses();
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToCregitScene");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Stop(m_audioObject);
		if (event->m_MsgStr == L"ToGameStage") {
			auto gm = GameManager::GetGM();
			gm->SetSceneName(L"GameStage");
			gm->Reset();
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
			if (m_playBGMName != L"GAMESCENE_WAV") {
				m_playBGMName = L"GAMESCENE_WAV";
				ptrXA->Stop(m_audioObject);
				m_audioObject = ptrXA->Start(m_playBGMName, XAUDIO2_LOOP_INFINITE, 0.3);
			}
		}
		else if(event->m_MsgStr == L"ToStartStage") {
			//�X�^�[�g���
			ResetActiveStage<StartScene>();
			auto gm = GameManager::GetGM();
			gm->SetSceneName(L"TitleScene");

			if (m_playBGMName != L"TITLE_WAV") {
				m_playBGMName = L"TITLE_WAV";
				ptrXA->Stop(m_audioObject);
				m_audioObject = ptrXA->Start(m_playBGMName, XAUDIO2_LOOP_INFINITE, 0.8);
			}
		}
		else if (event->m_MsgStr == L"ToSelectStage") {
			auto gm = GameManager::GetGM();
			gm->SetSceneName(L"StageSelect");

			GameManager::GetGM()->Reset();
			//�X�e�[�W�Z���N�g��
			ResetActiveStage<StageSelect>();
			if (m_playBGMName != L"STAGESELECT_WAV") {
				m_playBGMName = L"STAGESELECT_WAV";
				ptrXA->Stop(m_audioObject);
				m_audioObject = ptrXA->Start(m_playBGMName, XAUDIO2_LOOP_INFINITE, 0.5);
			}
		}
		else if (event->m_MsgStr == L"ToGameOver"){
			GameManager::GetGM()->Reset();
			//�Q�[���I�[�o�[��
			ResetActiveStage<GameOverScene>();
			if (m_playBGMName != L"GAMEOVER_WAV") {
				m_playBGMName = L"GAMEOVER_WAV";
				ptrXA->Stop(m_audioObject);
				m_audioObject = ptrXA->Start(m_playBGMName, XAUDIO2_LOOP_INFINITE, 0.5);
			}
		}
		else if (event->m_MsgStr == L"ToGameClear") {
			GameManager::GetGM()->Reset();
			//�Q�[���N���A��
			ResetActiveStage<GameClearScene>();
			if (m_playBGMName != L"CLEAR_WAV") {
				m_playBGMName = L"CLEAR_WAV";
				ptrXA->Stop(m_audioObject);
				m_audioObject = ptrXA->Start(m_playBGMName, XAUDIO2_LOOP_INFINITE, 0.5);
			}
		}
		else if (event->m_MsgStr == L"ToCregitScene") {
			auto gm = GameManager::GetGM();
			gm->SetSceneName(L"CregitScene");
			GameManager::GetGM()->Reset();

			//�N���W�b�g�\�L
			ResetActiveStage<CregitScene>();
			ptrXA->Stop(m_audioObject);
		}
	}



}
//end basecross

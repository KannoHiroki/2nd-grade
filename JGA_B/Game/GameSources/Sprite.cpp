#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//メイン
	MainSprite::MainSprite(shared_ptr<Stage>& stage,const Vec3& position,const Vec3& scale,const Vec3& Rotation,const wstring texKey)
		:GameObject(stage),
		m_pos(position),
		m_rotation(Rotation),
		m_scale(scale),
		m_texKey(texKey)
	{

	}
	void MainSprite::OnCreate() {
		auto color = Col4(1, 1, 1, 1);
		Vec2 size;
			size.x = float(App::GetApp()->GetGameWidth());
			size.y = float(App::GetApp()->GetGameHeight());
			float halfSize = 0.5f;
		vector<VertexPositionColorTexture>vertices = {
			{VertexPositionColorTexture(Vec3(-halfSize, +halfSize, 0.0f),color,Vec2(0,0))},
			{VertexPositionColorTexture(Vec3(halfSize, halfSize, 0.0f),color,Vec2(1,0))},
			{VertexPositionColorTexture(Vec3(-halfSize, -halfSize, 0.0f),color,Vec2(0,1))},
			{VertexPositionColorTexture(Vec3(halfSize, -halfSize, 0.0f),color,Vec2(1,1))}
		};
		vector<uint16_t>indices = {
			0,1,2,
			1,3,2
		};
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(m_texKey);
		GetComponent<Transform>()->SetScale(m_scale);
		GetComponent<Transform>()->SetPosition(m_pos);
	}
	void MainSprite::OnUpdate() {
	}

	//スタート画面

	StartSprite::StartSprite(shared_ptr<Stage>& stage,const Vec3& position,const Vec3& scale,const Vec3& Rotation,const wstring texKey)
		: MainSprite(stage, position, scale, Rotation, texKey)
	{
	}
	void StartSprite::OnCreate() {
		MainSprite::OnCreate();
	}
	void StartSprite::OnUpdate() {
	}


	PressAnyButtonSprite::PressAnyButtonSprite(shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale, const Vec3& Rotation, const wstring texKey)
		: MainSprite(stage, position, scale, Rotation, texKey)
	{
		m_blink = { 1.0f,8 };
		m_blinkTime = 0.7f;
		m_isPushButton = false;
		m_frameCount = 0.0f;
		m_tmpDrawActive = true;
	}
	void PressAnyButtonSprite::OnCreate() {
		MainSprite::OnCreate();
		//うごくちゃん
		auto ptrAct = AddComponent<Action>();
		ptrAct->AddMoveTo(0.5f, Vec3(0.0f, -230.0f, 0.0f));
		ptrAct->AddMoveTo(0.5f, Vec3(0.0f, -235.0f, 0.0f));
		ptrAct->SetLooped(true);
		ptrAct->Run();
		SetDrawActive(true);
	}
	void PressAnyButtonSprite::OnUpdate() {
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//ゲームステージへ
			//Aボタン
			if (CntlVec[0].wPressedButtons && m_isPushButton == false) {
				m_isPushButton = true;
				GetComponent<Action>()->Stop();
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"Decision", 0, 0.7f);
			}
		}
		Blink();
	}
	void PressAnyButtonSprite::Blink() {
		if (m_isPushButton == true) {
			if (m_blink.BlinkNum != 0) {
				if (m_blink.OneBlinkTime > 0.0f) {
					auto drawActive = GetDrawActive();
					if (m_tmpDrawActive == drawActive) {
						SetDrawActive(!drawActive);
					}
					m_blink.OneBlinkTime -= App::GetApp()->GetElapsedTime();
				}
				else {
					m_blink.Reset();
					m_tmpDrawActive = GetDrawActive();
					m_blink.BlinkNum--;
				}
			}
			else {
				dynamic_pointer_cast<StartScene>(GetStage())->SceneChange();
				return;
			}
		}
	}
	//タイトルロゴ

	TitleSprite::TitleSprite(shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale, const Vec3& Rotation, const wstring texKey)
		: MainSprite(stage, position, scale, Rotation, texKey)
	{
	}
	void TitleSprite::OnCreate() {
		MainSprite::OnCreate();
	}
	void TitleSprite::OnUpdate() {
	}

	//ステージセレクト画面

	SelectSprite::SelectSprite(shared_ptr<Stage>& stage,const Vec3& position,const Vec3& scale,const Vec3& Rotation,const wstring texKey)
		: MainSprite(stage, position, scale, Rotation, texKey)
	{
	}
	void SelectSprite::OnCreate() {
		MainSprite::OnCreate();
	}
	void SelectSprite::OnUpdate() {
	}

	//ゲームオーバー画面

	GameOverSprite::GameOverSprite(shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale, const Vec3& Rotation, const wstring texKey)
		: MainSprite(stage, position, scale, Rotation, texKey)
	{
	}
	void GameOverSprite::OnCreate() {
		MainSprite::OnCreate();
	}
	void GameOverSprite::OnUpdate() {
	}

	//ゲームクリア画面

	GameClearSprite::GameClearSprite(shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale, const Vec3& Rotation, const wstring texKey)
		: MainSprite(stage, position, scale, Rotation, texKey)
	{
	}
	void GameClearSprite::OnCreate() {
		MainSprite::OnCreate();
	}
	void GameClearSprite::OnUpdate() {
	}

	//クレジット画面
	CregitSprite::CregitSprite(shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale, const Vec3& Rotation, const wstring texKey)
		: MainSprite(stage, position, scale, Rotation, texKey)
	{
	}
	void CregitSprite::OnCreate() {
		MainSprite::OnCreate();
	}
	void CregitSprite::OnUpdate() {
		//auto ptrDraw = GetComponent<PCTSpriteDraw>();
		//auto diff = ptrDraw->GetDiffuse();
		//ptrDraw->SetDiffuse(Col4(diff.x, diff.y, diff.z, diff.w + App::GetApp()->GetElapsedTime()));
		//if (diff.w > 1.0f) {
		//	GameManager::GetGM()->SetFadeFlg(true);
		//}

		dynamic_pointer_cast<CregitScene>(GetStage())->SceneChange();
	}


}
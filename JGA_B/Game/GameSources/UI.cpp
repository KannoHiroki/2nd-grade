/*!
@file UI.cpp
@brief UI
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	通常のスプライト
	//--------------------------------------------------------------------------------------
	MultiSprite::MultiSprite(const shared_ptr<Stage>& StagePtr, bool Trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey) :
		GameObject(StagePtr),
		m_trace(Trace),
		m_startScale(StartScale),
		m_startPos(StartPos),
		m_textureKey(TextureKey)
	{}
	MultiSprite::~MultiSprite(){}

	void MultiSprite::OnCreate() {
		float halfSize = 0.5f;
		//頂点配列
		m_backupVertices = {
			{ VertexPositionTexture(Vec3(-halfSize, halfSize, 0), Vec2(0.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(halfSize, halfSize, 0), Vec2(1.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(-halfSize, -halfSize, 0), Vec2(0.0f, 1.0f)) },
			{ VertexPositionTexture(Vec3(halfSize, -halfSize, 0), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0,1,2,1,3,2 };
		SetAlphaActive(m_trace);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_startPos.x, m_startPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_backupVertices, indices);
		ptrDraw->SetTextureResource(m_textureKey);
	}

	//--------------------------------------------------------------------------------------
	///	マルチスクエア
	//--------------------------------------------------------------------------------------
	MultiSquare::MultiSquare(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Quat& Qt,
		const Vec3& Position,
		const wstring& TextureKey
	):
		GameObject(StagePtr),
		m_scale(Scale),
		m_qt(Qt),
		m_position(Position),
		m_textureKey(TextureKey)
	{}
	MultiSquare::~MultiSquare(){}

	void MultiSquare::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_scale);
		ptrTransform->SetQuaternion(m_qt);
		ptrTransform->SetPosition(m_position);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		ptrColl->SetAfterCollision(AfterCollision::None);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		ptrDraw->SetTextureResource(m_textureKey);
		SetAlphaActive(true);
	}

	MiniMap::MiniMap(const shared_ptr<Stage>& StagePtr, bool Trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey)
		:MultiSprite(StagePtr,Trace,StartScale,StartPos,TextureKey)
	{}
	MiniMap::~MiniMap() {}
	void MiniMap::OnCreate() {
		MultiSprite::OnCreate();
	}
	void MiniMap::OnUpdate() {
	}

	SkillA::SkillA(const shared_ptr<Stage>& StagePtr, bool Trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey)
		:MultiSprite(StagePtr, Trace, StartScale, StartPos, TextureKey)
	{}
	SkillA::~SkillA() {}
	void SkillA::OnCreate() {
		MultiSprite::OnCreate();
	}
	void SkillA::OnUpdate() {
	}

	SkillB::SkillB(const shared_ptr<Stage>& StagePtr, bool Trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey)
		:MultiSprite(StagePtr, Trace, StartScale, StartPos, TextureKey)
	{}
	SkillB::~SkillB() {}
	void SkillB::OnCreate() {
		MultiSprite::OnCreate();
	}
	void SkillB::OnUpdate() {
	}

	SkillX::SkillX(const shared_ptr<Stage>& StagePtr, bool Trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey)
		:MultiSprite(StagePtr, Trace, StartScale, StartPos, TextureKey)
	{}
	SkillX::~SkillX() {}
	void SkillX::OnCreate() {
		MultiSprite::OnCreate();
	}
	void SkillX::OnUpdate() {
	}

	SkillY::SkillY(const shared_ptr<Stage>& StagePtr, bool Trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey)
		:MultiSprite(StagePtr, Trace, StartScale, StartPos, TextureKey)
	{}
	SkillY::~SkillY() {}
	void SkillY::OnCreate() {
		MultiSprite::OnCreate();
	}
	void SkillY::OnUpdate() {
	}

	//--------------------------------------------------------------------------------------
	///	左右移動するスプライト
	//--------------------------------------------------------------------------------------
	LRMoveSprite::LRMoveSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace, const Vec2& StartScale, const Vec2& StartPos, const Vec3& Rotaion, bool IsRight) :
		GameObject(StagePtr),
		m_textureKey(TextureKey),
		m_trace(Trace),
		m_startScale(StartScale),
		m_startPos(StartPos),
		m_rotation(Rotaion),
		m_isRight(IsRight)
	{
		m_speed = 1.0f;
	}

	void LRMoveSprite::OnCreate() {
		float helfSize = 1.0f;
		//頂点配列(1個表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTrans->SetRotation(m_rotation);
		ptrTrans->SetPosition(m_startPos.x, m_startPos.y, 0);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey);
		this->AddComponent<Action>();
		LRProcess();
		SetDrawLayer(3);
	}

	void LRMoveSprite::OnUpdate() {
	}

	void LRMoveSprite::LRProcess() {

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_startPos);
		ptrTrans->SetScale(m_startScale.x, m_startScale.y, 1.0f);

		auto ptrAction = GetComponent<Action>();

		if (m_isRight == true) {
			ptrAction->AllActionClear();
			ptrAction->AddMoveTo(0.5f, Vec3(m_startPos.x, 0.0f, 0.0f), Lerp::Linear);
			ptrAction->AddMoveTo(0.5f, Vec3(m_startPos.x - 50.0f, 0.0f, 0.0f), Lerp::Linear);
			ptrAction->SetLooped(true);
			ptrAction->Run();
		}
		else {
			ptrAction->AllActionClear();
			ptrAction->AddMoveTo(0.5f, Vec3(m_startPos.x, 0.0f, 0.0f), Lerp::Linear);
			ptrAction->AddMoveTo(0.5f, Vec3(m_startPos.x + 50.0f, 0.0f, 0.0f), Lerp::Linear);
			ptrAction->SetLooped(true);
			ptrAction->Run();
		}
	}
	//--------------------------------------------------------------------------------------
	///	フェード
	//--------------------------------------------------------------------------------------

	//フェードイン

	FadeInSprite::FadeInSprite(const shared_ptr<Stage>& StagePtr,bool Trance,const Vec2& StageScale,const Vec3& StartPos,wstring TextureKey)
		:MultiSprite(StagePtr,Trance,StageScale,StartPos,TextureKey)
	{}
	FadeInSprite::~FadeInSprite() {}
	void FadeInSprite::OnCreate() {
		MultiSprite::OnCreate();
	}
	void FadeInSprite::OnUpdate() {
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		auto diff = ptrDraw->GetDiffuse();
		ptrDraw->SetDiffuse(Col4(diff.x, diff.y, diff.z, diff.w - App::GetApp()->GetElapsedTime()/5));
	}

	//フェードアウト

	FadeOutSprite::FadeOutSprite(const shared_ptr<Stage>& StagePtr, bool Trance, const Vec2& StageScale, const Vec3& StartPos, wstring TextureKey)
		:MultiSprite(StagePtr, Trance, StageScale, StartPos, TextureKey)
	{}
	FadeOutSprite::~FadeOutSprite() {}
	/*bool fldFade() {
		GameManager::GetGM()->
	}*/
	void FadeOutSprite::OnCreate() {
		MultiSprite::OnCreate();
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.0f));

	}
	void FadeOutSprite::OnUpdate() {
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		auto diff = ptrDraw->GetDiffuse();
		ptrDraw->SetDiffuse(Col4(diff.x, diff.y, diff.z, diff.w + App::GetApp()->GetElapsedTime()));
		if (diff.w > 1.0f) {
			GameManager::GetGM()->SetFadeFlg(true);
		}
	}


	//--------------------------------------------------------------------------------------
	/// フェードイン・アウトをするスプライト
	//--------------------------------------------------------------------------------------

	FadeInAndOutSprite::FadeInAndOutSprite(const shared_ptr<Stage>& StagePtr, const Vec2& StageScale, const Vec3& StartPos, wstring TextureKey, float FadeInTime, float DrawTime, float FadeOutTime)
		:MultiSprite(StagePtr, true, StageScale, StartPos, TextureKey)
	{
		m_inOut.InTime = FadeInTime;
		m_inOut.DrawTime = DrawTime;
		m_inOut.OutTime = FadeOutTime;

		m_isInEnd = false;
		m_isDrawEnd = false;
		m_isOutEnd = false;
	}

	void FadeInAndOutSprite::OnCreate() {
		MultiSprite::OnCreate();
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.0f));
	}

	void FadeInAndOutSprite::OnUpdate() {
		FadeIn();
		SpriteDraw();
		FadeOut();
		if (m_isDrawEnd == true && m_isInEnd == true && m_isOutEnd == true) {
			GetStage()->RemoveGameObject<FadeInAndOutSprite>(GetThis<FadeInAndOutSprite>());
		}
	}

	void FadeInAndOutSprite::FadeIn() {
		if (m_isInEnd == false) {
			auto alpha = m_inOut.GetInAlpha();
			auto ptrDraw = GetComponent<PTSpriteDraw>();
			auto Diff = ptrDraw->GetDiffuse();
			Diff.w += alpha;
			ptrDraw->SetDiffuse(Diff);
			if (Diff.w >= 1.0f) {
				m_isInEnd = true;
			}
		}
	}
	void FadeInAndOutSprite::SpriteDraw() {
		if (m_isDrawEnd == false && m_isInEnd == true) {
			if (m_inOut.frameCount < m_inOut.DrawTime) {
				m_inOut.frameCount += App::GetApp()->GetElapsedTime();
			}
			else {
				m_isDrawEnd = true;
			}
		}
	}

	void FadeInAndOutSprite::FadeOut() {
		if (m_isOutEnd == false && m_isDrawEnd == true && m_isInEnd == true) {
			auto alpha = m_inOut.GetOutAlpha();
			auto ptrDraw = GetComponent<PTSpriteDraw>();
			auto Diff = ptrDraw->GetDiffuse();
			Diff.w -= alpha;
			ptrDraw->SetDiffuse(Diff);
			if (Diff.w <= 0.0f) {
				m_isOutEnd = true;
			}
		}
	}
	//--------------------------------------------------------------------------------------
	///	数字のスプライト
	//--------------------------------------------------------------------------------------
	ScoreSprite::ScoreSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_NumberOfDigits(NumberOfDigits),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_Score(0.0f)
	{}

	void ScoreSprite::OnCreate() {
		float xPiecesize = 1.0f / (float)m_NumberOfDigits;
		float helfSize = 0.5f;

		//インデックス配列
		vector<uint16_t> indices;
		for (UINT i = 0; i < m_NumberOfDigits; i++) {
			float vertex0 = -helfSize + xPiecesize * (float)i;
			float vertex1 = vertex0 + xPiecesize;
			//0
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex0, helfSize, 0), Vec2(0.0f, 0.0f))
			);
			//1
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex1, helfSize, 0), Vec2(0.1f, 0.0f))
			);
			//2
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex0, -helfSize, 0), Vec2(0.0f, 1.0f))
			);
			//3
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex1, -helfSize, 0), Vec2(0.1f, 1.0f))
			);
			indices.push_back(i * 4 + 0);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 3);
			indices.push_back(i * 4 + 2);
		}

		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);
		GetStage()->SetSharedGameObject(L"ScoreSprite", GetThis<ScoreSprite>());
	}

	void ScoreSprite::OnUpdate() {
		vector<VertexPositionTexture> newVertices;
		UINT num;
		int verNum = 0;
		for (UINT i = m_NumberOfDigits; i > 0; i--) {
			UINT base = (UINT)pow(10, i);
			num = ((UINT)m_Score) % base;
			num = num / (base / 10);
			Vec2 uv0 = m_BackupVertices[verNum].textureCoordinate;
			uv0.x = (float)num / 10.0f;
			auto v = VertexPositionTexture(
				m_BackupVertices[verNum].position,
				uv0
			);
			newVertices.push_back(v);

			Vec2 uv1 = m_BackupVertices[verNum + 1].textureCoordinate;
			uv1.x = uv0.x + 0.1f;
			v = VertexPositionTexture(
				m_BackupVertices[verNum + 1].position,
				uv1
			);
			newVertices.push_back(v);

			Vec2 uv2 = m_BackupVertices[verNum + 2].textureCoordinate;
			uv2.x = uv0.x;

			v = VertexPositionTexture(
				m_BackupVertices[verNum + 2].position,
				uv2
			);
			newVertices.push_back(v);

			Vec2 uv3 = m_BackupVertices[verNum + 3].textureCoordinate;
			uv3.x = uv0.x + 0.1f;

			v = VertexPositionTexture(
				m_BackupVertices[verNum + 3].position,
				uv3
			);
			newVertices.push_back(v);

			verNum += 4;
		}
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);
		ErosionScore();

	}

	//緑化の%表記
	void ScoreSprite::ErosionScore() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		shared_ptr<Plant> ptrPlant;
		if (ptrPlayer->GetNowEreaName() == L"NONE") {
			ptrPlant = GetStage()->GetSharedGameObject<Plant>(L"A");
		}
		else {
			ptrPlant = GetStage()->GetSharedGameObject<Plant>(ptrPlayer->GetNowEreaName());
		}
		if (ptrPlant) {
			float eScore = ptrPlant->GetMaxScale().length() / 100.0f;
			auto ptrCircle = ptrPlant->GetMyGreenCircle().lock();
			if (ptrCircle) {
				auto nowScaleLen = ptrCircle->GetComponent<Transform>()->GetScale().length();
				m_percent = nowScaleLen / eScore;
				if (m_percent > 100.0f) {
					m_percent = 100.0f;
				}
				m_Score = m_percent;
			}
		}
	}


	//--------------------------------------------------------------------------------------
	///	拡大縮小するスプライト
	//--------------------------------------------------------------------------------------
	ScaleMoveSprite::ScaleMoveSprite(const shared_ptr<Stage>& StagePtr, bool Trace, const Vec2& StartScale, const Vec2& StartPos, const wstring& TextureKey) :
		GameObject(StagePtr),
		m_trace(Trace),
		m_startScale(StartScale),
		m_startPos(StartPos),
		m_textureKey(TextureKey)
	{
		m_speed = 1.0f;
		m_maxScale = Vec3(118.0f, 118.0f, 1.0f);
		m_onePer = m_maxScale / 100;
		auto scoreSprite = GetStage()->GetSharedGameObject<ScoreSprite>(L"Number");
		m_tmpPer = scoreSprite->GetPercent();
	}

	void ScaleMoveSprite::OnCreate() {
		float helfSize = 1.0f;
		//頂点配列(1個表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_startPos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey);
		this->AddComponent<Action>();
	}

	void ScaleMoveSprite::OnUpdate() {
		ScaleMoveProcess();
	}

	void ScaleMoveSprite::ScaleMoveProcess() {
		auto scoreSprite = GetStage()->GetSharedGameObject<ScoreSprite>(L"Number");
		if (m_tmpPer != scoreSprite->GetPercent()) {
			m_tmpPer = scoreSprite->GetPercent();
			auto percent = scoreSprite->GetPercent();
			auto ptrAction = GetComponent<Action>();
			auto scale = m_onePer * percent;
			ptrAction->AllActionClear();
			ptrAction->AddScaleTo(0.5f, Vec3(scale), Lerp::Linear);
			ptrAction->SetLooped(false);
			ptrAction->Run();
		}
	}
	//--------------------------------------------------------------------------------------
	/// クリア時、ゲームオーバー時に使うリトライのスプライト
	//--------------------------------------------------------------------------------------
	RetrySprite::RetrySprite(shared_ptr<Stage> &stage,bool trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey, wstring UseName)
		:MultiSprite(stage,trace,StartScale,StartPos,TextureKey),
		m_useName(UseName),
		m_scale(StartScale),
		m_pos(StartPos)
	{
		m_frameCount = 0.0f;
	}

	void RetrySprite::OnCreate() {
		MultiSprite::OnCreate();
		auto ptrAct = AddComponent<Action>();
		ptrAct->AddScaleTo(0.5f,Vec3(m_scale.x + 200.0f, m_scale.y + 200.0f,1.0f));
		ptrAct->AddScaleTo(0.5f,Vec3(m_scale.x,m_scale.y,1.0f));
		ptrAct->SetLooped(true);
		SetDrawLayer(200);
	}

	void RetrySprite::OnUpdate() {
		Select();
	}

	void RetrySprite::Select() {
		auto gm = GameManager::GetGM();
		auto ptrAct = GetComponent<Action>();
		auto ptrTrans = GetComponent<Transform>();
		auto ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (m_useName == L"Retry" || m_useName == L"NextStage") {
			if (gm->GetMenuSelect() == 1) {
				m_frameCount += App::GetApp()->GetElapsedTime();
				if (ptrAct->GetArrived() == false) {
					ptrAct->Run();
				}
				if (ctrlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					if (m_useName == L"Retry") {
						auto PtrScene = App::GetApp()->GetScene<Scene>();
						PostEvent(0.0f, GetStage(), PtrScene, L"ToGameStage");
					}
					else if (m_useName == L"NextStage") {
						auto PtrScene = App::GetApp()->GetScene<Scene>();
						PostEvent(0.0f, GetStage(), PtrScene, L"ToGameStage");
					}
				}
				if (ctrlVec[0].fThumbLX > 0.3f || ctrlVec[0].fThumbLX < -0.3f) {
					if (m_frameCount > 0.6f) {
						gm->SetMenuSelect(2);
						ptrAct->Stop();
						ptrTrans->SetScale(m_scale.x, m_scale.y, 1.0f);
						m_frameCount = 0.0f;
					}
				}
			}
		}
		else if (m_useName == L"StageSelect") {
			if (gm->GetMenuSelect() == 2) {
				m_frameCount += App::GetApp()->GetElapsedTime();
				if (ptrAct->GetArrived() == false) {
					ptrAct->Run();
				}
				if (ctrlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					auto PtrScene = App::GetApp()->GetScene<Scene>();
					PostEvent(0.0f, GetStage(), PtrScene, L"ToSelectStage");
				}
				if (ctrlVec[0].fThumbLX > 0.3f || ctrlVec[0].fThumbLX < -0.3f) {
					if (m_frameCount > 0.6f) {
						gm->SetMenuSelect(1);
						ptrAct->Stop();
						ptrTrans->SetScale(m_scale.x, m_scale.y, 1.0f);
						m_frameCount = 0.0f;
					}
				}
			}
		}
	}
	//--------------------------------------------------------------------------------------
/// クリア時、ゲームオーバー時に使うリトライのスプライト
//--------------------------------------------------------------------------------------
	ClearSprite::ClearSprite(shared_ptr<Stage> &stage, bool trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey, wstring UseName)
		:MultiSprite(stage, trace, StartScale, StartPos, TextureKey),
		m_useName(UseName)
	{

	}

	void ClearSprite::OnCreate() {
		MultiSprite::OnCreate();
		SetDrawLayer(200);
	}

	void ClearSprite::OnUpdate() {

	}
	//--------------------------------------------------------------------------------------
	/// クリア時、ゲームオーバー時に使うリトライのスプライト
	//--------------------------------------------------------------------------------------
	BlackSprite::BlackSprite(shared_ptr<Stage> &stage, bool trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey, wstring UseName)
		:MultiSprite(stage, trace, StartScale, StartPos, TextureKey),
		m_useName(UseName)
	{

	}

	void BlackSprite::OnCreate() {
		MultiSprite::OnCreate();
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.8f));
		SetDrawLayer(199);
	}

	void BlackSprite::OnUpdate() {

	}

}
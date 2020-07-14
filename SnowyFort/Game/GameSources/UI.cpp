/*!
@file UI.cpp
@brief UIなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	タイトルスプライト
	//--------------------------------------------------------------------------------------
	TitleSprite::TitleSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos)
	{}

	TitleSprite::~TitleSprite() {}
	void TitleSprite::OnCreate() {
		float HelfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
	}

	//--------------------------------------------------------------------------------------
	///	アニメスプライト(点滅)
	//--------------------------------------------------------------------------------------
	AnimeSprite::AnimeSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0.0f)
	{}

	AnimeSprite::~AnimeSprite() {}

	void AnimeSprite::OnCreate() {
		float HelfSize = 0.5f;
		//頂点配列
		vector<VertexPositionColorTexture> vertex = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertex, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
	}

	void AnimeSprite::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime * 5.0f;
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		auto PtrDraw = GetComponent<PCTSpriteDraw>();
		Col4 col(1.0, 1.0, 1.0, 1.0);
		col.w = sin(m_TotalTime) * 0.5f + 0.5f;
		PtrDraw->SetDiffuse(col);
	}

	//--------------------------------------------------------------------------------------
	///	数字スプライト
	//--------------------------------------------------------------------------------------
	NumSprite::NumSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
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

	NumSprite::NumSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos,
		const float& Score
	) :
		GameObject(StagePtr),
		m_NumberOfDigits(NumberOfDigits),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_Score(Score)
	{}

	void NumSprite::OnCreate() {
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
		GetStage()->SetSharedGameObject(L"NumSprite", GetThis<NumSprite>());
	}

	void NumSprite::OnUpdate() {
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
	}

	//--------------------------------------------------------------------------------------
	///	数字スプライト
	//--------------------------------------------------------------------------------------	
	MyNumSprite::MyNumSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_NumberOfDigits(NumberOfDigits),
		m_NumberOfDigitsBuff(m_NumberOfDigits),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_Score(0.0f)
	{}

	MyNumSprite::MyNumSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos,
		const float& Score) :
		GameObject(StagePtr),
		m_NumberOfDigits(NumberOfDigits),
		m_NumberOfDigitsBuff(m_NumberOfDigits),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_Score(Score)
	{}

	vector<uint16_t> MyNumSprite::UpdateDigits() {
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
		return indices;
	}

	void MyNumSprite::OnCreate() {

		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		m_ptSpriteDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, UpdateDigits());
		m_ptSpriteDraw->SetTextureResource(m_TextureKey);
		GetStage()->SetSharedGameObject(L"MyNumSprite", GetThis<MyNumSprite>());
	}

	void MyNumSprite::OnUpdate() {

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
		if (m_NumberOfDigitsBuff < m_NumberOfDigits) {
			m_ptSpriteDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, UpdateDigits());
			m_NumberOfDigitsBuff = m_NumberOfDigits;
		}


		m_ptSpriteDraw->SetBlendState(BlendState::Opaque);
		m_ptSpriteDraw->SetDepthStencilState(DepthStencilState::None);
		m_ptSpriteDraw->SetRasterizerState(RasterizerState::CullBack);
		m_ptSpriteDraw->SetSamplerState(SamplerState::LinearClamp);
		m_ptSpriteDraw->CreateMesh(newVertices, UpdateDigits());
	}

	//--------------------------------------------------------------------------------------
	///	連続して動くスプライト
	//--------------------------------------------------------------------------------------
	MoveSprite::MoveSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_Flg(true)
	{}

	void MoveSprite::OnCreate() {
		float HelfSize = 0.5f;
		//頂点配列
		vector<VertexPositionColorTexture> vertex = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertex, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_TextureKey);
	}

	void MoveSprite::OnUpdate() {
		auto pos = GetComponent<Transform>()->GetPosition();
		if (pos.y <= 0.0f && m_Flg) {
			GetStage()->AddGameObject<MoveSprite>(L"SNOW_TX", true, Vec2(1280.0f, 800.0f), Vec2(0.0f, 800.0f));
			m_Flg = false;
		}

		pos += Vec3(0.0f, -0.4f, 0.0f);
		GetComponent<Transform>()->SetPosition(pos);
	}
}
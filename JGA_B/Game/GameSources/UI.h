/*!
@file UI.h
@brief UI関連
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	通常スプライト
	//--------------------------------------------------------------------------------------
	class MultiSprite : public GameObject {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;

		//バックアップ頂点データ
		vector<VertexPositionTexture> m_backupVertices;

	public:
		MultiSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey);
		virtual ~MultiSprite();
		virtual void OnCreate() override;
		virtual void OnUpdate() override {}
		void ChangeTexture(wstring Name) {
			GetComponent<PTSpriteDraw>()->SetTextureResource(Name);
		}

	};

	//--------------------------------------------------------------------------------------
	///	マルチスクエア
	//--------------------------------------------------------------------------------------
	class MultiSquare : public GameObject {
		Vec3 m_scale;
		Quat m_qt;
		Vec3 m_position;
		wstring m_textureKey;

	public:
		MultiSquare(const shared_ptr<Stage>& StagePtr, const Vec3& Scale,
			const Quat& Qt, const Vec3& Position, const wstring& TextureKey);
		virtual ~MultiSquare();
		virtual void OnCreate() override;
	};

	class MiniMap :public MultiSprite {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
	public:
		MiniMap(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey);
		void SetPostion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
		virtual ~MiniMap();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
	class SkillA :public MultiSprite {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
	public:
		SkillA(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey);
		void SetPostion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
		virtual ~SkillA();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
	class SkillB :public MultiSprite {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
	public:
		SkillB(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey);
		void SetPostion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
		virtual ~SkillB();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
	class SkillX :public MultiSprite {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
	public:
		SkillX(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey);
		void SetPostion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
		virtual ~SkillX();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
	class SkillY :public MultiSprite {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
	public:
		SkillY(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey);
		void SetPostion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
		virtual ~SkillY();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	///	左右移動するスプライト
	//--------------------------------------------------------------------------------------
	class LRMoveSprite : public GameObject {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		Vec3 m_rotation;
		wstring m_textureKey;
		float m_speed;
		bool m_isRight;
	public:
		// 構築と破棄
		LRMoveSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos, const Vec3& Rotation, bool IsRight);
		virtual ~LRMoveSprite() {}

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;

		void LRProcess();

	};
	//--------------------------------------------------------------------------------------
	///	フェード
	//--------------------------------------------------------------------------------------

	//フェードイン
	class FadeInSprite :public MultiSprite {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
	public:
		FadeInSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey);
		void SetPostion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
		virtual ~FadeInSprite();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//フェードアウト
	class FadeOutSprite : public MultiSprite {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
	public:
		FadeOutSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey);
		void SetPostion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
		virtual~FadeOutSprite();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
	 

	struct FadeInOut
	{
		float InTime;
		float DrawTime;
		float OutTime;
		float frameCount = 0.0f;

		void FrameCountReset() {
			frameCount = 0.0f;
		}
		float GetInAlpha() {
			float alpha = (1.0f / InTime) / 60.0f;
			return alpha;
		}
		float GetOutAlpha() {
			float alpha = (1.0f / InTime) / 60.0f;
			return alpha;
		}
	};

	class FadeInAndOutSprite : public MultiSprite {
		Vec3 m_pos;
		Vec3 m_scale;
		wstring m_textureKey;
		bool m_isInEnd;
		bool m_isDrawEnd;
		bool m_isOutEnd;
		FadeInOut m_inOut;
		 
	public:
		// スケール, ポジション, フェードインの時間, 描画しておく時間 ,フェードアウトの時間
		FadeInAndOutSprite(const shared_ptr<Stage>& StagePtr,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey, float InTime, float DrawTime, float OutTime);
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void FadeIn();
		void SpriteDraw();
		void FadeOut();
	};
	//--------------------------------------------------------------------------------------
	///	数字のスプライト
	//--------------------------------------------------------------------------------------
	class ScoreSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Score;
		float m_percent;
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	NumberOfDigits	桁数
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		ScoreSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ScoreSprite() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief スコアのセット
		@param[in]	f	値
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetScore(float f) {
			m_Score = f;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

		//緑化された%表記の関数
		void ErosionScore();

		float GetPercent() {
			return m_percent;
		}
	};

	//--------------------------------------------------------------------------------------
	///	拡大縮小するスプライト
	//--------------------------------------------------------------------------------------
	class ScaleMoveSprite : public GameObject {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
		float m_speed;
		Vec3 m_maxScale;
		Vec3 m_onePer;
		float m_tmpPer;
	public:
		// 構築と破棄
		ScaleMoveSprite(const shared_ptr<Stage>& StagePtr,bool Trace,
			const Vec2& StartScale, const Vec2& StartPos, const wstring& TextureKey);
		virtual ~ScaleMoveSprite() {}

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;

		void ScaleMoveProcess();

	};
	//--------------------------------------------------------------------------------------
	/// クリア時、ゲームオーバー時に使うリトライのスプライト
	//--------------------------------------------------------------------------------------
	class RetrySprite : public MultiSprite {
		Vec3 m_pos;
		Vec2 m_scale;
		wstring m_useName;
		float m_frameCount;
	public:
		RetrySprite(shared_ptr<Stage> &stage, bool trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey,wstring UseName);
		virtual ~RetrySprite(){}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void Select();
	};
	//--------------------------------------------------------------------------------------
	/// クリア時、ゲームオーバー時に使うクリア、ゲームオーバーのスプライト
	//--------------------------------------------------------------------------------------
	class ClearSprite : public MultiSprite {
		Vec3 m_pos;
		Vec2 m_scale;
		wstring m_useName;
	public:
		ClearSprite(shared_ptr<Stage> &stage, bool trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey,wstring UseName);
		virtual ~ClearSprite() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
	//--------------------------------------------------------------------------------------
	/// クリア時、ゲームオーバー時に使う暗幕スプライト
	//--------------------------------------------------------------------------------------
	class BlackSprite : public MultiSprite {
		Vec3 m_pos;
		Vec2 m_scale;
		wstring m_useName;
	public:
		BlackSprite(shared_ptr<Stage> &stage, bool trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey, wstring UseName);
		virtual ~BlackSprite() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
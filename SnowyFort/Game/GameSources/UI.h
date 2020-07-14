/*!
@file UI.h
@brief UIなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	タイトルスプライト
	//--------------------------------------------------------------------------------------
	class TitleSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		TitleSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~TitleSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override {}
	};

	//--------------------------------------------------------------------------------------
	///	アニメスプライト
	//--------------------------------------------------------------------------------------
	class AnimeSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
		//トータル時間
		float m_TotalTime;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		AnimeSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~AnimeSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	///	数字のスプライト
	//--------------------------------------------------------------------------------------
	class NumSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		//表示する値
		float m_Score;
		//表示する桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		NumSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,const wstring& TextureKey, bool Trace,const Vec2& StartScale, const Vec3& StartPos);
		NumSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits, const wstring& TextureKey, bool Trace, const Vec2& StartScale, const Vec3& StartPos, const float& Score);
		virtual ~NumSprite(){}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//数値の設定
		inline float GetScore() const {
			return m_Score;
		}
		inline void SetScore(const float& val) {
			m_Score = val;
		}
	};

	//--------------------------------------------------------------------------------------
	///	数字のスプライト(非使用桁の非表示)
	//--------------------------------------------------------------------------------------
	class MyNumSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		//表示する値
		float m_Score;
		//表示する桁数
		UINT m_NumberOfDigits;
		UINT m_NumberOfDigitsBuff;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
		//桁を整える
		vector<uint16_t> UpdateDigits();
		shared_ptr<PTSpriteDraw> m_ptSpriteDraw;
	public:
		MyNumSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits, const wstring& TextureKey, bool Trace, const Vec2& StartScale, const Vec3& StartPos);
		MyNumSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits, const wstring& TextureKey, bool Trace, const Vec2& StartScale, const Vec3& StartPos, const float& Score);
		virtual ~MyNumSprite() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//数値の設定
		inline float GetScore() const {
			return m_Score;
		}
		inline void SetScore(const float& val) {
			m_Score = val;
		}
		inline void SetNumDigits(const UINT& NumberOfDigits) {
			m_NumberOfDigits = NumberOfDigits;
		}
	};

	//--------------------------------------------------------------------------------------
	///	連続して動くスプライト
	//--------------------------------------------------------------------------------------
	class MoveSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
		//生成フラグ
		bool m_Flg;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		MoveSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~MoveSprite() {};
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override;
	};
}
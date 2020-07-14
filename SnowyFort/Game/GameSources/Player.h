/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position; // プレイヤーが動く円の中心座標
		// 初期ステータス保存用
		Vec3 m_DefScale;
		Vec3 m_DefRotation;
		Vec3 m_DefPosition;
		//プレイヤーが使用するコントローラとキーボードの入力
		Vec2 GetInputState() const;
		// コントローラから方向ベクトルを得る
		//プレイヤーの移動
		void MovePlayer();
		//UIの作成
		void UICreate();
		//UIの移動
		void UIMove();
		//プレイヤーの位置をradを元に作成
		void PlayerRadToPos();
		//雪玉の進行方向の反対側に回り込む
		Vec3 PlayerWrapPos(Vec3 pos);
		//雪玉の進行方向を向く
		Vec3 PlayerWrapRot(Vec3 rot);
		//弾（雪玉）の生成位置を更新
		void ShotPosUpdate();
		//弾（雪玉）の大きさを初期化
		void ResetShotScale();
		//文字列の表示
		void DrawStrings();
		//入力ハンドラー
		InputHandler<Player> m_InputHandler;
		
		float m_PlayerMoveCircleHalf;	//プレイヤーの移動できる円のサイズ
		float m_Speed;					//プレイヤーのスピード
		float m_DefSpeed;				//プレイヤーの初期スピード
		Vec3 m_ShotPosition;			//弾の発射位置
		Vec3 m_ShotRotation;			//弾の回転（デバッグ用）
		float m_Rad;
		const float m_DEFAULTSHOTSCALE;
		float m_ShotScale;				//雪玉の大きさ
		float m_GettingLargeSpeed;		//雪玉の大きくなっていくスピード
		float m_MaxShotScale;
	public:
		Player(const shared_ptr<Stage>& StagePtr);
		Player(const shared_ptr<Stage>& StagePtr, const float Scale, const Vec3& Rotation, const Vec3& Position, const float m_PlayerMoveCircleHalf);
		virtual ~Player() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		//Bボタン
		void OnPushB();
		void OnPushX(){}

		//ゲッターセッター
		//Rad
		inline float GetRad() const
		{
			return m_Rad;
		}
		inline void SetRad(float rad)
		{
			m_Rad = rad;
		}
		//PlayerSpeed
		inline float GetSpeed() const
		{
			return m_Speed;
		}
		inline void SetSpeed(float speed)
		{
			m_Speed = speed;
		}
		//DefScale
		inline Vec3 SetDefScale() const
		{
			return m_DefScale;
		}
		inline void SetDefScale(Vec3 scale)
		{
			m_DefScale = scale;
		}
		//DefRot
		inline Vec3 GetDefRot() const
		{
			return m_DefRotation;
		}
		inline void SetDefRot(Vec3 rot)
		{
			m_DefRotation = rot;
		}
		//DefPos
		inline Vec3 GetDefPos() const
		{
			return m_DefPosition;
		}
		inline void SetDefPos(Vec3 pos)
		{
			m_DefPosition = pos;
		}
		//PlayerMoveCircleHalf
		inline float GetPlayerMoveCircleHalf() const
		{
			return m_PlayerMoveCircleHalf;
		}
		inline void SetCircleHalf(float radius)
		{
			m_PlayerMoveCircleHalf = radius;
		}

	};

}
//end basecross


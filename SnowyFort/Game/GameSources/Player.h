/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	�v���C���[
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position; // �v���C���[�������~�̒��S���W
		// �����X�e�[�^�X�ۑ��p
		Vec3 m_DefScale;
		Vec3 m_DefRotation;
		Vec3 m_DefPosition;
		//�v���C���[���g�p����R���g���[���ƃL�[�{�[�h�̓���
		Vec2 GetInputState() const;
		// �R���g���[����������x�N�g���𓾂�
		//�v���C���[�̈ړ�
		void MovePlayer();
		//UI�̍쐬
		void UICreate();
		//UI�̈ړ�
		void UIMove();
		//�v���C���[�̈ʒu��rad�����ɍ쐬
		void PlayerRadToPos();
		//��ʂ̐i�s�����̔��Α��ɉ�荞��
		Vec3 PlayerWrapPos(Vec3 pos);
		//��ʂ̐i�s����������
		Vec3 PlayerWrapRot(Vec3 rot);
		//�e�i��ʁj�̐����ʒu���X�V
		void ShotPosUpdate();
		//�e�i��ʁj�̑傫����������
		void ResetShotScale();
		//������̕\��
		void DrawStrings();
		//���̓n���h���[
		InputHandler<Player> m_InputHandler;
		
		float m_PlayerMoveCircleHalf;	//�v���C���[�̈ړ��ł���~�̃T�C�Y
		float m_Speed;					//�v���C���[�̃X�s�[�h
		float m_DefSpeed;				//�v���C���[�̏����X�s�[�h
		Vec3 m_ShotPosition;			//�e�̔��ˈʒu
		Vec3 m_ShotRotation;			//�e�̉�]�i�f�o�b�O�p�j
		float m_Rad;
		const float m_DEFAULTSHOTSCALE;
		float m_ShotScale;				//��ʂ̑傫��
		float m_GettingLargeSpeed;		//��ʂ̑傫���Ȃ��Ă����X�s�[�h
		float m_MaxShotScale;
	public:
		Player(const shared_ptr<Stage>& StagePtr);
		Player(const shared_ptr<Stage>& StagePtr, const float Scale, const Vec3& Rotation, const Vec3& Position, const float m_PlayerMoveCircleHalf);
		virtual ~Player() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		//B�{�^��
		void OnPushB();
		void OnPushX(){}

		//�Q�b�^�[�Z�b�^�[
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


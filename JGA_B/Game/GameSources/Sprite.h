#pragma once
#include "stdafx.h"

namespace basecross {
	struct BlinkRelated
	{
		float TotalBlinkTime;
		int BlinkNum;
		float OneBlinkTime = TotalBlinkTime / float(BlinkNum);

		void Reset() {
			OneBlinkTime = TmpOneBlinkTime;
		}
		float TmpOneBlinkTime = OneBlinkTime;
	};
	//���C��

	class MainSprite :public GameObject
	{
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_rotation;
		wstring m_texKey;
	public :
		MainSprite(shared_ptr<Stage>& stage,const Vec3& position,const Vec3& scale,const Vec3& Rotation,const wstring texKey);

		virtual ~MainSprite()
		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//2D���W�n��SetPostion�֐�
		void SetPosTion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
	};

	//�X�^�[�g���

	class StartSprite :public MainSprite
	{
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_rotation;
		wstring m_texKey;
	public:
		StartSprite(shared_ptr<Stage>& stage,const Vec3& postion,const Vec3& scale,const Vec3& Rotation,const wstring texKey);

		virtual ~StartSprite()
		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//2D���W�n��SetPostion�֐�
		void SetPostion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
	};

	//�{�^�������Ă˂̂���
	class PressAnyButtonSprite :public MainSprite
	{
		BlinkRelated m_blink;
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_rotation;
		wstring m_texKey;
		bool m_isPushButton;
		float m_blinkTime;
		float m_frameCount;
		bool m_tmpDrawActive;
	public:
		PressAnyButtonSprite(shared_ptr<Stage>& stage, const Vec3& postion, const Vec3& scale, const Vec3& Rotation, const wstring texKey);

		virtual ~PressAnyButtonSprite()
		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void Blink();
	};

	//�^�C�g�����S

	class TitleSprite :public MainSprite
	{
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_rotation;
		wstring m_texKey;
	public:
		TitleSprite(shared_ptr<Stage>& stage, const Vec3& postion, const Vec3& scale, const Vec3& Rotation, const wstring texKey);

		virtual ~TitleSprite()
		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//2D���W�n��SetPostion�֐�
		void SetPostion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
	};

	//�Z���N�g���

	class SelectSprite :public MainSprite
	{
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_rotation;
		wstring m_texKey;
	public:
		SelectSprite(shared_ptr<Stage>& stage,const Vec3& postion,const Vec3&scale,const Vec3& Rotation,const wstring texKey);

		virtual ~SelectSprite()
		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//2D���W�n��SetPostion�֐�
		void SetPosTion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
	};

	//�Q�[���I�[�o�[���

	class GameOverSprite :public MainSprite
	{
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_rotation;
		wstring m_texKey;
	public:
		GameOverSprite(shared_ptr<Stage>& stage, const Vec3& postion, const Vec3&scale, const Vec3& Rotation, const wstring texKey);

		virtual ~GameOverSprite()
		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//2D���W�n��SetPostion�֐�
		void SetPosTion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
	};

	//�Q�[���N���A���

	class GameClearSprite :public MainSprite
	{
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_rotation;
		wstring m_texKey;
	public:
		GameClearSprite(shared_ptr<Stage>& stage, const Vec3& postion, const Vec3&scale, const Vec3& Rotation, const wstring texKey);

		virtual ~GameClearSprite()
		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//2D���W�n��SetPostion�֐�
		void SetPosTion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
	};

	class CregitSprite :public MainSprite
	{
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_rotation;
		wstring m_texKey;
	public:
		CregitSprite(shared_ptr<Stage>& stage, const Vec3& postion, const Vec3&scale, const Vec3& Rotation, const wstring texKey);

		virtual ~CregitSprite()
		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//2D���W�n��SetPostion�֐�
		void SetPostion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
	};


}
/*!
@file UI.h
@brief UI�֘A
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�ʏ�X�v���C�g
	//--------------------------------------------------------------------------------------
	class MultiSprite : public GameObject {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;

		//�o�b�N�A�b�v���_�f�[�^
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
	///	�}���`�X�N�G�A
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
	///	���E�ړ�����X�v���C�g
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
		// �\�z�Ɣj��
		LRMoveSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos, const Vec3& Rotation, bool IsRight);
		virtual ~LRMoveSprite() {}

		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;

		void LRProcess();

	};
	//--------------------------------------------------------------------------------------
	///	�t�F�[�h
	//--------------------------------------------------------------------------------------

	//�t�F�[�h�C��
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

	//�t�F�[�h�A�E�g
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
		// �X�P�[��, �|�W�V����, �t�F�[�h�C���̎���, �`�悵�Ă������� ,�t�F�[�h�A�E�g�̎���
		FadeInAndOutSprite(const shared_ptr<Stage>& StagePtr,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey, float InTime, float DrawTime, float OutTime);
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void FadeIn();
		void SpriteDraw();
		void FadeOut();
	};
	//--------------------------------------------------------------------------------------
	///	�����̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class ScoreSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Score;
		float m_percent;
		//����
		UINT m_NumberOfDigits;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	NumberOfDigits	����
		@param[in]	TextureKey	�e�N�X�`���L�[
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		ScoreSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ScoreSprite() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�R�A�̃Z�b�g
		@param[in]	f	�l
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetScore(float f) {
			m_Score = f;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

		//�Ή����ꂽ%�\�L�̊֐�
		void ErosionScore();

		float GetPercent() {
			return m_percent;
		}
	};

	//--------------------------------------------------------------------------------------
	///	�g��k������X�v���C�g
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
		// �\�z�Ɣj��
		ScaleMoveSprite(const shared_ptr<Stage>& StagePtr,bool Trace,
			const Vec2& StartScale, const Vec2& StartPos, const wstring& TextureKey);
		virtual ~ScaleMoveSprite() {}

		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;

		void ScaleMoveProcess();

	};
	//--------------------------------------------------------------------------------------
	/// �N���A���A�Q�[���I�[�o�[���Ɏg�����g���C�̃X�v���C�g
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
	/// �N���A���A�Q�[���I�[�o�[���Ɏg���N���A�A�Q�[���I�[�o�[�̃X�v���C�g
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
	/// �N���A���A�Q�[���I�[�o�[���Ɏg���Ö��X�v���C�g
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
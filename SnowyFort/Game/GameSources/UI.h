/*!
@file UI.h
@brief UI�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�^�C�g���X�v���C�g
	//--------------------------------------------------------------------------------------
	class TitleSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	TextureKey	�e�N�X�`���L�[
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		TitleSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//�j��
		virtual ~TitleSprite();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override {}
	};

	//--------------------------------------------------------------------------------------
	///	�A�j���X�v���C�g
	//--------------------------------------------------------------------------------------
	class AnimeSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
		//�g�[�^������
		float m_TotalTime;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	TextureKey	�e�N�X�`���L�[
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		AnimeSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//�j��
		virtual ~AnimeSprite();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	///	�����̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class NumSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		//�\������l
		float m_Score;
		//�\�����錅��
		UINT m_NumberOfDigits;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		NumSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,const wstring& TextureKey, bool Trace,const Vec2& StartScale, const Vec3& StartPos);
		NumSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits, const wstring& TextureKey, bool Trace, const Vec2& StartScale, const Vec3& StartPos, const float& Score);
		virtual ~NumSprite(){}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//���l�̐ݒ�
		inline float GetScore() const {
			return m_Score;
		}
		inline void SetScore(const float& val) {
			m_Score = val;
		}
	};

	//--------------------------------------------------------------------------------------
	///	�����̃X�v���C�g(��g�p���̔�\��)
	//--------------------------------------------------------------------------------------
	class MyNumSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		//�\������l
		float m_Score;
		//�\�����錅��
		UINT m_NumberOfDigits;
		UINT m_NumberOfDigitsBuff;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
		//���𐮂���
		vector<uint16_t> UpdateDigits();
		shared_ptr<PTSpriteDraw> m_ptSpriteDraw;
	public:
		MyNumSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits, const wstring& TextureKey, bool Trace, const Vec2& StartScale, const Vec3& StartPos);
		MyNumSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits, const wstring& TextureKey, bool Trace, const Vec2& StartScale, const Vec3& StartPos, const float& Score);
		virtual ~MyNumSprite() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//���l�̐ݒ�
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
	///	�A�����ē����X�v���C�g
	//--------------------------------------------------------------------------------------
	class MoveSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
		//�����t���O
		bool m_Flg;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	TextureKey	�e�N�X�`���L�[
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		MoveSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//�j��
		virtual ~MoveSprite() {};
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override;
	};
}
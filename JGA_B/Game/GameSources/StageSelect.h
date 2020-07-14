#pragma once
#include "stdafx.h"

namespace basecross {
	class StageSelectObject;

	//--------------------------------------------------------------------------------------
	//�X�e�[�W�Z���N�g�V�[��
	//--------------------------------------------------------------------------------------
	class StageSelect : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		bool m_cntrolLock;
		float m_totalTime = 1.0f;
		int m_nowStageNum = 1;
		float m_frameCount = 0.0f;
		vector<weak_ptr<StageSelectObject>> m_spVec;
		void ChangeSelect(int num);
		void CreateSprite();
		void CreateFadeIn();
		void CreateFadeOut();
		void CreateNextStage();

	public:
		//�\�z�Ɣj��
		StageSelect() :Stage(), m_cntrolLock(false),m_spVec(6){}
		virtual ~StageSelect() {}

		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void CreateStageSelectObject();
		void CreateCameraTarget();
	};

	//--------------------------------------------------------------------------------------
	//�X�e�[�W�Z���N�g�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class StageSelectObject : public GameObject {
		Vec3 m_scale;
		Vec3 m_rotation;
		Vec3 m_position;
		wstring m_textureKey;
		bool m_selected;
		float m_frameTime;

	public:
		StageSelectObject(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Postion,
			const wstring& TextureKey
		);
		virtual ~StageSelectObject(){}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		bool IsSelect() const {
			return m_selected;
		}
		void SetSelect(bool b) {
			m_selected = b;
		}
	};
}
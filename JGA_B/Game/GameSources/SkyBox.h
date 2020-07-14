#pragma once
#include "stdafx.h"
#include "project.h"
namespace basecross
{
	class SkyBox : public GameObject
	{
		vector<shared_ptr<GameObject>> planes;
		vector<wstring> m_textureKeys;

	public:
		SkyBox(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{
			for (int i = 0; i < 12; i++) {
				m_textureKeys.push_back(L"SkyBox_TX" + Util::IntToWStr(i + 1));
			}
		}
		virtual void OnCreate()override;
		virtual void OnUpdate2()override;
		virtual void OnDraw()override;
	};
}
#include "stdafx.h"
#include "Project.h"
namespace basecross
{
	void SkyBox::OnCreate()
	{
		auto& app = App::GetApp();

		// スカイボックス用のテクスチャが入っているフォルダを指定する
		auto ptrTexturePath = app->GetDataDirWString() + L"Textures/";
		



		// 頂点カラーはすべて白
		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f);

		// ボックスの「角」にあたる頂点の座標だけをまとめておく
		const vector<Vec3> positions{
		 { -0.5f, +0.5f, +0.5f }, // 0
		 { +0.5f, +0.5f, +0.5f }, // 1
		 { -0.5f, -0.5f, +0.5f }, // 2
		 { +0.5f, -0.5f, +0.5f }, // 3

		 { -0.5f, +0.5f, -0.5f }, // 4
		 { +0.5f, +0.5f, -0.5f }, // 5
		 { -0.5f, -0.5f, -0.5f }, // 6
		 { +0.5f, -0.5f, -0.5f }  // 7
		};
		// 頂点の座標を並べて「面」を作る
		vector<vector<Vec3>> positionsArray = {
		 { positions[0], positions[1], positions[2], positions[3] }, // 正面
		 { positions[1], positions[5], positions[3], positions[7] }, // 右手
		 { positions[5], positions[4], positions[7], positions[6] }, // 手前
		 { positions[4], positions[0], positions[6], positions[2] }, // 左手
		 { positions[4], positions[5], positions[0], positions[1] }, // 上
		 { positions[2], positions[3], positions[6], positions[7] }  // 下
		};
		vector<uint16_t> indices = {
		 0, 1, 2,
		 2, 1, 3
		};
		// 面の数(6面)だけループ
		int textureIndex = 0;
		auto gm = GameManager::GetGM();
		auto sceneName = gm->GetSceneName();
		if (sceneName == L"StageSelect") {
			for (auto vPos : positionsArray) {
				// 面を形成する頂点データを作成
				vector<VertexPositionColorTexture> vertices = {
				 { vPos[0], white,{ 0.0f, 0.0f } },
				 { vPos[1], white,{ 1.0f, 0.0f } },
				 { vPos[2], white,{ 0.0f, 1.0f } },
				 { vPos[3], white,{ 1.0f, 1.0f } }
				};
				// 面をオブジェクトとして生成する
				auto plane = ObjectFactory::Create<GameObject>(GetStage());

				// 面にはドローコンポーネントをつけて、ポリゴンとテクスチャを適用する
				auto drawComp = plane->AddComponent<PCTStaticDraw>();
				drawComp->CreateOriginalMesh<VertexPositionColorTexture>(vertices, indices);
				drawComp->SetOriginalMeshUse(true);

					drawComp->SetTextureResource(m_textureKeys[textureIndex++]); // フォルダから読み込んだテクスチャを順番に適用

				// スカイボックスは可能な限り大きくする
					auto ptrTrans = plane->GetComponent<Transform>();
					const float scale = 707.0f;
					ptrTrans->SetScale(Vec3(scale));

					planes.push_back(plane);
			}
		}
		else if (sceneName == L"GameStage") {
			textureIndex = 6;
			for (auto vPos : positionsArray) {
				// 面を形成する頂点データを作成
				vector<VertexPositionColorTexture> vertices = {
				 { vPos[0], white,{ 0.0f, 0.0f } },
				 { vPos[1], white,{ 1.0f, 0.0f } },
				 { vPos[2], white,{ 0.0f, 1.0f } },
				 { vPos[3], white,{ 1.0f, 1.0f } }
				};
				// 面をオブジェクトとして生成する
				auto plane = ObjectFactory::Create<GameObject>(GetStage());

				// 面にはドローコンポーネントをつけて、ポリゴンとテクスチャを適用する
				auto drawComp = plane->AddComponent<PCTStaticDraw>();
				drawComp->CreateOriginalMesh<VertexPositionColorTexture>(vertices, indices);
				drawComp->SetOriginalMeshUse(true);
				drawComp->SetTextureResource(m_textureKeys[textureIndex++]); // フォルダから読み込んだテクスチャを順番に適用
				
				// スカイボックスは可能な限り大きくする
				auto ptrTrans = plane->GetComponent<Transform>();
				const float scale = 707.0f;
				ptrTrans->SetScale(Vec3(scale));

				planes.push_back(plane);
			}
		}
	}
	void SkyBox::OnUpdate2()
	{
		// スカイボックスの中心はカメラの座標と同じにしておかないと歪んで見えてしまう

		// カメラの座標を取得する
		auto ptrCamera = GetStage()->GetView()->GetTargetCamera();
		auto ptrCameraEye = ptrCamera->GetEye();

		// 全ての面にカメラの座標を適用する
		for (auto plane : planes) {
			auto transComp = plane->GetComponent<Transform>();
			transComp->SetPosition(ptrCameraEye);
		}
	}

	void SkyBox::OnDraw()
	{
		// 全ての面を描画する
		for (auto plane : planes) {
			plane->OnDraw();
		}
	}
}
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
//class MultiSpark : public MultiParticle;
//用途: 複数のスパーククラス
//--------------------------------------------------------------------------------------
//構築と破棄
	MultiSpark::MultiSpark(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	MultiSpark::~MultiSpark() {}

	//初期化
	void MultiSpark::OnCreate() {
		//加算描画処理をする
		//SetAddType(true);
	}

	void MultiSpark::InsertSpark(const Vec3& Pos) {
		auto ParticlePtr = InsertParticle(8);
		ParticlePtr->SetEmitterPos(Pos);
		ParticlePtr->SetTextureResource(L"FIRE_TX");
		ParticlePtr->SetMaxTime(0.4f);
		vector<ParticleSprite>& pSpriteVec = ParticlePtr->GetParticleSpriteVec();
		for (auto& rParticleSprite : ParticlePtr->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.3f - 0.15f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.1f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.3f - 0.15f;
			rParticleSprite.m_LocalScale = Vec2(0.75f, 0.75f);
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 15.0f,
				rParticleSprite.m_LocalPos.y * 60.0f,
				rParticleSprite.m_LocalPos.z * 15.0f
			);
			rParticleSprite.m_Color = Col4(0.01f, 1.0f, 0.02f, 1.0f);
		}
	}

	void MultiSpark::OnUpdate() {
		MultiParticle::OnUpdate();
	}


}
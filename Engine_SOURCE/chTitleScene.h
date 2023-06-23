#pragma once
#include "chScene.h"
#include "chAudioClip.h"
#include "chAudioSource.h"

namespace ch 
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		std::shared_ptr<AudioClip> audioClip;
		AudioSource* boss_audio;
		GameObject* audioObj;

	};


}


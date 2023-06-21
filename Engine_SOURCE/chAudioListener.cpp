#include "chAudioListener.h"
#include "chTransform.h"
#include "chGameObject.h"
#include "chFmod.h"

namespace ch
{
	AudioListener::AudioListener()
		: Component(eComponentType::AudioListener)
	{

	}

	AudioListener::~AudioListener()
	{

	}

	void AudioListener::Initalize()
	{

	}

	void AudioListener::Update()
	{

	}

	void AudioListener::FixedUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 foward = tr->Foward();
		Vector3 up = tr->Up();

		Vector3 vel = { 0.0f, 0.0f, 0.0f };
		Fmod::Set3DListenerAttributes(&pos, &vel, &foward, &up);
	}

	void AudioListener::Render()
	{

	}
}
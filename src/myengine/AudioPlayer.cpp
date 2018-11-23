#include "AudioPlayer.h"
#include "Sound.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include "Camera.h"

namespace frontier
{
	void AudioPlayer::OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<Sound> _sound)
	{
		Component::OnInit(_parent);
		_attachedSound = _sound;
	}

	void AudioPlayer::Play()
	{
		_attachedSound->play(getEntity()->getComponent<Transform>()->getPosition(), getCore()->getMainCamera()->getEntity()->getComponent<Transform>()->getPosition());
	}

	void AudioPlayer::Play(glm::vec3 _soundPosition, glm::vec3 _listenerPosition)
	{
		_attachedSound->play(_soundPosition, _listenerPosition);
	}

	void AudioPlayer::PlayWithVariance(float vol, float varMin, float varMax)
	{
		_attachedSound->play(vol, varMin, varMax, getEntity()->getComponent<Transform>()->getPosition(), getCore()->getMainCamera()->getEntity()->getComponent<Transform>()->getPosition());
	}

	void AudioPlayer::AttachSound(std::shared_ptr<Sound> _sound)
	{
		_attachedSound = _sound;
	}
}
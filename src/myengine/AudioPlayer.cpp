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
		m_attachedSound = _sound;
	}

	void AudioPlayer::Play(bool _looping)
	{
		m_attachedSound->play(getEntity()->getComponent<Transform>()->getPosition(), getCore()->getMainCamera()->getEntity()->getComponent<Transform>()->getPosition(), _looping);
	}

	void AudioPlayer::Play(glm::vec3 _soundPosition, glm::vec3 _listenerPosition, bool _looping)
	{
		m_attachedSound->play(_soundPosition, _listenerPosition, _looping);
	}

	void AudioPlayer::PlayWithVariance(float _vol, float _varMin, float _varMax)
	{
		m_attachedSound->play(_vol, _varMin, _varMax, getEntity()->getComponent<Transform>()->getPosition(), getCore()->getMainCamera()->getEntity()->getComponent<Transform>()->getPosition());
	}

	void AudioPlayer::AttachSound(std::shared_ptr<Sound> _sound)
	{
		m_attachedSound = _sound;
	}

	void AudioPlayer::Stop()
	{
		m_attachedSound->stop();
	}
}
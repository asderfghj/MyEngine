#ifndef _AUDIOPLAYER_H_
#define _AUDIOPLAYER_H_

#include "Component.h" 
#include "glm.hpp"

namespace frontier
{

	class Sound;
	class Entity;

	class AudioPlayer : public Component
	{
	private:
		std::shared_ptr<Sound> _attachedSound;

	public:
		void OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<Sound> _sound);
		void Play();
		void Play(glm::vec3 _soundPosition, glm::vec3 _listenerPosition);
		void PlayWithVariance(float vol, float varMin, float varMax);
		void AttachSound(std::shared_ptr<Sound> _sound);

	};

}

#endif
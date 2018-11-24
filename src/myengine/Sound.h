#include <memory>
#include <string>
#include "Resource.h"
#include "glm.hpp"
#include <AL/al.h>

namespace frontier
{
	struct SoundImpl;
	class Resources;


	class Sound : public Resource
	{
	private:
		std::shared_ptr<SoundImpl> impl;
		ALuint sid;

	public:
		Sound();
		static std::shared_ptr<Sound> Create(std::string path, std::shared_ptr<Resources> _resources);
		void load(std::string path);
		void play(float vol, float varMin, float varMax, glm::vec3 _soundPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _listenerPosition = glm::vec3(0.0f, 0.0f, 0.0f));
		void play(glm::vec3 _soundPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _listenerPosition = glm::vec3(0.0f, 0.0f, 0.0f), bool looping = false);
		void stop();
	};
}
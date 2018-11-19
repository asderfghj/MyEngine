#include <memory>
#include <string>
#include "Resource.h"

namespace myengine
{
	struct SoundImpl;
	class Resources;


	class Sound : public Resource
	{
	private:
		std::shared_ptr<SoundImpl> impl;

	public:
		Sound();
		static std::shared_ptr<Sound> Create(std::string path, std::shared_ptr<Resources> _resources);
		void load(std::string path);
		void play(float vol, float varMin, float varMax);
		void play();
	};
}
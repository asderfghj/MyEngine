#include "Component.h"

namespace frontier
{
	class Pooler;

	class AsteroidSpawner : public Component
	{
	private:
		std::weak_ptr<Pooler> AsteroidPooler;
		bool _doSpawn;
		int spawnCooldownTime, countedFrames, asteroidLimit;
		void Spawn();

	public:
		void OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<Pooler> _asteroidPooler);
		void OnTick() override;
		
	};
}
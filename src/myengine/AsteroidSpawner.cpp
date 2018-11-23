#include "AsteroidSpawner.h"
#include "Pooler.h"
#include "Environment.h"

namespace frontier
{
	void AsteroidSpawner::OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<Pooler> _asteroidPooler)
	{
		Component::OnInit(_parent);
		AsteroidPooler = _asteroidPooler;
		_doSpawn = true;
		countedFrames = 0;
		spawnCooldownTime = 120;
		asteroidLimit = 8;
	}

	void AsteroidSpawner::OnTick()
	{
		if (_doSpawn)
		{
			Spawn();
			_doSpawn = false;

		}
		else
		{
			countedFrames++;
			if (countedFrames > spawnCooldownTime)
			{
				_doSpawn = true;
				countedFrames = 0;
			}
		}
	}

	void AsteroidSpawner::Spawn()
	{
		if (AsteroidPooler.lock()->getActiveInPool() < asteroidLimit)
		{
			float determinant = getEnvironment()->getRandomBetweenTwoValues(0.0f, 4.0f);
			if (determinant < 1.0f)
			{
				//spawnpoint 1
				std::weak_ptr<Entity> newAsteroid = AsteroidPooler.lock()->Spawn()
			}
		}
	}

}
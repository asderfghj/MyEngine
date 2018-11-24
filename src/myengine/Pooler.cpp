#include "Pooler.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"

namespace frontier
{
	std::weak_ptr<Entity> Pooler::AddNewEntity()
	{
		std::weak_ptr<Entity> rtn = _corePtr.lock()->addEntity(poolPrefab);
		rtn.lock()->setActive(false);
		entities.push_back(rtn);
		return rtn;
	}

	void Pooler::OnInit(std::weak_ptr<Core> _core, std::string _id, std::shared_ptr<Prefab> _prefab, int initialPoolSize)
	{
		_corePtr = _core;
		poolID = _id;
		poolPrefab = _prefab;
		for (size_t i = 0; i < initialPoolSize; i++)
		{
			AddNewEntity();
		}
	}

	std::weak_ptr<Entity> Pooler::Spawn(glm::vec3 _position, bool _modifyScale, glm::vec3 _scale)
	{
		std::weak_ptr<Entity> newObject;
		bool objectFound = false;

		for (size_t i = 0; i < entities.size(); i++)
		{
			if (!entities[i].lock()->isActive() && !entities[i].lock()->isActivating())
			{
				newObject = entities[i];
				objectFound = true;
				newObject.lock()->setActivating(true);
				break;
			}
		}

		if (!objectFound)
		{
			newObject = AddNewEntity();
		}

		newObject.lock()->getComponent<Transform>()->setPosition(_position);
		if (_modifyScale)
		{
			newObject.lock()->getComponent<Transform>()->setScale(_scale);
		}
		_corePtr.lock()->AddToEntitiesToActivate(newObject.lock());
		return newObject;
	}

	std::string Pooler::getID()
	{
		return poolID;
	}

	int Pooler::getActiveInPool()
	{
		int activeObjects = 0;
		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities[i].lock()->isActive())
			{
				activeObjects++;
			}
		}

		return activeObjects;
	}

	void Pooler::deactivateAllInstances()
	{
		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities[i].lock()->isActive())
			{
				entities[i].lock()->setActive(false);
			}
		}
	}

}
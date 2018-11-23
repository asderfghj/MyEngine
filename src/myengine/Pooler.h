#include <string>
#include <memory>
#include <vector>
#include "glm.hpp"

namespace frontier
{
	class Prefab;
	class Entity;
	class Core;

	class Pooler
	{
	private:
		std::string poolID;
		std::shared_ptr<Prefab> poolPrefab;
		std::vector<std::weak_ptr<Entity>> entities;
		int poolSize;
		std::weak_ptr<Core> _corePtr;
		std::weak_ptr<Entity> AddNewEntity();
		

	public:
		void OnInit(std::weak_ptr<Core> _core, std::string _id, std::shared_ptr<Prefab> _prefab, int initialPoolSize);
		std::weak_ptr<Entity> Spawn(glm::vec3 _position, bool modifyScale = false, glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f));
		std::string getID();
		int getActiveInPool();

	};

}
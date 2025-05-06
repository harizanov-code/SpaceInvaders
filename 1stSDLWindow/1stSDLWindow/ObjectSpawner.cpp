#include "ECS.h"
#include "ObjectSpawner.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "ENUMS.h"


ObjectSpawner::ObjectSpawner(Manager& mManager) : manager(mManager) {
}

ObjectSpawner::~ObjectSpawner() {

}

  

void ObjectSpawner::spawnObject(Entity* e) {
    clearUnusedObjects();

    // 30% chance to spawn item
    int chance = rand() % 100;
    if (chance > 30) return; // 70% of the time, skip spawning

    if (!e->hasComponent<TransformComponent>()) return;

    auto& object = manager.addEntity();

    // Set transform
    auto& transform = e->getComponent<TransformComponent>();
    object.addComponent<TransformComponent>(
        transform.position.x, transform.position.y,
        64, 64, 1, 1024, 1024);
    object.getComponent<TransformComponent>().velocity.y = 2.0f;

    
    int typeIndex = rand() % 3;
    ItemType type = static_cast<ItemType>(typeIndex);

    const char* spritePath;
    std::string colliderTag;

    switch (type) {
    case ItemType::Speed:
        spritePath = "Pictures/Objects/Energy_Object_1.png";
        colliderTag = "itemSpeed";
        break;
    case ItemType::Health:
        spritePath = "Pictures/Objects/Health_Object_1.png";
        colliderTag = "itemHealth";
        break;
    case ItemType::BulletSpeed:
        spritePath = "Pictures/Objects/BulletSpeed_Object_1.png";
        colliderTag = "itemBulletSpeed";
        break;
    }

    object.addComponent<SpriteComponent>(spritePath);
    object.addComponent<ColliderComponent>(colliderTag);
    object.addGroup(groupItems);
}

void ObjectSpawner::clearUnusedObjects() {



	objects.erase(
		std::remove_if(objects.begin(), objects.end(), [](Entity* e) {
		if (e->isActive()) {
			return false;
		}
		return true;
	}),
		objects.end()
	);

}

#include "ECS.h"

void Entity::addGroup(Group mGroup) {

	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}
Entity::Entity(Manager& mManager)
	: manager(mManager) {
}

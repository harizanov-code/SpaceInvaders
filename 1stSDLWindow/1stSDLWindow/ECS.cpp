#include "ECS.h"

// Component class
Component::Component() : entity(nullptr) {
}

void Component::init() {
}
void Component::update() {
}
void Component::draw() {
}
Component::~Component() {
}

Manager& Entity::getManager() {
    
        return this->manager;

  
}

// Entity class
Entity::Entity(Manager& mManager) : manager(mManager) {
}

void Entity::update() {
    for (auto& c : components) {
        c->update();
    }
}

void Entity::draw() {
    for (auto& c : components) {
        c->draw();
    }
}

bool Entity::isActive() const {
    return active;
}

void Entity::destroy() {
    active = false;
}

bool Entity::hasGroup(Group mGroup) {
    return groupBitset[mGroup];
}

void Entity::addGroup(Group mGroup) {
    groupBitset[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}

void Entity::delGroup(Group mGroup) {
    groupBitset[mGroup] = false;
}


// Manager class
void Manager::update() {
    for (auto& e : entities) {
        e->update();
    }
}

void Manager::draw() {
    for (auto& e : entities) {
        e->draw();
    }
}

void Manager::refresh() {
    for (auto i(0u); i < maxGroups; i++) {
        auto& v(groupedEntities[i]);
        v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity) {
            return !mEntity->isActive() || !mEntity->hasGroup(i);
        }), std::end(v));
    }

    entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity) {
        return !mEntity->isActive();
    }), std::end(entities));
}

void Manager::AddToGroup(Entity* mEntity, Group mGroup) {
    groupedEntities[mGroup].emplace_back(mEntity);
}

std::vector<Entity*>& Manager::getGroup(Group mGroup) {
    return groupedEntities[mGroup];
}

Entity& Manager::addEntity() {
    Entity* e = new Entity(*this);
    std::unique_ptr<Entity> uPtr{ e };
    entities.emplace_back(std::move(uPtr));
    return *e;
}

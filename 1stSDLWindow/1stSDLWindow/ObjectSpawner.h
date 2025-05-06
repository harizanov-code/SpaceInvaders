#pragma once

#include <vector>
#include <random>
#include <cstdlib>  
#include <ctime> 

class Manager;
class Entity;

class ObjectSpawner {
private:
	Manager& manager;
	std::vector<Entity*> objects;
	std::mt19937 rng;


public:

	ObjectSpawner(Manager& mManager);
	~ObjectSpawner();

	void spawnObject(Entity* e);
	void clearUnusedObjects();

};
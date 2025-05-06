#pragma once
#include <SDL3/SDL.h>


class ColliderComponent;

class Collision {
	
public:

	//access align bounding box;
	static bool AABB(const SDL_FRect& recA, const SDL_FRect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};
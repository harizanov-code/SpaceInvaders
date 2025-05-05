#include "Collision.h"
#include "ColliderComponent.h"

 bool Collision::AABB(const SDL_FRect& recA, const SDL_FRect& recB) {
    // Check for no collision (early exit)

    if (recA.x + recA.w < recB.x || recB.x + recB.w < recA.x ||
        recA.y + recA.h < recB.y || recB.y + recB.h < recA.y) {
        return false;
    }


    return true;
}

 bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB) {
 
     if (AABB(colA.collider, colB.collider)) {

         //std::cout << colA.tag << "hit : " << colB.tag << std::endl;

         return true;
     }
     else {

        return false;
     }
 

 
 
 
 };

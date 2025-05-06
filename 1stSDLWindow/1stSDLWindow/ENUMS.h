#pragma once
#include <cstddef>



enum groupLabels : std::size_t {

	groupMap,
	groupPlayers,
	groupEnemies,
	groupWall,
	groupColliders,
	groupItems,
	groupProjectile

};





enum class ItemType {
	Speed,
	Health,
	BulletSpeed
};

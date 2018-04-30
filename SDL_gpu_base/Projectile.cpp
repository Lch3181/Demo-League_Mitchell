#include "Projectiles.h"

bool Projectile::IsColliding(Car* car)
{
	Vec2 separation = car->position - position;
	return (separation.Magnitude() < car->position.w);
}
#include "Gun.h"

void Gun::Fire(Vector<Projectile*>&projectiles) // Here is the definition
{
	if (firerateTimer > firerate && Ammo>0)
	{
		projectiles.push_back(new Projectile(position, facingDegrees, damage, initialSpeedOfProjectile, projectilesImage));
		Ammo--;
		firerateTimer = 0.0f;
	}
}
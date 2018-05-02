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

void Gun::FireBackward(Vector<Projectile*>&projectiles) // Here is the definition
{
	if (firerateTimer > firerate && Ammo>0)
	{
		projectiles.push_back(new Projectile(position, facingDegrees, damage, initialSpeedOfProjectile, projectilesImage));
		Ammo--;

		initialSpeedOfProjectile *= -1;
		projectiles.push_back(new Projectile(position, facingDegrees, damage, initialSpeedOfProjectile, projectilesImage));
		Ammo--;
		firerateTimer = 0.0f;
	}
}

void Gun::ShortGun(Vector<Projectile*>&projectiles)
{
	if (firerateTimer > firerate && Ammo>=5)
	{
		float temp_facingDegree = facingDegrees;
		temp_facingDegree -= 30;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		temp_facingDegree += 6;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		temp_facingDegree += 6;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		temp_facingDegree += 6;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		temp_facingDegree += 6;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		Ammo-=5;
		firerateTimer = 0.0f;
		firerateTimer -= firerate * 3;
	}
}

void Gun::ShortGunBackward(Vector<Projectile*>&projectiles)
{
	if (firerateTimer > firerate && Ammo>=5)
	{
		float temp_facingDegree = facingDegrees;
		temp_facingDegree -= 30;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		temp_facingDegree += 6;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		temp_facingDegree += 6;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		temp_facingDegree += 6;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		temp_facingDegree += 6;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		Ammo -= 5;

		initialSpeedOfProjectile *= -1;
		temp_facingDegree -= 30;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		temp_facingDegree += 6;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		temp_facingDegree += 6;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		temp_facingDegree += 6;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		temp_facingDegree += 6;
		projectiles.push_back(new Projectile(position, temp_facingDegree, damage, initialSpeedOfProjectile, projectilesImage));
		Ammo-=5;
		firerateTimer = 0.0f;
		firerateTimer -= firerate * 3;
	}
}

void Gun::ForFun(Vector<Projectile*>&projectiles)
{
	if (firerateTimer > firerate && Ammo>0)
	{
		for (int i = 0; i < 60; i++)
		{
			projectiles.push_back(new Projectile(position, facingDegrees, damage, initialSpeedOfProjectile, projectilesImage));
			facingDegrees += 6;
		}

		Ammo-=60;
		firerateTimer = 0.0f;
		firerateTimer -= firerate * 20;
	}
}
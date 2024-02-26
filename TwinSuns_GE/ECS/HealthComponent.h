#pragma once

#include "Components.h"

class HealthComponent : public Component
{
	
public:

	int maxHealth;
	int currentHealth;
	bool isAlive;

	HealthComponent()
	{
		maxHealth = 100;
		currentHealth = 100;
		isAlive = true;
	}

	HealthComponent(int h1, int h2, bool status)
	{
		maxHealth = h1;
		currentHealth = h2;
		isAlive = status;
	}

	void Init() override
	{

	}

	void Update() override
	{
	}

	void Heal()
	{
		currentHealth = maxHealth;
	}

	void ApplyDamage(int dam)
	{
		currentHealth = currentHealth - dam;

		if (currentHealth <= 0)
		{
			isAlive = false;
		}

	}

	bool GetStatus()
	{
		return isAlive;
	}

};

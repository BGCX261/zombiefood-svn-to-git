#include "WeaponManager.h"

WeaponManager::WeaponManager(void)
{
	iPrimaryWeaponType = MACHINEGUN;
	iPrimaryWeaponAmmunition = eMACHINEGUNInfo::CLIPCAPACITY;
	iPrimaryWeaponAmmunitionMaxClip = eMACHINEGUNInfo::MAXCLIP;
	iPrimaryWeaponAmmunitionClipCapacity = eMACHINEGUNInfo::CLIPCAPACITY;
	bPrimaryWeaponFired = false;
}

WeaponManager::~WeaponManager(void)
{
}

// functions to get information about the primary weapons
ePrimaryWeaponTypes WeaponManager::GetPrimaryWeaponType(void)
{
	return iPrimaryWeaponType;
}
int WeaponManager::GetPrimaryWeaponAmmunition(void)
{
	return iPrimaryWeaponAmmunition;
}
int WeaponManager::GetPrimaryWeaponTotalAmmunition(void)
{
	return iPrimaryWeaponTotalAmmunition;
}
int WeaponManager::GetPrimaryWeaponAmmunitionClip(void)
{
	return iPrimaryWeaponAmmunitionClip;
}
int WeaponManager::GetPrimaryWeaponMaxClip(void)
{
	return iPrimaryWeaponAmmunitionMaxClip;
}
int WeaponManager::GetPrimaryWeaponClipCapacity(void)
{
	return iPrimaryWeaponAmmunitionClipCapacity;
}
bool WeaponManager::hasPrimaryWeaponFired(void)
{
	return bPrimaryWeaponFired;
}

bool WeaponManager::ReloadPrimaryWeapon(void)
{
	int totalAmmo = iPrimaryWeaponAmmunition + iPrimaryWeaponTotalAmmunition;
	if (totalAmmo > iPrimaryWeaponAmmunitionClipCapacity)
	{
		iPrimaryWeaponAmmunition = iPrimaryWeaponAmmunitionClipCapacity;
		iPrimaryWeaponTotalAmmunition -= iPrimaryWeaponAmmunitionClipCapacity;
		iPrimaryWeaponAmmunitionClip = (int) (iPrimaryWeaponTotalAmmunition / iPrimaryWeaponAmmunitionClipCapacity);
	}
	else
	{
		iPrimaryWeaponAmmunition = iPrimaryWeaponAmmunitionClipCapacity;
		iPrimaryWeaponAmmunitionClipCapacity = 0;
		iPrimaryWeaponAmmunitionClip = 0;
	}

	return true;
}
bool WeaponManager::UpdatePrimaryWeaponAmmunition(const int iAmmunitionUsed)
{
	if (iPrimaryWeaponAmmunition < iAmmunitionUsed)
		return false;

	iPrimaryWeaponAmmunition -= iAmmunitionUsed;
	if (iPrimaryWeaponAmmunition < 0)
		return false;
	else
		ReloadPrimaryWeapon();

	return true;
}

bool WeaponManager::AddPrimaryWeaponAmmunitionClip(void)
{
	if (iPrimaryWeaponAmmunitionClip==iPrimaryWeaponAmmunitionMaxClip)
		return false;

	iPrimaryWeaponAmmunitionClip++;
	return true;
}

void WeaponManager::togglePrimaryWeaponFired(void)
{
	bPrimaryWeaponFired = !bPrimaryWeaponFired;
}

#pragma once

enum ePrimaryWeaponTypes
{
	EMPTY				= 0,
	REVOLVER			= 1,
	PISTOL				= 2,
	MACHINEGUN			= 3,
	SHOTGUN				= 4,

	UNKNOWN				= -1
};

class eMACHINEGUNInfo
{
public:
	static const int MAXCLIP = 5;
	static const int CLIPCAPACITY = 30;
};

enum eSecondaryWeaponTypes
{
	KNIFE				= 10,
	GRENADE				= 11,
	FLARE				= 12,
	SWORD				= 13,
	TENNISRACQUET		= 14,
	GOLFCLUB			= 15,
};

class WeaponManager
{
public:
	WeaponManager(void);
	~WeaponManager(void);

	// functions to get information about the primary weapons
	ePrimaryWeaponTypes GetPrimaryWeaponType(void);
	int GetPrimaryWeaponAmmunition(void);
	int GetPrimaryWeaponTotalAmmunition(void);
	int GetPrimaryWeaponAmmunitionClip(void);
	int GetPrimaryWeaponMaxClip(void);
	int GetPrimaryWeaponClipCapacity(void);
	bool hasPrimaryWeaponFired(void);

	bool ReloadPrimaryWeapon(void);
	bool UpdatePrimaryWeaponAmmunition(const int iAmmunitionUsed);
	bool AddPrimaryWeaponAmmunitionClip(void);
	void togglePrimaryWeaponFired(void);

	int GetSecondaryWeaponType(void);

private:
	ePrimaryWeaponTypes  iPrimaryWeaponType;
	int  iPrimaryWeaponAmmunition;				// The number of ammunition left
	int  iPrimaryWeaponTotalAmmunition;			// The number of ammunition left including those in the clips
	int  iPrimaryWeaponAmmunitionClip;			// The number of clips which a player currently hold
	int  iPrimaryWeaponAmmunitionMaxClip;		// The maximum number of clips which a player can hold
	int  iPrimaryWeaponAmmunitionClipCapacity;	// The maximum number of ammunition in 1 clip
	bool bPrimaryWeaponFired;					// true = fired, false = not fired
	int  iSecondaryWeaponType;
	bool bSecondaryWeaponFired;		// true = fired, false = not fired
};

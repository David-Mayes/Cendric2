#pragma once

#include <SFML/Graphics.hpp>
#include "global.h"

#include "Enums/SpellID.h"
#include "Enums/SpellType.h"
#include "Enums/DamageType.h"
#include "Enums/Key.h"
#include "Structs/SpellModifier.h"

class SpellCreator;
class LevelMovableGameObject;

/* describes the attributes of a spell */
struct SpellData {
	SpellID id;
	SpellType spellType;
	sf::IntRect iconTextureRect;
	sf::Time cooldown;
	sf::FloatRect boundingBox;
	DamageType damageType;
	bool needsTarget;

	// modifiable by crystal modifiers
	int damage;
	int heal;
	int reflectCount;
	float startVelocity;
	int count;
	sf::Time duration;
	float range;

	float divergenceAngle;
	float rangeModifierAddition;
	int damageModifierAddition;
	float speedModifierAddition;
	int countModifierAddition;
	int reflectModifierAddition;
	sf::Time durationModifierAddition;

	Key inputKey;

	static SpellData getSpellData(SpellID id);
	static std::vector<SpellModifierType> getAllowedModifiers(SpellID id);
	static SpellCreator* getSpellCreator(const SpellData& data, const std::vector<SpellModifier>& modifiers, LevelMovableGameObject* owner);

private:
	static SpellData getChopSpellData();

	static SpellData getFireBallSpellData();
	static SpellData getIceBallSpellData();
	static SpellData getTelekinesisSpellData();
	static SpellData getWindGustSpellData();
	static SpellData getAntiGravitySpellData();

	static SpellData getUnlockSpellData();
	// static SpellData getShadowTrapSpellData();
	static SpellData getInvisibilitySpellData();
	// static SpellData getFlashSpellData();
	static SpellData getIcyAmbushSpellData();

	static SpellData getFearSpellData();
	static SpellData getLeechSpellData();
	// static SpellData getReviveTheDeadSpellData();
	// static SpellData getGhostSpellData();
	// static SpellData getSummonCreatureSpellData();

	static SpellData getLightSpellData();
	static SpellData getDivineShieldSpellData();
	// static SpellData getWrathOfTheGodsSpellData();
	// static SpellData getJusticeSpellData();
	static SpellData getAureolaSpellData();
};

const struct SpellData EMPTY_SPELL =
{
	SpellID::VOID,
	SpellType::VOID,
	sf::IntRect(0, 0, 0, 0),
	sf::seconds(1),
	sf::FloatRect(0, 0, 0, 0),
	DamageType::VOID,
	false,

	0,
	0,
	0,
	0.f,
	1,
	sf::Time::Zero,
	0.f,

	0.f,
	0.f,
	0,
	0,
	0,
	0,
	sf::Time::Zero,

	Key::VOID
};
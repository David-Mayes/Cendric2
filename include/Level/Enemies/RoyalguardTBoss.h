#pragma once

#include "global.h"
#include "Level/Enemies/RoyalguardBoss.h"

class RoyalguardTBoss final : public RoyalguardBoss {
public:
	RoyalguardTBoss(const Level* level, Screen* screen);

	void addDamage(int damage, DamageType damageType, bool overTime, bool critical) override;
	EnemyID getEnemyID() const override { return EnemyID::Boss_Royalguard_T; }

protected:
	void updateBossState(const sf::Time& frameTime) override;

	std::string getSpritePath() const override;
	std::string getDeathSoundPath() const override;
	std::string getWeaponTexturePath() const override;

	MovingBehavior* createMovingBehavior(bool asAlly) override;
	AttackingBehavior* createAttackingBehavior(bool asAlly) override;
	void handleAttackInput();
	void loadAttributes() override;
	void loadSpells() override;
	void loadAnimation(int skinNr) override;
	void loadParticles() override;

protected:
	ParticleComponent* m_icePc;
};
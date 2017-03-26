#pragma once

#include "global.h"
#include "Level/LevelDynamicTile.h"

#include "Particles/ParticleGenerator.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleUpdater.h"

class LightComponent;

class DivineTorchTile : public LevelDynamicTile {
public:
	DivineTorchTile(LevelScreen* levelScreen);

	void update(const sf::Time& frameTime) override;
	void render(sf::RenderTarget& target) override;

	void setPosition(const sf::Vector2f& position) override;
	void setTarget(GameObject* target, bool force = false);

	void init() override;
	void loadAnimation(int skinNr) override;
	void onHit(Spell* spell) override;
	LevelDynamicTileID getDynamicTileID() const override { return LevelDynamicTileID::DivineTorch; }

private:
	std::string getSpritePath() const override;
	LightComponent* m_lightComponent;
	GameObject* m_target = nullptr;

	particles::TextureParticleSystem* m_ps = nullptr;
	particles::ParticleSpawner* m_particleSpawner = nullptr;
	particles::AimedVelocityGenerator* m_velGen = nullptr;

	void loadParticleSystem();

	void updateParticleSystemPosition();
};
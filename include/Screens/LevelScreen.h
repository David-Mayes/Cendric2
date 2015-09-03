#pragma once

#include "global.h"
#include "Level.h"
#include "LevelMainCharacter.h"
#include "Screen.h"
#include "ResourceManager.h"
#include "LevelMainCharacterLoader.h"
#include "LevelInterface.h"

#include "GUI/Button.h"
#include "Enums/LevelID.h"

class LevelScreen : public Screen
{
public:
	LevelScreen(LevelID levelID, CharacterCore* core);
	// called by the loading screen
	void load();

	Screen* update(const sf::Time& frameTime) override;
	void render(sf::RenderTarget& renderTarget) override;
	void execOnEnter(const Screen* previousScreen) override;
	void execOnExit(const Screen* nextScreen) override;

	void addBuffToInterface(BuffType type, const sf::IntRect& textureLocation, const sf::Time& duration) const;
	// reloads the inventory if it is visible
	void reloadInventory();

	// called by the loading screen. the dynamic tiles in level
	void loadDynamicTiles();

	// the level screen does not use the original core, but runs on a copy. To get the original, call this method.
	CharacterCore* getOriginalCharacterCore() const;
	// the level screen doesn't return the original core here, but a mere copy.
	CharacterCore* getCharacterCore() const override;

private:
	Level m_currentLevel;
	LevelMainCharacter* m_mainChar;
	LevelID m_levelID;
	LevelInterface* m_interface;	

	bool m_isGameOver = false;
	BitmapText* m_overlayText = nullptr;
	sf::Sprite* m_overlaySprite = nullptr;
	Button* m_retryButton = nullptr;
	Button* m_backToMenuButton = nullptr;

	// the level screen runs on a copy of the character core that only gets written back to the original core
	// if a checkpoint is reached or the level is finished.
	CharacterCore* m_characterCoreCopy = nullptr;

	void cleanUp();
};
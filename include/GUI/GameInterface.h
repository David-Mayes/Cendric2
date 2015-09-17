#pragma once

#include "global.h"
#include "CharacterCore.h"
#include "InputController.h"
#include "ResourceManager.h"

#include "GUI/Inventory.h"
#include "GUI/CharacterInfo.h"
#include "GUI/Spellbook.h"
#include "GUI/QuestLog.h"

class GameScreen;

// abstract class for an interface in level or map
class GameInterface
{
public:
	GameInterface(GameScreen* screen);
	virtual ~GameInterface();

	// reloads the inventory for the items that have changed. if the string equals "gold", reloads gold
	virtual void reloadInventory(const std::string& changeditemID);
	// reloads the quest log 
	virtual void reloadQuestLog();
	
	virtual void render(sf::RenderTarget& target);
	virtual void update(const sf::Time& frameTime);

	CharacterCore* getCore() const;

protected:
	GameScreen* m_screen;
	CharacterCore* m_core;

	// <<< INVENTORY >>>
	Inventory* m_inventory = nullptr;
	void updateInventory(const sf::Time& frameTime);

	// <<< CHARCTER INFO >>>
	CharacterInfo* m_characterInfo = nullptr;
	void updateCharacterInfo();

	// <<< SPELLBOOK >>>
	Spellbook* m_spellbook = nullptr;
	void updateSpellbook(const sf::Time& frameTime);

	// <<< QUEST LOG >>>
	QuestLog* m_questLog = nullptr;
	void updateQuestLog(const sf::Time& frameTime);
};
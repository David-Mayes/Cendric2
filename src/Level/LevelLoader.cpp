#include "Level/LevelLoader.h"
#include "Level/LevelMainCharacter.h"
#include "Level/Level.h"
#include "Level/Enemy.h"
#include "Enemies/RatEnemy.h"
#include "Enemies/FireRatEnemy.h"
#include "Enemies/NekomataEnemy.h"
#include "LightObject.h"

using namespace std;

void LevelLoader::loadChestTiles(LevelData& data, Screen* screen, Level* level) const {
	LevelMainCharacter* mainCharacter = dynamic_cast<LevelMainCharacter*>(screen->getObjects(GameObjectType::_MainCharacter)->at(0));
	if (mainCharacter == nullptr) {
		g_logger->logError("LevelLoader", "Could not find main character of game screen");
		return;
	}

	const CharacterCoreData& coreData = screen->getCharacterCore()->getData();

	// create chests if they are not looted yet
	for (auto& it : data.chests) {
		if (coreData.chestsLooted.at(data.id).find(it.first) == coreData.chestsLooted.at(data.id).end()) {
			ChestTile* chestTile = nullptr;
			// calculate loot.
			std::map<string, int> loot;
			int gold = 0;
			if (data.chestLoot.find(it.first) != data.chestLoot.end()) {
				gold = data.chestLoot.at(it.first).second;
				for (auto& item : data.chestLoot.at(it.first).first) {
					loot.insert({ item.first, item.second });
				}
			}
			chestTile = new ChestTile(mainCharacter, level);
			chestTile->setTileSize(data.tileSize);
			chestTile->init();
			chestTile->setObjectID(it.first);
			if (data.chestStrength.find(it.first) != data.chestStrength.end()) chestTile->setStrength(data.chestStrength.at(it.first));
			chestTile->setLoot(loot, gold);
			chestTile->setPosition(it.second.second - chestTile->getPositionOffset());
			chestTile->setDebugBoundingBox(sf::Color::Yellow);
			chestTile->load(it.second.first);
			screen->addObject(chestTile);
		}
	}
}

void LevelLoader::loadLeverTiles(LevelData& data, Screen* screen, Level* level) const {
	LevelMainCharacter* mainCharacter = dynamic_cast<LevelMainCharacter*>(screen->getObjects(GameObjectType::_MainCharacter)->at(0));
	if (mainCharacter == nullptr) {
		g_logger->logError("LevelLoader", "Could not find main character of game screen");
		return;
	}

	for (auto& it : data.levers) {
		
		std::vector<SwitchableTile*> dependentTiles;

		// create the switch tiles and add them.
		for (auto& switchBean : it.dependentTiles) {
			SwitchableTile* tile = new SwitchableTile(level);
			tile->setInitialState(switchBean.id == LevelDynamicTileID::SwitchableOn);
			tile->setTileSize(data.tileSize);
			tile->init();
			tile->setPosition(switchBean.position);
			tile->setDebugBoundingBox(sf::Color::Yellow);
			tile->load(switchBean.skinNr);
			screen->addObject(tile);
			dependentTiles.push_back(tile);
		}

		// create the lever tiles and add them.
		for (auto& leverBean : it.levers) {
			LeverTile* tile = new LeverTile(level, mainCharacter);
			tile->setTileSize(data.tileSize);
			tile->init();
			tile->setPosition(leverBean.position);
			tile->setDebugBoundingBox(sf::Color::Yellow);
			tile->load(leverBean.skinNr);
			tile->setDependantTiles(dependentTiles);
			screen->addObject(tile);
		}
	}
}

void LevelLoader::loadDynamicTiles(LevelData& data, Screen* screen, Level* level) const {
	LevelMainCharacter* mainCharacter = dynamic_cast<LevelMainCharacter*>(screen->getObjects(GameObjectType::_MainCharacter)->at(0));
	if (mainCharacter == nullptr) {
		g_logger->logError("LevelLoader", "Could not find main character of game screen");
		return;
	}

	const CharacterCoreData& coreData = screen->getCharacterCore()->getData();

	for (auto& it : data.dynamicTiles) {
		LevelDynamicTile* tile = nullptr;
		switch (it.id) {
		case LevelDynamicTileID::Water:
			tile = new SimulatedWaterTile(level);
			tile->setBoundingBox(sf::FloatRect(0.f, 0.f, it.size.x, it.size.y));
			break;
		case LevelDynamicTileID::Ice:
			tile = new IceTile(level);
			break;
		case LevelDynamicTileID::CrumblyBlock:
			tile = new CrumblyBlockTile(level);
			break;
		case LevelDynamicTileID::Torch:
			tile = new TorchTile(level);
			break;
		case LevelDynamicTileID::SpikesBottom:
			tile = new SpikesBottomTile(level);
			break;
		case LevelDynamicTileID::SpikesTop:
			tile = new SpikesTopTile(level);
			break;
		case LevelDynamicTileID::ShiftableBlock:
			tile = new ShiftableBlockTile(level);
			break;
		case LevelDynamicTileID::Checkpoint:
			tile = new CheckpointTile(level);
			break;
		default:
			// unexpected error
			g_logger->logError("LevelLoader", "Dynamic tile was not loaded, unknown id.");
			return;
		}

		tile->setTileSize(data.tileSize);
		tile->init();
		tile->setPosition(it.position - tile->getPositionOffset());
		tile->setDebugBoundingBox(sf::Color::Yellow);
		tile->load(it.skinNr);
		screen->addObject(tile);
	}
}

void LevelLoader::loadLevelItems(LevelData& data, Screen* screen) const {
	LevelMainCharacter* mainCharacter = dynamic_cast<LevelMainCharacter*>(screen->getObjects(GameObjectType::_MainCharacter)->at(0));
	if (mainCharacter == nullptr) {
		g_logger->logError("LevelLoader", "Could not find main character of game screen");
		return;
	}

	int x = 0;
	int y = 0;
	const CharacterCoreData& coreData = screen->getCharacterCore()->getData();

	// calculate level positions and create them if they are not looted yet
	for (int i = 0; i < data.levelItems.size(); i++) {
		auto& it = data.levelItems.at(i);
		if (!it.empty() && (coreData.itemsLooted.at(data.id).find(i) == coreData.itemsLooted.at(data.id).end())) {
			sf::Vector2f position(static_cast<float>(x * data.tileSize.x), static_cast<float>(y * data.tileSize.y));
			ItemBean item = g_databaseManager->getItemBean(it);
			if (item.status == BeanStatus::Error) {
				// unexpected error
				g_logger->logError("LevelLoader", "Level item was not loaded, unknown id.");
				return;
			}

			LevelItem* levelItem = new LevelItem();
			levelItem->load(mainCharacter, Item(item.item_id), position);
			levelItem->setSpawnPosition(i);
			screen->addObject(levelItem);
		}
		if (x + 1 >= data.mapSize.x) {
			x = 0;
			y++;
		}
		else {
			x++;
		}
	}
}

void LevelLoader::loadEnemies(LevelData& data, Screen* screen, Level* level) const {
	LevelMainCharacter* mainCharacter = dynamic_cast<LevelMainCharacter*>(screen->getObjects(GameObjectType::_MainCharacter)->at(0));
	if (mainCharacter == nullptr) {
		g_logger->logError("LevelLoader", "Could not find main character of game screen");
		return;
	}

	const CharacterCoreData& coreData = screen->getCharacterCore()->getData();

	// create enemies if they are not looted yet
	for (auto& it : data.enemies) {
		if (coreData.enemiesLooted.at(data.id).find(it.first) == coreData.enemiesLooted.at(data.id).end()) {
			Enemy* enemy = nullptr;
			// calculate loot.
			std::map<string, int> loot;
			int gold = 0;
			if (data.enemyLoot.find(it.first) != data.enemyLoot.end()) {
				gold = data.enemyLoot.at(it.first).second;
				for (auto& item : data.enemyLoot.at(it.first).first) {
					loot.insert({ item.first, item.second });
				}
			}
			switch (it.second.first) {
			case EnemyID::Rat:
				enemy = new RatEnemy(level, mainCharacter);
				if (gold == 0 && loot.empty()) {
					loot.insert({ "fo_cheese", 1 });
					gold = 1;
				}
				break;
			case EnemyID::FireRat:
				enemy = new FireRatEnemy(level, mainCharacter);
				if (gold == 0 && loot.empty()) {
					loot.insert({ "fo_bread", 2 });
					gold = 2;
				}
				break;
			case EnemyID::Nekomata_blue:
				enemy = new NekomataEnemy(level, mainCharacter);
				if (gold == 0 && loot.empty()) {
					loot.insert({ "mi_goldengoblet", 1 });
					gold = 100;
				}
				break;
			case EnemyID::VOID:
			default:
				// unexpected error
				g_logger->logError("LevelLoader", "Enemy was not loaded, unknown id.");
				return;
			}

			if (data.enemyQuesttarget.find(it.first) != data.enemyQuesttarget.end()) {
				enemy->setQuestTarget(data.enemyQuesttarget.at(it.first));
			}

			enemy->setLoot(loot, gold);
			enemy->setPosition(it.second.second);
			enemy->setObjectID(it.first);
			enemy->setDebugBoundingBox(sf::Color::Magenta);
			if (coreData.enemiesKilled.at(data.id).find(it.first) != coreData.enemiesKilled.at(data.id).end()) enemy->setDead();
			screen->addObject(enemy);
		}
	}
}

void LevelLoader::loadLights(LevelData& data, Screen* screen) const {
	// calculate lights
	for (auto& it : data.lights) {
		LightObject* lightObject = new LightObject(it);
		screen->addObject(lightObject);
	}
}
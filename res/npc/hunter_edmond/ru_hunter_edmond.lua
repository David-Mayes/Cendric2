-- Routine for NPC "Hunter Edmond"

velocity = 50

loadRoutine = function(R)
		if (R:isConditionFulfilled("default","tutorial_complete")) then 
			R:setTilePosition(57, 17)
			R:setTalkingActive(true)
			
			R:wait(3000)
			R:goToTile(57,17)
			R:goToTile(65,17)
			R:goToTile(65,14)
			R:goToTile(66,14)
			R:goToTile(66,12)
			R:goToTile(61,12)
			R:goToTile(61,13)
			R:goToTile(60,13)
			R:goToTile(60,17)
			
		elseif (R:isConditionFulfilled("level_entry","tutorial_started")) then 
		
			R:setTilePosition(44, 17)
			R:setTalkingEnabled(false)
			
			R:wait(1000)
			R:goToTile(46,18)
			R:setLooped(false)
			
		else
			R:setTalkingActive(true)
			R:setTilePosition(44, 17)
			
			R:wait(1000)
			R:goToTile(40,17)
			R:wait(1000)
			R:goToTile(44,17)
		end
    end
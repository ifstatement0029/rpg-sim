#pragma once

#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <time.h>
#include "commonfunctions.h"
#include <thread>

namespace fs = filesystem;

namespace cyberpunkSim {

	bool fullscreen = false;
	SDL_Window* window = NULL;
	//WHStruct windowResolution = { 3840, 2160 };
	//WHStruct windowResolution = { 2560, 1440 };
	WHStruct windowResolution = { 1920, 1080 };

	int FPSCap = 60; // 0 for uncapped
	bool vSyncOn = true;
	int refreshRate = -1, FPSTimerMod = -1;

	struct aspectRatioStruct {
		WHStruct ratio = { -1, -1 };
		int factor = -1;
	} aspectRatio = { { 16, 9 }, 25 };

	SDL_Renderer* renderer = NULL;

	SDL_Event event;
	struct deactivateEventStruct {
		Uint32 startTicks = 0, delay = 0;
	} deactivateEvent;

	int xDir = 0;
	int yDir = 0;
	int rightStickXDir = 0, rightStickYDir = 0;
	int leftStickDirection = 0, rightStickDirection = 0;

	int triggerDeadzone = 0;
	struct triggerStruct {
		bool activated = false;
		int axisVal = 0;
		Uint32 pressedStartTicks = 0, pressedDelay = 100;
	} leftTrigger, rightTrigger;

	SDL_Joystick* controller = NULL;
	int controllerID = -1;
	int deadZone = 8000;
	int joystickAxisMaxValue = 32767;
	int joystickAxisX = -1, joystickAxisY = -1, rightJoystickAxisX = -1, rightJoystickAxisY = -1;

	bool returnKeyPressed = false;
	bool cKeyPressed = false;

	struct controllerButtonsStruct {
		bool A = false, B = false, X = false, Y = false, LB = false, RB = false, select = false, start = false, LJ = false, RJ = false;
	} controllerButtons;

	struct controllerButtonStartTicksStruct {
		Uint32 A = 0, B = 0, X = 0, Y = 0, LB = 0, RB = 0, select = 0, start = 0, LJ = 0, RJ = 0;
	} controllerButtonStartTicks, controllerButtonPressedDuration;

	struct hatButtonsStruct {
		bool centered = false, up = false, right = false, rightUp = false, down = false, rightDown = false, left = false, leftUp = false, leftDown = false;
	} hatButtons;

	struct hatButtonsTicksStruct {
		Uint32 centered = 0, up = 0, right = 0, rightUp = 0, down = 0, rightDown = 0, left = 0, leftUp = 0, leftDown = 0;
	} hatButtonsPressedDuration, hatButtonsStartTicks;

	struct musicStruct {
		string name = "";
		Mix_Music* music = NULL;
	};
	vector<musicStruct> music;

	struct soundEffectStruct {
		string name = "";
		Mix_Chunk* soundEffect = NULL;
	};
	vector<soundEffectStruct> soundEffects;

	bool mute = true;

	SDL_Rect sRect = { -1, -1, -1, -1 }, dRect = { -1, -1, -1, -1 };

	struct spriteSheetStruct {
		string filePath = "";
		SDL_Surface* surface = NULL;
		SDL_Texture* texture = NULL;
	};
	vector<spriteSheetStruct> spriteSheets;

	struct tileStruct {
		int spriteSheetIndex = -1;
		string tileName = "";
		areaStruct spriteSheetArea = { -1, -1, -1, -1 };
	};
	vector<tileStruct> tiles;
	const WHStruct tileSize = { 8, 8 };

	bool exitMainLoop = false, displayMainMenu = false, inMainMenu = true;

	bool inMenu = false, characterMenuOn = false;

	bool loadLevel = false;

	struct gridTileStruct {
		int tileIndex = -1;
		bool collidable = false;
	};

	enum class regionTypeEnum { none, urban } regionType;

	struct regionGridStruct {
		vector<vector<regionTypeEnum>> tiles; //x, y
		vector<vector<string>> names; //x, y
		areaStruct camera = { -1, -1, -1, -1 }; //uses grid coordinates
		XYUnsignedIntStruct position = { 0, 0 };
	} regionGrid;

	bool changeOverworldRegionBool = false;

	struct gridStruct {
		vector<vector<vector<gridTileStruct>>> gridTile; //layer, x, y
		areaStruct camera = { -1, -1, -1, -1 }; //uses grid coordinates
		int groundLayerIndex = -1;
		startEndStruct heightStartEnd = { -3, 3 };
		int height = 0;
	} overworldGrid;

	bool currentlyInsideBuilding = false;
	XYStruct buildingDoorEntryRelativePosition = { -1, -1 };

	bool usedStairs = false;

	areaStruct originalCameraArea; //Uses pixel coordinates
	struct cameraStruct {
		areaStruct area = { -1, -1, -1, -1 };
		Uint32 moveStartTicks = SDL_GetTicks(), moveDelay = 0;
	} camera;
	WHStruct cameraLogicalSize;

	SDL_Texture* preRenderTexture = NULL;

	unsigned int playerSeed = 2;
	//int playerSeed = time(0); //randomize seed

	enum class targetTypeEnum { screen, texture };

	int controlledCharacterIndex = 0;

	struct renderOrderStruct {
		//enum class typeEnum { character, skillBasedInteractableObject } type;
		enum class typeEnum { character, object } type = typeEnum::character;
		int layerIndex = -1, index = -1;
		XYStruct position = { -1, -1 };
	};

	WHStruct textLogicalSize = { 1920, 1080 };

	struct fontDataStruct {
		string name = "";
		int size = -1;
		TTF_Font* font = NULL;
	};
	vector<fontDataStruct> fontData;
	TTF_Font* defaultFont = NULL;

	SDL_Color defaultColour = { 0, 0, 0 };

	struct iconStruct {
		int spriteSheetIndex = -1;
		areaStruct spriteSheetArea = { -1, -1, -1, -1 };
		string caption = "";
	};

	struct itemStruct {
		string name = "", description = "";
		iconStruct icon;
		int quantity = -1;
		float weight = -1;
	};

	vector<iconStruct> controllerButtonIcons;

	struct durationStruct {
		Uint32 startTicks = 0, delay = 0;
	};

	enum class headerStyleEnum { text, icon };

	struct headerMenuVarsStruct {
		string name = "";
		int scrollStart = -1, scrollEnd = -1, selected = 0, layer = -1;
		bool display = true;
	};
	vector<headerMenuVarsStruct> headerMenuVars;
	iconStruct selectedHeaderSprite;

	struct menuVarsStruct {
		string name = "";
		int scrollStart = -1, scrollEnd = -1, scrollCursor = 0, layer = -1;
		XYStruct gridCursor = { -1, -1 };
		enum class styleEnum { randomized, icons, list } style = menuVarsStruct::styleEnum::randomized;
		bool display = true;
		areaStruct backgroundArea = { -1, -1, -1, -1 };
	};
	vector<menuVarsStruct> menuVars;
	iconStruct selectedIconSprite;
	int selectedMenuLayer = -1, selectedMenu = 0;

	struct mainMenuStruct {
		string title = "";
		struct optionStruct {
			string name = "", value = "";
			enum class actionTypeEnum { none, continueGame, newGame, exitGame, setScreen, setAspectRatio, setResolution, setVSync, setFPSCap, exitMenu };
			vector<actionTypeEnum> actionTypes; //action type selecting this option does
			int mainMenuIndex = -1; //selecting this option sets currentMainMenuIndex to mainMenuIndex
		};
		vector<optionStruct> options;
		int backMainMenuIndex = -1;
	};
	vector<mainMenuStruct> mainMenus;
	int currentMainMenuIndex = 0, mainMenuSelectedOption = 0;

	iconStruct iconBackgroundSprite, menuBackgroundSprite, loadIconBack, loadIconFront, blankIcon;

	int UISpriteSheetIndex = -1, controllerButtonsSpriteSheetIndex = -1;

	enum class textBlockDisplayStyleEnum { vertical, horizontal };
	enum class textBlockAlignmentEnum { centered, left };

	bool quickslotSelectedItem = false, displayEquipMenu = false;

	int tracker = 0;

	struct barStruct {
		struct barIconStruct {
			iconStruct icon;
			areaStruct dRect = { -1, -1, -1, -1 };
			int totalIcons = -1;
		} backIcon, foreIcon;
	};

	struct skillStruct {
		string name = "", description = "";
		int current = 0, modified = 0, max = 0;
		iconStruct icon;
		barStruct bar; //for experience
		struct experienceStruct {
			unsigned int min = 0, max = 0;
		} experience;
	};

	struct createdObjectStruct {
		string name = "";
		areaStruct pixelArea = { -1, -1, -1, -1 }, gridArea = { -1, -1, -1, -1 };
	};
	vector< createdObjectStruct> createdObjects;
	int totalCreatedObjects = 0;

	struct rotationStruct {
		double angle = 0;
		SDL_Point centre = { -1, -1 };
		SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
	};

	struct animationStruct {
		string name = "";
		int spriteSheetIndex = -1, spriteIndex = 0;
		Uint32 startTicks = SDL_GetTicks(), delay = 100;
		vector<SDL_Rect> spritesSRect;
		XYStruct originalPosition = { -1, -1 };
		SDL_Rect spriteDRect = { -1, -1, -1, -1 };
		double startAngle = -1, endAngle = -1, currentAngle = -1;
		int pixelIncrement = 1, distance = 0;
		SDL_Point centre = { -1, -1 };
		SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
		string type = "";
		bool running = false;
		int currentLoops = 0, totalLoops = -1; //totalLoops: if == -1 then loop infinitely
	};

	struct cityGridUnitStruct {
		string name = "";
		vector<vector<gridTileStruct>> tiles; //x, y
	};

	vector<cityGridUnitStruct> cityGridUnits;

	struct cityGridStruct {
		vector<vector<vector<cityGridUnitStruct>>> units; //layer, x, y
		WHStruct gridSize = { -1, -1 }, unitTileSize = { -1, -1 }, spaceBetweenUnits = { -1, -1 };
	} cityGrid;

	struct miscItemsStruct {
		string name = "", description = "";
		int quantity = 0;
		iconStruct icon;
	};

	struct collisionStruct {
		bool collision = false;
		enum class regionCornerEnum { up, right, down, left } regionCorner = regionCornerEnum::up;
	};

	collisionStruct collisionData;

	struct menuControlsStruct {
		string buttonName = "", text = "";
	};

	enum class directionEnum { up, down, left, right, upRight, downRight, downLeft, upLeft };

	struct directionNamesStruct {
		bool up = false, down = false, left = false, right = false, upRight = false, downRight = false, downLeft = false, upLeft = false;
	};

	areaStruct overworldDoorEnteredThroughArea = { -1, -1, -1, -1 };
	int overworldBuildingEnteredThroughID = -1;

	//struct stairPositionsStruct {
	//	enum class typeEnum { none, up, down } type;
	//	XYStruct position;
	//};
	//vector<vector<stairPositionsStruct>> stairsPositions; //building floors, stair positions

	int activeMapIndex = -1;

	struct blueprintStruct {
		miscItemsStruct blueprint;
		vector<miscItemsStruct> requiredMiscItems;
	};

	timeStruct gameClock;
	int gameClockSpeedMultiplier = 10;

	struct closestObjectStruct {
		string objectType = "";
		XYStruct position = { -1, -1 };
		WHStruct size = { -1, -1 };
		int heuristic = -1;
		int ID = -1;
		bool reached = false;
	};

	struct findObjectDataStruct {
		int index = -1, heuristic = -1, ID = -1;
	};

	struct pathStruct {
		vector<XYStruct> pathToFollow;
		bool getPath = false, pathFound = false, walkPath = false, clearPath = true;
		int currentPathNode = 0;
		int walkSpeed = -1;
	} path;

	enum class repositionCharactersRelativeToEnum { object, character };

	struct scheduleStruct {
		struct taskStruct {
			timeStruct startTime, endTime;
			string name = "", goal = ""; //goal: Sleep, Eat
		};
		vector<taskStruct> tasks;
		int currentTask = 0;
	};

	//classes start

	struct characterConstructorVarsStruct {
		int ID = -1, layerIndex = 1;

		string name = "";

		XYStruct position = { -1, -1 };

		XYUnsignedIntStruct regionPosition = { 0, 0 };

		directionEnum direction = directionEnum::up;
		int spriteIndex = -1, spriteSheetIndex = -1;
		enum class spriteTypeEnum { single, combo } spriteType = spriteTypeEnum::single;

		WHStruct spriteTargetSize = { -1, -1 };

		vector<vector<areaStruct>> sprites; //direction, sprite turn

		struct statStruct {
			string name = "", description = "";
			int current = -1, modified = -1, max = -1;
			iconStruct icon;
			barStruct bar;
		};
		vector<statStruct> stats;

		struct miscStruct {
			string name = "", description = "", strValue = "";
			int intValue = -1;
			iconStruct icon;
		};
		vector<miscStruct> misc;

		struct spriteUpdateStruct {
			Uint32 startTicks = SDL_GetTicks(), delay = 100;
		} spriteUpdate;

		vector<skillStruct> skills;

		struct statusEffectStruct {
			int index = -1;
			string name = "", modType = "", modTargetType = "", modTargetName = ""; //modType: damage, boost; modTargetType: Skill, Stat
			int modValue = -1;
			durationStruct duration, applicationFrequency;
			iconStruct icon;
			barStruct bar; //for duration
			int sourceCharacterIndex = -1, sourceAbilityIndex = -1, numberOfTimesAdded = 0;
			struct cumulativeTypeStruct {
				bool createAdditionalEffect = false, addToExistingEffect = false, addToModValue = false, addToDuration = false;
				int numberOfTimesToAdd = -1, numberOfTimesAdded = 0; //if = -1 then will create additional effect or add to existing effect infinitely, if createAdditionalEffect or addToExistingEffect = true
			} cumulativeType;
			animationStruct animation;
		};
		vector<statusEffectStruct> statusEffects;

		struct abilityStruct {
			int index = -1;
			string name = "", description = "", targetType = ""; //targetType: self, enemy, object, companion, etc.
			int staminaConsumption = -1;
			string requiredAmmoName = ""; //if = "" then no ammo is required
			iconStruct icon;
			vector<characterConstructorVarsStruct::statusEffectStruct> statusEffects;
			struct sourceStruct {
				string name = "";
				int index = -1;
			} source;
			vector<animationStruct> animations;
		};
		vector<characterConstructorVarsStruct::abilityStruct> abilities;

		struct ammoStruct {
			iconStruct icon;
			string name = "";
			int quantity = -1;
		};
		vector<ammoStruct> ammos;

		struct cyberwareStruct {
			int index = -1;
			string name = "", description = "";
			int energyConsumptionPerSecond = -1, quantity = -1;
			iconStruct icon;
			vector<characterConstructorVarsStruct::abilityStruct> abilities;
		};
		vector<cyberwareStruct> cyberwares;

		struct gearStruct {
			int index = -1;
			string name = "", description = "";
			int quantity = -1;
			iconStruct icon;

			struct skillStruct {
				string name = "";
				int modValue = -1;
				iconStruct icon;
			};
			vector<skillStruct> skills;
		};
		vector<gearStruct> gears;

		struct weaponStruct {
			int index = -1;
			XYStruct position = { -1, -1 };
			string name = "", description = "";
			string rangeType = ""; //Melee, Ranged
			int quantity = -1;
			iconStruct icon;
			WHStruct weaponSize = { -1, -1 };
			vector<characterConstructorVarsStruct::abilityStruct> abilities;
			rotationStruct rotation;
			bool renderWhenAnimationRunning = false;
		};
		vector<weaponStruct> weapons;

		struct consumableItemStruct {
			int index = -1;
			string name = "", description = "";
			int quantity = -1;
			iconStruct icon;
			vector<characterConstructorVarsStruct::statusEffectStruct> statusEffects;
		};
		vector< consumableItemStruct> consumableItems;

		vector<miscItemsStruct> miscItems;

		vector<blueprintStruct> blueprints;

		vector<miscItemsStruct> craftingItems;

		struct quickslotsStruct {
			string slottedItemType = "", controllerButtonName = "";
			int slottedItemIndex = -1;
			iconStruct icon;
		};
		vector<quickslotsStruct> quickslots;

		struct equipmentSlotStruct {
			string name = "";
			int equipmentIndex = -1;
		};
		vector<equipmentSlotStruct> cyberwareEquipmentSlots, gearEquipmentSlots, weaponEquipmentSlots;

		struct bodyPartStruct {
			string type = "";
			SDL_Rect bodyPartSRect = { -1, -1, -1, -1 };
		};
		vector<vector<vector<vector<bodyPartStruct>>>> bodyParts; //direction, sprite turn, x, y

		struct sleepStruct {
			bool state = false;
			Uint32 startTicks = -1, delay = -1; //delay = -1 (indefinitly)
			int spriteSheetIndex = -1;
			SDL_Rect spriteSRect = { -1, -1, -1, -1 };
		} sleep;
	};

	struct characterConstructorScheduleVarsStruct {
		vector<scheduleStruct> schedules;
		int currentSchedule = 0;
	};

	class Character {
	public:
		vector<skillStruct> skills;

		vector<miscItemsStruct> miscItems;

		bool disableControls = false;

		vector<miscItemsStruct> craftingItems;

		struct sleepStateStruct {
			bool state = false;
			Uint32 startTicks = -1;
		};

		struct organisationStruct {
			int ID = -1, roleID = -1;
			Uint32 checkFrequencyStartTicks = SDL_GetTicks(), checkFrequencyDelay = 30000;
		};

		Character(characterConstructorVarsStruct characterConstructorVars, characterConstructorScheduleVarsStruct characterConstructorScheduleVars);

		int getID();
		int getLayerIndex();
		XYStruct getPosition();
		void setPosition(XYStruct position);
		directionEnum getDirection();
		WHStruct getSpriteTargetSize();
		vector<characterConstructorVarsStruct::statStruct> getStats();
		void setStats(vector<characterConstructorVarsStruct::statStruct> characterStats);
		vector<characterConstructorVarsStruct::abilityStruct> getAbilities();
		vector<characterConstructorVarsStruct::ammoStruct> getAmmos();
		vector<characterConstructorVarsStruct::quickslotsStruct> getQuickslots();
		vector<blueprintStruct> getBlueprints();
		vector<characterConstructorVarsStruct::cyberwareStruct> getCyberwares();
		vector<characterConstructorVarsStruct::gearStruct> getGear();
		vector<characterConstructorVarsStruct::weaponStruct> getWeapons();
		vector<characterConstructorVarsStruct::consumableItemStruct> getConsumableItems();
		string getName();
		//int getObjectReachedID();
		void setOrganisation(Character::organisationStruct organisation);

		void renderEquippedWeapon();
		void renderAbilityAnimations();
		void render();
		void renderStatusEffects();
		int getQuickslotIndex(string name);
		void move();
		void activateMenu();
		void attack();
		void animateAbilities();
		void checkTargetHitByAttack();
		void runStatusEffects();
		void removeStatusEffects();
		void animateStatusEffects();
		void stopAbilityAnimations();
		void checkObjectProximity();
		void displayCharacterMenu();
		void removeMiscItems(vector<miscItemsStruct> miscItemsToRemove);
		void addMiscItem(miscItemsStruct currentMiscItem);
		void addCraftingItems(miscItemsStruct currentCraftingItem);
		void addCyberware(characterConstructorVarsStruct::cyberwareStruct currentCyberware);
		void addGear(characterConstructorVarsStruct::gearStruct currentGear);
		void addWeapon(characterConstructorVarsStruct::weaponStruct currentWeapon);
		void addConsumable(characterConstructorVarsStruct::consumableItemStruct currentConsumableItem);
		void addAmmo(characterConstructorVarsStruct::ammoStruct currentAmmo);
		void removeCraftingItem(miscItemsStruct currentCraftingItem);
		void addBlueprint(blueprintStruct currentBlueprint);
		void setGoal();
		void carryOutGoal();
		void setCharacterSleepState(sleepStateStruct currentSleepState);
		void followPath();
		void runSleepAnimation();
		int getMoveSpeedPixelIncrement();
		void getScheduleFromOrganisation();

	private:
		int ID = -1, layerIndex = -1;
		string name = "";

		XYStruct position;

		XYUnsignedIntStruct regionPosition;

		directionEnum direction = directionEnum::up;

		WHStruct spriteTargetSize;

		bool displayMenuOn = false, blockCursorMovement = false, blockSlottedElementsUse = false;

		vector<int> indicesOfStatusEffectsToRemove;

		vector<vector<vector<vector<characterConstructorVarsStruct::bodyPartStruct>>>> bodyParts; //direction, sprite turn, x, y

		struct moveSpeedStruct {
			Uint32 startTicks = SDL_GetTicks(), delay = 1;
			int pixelIncrement = 1;
		} moveSpeed;

		int spriteIndex = -1, spriteSheetIndex = -1;
		characterConstructorVarsStruct::spriteTypeEnum spriteType;

		vector<vector<areaStruct>> sprites; //direction, sprite turn

		characterConstructorVarsStruct::spriteUpdateStruct spriteUpdate;

		vector<characterConstructorVarsStruct::miscStruct> misc;

		vector<characterConstructorVarsStruct::statStruct> stats;

		vector<characterConstructorVarsStruct::abilityStruct> abilities;

		vector<characterConstructorVarsStruct::statusEffectStruct> statusEffects;

		vector<characterConstructorVarsStruct::cyberwareStruct> cyberwares;

		vector<characterConstructorVarsStruct::gearStruct> gears;

		vector<characterConstructorVarsStruct::weaponStruct> weapons;

		vector<characterConstructorVarsStruct::consumableItemStruct> consumableItems;

		vector<characterConstructorVarsStruct::ammoStruct> ammos;

		vector<characterConstructorVarsStruct::quickslotsStruct> quickslots;

		vector<characterConstructorVarsStruct::equipmentSlotStruct> cyberwareEquipmentSlots, gearEquipmentSlots, weaponEquipmentSlots;

		vector<blueprintStruct> blueprints;

		characterConstructorScheduleVarsStruct privateCharacterConstructorScheduleVars;

		string goal = "";

		struct conditionStruct {
			string condition = "";
			bool passed = false;
		};
		vector<conditionStruct> conditions;

		/*struct goalStruct {
			string goal = "";

			enum class conditionTypeEnum { isAwake, findObject, isAtObject };
			enum class argumentTypeEnum { sleepState, object, pathToFollow, objectReachedID };
			enum class actionTypeEnum { checkIsAwake, getClosestObject, --;; };
			enum class runTypeEnum { repeat, once };

			struct conditionStruct {
				conditionTypeEnum conditionType;
				vector<argumentTypeEnum> arguments;
				vector<actionTypeEnum> actions;
				runTypeEnum runType;
			};
			vector<conditionStruct> conditions;
			int currentCondition = -1;
		};
		vector<goalStruct> goals;
		int currentGoal = -1;*/

		characterConstructorVarsStruct::sleepStruct sleep;

		closestObjectStruct closestObject;

		pathStruct path;

		//Determines what organisation the character works for and what role they have within it - used for setting of character's schedule
		organisationStruct organisation;

		void updateSpriteIndex();
		collisionStruct characterCheckCollision();
		vector<int> getQuickslotButtonsPressedIndices();
		//enum class objectInteractionTypeEnum { skillBasedInteractableObject };
		//void checkObjectInteraction(objectInteractionTypeEnum objectInteractionType);
		int getStatIndex(string statName);
		void createAdditionalStatusEffect(characterConstructorVarsStruct::abilityStruct& ability, int statusEffectsCnt, int characterHitCnt);
		int getSkillCntByName(string name);
		int getStatCntByName(string name);
		int getStatusEffectCntByIndex(int index);
		void wakeUp();
		bool compareSchedules(scheduleStruct scheduleA, scheduleStruct scheduleB);
	};

	vector<Character> characters;

	struct buildingConstructorVarsStruct {
		int ID = -1, buildingDoorID = -1, minFloors = -1, maxFloors = -1;
		areaStruct area = { -1, -1, -1, -1 };
	};

	class Building {
	public:
		Building(buildingConstructorVarsStruct buildingConstructorVars);

		int getID();
		int getBuildingDoorID();
		areaStruct getArea();

	private:
		int ID = -1, buildingDoorID = -1;

		int minFloors = -1, maxFloors = -1;

		areaStruct area = { -1, -1, -1, -1 };
	};

	vector<Building> buildings;

	struct organisationConstructorVarsStruct {
		int ID = -1;
		string name = "";
		string type = ""; //Gang/Company/Religion/
		string goal = ""; //

		struct rolePositionStruct {
			int ID = -1;
			string name = "", goal = "";
			int characterID = -1;
			iconStruct icon;
			scheduleStruct schedule;
		};
		vector<vector<rolePositionStruct>> hierarchyTable;

		struct relationshipStruct {
			struct fromToStruct {
				int roleIDFrom = -1, roleIDTo = -1;
				string relationshipType = "";
			};
			fromToStruct direction[2];
		};
		vector<relationshipStruct> relationships;
	};

	class Organisation {
	public:
		Organisation(organisationConstructorVarsStruct functionOrganisationConstructorVarsStruct);
		~Organisation();

		int getID();
		void setDisplayHierarchyBool(bool currentDisplayHierarchyBool);
		vector<int> getRoleIDs();
		vector<organisationConstructorVarsStruct::rolePositionStruct> getRoles();

		void displayHierarchy();

	private:
		organisationConstructorVarsStruct privateOrganisationConstructorVars;

		SDL_Texture* hierarchyTexture = NULL;

		bool displayHierarchyBool = false;
	};

	vector<Organisation> organisations;

	struct objectConstructorVarsStruct {
		int ID = -1, layer = -1;
		string type = "";

		bool collision = true;

		SDL_Rect objectDRect = { -1, -1, -1, -1 };

		int currentStateAnimation = 0;
		vector<animationStruct> stateAnimations;

		struct inputDeviceStruct {
			string name = "";
			bool inputCode = false;
			string codeEntered = "";
			vector<vector<iconStruct>> grid;
			XYStruct gridCursor = { 0, 0 };
			SDL_Rect inputDevicedDRect = { -1, -1, -1, -1 };
		};
		vector<inputDeviceStruct> inputDevices;

		struct optionStruct {
			iconStruct icon; //icon caption used for option title

			int requiredStateAnimation = -1;

			vector<skillStruct> requiredSkills, characterMatchingSkills;
			vector<miscItemsStruct> requiredMiscItems, characterMatchingMiscItems;
			bool removeMiscItems = false;

			struct inputDeviceRequirementsStruct {
				string name = "", code = "";
				bool codeFound = false, codeEntered = false;
			};
			vector<inputDeviceRequirementsStruct> inputDeviceRequirements;

			int newCurrentStateAnimation = 0;

			struct optionChangeStruct {
				bool newOption = false;
				iconStruct newIcon;
				int optionToChangeIndex = -1; //identify option to change by index
				string optionToChangeIconCaption = ""; //identify option to change by icon caption
				string newCaption = ""; //used for icon caption
				int newRequiredStateAnimation = -1;
				vector<skillStruct> newRequiredSkills;
				vector<miscItemsStruct> newRequiredMiscItems;
				bool newLoadInsideBuilding = false;
			};
			vector<optionChangeStruct> optionChanges;

			bool newCollision = false;

			bool loadInsideBuilding = false, loadOverworld = false, goUpStairs = false, goDownStairs = false, canSleep = false;

			string craftingType = "";

			int organisationID = -1; //for displaying organisation hierarchy
		};
		vector<optionStruct> options;
	};

	struct craftingItemDataStruct {
		struct requiredItemsStruct {
			string name = "";
			int quantityRequired = -1;
		};
		vector<craftingItemDataStruct::requiredItemsStruct> requiredItems;

		struct resultingItemStruct {
			string type = ""; //{ "Misc", "Crafting", "Cyberware", "Gear", "Weapon", "Consumable", "Ammo" }
			miscItemsStruct miscItem;
			miscItemsStruct craftingItem;
			characterConstructorVarsStruct::cyberwareStruct cyberware;
			characterConstructorVarsStruct::gearStruct gear;
			characterConstructorVarsStruct::weaponStruct weapon;
			characterConstructorVarsStruct::consumableItemStruct consumableItem;
			characterConstructorVarsStruct::ammoStruct ammo;
		} resultingItem;

		bool blueprintFound = false;
		blueprintStruct blueprint;
	};
	vector<craftingItemDataStruct> craftingTable;
	craftingItemDataStruct::resultingItemStruct craftingTableCraftedItem;

	class Object {
	public:
		bool displayOptions = false, displayCraftingMenu = false;

		vector<objectConstructorVarsStruct::inputDeviceStruct> inputDevices;

		Object(objectConstructorVarsStruct objectConstructorVars);

		int getID();
		int getLayer();
		void setCharacterID(int objectCharacterID);
		string getType();
		SDL_Rect getObjectDRect();
		void setDisplayInputDeviceSelectionMenu(bool objectDisplayInputDeviceSelectionMenu);
		vector<objectConstructorVarsStruct::inputDeviceStruct> getInputDevices();
		vector<objectConstructorVarsStruct::optionStruct> getOptions();
		int getOptionOrganisationID();
		void setPosition(XYStruct position);
		void setCollisionSet(bool newCollisionSet);

		void setObjectCollision();
		void render();
		void animate();
		void interact();
		void displayOptionsMenu();
		void inputDeviceSelectionMenu();
		void inputDeviceMenu();
		void craftingMenu(vector<craftingItemDataStruct>& craftingTable, Character& teamCharacter, craftingItemDataStruct::resultingItemStruct& craftingTableCraftedItem);
		void setOrganisationDisplayHierarchyBoolToTrue(vector<Organisation>& organisations);
		void updateCharacterSleepState(Character& character);

	private:
		int ID = -1, layer = -1, characterID = -1;
		string type = "";

		int buildingID = -1;

		bool collision = true, collisionSet = false;

		int currentStateAnimation = 0;
		vector<animationStruct> stateAnimations; //a static sprite can be an animation with only index 0 containing data

		SDL_Rect objectDRect = { -1, -1, -1, -1 };

		bool displayInputDeviceSelectionMenu = false;
		int selectedInputDevice = -1;

		int currentOption = 0, currentOptionChange = 0;
		vector<objectConstructorVarsStruct::optionStruct> options;

		struct selectedCraftingItemsStruct {
			int index = -1, quantity = -1;
		};
		vector<selectedCraftingItemsStruct> craftingItemsSelected;
		enum class selectedCraftingMenuSectionEnum { craftingItems, selectedCraftingItems } selectedCraftingMenuSection = Object::selectedCraftingMenuSectionEnum::craftingItems;

		struct selectQuantityMenuStruct {
			XYStruct textPosition = { -1, -1 };
			bool display = false;
			string caption = "";
			int selected = -1, min = -1, max = -1;
			Uint32 scrollDelay = 150;
			bool blockCursorMovement = false, centreText = false, showControlCaptions = true;
		} selectQuantityMenu;

		bool objectOptionsInitialized = false; //for testing
		bool craftingItemsSelectedInitialized = false; //for testing

		int matchingCraftingTableLineIndex = -1;

		int optionOrganisationID = -1;
		bool setOrganisationDisplayHierarchyBoolToTrueBool = false;

		bool updateCharacterSleepStateBool = false;

		int getInputDeviceIndex(string inputDeviceName);
		int getInputDeviceRequirementIndex(string inputDeviceName);
		void checkCorrectCodeEntered(int inputDeviceRequirementIndex);
		void initObjectOptions(); //for testing
		void initCraftingItemsSelected(vector<craftingItemDataStruct>& craftingTable, vector<miscItemsStruct>& characterCraftingItems); //for testing
	};

	vector<Object> objects;

	struct mapConstructorVarsStruct {
		int ID = -1;
		string name = "";
		SDL_Texture* texture = NULL;
		SDL_Rect textureSRect = { -1, -1, -1, -1 }, textureDRect = { -1, -1, -1, -1 };
		bool sRectRelativeToControllerCharacter = false, alwaysDisplayMap = false;
		WHStruct gridScaleSize = { -1, -1 };
	};

	class Map {
	public:
		SDL_Texture* texture = NULL;

		bool display = false;

		Map(mapConstructorVarsStruct constructorVars);

		int getID();
		string getName();
		bool getAlwaysDisplayMap();

		void render();

	private:
		int ID = -1;
		string name = "";

		SDL_Rect textureSRect = { -1, -1, -1, -1 }, textureDRect = { -1, -1, -1, -1 };
		int textureTransparency = 75;

		WHStruct gridScaleSize;

		bool alwaysDisplayMap = false, sRectRelativeToControllerCharacter = false;
	};

	vector<Map> maps;

	//classes end

}

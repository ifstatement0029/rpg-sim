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

namespace game {

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
		string filePathAndName = "";
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
		int tileIndex = -1, height = 0, resistance = -1, stuckTolerancePercentage = 10;
		bool collidable = false, jumpable = false;
	};

	enum class regionTypeEnum { none, urban } regionType;

	struct regionGridStruct {
		vector<vector<regionTypeEnum>> tiles; //x, y
		vector<vector<string>> names; //x, y
		areaStruct camera = { -1, -1, -1, -1 }; //uses grid coordinates
		XYUnsignedIntStruct position = { 0, 0 };
	} regionGrid;

	struct gridStruct {
		vector<vector<vector<gridTileStruct>>> gridTile; //layer, x, y
		areaStruct camera = { -1, -1, -1, -1 }; //uses grid coordinates
		int groundLayerIndex = -1;
		startEndStruct heightStartEnd = { -3, 3 };
		int height = 0;
	} overworldGrid;

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
		enum class typeEnum { character, table, bullet, explosion } type = typeEnum::character;
		int layerIndex = -1, index = -1, height = 0;
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

	vector<iconStruct> controllerButtonIcons;

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

	struct collisionDataStruct {
		bool collision = false;
		XYStruct collidePosition = { -1, -1 };
		enum class tileHitCornerEnum { none, up, right, down, left } hitCorner = tileHitCornerEnum::none;
		int instanceID = -1;
	};

	struct menuControlsStruct {
		string buttonName = "", text = "";
	};

	enum class directionEnum { up, down, left, right, upRight, downRight, downLeft, upLeft };

	struct directionNamesStruct {
		bool up = false, down = false, left = false, right = false, upRight = false, downRight = false, downLeft = false, upLeft = false;
	};

	timeStruct gameClock;
	int gameClockSpeedMultiplier = 10;

	struct pathStruct {
		vector<XYStruct> pathToFollow;
		bool getPath = false, pathFound = false, walkPath = false, clearPath = true;
		int currentPathNode = 0;
		int walkSpeed = -1;
	} path;

	struct spriteStruct {
		int spriteSheetIndex = -1;
		vector<vector<areaStruct>> areas; //directions (up, down, left, right, upRight, downRight, downLeft, upLeft), frames
		double angle = 0;
		SDL_Point center = { -1, -1 };
		SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
	};

	struct shadowSpriteStruct {
		int spriteSheetIndex = -1;
		SDL_Rect sRect = { -1, -1, -1, -1 };
	} shadowSprite;

	struct collidableObjectStruct {
		areaStruct area = { -1, -1, -1, -1 };
		int height = -1;
	};
	vector<collidableObjectStruct> collidableObjects;

	struct colourStruct {
		Uint8 r = 0, g = 0, b = 0, a = 0;
	};

	int maxStuckBullets = 2;
	//vector<int> stuckBulletIDs;
	vector<int> bulletsToDestroyIDs;

	vector<int> charactersToDestroyIDs;

	vector<int> tablesToDestroyIDs;

	int maxExplosions = 2;
	vector<int> explosionsToDestroyIDs;

	//classes start

	struct characterParams {
		int ID = -1;

		XYStruct position = { -1, -1 }, groundPosition = { -1, -1 };
		WHStruct size = { -1, -1 };
		int layer = 0, shadowHeight = 0;
		
		bool displaySprites = true;
		spriteStruct sprites;

		directionEnum direction = directionEnum::down;
		int frame = 0;

		struct moveStruct {
			int pixelIncrement = 2;
			delayStruct speed = { SDL_GetTicks(), 1 }, frameSwap = { SDL_GetTicks(), 100 };
		} move;

		struct idleAnimationStruct {
			delayStruct delayBeforeAnimation = { SDL_GetTicks(), 60000 }, frameDuration = { 0, 0 };
			bool animationRunning = false;
		} idleAnimation;

		struct jumpStruct {
			bool jumping = false, onObject = false, onTileObject = false;
			int currentHeight = 0, maxHeight = -1, addedMaxHeight = 0, pixelIncrement = 2;
			delayStruct move = { 0, 1 }, jumpButtonPress = { 0, 100 };
			directionEnum direction = directionEnum::up;
		} jump;

		enum class equippedWeaponTypeEnum { ranged, melee } equippedWeaponType = characterParams::equippedWeaponTypeEnum::melee;

		struct rangedWeaponStruct {
			string name = "";

			XYStruct position = { -1, -1 };
			WHStruct size = { -1, -1 };

			spriteStruct sprite;

			enum class fireModeEnum { semiAuto, burst, fullAuto } fireMode = characterParams::rangedWeaponStruct::fireModeEnum::semiAuto;

			struct burstStruct {
				bool pause = false;
				int bulletsFired = 0, maxBulletsBeforePause = -1;
				delayStruct delay;
			} burst;

			struct magazineStruct {
				string ammoName = "";
				int capacity = -1, currentLoad = -1;
			} magazine;

			struct reloadStruct {
				bool reloading = false;
				delayStruct delay;
				spriteStruct sprite;
			} reload;
		} equippedRangedWeapon;

		struct meleeWeaponStruct {
			string name = "";

			XYStruct position = { -1, -1 };
			WHStruct size = { -1, -1 };

			spriteStruct sprite;

			struct swingStruct {
				bool swinging = false;
				double originalAngle = -1;
				int angle = 180, currentAngle = -1, startAngle = -1, endAngle = -1, pixelIncrement = 12;
				delayStruct delay;
			} swing;
		} equippedMeleeWeapon;

		int resistance = -1, stuckTolerancePercentage = 10;

		bool destroy = false;

		vector<int> bulletsFiredIDs;
	};

	class Character {
	public:
		Character(characterParams newParams);
		
		int getLayer();
		XYStruct getPosition();
		WHStruct getSize();
		int getCurrentHeight();
		directionEnum getDirection();
		int getFrame();
		characterParams::rangedWeaponStruct::magazineStruct getMagazine();
		string getEquippedWeaponName();
		int getID();
		int getResistance();
		void setResistance(int newResistance);
		int getStuckTolerancePercentage();
		int getCharacterSpriteSheetIndex();
		areaStruct getSpriteSheetArea(directionEnum direction, int frame);
		bool getDisplaySprites();
		void setDisplaySprites(bool newDisplaySprites);
		void setDestroy(bool newDestroy);
		vector<int> getBulletsFiredIDs();
		
		void render();
		void updateEquippedWeaponAngle();
		void renderEquippedWeapon();
		void renderReloadAnimation();
		void move();
		void idleAnimation();
		void jump();
		void jumpOnCollidableObject();
		void jumpOnTile();
		void useEquippedWeapon();
		void markForDestruction();

	private:
		characterParams params;

		void swapFrame();
	};

	vector<Character> characters;

	struct tableParamsStruct {
		int ID = -1, layer = 0;

		XYStruct position = { -1, -1 };
		WHStruct size = { -1, -1 };
		int height = -1;

		/*int spriteSheetIndex = -1;
		SDL_Rect spriteSRect = { -1, -1, -1, -1 };*/
		spriteStruct sprite;
		bool displaySprite = true;

		int resistance = -1, stuckTolerancePercentage = 10;

		bool destroy = false;
	};

	class Table {
	public:
		Table(tableParamsStruct newParams);

		int getLayer();
		XYStruct getPosition();
		WHStruct getSize();
		int getID();
		int getHeight();
		int getResistance();
		void setResistance(int newResistance);
		int getStuckTolerancePercentage();
		int getTableSpriteSheetIndex();
		areaStruct getSpriteSheetArea();
		void setDisplaySprites(bool newDisplaySprite);
		void setDestroy(bool newDestroy);

		void markForDestruction();

		void render();
	
	private:
		tableParamsStruct params;
	};

	vector<Table> tables;

	struct bulletParamsStruct {
		int ID = -1, layer = -1, height = 0;

		XYStruct position = { -1, -1 }, originalPosition = { -1, -1 }, previousPosition = { -1, -1 }, directionMods = { 1, 1 };
		WHStruct size = { -1, -1 };

		bool displaySprite = true;
		spriteStruct sprite;

		delayStruct speed;
		int movePixelIncrement = 1;
		
		int distanceTravelled = 0, totalDistanceTravelled = 0;

		int damage = -1, resistance = -1, stuckTolerancePercentage = 10;

		bool stuck = false, destroy = false;

		int characterID = -1;

		delayStruct fadeOut;
	};

	class Bullet {
	public:
		Bullet(bulletParamsStruct newParams);

		int getID();
		int getLayer();
		XYStruct getPosition();
		WHStruct getSize();
		int getResistance();
		void setResistance(int newResistance);
		int getStuckTolerancePercentage();
		int getBulletSpriteSheetIndex();
		areaStruct getSpriteSheetArea();
		void setDisplaySprite(bool newDisplaySprite);
		void setDestroy(bool newDestroy);
		int getCharacterID();
		delayStruct getFadeOut();
		void setFadeOut(delayStruct newFadeOut);
		bool getStuck();

		void render();
		void move();
		void markForDestruction();
		void ricochet(collisionDataStruct& collisionData);
		void ricochetPenetrateOrStayStuck();
		void explode();

	private:
		bulletParamsStruct params;
	};

	vector<Bullet> bullets;

	struct explosionParamsStruct {
		int ID = -1, overworldGridLayer = -1;

		spriteStruct sprite;

		collisionDataStruct collisionData;

		int force = -1;

		XYStruct totalFragments = { -1, -1 };
		struct fragmentStruct {
			XYStruct position = { -1, -1 }, originalPosition = { -1, -1 };
			WHStruct size = { -1, -1 };

			int distanceTravelled = 0, maxDistance = -1;

			spriteStruct sprite;
			
			delayStruct speed;
			int pixelIncrement = -1;
		};
		vector<fragmentStruct> fragments;

		delayStruct fadeOut;
	};

	class Explosion {
	public:
		Explosion(explosionParamsStruct newParams);

		int getID();
		int getOverworldGridLayer();
		XYStruct getFragmentPosition(int fragmentIndex);
		int getTotalFragments();
		vector<explosionParamsStruct::fragmentStruct> getFragments();
		delayStruct getFadeOut();
		void setFadeOut(delayStruct newFadeOut);

		void createFragments();
		void render();
		void explode();
		void markForDestruction();

	private:
		explosionParamsStruct params;
	};

	vector<Explosion> explosions;

	//classes end

}

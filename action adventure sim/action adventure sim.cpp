#include "variables.h"

using namespace cyberpunkSim;

//functions start

void setSDLRenderTarget(SDL_Texture* targetTexture) {
	if (SDL_GetRenderTarget(renderer) != targetTexture) {
		SDL_SetRenderTarget(renderer, targetTexture);
	}
}

void setSDLLogicalSize(WHStruct targetSize) {
	WHStruct currentLogicalSize = { -1, -1 };
	SDL_RenderGetLogicalSize(renderer, &currentLogicalSize.w, &currentLogicalSize.h);
	if (currentLogicalSize.w != targetSize.w || currentLogicalSize.h != targetSize.h) {
		SDL_RenderSetLogicalSize(renderer, targetSize.w, targetSize.h);
	}
}

WHStruct getSDLTextureSize(SDL_Texture* texture) {
	WHStruct textureSize = { -1, -1 };
	if (texture != NULL) {
		SDL_QueryTexture(texture, NULL, NULL, &textureSize.w, &textureSize.h);
	}
	return textureSize;
}

//DO NOT USE. Does not work. Seems texture that is passed to function is not affected
void initSDLTexture(SDL_Texture* texture, WHStruct size) {
	WHStruct textureSize = getSDLTextureSize(texture);
	if (texture == NULL || textureSize.w == -1) {
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.w, size.h);
	}
}

//DO NOT USE. Does not work. Seems texture that is passed to function is not affected
void destroySDLTexture(SDL_Texture* texture) {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

void setSDLTextureTransparency(SDL_Texture* texture, int transparencyPercentage) {
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texture, (255 * transparencyPercentage) / 100);
}

void removeSDLTextureTransparency(SDL_Texture* texture) {
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
}

//int roundDiv(int firstNumber, int secondNumber) {
//	return lround((float)firstNumber / secondNumber);
//}
//
//int roundInt(int number) {
//	return lround(number);
//}
//
//float roundDec(float number, int decimalPoint) {
//	float value = (int)(number * (10 * decimalPoint) + .5);
//	return (float)value / (10 * decimalPoint);
//}
//
//struct decimalNumPartsStruct {
//	double fractpart, intpart;
//};
//
//decimalNumPartsStruct getDecimalNumParts(double param) {
//	decimalNumPartsStruct currentDecimalNumParts;
//	currentDecimalNumParts.fractpart = modf(param, &currentDecimalNumParts.intpart);
//	return currentDecimalNumParts;
//}
//
//int roundDivUp(double param) {
//	decimalNumPartsStruct decimalNumParts = getDecimalNumParts(param);
//	if (decimalNumParts.fractpart != 0) {
//		++decimalNumParts.intpart;
//	}
//	return decimalNumParts.intpart;
//}
//
//string str(int value) {
//	return to_string(value);
//}
//
//string strRoundDec(float number, int decimalPoint) {
//	return to_string(roundDec(number, decimalPoint));
//}
//
//int randInt(int startInt, int endInt) {
//	return startInt + rand() % (endInt - startInt + 1);
//}
//
//string randStringList(vector<string> list) {
//	return list[rand() % (int)list.size()];
//}
//
//void printRand() {
//	printf("%d\n", rand() % 10);
//}
//
//void printInt(int value) {
//	printf("%d, %d\n", rand() % 10, value);
//}
//
//void printIntL(vector<int> values) {
//	string str = to_string(rand() % 10) + ", " + to_string(values[0]);
//	if ((int)values.size() > 1) {
//		for (int valuesCnt = 1; valuesCnt < (int)values.size(); ++valuesCnt) {
//			str += ", " + to_string(values[valuesCnt]);
//		}
//	}
//	printf("%s\n", str.c_str());
//}
//
//void printFloat(float value) {
//	printf("%d, %f\n", rand() % 10, value);
//}
//
//void printFloatL(vector<float> values) {
//	string str = to_string(rand() % 10) + ", " + to_string(values[0]);
//	if ((int)values.size() > 1) {
//		for (int valuesCnt = 1; valuesCnt < (int)values.size(); ++valuesCnt) {
//			str += ", " + to_string(values[valuesCnt]);
//		}
//	}
//	printf("%s\n", str.c_str());
//}
//
//void printStr(string value) {
//	printf("%d, %s\n", rand() % 10, value.c_str());
//}
//
//void printStrL(vector<string> values) {
//	string str = to_string(rand() % 10);
//	str += ", " + values[0];
//	if ((int)values.size() > 1) {
//		for (int valuesCnt = 1; valuesCnt < (int)values.size(); ++valuesCnt) {
//			str += ", " + values[valuesCnt];
//		}
//	}
//	printf("%s\n", str.c_str());
//}
//
//int getFreeID(vector<int> indices) {
//
//	//Get index number not already used in indices list
//	int index = 0;
//	if ((int)indices.size() > 0) {
//		while (true) {
//			int indicesCnt;
//			for (indicesCnt = 0; indicesCnt < (int)indices.size(); ++indicesCnt) {
//				if (indices[indicesCnt] == index) {
//					break;
//				}
//			}
//			if (indices[indicesCnt] == index) {
//				++index;
//			}
//			else {
//				return index;
//			}
//		}
//	}
//
//	return index;
//}

areaStruct randArea(vector<areaStruct> areas) {
	return areas[randInt(0, (int)areas.size() - 1)];
}

SDL_Rect randSDLRect(vector<SDL_Rect> rects) {
	return rects[randInt(0, (int)rects.size() - 1)];
}

XYStruct convertPosition(XYStruct sourcePosition, WHStruct sourceLogicalSize, WHStruct destinationLogicalSize) {
	/*float logicalSizeFactorX = (float)destinationLogicalSize.w / sourceLogicalSize.w;
	float logicalSizeFactorY = (float)destinationLogicalSize.h / sourceLogicalSize.h;
	XYStruct destinationPosition = { sourcePosition.x * static_cast<int>(logicalSizeFactorX), sourcePosition.y * static_cast<int>(logicalSizeFactorY) };
	return destinationPosition;*/
	return { lround((float)(sourcePosition.x * destinationLogicalSize.w) / sourceLogicalSize.w), lround((float)(sourcePosition.y * destinationLogicalSize.h) / sourceLogicalSize.h) };
}

WHStruct convertSize(WHStruct sourceSize, WHStruct sourceLogicalSize, WHStruct destinationLogicalSize) {
	/*float logicalSizeFactorX = (float)destinationLogicalSize.w / sourceLogicalSize.w;
	float logicalSizeFactorY = (float)destinationLogicalSize.h / sourceLogicalSize.h;
	WHStruct destinationSize = { sourceSize.w * static_cast<int>(logicalSizeFactorX), sourceSize.h * static_cast<int>(logicalSizeFactorY) };
	return destinationSize;*/
	return { lround((float)(sourceSize.w * destinationLogicalSize.w) / sourceLogicalSize.w), lround((float)(sourceSize.h * destinationLogicalSize.h) / sourceLogicalSize.h) };
}

void renderText(/*WHStruct logicalSize, */string text, TTF_Font* textFont, SDL_Color colour, XYStruct position) {
	if (text != "") {
		//SDL_RenderSetLogicalSize(renderer, logicalSize.w, logicalSize.h);
		SDL_Surface* textSurface = TTF_RenderText_Solid(textFont, text.c_str(), colour);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

		//SDL_SetRenderTarget(renderer, NULL);
		dRect = { position.x, position.y, textSurface->w, textSurface->h };
		SDL_RenderCopy(renderer, textTexture, NULL, &dRect);

		SDL_DestroyTexture(textTexture);
		textTexture = NULL;
		SDL_FreeSurface(textSurface);
		textSurface = NULL;
	}
}

WHStruct getTextSize(/*WHStruct logicalSize, */string text, TTF_Font* textFont) {
	WHStruct size = { -1, -1 };

	if (text != "") {
		//SDL_RenderSetLogicalSize(renderer, logicalSize.w, logicalSize.h);
		SDL_Surface* textSurface = TTF_RenderText_Solid(textFont, text.c_str(), defaultColour);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		size.w = textSurface->w;
		size.h = textSurface->h;
		SDL_DestroyTexture(textTexture);
		textTexture = NULL;
		SDL_FreeSurface(textSurface);
		textSurface = NULL;
	}

	return size;
}

vector<WHStruct> getTextSizes(vector<string> text, TTF_Font* textFont) {
	vector<WHStruct> textSizes;
	for (int textCnt = 0; textCnt < (int)text.size(); ++textCnt) {
		textSizes.push_back(getTextSize(text[textCnt], textFont));
	}
	return textSizes;
}

vector<string> getFilesOrFolders(string path) {
	vector<string> paths;
	for (const auto& entry : fs::directory_iterator(path)) {
		paths.push_back(entry.path().string());
		//cout << entry.path().string() << "\n";
	}
	return paths;
}


void initWindowAndRenderer() {

	//Init window
	if (fullscreen == false) {
		window = SDL_CreateWindow("game", 2560 - windowResolution.w - 10, 50, windowResolution.w, windowResolution.h, SDL_WINDOW_SHOWN);
	}
	else {
		window = SDL_CreateWindow("game", 0, 0, windowResolution.w, windowResolution.h, SDL_WINDOW_FULLSCREEN);
	}

	//Init renderer
	if (vSyncOn == true) {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	}
	else {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}

}

void init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	//Get monitor refresh rate
	/*for (int monitorsCnt = 0; monitorsCnt < SDL_GetNumVideoDisplays(); ++monitorsCnt) {
		SDL_DisplayMode mode;
		if (SDL_GetCurrentDisplayMode(monitorsCnt, &mode) == 0) {
			cout << mode.refresh_rate << "\n";
		}
	}*/
	SDL_DisplayMode mode;
	if (SDL_GetCurrentDisplayMode(0, &mode) == 0) {
		//printInt(mode.refresh_rate);
		refreshRate = mode.refresh_rate;
	}

	//Set timer mod
	FPSTimerMod = 60 / FPSCap;

	initWindowAndRenderer();
	SDL_ShowCursor(SDL_DISABLE);

	IMG_Init(IMG_INIT_PNG);

	TTF_Init();

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void destroyWindowAndRenderer() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void close() {
	Mix_CloseAudio();
	TTF_Quit();
	IMG_Quit();
	destroyWindowAndRenderer();
	window = NULL;
	SDL_JoystickClose(controller);
	SDL_Quit();
}

void initMusic() {
	vector<string> musicFiles = getFilesOrFolders("assets\\music\\");
	for (int musicFilesCnt = 0; musicFilesCnt < (int)musicFiles.size(); ++musicFilesCnt) {
		musicStruct currentMusic;
		string folderPath = "assets\\music\\";
		string musicName = musicFiles[musicFilesCnt].substr(folderPath.length(), musicFiles[musicFilesCnt].length() - folderPath.length() - 4);
		currentMusic.music = Mix_LoadMUS(musicFiles[musicFilesCnt].c_str());
		currentMusic.name = musicName;
		music.push_back(currentMusic);
	}

	/*struct musicStruct {
		string name;
		Mix_Music* music;
	};
	vector<musicStruct> music;*/
}

void freeMusic() {
	for (int musicCnt = 0; musicCnt < (int)music.size(); ++musicCnt) {
		Mix_FreeMusic(music[musicCnt].music);
	}
}

int getMusicIndex(string name) {
	for (int musicCnt = 0; musicCnt < (int)music.size(); ++musicCnt) {
		if (music[musicCnt].name == name) {
			return musicCnt;
		}
	}
	return -1;
}

void initSoundEffects() {
	vector<string> soundEffectFiles = getFilesOrFolders("assets\\sound effects\\");
	for (int soundEffectFilesCnt = 0; soundEffectFilesCnt < (int)soundEffectFiles.size(); ++soundEffectFilesCnt) {
		soundEffectStruct currentsoundEffect;
		string folderPath = "assets\\sound effects\\";
		string soundEffectName = soundEffectFiles[soundEffectFilesCnt].substr(folderPath.length(), soundEffectFiles[soundEffectFilesCnt].length() - folderPath.length() - 4);
		currentsoundEffect.soundEffect = Mix_LoadWAV(soundEffectFiles[soundEffectFilesCnt].c_str());
		currentsoundEffect.name = soundEffectName;
		soundEffects.push_back(currentsoundEffect);
	}

	/*struct soundFXStruct {
		string name;
		Mix_Chunk* soundEffect;
	};
	vector<soundFXStruct> soundEffects;*/
}

void freeSoundEffects() {
	for (int soundEffectsCnt = 0; soundEffectsCnt < (int)soundEffects.size(); ++soundEffectsCnt) {
		Mix_FreeChunk(soundEffects[soundEffectsCnt].soundEffect);
	}
}

int getSoundEffectIndex(string name) {
	for (int soundEffectsCnt = 0; soundEffectsCnt < (int)soundEffects.size(); ++soundEffectsCnt) {
		if (soundEffects[soundEffectsCnt].name == name) {
			return soundEffectsCnt;
		}
	}
	return -1;
}

TTF_Font* getFont(string name, int size) {
	for (int fontDataCnt = 0; fontDataCnt < (int)fontData.size(); ++fontDataCnt) {
		if (fontData[fontDataCnt].name == name && fontData[fontDataCnt].size == size) {
			return fontData[fontDataCnt].font;
		}
	}

	return NULL;
}

void initFonts() {

	//Define font names and sizes
	/*fontData = {
		{ "PressStart2P-vaV7.ttf", 12, NULL },
		{ "PressStart2P-vaV7.ttf", 24, NULL },
		{ "PressStart2P-vaV7.ttf", 48, NULL }
	};*/
	//int fontSize = 8;
	/*for (int fontDataCnt = 0; fontDataCnt < 12; ++fontDataCnt) {
		fontData.push_back({ "PressStart2P-vaV7.ttf", fontSize, NULL });
		fontSize += 4;
	}*/
	int fontSize = tileSize.w * 2;
	fontData.push_back({ "PressStart2P-vaV7.ttf", fontSize, NULL });

	//Create fonts
	for (int fontDataCnt = 0; fontDataCnt < (int)fontData.size(); ++fontDataCnt) {
		fontData[fontDataCnt].font = { TTF_OpenFont(fontData[fontDataCnt].name.c_str(), fontData[fontDataCnt].size) };
	}

	defaultFont = getFont("PressStart2P-vaV7.ttf", tileSize.w * 2);
}

void closeFonts() {
	for (int fontDataCnt = 0; fontDataCnt < (int)fontData.size(); ++fontDataCnt) {
		TTF_CloseFont(fontData[fontDataCnt].font);
	}
}

void initColours() {
	defaultColour = { 255, 255, 255 };
}

int getSpriteSheetIndex(string spriteSheetName) {
	for (int spriteSheetsCnt = 0; spriteSheetsCnt < (int)spriteSheets.size(); ++spriteSheetsCnt) {
		string folderPath = "assets\\sprite sheets\\";
		if (spriteSheets[spriteSheetsCnt].filePath.substr(folderPath.length(), spriteSheets[spriteSheetsCnt].filePath.length() - folderPath.length() - 4) == spriteSheetName) {
			return spriteSheetsCnt;
		}
	}

	/*struct spriteSheetStruct {
		string filePath;
		SDL_Surface* surface;
		SDL_Texture* texture;
	};
	vector<spriteSheetStruct> spriteSheets;*/

	return -1;
}

void initSpriteSheets() {

	//Load sprite sheets
	//vector<string> spriteSheetFiles = getFilesOrFolders("C:\\Users\\abc003\\source\\repos\\game1\\exploration-game\\assets\\sprite sheets");
	vector<string> spriteSheetFiles = getFilesOrFolders("assets\\sprite sheets");
	for (int spriteSheetFilesCnt = 0; spriteSheetFilesCnt < (int)spriteSheetFiles.size(); ++spriteSheetFilesCnt) {
		spriteSheetStruct currentSpriteSheet;
		currentSpriteSheet.filePath = spriteSheetFiles[spriteSheetFilesCnt];
		currentSpriteSheet.surface = IMG_Load(currentSpriteSheet.filePath.c_str());
		spriteSheets.push_back(currentSpriteSheet);
	}

	//Set colour key and create textures
	struct colourStruct {
		int r, g, b;
	};
	struct colourKeyExceptionsStruct {
		string spriteSheetName;
		int spriteSheetIndex;
		colourStruct colour;
	};
	vector<colourKeyExceptionsStruct> colourKeyExceptions = {
		{ "main character", -1, { 186, 254, 202 } }
	};
	for (int colourKeyExceptionsCnt = 0; colourKeyExceptionsCnt < (int)colourKeyExceptions.size(); ++colourKeyExceptionsCnt) {
		colourKeyExceptions[colourKeyExceptionsCnt].spriteSheetIndex = getSpriteSheetIndex(colourKeyExceptions[colourKeyExceptionsCnt].spriteSheetName);
	}
	for (int spriteSheetsCnt = 0; spriteSheetsCnt < (int)spriteSheets.size(); ++spriteSheetsCnt) {

		//Set colour key
		int colourKeyExceptionsIndex = -1;
		for (int colourKeyExceptionsCnt = 0; colourKeyExceptionsCnt < (int)colourKeyExceptions.size(); ++colourKeyExceptionsCnt) {
			if (colourKeyExceptions[colourKeyExceptionsCnt].spriteSheetIndex == spriteSheetsCnt) {
				colourKeyExceptionsIndex = colourKeyExceptionsCnt;
				break;
			}
		}
		if (colourKeyExceptionsIndex > -1) {
			SDL_SetColorKey(spriteSheets[spriteSheetsCnt].surface, SDL_TRUE, SDL_MapRGB(spriteSheets[spriteSheetsCnt].surface->format, colourKeyExceptions[colourKeyExceptionsIndex].colour.r, colourKeyExceptions[colourKeyExceptionsIndex].colour.g, colourKeyExceptions[colourKeyExceptionsIndex].colour.b));
		}
		else {
			SDL_SetColorKey(spriteSheets[spriteSheetsCnt].surface, SDL_TRUE, SDL_MapRGB(spriteSheets[spriteSheetsCnt].surface->format, 255, 0, 255));
		}

		spriteSheets[spriteSheetsCnt].texture = SDL_CreateTextureFromSurface(renderer, spriteSheets[spriteSheetsCnt].surface);
	}
}

void initGlobalSprites() {
	selectedHeaderSprite = { getSpriteSheetIndex("UI"), { 21, 0, 8, 8 }, "" };
	selectedIconSprite = { getSpriteSheetIndex("UI"), { 21, 0, 8, 8 }, "" };
	iconBackgroundSprite = { getSpriteSheetIndex("UI"), { 46, 0, 8, 8 }, "" };
	menuBackgroundSprite = { getSpriteSheetIndex("UI"), { 34, 0, 8, 8 }, "" };
	loadIconBack = { getSpriteSheetIndex("UI"), { 56, 0, 8, 8 }, "" };
	loadIconFront = { getSpriteSheetIndex("UI"), { 66, 0, 8, 8 }, "" };
	blankIcon = { getSpriteSheetIndex("UI"), { 76, 0, 8, 8 }, "" };
	UISpriteSheetIndex = getSpriteSheetIndex("UI");
	controllerButtonsSpriteSheetIndex = getSpriteSheetIndex("controller buttons");
}

void destroySpriteSheets() {
	for (int spriteSheetsCnt = 0; spriteSheetsCnt < (int)spriteSheets.size(); ++spriteSheetsCnt) {
		SDL_FreeSurface(spriteSheets[spriteSheetsCnt].surface);
		SDL_DestroyTexture(spriteSheets[spriteSheetsCnt].texture);
	}
}

void initTiles() {

	//Define tiles
	const vector<tileStruct> initialTiles = {
		{ getSpriteSheetIndex("shadowrun"), "concrete floor", { 42, 64, tileSize.w, tileSize.h } },
		{ getSpriteSheetIndex("shadowrun"), "wall", { 95, 152, tileSize.w, tileSize.h } },
		{ getSpriteSheetIndex("shadowrun"), "wall2", { 112, 103, tileSize.w, tileSize.h } },
		{ getSpriteSheetIndex("shadowrun"), "road tar", { 0, 68, tileSize.w, tileSize.h } },
		{ getSpriteSheetIndex("shadowrun"), "road horizontal stripe", { 151, 53, tileSize.w, tileSize.h } },
		{ getSpriteSheetIndex("shadowrun"), "road vertical stripe", { 133, 42, tileSize.w, tileSize.h } },
		{ getSpriteSheetIndex("shadowrun room"), "room floor", { 310, 264, tileSize.w, tileSize.h } },
		{ getSpriteSheetIndex("shadowrun room"), "room wall", { 49, 224, tileSize.w, tileSize.h } }
	};

	/*struct tileStruct {
		int spriteSheetIndex;
		string tileName;
		areaStruct spriteSheetArea;
	};
	vector<tileStruct> tiles;*/

	//Init tiles
	for (int initialTilesCnt = 0; initialTilesCnt < (int)initialTiles.size(); ++initialTilesCnt) {
		tileStruct currentTile = initialTiles[initialTilesCnt];

		//Adjust tile width and height to keep it at tileWidth x tileHeight when x and y = 0
		int currentTileWidth = tileSize.w;
		if (initialTiles[initialTilesCnt].spriteSheetArea.x == 0) {
			--currentTileWidth;
		}
		int currentTileHeight = tileSize.h;
		if (initialTiles[initialTilesCnt].spriteSheetArea.y == 0) {
			--currentTileHeight;
		}
		currentTile.spriteSheetArea.w = currentTileWidth;
		currentTile.spriteSheetArea.h = currentTileHeight;

		tiles.push_back(currentTile);
	}

}

void initFiles() {
	emptyFile("assets\\misc\\created objects.txt");
}

void clearScreen(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
}

void clearTexture(SDL_Texture* texture, int r, int g, int b, int a) {
	setSDLRenderTarget(texture);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
}

int getTileIndex(string tileName) {
	for (int tileIndex = 0; tileIndex < (int)tiles.size(); ++tileIndex) {
		if (tiles[tileIndex].tileName == tileName) {
			return tileIndex;
		}
	}
	return -1;
}

XYStruct getGridPosition(XYStruct position) {
	return { lround((float)position.x / tileSize.w), lround((float)position.y / tileSize.h) };
}

WHStruct getGridSize(WHStruct size) {
	return { lround((float)size.w / tileSize.w), lround((float)size.h / tileSize.h) };
}

areaStruct getGridArea(XYStruct pixelPosition, XYStruct pixelSize) {
	XYStruct objectGridCoordinates = getGridPosition(pixelPosition);
	XYStruct objectGridSize = getGridPosition(pixelSize);
	return { objectGridCoordinates.x, objectGridCoordinates.y, objectGridSize.x, objectGridSize.y };
}

areaStruct getGridAreaFromPixelArea(areaStruct area) {
	XYStruct gridPosition = getGridPosition({ area.x, area.y });
	XYStruct gridSize = getGridPosition({ area.w, area.h });
	return { gridPosition.x, gridPosition.y, gridSize.x, gridSize.y };
}

areaStruct getGridAreaFromSDLRect(SDL_Rect rect) {
	XYStruct gridPosition = getGridPosition({ rect.x, rect.y });
	XYStruct gridSize = getGridPosition({ rect.w, rect.h });
	return { gridPosition.x, gridPosition.y, gridSize.x, gridSize.y };
}

SDL_Rect convertAreaToSDLRect(areaStruct area) {
	return { area.x, area.y, area.w, area.h };
}

areaStruct convertSDLRectToArea(SDL_Rect rect) {
	return { rect.x, rect.y, rect.w, rect.h };
}

areaStruct alignPixelAreaToGrid(areaStruct area) {
	return { ((int)area.x / tileSize.w) * tileSize.w, ((int)area.y / tileSize.h) * tileSize.h, ((int)area.w / tileSize.w) * tileSize.w, ((int)area.h / tileSize.h) * tileSize.h };
}

int getCityGridUnitIndex(string name) {
	for (int cityGridUnitsCnt = 0; cityGridUnitsCnt < (int)cityGridUnits.size(); ++cityGridUnitsCnt) {
		if (cityGridUnits[cityGridUnitsCnt].name == name) {
			return cityGridUnitsCnt;
		}
	}
	return -1;
}

void initBuildingDoor(int doorID, int unitsXCnt, int unitsYCnt) {
	objectConstructorVarsStruct objectConstructorVars;

	objectConstructorVars.ID = doorID;
	objectConstructorVars.layer = 1;
	objectConstructorVars.type = "Door";

	if (currentlyInsideBuilding == true) {
		objectConstructorVars.collision = false;
	}

	XYStruct initialTilePosition = { unitsXCnt * (cityGrid.unitTileSize.w + cityGrid.spaceBetweenUnits.w), unitsYCnt * (cityGrid.unitTileSize.h + cityGrid.spaceBetweenUnits.h) };

	//Get offset for empty bottom of building
	/*XYStruct buildingLimits = { 0, 0 }, offset = { 0, 0 };
	bool broke = false;
	for (buildingLimits.y = (int)cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles[buildingLimits.x].size() - 1; buildingLimits.y > 0; --buildingLimits.y) {
		if (cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles[buildingLimits.x][buildingLimits.y].tileIndex > -1) {
			broke = true;
			break;
		}
		++offset.y;
	}
	if (broke == false) {
		offset.y = 0;
	}*/

	WHStruct doorTileSize = { 4, 4 };
	WHStruct doorPixelSize = { tileSize.w * doorTileSize.w, tileSize.h * doorTileSize.h };

	//Get building x start
	int tileMiddleY = ((int)cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles[0].size() - 1) / 2;
	int roomXStart = 0;
	while (cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles[roomXStart][tileMiddleY].tileIndex == -1) {
		++roomXStart;
	}

	//Get room x end
	int roomXEnd = (int)cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles.size() - 1;
	while (cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles[roomXEnd][tileMiddleY].tileIndex == -1) {
		--roomXEnd;
	}

	//Get room y
	int tileMiddleX = ((int)cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles.size() - 1) / 2;
	int roomY = (int)cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles[tileMiddleX].size() - 1;
	while (cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles[tileMiddleX][roomY].tileIndex == -1) {
		--roomY;
	}

	objectConstructorVars.objectDRect = { randInt((initialTilePosition.x + roomXStart) * tileSize.w, (initialTilePosition.x + roomXEnd - doorTileSize.w) * tileSize.w), ((initialTilePosition.y + roomY + 1) * tileSize.h) - doorPixelSize.h, doorPixelSize.w, doorPixelSize.h };

	//Get x offset for randInt start and end to position door on building and not in empty space at bottom of building
	/*int randIntStart, randIntEnd;
	while (true) {
		int randIntStartStart = buildingXStart;
		int randIntStartEnd = buildingXEnd - doorTileSize.w;
		if (randIntStartEnd < randIntStartStart) {
			randIntStartEnd = randIntStartStart;
		}
		randIntStart = randInt(randIntStartStart, randIntStartEnd);

		int randIntEndStart = randIntStart;
		int randIntEndEnd = buildingXEnd - doorTileSize.w;
		if (randIntEndEnd < randIntEndStart) {
			randIntEndEnd = randIntEndStart;
		}
		randIntEnd = randInt(randIntEndStart, randIntEndEnd);

		if (unitsXCnt < (int)cityGrid.units[objectConstructorVars.layer].size() && unitsYCnt < (int)cityGrid.units[objectConstructorVars.layer][unitsXCnt].size()) {

			int randIntStartTileY = ((int)cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles[randIntStart].size() - 1) / 2;
			int randIntEndTileY = ((int)cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles[randIntEnd].size() - 1) / 2;

			if (randIntStart < (int)cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles.size() && randIntStartTileY < (int)cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles[randIntStart].size() && randIntEnd < (int)cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles.size() && randIntEndTileY < (int)cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles[randIntEnd].size()) {

				if (randIntStart <= randIntEnd && cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles[randIntStart][randIntStartTileY].tileIndex > -1 && cityGrid.units[objectConstructorVars.layer][unitsXCnt][unitsYCnt].tiles[randIntEnd][randIntEndTileY].tileIndex > -1) {
					break;
				}

			}
		}

	}*/

	//objectConstructorVars.objectDRect = { randInt(initialTilePosition.x, initialTilePosition.x + cityGrid.unitTileSize.w - doorTileSize.w) * tileSize.w, (initialTilePosition.y + cityGrid.unitTileSize.h - doorTileSize.h - offset.y) * tileSize.h, tileSize.w * 4, tileSize.h * 4 };

	objectConstructorVars.currentStateAnimation = 0;

	//Init state animations
	//const vector<string> stateAnimations = { "Closed", "Opened" };
	const vector<string> stateAnimations = { "Opened" };
	for (int stateAnimationsCnt = 0; stateAnimationsCnt < (int)stateAnimations.size(); ++stateAnimationsCnt) {
		animationStruct currentAnimation;
		currentAnimation.name = stateAnimations[stateAnimationsCnt];
		currentAnimation.spriteSheetIndex = getSpriteSheetIndex("doors");
		if (currentAnimation.name == "Closed") {
			currentAnimation.spritesSRect = {
				{ 0, 35, 32, 29 }
				/*{ 38, 35, 32, 29 },
				{ 76, 35, 32, 29 }*/
			};
		}
		else if (currentAnimation.name == "Opened") {
			currentAnimation.spritesSRect = { { 76, 35, 32, 29 } };
		}
		currentAnimation.totalLoops = -1;
		objectConstructorVars.stateAnimations.push_back(currentAnimation);
	}

	//Init keypad
	objectConstructorVarsStruct::inputDeviceStruct keypad;
	keypad.name = "Keypad";
	int keypadSpriteSheetIndex = getSpriteSheetIndex("keypad");
	const vector<vector<string>> keypadGridCaptions = {
		{ "1", "2", "3" },
		{ "4", "5", "6" },
		{ "7", "8", "9" },
		{ "BK", "0", "DL"}
	};
	const vector<vector<areaStruct>> keypadGridSpriteSheetIconAreas = {
		{ {  }, {  }, {  } },
		{ {  }, {  }, {  } },
		{ {  }, {  }, {  } },
		{ {  }, {  }, {  } }
	};
	keypad.grid.resize((int)keypadGridCaptions.size());
	for (int keypadGridCaptionYCnt = 0; keypadGridCaptionYCnt < (int)keypadGridCaptions.size(); ++keypadGridCaptionYCnt) {
		keypad.grid[keypadGridCaptionYCnt].resize((int)keypadGridCaptions[0].size());
		for (int keypadGridCaptionXCnt = 0; keypadGridCaptionXCnt < (int)keypadGridCaptions[0].size(); ++keypadGridCaptionXCnt) {
			iconStruct currentIcon;

			currentIcon.caption = keypadGridCaptions[keypadGridCaptionYCnt][keypadGridCaptionXCnt];
			currentIcon.spriteSheetArea = keypadGridSpriteSheetIconAreas[keypadGridCaptionYCnt][keypadGridCaptionXCnt];
			currentIcon.spriteSheetIndex = getSpriteSheetIndex("keypad");

			keypad.grid[keypadGridCaptionYCnt][keypadGridCaptionXCnt] = currentIcon;
		}
	}
	keypad.inputDevicedDRect = { 0, 0, tileSize.w * 30, tileSize.h * 30 };
	objectConstructorVars.inputDevices.push_back(keypad);

	//Init keyboard
	objectConstructorVarsStruct::inputDeviceStruct keyboard;
	keyboard.name = "Keyboard";
	int keyboardSpriteSheetIndex = getSpriteSheetIndex("keyboard");
	const vector<vector<string>> keyboardGridCaption = {
		{ { "Q" }, { "W" }, { "E" }, { "R" }, { "T" }, { "Y" }, { "U" }, { "I" }, { "O" }, { "P" } },
		{ { "A" }, { "S" }, { "D" }, { "F" }, { "G" }, { "H" }, { "J" }, { "K" }, { "L" }, { "BK"} },
		{ { "Z" }, { "X" }, { "C" }, { "V" }, { "B" }, { "N" }, { "M" }, { "SP" } , { "EN" }, { "DL" } }
	};
	const vector<vector<areaStruct>> keyboardGridSpriteSheetIconAreas = {
		{ {  }, {  }, {  }, {  }, {  }, {  }, {  }, {  }, {  }, {  } },
		{ {  }, {  }, {  }, {  }, {  }, {  }, {  }, {  }, {  }, {  } },
		{ {  }, {  }, {  }, {  }, {  }, {  }, {  }, {  }, {  }, {  } }
	};
	keyboard.grid.resize((int)keyboardGridCaption.size());
	for (int keyboardGridCaptionYCnt = 0; keyboardGridCaptionYCnt < (int)keyboardGridCaption.size(); ++keyboardGridCaptionYCnt) {
		keyboard.grid[keyboardGridCaptionYCnt].resize((int)keyboardGridCaption[0].size());
		for (int keyboardGridCaptionXCnt = 0; keyboardGridCaptionXCnt < (int)keyboardGridCaption[0].size(); ++keyboardGridCaptionXCnt) {
			iconStruct currentIcon;

			currentIcon.caption = keyboardGridCaption[keyboardGridCaptionYCnt][keyboardGridCaptionXCnt];
			currentIcon.spriteSheetArea = keyboardGridSpriteSheetIconAreas[keyboardGridCaptionYCnt][keyboardGridCaptionXCnt];
			currentIcon.spriteSheetIndex = getSpriteSheetIndex("keyboard");

			keyboard.grid[keyboardGridCaptionYCnt][keyboardGridCaptionXCnt] = currentIcon;
		}
	}
	keyboard.inputDevicedDRect = { 0, 0, tileSize.w * 60, tileSize.h * 30 };
	objectConstructorVars.inputDevices.push_back(keyboard);

	//Init options
	int totalOptions = randInt(2, 5);
	for (int optionsCnt = 0; optionsCnt < totalOptions; ++optionsCnt) {
		objectConstructorVarsStruct::optionStruct currentOption;

		currentOption.icon = { getSpriteSheetIndex("door interactions"), randArea({ { 77, 0, 32, 32 }, { 114, 0, 32, 32 } }), "Option " + str(optionsCnt) };
		currentOption.requiredStateAnimation = randInt(0, (int)stateAnimations.size() - 1);

		//Init require skills
		for (int requiredSkillsCnt = 0; requiredSkillsCnt < randInt(2, 9); ++requiredSkillsCnt) {
			skillStruct currentSkill;

			currentSkill.name = "Skill " + str(randInt(0, 9));
			currentSkill.description = "Description " + str(randInt(0, 9));
			currentSkill.current = randInt(0, 9);
			currentSkill.modified = randInt(0, 9);
			currentSkill.max = randInt(0, 9);
			currentSkill.icon = { getSpriteSheetIndex("skills"), randArea({ { 25, 0, 22, 23 }, { 49, 0, 22, 23 } }), "" };

			currentOption.requiredSkills.push_back(currentSkill);
		}

		//Init required misc items
		if (randInt(0, 1) == 0) {
			currentOption.removeMiscItems = true;
		}
		for (int requiredMiscItemsCnt = 0; requiredMiscItemsCnt < randInt(2, 9); ++requiredMiscItemsCnt) {
			currentOption.requiredMiscItems.push_back({ "Item " + str(randInt(0, 9)), "Description " + str(randInt(0, 9)), randInt(0, 9), { getSpriteSheetIndex("misc items"), randArea({ { 0, 0, 27, 28 }, { 32, 0, 26, 27 } }), "" } });
		}

		//Init required keypad code
		//if (randInt(0, 9) < 7) {
			/*Object::optionStruct::inputDeviceRequirementsStruct keypadRequirements;
			keypadRequirements.name = "Keypad";
			int codeLength = 4;
			for (int codeLengthCnt = 0; codeLengthCnt < codeLength; ++codeLengthCnt) {
				keypadRequirements.code += str(randInt(0, 9));
			}
			keypadRequirements.codeFound = true;
			currentOption.inputDeviceRequirements.push_back(keypadRequirements);*/
			//}

			// Init required keyboard code
			//if (randInt(0, 9) < 7) {
				/*Object::optionStruct::inputDeviceRequirementsStruct keyboardRequirements;
				keyboardRequirements.name = "Keyboard";
				keyboardRequirements.code = "CODE" + randStringList({ "A", "B", "C" });
				keyboardRequirements.codeFound = true;
				currentOption.inputDeviceRequirements.push_back(keyboardRequirements);*/
				//}

		currentOption.newCurrentStateAnimation = randInt(0, (int)stateAnimations.size() - 1);

		//Init option changes
		for (int optionChangesCnt = 0; optionChangesCnt < randInt(2, 9); ++optionChangesCnt) {
			objectConstructorVarsStruct::optionStruct::optionChangeStruct currentOptionChange;

			currentOptionChange.newOption = randInt(0, 1);

			currentOptionChange.newIcon = blankIcon;

			if (randInt(0, 1) == 0) {
				currentOptionChange.optionToChangeIndex = randInt(-1, totalOptions - 1);
			}
			else {
				currentOptionChange.optionToChangeIconCaption = "Option " + str(randInt(0, 9));
			}

			currentOptionChange.newCaption = randStringList({ "", "Caption 1", "Caption 2" });
			currentOptionChange.newRequiredStateAnimation = randInt(0, (int)objectConstructorVars.stateAnimations.size() - 1);

			for (int newRequiredSkillsCnt = 0; newRequiredSkillsCnt < randInt(2, 9); ++newRequiredSkillsCnt) {
				skillStruct currentNewRequiredSkill;

				currentNewRequiredSkill.name = "Skill " + str(randInt(0, 9));
				currentNewRequiredSkill.description = "Description " + str(randInt(0, 9));
				currentNewRequiredSkill.current = randInt(0, 9);
				currentNewRequiredSkill.modified = randInt(0, 9);
				currentNewRequiredSkill.max = randInt(0, 9);
				currentNewRequiredSkill.icon = { getSpriteSheetIndex("skills"), randArea({ { 25, 0, 22, 23 }, { 49, 0, 22, 23 } }), "" };

				currentOptionChange.newRequiredSkills.push_back(currentNewRequiredSkill);
			}

			for (int newRequiredMiscItemsCnt = 0; newRequiredMiscItemsCnt < randInt(2, 9); ++newRequiredMiscItemsCnt) {
				currentOptionChange.newRequiredMiscItems.push_back({ "Item " + str(randInt(0, 9)), "Description " + str(randInt(0, 9)), randInt(0, 9), { getSpriteSheetIndex("misc items"), randArea({ { 0, 0, 27, 28 }, { 32, 0, 26, 27 } }), "" } });
			}

			currentOptionChange.newLoadInsideBuilding = false;

			currentOption.optionChanges.push_back(currentOptionChange);
		}

		currentOption.newCollision = false;

		if (currentlyInsideBuilding == false) {
			currentOption.loadInsideBuilding = true;
		}
		else {
			currentOption.loadOverworld = true;
		}

		objectConstructorVars.options.push_back(currentOption);
	}

	Object currentDoor(objectConstructorVars);
	objects.push_back(currentDoor);
}

int getObjectFreeIndex() {
	vector<int> indices;
	for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
		indices.push_back(objects[objectsCnt].getID());
	}
	return getFreeID(indices);
}

bool checkCollision(areaStruct area1, areaStruct area2) {
	for (int area1XCnt = area1.x; area1XCnt < area1.x + area1.w; ++area1XCnt) {
		for (int area1YCnt = area1.y; area1YCnt < area1.y + area1.h; ++area1YCnt) {

			for (int area2XCnt = area2.x; area2XCnt < area2.x + area2.w; ++area2XCnt) {
				for (int area2YCnt = area2.y; area2YCnt < area2.y + area2.h; ++area2YCnt) {

					if (area1XCnt == area2XCnt && area1YCnt == area2YCnt) {
						return true;
					}

				}
			}

		}
	}
	return false;
}

bool checkCollisionWithOverworldGrid(areaStruct gridArea, int gridLayer) {
	for (int areaXCnt = gridArea.x; areaXCnt < gridArea.x + gridArea.w; ++areaXCnt) {
		for (int areaYCnt = gridArea.y; areaYCnt < gridArea.y + gridArea.h; ++areaYCnt) {
			if (gridLayer < (int)overworldGrid.gridTile.size() && areaXCnt < (int)overworldGrid.gridTile[gridLayer].size() && areaYCnt < (int)overworldGrid.gridTile[gridLayer][areaXCnt].size() && overworldGrid.gridTile[gridLayer][areaXCnt][areaYCnt].collidable == true) {
				return true;
			}
		}
	}
	return false;
}

int getBuildingIndexByDoorID(int buildingDoorID) {
	for (int buildingsCnt = 0; buildingsCnt < (int)buildings.size(); ++buildingsCnt) {
		if (buildings[buildingsCnt].getBuildingDoorID() == buildingDoorID) {
			return buildingsCnt;
		}
	}
	return -1;
}

int getBuildingIDByIndex(int index) {
	for (int buildingsCnt = 0; buildingsCnt < (int)buildings.size(); ++buildingsCnt) {
		if (buildingsCnt == index) {
			return buildings[buildingsCnt].getID();
		}
	}
	return -1;
}

int getBuildingIndexByID(int ID) {
	for (int buildingsCnt = 0; buildingsCnt < (int)buildings.size(); ++buildingsCnt) {
		if (buildings[buildingsCnt].getID() == ID) {
			return buildingsCnt;
		}
	}
	return -1;
}

void initCityGrid() {
	//City grid is used to organize overworld layout, to place grid units on overworld

	cityGrid.unitTileSize = { 30, 30 };
	cityGrid.spaceBetweenUnits = { 0, 0 };

	vector<string> cityGridUnitNames = { "road horizontal", "road vertical", "road intersection" };

	//Add building names
	for (int buildingNamesCnt = 0; buildingNamesCnt < randInt(3, 6); ++buildingNamesCnt) {
		cityGridUnitNames.push_back("building " + str(buildingNamesCnt));
	}

	//Add room names
	for (int roomNamesCnt = 0; roomNamesCnt < randInt(5, 10); ++roomNamesCnt) {
		cityGridUnitNames.push_back("room " + str(roomNamesCnt));
	}

	//Add bottom room (no space at bottom)
	cityGridUnitNames.push_back("bottom room");

	//Define city grid unit
	cityGridUnits.clear();
	for (int cityGridUnitNamesCnt = 0; cityGridUnitNamesCnt < (int)cityGridUnitNames.size(); ++cityGridUnitNamesCnt) {
		cityGridUnits.resize(cityGridUnitNamesCnt + 1);
		cityGridUnits[cityGridUnitNamesCnt].name = cityGridUnitNames[cityGridUnitNamesCnt];
		if ((int)cityGridUnits[cityGridUnitNamesCnt].name.find("building") > -1) {

			//Define wall
			for (int tilesXCnt = 0; tilesXCnt < cityGrid.unitTileSize.w; ++tilesXCnt) {
				cityGridUnits[cityGridUnitNamesCnt].tiles.resize(tilesXCnt + 1);
				for (int tilesYCnt = 0; tilesYCnt < cityGrid.unitTileSize.h; ++tilesYCnt) {
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt].resize(tilesYCnt + 1);
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].tileIndex = getTileIndex("wall");
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].collidable = true;
				}
			}

			//Define wall2
			for (int wallsCnt = 0; wallsCnt < randInt(5, 10); ++wallsCnt) {
				XYStruct position = { randInt(0, cityGrid.unitTileSize.w - 1), randInt(0, cityGrid.unitTileSize.h - 1) };
				cityGridUnits[cityGridUnitNamesCnt].tiles[position.x][position.y].tileIndex = getTileIndex("wall2");
				cityGridUnits[cityGridUnitNamesCnt].tiles[position.x][position.y].collidable = true;
			}

			//Define space around building
			const vector<areaStruct> tilesStartEndList = {
				{ 0, cityGrid.unitTileSize.h - 4, cityGrid.unitTileSize.w, cityGrid.unitTileSize.h }, //down
				{ 0, 0, cityGrid.unitTileSize.w, 4 }, //up
				{ 0, 0, 4, cityGrid.unitTileSize.h }, //left
				{ cityGrid.unitTileSize.w - 4, 0, cityGrid.unitTileSize.w, cityGrid.unitTileSize.h } //right
			};
			for (int sidesCnt = 0; sidesCnt < 4; ++sidesCnt) {
				if (randInt(1, 2) == 1) {
					for (int tilesXCnt = tilesStartEndList[sidesCnt].x; tilesXCnt < tilesStartEndList[sidesCnt].w; ++tilesXCnt) {
						for (int tilesYCnt = tilesStartEndList[sidesCnt].y; tilesYCnt < tilesStartEndList[sidesCnt].h; ++tilesYCnt) {
							cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].tileIndex = -1;
							cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].collidable = false;
						}
					}
				}
			}

		}
		else if (cityGridUnits[cityGridUnitNamesCnt].name == "road horizontal") {

			//Define tar
			for (int tilesXCnt = 0; tilesXCnt < cityGrid.unitTileSize.w; ++tilesXCnt) {
				cityGridUnits[cityGridUnitNamesCnt].tiles.resize(tilesXCnt + 1);
				for (int tilesYCnt = 0; tilesYCnt < cityGrid.unitTileSize.h; ++tilesYCnt) {
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt].resize(tilesYCnt + 1);
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].tileIndex = getTileIndex("road tar");
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].collidable = false;
				}
			}

			//Define horizontal stripe
			int tilesYCnt = cityGrid.unitTileSize.h / 2;
			for (int tilesXCnt = 0; tilesXCnt < cityGrid.unitTileSize.w; ++tilesXCnt) {
				cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].tileIndex = getTileIndex("road horizontal stripe");
				cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].collidable = false;
			}

		}
		else if (cityGridUnits[cityGridUnitNamesCnt].name == "road vertical") {

			//Define tar
			for (int tilesXCnt = 0; tilesXCnt < cityGrid.unitTileSize.w; ++tilesXCnt) {
				cityGridUnits[cityGridUnitNamesCnt].tiles.resize(tilesXCnt + 1);
				for (int tilesYCnt = 0; tilesYCnt < cityGrid.unitTileSize.h; ++tilesYCnt) {
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt].resize(tilesYCnt + 1);
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].tileIndex = getTileIndex("road tar");
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].collidable = false;
				}
			}

			//Define vertical stripe
			int tilesXCnt = cityGrid.unitTileSize.w / 2;
			for (int tilesYCnt = 0; tilesYCnt < cityGrid.unitTileSize.h; ++tilesYCnt) {
				cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].tileIndex = getTileIndex("road vertical stripe");
				cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].collidable = false;
			}

		}
		else if (cityGridUnits[cityGridUnitNamesCnt].name == "road intersection") {

			//Define tar
			for (int tilesXCnt = 0; tilesXCnt < cityGrid.unitTileSize.w; ++tilesXCnt) {
				cityGridUnits[cityGridUnitNamesCnt].tiles.resize(tilesXCnt + 1);
				for (int tilesYCnt = 0; tilesYCnt < cityGrid.unitTileSize.h; ++tilesYCnt) {
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt].resize(tilesYCnt + 1);
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].tileIndex = getTileIndex("road tar");
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].collidable = false;
				}
			}

			//Define horizontal stripe
			int tilesYCnt = cityGrid.unitTileSize.h / 2;
			for (int tilesXCnt = 0; tilesXCnt < cityGrid.unitTileSize.w; ++tilesXCnt) {
				cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].tileIndex = getTileIndex("road horizontal stripe");
				cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].collidable = false;
			}

			//Define vertical stripe
			int tilesXCnt = cityGrid.unitTileSize.w / 2;
			for (int tilesYCnt = 0; tilesYCnt < cityGrid.unitTileSize.h; ++tilesYCnt) {
				cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].tileIndex = getTileIndex("road vertical stripe");
				cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].collidable = false;
			}

		}
		else if ((int)cityGridUnits[cityGridUnitNamesCnt].name.find("room") > -1) {

			//Define room floor
			for (int tilesXCnt = 0; tilesXCnt < cityGrid.unitTileSize.w; ++tilesXCnt) {
				cityGridUnits[cityGridUnitNamesCnt].tiles.resize(tilesXCnt + 1);
				for (int tilesYCnt = 0; tilesYCnt < cityGrid.unitTileSize.h; ++tilesYCnt) {
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt].resize(tilesYCnt + 1);
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].tileIndex = getTileIndex("room floor");
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].collidable = false;
				}
			}

			//Define room wall
			for (int tilesXCnt = 4; tilesXCnt < cityGrid.unitTileSize.w - 4; ++tilesXCnt) {
				cityGridUnits[cityGridUnitNamesCnt].tiles.resize(tilesXCnt + 1);
				for (int tilesYCnt = 4; tilesYCnt < cityGrid.unitTileSize.h - 4; ++tilesYCnt) {
					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt].resize(tilesYCnt + 1);
					if (tilesXCnt == 4 || tilesXCnt == cityGrid.unitTileSize.w - 5 || tilesYCnt == 4 || tilesYCnt == cityGrid.unitTileSize.h - 5) {
						cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].tileIndex = getTileIndex("room wall");
						cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].collidable = true;
					}
				}
			}

			//Define space around room
			//const vector<areaStruct> tilesStartEndList = {
			//	{ 0, cityGrid.unitTileSize.h - 4, cityGrid.unitTileSize.w, cityGrid.unitTileSize.h }, //down
			//	{ 0, 0, cityGrid.unitTileSize.w, 4 }, //up
			//	{ 0, 0, 4, cityGrid.unitTileSize.h }, //left
			//	{ cityGrid.unitTileSize.w - 4, 0, cityGrid.unitTileSize.w, cityGrid.unitTileSize.h } //right
			//};
			//const vector<areaStruct> newTilesStartEndList = {
			//	{ tilesStartEndList[0].x, tilesStartEndList[0].y, tilesStartEndList[0].w, tilesStartEndList[0].y }, //down
			//	{ tilesStartEndList[1].x, tilesStartEndList[1].h, tilesStartEndList[1].w, tilesStartEndList[1].h }, //up
			//	{ tilesStartEndList[2].w, tilesStartEndList[2].y, tilesStartEndList[2].w, tilesStartEndList[2].h }, //left
			//	{ tilesStartEndList[3].x, tilesStartEndList[3].y, tilesStartEndList[3].x, tilesStartEndList[3].h } //right
			//};
			//for (int sidesCnt = 0; sidesCnt < 4; ++sidesCnt) {
			//	if (randInt(1, 2) == 1) {

			//		//Only leave space at bottom if unit is not a bottom room
			//		if (cityGridUnits[cityGridUnitNamesCnt].name != "bottom room" || cityGridUnits[cityGridUnitNamesCnt].name == "bottom room" && sidesCnt != 0) {

			//			//Remove building section
			//			for (int tilesXCnt = tilesStartEndList[sidesCnt].x; tilesXCnt < tilesStartEndList[sidesCnt].w; ++tilesXCnt) {
			//				for (int tilesYCnt = tilesStartEndList[sidesCnt].y; tilesYCnt < tilesStartEndList[sidesCnt].h; ++tilesYCnt) {
			//					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].tileIndex = -1;
			//					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].collidable = false;
			//				}
			//			}

			//			//Insert new wall
			//			for (int tilesXCnt = newTilesStartEndList[sidesCnt].x; tilesXCnt < newTilesStartEndList[sidesCnt].w; ++tilesXCnt) {
			//				for (int tilesYCnt = newTilesStartEndList[sidesCnt].y; tilesYCnt < newTilesStartEndList[sidesCnt].h; ++tilesYCnt) {
			//					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].tileIndex = getTileIndex("room wall");
			//					cityGridUnits[cityGridUnitNamesCnt].tiles[tilesXCnt][tilesYCnt].collidable = true;
			//				}
			//			}

			//		}

			//	}
			//}

		}
	}

	//Get all building/room indices
	string keyWord;
	if (currentlyInsideBuilding == false) {
		keyWord = "building";
	}
	else {
		keyWord = "room";
	}
	vector<int> buildingUnitIndices;
	for (int cityGridUnitsCnt = 0; cityGridUnitsCnt < (int)cityGridUnits.size(); ++cityGridUnitsCnt) {
		if ((int)cityGridUnits[cityGridUnitsCnt].name.find(keyWord) == 0) {
			buildingUnitIndices.push_back(cityGridUnitsCnt);
		}
	}

	//Clear city grid
	cityGrid.units.clear();

	//Define buildings on city grid
	cityGrid.gridSize = { lround((int)overworldGrid.gridTile[overworldGrid.groundLayerIndex].size() / cityGrid.unitTileSize.w), lround((int)overworldGrid.gridTile[overworldGrid.groundLayerIndex][0].size() / cityGrid.unitTileSize.h) };
	cityGrid.units.resize(2);
	for (int cityGridXCnt = 0; cityGridXCnt < cityGrid.gridSize.w; ++cityGridXCnt) {
		cityGrid.units[1].resize(cityGridXCnt + 1);
		for (int cityGridYCnt = 0; cityGridYCnt < cityGrid.gridSize.h; ++cityGridYCnt) {
			cityGrid.units[1][cityGridXCnt].resize(cityGridYCnt + 1);
			if (randInt(1, 10) > 1) {

				//Building/room unit
				int cityGridUnitIndex = buildingUnitIndices[randInt(0, (int)buildingUnitIndices.size() - 1)];
				if (cityGridUnitIndex < (int)cityGridUnits.size()) {
					cityGrid.units[1][cityGridXCnt][cityGridYCnt].name = cityGridUnits[cityGridUnitIndex].name;
					cityGrid.units[1][cityGridXCnt][cityGridYCnt].tiles = cityGridUnits[cityGridUnitIndex].tiles;
				}

			}
			else {

				//Empty unit
				cityGrid.units[1][cityGridXCnt][cityGridYCnt].name = "";
				cityGrid.units[1][cityGridXCnt][cityGridYCnt].tiles = {  };

			}
		}
	}

	if (currentlyInsideBuilding == false) {

		//Define roads on city grid
		vector<XYStruct> horizontalPositions;
		int unitYCnt = 0;
		for (int horizontalRoadsCnt = 0; horizontalRoadsCnt < randInt(5, 10); ++horizontalRoadsCnt) {
			for (int unitXCnt = 0; unitXCnt < (int)cityGrid.units[1].size(); ++unitXCnt) {
				if (unitXCnt >= 0 && unitXCnt <= (int)cityGrid.units[1].size() - 1 && unitYCnt >= 0 && unitYCnt <= (int)cityGrid.units[1][unitXCnt].size() - 1) {
					cityGrid.units[1][unitXCnt][unitYCnt].name = "road horizontal";
					cityGrid.units[1][unitXCnt][unitYCnt].tiles = cityGridUnits[getCityGridUnitIndex(cityGrid.units[1][unitXCnt][unitYCnt].name)].tiles;
					horizontalPositions.push_back({ unitXCnt, unitYCnt });
				}
			}
			unitYCnt += randInt(5, 10);
		}
		vector<XYStruct> verticalPositions;
		int unitXCnt = 0;
		for (int horizontalRoadsCnt = 0; horizontalRoadsCnt < randInt(5, 10); ++horizontalRoadsCnt) {
			for (int unitYCnt = 0; unitYCnt < (int)cityGrid.units[0].size(); ++unitYCnt) {
				if (unitXCnt >= 0 && unitXCnt <= (int)cityGrid.units[1].size() - 1 && unitYCnt >= 0 && unitYCnt <= (int)cityGrid.units[1][unitXCnt].size() - 1) {
					cityGrid.units[1][unitXCnt][unitYCnt].name = "road vertical";
					cityGrid.units[1][unitXCnt][unitYCnt].tiles = cityGridUnits[getCityGridUnitIndex(cityGrid.units[1][unitXCnt][unitYCnt].name)].tiles;
					verticalPositions.push_back({ unitXCnt, unitYCnt });
				}
			}
			unitXCnt += randInt(5, 10);
		}

		//Define road intersections
		for (int horizontalPositionsCnt = 0; horizontalPositionsCnt < (int)horizontalPositions.size(); ++horizontalPositionsCnt) {
			for (int verticalPositionsCnt = 0; verticalPositionsCnt < (int)verticalPositions.size(); ++verticalPositionsCnt) {
				if (horizontalPositions[horizontalPositionsCnt].x == verticalPositions[verticalPositionsCnt].x && horizontalPositions[horizontalPositionsCnt].y == verticalPositions[verticalPositionsCnt].y) {
					cityGrid.units[1][horizontalPositions[horizontalPositionsCnt].x][horizontalPositions[horizontalPositionsCnt].y].name = "road intersection";
					cityGrid.units[1][horizontalPositions[horizontalPositionsCnt].x][horizontalPositions[horizontalPositionsCnt].y].tiles = cityGridUnits[getCityGridUnitIndex(cityGrid.units[1][horizontalPositions[horizontalPositionsCnt].x][horizontalPositions[horizontalPositionsCnt].y].name)].tiles;
				}
			}
		}

	}

	//Get interactable object free index
	/*vector<int> indices;
	for (int skillBasedInteractableObjectsCnt = 0; skillBasedInteractableObjectsCnt < (int)skillBasedInteractableObjects.size(); ++skillBasedInteractableObjectsCnt) {
		indices.push_back(skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].index);
	}
	int skillBasedInteractableObjectIndex = getFreeID(indices);*/

	if (usedStairs == true) {

		//Find stairs closest to controlled character's position
		int closestStairsIndex = -1, closestStairsHeuristic = -1;
		for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
			if ((int)objects[objectsCnt].getType().find("Stairs") > -1) {
				SDL_Rect objectDRect = objects[objectsCnt].getObjectDRect();

				int currentHeuristic = getHeuristic(characters[controlledCharacterIndex].getPosition(), { objectDRect.x, objectDRect.y });

				if (closestStairsHeuristic == -1 || currentHeuristic < closestStairsHeuristic) {
					closestStairsHeuristic = currentHeuristic;
					closestStairsIndex = objectsCnt;
				}
			}
		}

		//Reposition characters next to stairs that is closest to controlled character's position
		for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
			SDL_Rect objectDRect = objects[closestStairsIndex].getObjectDRect();

			characters[charactersCnt].setPosition({ objectDRect.x, objectDRect.y + objectDRect.h });
		}

	}

	objects.clear();

	int doorID = getObjectFreeIndex();

	if (currentlyInsideBuilding == false) {
		buildings.clear();
	}

	//Pass city grid tiles to overworld grid
	for (int unitsXCnt = 0; unitsXCnt < (int)cityGrid.units[1].size(); ++unitsXCnt) {
		for (int unitsYCnt = 0; unitsYCnt < (int)cityGrid.units[1][unitsXCnt].size(); ++unitsYCnt) {
			if (cityGrid.units[1][unitsXCnt][unitsYCnt].name != "") {

				//Pass tiles
				XYStruct initialTilePosition = { unitsXCnt * (cityGrid.unitTileSize.w + cityGrid.spaceBetweenUnits.w), unitsYCnt * (cityGrid.unitTileSize.h + cityGrid.spaceBetweenUnits.h) };
				XYStruct tilePosition = initialTilePosition;
				for (int tilesXCnt = 0; tilesXCnt < (int)cityGrid.units[1][unitsXCnt][unitsYCnt].tiles.size(); ++tilesXCnt) {
					tilePosition.y = initialTilePosition.y;
					for (int tilesYCnt = 0; tilesYCnt < (int)cityGrid.units[1][unitsXCnt][unitsYCnt].tiles[tilesXCnt].size(); ++tilesYCnt) {

						if (tilePosition.x < (int)overworldGrid.gridTile[overworldGrid.groundLayerIndex + 1].size() && tilePosition.y < (int)overworldGrid.gridTile[overworldGrid.groundLayerIndex + 1][tilePosition.x].size() && unitsXCnt < (int)cityGrid.units[1].size() && unitsYCnt < (int)cityGrid.units[1][unitsXCnt].size() && tilesXCnt < (int)cityGrid.units[1][unitsXCnt][unitsYCnt].tiles.size() && tilesYCnt < (int)cityGrid.units[1][unitsXCnt][unitsYCnt].tiles[tilesXCnt].size()) {

							//Pass unit tiles to overworld grid
							overworldGrid.gridTile[overworldGrid.groundLayerIndex + 1][tilePosition.x][tilePosition.y] = cityGrid.units[1][unitsXCnt][unitsYCnt].tiles[tilesXCnt][tilesYCnt];

						}

						++tilePosition.y;
					}
					++tilePosition.x;
				}

				//Init building door
				if ((int)cityGrid.units[1][unitsXCnt][unitsYCnt].name.find(keyWord) > -1) {
					//initBuildingDoor(skillBasedInteractableObjectIndex, unitsXCnt, unitsYCnt);
					//++skillBasedInteractableObjectIndex;
					initBuildingDoor(doorID, unitsXCnt, unitsYCnt);

					//Remove collidability of tiles in door area
					/*int doorIndex = doorID;
					areaStruct doorGridArea = getGridAreaFromSDLRect(objects[doorIndex].objectDRect);
					for (int doorGridAreaXCnt = doorGridArea.x; doorGridAreaXCnt < doorGridArea.x + doorGridArea.w - 1; ++doorGridAreaXCnt) {
						for (int doorGridAreaYCnt = doorGridArea.y; doorGridAreaYCnt < doorGridArea.y + doorGridArea.h - 1; ++doorGridAreaYCnt) {
							if (1 < (int)overworldGrid.gridTile.size() && doorGridAreaXCnt < (int)overworldGrid.gridTile[overworldGrid.groundLayerIndex + 1].size() && doorGridAreaYCnt < (int)overworldGrid.gridTile[overworldGrid.groundLayerIndex + 1][doorGridAreaXCnt].size()) {
								overworldGrid.gridTile[overworldGrid.groundLayerIndex + 1][doorGridAreaXCnt][doorGridAreaYCnt].collidable = false;
							}
						}
					}*/

					if (currentlyInsideBuilding == false) {

						//Init building
						buildingConstructorVarsStruct buildingConstructorVars;
						vector<int> buildingIndices;
						for (int buildingsCnt = 0; buildingsCnt < (int)buildings.size(); ++buildingsCnt) {
							buildingIndices.push_back(buildings[buildingsCnt].getID());
						}
						buildingConstructorVars.ID = getFreeID(buildingIndices);
						buildingConstructorVars.buildingDoorID = doorID;
						buildingConstructorVars.minFloors = randInt(-10, -1);
						buildingConstructorVars.maxFloors = randInt(0, 10);
						buildingConstructorVars.area = { initialTilePosition.x * tileSize.w, initialTilePosition.y * tileSize.h, (int)cityGrid.units[1][unitsXCnt][unitsYCnt].tiles.size() * tileSize.w, (int)cityGrid.units[1][unitsXCnt][unitsYCnt].tiles[0].size() * tileSize.h };
						Building newBuilding(buildingConstructorVars);
						buildings.push_back(newBuilding);

					}

					++doorID;
				}

			}
		}
	}

	if (currentlyInsideBuilding == true) {

		//Get door closest to door character entered from
		XYStruct doorEnteredFromPosition = { (((int)overworldGrid.gridTile[overworldGrid.groundLayerIndex + 1].size() * tileSize.w) * buildingDoorEntryRelativePosition.x) / 100, (((int)overworldGrid.gridTile[overworldGrid.groundLayerIndex + 1][0].size() * tileSize.h) * buildingDoorEntryRelativePosition.y) / 100 };
		struct doorPositionStruct {
			XYStruct position;
			int distanceFromDoorEnteredFrom;
		};
		vector<doorPositionStruct> doorPositions;
		for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
			if (objects[objectsCnt].getType() == "Door") {
				SDL_Rect objectDRect = objects[objectsCnt].getObjectDRect();

				doorPositions.push_back({ { objectDRect.x, objectDRect.y }, abs(doorEnteredFromPosition.x - objectDRect.x) + abs(doorEnteredFromPosition.y - objectDRect.y) });
			}
		}
		int closestDoorDistanceFromDoorEntered = -1;
		int closestDoorIndex = -1;
		for (int doorPositionsCnt = 0; doorPositionsCnt < (int)doorPositions.size(); ++doorPositionsCnt) {
			if (closestDoorIndex == -1 || closestDoorIndex > -1 && doorPositions[doorPositionsCnt].distanceFromDoorEnteredFrom < closestDoorDistanceFromDoorEntered) {
				closestDoorDistanceFromDoorEntered = doorPositions[doorPositionsCnt].distanceFromDoorEnteredFrom;
				closestDoorIndex = doorPositionsCnt;
			}
		}

		int buildingIndex = getBuildingIndexByDoorID(objects[closestDoorIndex].getID());

		//Reposition characters next to door closest to door character entered from
		for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
			WHStruct characterSpriteTargetSize = characters[charactersCnt].getSpriteTargetSize();

			SDL_Rect objectDRect = objects[closestDoorIndex].getObjectDRect();

			characters[charactersCnt].setPosition({ objectDRect.x, objectDRect.y - characterSpriteTargetSize.h });

			//Move character to the left until he is no longer colliding with a wall or until he leaves the building area
			//If character still colliding with wall, move character to the right until he is no longer colliding with a wall or until he leaves the building area
			directionEnum checkDirection = directionEnum::left;
			XYStruct characterOriginalPosition = characters[charactersCnt].getPosition();
			XYStruct characterPosition = characters[charactersCnt].getPosition();
			while (checkCollisionWithOverworldGrid(getGridAreaFromPixelArea({ characterPosition.x, characterPosition.y, characterSpriteTargetSize.w, characterSpriteTargetSize.h }), characters[charactersCnt].getLayerIndex()) == true) {
				areaStruct buildingArea = buildings[buildingIndex].getArea();
				if (checkDirection == directionEnum::left) {
					if (characterPosition.x - tileSize.w >= buildingArea.x) {
						characterPosition.x -= tileSize.w;
					}
					else {
						checkDirection = directionEnum::right;
						characterPosition = characterOriginalPosition;
					}
				}
				else if (checkDirection == directionEnum::right) {
					if (characterPosition.x + tileSize.w <= buildingArea.x + buildingArea.w - 1) {
						characterPosition.x += tileSize.w;
					}
					else {
						break;
					}
				}
			}
			characters[charactersCnt].setPosition(characterPosition);

		}

	}

	//Define stairs types and positions for all building levels
	//Start at level 0 and define stairs below and above based on stairs in level 0. Don't have to position matching stairs with level 0 right under/above
	//if ((int)stairsPositions.size() == 0) {
	//	struct directionStruct {
	//		startEndStruct startEnd;
	//		int incrementDirection;
	//	};

	//	vector<directionStruct> directions;
	//	if (overworldBuildingEnteredThroughID > -1) {
	//		int buildingIndex = getBuildingIndexByID(overworldBuildingEnteredThroughID);
	//		directions = {
	//			{ { 0, buildings[buildingIndex].minFloors }, -1 },
	//			{ { 0, buildings[buildingIndex].maxFloors }, 1 }
	//		};
	//	}
	//	else {
	//		directions = {
	//			{ { 0, overworldGrid.heightStartEnd.start }, -1 },
	//			{ { 0, overworldGrid.heightStartEnd.end }, 1 }
	//		};
	//	}

	//	for (int directionsCnt = 0; directionsCnt < (int)directions.size(); ++directionsCnt) {
	//		int floorCnt = directions[directionsCnt].startEnd.start;
	//		while (directions[directionsCnt].incrementDirection == -1 && floorCnt >= directions[directionsCnt].startEnd.end || directions[directionsCnt].incrementDirection == 1 && floorCnt <= directions[directionsCnt].startEnd.end) {

	//			printInt(floorCnt);

	//			int previousFloorIndex = (int)stairsPositions.size() - 1;

	//			//Reset previousFloorIndex when starting to build stairs for a new direction
	//			if (directions[directionsCnt].incrementDirection == 1 && floorCnt == 0) {
	//				previousFloorIndex = -1;
	//			}

	//			//Add new floor
	//			stairsPositions.resize((int)stairsPositions.size() + 1);
	//			int currentFloorIndex = (int)stairsPositions.size() - 1;

	//			//Define stairs matching previous floor
	//			if (previousFloorIndex > -1 && (int)stairsPositions.size() > 0) {
	//				for (int stairsPositionsCnt = 0; stairsPositionsCnt < (int)stairsPositions[previousFloorIndex].size(); ++stairsPositionsCnt) {
	//					stairPositionsStruct currentStairPosition;
	//					switch (stairsPositions[previousFloorIndex][stairsPositionsCnt].type) {
	//						case stairPositionsStruct::typeEnum::down: {
	//							currentStairPosition.type = stairPositionsStruct::typeEnum::up;
	//							printStr("up p");
	//							break;
	//						}
	//						case stairPositionsStruct::typeEnum::up: {
	//							currentStairPosition.type = stairPositionsStruct::typeEnum::down;
	//							printStr("down p");
	//							break;
	//						}
	//					}
	//					currentStairPosition.position = stairsPositions[previousFloorIndex][stairsPositionsCnt].position;
	//					stairsPositions[currentFloorIndex].push_back(currentStairPosition);
	//				}
	//			}

	//			runThroughRand(playerSeed, { 0, 0, overworldRegionPosition.x - 0, overworldRegionPosition.y - 0 }, { overworldGrid.heightStartEnd.start, overworldGrid.height }, 0, 1);

	//			//Get stair positions for current floor
	//			if (directions[directionsCnt].incrementDirection == -1 && floorCnt > directions[directionsCnt].startEnd.end || directions[directionsCnt].incrementDirection == 1 && floorCnt < directions[directionsCnt].startEnd.end) {
	//				for (int stairsCnt = 0; stairsCnt < randInt(1, 8); ++stairsCnt) {
	//					stairPositionsStruct currentStairsPosition;
	//					switch (directions[directionsCnt].incrementDirection) {
	//						case -1: {
	//							currentStairsPosition.type = stairPositionsStruct::typeEnum::down;
	//							printStr("down c");
	//							break;
	//						}
	//						case 1: {
	//							currentStairsPosition.type = stairPositionsStruct::typeEnum::up;
	//							printStr("up c");
	//							break;
	//						}
	//					}
	//					currentStairsPosition.position = { randInt(0, (int)overworldGrid.gridTile[overworldGrid.groundLayerIndex + 1].size() * tileSize.w), randInt(0, (int)overworldGrid.gridTile[overworldGrid.groundLayerIndex + 1][0].size() * tileSize.h) };
	//					stairsPositions[currentFloorIndex].push_back(currentStairsPosition);
	//				}
	//			}

	//			floorCnt += directions[directionsCnt].incrementDirection;
	//		}
	//	}
	//}

	//Get indices of stairs objects
	/*vector<int> stairsObjects;
	for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
		if ((int)objects[objectsCnt].type.find("Stairs") > -1) {
			stairsObjects.push_back(objectsCnt);
		}
	}*/

	//Remove all stairs from objects
	/*for (int stairsObjectsCnt = 0; stairsObjectsCnt < (int)stairsObjects.size(); ++stairsObjectsCnt) {
		objects.erase(objects.begin() + stairsObjects[stairsObjectsCnt]);
	}*/

	//Init stairs for current level
	/*for (int stairsPositionsCnt = 0; stairsPositionsCnt < (int)stairsPositions[overworldGrid.height].size(); ++stairsPositionsCnt) {
		Object currentStairs;
		vector<int> IDs;
		for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
			IDs.push_back(objects[objectsCnt].ID);
		}
		currentStairs.ID = getFreeID(IDs);
		currentStairs.layer = 1;

		switch (stairsPositions[overworldGrid.height][stairsPositionsCnt].type) {
			case stairPositionsStruct::typeEnum::down: {
				currentStairs.type = "Stairs (Down)";
				break;
			}
			case stairPositionsStruct::typeEnum::up: {
				currentStairs.type = "Stairs (Up)";
				break;
			}
		}

		currentStairs.objectDRect = { stairsPositions[overworldGrid.height][stairsPositionsCnt].position.x, stairsPositions[overworldGrid.height][stairsPositionsCnt].position.y, tileSize.w * 4, tileSize.h * 4 };

		animationStruct currentAnimation;
		currentAnimation.name = "static";
		currentAnimation.spriteSheetIndex = getSpriteSheetIndex("stairs");

		if (currentStairs.type == "Stairs (Up)") {
			currentAnimation.spritesSRect.push_back({ 0, 0, 32, 32 });
		}
		else if (currentStairs.type == "Stairs (Down)") {
			currentAnimation.spritesSRect.push_back({ 36, 0, 32, 32 });
		}

		currentAnimation.originalPosition = { currentStairs.objectDRect.x, currentStairs.objectDRect.y };
		currentAnimation.spriteDRect = currentStairs.objectDRect;
		currentAnimation.totalLoops = -1;
		currentStairs.stateAnimations.push_back(currentAnimation);

		Object::optionStruct currentOption;
		currentOption.icon.caption = "Use";
		currentOption.requiredStateAnimation = 0;
		if (currentStairs.type == "Stairs (Down)") {
			currentOption.goDown = true;
		}
		else if (currentStairs.type == "Stairs (Up)") {
			currentOption.goUp = true;
		}
		currentStairs.options.push_back(currentOption);

		objects.push_back(currentStairs);
	}*/

	//Init stairs
	bool stairsDownInitiated = false, stairsUpInitiated = false;
	for (int stairsCnt = 0; stairsCnt < 50; ++stairsCnt) {
		objectConstructorVarsStruct objectConstructorVars;

		vector<int> IDs;
		for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
			IDs.push_back(objects[objectsCnt].getID());
		}
		objectConstructorVars.ID = getFreeID(IDs);

		objectConstructorVars.layer = 1;

		if (stairsDownInitiated == true && stairsUpInitiated == true) {
			if (randInt(0, 1) == 0) {
				objectConstructorVars.type = "Stairs (Down)";
			}
			else {
				objectConstructorVars.type = "Stairs (Up)";
			}
		}
		else {

			//Ensure there is always stairs to go up or down within building
			if (stairsDownInitiated == false && overworldGrid.height > overworldGrid.heightStartEnd.start) {
				objectConstructorVars.type = "Stairs (Down)";
				stairsDownInitiated = true;
			}
			else if (stairsUpInitiated == false && overworldGrid.height < overworldGrid.heightStartEnd.end) {
				objectConstructorVars.type = "Stairs (Up)";
				stairsUpInitiated = true;
			}

		}

		WHStruct stairsSize = { tileSize.w * 4, tileSize.h * 4 };
		bool checkCollision = true;
		while (checkCollision == true) {
			XYStruct stairsGridPosition = { randInt(0, (int)overworldGrid.gridTile[overworldGrid.groundLayerIndex + 1].size() - 1), randInt(0, (int)overworldGrid.gridTile[overworldGrid.groundLayerIndex + 1][0].size() - 1) };
			objectConstructorVars.objectDRect = { stairsGridPosition.x * tileSize.w, stairsGridPosition.y * tileSize.h, stairsSize.w, stairsSize.h };

			if (checkCollisionWithOverworldGrid(getGridAreaFromPixelArea(convertSDLRectToArea(objectConstructorVars.objectDRect)), 1) == false) {
				checkCollision = false;
			}
		}

		animationStruct currentAnimation;
		currentAnimation.name = "static";
		currentAnimation.spriteSheetIndex = getSpriteSheetIndex("stairs");

		if (objectConstructorVars.type == "Stairs (Up)") {
			currentAnimation.spritesSRect.push_back({ 0, 0, 32, 32 });
		}
		else if (objectConstructorVars.type == "Stairs (Down)") {
			currentAnimation.spritesSRect.push_back({ 36, 0, 32, 32 });
		}

		currentAnimation.originalPosition = { objectConstructorVars.objectDRect.x, objectConstructorVars.objectDRect.y };
		currentAnimation.spriteDRect = objectConstructorVars.objectDRect;
		currentAnimation.totalLoops = -1;
		objectConstructorVars.stateAnimations.push_back(currentAnimation);

		objectConstructorVarsStruct::optionStruct currentOption;
		currentOption.icon.caption = "Use";
		currentOption.requiredStateAnimation = 0;
		if (objectConstructorVars.type == "Stairs (Down)") {
			currentOption.goDownStairs = true;
		}
		else if (objectConstructorVars.type == "Stairs (Up)") {
			currentOption.goUpStairs = true;
		}
		objectConstructorVars.options.push_back(currentOption);

		Object currentStairs(objectConstructorVars);
		objects.push_back(currentStairs);
	}

}

void saveCreatedObjectToFile(createdObjectStruct currentObject) {
	char fileName[] = "assets\\misc\\created objects.txt";
	fstream myFile(fileName, fstream::in | fstream::out | fstream::app);

	myFile << "object start" << "\n";
	myFile << currentObject.name << "\n";
	myFile << currentObject.pixelArea.x << "\n";
	myFile << currentObject.pixelArea.y << "\n";
	myFile << currentObject.pixelArea.w << "\n";
	myFile << currentObject.pixelArea.h << "\n";
	myFile << currentObject.gridArea.x << "\n";
	myFile << currentObject.gridArea.y << "\n";
	myFile << currentObject.gridArea.w << "\n";
	myFile << currentObject.gridArea.h << "\n";
	myFile << "object end" << "\n";

	myFile.close();

	/*string fileNameAndPath = "assets\\misc\\created objects.txt";
	appendToFile(fileNameAndPath, currentObject.name);
	appendToFile(fileNameAndPath, str(currentObject.pixelArea.x));
	appendToFile(fileNameAndPath, str(currentObject.pixelArea.y));
	appendToFile(fileNameAndPath, str(currentObject.pixelArea.w));
	appendToFile(fileNameAndPath, str(currentObject.pixelArea.h));
	appendToFile(fileNameAndPath, str(currentObject.gridArea.x));
	appendToFile(fileNameAndPath, str(currentObject.gridArea.y));
	appendToFile(fileNameAndPath, str(currentObject.gridArea.w));
	appendToFile(fileNameAndPath, str(currentObject.gridArea.h));*/

	++totalCreatedObjects;
}

createdObjectStruct loadCreatedObjectFromFile(int currentObjectCnt) {
	createdObjectStruct currentCreatedObject;

	int objectCnt = -1;
	string myText;
	ifstream myFile("assets\\misc\\created objects.txt");
	while (getline(myFile, myText)) {
		if (myText == "object start") {
			++objectCnt;
			if (objectCnt == currentObjectCnt) {
				getline(myFile, currentCreatedObject.name);
				getline(myFile, myText);
				currentCreatedObject.pixelArea.x = toInt(myText);
				getline(myFile, myText);
				currentCreatedObject.pixelArea.y = toInt(myText);
				getline(myFile, myText);
				currentCreatedObject.pixelArea.w = toInt(myText);
				getline(myFile, myText);
				currentCreatedObject.pixelArea.h = toInt(myText);
				getline(myFile, myText);
				currentCreatedObject.gridArea.x = toInt(myText);
				getline(myFile, myText);
				currentCreatedObject.gridArea.y = toInt(myText);
				getline(myFile, myText);
				currentCreatedObject.gridArea.w = toInt(myText);
				getline(myFile, myText);
				currentCreatedObject.gridArea.h = toInt(myText);
				break;
			}
		}
	}
	myFile.close();

	return currentCreatedObject;
}

void displayLoadingMessage() {
	setSDLRenderTarget(NULL);
	clearScreen(0, 0, 0, 255);
	string text = "LOADING";
	renderText(text, defaultFont, defaultColour, { tileSize.w, textLogicalSize.h - (getTextSize(text, defaultFont).h * 2) });
	SDL_RenderPresent(renderer);
}

int getDoorIndexByID(int doorID) {
	for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
		if (objects[objectsCnt].getID() == doorID) {
			return objectsCnt;
		}
	}
	return -1;
}

void initRegions() {

	//Set region grid size
	WHStruct regionGridSize = { 500, 500 };
	regionGrid.tiles.clear();
	regionGrid.names.clear();
	regionGrid.tiles.resize(regionGridSize.w);
	regionGrid.names.resize(regionGridSize.w);
	for (int regionGridTilesXCnt = 0; regionGridTilesXCnt < (int)regionGrid.tiles.size(); ++regionGridTilesXCnt) {
		regionGrid.tiles[regionGridTilesXCnt].clear();
		regionGrid.tiles[regionGridTilesXCnt].resize(regionGridSize.h);
		regionGrid.names[regionGridTilesXCnt].clear();
		regionGrid.names[regionGridTilesXCnt].resize(regionGridSize.h);
	}

	//Init region grid
	int totalRegionTypes = 2;
	for (int regionGridTilesXCnt = 0; regionGridTilesXCnt < (int)regionGrid.tiles.size(); ++regionGridTilesXCnt) {
		for (int regionGridTilesYCnt = 0; regionGridTilesYCnt < (int)regionGrid.tiles[regionGridTilesXCnt].size(); ++regionGridTilesYCnt) {
			regionGrid.tiles[regionGridTilesXCnt][regionGridTilesYCnt] = regionTypeEnum(randInt(0, totalRegionTypes - 1));
			regionGrid.names[regionGridTilesXCnt][regionGridTilesYCnt] = "Region " + str(randInt(0, 9));
		}
	}

	//Ensure there is at least one region with region type different than none around each region
	for (int regionGridTilesXCnt = 0; regionGridTilesXCnt < (int)regionGrid.tiles.size(); ++regionGridTilesXCnt) {
		for (int regionGridTilesYCnt = 0; regionGridTilesYCnt < (int)regionGrid.tiles[regionGridTilesXCnt].size(); ++regionGridTilesYCnt) {

			//Check if there is at least one region type different than none around this region
			bool regionDifferentThanNoneFound = false;
			for (int adjacentRegionXCnt = regionGridTilesXCnt - 1; adjacentRegionXCnt <= regionGridTilesXCnt + 1; ++adjacentRegionXCnt) {
				for (int adjacentRegionYCnt = regionGridTilesYCnt - 1; adjacentRegionYCnt <= regionGridTilesYCnt + 1; ++adjacentRegionYCnt) {
					if (areaWithinArea({ adjacentRegionXCnt, adjacentRegionYCnt, adjacentRegionXCnt, adjacentRegionYCnt }, { 0, 0, (int)regionGrid.tiles.size(), (int)regionGrid.tiles[0].size() }) == true) {
						if (adjacentRegionXCnt != regionGridTilesXCnt || adjacentRegionYCnt != regionGridTilesYCnt) {
							if (regionGrid.tiles[adjacentRegionXCnt][adjacentRegionYCnt] != regionTypeEnum::none) {
								regionDifferentThanNoneFound = true;
								goto exitAdjacentRegionCheck;
							}
						}
					}
				}
			}
		exitAdjacentRegionCheck:

			if (regionDifferentThanNoneFound == false) {

				//Randomly place an adjacent region different than none
				bool place = true;
				while (place == true) {
					XYStruct adjacentRegionPosition = { randInt(regionGridTilesXCnt - 1, regionGridTilesXCnt + 1), randInt(regionGridTilesYCnt - 1, regionGridTilesYCnt + 1) };
					if (adjacentRegionPosition.x != regionGridTilesXCnt || adjacentRegionPosition.y != regionGridTilesYCnt) {
						if (adjacentRegionPosition.x >= 0 && adjacentRegionPosition.x <= (int)regionGrid.tiles.size() - 1 && adjacentRegionPosition.y >= 0 && adjacentRegionPosition.y <= (int)regionGrid.tiles[0].size() - 1) {
							regionGrid.tiles[adjacentRegionPosition.x][adjacentRegionPosition.y] = regionTypeEnum(randInt(1, totalRegionTypes - 1));
							place = false;
						}
					}
				}

			}
		}
	}

	//Init region grid camera
	regionGrid.camera = { 0, 0, 10, 10 };

}

bool checkCreatedObjectsCollision(createdObjectStruct currentCreatedObject) {
	for (int createdObjectsCnt = 0; createdObjectsCnt < (int)createdObjects.size(); ++createdObjectsCnt) {

		for (int objectGridXCnt = createdObjects[createdObjectsCnt].gridArea.x; objectGridXCnt < createdObjects[createdObjectsCnt].gridArea.x + createdObjects[createdObjectsCnt].gridArea.w; ++objectGridXCnt) {
			for (int objectGridYCnt = createdObjects[createdObjectsCnt].gridArea.y; objectGridYCnt < createdObjects[createdObjectsCnt].gridArea.y + createdObjects[createdObjectsCnt].gridArea.h; ++objectGridYCnt) {

				for (int currentCreatedObjectGridXCnt = currentCreatedObject.gridArea.x; currentCreatedObjectGridXCnt < currentCreatedObject.gridArea.x + currentCreatedObject.gridArea.w; ++currentCreatedObjectGridXCnt) {
					for (int currentCreatedObjectGridYCnt = currentCreatedObject.gridArea.y; currentCreatedObjectGridYCnt < currentCreatedObject.gridArea.y + currentCreatedObject.gridArea.h; ++currentCreatedObjectGridYCnt) {

						if (objectGridXCnt == currentCreatedObjectGridXCnt && objectGridYCnt == currentCreatedObjectGridYCnt) {
							return true;
						}

					}
				}

			}
		}

	}

	/*for (int createdObjectsCnt = 0; createdObjectsCnt < totalCreatedObjects; ++createdObjectsCnt) {

		createdObjectStruct currentCreatedObject = loadCreatedObjectFromFile(createdObjectsCnt);

		for (int objectGridXCnt = currentCreatedObject.gridArea.x; objectGridXCnt < currentCreatedObject.gridArea.x + currentCreatedObject.gridArea.w; ++objectGridXCnt) {
			for (int objectGridYCnt = currentCreatedObject.gridArea.y; objectGridYCnt < currentCreatedObject.gridArea.y + currentCreatedObject.gridArea.h; ++objectGridYCnt) {

				for (int currentCreatedObjectGridXCnt = currentCreatedObject.gridArea.x; currentCreatedObjectGridXCnt < currentCreatedObject.gridArea.x + currentCreatedObject.gridArea.w; ++currentCreatedObjectGridXCnt) {
					for (int currentCreatedObjectGridYCnt = currentCreatedObject.gridArea.y; currentCreatedObjectGridYCnt < currentCreatedObject.gridArea.y + currentCreatedObject.gridArea.h; ++currentCreatedObjectGridYCnt) {

						if (objectGridXCnt == currentCreatedObjectGridXCnt && objectGridYCnt == currentCreatedObjectGridYCnt) {
							return true;
						}

					}
				}

			}
		}

	}*/

	return false;
}

bool areaWithinGrid(areaStruct gridArea, int gridLayer) {
	if (gridArea.x < 0 || gridArea.x + gridArea.w - 1 >(int)overworldGrid.gridTile[gridLayer].size() - 1 || gridArea.y < 0 || gridArea.y + gridArea.h - 1 >(int)overworldGrid.gridTile[gridLayer][gridArea.x].size() - 1) {
		return false;
	}
	return true;
}

void initGameClock() {
	gameClock.year = randInt(2021, 2030);
	gameClock.month = randInt(1, 12);
	gameClock.day = randInt(1, 31);
	gameClock.hour = randInt(0, 23);
	gameClock.minute = randInt(0, 59);
	gameClock.second = randInt(0, 59);
}

void initCharacters() {

	//Set object collision in overworld grid
	for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
		objects[objectsCnt].setObjectCollision();
	}

	for (int charactersCnt = 0; charactersCnt < 3; ++charactersCnt) {
		characterConstructorVarsStruct characterConstructorVars;

		if ((int)characters.size() > 0) {
			vector<int> characterIndices;
			for (int indexCnt = 0; indexCnt < (int)characters.size(); ++indexCnt) {
				characterIndices.push_back(characters[indexCnt].getID());
			}
			characterConstructorVars.ID = getFreeID(characterIndices);
		}
		else {
			characterConstructorVars.ID = 0;
		}

		characterConstructorVars.layerIndex = 1;

		characterConstructorVars.spriteTargetSize = { tileSize.w * 3, tileSize.h * 4 };

		characterConstructorVars.regionPosition = regionGrid.position;

		//Get character position
		bool getCharacterPosition = true;
		while (getCharacterPosition == true) {
			characterConstructorVars.position = { randInt(0, (int)overworldGrid.gridTile[characterConstructorVars.layerIndex].size() * tileSize.w), randInt(0, (int)overworldGrid.gridTile[characterConstructorVars.layerIndex][0].size() * tileSize.h) };
			characterConstructorVars.position = getGridPosition(characterConstructorVars.position);

			XYStruct characterGridSize = { characterConstructorVars.spriteTargetSize.w, characterConstructorVars.spriteTargetSize.h };
			createdObjectStruct currentCreatedObject = { "character", { characterConstructorVars.position.x, characterConstructorVars.position.y, characterConstructorVars.spriteTargetSize.w, characterConstructorVars.spriteTargetSize.h }, getGridArea(characterConstructorVars.position, characterGridSize) };
			//printIntL({ checkCreatedObjectsCollision(currentCreatedObject) == false, checkOverworldGridCollision(getGridArea(characterConstructorVars.position, characterGridSize), characterConstructorVars.layerIndex) == false });
			if (checkCreatedObjectsCollision(currentCreatedObject) == false && checkCollisionWithOverworldGrid(getGridArea(characterConstructorVars.position, characterGridSize), characterConstructorVars.layerIndex) == false) {
				createdObjects.push_back(currentCreatedObject);
				//saveCreatedObjectToFile(currentCreatedObject);
				getCharacterPosition = false;
			}
			//break;
		}

		//Force character at specific position
		if (charactersCnt > -1) {
			//characterConstructorVars.position = { ((int)overworldGrid.gridTile[characterConstructorVars.layerIndex].size() * tileSize.w) - characterConstructorVars.spriteTargetSize.w - tileSize.w, ((int)overworldGrid.gridTile[characterConstructorVars.layerIndex][0].size() * tileSize.h) - characterConstructorVars.spriteTargetSize.h - tileSize.h }; //for testing region switching

			//characterConstructorVars.position = { 3424, 1884 };

			//Position character next to object
			//string objectType = "Hierarchy Board";
			//int firstMatchingObjectIndex = -1;
			//bool positionFound = false;
			//for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
			//	if ((int)objects[objectsCnt].getType().find(objectType) > -1) {
			//		if (firstMatchingObjectIndex == -1) {
			//			firstMatchingObjectIndex = objectsCnt;
			//		}

			//		SDL_Rect objectDRect = objects[objectsCnt].getObjectDRect();

			//		characterConstructorVars.position = { objectDRect.x, objectDRect.y + objectDRect.h };

			//		//Check that character is within overworld grid and not on wall
			//		if (areaWithinGrid(getGridAreaFromPixelArea({ characterConstructorVars.position.x, characterConstructorVars.position.y, characterConstructorVars.spriteTargetSize.w, characterConstructorVars.spriteTargetSize.h }), characterConstructorVars.layerIndex) == true && checkCollisionWithOverworldGrid(getGridAreaFromPixelArea({ characterConstructorVars.position.x, characterConstructorVars.position.y, characterConstructorVars.spriteTargetSize.w, characterConstructorVars.spriteTargetSize.h }), characterConstructorVars.layerIndex) == false) {
			//			positionFound = true;
			//			break;
			//		}

			//	}
			//}

			//if (positionFound == false && firstMatchingObjectIndex > -1) {

			//	//Set character position to first matching object
			//	SDL_Rect objectDRect = objects[firstMatchingObjectIndex].getObjectDRect();
			//	characterConstructorVars.position = { objectDRect.x, objectDRect.y + objectDRect.h };

			//}
		}

		characterConstructorVars.name = "Name " + str(randInt(0, 9));

		characterConstructorVars.direction = (directionEnum)randInt(0, 7);
		characterConstructorVars.spriteIndex = randInt(0, 1);
		characterConstructorVars.spriteSheetIndex = getSpriteSheetIndex("main character");
		characterConstructorVars.spriteType = characterConstructorVarsStruct::spriteTypeEnum::single;

		vector<vector<areaStruct>> sprites = {
			//Up
			{
				{ 527, 7, 28, 35 },
				{ 559, 7, 28, 35 },
				{ 591, 7, 28, 35 },
				{ 622, 7, 28, 35 }
			},
			//Down
			{
				{ 7, 7, 28, 35 },
				{ 46, 7, 28, 35 },
				{ 78, 7, 28, 35 },
				{ 118, 7, 28, 35 }
			},
			//Left
			{
				{ 147, 162, 28, 35 },
				{ 175, 162, 28, 35 },
				{ 199, 162, 28, 35 },
				{ 229, 162, 28, 35 }
			},
			//Right
			{
				{ 278, 8, 28, 35 },
				{ 302, 8, 28, 35 },
				{ 332, 8, 28, 35 },
				{ 357, 8, 28, 35 }
			},
			//Up Right
			{
				{ 389, 8, 28, 35 },
				{ 422, 8, 28, 35 },
				{ 462, 8, 28, 35 },
				{ 492, 8, 28, 35 }
			},
			//Down Right
			{
				{ 150, 8, 28, 35 },
				{ 181, 8, 28, 35 },
				{ 214, 8, 28, 35 },
				{ 246, 8, 28, 35 }
			},
			//Down Left
			{
				{ 256, 160, 28, 35 },
				{ 291, 160, 28, 35 },
				{ 322, 160, 28, 35 },
				{ 355, 160, 28, 35 }
			},
			//Up Left
			{
				{ 11, 160, 28, 35 },
				{ 42, 160, 28, 35 },
				{ 77, 160, 28, 35 },
				{ 115, 160, 28, 35 }
			}
		};
		characterConstructorVars.sprites = sprites;

		//Init body parts
		const vector<vector<vector<vector<characterConstructorVarsStruct::bodyPartStruct>>>> currentBodyParts = {
			{
				{
					{
						{  }
					}
				}
			}
		};

		//Init Stats
		struct statNameAndDescrStruct {
			string name, description;
		};
		vector<statNameAndDescrStruct> statNames = {
			{ "Life", "Character Hit Points. If reaches 0, character is dead." },
			{ "Stamina", "Consumed by abilities" },
			{ "Energy", "Consumed by cyberwares" },
			{ "Hunger", "Lowers max life if food is not eaten" },
			{ "Thirst", "Lowers max stamina if water is not drunk" }
		};
		for (int statNamesCnt = 0; statNamesCnt < (int)statNames.size(); ++statNamesCnt) {
			characterConstructorVarsStruct::statStruct currentStat;
			currentStat.name = statNames[statNamesCnt].name;
			currentStat.description = statNames[statNamesCnt].description;
			currentStat.current = randInt(50, 100);
			currentStat.modified = 0;
			currentStat.max = randInt(101, 150);
			currentStat.icon = { getSpriteSheetIndex("stats"), randArea({ { 278, 34, 62, 63 }, { 353, 34, 62, 63 } }), "" };
			currentStat.bar.backIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 26, 8, 8 }, { 140, 26, 8, 8 } }), "" };
			currentStat.bar.backIcon.dRect = { 0, 0, 24, 24 };
			currentStat.bar.backIcon.totalIcons = 0;
			currentStat.bar.foreIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 52, 8, 8 }, { 140, 52, 8, 8 } }), "" };
			currentStat.bar.foreIcon.dRect = { 0, 0, 24, 24 };
			currentStat.bar.foreIcon.totalIcons = 0;
			characterConstructorVars.stats.push_back(currentStat);
		}

		//Init Misc
		characterConstructorVars.misc = {
			{ "Race", "Determines starting skills and some interactions with other NPCs", randStringList({ "Human", "AI", "Mutant", "Alien", "Hybrid" }), -1, { getSpriteSheetIndex("misc"), randArea({ { 3, 0, 12, 18 }, { 41, 18, 16, 18 } }), "" } },
			{ "Crypto", "Currency", "", randInt(1000, 2000) }
		};

		//Init Skills
		for (int skillsCnt = 0; skillsCnt < randInt(5, 10); ++skillsCnt) {
			skillStruct currentSkill;
			currentSkill.name = "Skill " + str(randInt(0, 9));
			currentSkill.description = "Description " + str(randInt(0, 9));
			currentSkill.current = randInt(0, 50);
			currentSkill.modified = 0;
			currentSkill.max = randInt(51, 100);
			currentSkill.icon = { getSpriteSheetIndex("skills"), randArea({ { 193, 0, 22, 23 }, { 193, 25, 22, 23 } }), "" };
			currentSkill.experience.min = randInt(0, 100);
			currentSkill.experience.max = randInt(101, 200);
			currentSkill.bar.backIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 26, 8, 8 }, { 140, 26, 8, 8 } }), "" };
			currentSkill.bar.backIcon.dRect = { 0, 0, 24, 24 };
			currentSkill.bar.backIcon.totalIcons = 0;
			currentSkill.bar.foreIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 52, 8, 8 }, { 140, 52, 8, 8 } }), "" };
			currentSkill.bar.foreIcon.dRect = { 0, 0, 24, 24 };
			currentSkill.bar.foreIcon.totalIcons = 0;
			characterConstructorVars.skills.push_back(currentSkill);
		}

		//Init Status effects
		/*for (int statusEffectsCnt = 0; statusEffectsCnt < randInt(5, 10); ++statusEffectsCnt) {
			Character::statusEffectStruct currentStatusEffect;
			vector<int> indices;
			for (int effectsCnt = 0; effectsCnt < (int)characterConstructorVars.statusEffects.size(); ++effectsCnt) {
				indices.push_back(characterConstructorVars.statusEffects[effectsCnt].index);
			}
			currentStatusEffect.index = getFreeID(indices);
			currentStatusEffect.name = "Name " + str(randInt(0, 9));
			currentStatusEffect.modTargetType = randStringList({ "Skill", "Stat" });
			currentStatusEffect.modTargetName = "Name " + str(randInt(0, 9));
			currentStatusEffect.modType = randStringList({ "Damage", "Boost" });
			currentStatusEffect.modValue = randInt(1, 100);
			currentStatusEffect.duration.startTicks = SDL_GetTicks();
			currentStatusEffect.duration.delay = randInt(30, 60) * 1000;
			currentStatusEffect.icon = { getSpriteSheetIndex("status effects"), randArea({ { 46, 13, 89, 49 }, { 1518, 131, 83, 67 } }), "Caption" + str(randInt(0, 9)) };
			currentStatusEffect.bar.backIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 26, 8, 8 }, { 140, 26, 8, 8 } }), "" };
			currentStatusEffect.bar.backIcon.dRect = { 0, 0, 24, 24 };
			currentStatusEffect.bar.backIcon.totalIcons = 0;
			currentStatusEffect.bar.foreIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 52, 8, 8 }, { 140, 52, 8, 8 } }), "" };
			currentStatusEffect.bar.foreIcon.dRect = { 0, 0, 24, 24 };
			currentStatusEffect.bar.foreIcon.totalIcons = 0;
			characterConstructorVars.statusEffects.push_back(currentStatusEffect);
		}*/

		//Init Abilities
		for (int abilitiesCnt = 0; abilitiesCnt < randInt(5, 10); ++abilitiesCnt) {
			characterConstructorVarsStruct::abilityStruct currentAbility;
			vector<int> indices;
			for (int abilityIndicesCnt = 0; abilityIndicesCnt < (int)characterConstructorVars.abilities.size(); ++abilityIndicesCnt) {
				indices.push_back(characterConstructorVars.abilities[abilityIndicesCnt].index);
			}
			currentAbility.index = getFreeID(indices);
			currentAbility.name = "Name " + str(randInt(0, 9));
			currentAbility.description = "Description " + str(randInt(0, 9));
			currentAbility.targetType = randStringList({ "Self", "Enemy", "Object", "Companion" });
			currentAbility.staminaConsumption = randInt(1, 100);
			currentAbility.icon = { getSpriteSheetIndex("abilities"), randArea({ { 47, 1964, 59, 52 }, { 312, 2127, 29, 52 } }), "" };
			for (int statusEffectsCnt = 0; statusEffectsCnt < randInt(5, 10); ++statusEffectsCnt) {
				characterConstructorVarsStruct::statusEffectStruct currentStatusEffect;
				vector<int> indices;
				for (int effectsCnt = 0; effectsCnt < (int)characterConstructorVars.statusEffects.size(); ++effectsCnt) {
					indices.push_back(characterConstructorVars.statusEffects[effectsCnt].index);
				}
				currentStatusEffect.index = getFreeID(indices);
				currentStatusEffect.name = "Name " + str(randInt(0, 9));
				currentStatusEffect.modTargetType = randStringList({ "Skill", "Stat" });
				currentStatusEffect.modTargetName = "Name " + str(randInt(0, 9));
				currentStatusEffect.modType = randStringList({ "Damage", "Boost" });
				currentStatusEffect.modValue = randInt(1, 100);
				currentStatusEffect.duration.startTicks = SDL_GetTicks();
				currentStatusEffect.duration.delay = randInt(30, 60) * 1000;
				currentStatusEffect.icon = { getSpriteSheetIndex("status effects"), randArea({ { 46, 13, 89, 49 }, { 1518, 131, 83, 67 } }), "Caption" + str(randInt(0, 9)) };
				currentStatusEffect.bar.backIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 26, 8, 8 }, { 140, 26, 8, 8 } }), "" };
				currentStatusEffect.bar.backIcon.dRect = { 0, 0, 24, 24 };
				currentStatusEffect.bar.backIcon.totalIcons = 0;
				currentStatusEffect.bar.foreIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 52, 8, 8 }, { 140, 52, 8, 8 } }), "" };
				currentStatusEffect.bar.foreIcon.dRect = { 0, 0, 24, 24 };
				currentStatusEffect.bar.foreIcon.totalIcons = 0;
				currentAbility.statusEffects.push_back(currentStatusEffect);
			}
			currentAbility.source.name = "Ability";
			currentAbility.source.index = -1;
			characterConstructorVars.abilities.push_back(currentAbility);
		}

		//Init ammo
		for (int ammoCnt = 0; ammoCnt < 1; ++ammoCnt) {
			characterConstructorVarsStruct::ammoStruct currentAmmo;
			currentAmmo.name = "Ammo " + randInt(0, 9);
			currentAmmo.quantity = randInt(50, 100);
			currentAmmo.icon.caption = currentAmmo.name;
			currentAmmo.icon.spriteSheetIndex = getSpriteSheetIndex("bullets");
			currentAmmo.icon.spriteSheetArea = randArea({ { 174, 4, 17, 19 }, { 273, 4, 23, 19 } });
			characterConstructorVars.ammos.push_back(currentAmmo);
		}

		//Init Cyberwares
		for (int cyberwaresCnt = 0; cyberwaresCnt < randInt(5, 10); ++cyberwaresCnt) {
			characterConstructorVarsStruct::cyberwareStruct currentCyberware;
			vector<int> indices;
			for (int cyberwareIndicesCnt = 0; cyberwareIndicesCnt < (int)characterConstructorVars.cyberwares.size(); ++cyberwareIndicesCnt) {
				indices.push_back(characterConstructorVars.cyberwares[cyberwareIndicesCnt].index);
			}
			currentCyberware.index = getFreeID(indices);
			currentCyberware.name = "Name " + str(randInt(0, 9));
			currentCyberware.description = "Description " + str(randInt(0, 9));
			currentCyberware.energyConsumptionPerSecond = randInt(1, 10);
			currentCyberware.quantity = randInt(3, 6);
			currentCyberware.icon = { getSpriteSheetIndex("cyberwares"), randArea({ { 11, 2, 276, 139 }, { 14, 144, 279, 197 } }), "" };

			for (int abilitiesCnt = 0; abilitiesCnt < randInt(5, 10); ++abilitiesCnt) {
				characterConstructorVarsStruct::abilityStruct currentAbility;
				currentAbility.name = "Name " + str(randInt(0, 9));
				currentAbility.description = "Description " + str(randInt(0, 9));
				currentAbility.targetType = randStringList({ "Self", "Enemy", "Object", "Companion" });
				currentAbility.staminaConsumption = randInt(1, 100);
				currentAbility.icon = { getSpriteSheetIndex("abilities"), randArea({ { 47, 1964, 59, 52 }, { 312, 2127, 29, 52 } }), "" };
				for (int statusEffectsCnt = 0; statusEffectsCnt < randInt(5, 10); ++statusEffectsCnt) {
					characterConstructorVarsStruct::statusEffectStruct currentStatusEffect;
					vector<int> indices;
					for (int effectsCnt = 0; effectsCnt < (int)characterConstructorVars.statusEffects.size(); ++effectsCnt) {
						indices.push_back(characterConstructorVars.statusEffects[effectsCnt].index);
					}
					currentStatusEffect.index = getFreeID(indices);
					currentStatusEffect.name = "Name " + str(randInt(0, 9));
					currentStatusEffect.modTargetType = randStringList({ "Skill", "Stat" });
					currentStatusEffect.modTargetName = "Name " + str(randInt(0, 9));
					currentStatusEffect.modType = randStringList({ "Damage", "Boost" });
					currentStatusEffect.modValue = randInt(1, 100);
					currentStatusEffect.duration.startTicks = SDL_GetTicks();
					currentStatusEffect.duration.delay = randInt(30, 60) * 1000;
					currentStatusEffect.icon = { getSpriteSheetIndex("status effects"), randArea({ { 46, 13, 89, 49 }, { 1518, 131, 83, 67 } }), "Caption" + str(randInt(0, 9)) };
					currentStatusEffect.bar.backIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 26, 8, 8 }, { 140, 26, 8, 8 } }), "" };
					currentStatusEffect.bar.backIcon.dRect = { 0, 0, 24, 24 };
					currentStatusEffect.bar.backIcon.totalIcons = 0;
					currentStatusEffect.bar.foreIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 52, 8, 8 }, { 140, 52, 8, 8 } }), "" };
					currentStatusEffect.bar.foreIcon.dRect = { 0, 0, 24, 24 };
					currentStatusEffect.bar.foreIcon.totalIcons = 0;
					currentAbility.statusEffects.push_back(currentStatusEffect);
				}
				currentAbility.source.name = "Cyberware";
				currentAbility.source.index = cyberwaresCnt;
				currentCyberware.abilities.push_back(currentAbility);
			}

			characterConstructorVars.cyberwares.push_back(currentCyberware);
		}

		//Init Gear
		for (int gearsCnt = 0; gearsCnt < randInt(5, 10); ++gearsCnt) {
			characterConstructorVarsStruct::gearStruct currentGear;
			vector<int> indices;
			for (int gearIndicesCnt = 0; gearIndicesCnt < (int)characterConstructorVars.gears.size(); ++gearIndicesCnt) {
				indices.push_back(characterConstructorVars.gears[gearIndicesCnt].index);
			}
			currentGear.index = getFreeID(indices);
			currentGear.name = "Name " + str(randInt(0, 9));
			currentGear.description = "Description " + str(randInt(0, 9));
			currentGear.quantity = randInt(3, 6);
			currentGear.icon = { getSpriteSheetIndex("gears"), randArea({ { 1, 2, 29, 28 }, { 34, 2, 29, 28 } }), "" };

			for (int skillsCnt = 0; skillsCnt < randInt(5, 10); ++skillsCnt) {
				characterConstructorVarsStruct::gearStruct::skillStruct currentSkill;
				currentSkill.name = "Name " + str(randInt(0, 9));
				currentSkill.modValue = randInt(1, 10);
				currentSkill.icon = { getSpriteSheetIndex("skills"), randArea({ { 193, 0, 22, 23 }, { 193, 25, 22, 23 } }), "" };
				currentGear.skills.push_back(currentSkill);
			}

			characterConstructorVars.gears.push_back(currentGear);
		}

		//Init Weapons
		for (int weaponsCnt = 0; weaponsCnt < randInt(5, 10); ++weaponsCnt) {
			characterConstructorVarsStruct::weaponStruct currentWeapon;
			vector<int> indices;
			for (int weaponIndicesCnt = 0; weaponIndicesCnt < (int)characterConstructorVars.weapons.size(); ++weaponIndicesCnt) {
				indices.push_back(characterConstructorVars.weapons[weaponIndicesCnt].index);
			}
			currentWeapon.index = getFreeID(indices);
			currentWeapon.name = "Name " + str(randInt(0, 9));
			currentWeapon.description = "Description " + str(randInt(0, 9));
			currentWeapon.quantity = randInt(3, 6);

			currentWeapon.rangeType = "Ranged";
			//currentWeapon.rangeType = "Melee";
			if (currentWeapon.rangeType == "Ranged") {
				currentWeapon.icon = { getSpriteSheetIndex("weapons"), randArea({ { 3, 30, 25, 13 }, { 3, 46, 23, 16 } }), "" };
				currentWeapon.weaponSize = { tileSize.w * 3, tileSize.h * 2 };
				currentWeapon.renderWhenAnimationRunning = true;
			}
			else if (currentWeapon.rangeType == "Melee") {
				currentWeapon.icon = { getSpriteSheetIndex("weapons"), randArea({ { 521, 7, 30, 9 }, { 521, 26, 34, 11 } }), "" };
				currentWeapon.weaponSize = { tileSize.w * 3, tileSize.h * 2 };
				currentWeapon.renderWhenAnimationRunning = false;
			}

			for (int abilitiesCnt = 0; abilitiesCnt < 1; ++abilitiesCnt) {
				characterConstructorVarsStruct::abilityStruct currentAbility;
				currentAbility.name = "Name " + str(randInt(0, 9));
				currentAbility.description = "Description " + str(randInt(0, 9));
				currentAbility.targetType = randStringList({ "Self", "Enemy", "Object", "Companion" });
				currentAbility.staminaConsumption = randInt(1, 5);
				currentAbility.requiredAmmoName = "Ammo 1";
				currentAbility.icon = { getSpriteSheetIndex("abilities"), randArea({ { 47, 1964, 59, 52 }, { 312, 2127, 29, 52 } }), "" };

				for (int statusEffectsCnt = 0; statusEffectsCnt < 1; ++statusEffectsCnt) {
					characterConstructorVarsStruct::statusEffectStruct currentStatusEffect;
					vector<int> indices;
					for (int effectsCnt = 0; effectsCnt < (int)characterConstructorVars.statusEffects.size(); ++effectsCnt) {
						indices.push_back(characterConstructorVars.statusEffects[effectsCnt].index);
					}
					currentStatusEffect.index = getFreeID(indices);
					currentStatusEffect.name = "Name " + str(randInt(0, 9));
					currentStatusEffect.modTargetType = randStringList({ "Skill", "Stat" });
					currentStatusEffect.modTargetName = "Name " + str(randInt(0, 9));
					currentStatusEffect.modType = randStringList({ "Damage", "Boost" });
					currentStatusEffect.modValue = randInt(1, 100);
					currentStatusEffect.duration.startTicks = SDL_GetTicks();
					currentStatusEffect.duration.delay = 3000;
					currentStatusEffect.icon = { getSpriteSheetIndex("status effects"), randArea({ { 46, 13, 89, 49 }, { 1518, 131, 83, 67 } }), "Caption" + str(randInt(0, 9)) };
					currentStatusEffect.bar.backIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 26, 8, 8 }, { 140, 26, 8, 8 } }), "" };
					currentStatusEffect.bar.backIcon.dRect = { 0, 0, 24, 24 };
					currentStatusEffect.bar.backIcon.totalIcons = 0;
					currentStatusEffect.bar.foreIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 52, 8, 8 }, { 140, 52, 8, 8 } }), "" };
					currentStatusEffect.bar.foreIcon.dRect = { 0, 0, 24, 24 };
					currentStatusEffect.bar.foreIcon.totalIcons = 0;

					if (randInt(0, 1) == 0) {
						currentStatusEffect.cumulativeType.createAdditionalEffect = true;
					}
					else {
						currentStatusEffect.cumulativeType.addToExistingEffect = true;
						switch (randInt(0, 2)) {
						case 0: {
							currentStatusEffect.cumulativeType.addToModValue = true;
							break;
						}
						case 1: {
							currentStatusEffect.cumulativeType.addToDuration = true;
							break;
						}
						case 2: {
							currentStatusEffect.cumulativeType.addToModValue = true;
							currentStatusEffect.cumulativeType.addToDuration = true;
							break;
						}
						}
					}
					currentStatusEffect.cumulativeType.numberOfTimesToAdd = randInt(-1, 10);
					currentStatusEffect.applicationFrequency.delay = randInt(1, 5) * 1000;

					currentStatusEffect.animation.spriteSheetIndex = getSpriteSheetIndex("status effects");
					currentStatusEffect.animation.spriteIndex = 0;
					currentStatusEffect.animation.delay = 1;
					currentStatusEffect.animation.spritesSRect = {
						{ 283, 262, 72, 59 },
						{ 355, 262, 72, 59 },
						{ 425, 262, 72, 59 }
					};
					currentStatusEffect.animation.type = "Effect";

					currentAbility.statusEffects.push_back(currentStatusEffect);
				}

				currentAbility.source.name = "Weapon";
				currentAbility.source.index = weaponsCnt;

				animationStruct currentAnimation;
				if (currentWeapon.rangeType == "Melee") {
					currentAnimation.spriteSheetIndex = currentWeapon.icon.spriteSheetIndex;
					currentAnimation.spritesSRect.push_back(convertAreaToSDLRect(currentWeapon.icon.spriteSheetArea));
					currentAnimation.pixelIncrement = tileSize.w;
				}
				else if (currentWeapon.rangeType == "Ranged") {
					currentAnimation.spriteSheetIndex = getSpriteSheetIndex("bullets");
					currentAnimation.spritesSRect.push_back({ 343, 212, 17, 15 });
					currentAnimation.pixelIncrement = tileSize.w;
					currentAnimation.spriteDRect = { currentWeapon.position.x, currentWeapon.position.y, tileSize.w * 2, tileSize.h * 2 };
				}
				currentAnimation.spriteIndex = 0;
				currentAnimation.type = currentWeapon.rangeType;
				currentAnimation.delay = 1;
				currentAbility.animations.push_back(currentAnimation);

				currentWeapon.abilities.push_back(currentAbility);
			}

			characterConstructorVars.weapons.push_back(currentWeapon);
		}

		//Init Consumable Items
		for (int consumableItemsCnt = 0; consumableItemsCnt < randInt(60, 80); ++consumableItemsCnt) {
			characterConstructorVarsStruct::consumableItemStruct currentConsumableItem;
			vector<int> indices;
			for (int consumableItemIndicesCnt = 0; consumableItemIndicesCnt < (int)characterConstructorVars.consumableItems.size(); ++consumableItemIndicesCnt) {
				indices.push_back(characterConstructorVars.consumableItems[consumableItemIndicesCnt].index);
			}
			currentConsumableItem.index = getFreeID(indices);
			currentConsumableItem.name = "Name " + str(randInt(0, 9));
			currentConsumableItem.description = "Description " + str(randInt(0, 9));
			currentConsumableItem.quantity = randInt(3, 6);
			currentConsumableItem.icon = { getSpriteSheetIndex("consumable items"), randArea({ { 32, 45, 23, 21 }, { 56, 44, 26, 23 } }), "" };

			for (int statusEffectsCnt = 0; statusEffectsCnt < randInt(5, 10); ++statusEffectsCnt) {
				characterConstructorVarsStruct::statusEffectStruct currentStatusEffect;
				vector<int> indices;
				for (int effectsCnt = 0; effectsCnt < (int)characterConstructorVars.statusEffects.size(); ++effectsCnt) {
					indices.push_back(characterConstructorVars.statusEffects[effectsCnt].index);
				}
				currentStatusEffect.index = getFreeID(indices);
				currentStatusEffect.name = "Name " + str(randInt(0, 9));
				currentStatusEffect.modTargetType = randStringList({ "Skill", "Stat" });
				currentStatusEffect.modTargetName = "Name " + str(randInt(0, 9));
				currentStatusEffect.modType = randStringList({ "Damage", "Boost" });
				currentStatusEffect.modValue = randInt(1, 100);
				currentStatusEffect.duration.startTicks = SDL_GetTicks();
				currentStatusEffect.duration.delay = randInt(30, 60) * 1000;
				currentStatusEffect.icon = { getSpriteSheetIndex("status effects"), randArea({ { 46, 13, 89, 49 }, { 1518, 131, 83, 67 } }), "Caption" + str(randInt(0, 9)) };
				currentStatusEffect.bar.backIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 26, 8, 8 }, { 140, 26, 8, 8 } }), "" };
				currentStatusEffect.bar.backIcon.dRect = { 0, 0, 24, 24 };
				currentStatusEffect.bar.backIcon.totalIcons = 0;
				currentStatusEffect.bar.foreIcon.icon = { getSpriteSheetIndex("stats"), randArea({ { 127, 52, 8, 8 }, { 140, 52, 8, 8 } }), "" };
				currentStatusEffect.bar.foreIcon.dRect = { 0, 0, 24, 24 };
				currentStatusEffect.bar.foreIcon.totalIcons = 0;
				currentConsumableItem.statusEffects.push_back(currentStatusEffect);
			}

			characterConstructorVars.consumableItems.push_back(currentConsumableItem);
		}

		//Init misc items
		for (int miscItemsCnt = 0; miscItemsCnt < randInt(5, 10); ++miscItemsCnt) {
			miscItemsStruct currentMiscItem;
			currentMiscItem.name = "Name " + str(randInt(0, 9));
			currentMiscItem.description = "Description " + str(randInt(0, 9));
			currentMiscItem.quantity = randInt(3, 6);
			currentMiscItem.icon = { getSpriteSheetIndex("misc items"), randArea({ { 0, 1, 26, 24 }, { 33, 0, 25, 26 } }), "" };
			characterConstructorVars.miscItems.push_back(currentMiscItem);
		}

		//Init crafting items
		for (int craftingItemsCnt = 0; craftingItemsCnt < randInt(10, 20); ++craftingItemsCnt) {
			miscItemsStruct currentCraftingItem;
			currentCraftingItem.name = "Item " + str(randInt(0, 9));
			currentCraftingItem.description = "Description " + str(randInt(0, 9));
			currentCraftingItem.quantity = randInt(10, 20);
			currentCraftingItem.icon.spriteSheetIndex = getSpriteSheetIndex("crafting items");
			currentCraftingItem.icon.spriteSheetArea = randArea({ { 0, 0, 16, 17 }, { 16, 0, 15, 15 } });
			characterConstructorVars.craftingItems.push_back(currentCraftingItem);
		}

		//Init blueprints
		for (int blueprintsCnt = 0; blueprintsCnt < randInt(5, 10); ++blueprintsCnt) {
			blueprintStruct currentBlueprint;
			currentBlueprint.blueprint.name = "Blueprint " + str(randInt(0, 9));
			currentBlueprint.blueprint.description = "Description " + str(randInt(0, 9));
			currentBlueprint.blueprint.quantity = randInt(1, 5);
			currentBlueprint.blueprint.icon.spriteSheetIndex = getSpriteSheetIndex("blueprints");
			currentBlueprint.blueprint.icon.spriteSheetArea = randArea({ { 0, 0, 32, 47 }, { 35, 0, 32, 47 } });
			currentBlueprint.blueprint.icon.caption = currentBlueprint.blueprint.name;
			for (int requiredMiscItemsCnt = 0; requiredMiscItemsCnt < 3; ++requiredMiscItemsCnt) {
				currentBlueprint.requiredMiscItems.push_back(characterConstructorVars.craftingItems[randInt(0, (int)characterConstructorVars.craftingItems.size() - 1)]);

				int requiredMiscItemIndex = (int)currentBlueprint.requiredMiscItems.size() - 1;
				currentBlueprint.requiredMiscItems[requiredMiscItemIndex].quantity = randInt(1, currentBlueprint.requiredMiscItems[requiredMiscItemIndex].quantity);
			}
			characterConstructorVars.blueprints.push_back(currentBlueprint);
		}

		//Init quickslots
		iconStruct icon;
		vector<characterConstructorVarsStruct::quickslotsStruct> currentQuickslots = {
			{ "", "A", -1, icon },
			{ "", "B", -1, icon },
			{ "", "X", -1, icon },
			{ "", "Y", -1, icon },
			{ "", "LB", -1, icon },
			{ "", "RB", -1, icon },
			{ "", "LT", -1, icon },
			{ "", "RT", -1, icon },
			{ "", "up", -1, icon },
			{ "", "down", -1, icon },
			{ "", "left", -1, icon },
			{ "", "right", -1, icon }
		};
		characterConstructorVars.quickslots = currentQuickslots;

		//Init cyberware equipment slots
		for (int slotsCnt = 0; slotsCnt < randInt(3, 10); ++slotsCnt) {
			characterConstructorVars.cyberwareEquipmentSlots.push_back({ "", -1 });
		}

		//Init gear equipment slots
		for (int slotsCnt = 0; slotsCnt < randInt(3, 10); ++slotsCnt) {
			characterConstructorVars.gearEquipmentSlots.push_back({ "", -1 });
		}

		//Init weapon equipment slots
		for (int slotsCnt = 0; slotsCnt < randInt(3, 10); ++slotsCnt) {
			characterConstructorVars.weaponEquipmentSlots.push_back({ "", -1 });
		}

		//Init schedule
		characterConstructorScheduleVarsStruct currentCharacterConstructorScheduleVars;
		//for (int schedulesCnt = 0; schedulesCnt < randInt(1, 3); ++schedulesCnt) {
		//	characterConstructorScheduleVarsStruct::scheduleStruct currentSchedule;
		//	
		//	timeStruct taskStartTime = gameClock;
		//	for (int tasksCnt = 0; tasksCnt < randInt(5, 10); ++tasksCnt) {
		//		characterConstructorScheduleVarsStruct::scheduleStruct::taskStruct currentTask;
		//		
		//		timeStruct addedTime;
		//		/*addedTime.year = randInt(0, 3);
		//		addedTime.month = randInt(0, 12);
		//		addedTime.day = randInt(0, 31);
		//		addedTime.hour = randInt(0, 24);
		//		addedTime.minute = randInt(0, 60);
		//		addedTime.second = randInt(0, 60);*/
		//		currentTask.startTime = taskStartTime;

		//		/*addedTime.year = randInt(0, 3);
		//		addedTime.month = randInt(0, 12);
		//		addedTime.day = randInt(0, 31);
		//		addedTime.hour = randInt(0, 24);
		//		addedTime.minute = randInt(0, 60);
		//		addedTime.second = randInt(0, 60);*/
		//		addedTime.second = 5;
		//		currentTask.endTime = addTime(currentTask.startTime, addedTime);

		//		taskStartTime = currentTask.endTime;

		//		currentTask.name = "Task " + str(randInt(0, 9));
		//		currentTask.goal = randStringList({ "Sleep", "Eat" });

		//		currentSchedule.tasks.push_back(currentTask);
		//	}

		//	currentSchedule.currentTask = randInt(0, (int)currentSchedule.tasks.size() - 1);

		//	currentCharacterConstructorScheduleVars.schedules.push_back(currentSchedule);
		//}
		//currentCharacterConstructorScheduleVars.currentSchedule = randInt(0, (int)currentCharacterConstructorScheduleVars.schedules.size() - 1);


		//Have two tasks
		scheduleStruct currentSchedule;

		scheduleStruct::taskStruct task1;
		task1.name = "Name " + str(randInt(0, 9));
		task1.goal = "Follow controlled character";
		task1.startTime = gameClock;
		timeStruct addedTime1;
		addedTime1.hour = 12;
		task1.endTime = addTime(task1.startTime, addedTime1);
		currentSchedule.tasks.push_back(task1);

		scheduleStruct::taskStruct task2;
		task2.name = "Name " + str(randInt(0, 9));
		task2.goal = "Follow controlled character";
		task2.startTime = task1.endTime;
		timeStruct addedTime2;
		addedTime2.hour = 12;
		task2.endTime = addTime(task2.startTime, addedTime2);

		currentSchedule.tasks.push_back(task1);
		currentSchedule.tasks.push_back(task2);

		currentCharacterConstructorScheduleVars.schedules.push_back(currentSchedule);


		//Init sleep
		characterConstructorVars.sleep.spriteSheetIndex = getSpriteSheetIndex("main character");
		characterConstructorVars.sleep.spriteSRect = { 508, 93, 37, 37 };

		Character currentCharacter(characterConstructorVars, currentCharacterConstructorScheduleVars);
		characters.push_back(currentCharacter);
	}

	//Modify building door variables for testing
	//for (int buildingDoorsCnt = 0; buildingDoorsCnt < (int)skillBasedInteractableObjects.size(); ++buildingDoorsCnt) {
	//	if (skillBasedInteractableObjects[buildingDoorsCnt].type == "Building Door") {

	//		//Modify building door skills required to match that of controlled character so can open door for testing
	//		for (int doorRequiredSkillsCnt = 0; doorRequiredSkillsCnt < (int)skillBasedInteractableObjects[buildingDoorsCnt].skillsRequired.size(); ++doorRequiredSkillsCnt) {
	//			skillBasedInteractableObjects[buildingDoorsCnt].skillsRequired[doorRequiredSkillsCnt] = characters[controlledCharacterIndex].skills[randInt(0, (int)characters[controlledCharacterIndex].skills.size() - 1)];
	//		}

	//		//Set building door misc items required to same as controlled character's for testing opening door
	//		for (int miscItemsRequiredCnt = 0; miscItemsRequiredCnt < randInt(3, 6); ++miscItemsRequiredCnt) {
	//			skillBasedInteractableObjects[buildingDoorsCnt].miscItemsRequired.push_back(characters[controlledCharacterIndex].miscItems[randInt(0, (int)characters[controlledCharacterIndex].miscItems.size() - 1)]);
	//		}

	//	}
	//}

	//Insert all skills and misc items required to interact with all options in all objects into controlled character's stats - for testing
	//for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
	//	vector<objectConstructorVarsStruct::optionStruct> objectOptions = objects[objectsCnt].getOptions();

	//	for (int objectOptionsCnt = 0; objectOptionsCnt < (int)objectOptions.size(); ++objectOptionsCnt) {

	//		//Insert required skills
	//		for (int requiredSkillsCnt = 0; requiredSkillsCnt < (int)objectOptions[objectOptionsCnt].requiredSkills.size(); ++requiredSkillsCnt) {

	//			//If skill already in character skills then update skill stats else add skill
	//			bool skillFound = false;
	//			for (int characterSkillsCnt = 0; characterSkillsCnt < (int)characters[controlledCharacterIndex].skills.size(); ++characterSkillsCnt) {
	//				if (characters[controlledCharacterIndex].skills[characterSkillsCnt].name == objectOptions[objectOptionsCnt].requiredSkills[requiredSkillsCnt].name) {
	//					skillFound = true;
	//					characters[controlledCharacterIndex].skills[characterSkillsCnt].current += objectOptions[objectOptionsCnt].requiredSkills[requiredSkillsCnt].current;
	//					characters[controlledCharacterIndex].skills[characterSkillsCnt].modified += objectOptions[objectOptionsCnt].requiredSkills[requiredSkillsCnt].modified;
	//					characters[controlledCharacterIndex].skills[characterSkillsCnt].max += objectOptions[objectOptionsCnt].requiredSkills[requiredSkillsCnt].max;
	//					break;
	//				}
	//			}
	//			if (skillFound == false) {
	//				characters[controlledCharacterIndex].skills.push_back(objectOptions[objectOptionsCnt].requiredSkills[requiredSkillsCnt]);
	//			}

	//		}

	//		//Insert required misc items
	//		for (int requiredMiscItemsCnt = 0; requiredMiscItemsCnt < (int)objectOptions[objectOptionsCnt].requiredMiscItems.size(); ++requiredMiscItemsCnt) {

	//			//If misc item already in character inventory then update quantity else add misc item
	//			bool miscItemFound = false;
	//			for (int characterMiscItemsCnt = 0; characterMiscItemsCnt < (int)characters[controlledCharacterIndex].miscItems.size(); ++characterMiscItemsCnt) {
	//				vector<objectConstructorVarsStruct::optionStruct> objectOptions = objects[objectsCnt].getOptions();

	//				if (characters[controlledCharacterIndex].miscItems[characterMiscItemsCnt].name == objectOptions[objectOptionsCnt].requiredMiscItems[requiredMiscItemsCnt].name) {
	//					miscItemFound = true;
	//					characters[controlledCharacterIndex].miscItems[characterMiscItemsCnt].quantity += objectOptions[objectOptionsCnt].requiredMiscItems[requiredMiscItemsCnt].quantity;
	//					break;
	//				}
	//			}
	//			if (miscItemFound == false) {
	//				characters[controlledCharacterIndex].miscItems.push_back(objectOptions[objectOptionsCnt].requiredMiscItems[requiredMiscItemsCnt]);
	//			}

	//		}

	//	}
	//}

}

//gridTiles: layer, x, y
WHStruct renderMap(vector<vector<vector<bool>>> gridTiles, string mapName, SDL_Texture* mapTexture, WHStruct mapSize) {

	//Init map tiles
	tileStruct collidable, nonCollidable, character;
	collidable.spriteSheetIndex = getSpriteSheetIndex("map");
	collidable.tileName = "collidable";
	collidable.spriteSheetArea = { 0, 0, 11, 11 };
	nonCollidable.spriteSheetIndex = getSpriteSheetIndex("map");
	nonCollidable.tileName = "non-collidable";
	nonCollidable.spriteSheetArea = { 13, 0, 11, 11 };
	character.spriteSheetIndex = getSpriteSheetIndex("map");
	character.tileName = "character";
	character.spriteSheetArea = { 26, 0, 11, 11 };

	setSDLRenderTarget(mapTexture);

	//Render map
	WHStruct gridScaleSize = { lround((float)(int)gridTiles[0].size() / (mapSize.w / tileSize.w)), lround((float)(int)gridTiles[0][0].size() / (mapSize.h / tileSize.h)) };
	XYStruct mapTilePosition = { 0, 0 };
	int totalCharactersChecked = 0;
	vector<SDL_Rect> characterMapPositions;
	for (int gridTilesLayerCnt = 0; gridTilesLayerCnt < (int)gridTiles.size(); ++gridTilesLayerCnt) {
		mapTilePosition.x = 0;
		for (int gridTilesXCnt = 0; gridTilesXCnt < (int)gridTiles[gridTilesLayerCnt].size(); gridTilesXCnt += gridScaleSize.w) {
			mapTilePosition.y = 0;
			for (int gridTilesYCnt = 0; gridTilesYCnt < (int)gridTiles[gridTilesLayerCnt][gridTilesXCnt].size(); gridTilesYCnt += gridScaleSize.h) {

				dRect = { mapTilePosition.x, mapTilePosition.y, tileSize.w, tileSize.h };

				//Check tiles around coordinates and get majority if collidable or not
				int collidableCnt = 0, nonCollidableCnt = 0;
				for (int tilesXCnt = gridTilesXCnt; tilesXCnt < gridTilesXCnt + gridScaleSize.w; ++tilesXCnt) {
					for (int tilesYCnt = gridTilesYCnt; tilesYCnt < gridTilesYCnt + gridScaleSize.h; ++tilesYCnt) {

						//Get tile collidability
						if (gridTilesLayerCnt < (int)gridTiles.size() && tilesXCnt < (int)gridTiles[gridTilesLayerCnt].size() && tilesYCnt < (int)gridTiles[gridTilesLayerCnt][tilesXCnt].size()) {
							if (gridTiles[gridTilesLayerCnt][tilesXCnt][tilesYCnt] == true) {
								++collidableCnt;
							}
							else {
								++nonCollidableCnt;
							}
						}

						//Get where characters in party are located on map
						/*if (totalCharactersChecked < (int)characters.size()) {
							for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
								XYUnsignedIntStruct characterGridPosition;
								if (mapName == "local") {
									XYStruct gridPosition = getGridPosition(characters[charactersCnt].position);
									characterGridPosition = { (unsigned int)gridPosition.x, (unsigned int)gridPosition.y };
								}
								else if (mapName == "region") {
									characterGridPosition = characters[charactersCnt].regionPosition;
								}
								if (characterGridPosition.x == tilesXCnt && characterGridPosition.y == tilesYCnt) {
									++totalCharactersChecked;
									characterMapPositions.push_back(dRect);
									break;
								}
							}
						}*/

					}
				}

				//Render map tile
				if (collidableCnt > nonCollidableCnt) {
					sRect = convertAreaToSDLRect(collidable.spriteSheetArea);
					SDL_RenderCopy(renderer, spriteSheets[collidable.spriteSheetIndex].texture, &sRect, &dRect);
				}
				else {
					sRect = convertAreaToSDLRect(nonCollidable.spriteSheetArea);
					SDL_RenderCopy(renderer, spriteSheets[nonCollidable.spriteSheetIndex].texture, &sRect, &dRect);
				}

				mapTilePosition.y += dRect.h;
			}
			mapTilePosition.x += dRect.w;
		}
	}

	//Render character map tiles
	/*if ((int)characterMapPositions.size() > 0) {
		for (int characterMapPositionsCnt = 0; characterMapPositionsCnt < (int)characterMapPositions.size(); ++characterMapPositionsCnt) {
			sRect = convertAreaToSDLRect(character.spriteSheetArea);
			SDL_RenderCopy(renderer, spriteSheets[character.spriteSheetIndex].texture, &sRect, &characterMapPositions[characterMapPositionsCnt]);
		}
	}*/

	return gridScaleSize;
}

void destroyMaps() {
	for (int mapsCnt = 0; mapsCnt < (int)maps.size(); ++mapsCnt) {
		if (maps[mapsCnt].texture != NULL) {
			SDL_DestroyTexture(maps[mapsCnt].texture);
			maps[mapsCnt].texture = NULL;
		}
	}
	maps.clear();
}

void initMaps() {

	//Init maps
	const vector<string> mapNames = { "local", "region", "mini" };
	for (int mapNamesCnt = 0; mapNamesCnt < (int)mapNames.size(); ++mapNamesCnt) {

		mapConstructorVarsStruct mapConstructorVars;

		vector<int> IDs;
		for (int mapsCnt = 0; mapsCnt < (int)maps.size(); ++mapsCnt) {
			IDs.push_back(maps[mapsCnt].getID());
		}
		mapConstructorVars.ID = getFreeID(IDs);

		mapConstructorVars.name = mapNames[mapNamesCnt];

		//Get grid tiles
		vector<vector<vector<bool>>> gridTiles;
		WHStruct mapSize = { -1, -1 };
		if (getStringIndex({ "local", "mini" }, mapConstructorVars.name) > -1) {
			gridTiles.resize(overworldGrid.gridTile.size());
			for (int overworldGridLayerCnt = 0; overworldGridLayerCnt < (int)overworldGrid.gridTile.size(); ++overworldGridLayerCnt) {
				gridTiles[overworldGridLayerCnt].resize((int)overworldGrid.gridTile[overworldGridLayerCnt].size());
				for (int overworldGridTilesXCnt = 0; overworldGridTilesXCnt < (int)overworldGrid.gridTile[overworldGridLayerCnt].size(); ++overworldGridTilesXCnt) {
					gridTiles[overworldGridLayerCnt][overworldGridTilesXCnt].resize((int)overworldGrid.gridTile[overworldGridLayerCnt][overworldGridTilesXCnt].size());
					for (int overworldGridTilesYCnt = 0; overworldGridTilesYCnt < (int)overworldGrid.gridTile[overworldGridLayerCnt][overworldGridTilesXCnt].size(); ++overworldGridTilesYCnt) {
						gridTiles[overworldGridLayerCnt][overworldGridTilesXCnt][overworldGridTilesYCnt] = overworldGrid.gridTile[overworldGridLayerCnt][overworldGridTilesXCnt][overworldGridTilesYCnt].collidable;
					}
				}
			}
			mapSize = textLogicalSize;
		}
		else if (mapConstructorVars.name == "region") {
			gridTiles.resize(1);
			for (int regionGridTilesLayersCnt = 0; regionGridTilesLayersCnt < (int)gridTiles.size(); ++regionGridTilesLayersCnt) {
				gridTiles[regionGridTilesLayersCnt].resize((int)regionGrid.tiles.size());
				for (int regionGridTilesXCnt = 0; regionGridTilesXCnt < (int)regionGrid.tiles.size(); ++regionGridTilesXCnt) {
					gridTiles[regionGridTilesLayersCnt][regionGridTilesXCnt].resize((int)regionGrid.tiles[regionGridTilesXCnt].size());
					for (int regionGridTilesYCnt = 0; regionGridTilesYCnt < (int)regionGrid.tiles[regionGridTilesXCnt].size(); ++regionGridTilesYCnt) {
						if (regionGrid.tiles[regionGridTilesXCnt][regionGridTilesYCnt] != regionTypeEnum::none) {
							gridTiles[regionGridTilesLayersCnt][regionGridTilesXCnt][regionGridTilesYCnt] = true;
						}
						else {
							gridTiles[regionGridTilesLayersCnt][regionGridTilesXCnt][regionGridTilesYCnt] = false;
						}
					}
				}
			}
			mapSize = textLogicalSize;
		}

		mapConstructorVars.texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mapSize.w, mapSize.h);

		//Set texture camera size
		if (getStringIndex({ "local", "region" }, mapConstructorVars.name) > -1) {
			WHStruct textureSize = getSDLTextureSize(mapConstructorVars.texture);
			mapConstructorVars.textureSRect = { 0, 0, textureSize.w, textureSize.h };
			mapConstructorVars.textureDRect = mapConstructorVars.textureSRect;
		}
		else if (mapConstructorVars.name == "mini") {
			mapConstructorVars.textureSRect = { -1, -1, tileSize.w * 20, tileSize.h * 20 };
			mapConstructorVars.textureDRect = { textLogicalSize.w - (textLogicalSize.w / 4), 0, textLogicalSize.w / 4, textLogicalSize.h / 4 };
			mapConstructorVars.sRectRelativeToControllerCharacter = true;
			mapConstructorVars.alwaysDisplayMap = true;
		}

		mapConstructorVars.gridScaleSize = renderMap(gridTiles, mapConstructorVars.name, mapConstructorVars.texture, mapSize);

		Map currentMap(mapConstructorVars);
		maps.push_back(currentMap);
	}
}

void initController() {
	int totalJoysticks = SDL_NumJoysticks();
	if (controller == NULL && totalJoysticks > 0) {
		controller = SDL_JoystickOpen(0);
		controllerID = SDL_JoystickInstanceID(controller);

		//Init controller button icons
		controllerButtonIcons = {
			{ getSpriteSheetIndex("controller buttons"), { 254, 193, 60, 60 }, "X" },
			{ getSpriteSheetIndex("controller buttons"), { 333, 193, 63, 59 }, "Y" },
			{ getSpriteSheetIndex("controller buttons"), { 90, 194, 60, 57 }, "A" },
			{ getSpriteSheetIndex("controller buttons"), { 171, 193, 59, 59 }, "B" },
			{ getSpriteSheetIndex("controller buttons"), { 29, 199, 20, 17 }, "dPadUp" },
			{ getSpriteSheetIndex("controller buttons"), { 29, 229, 20, 17 }, "dPadDown" },
			{ getSpriteSheetIndex("controller buttons"), { 15, 212, 17, 21 }, "dPadLeft" },
			{ getSpriteSheetIndex("controller buttons"), { 46, 211, 17, 22 }, "dPadRight" },
			{ getSpriteSheetIndex("controller buttons"), { 368, 59, 69, 48 }, "LB" },
			{ getSpriteSheetIndex("controller buttons"), { 450, 58, 69, 49 }, "RB" },
			{ getSpriteSheetIndex("controller buttons"), { 214, 51, 52, 62 }, "LT" },
			{ getSpriteSheetIndex("controller buttons"), { 296, 51, 50, 63 }, "RT" },
			{ getSpriteSheetIndex("controller buttons"), { 497, 190, 60, 63 }, "select" },
			{ getSpriteSheetIndex("controller buttons"), { 416, 192, 59, 62 }, "start" },
			{ getSpriteSheetIndex("controller buttons"), { 58, 62, 38, 53 }, "LStick" },
			{ getSpriteSheetIndex("controller buttons"), { 139, 62, 38, 52 }, "RStick" }
		};

	}
	else if (totalJoysticks == 0) {
		SDL_JoystickClose(controller);
		controller = NULL;
	}
}

void getEvent() {
	initController();
	if (deactivateEvent.startTicks > 0 && SDL_GetTicks() - deactivateEvent.startTicks >= deactivateEvent.delay / FPSTimerMod) {
		deactivateEvent.startTicks = 0;
	}
	while (SDL_PollEvent(&event) != 0 && deactivateEvent.startTicks == 0) {
		switch (event.type) {
		case SDL_QUIT:
			exitMainLoop = true;
			break;
		case SDL_JOYAXISMOTION:
			//printf("controller %d, axis %d, value %d\n", event.jaxis.which, event.jaxis.axis, event.jaxis.value);
			//Motion on controller 0
			//if (event.jaxis.which == 0)
			//{
				//Left stick X axis motion
			if (event.jaxis.axis == 0)
			{
				//Left of dead zone
				joystickAxisX = event.jaxis.value;
				if (event.jaxis.value < -deadZone)
				{
					xDir = -1; //left
				}
				//Right of dead zone
				else if (event.jaxis.value > deadZone)
				{
					xDir = 1; //right
				}
				else
				{
					xDir = 0;
				}
			}
			//Left stick Y axis motion
			else if (event.jaxis.axis == 1)
			{
				//Below of dead zone
				joystickAxisY = event.jaxis.value;
				if (event.jaxis.value < -deadZone)
				{
					yDir = -1; //up
				}
				//Above of dead zone
				else if (event.jaxis.value > deadZone)
				{
					yDir = 1; //down
				}
				else
				{
					yDir = 0;
				}
			}
			else if (event.jaxis.axis == 3) {

				//Right stick Y axis motion
				rightJoystickAxisY = event.jaxis.value;
				if (event.jaxis.value < -deadZone)
				{
					rightStickYDir = -1; //left
				}
				else if (event.jaxis.value > deadZone)
				{
					rightStickYDir = 1; //right
				}
				else
				{
					rightStickYDir = 0;
				}

			}
			else if (event.jaxis.axis == 4) {

				//Right stick X axis motion
				rightJoystickAxisX = event.jaxis.value;
				if (event.jaxis.value < -deadZone)
				{
					rightStickXDir = -1; //up
				}
				else if (event.jaxis.value > deadZone)
				{
					rightStickXDir = 1; //down
				}
				else
				{
					rightStickXDir = 0;
				}
				/*rightStickXDir: = -1: up, = 1: down
				rightStickYDir: = -1: left, = 1: right*/
			}
			else if (event.jaxis.axis == 2) {

				//Left trigger
				if (event.jaxis.value > triggerDeadzone) {
					/*if (leftTrigger.pressedStartTicks == 0 || (leftTrigger.pressedStartTicks > 0 && SDL_GetTicks() - leftTrigger.pressedStartTicks >= leftTrigger.pressedDelay)) {
						leftTrigger.activated = true;
						if (leftTrigger.pressedStartTicks > 0) {
							leftTrigger.pressedStartTicks = 0;
						}
						else {
							leftTrigger.pressedStartTicks = SDL_GetTicks();
						}
					}*/
					if (leftTrigger.pressedStartTicks == 0) {
						leftTrigger.pressedStartTicks = SDL_GetTicks();
						leftTrigger.activated = true;
					}
					else if (SDL_GetTicks() - leftTrigger.pressedStartTicks >= leftTrigger.pressedDelay) {
						leftTrigger.pressedStartTicks = 0;
						leftTrigger.activated = false;
					}
					leftTrigger.axisVal = event.jaxis.value;
				}
				else {
					leftTrigger.activated = false;
					leftTrigger.axisVal = 0;
					leftTrigger.pressedStartTicks = 0;
				}

			}
			else if (event.jaxis.axis == 5) {

				//Right trigger
				if (event.jaxis.value > triggerDeadzone) {
					//printf("%d, %d\n", rightTrigger.pressedStartTicks == 0, rightTrigger.pressedStartTicks > 0 && SDL_GetTicks() - rightTrigger.pressedStartTicks >= rightTrigger.pressedDelay);
					/*if (rightTrigger.pressedStartTicks == 0 || (rightTrigger.pressedStartTicks > 0 && SDL_GetTicks() - rightTrigger.pressedStartTicks >= rightTrigger.pressedDelay)) {
						rightTrigger.activated = true;
						if (rightTrigger.pressedStartTicks > 0) {
							rightTrigger.pressedStartTicks = 0;
						}
						else {
							rightTrigger.pressedStartTicks = SDL_GetTicks();
						}
					}*/
					if (rightTrigger.pressedStartTicks == 0) {
						rightTrigger.pressedStartTicks = SDL_GetTicks();
						rightTrigger.activated = true;
					}
					else if (SDL_GetTicks() - rightTrigger.pressedStartTicks >= rightTrigger.pressedDelay) {
						rightTrigger.pressedStartTicks = 0;
						rightTrigger.activated = false;
					}
					rightTrigger.axisVal = event.jaxis.value;
				}
				else {
					rightTrigger.activated = false;
					rightTrigger.axisVal = 0;
					rightTrigger.pressedStartTicks = 0;
				}

			}
			//printf("xDir: %d, yDir: %d, rightStickXDir: %d, rightStickYDir: %d\n", xDir, yDir, rightStickXDir, rightStickYDir);
		//}
			break;
		case SDL_JOYBUTTONDOWN:
			//printf("controller %d\n", event.jbutton.button);
			if (event.jbutton.button == 0) {
				controllerButtons.A = true;
				controllerButtonPressedDuration.A = 0;
				controllerButtonStartTicks.A = SDL_GetTicks();
			}
			if (event.jbutton.button == 1) {
				controllerButtons.B = true;
				controllerButtonPressedDuration.B = 0;
				controllerButtonStartTicks.B = SDL_GetTicks();
			}
			if (event.jbutton.button == 2) {
				controllerButtons.X = true;
				controllerButtonPressedDuration.X = 0;
				controllerButtonStartTicks.X = SDL_GetTicks();
			}
			if (event.jbutton.button == 3) {
				controllerButtons.Y = true;
				controllerButtonPressedDuration.Y = 0;
				controllerButtonStartTicks.Y = SDL_GetTicks();
			}
			if (event.jbutton.button == 4) {
				controllerButtons.LB = true;
				controllerButtonPressedDuration.LB = 0;
				controllerButtonStartTicks.LB = SDL_GetTicks();
			}
			if (event.jbutton.button == 5) {
				controllerButtons.RB = true;
				controllerButtonPressedDuration.RB = 0;
				controllerButtonStartTicks.RB = SDL_GetTicks();
			}
			if (event.jbutton.button == 6) {
				controllerButtons.select = true;
				controllerButtonPressedDuration.select = 0;
				controllerButtonStartTicks.select = SDL_GetTicks();
			}
			if (event.jbutton.button == 7) {
				controllerButtons.start = true;
				controllerButtonPressedDuration.start = 0;
				controllerButtonStartTicks.start = SDL_GetTicks();
			}
			if (event.jbutton.button == 8) {
				controllerButtons.LJ = true;
				controllerButtonPressedDuration.LJ = 0;
				controllerButtonStartTicks.LJ = SDL_GetTicks();
			}
			if (event.jbutton.button == 9) {
				controllerButtons.RJ = true;
				controllerButtonPressedDuration.RJ = 0;
				controllerButtonStartTicks.RJ = SDL_GetTicks();
			}
			break;
		case SDL_JOYBUTTONUP:
			if (event.jbutton.button == 0) {
				controllerButtons.A = false;
				//if (inMenu == false && characterMenuOn == false) {
				controllerButtonPressedDuration.A = SDL_GetTicks() - controllerButtonStartTicks.A;
				//}
				controllerButtonStartTicks.A = 0;
			}
			if (event.jbutton.button == 1) {
				controllerButtons.B = false;
				//if (inMenu == false && characterMenuOn == false) {
				controllerButtonPressedDuration.B = SDL_GetTicks() - controllerButtonStartTicks.B;
				//}
				controllerButtonStartTicks.B = 0;
			}
			if (event.jbutton.button == 2) {
				controllerButtons.X = false;
				//if (inMenu == false && characterMenuOn == false) {
				controllerButtonPressedDuration.X = SDL_GetTicks() - controllerButtonStartTicks.X;
				//}
				controllerButtonStartTicks.X = 0;
			}
			if (event.jbutton.button == 3) {
				controllerButtons.Y = false;
				//if (inMenu == false && characterMenuOn == false) {
				controllerButtonPressedDuration.Y = SDL_GetTicks() - controllerButtonStartTicks.Y;
				//}
				controllerButtonStartTicks.Y = 0;
			}
			if (event.jbutton.button == 4) {
				controllerButtons.LB = false;
				//if (inMenu == false && characterMenuOn == false) {
				controllerButtonPressedDuration.LB = SDL_GetTicks() - controllerButtonStartTicks.LB;
				//}
				controllerButtonStartTicks.LB = 0;
			}
			if (event.jbutton.button == 5) {
				controllerButtons.RB = false;
				//if (inMenu == false && characterMenuOn == false) {
				controllerButtonPressedDuration.RB = SDL_GetTicks() - controllerButtonStartTicks.RB;
				//}
				controllerButtonStartTicks.RB = 0;
			}
			if (event.jbutton.button == 6) {
				controllerButtons.select = false;
				//if (inMenu == false && characterMenuOn == false) {
				controllerButtonPressedDuration.select = SDL_GetTicks() - controllerButtonStartTicks.select;
				//}
				controllerButtonStartTicks.select = 0;
			}
			if (event.jbutton.button == 7) {
				controllerButtons.start = false;
				//if (inMenu == false && characterMenuOn == false) {
				controllerButtonPressedDuration.start = SDL_GetTicks() - controllerButtonStartTicks.start;
				//}
				controllerButtonStartTicks.start = 0;
			}
			if (event.jbutton.button == 8) {
				controllerButtons.LJ = false;
				//if (inMenu == false && characterMenuOn == false) {
				controllerButtonPressedDuration.LJ = SDL_GetTicks() - controllerButtonStartTicks.LJ;
				//}
				controllerButtonStartTicks.LJ = 0;
			}
			if (event.jbutton.button == 9) {
				controllerButtons.RJ = false;
				//if (inMenu == false && characterMenuOn == false) {
				controllerButtonPressedDuration.RJ = SDL_GetTicks() - controllerButtonStartTicks.RJ;
				//}
				controllerButtonStartTicks.RJ = 0;
			}
			break;
		case SDL_JOYHATMOTION:
			/*system("CLS");
			printf("hat %d\n", event.jhat.value);*/
			hatButtons.centered = false;
			//if (event.jhat.value & SDL_HAT_CENTERED) {
			if (event.jhat.value == 0) {
				hatButtons.centered = true;

				hatButtons.up = false;
				hatButtonsPressedDuration.up = SDL_GetTicks() - hatButtonsStartTicks.up;
				hatButtonsStartTicks.up = 0;

				hatButtons.right = false;
				hatButtonsPressedDuration.right = SDL_GetTicks() - hatButtonsStartTicks.right;
				hatButtonsStartTicks.right = 0;

				hatButtons.rightUp = false;
				hatButtonsPressedDuration.rightUp = SDL_GetTicks() - hatButtonsStartTicks.rightUp;
				hatButtonsStartTicks.rightUp = 0;

				hatButtons.down = false;
				hatButtonsPressedDuration.down = SDL_GetTicks() - hatButtonsStartTicks.down;
				hatButtonsStartTicks.down = 0;

				hatButtons.rightDown = false;
				hatButtonsPressedDuration.rightDown = SDL_GetTicks() - hatButtonsStartTicks.rightDown;
				hatButtonsStartTicks.rightDown = 0;

				hatButtons.left = false;
				hatButtonsPressedDuration.left = SDL_GetTicks() - hatButtonsStartTicks.left;
				hatButtonsStartTicks.left = 0;

				hatButtons.leftUp = false;
				hatButtonsPressedDuration.leftUp = SDL_GetTicks() - hatButtonsStartTicks.leftUp;
				hatButtonsStartTicks.leftUp = 0;

				hatButtons.leftDown = false;
				hatButtonsPressedDuration.leftDown = SDL_GetTicks() - hatButtonsStartTicks.leftDown;
				hatButtonsStartTicks.leftDown = 0;

			}
			if (event.jhat.value & SDL_HAT_UP) {
				hatButtons.up = true;
				hatButtonsPressedDuration.up = 0;
				hatButtonsStartTicks.up = SDL_GetTicks();
			}
			if (event.jhat.value & SDL_HAT_RIGHT) {
				hatButtons.right = true;
				hatButtonsPressedDuration.right = 0;
				hatButtonsStartTicks.right = SDL_GetTicks();
			}
			if (event.jhat.value & SDL_HAT_RIGHTUP) {
				hatButtons.rightUp = true;
				hatButtonsPressedDuration.rightUp = 0;
				hatButtonsStartTicks.rightUp = SDL_GetTicks();
			}
			if (event.jhat.value & SDL_HAT_DOWN) {
				hatButtons.down = true;
				hatButtonsPressedDuration.down = 0;
				hatButtonsStartTicks.down = SDL_GetTicks();
			}
			if (event.jhat.value & SDL_HAT_RIGHTDOWN) {
				hatButtons.rightDown = true;
				hatButtonsPressedDuration.rightDown = 0;
				hatButtonsStartTicks.rightDown = SDL_GetTicks();
			}
			if (event.jhat.value & SDL_HAT_LEFT) {
				hatButtons.left = true;
				hatButtonsPressedDuration.left = 0;
				hatButtonsStartTicks.left = SDL_GetTicks();
			}
			if (event.jhat.value & SDL_HAT_LEFTUP) {
				hatButtons.leftUp = true;
				hatButtonsPressedDuration.leftUp = 0;
				hatButtonsStartTicks.leftUp = SDL_GetTicks();
			}
			if (event.jhat.value & SDL_HAT_LEFTDOWN) {
				hatButtons.leftDown = true;
				hatButtonsPressedDuration.leftDown = 0;
				hatButtonsStartTicks.leftDown = SDL_GetTicks();
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				/*case SDLK_t:
					if (showCollisionTiles == false) {
						showCollisionTiles = true;
					}
					else {
						showCollisionTiles = false;
					}
					break;*/
			case SDLK_c: {
				cKeyPressed = true;

				//Show controlled character pixel and tile coordinates
				/*printf("%d\n", lround(1.625));
				printf("%d\n", lround((float)13 / 8));*/
				/*int characterX = characters[controlledCharacterIndex].x;
				int characterY = characters[controlledCharacterIndex].y;
				int characterDirection = characters[controlledCharacterIndex].direction;
				int characterSpriteTurn = characters[controlledCharacterIndex].spriteTurn;
				int characterW = characters[controlledCharacterIndex].directionData[characterDirection].sprites[characterSpriteTurn].tilesetW;
				int characterH = characters[controlledCharacterIndex].directionData[characterDirection].sprites[characterSpriteTurn].tilesetH;
				int characterTileX = lround((float)characterX / tileSize);
				int characterTileY = lround((float)characterY / tileSize);
				int characterTileW = lround((float)characterW / tileSize);
				int characterTileH = lround((float)characterH / tileSize);
				for (int characterTileXCnt = characterTileX; characterTileXCnt <= characterTileX + characterTileW - 1; ++characterTileXCnt) {
					for (int characterTileYCnt = characterTileY; characterTileYCnt <= characterTileY + characterTileH - 1; ++characterTileYCnt) {
						printf("tile x: %d, tile y: %d, tile w: %d, tile h: %d, pixel x: %d, pixel y: %d, pixel w: %d, pixel h: %d\n", characterTileXCnt, characterTileYCnt, characterTileW, characterTileH, characterTileXCnt * tileSize, characterTileYCnt * tileSize, characterW, characterH);
					}
				}*/

				XYStruct characterPosition = characters[controlledCharacterIndex].getPosition();
				printIntL({ characterPosition.x, characterPosition.y });

				break;
			}
			case SDLK_x:
				exitMainLoop = true;
				break;
			case SDLK_f:
				if (fullscreen == false) {
					fullscreen = true;
				}
				else {
					fullscreen = false;
				}
				destroyWindowAndRenderer();
				initWindowAndRenderer();
				initSpriteSheets();
				destroyMaps();
				initMaps();
				break;
			case SDLK_RIGHT:
				xDir = 1;
				break;
			case SDLK_LEFT:
				xDir = -1;
				break;
			case SDLK_UP:
				yDir = -1;
				break;
			case SDLK_DOWN:
				yDir = 1;
				break;
			case SDLK_RETURN:
				returnKeyPressed = true;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_RIGHT:
				xDir = 0;
				break;
			case SDLK_LEFT:
				xDir = 0;
				break;
			case SDLK_UP:
				yDir = 0;
				break;
			case SDLK_DOWN:
				yDir = 0;
				break;
			case SDLK_RETURN:
				returnKeyPressed = false;
				break;
			case SDLK_c:
				cKeyPressed = false;
				break;
			}
		}
	}
}

void pressAToContinue() {
	bool exitLoop = false;
	while (exitLoop == false) {
		setSDLRenderTarget(NULL);
		clearScreen(0, 0, 0, 255);
		string text = "Press A to continue";
		renderText(text, defaultFont, defaultColour, { tileSize.w, textLogicalSize.h - (getTextSize(text, defaultFont).h * 2) });
		SDL_RenderPresent(renderer);
		getEvent();
		if (controllerButtons.A == true) {
			controllerButtons.A = false;
			return;
		}
	}
}

void pause() {
	bool exitLoop = false;
	while (exitLoop == false) {
		getEvent();
		if (returnKeyPressed == true) {
			returnKeyPressed = false;
			return;
		}
	}
}

void initCraftingStations() {
	int overworldGridObjectLayerIndex = overworldGrid.groundLayerIndex + 1;
	for (int craftingStationCnt = 0; craftingStationCnt < randInt(20, 40); ++craftingStationCnt) {
		objectConstructorVarsStruct objectConstructorVars;

		vector<int> objectIDs;
		for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
			objectIDs.push_back(objects[objectsCnt].getID());
		}
		objectConstructorVars.ID = getFreeID(objectIDs);

		objectConstructorVars.layer = overworldGridObjectLayerIndex;
		objectConstructorVars.type = "Crafting Station";

		objectConstructorVars.objectDRect = { randInt(0, (int)overworldGrid.gridTile[overworldGridObjectLayerIndex].size() - 1) * tileSize.w, randInt(0, (int)overworldGrid.gridTile[overworldGridObjectLayerIndex][0].size() - 1) * tileSize.h, tileSize.w * 4, tileSize.h * 4 };

		animationStruct currentStateAnimation;
		currentStateAnimation.spriteSheetIndex = getSpriteSheetIndex("crafting station");
		currentStateAnimation.spritesSRect.push_back({ 0, 0, 32, 32 });
		currentStateAnimation.spriteDRect = objectConstructorVars.objectDRect;
		objectConstructorVars.stateAnimations.push_back(currentStateAnimation);

		objectConstructorVarsStruct::optionStruct currentOption;
		currentOption.icon = blankIcon;
		currentOption.icon.caption = "Use";
		currentOption.requiredStateAnimation = 0;
		currentOption.craftingType = "Cyberware";
		objectConstructorVars.options.push_back(currentOption);

		Object currentCraftingStation(objectConstructorVars);
		objects.push_back(currentCraftingStation);
	}
}

void initBeds(int overworldGridLayer) {
	objectConstructorVarsStruct currentObjectConstructorVars;

	for (int bedsCnt = 0; bedsCnt < randInt(5, 10); ++bedsCnt) {
		vector<int> objectIDs;
		for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
			objectIDs.push_back(objects[objectsCnt].getID());
		}
		currentObjectConstructorVars.ID = getFreeID(objectIDs);
		currentObjectConstructorVars.layer = overworldGridLayer;
		currentObjectConstructorVars.type = "Bed";

		//Position bed into area on overworld grid that does not have collidable tiles
		WHStruct bedSize = { tileSize.w * 4, tileSize.h * 4 };
		WHStruct bedGridSize = getGridSize(bedSize);
		bool defineBedPosition = true;
		while (defineBedPosition == true) {
			currentObjectConstructorVars.objectDRect = { randInt(0, (int)overworldGrid.gridTile[currentObjectConstructorVars.layer].size() - 1) * tileSize.w, randInt(0, (int)overworldGrid.gridTile[currentObjectConstructorVars.layer][0].size() - 1) * tileSize.h, bedSize.w, bedSize.h };
			
			if (checkCollisionWithOverworldGrid(getGridAreaFromSDLRect(currentObjectConstructorVars.objectDRect), overworldGridLayer) == false) {
				defineBedPosition = false;
			}
		}

		animationStruct currentStateAnimation;
		currentStateAnimation.name = "Animation " + str(randInt(0, 9));
		currentStateAnimation.spriteSheetIndex = getSpriteSheetIndex("bed");
		currentStateAnimation.spritesSRect.push_back({ 0, 0, 32, 32 });
		currentStateAnimation.spriteDRect = currentObjectConstructorVars.objectDRect;
		currentObjectConstructorVars.stateAnimations.push_back(currentStateAnimation);

		objectConstructorVarsStruct::optionStruct currentOption;
		currentOption.icon = blankIcon;
		currentOption.icon.caption = "Sleep";
		currentOption.requiredStateAnimation = 0;
		currentOption.canSleep = true;
		currentObjectConstructorVars.options.push_back(currentOption);

		Object bed(currentObjectConstructorVars);
		objects.push_back(bed);
	}
}

void initLevel() {
	displayLoadingMessage();

	//Run through rand
	runThroughRand(playerSeed, { 0, 0, regionGrid.position.x - 0, regionGrid.position.y - 0 }, { overworldGrid.heightStartEnd.start, overworldGrid.height }, regionGrid.position, 0, 0, 1);

	if (currentlyInsideBuilding == true) {

		//Run through rand for controlled character position
		XYStruct characterPosition = characters[controlledCharacterIndex].getPosition();
		runThroughRand(playerSeed, { (unsigned int)overworldDoorEnteredThroughArea.x / tileSize.w, (unsigned int)overworldDoorEnteredThroughArea.y / tileSize.h, (unsigned int)overworldDoorEnteredThroughArea.w / tileSize.w, (unsigned int)overworldDoorEnteredThroughArea.h / tileSize.h }, { overworldGrid.heightStartEnd.start, overworldGrid.height }, { (unsigned int)characterPosition.x, (unsigned int)characterPosition.y }, characters[controlledCharacterIndex].getLayerIndex(), 0, 1);

	}

	//SNES res: 256 x 224
	//SNES aspect ratio: 8:7

	//Set aspect ratio factor
	aspectRatio.factor = 224 / aspectRatio.ratio.h;

	//Init camera
	camera.area = { 0, 0, aspectRatio.ratio.w * aspectRatio.factor, aspectRatio.ratio.h * aspectRatio.factor };

	//Init overworld grid camera
	overworldGrid.camera = { 0, 0, roundDiv(camera.area.w, tileSize.w), roundDiv(camera.area.h, tileSize.h) };

	//Init overworld grid
	overworldGrid.gridTile.resize(0); //Empty overworld grid
	int gridSizeFactor = 10; //determines grid actual size, defines the size of the level
	int totalLayers = 2;
	int gridWidth = roundDiv((aspectRatio.ratio.w * 25), tileSize.w) * gridSizeFactor; //based on SNES
	int gridHeight = roundDiv((aspectRatio.ratio.h * 25), tileSize.w) * gridSizeFactor;
	overworldGrid.gridTile.resize(totalLayers);
	for (int layersCnt = 0; layersCnt < totalLayers; ++layersCnt) {
		overworldGrid.gridTile[layersCnt].resize(gridWidth);
		for (int gridXCnt = 0; gridXCnt < (int)overworldGrid.gridTile[layersCnt].size(); ++gridXCnt) {
			overworldGrid.gridTile[layersCnt][gridXCnt].resize(gridHeight);
		}
	}
	overworldGrid.groundLayerIndex = 0;
	//printStr(formatStr("overworld grid size: {} x {}, layers: {}", { str((int)overworldGrid.gridTile[0].size()), str((int)overworldGrid.gridTile[0][0].size()), str((int)overworldGrid.gridTile.size()) }));

	//Floor
	for (int gridXCnt = 0; gridXCnt < (int)overworldGrid.gridTile[overworldGrid.groundLayerIndex].size(); ++gridXCnt) {
		for (int gridYCnt = 0; gridYCnt < (int)overworldGrid.gridTile[overworldGrid.groundLayerIndex][gridXCnt].size(); ++gridYCnt) {
			overworldGrid.gridTile[overworldGrid.groundLayerIndex][gridXCnt][gridYCnt] = { getTileIndex("concrete floor"), false };
		}
	}

	//Create walls
	//for (int wallsCnt = 0; wallsCnt < randInt(10, 20); ++wallsCnt) {
	//	/*int gridXCnt = randInt(0, (int)overworldGrid.gridTile[1].size());
	//	int gridYCnt = randInt(0, (int)overworldGrid.gridTile[1][0].size());*/
	//	int gridXCnt = randInt(0, overworldGrid.camera.w);
	//	int gridYCnt = randInt(0, overworldGrid.camera.h);
	//	overworldGrid.gridTile[1][gridXCnt][gridYCnt] = { getTileIndex("wall"), true };
	//}

	initCityGrid();

	//Enter solid tiles in createdObjects
	//vector<int> layersWithSolidObjects = { 1 };
	//for (int layersWithSolidObjectsCnt = 0; layersWithSolidObjectsCnt < (int)layersWithSolidObjects.size(); ++layersWithSolidObjectsCnt) {
	//	for (int tileXCnt = 0; tileXCnt < (int)overworldGrid.gridTile[layersWithSolidObjectsCnt].size(); ++tileXCnt) {
	//		for (int tileYCnt = 0; tileYCnt < (int)overworldGrid.gridTile[layersWithSolidObjectsCnt][tileXCnt].size(); ++tileYCnt) {
	//			if (overworldGrid.gridTile[layersWithSolidObjects[layersWithSolidObjectsCnt]][tileXCnt][tileYCnt].collidable == true) {
	//				areaStruct tileGridArea = getGridArea({ tileXCnt * tileSize.w, tileYCnt * tileSize.h }, { tileSize.w, tileSize.h });
	//				//createdObjects.push_back({ "solid tiles", { tileXCnt * tileSize.w, tileYCnt * tileSize.h, tileSize.w, tileSize.h }, tileGridArea });
	//				saveCreatedObjectToFile({ "solid tiles", { tileXCnt * tileSize.w, tileYCnt * tileSize.h, tileSize.w, tileSize.h }, tileGridArea });
	//			}
	//		}
	//	}
	//}

	//Init objects
	initCraftingStations();
	initBeds(1);

	initGameClock();
	initCharacters();

	destroyMaps();
	initMaps();
}

void initCraftingTable(vector<craftingItemDataStruct>& craftingTable, vector<miscItemsStruct> characterMiscItems, vector<miscItemsStruct> characterCraftingItems, vector<characterConstructorVarsStruct::cyberwareStruct> characterCyberwares, vector<characterConstructorVarsStruct::gearStruct> characterGears, vector<characterConstructorVarsStruct::weaponStruct> characterWeapons, vector<characterConstructorVarsStruct::consumableItemStruct> characterConsumableItems, vector<characterConstructorVarsStruct::ammoStruct> characterAmmos) {

	//Insert random crafting items from controlled character - for testing
	for (int craftingTableLineCnt = 0; craftingTableLineCnt < randInt(50, 100); ++craftingTableLineCnt) {
		craftingItemDataStruct currentCraftingTableLine;

		//Insert required items
		for (int requiredItemsCnt = 0; requiredItemsCnt < 3; ++requiredItemsCnt) {
			craftingItemDataStruct::requiredItemsStruct currentRequiredItem;
			int currentRequiredItemIndex = randInt(0, (int)characterCraftingItems.size() - 1);
			currentRequiredItem.name = characterCraftingItems[currentRequiredItemIndex].name;
			currentRequiredItem.quantityRequired = randInt(1, characterCraftingItems[currentRequiredItemIndex].quantity);
			currentCraftingTableLine.requiredItems.push_back(currentRequiredItem);
		}

		//Insert resulting item
		const string resultingItemTypes[7] = { "Misc", "Crafting", "Cyberware", "Gear", "Weapon", "Consumable", "Ammo" };
		currentCraftingTableLine.resultingItem.type = resultingItemTypes[randInt(0, 6)];
		if (currentCraftingTableLine.resultingItem.type == "Misc") {
			currentCraftingTableLine.resultingItem.miscItem = characterMiscItems[randInt(0, (int)characterMiscItems.size() - 1)];
			currentCraftingTableLine.resultingItem.miscItem.quantity = 1;
		}
		else if (currentCraftingTableLine.resultingItem.type == "Crafting") {
			currentCraftingTableLine.resultingItem.craftingItem = characterCraftingItems[randInt(0, (int)characterCraftingItems.size() - 1)];
			currentCraftingTableLine.resultingItem.craftingItem.quantity = 1;
		}
		else if (currentCraftingTableLine.resultingItem.type == "Cyberware") {
			currentCraftingTableLine.resultingItem.cyberware = characterCyberwares[randInt(0, (int)characterCyberwares.size() - 1)];
			currentCraftingTableLine.resultingItem.cyberware.quantity = 1;
		}
		else if (currentCraftingTableLine.resultingItem.type == "Gear") {
			currentCraftingTableLine.resultingItem.gear = characterGears[randInt(0, (int)characterGears.size() - 1)];
			currentCraftingTableLine.resultingItem.gear.quantity = 1;
		}
		else if (currentCraftingTableLine.resultingItem.type == "Weapon") {
			currentCraftingTableLine.resultingItem.weapon = characterWeapons[randInt(0, (int)characterWeapons.size() - 1)];
			currentCraftingTableLine.resultingItem.weapon.quantity = 1;
		}
		else if (currentCraftingTableLine.resultingItem.type == "Consumable") {
			currentCraftingTableLine.resultingItem.consumableItem = characterConsumableItems[randInt(0, (int)characterConsumableItems.size() - 1)];
			currentCraftingTableLine.resultingItem.consumableItem.quantity = 1;
		}
		else if (currentCraftingTableLine.resultingItem.type == "Ammo") {
			currentCraftingTableLine.resultingItem.ammo = characterAmmos[randInt(0, (int)characterAmmos.size() - 1)];
			currentCraftingTableLine.resultingItem.ammo.quantity = 1;
		}

		//Insert blueprint
		currentCraftingTableLine.blueprint.blueprint.name = "Blueprint " + str(randInt(0, 9));
		currentCraftingTableLine.blueprint.blueprint.description = "Description " + str(randInt(0, 9));
		currentCraftingTableLine.blueprint.blueprint.quantity = 1;
		currentCraftingTableLine.blueprint.blueprint.icon.caption = currentCraftingTableLine.blueprint.blueprint.name;
		currentCraftingTableLine.blueprint.blueprint.icon.spriteSheetIndex = getSpriteSheetIndex("blueprints");
		currentCraftingTableLine.blueprint.blueprint.icon.spriteSheetArea = randArea({ { 0, 0, 32, 47 }, { 35, 0, 32, 47 } });

		craftingTable.push_back(currentCraftingTableLine);
	}

}

void initOrganisations() {
	for (int organisationsCnt = 0; organisationsCnt < randInt(3, 5); ++organisationsCnt) {
		/*printStr("");
		printStr("organisation " + str(organisationsCnt));*/
		organisationConstructorVarsStruct organisationConstructorVars;

		vector<int> organisationIndices;
		for (int organisationsCnt = 0; organisationsCnt < (int)organisations.size(); ++organisationsCnt) {
			organisationIndices.push_back(organisations[organisationsCnt].getID());
		}
		organisationConstructorVars.ID = getFreeID(organisationIndices);

		organisationConstructorVars.name = "Organisation " + str(organisationsCnt);
		organisationConstructorVars.type = "Type " + str(randInt(0, 9));
		organisationConstructorVars.goal = "Goal " + str(randInt(0, 9));

		//Init hierarchy
		vector<vector<int>> roleIDs;
		int roleIDCnt = 0;
		for (int layersCnt = 0; layersCnt < randInt(1, 5); ++layersCnt) {
			//printStr("layer " + str(layersCnt));
			vector<organisationConstructorVarsStruct::rolePositionStruct> layer;

			vector<int> layerRoleIDs;

			for (int rolesCnt = 0; rolesCnt < randInt(1, 20); ++rolesCnt) {
				//printStr("role " + str(rolesCnt));
				organisationConstructorVarsStruct::rolePositionStruct role;

				role.ID = roleIDCnt;
				role.name = randStringList({ "Boss", "Team Leader", "Team Member" });
				role.goal = "Goal " + str(randInt(0, 9));
				role.characterID = randInt(0, (int)characters.size() - 1);
				role.icon.caption = role.name;
				role.icon.spriteSheetIndex = getSpriteSheetIndex("organisation icons");

				if (role.name == "Boss") {
					role.icon.spriteSheetArea = { 82, 10, 35, 53 };
				}
				else if (role.name == "Team Leader") {
					role.icon.spriteSheetArea = { 9, 75, 57, 47 };
				}
				else if (role.name == "Team Member") {
					role.icon.spriteSheetArea = { 7, 21, 60, 36 };
				}

				layer.push_back(role);

				layerRoleIDs.push_back(role.ID);

				roleIDCnt += 1;
			}

			organisationConstructorVars.hierarchyTable.push_back(layer);

			roleIDs.push_back(layerRoleIDs);
		}

		//Init relationships
		for (int roleIDsLayersCnt = 0; roleIDsLayersCnt < (int)roleIDs.size(); ++roleIDsLayersCnt) {
			for (int roleIDsRolesCnt = 0; roleIDsRolesCnt < (int)roleIDs[roleIDsLayersCnt].size(); ++roleIDsRolesCnt) {
				organisationConstructorVarsStruct::relationshipStruct currentRelationship;

				//First direction
				currentRelationship.direction[0].roleIDFrom = roleIDs[roleIDsLayersCnt][roleIDsRolesCnt];
				bool compareRoleID = true;
				while (compareRoleID == true) {
					int roleIDLayerIndex = randInt(0, (int)roleIDs.size() - 1);
					int roleIDRoleIndex = randInt(0, (int)roleIDs[roleIDLayerIndex].size() - 1);
					currentRelationship.direction[0].roleIDTo = roleIDs[roleIDLayerIndex][roleIDRoleIndex];
					if (currentRelationship.direction[0].roleIDTo != currentRelationship.direction[0].roleIDFrom) {
						compareRoleID = false;
					}
				}
				currentRelationship.direction[0].relationshipType = "Type " + str(randInt(0, 9));

				//Second direction - opposite direction of first direction
				currentRelationship.direction[1].roleIDFrom = currentRelationship.direction[0].roleIDTo;
				currentRelationship.direction[1].roleIDTo = currentRelationship.direction[0].roleIDFrom;
				currentRelationship.direction[1].relationshipType = "Type " + str(randInt(0, 9));

				organisationConstructorVars.relationships.push_back(currentRelationship);
			}
		}

		//Init hierarchy boards
		XYStruct characterPosition = characters[controlledCharacterIndex].getPosition();
		for (int boardsCnt = 0; boardsCnt < 1; ++boardsCnt) {
			objectConstructorVarsStruct objectConstructorVars;

			vector<int> objectIndices;
			for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
				objectIndices.push_back(objects[objectsCnt].getID());
			}
			objectConstructorVars.ID = getFreeID(objectIndices);

			objectConstructorVars.layer = characters[controlledCharacterIndex].getLayerIndex();
			objectConstructorVars.type = "Hierarchy Board";

			objectConstructorVars.objectDRect = { randInt(0, ((int)overworldGrid.gridTile[1].size() * tileSize.w) - (tileSize.w * 2)), randInt(0, ((int)overworldGrid.gridTile[1][0].size() * tileSize.h) - (tileSize.h * 2)), tileSize.w * 2, tileSize.h * 2 };

			animationStruct currentStateAnimation;
			currentStateAnimation.name = "display";
			currentStateAnimation.spriteSheetIndex = getSpriteSheetIndex("hierarchy board");
			currentStateAnimation.spritesSRect.push_back({ 0, 0, 250, 202 });
			currentStateAnimation.spriteDRect = objectConstructorVars.objectDRect;
			objectConstructorVars.stateAnimations.push_back(currentStateAnimation);

			objectConstructorVarsStruct::optionStruct currentOption;
			currentOption.icon = blankIcon;
			currentOption.icon.caption = "View hierarchy";
			currentOption.organisationID = organisationConstructorVars.ID;
			objectConstructorVars.options.push_back(currentOption);

			Object currentHierarchyBoard(objectConstructorVars);
			objects.push_back(currentHierarchyBoard);
		}

		Organisation currentOrganisation(organisationConstructorVars);
		organisations.push_back(currentOrganisation);
	}
}

void initCharacterOrganisation() {
	for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
		Character::organisationStruct characterOrganisation;
		int organisationIndex = randInt(0, (int)organisations.size() - 1);
		characterOrganisation.ID = organisations[organisationIndex].getID();
		vector<int> organistionRoleIDs = organisations[organisationIndex].getRoleIDs();
		characterOrganisation.roleID = organistionRoleIDs[randInt(0, (int)organistionRoleIDs.size() - 1)];
	}
}

void repositionCharacters(repositionCharactersRelativeToEnum relativeTo, vector<Object>& objects, string objectType, vector<Character>& characters, int characterIndex, int relativeToCharacterIndex, bool avoidCollidableTiles, directionEnum direction, int distance) {
	WHStruct characterSize = characters[characterIndex].getSpriteTargetSize();
	WHStruct characterGridSize = getGridSize(characterSize);
	int characterLayerIndex = characters[characterIndex].getLayerIndex();
	switch (relativeTo) {
		case repositionCharactersRelativeToEnum::object: {
			for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
				if (objects[objectsCnt].getType() == objectType) {
					SDL_Rect objectDRect = objects[objectsCnt].getObjectDRect();

					XYStruct characterPosition = { objectDRect.x, objectDRect.y };
					switch (direction) {
						case directionEnum::down: {
							characterPosition.y += distance;
							break;
						}
						case directionEnum::up: {
							characterPosition.y -= distance;
							break;
						}
						case directionEnum::right: {
							characterPosition.x += distance;
							break;
						}
						case directionEnum::left: {
							characterPosition.x -= distance;
							break;
						}
					}

					XYStruct characterGridPosition = getGridPosition(characterPosition);

					if (avoidCollidableTiles == true && checkCollisionWithOverworldGrid({ characterGridPosition.x, characterGridPosition.y, characterGridSize.w, characterGridSize.h }, characterLayerIndex) == false || avoidCollidableTiles == false) {
						characters[characterIndex].setPosition(characterPosition);
						return;
					}
				}
			}
			break;
		}
		case repositionCharactersRelativeToEnum::character: {
			XYStruct characterNewPosition = characters[relativeToCharacterIndex].getPosition();

			switch (direction) {
				case directionEnum::down: {
					characterNewPosition.y += distance;
					break;
				}
				case directionEnum::up: {
					characterNewPosition.y -= distance;
					break;
				}
				case directionEnum::right: {
					characterNewPosition.x += distance;
					break;
				}
				case directionEnum::left: {
					characterNewPosition.x -= distance;
					break;
				}
			}

			XYStruct characterGridPosition = getGridPosition(characterNewPosition);

			if (avoidCollidableTiles == true && checkCollisionWithOverworldGrid({ characterGridPosition.x, characterGridPosition.y, characterGridSize.w, characterGridSize.h }, characterLayerIndex) == false || avoidCollidableTiles == false) {
				characters[characterIndex].setPosition(characterNewPosition);
				return;
			}
			
			break;
		}
	}
}

void repositionObject(vector<Object>& objects, string objectType, XYStruct newPosition) {

	//Find object by type
	for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
		if (objects[objectsCnt].getType() == objectType) {

			//Reposition object
			objects[objectsCnt].setPosition(newPosition);
			objects[objectsCnt].setCollisionSet(false); //to get object collision to be set again

			return;
		}
	}

}

//Maybe not a good idea to use this function if elements need to be decoupled for performance. E.g.: running SDL_RenderCopy in a loop and running SDL_SetRenderTarget and SDL_RenderSetLogicalSize outside of that loop
void renderTexture(/*targetTypeEnum targetType, */WHStruct logicalSize, SDL_Texture* sTexture, SDL_Texture* dTexture, areaStruct sRect, areaStruct dRect, int transparencyPercentage) { //s: source, d: destination
	/*switch (targetType) {
		case targetTypeEnum::screen: {
			SDL_SetRenderTarget(renderer, NULL);
			break;
		}
		case targetTypeEnum::texture: {
			SDL_SetRenderTarget(renderer, dTexture);
			break;
		}
	}*/

	setSDLRenderTarget(dTexture);
	setSDLLogicalSize(logicalSize);

	SDL_Rect sourceRect = { sRect.x, sRect.y, sRect.w, sRect.h };
	SDL_Rect destinationRect = { dRect.x, dRect.y, dRect.w, dRect.h };

	setSDLTextureTransparency(sTexture, transparencyPercentage);

	if (sRect.w > -1 && dRect.w > -1) {
		SDL_RenderCopy(renderer, sTexture, &sourceRect, &destinationRect);
	}
	else if (sRect.w == -1 && dRect.w > -1) {
		SDL_RenderCopy(renderer, sTexture, NULL, &destinationRect);
	}
	else if (sRect.w > -1 && dRect.w == -1) {
		SDL_RenderCopy(renderer, sTexture, &sourceRect, NULL);
	}
}

vector<areaStruct> getSpriteAreas(XYStruct start, WHStruct spriteSize, int totalSprites) {

	//Get areas of each sprite
	vector<areaStruct> spriteAreas;
	areaStruct currentSpriteArea = { start.x, start.y, spriteSize.w, spriteSize.h };
	for (int spritesCnt = 0; spritesCnt < totalSprites; ++spritesCnt) {
		spriteAreas.push_back(currentSpriteArea);
		currentSpriteArea.x += spriteSize.w;
	}

	return spriteAreas;
}

vector<iconStruct> convertHeaderSringsToHeaderIcons(vector<string> headers) {
	vector<iconStruct> headerIcons;
	for (int headersCnt = 0; headersCnt < (int)headers.size(); ++headersCnt) {
		iconStruct currentHeaderIcon;
		currentHeaderIcon.caption = headers[headersCnt];
		headerIcons.push_back(currentHeaderIcon);
	}
	return headerIcons;
}

vector<string> convertHeaderIconsToHeaderStrings(vector<iconStruct> headerIcons) {
	vector<string> headerStrings;
	for (int headerIconsCnt = 0; headerIconsCnt < (int)headerIcons.size(); ++headerIconsCnt) {
		headerStrings.push_back(headerIcons[headerIconsCnt].caption);
	}
	return headerStrings;
}

void moveHeaderCursor(vector<iconStruct> headers, int cursor, int scrollStart, int scrollEnd, int displayLength, Uint32 scrollDelay, bool blockCursorMovement, int& returnedCursor, int& returnedScrollStart, int& returnedScrollEnd) {
	if (blockCursorMovement == false) {
		if ((controllerButtons.LB == true && SDL_GetTicks() - controllerButtonStartTicks.LB >= scrollDelay) || (controllerButtonPressedDuration.LB > 0 && controllerButtonPressedDuration.LB < scrollDelay)) {
			controllerButtonStartTicks.LB = SDL_GetTicks();
			controllerButtonPressedDuration.LB = 0;
			if (cursor > scrollStart) {
				--cursor;
			}
			else {
				if (scrollStart > 0) {
					--scrollStart;
					--scrollEnd;
					--cursor;
				}
				else {
					scrollEnd = (int)headers.size() - 1;
					scrollStart = scrollEnd - displayLength + 1;
					cursor = scrollEnd;
				}
			}
		}
		if ((controllerButtons.RB == true && SDL_GetTicks() - controllerButtonStartTicks.RB >= scrollDelay) || (controllerButtonPressedDuration.RB > 0 && controllerButtonPressedDuration.RB < scrollDelay)) {
			controllerButtonStartTicks.RB = SDL_GetTicks();
			controllerButtonPressedDuration.RB = 0;
			if (cursor < scrollEnd) {
				++cursor;
			}
			else {
				if (scrollEnd < (int)headers.size() - 1) {
					++scrollEnd;
					++scrollStart;
					++cursor;
				}
				else {
					scrollStart = 0;
					scrollEnd = scrollStart + displayLength - 1;
					cursor = scrollStart;
				}
			}
		}
	}

	returnedCursor = cursor;
	returnedScrollStart = scrollStart;
	returnedScrollEnd = scrollEnd;
}

void moveGridCursor(vector<iconStruct> icons, WHStruct gridSize, XYStruct gridCursor, int scrollStart, int scrollEnd, int scrollDelay, bool blockCursorMovement, XYStruct& returnedGridCursor, int& returnedScrollStart, int& returnedScrollEnd) {
	if (blockCursorMovement == false) {
		int scrollDistance = scrollEnd - scrollStart;

		//if ((hatButtons.left == true && SDL_GetTicks() - hatButtonsStartTicks.left >= scrollDelay / FPSTimerMod) || (hatButtonsPressedDuration.left > 0 && hatButtonsPressedDuration.left < scrollDelay / FPSTimerMod)) {
		if (hatButtons.left == true) {
			hatButtons.left = false;
			hatButtonsStartTicks.left = SDL_GetTicks();
			hatButtonsPressedDuration.left = 0;
			if (gridCursor.x > 0) {
				--gridCursor.x;
			}
			else {
				gridCursor.x = gridSize.w - 1;
				if (scrollStart - scrollDistance - 1 >= 0) {
					scrollStart -= scrollDistance + 1;
					scrollEnd = scrollStart + scrollDistance;
				}
				else {
					scrollStart = (int)icons.size() - 1 - scrollDistance;
					scrollEnd = scrollStart + scrollDistance;
				}
			}
		}

		//if ((hatButtons.right == true && SDL_GetTicks() - hatButtonsStartTicks.right >= scrollDelay / FPSTimerMod) || (hatButtonsPressedDuration.right > 0 && hatButtonsPressedDuration.right < scrollDelay / FPSTimerMod)) {
		if (hatButtons.right == true) {
			hatButtons.right = false;
			hatButtonsStartTicks.right = SDL_GetTicks();
			hatButtonsPressedDuration.right = 0;
			if (gridCursor.x < gridSize.w - 1) {
				++gridCursor.x;
			}
			else {
				gridCursor.x = 0;
				if ((int)icons.size() > scrollEnd - scrollStart + 1 && scrollStart + scrollDistance + 1 <= (int)icons.size() - 1) {
					scrollStart += scrollDistance + 1;
					scrollEnd = scrollStart + scrollDistance;
				}
				else {
					scrollStart = 0;
					scrollEnd = scrollStart + scrollDistance;
				}
			}
		}

		//if ((hatButtons.up == true && SDL_GetTicks() - hatButtonsStartTicks.up >= scrollDelay / FPSTimerMod) || (hatButtonsPressedDuration.up > 0 && hatButtonsPressedDuration.up < scrollDelay / FPSTimerMod)) {
		if (hatButtons.up == true) {
			hatButtons.up = false;
			hatButtonsStartTicks.up = SDL_GetTicks();
			hatButtonsPressedDuration.up = 0;
			if (gridCursor.y > 0) {
				--gridCursor.y;
			}
			else {
				gridCursor.y = gridSize.h - 1;
				if (scrollStart - scrollDistance - 1 >= 0) {
					scrollStart -= scrollDistance + 1;
					scrollEnd = scrollStart + scrollDistance;
				}
				else {
					scrollStart = (int)icons.size() - 1 - scrollDistance;
					scrollEnd = scrollStart + scrollDistance;
				}
			}
		}

		//if ((hatButtons.down == true && SDL_GetTicks() - hatButtonsStartTicks.down >= scrollDelay / FPSTimerMod) || (hatButtonsPressedDuration.down > 0 && hatButtonsPressedDuration.down < scrollDelay / FPSTimerMod)) {
		if (hatButtons.down == true) {
			hatButtons.down = false;
			hatButtonsStartTicks.down = SDL_GetTicks();
			hatButtonsPressedDuration.down = 0;
			if (gridCursor.y < gridSize.h - 1) {
				++gridCursor.y;
			}
			else {
				gridCursor.y = 0;
				if (scrollStart + scrollDistance + 1 <= (int)icons.size() - 1) {
					scrollStart += scrollDistance + 1;
					scrollEnd = scrollStart + scrollDistance;
				}
				else {
					scrollStart = 0;
					scrollEnd = scrollStart + scrollDistance;
				}
			}
		}
	}
	returnedGridCursor = gridCursor;
	returnedScrollStart = scrollStart;
	returnedScrollEnd = scrollEnd;
}

void moveIconListCursor(vector<iconStruct> icons, int listSize, int scrollCursor, int scrollStart, int scrollEnd, int scrollDelay, bool blockCursorMovement, int& returnedScrollCursor, int& returnedScrollStart, int& returnedScrollEnd) {
	if (blockCursorMovement == false) {
		//if ((hatButtons.up == true && SDL_GetTicks() - hatButtonsStartTicks.up >= scrollDelay / FPSTimerMod) || (hatButtonsPressedDuration.up > 0 && hatButtonsPressedDuration.up < scrollDelay / FPSTimerMod)) {
		if (hatButtons.up == true) {
			hatButtons.up = false;
			hatButtonsStartTicks.up = SDL_GetTicks();
			hatButtonsPressedDuration.up = 0;
			if (scrollCursor > scrollStart) {
				--scrollCursor;
			}
			else {
				if (scrollStart > 0) {
					--scrollStart;
					--scrollEnd;
					scrollCursor = scrollStart;
				}
				else {
					scrollEnd = (int)icons.size() - 1;
					scrollStart = scrollEnd - listSize + 1;
					scrollCursor = scrollEnd;
					if (scrollEnd - scrollStart + 1 > (int)icons.size()) {
						scrollStart = 0;
						scrollEnd = (int)icons.size() - 1;
						scrollCursor = scrollEnd;
					}
				}
			}
		}

		//if ((hatButtons.down == true && SDL_GetTicks() - hatButtonsStartTicks.down >= scrollDelay / FPSTimerMod) || (hatButtonsPressedDuration.down > 0 && hatButtonsPressedDuration.down < scrollDelay / FPSTimerMod)) {
		if (hatButtons.down == true) {
			hatButtons.down = false;
			hatButtonsStartTicks.down = SDL_GetTicks();
			hatButtonsPressedDuration.down = 0;
			if (scrollCursor < scrollEnd) {
				++scrollCursor;
			}
			else {
				if (scrollEnd < (int)icons.size() - 1) {
					++scrollStart;
					++scrollEnd;
					scrollCursor = scrollEnd;
				}
				else {
					scrollStart = 0;
					scrollEnd = scrollStart + listSize - 1;
					scrollCursor = scrollStart;
					if (scrollEnd - scrollStart + 1 > (int)icons.size()) {
						scrollStart = 0;
						scrollEnd = (int)icons.size() - 1;
						scrollCursor = scrollStart;
					}
				}
			}
		}
	}

	returnedScrollCursor = scrollCursor;
	returnedScrollStart = scrollStart;
	returnedScrollEnd = scrollEnd;
}

XYStruct getCenteredTextPosition(string text, TTF_Font* font, WHStruct logicalSize) {
	XYStruct position = { -1, -1 };
	WHStruct textSize = getTextSize(text, font);
	position.x = (logicalSize.w / 2) - (textSize.w / 2);
	position.y = (logicalSize.h / 2) - (textSize.h / 2);
	return position;
}

int getWidestTextWidth(vector<string> text, TTF_Font* font) {
	int widestTextWidth = -1;
	for (int textCnt = 0; textCnt < (int)text.size(); ++textCnt) {
		WHStruct textSize = getTextSize(text[textCnt], font);
		if (textSize.w > widestTextWidth) {
			widestTextWidth = textSize.w;
		}
	}
	return widestTextWidth;
}

void displayText(string text, XYStruct position, TTF_Font* font, SDL_Color colour, int backgroundTransparencyPercentage) {
	if (backgroundTransparencyPercentage > 0) {
		WHStruct textSize = getTextSize(text, font);
		sRect = convertAreaToSDLRect(menuBackgroundSprite.spriteSheetArea);
		dRect = { position.x, position.y, textSize.w, textSize.h };
		setSDLTextureTransparency(spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture, backgroundTransparencyPercentage);
		SDL_RenderCopy(renderer, spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture, &sRect, &dRect);
		removeSDLTextureTransparency(spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture);
	}

	renderText(text, font, colour, position);
}

void displayTextBlock(textBlockDisplayStyleEnum textBlockDisplayStyle, textBlockAlignmentEnum alignment, vector<iconStruct> icons, vector<string> text, XYStruct position, TTF_Font* font, SDL_Color colour, bool displayBackground, int backgroundTransparencyPercentage) {
	WHStruct textSize = getTextSize("Z", font);
	int iconSize = lround((double)textSize.h * 1.5);

	if (displayBackground == true) {
		sRect = convertAreaToSDLRect(menuBackgroundSprite.spriteSheetArea);
		dRect = { position.x, position.y, getWidestTextWidth(text, font) + iconSize, getTextSize(text[0], font).h * (int)text.size() * 2 };
		setSDLTextureTransparency(spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture, backgroundTransparencyPercentage);
		SDL_RenderCopy(renderer, spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture, &sRect, &dRect);
		removeSDLTextureTransparency(spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture);
	}

	XYStruct originalPosition = position;
	for (int textCnt = 0; textCnt < (int)text.size(); ++textCnt) {

		if (textBlockDisplayStyle == textBlockDisplayStyleEnum::vertical) {
			position.x = originalPosition.x;
		}

		//Update position.x based on alignment type
		if (alignment == textBlockAlignmentEnum::centered) {
			XYStruct currentPosition = getCenteredTextPosition(text[textCnt], font, textLogicalSize);
			position.x = currentPosition.x;
		}

		//Render icon
		if ((int)icons.size() > 0 && textCnt < (int)icons.size() && icons[textCnt].spriteSheetIndex > -1) {
			sRect = convertAreaToSDLRect(icons[textCnt].spriteSheetArea);
			dRect = { position.x, position.y - (textSize.h / 2), iconSize, iconSize };
			SDL_RenderCopy(renderer, spriteSheets[icons[textCnt].spriteSheetIndex].texture, &sRect, &dRect);
			position.x += textSize.h * 2;
		}

		//Render text
		renderText(text[textCnt], font, colour, position);

		switch (textBlockDisplayStyle) {
		case textBlockDisplayStyleEnum::vertical: {
			position.y += textSize.h * 2;
			break;
		}
		case textBlockDisplayStyleEnum::horizontal: {
			textSize = getTextSize(text[textCnt], font);
			position.x += textSize.w + iconSize;
			break;
		}
		}
	}
}

int getHeaderMenuVarsIndex(string name) {
	for (int headerMenuVarsCnt = 0; headerMenuVarsCnt < (int)headerMenuVars.size(); ++headerMenuVarsCnt) {
		if (headerMenuVars[headerMenuVarsCnt].name == name) {
			return headerMenuVarsCnt;
		}
	}

	return -1;
}

int getMenuVarsIndex(string name) {
	for (int menuVarsCnt = 0; menuVarsCnt < (int)menuVars.size(); ++menuVarsCnt) {
		if (menuVars[menuVarsCnt].name == name) {
			return menuVarsCnt;
		}
	}

	return -1;
}

iconStruct getControllerButtonIcon(string iconCaption) {
	iconStruct controllerButtonIcon;
	for (int controllerButtonIconsCnt = 0; controllerButtonIconsCnt < (int)controllerButtonIcons.size(); ++controllerButtonIconsCnt) {
		if (controllerButtonIcons[controllerButtonIconsCnt].caption == iconCaption) {
			return controllerButtonIcons[controllerButtonIconsCnt];
		}
	}
	return controllerButtonIcon;
}

int getControllerButtonIconIndex(string iconCaption) {
	for (int controllerButtonIconsCnt = 0; controllerButtonIconsCnt < (int)controllerButtonIcons.size(); ++controllerButtonIconsCnt) {
		if (controllerButtonIcons[controllerButtonIconsCnt].caption == iconCaption) {
			return controllerButtonIconsCnt;
		}
	}
	return -1;
}

void displayHeaderMenu(string headerMenuVarsName, headerStyleEnum headerStyle, XYStruct textPosition, vector<iconStruct> headers, int displayLength, WHStruct iconSize, TTF_Font* textFont, SDL_Color colour, iconStruct selectedHeaderSprite, int layer, bool blockCursorMovement, int backgroundTransparencyPercentage) {
	if ((int)headers.size() > 0) {
		/*if (selectedMenuLayer != layer) {
			blockCursorMovement = true;
		}*/

		//Create header menu vars
		int headerMenuVarsIndex = getHeaderMenuVarsIndex(headerMenuVarsName);
		if (headerMenuVarsIndex == -1) {
			headerMenuVarsStruct currentHeaderMenuVars;
			currentHeaderMenuVars.name = headerMenuVarsName;
			currentHeaderMenuVars.scrollStart = 0;
			currentHeaderMenuVars.scrollEnd = currentHeaderMenuVars.scrollStart + displayLength - 1;
			if (currentHeaderMenuVars.scrollEnd > (int)headers.size() - 1) {
				currentHeaderMenuVars.scrollEnd = (int)headers.size() - 1;
			}
			currentHeaderMenuVars.layer = layer;
			headerMenuVars.push_back(currentHeaderMenuVars);
			headerMenuVarsIndex = getHeaderMenuVarsIndex(headerMenuVarsName);
		}

		//Move header cursor
		moveHeaderCursor(headers, headerMenuVars[headerMenuVarsIndex].selected, headerMenuVars[headerMenuVarsIndex].scrollStart, headerMenuVars[headerMenuVarsIndex].scrollEnd, displayLength, 200, blockCursorMovement, headerMenuVars[headerMenuVarsIndex].selected, headerMenuVars[headerMenuVarsIndex].scrollStart, headerMenuVars[headerMenuVarsIndex].scrollEnd);

		setSDLRenderTarget(NULL);
		setSDLLogicalSize(textLogicalSize);

		//Render background
		if (backgroundTransparencyPercentage > 0) {
			sRect = { convertAreaToSDLRect(menuBackgroundSprite.spriteSheetArea) };
			setSDLTextureTransparency(spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture, backgroundTransparencyPercentage);
			SDL_RenderCopy(renderer, spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture, &sRect, NULL);
			removeSDLTextureTransparency(spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture);
		}

		//Display LB button icon
		if ((int)headers.size() > 0) {
			sRect = convertAreaToSDLRect(controllerButtonIcons[getControllerButtonIconIndex("LB")].spriteSheetArea);
			dRect = { textPosition.x, textPosition.y, tileSize.w * 4, tileSize.h * 4 };
			SDL_RenderCopy(renderer, spriteSheets[controllerButtonsSpriteSheetIndex].texture, &sRect, &dRect);
			textPosition.x += tileSize.w * 4;
		}

		//Display headers
		for (int headersCnt = headerMenuVars[headerMenuVarsIndex].scrollStart; headersCnt <= headerMenuVars[headerMenuVarsIndex].scrollEnd; ++headersCnt) {

			switch (headerStyle) {
			case headerStyleEnum::text: {
				WHStruct textSize = getTextSize(headers[headersCnt].caption + "   ", textFont);

				//Highlight selected header
				if (headerMenuVars[headerMenuVarsIndex].selected == headersCnt) {
					sRect = convertAreaToSDLRect(selectedHeaderSprite.spriteSheetArea);
					dRect = { textPosition.x, textPosition.y, textSize.w, textSize.h };
					SDL_RenderCopy(renderer, spriteSheets[selectedHeaderSprite.spriteSheetIndex].texture, &sRect, &dRect);
				}

				//Display icon
				if (headers[headersCnt].spriteSheetIndex > -1) {
					sRect = convertAreaToSDLRect(headers[headersCnt].spriteSheetArea);
					dRect = { textPosition.x, textPosition.y, textSize.h, textSize.h };
					SDL_RenderCopy(renderer, spriteSheets[headers[headersCnt].spriteSheetIndex].texture, &sRect, &dRect);

					textPosition.x += textSize.h;
				}

				//Display header caption
				renderText(headers[headersCnt].caption + "   ", textFont, colour, textPosition);

				textPosition.x += textSize.w;
				break;
			}
			case headerStyleEnum::icon: {

				//Highlight selected header icon
				if (headerMenuVars[headerMenuVarsIndex].selected == headersCnt) {
					sRect = convertAreaToSDLRect(selectedHeaderSprite.spriteSheetArea);
					dRect = { textPosition.x - tileSize.w, textPosition.y - tileSize.h, iconSize.w + (tileSize.w * 2), iconSize.h + (tileSize.h * 2) };
					SDL_RenderCopy(renderer, spriteSheets[selectedHeaderSprite.spriteSheetIndex].texture, &sRect, &dRect);
				}

				//Display header icon
				sRect = convertAreaToSDLRect(headers[headersCnt].spriteSheetArea);
				dRect = { textPosition.x, textPosition.y, iconSize.w, iconSize.h };
				SDL_RenderCopy(renderer, spriteSheets[headers[headersCnt].spriteSheetIndex].texture, &sRect, &dRect);

				//Display caption
				if (headerMenuVars[headerMenuVarsIndex].selected == headersCnt) {
					renderText(headers[headersCnt].caption, textFont, colour, { textPosition.x, textPosition.y + iconSize.h });
				}

				textPosition.x += iconSize.w + (tileSize.w * 2);
				break;
			}
			}
		}

		//Display RB button icon
		if ((int)headers.size() > 0) {
			sRect = convertAreaToSDLRect(controllerButtonIcons[getControllerButtonIconIndex("RB")].spriteSheetArea);
			dRect = { textPosition.x, textPosition.y, tileSize.w * 4, tileSize.h * 4 };
			SDL_RenderCopy(renderer, spriteSheets[controllerButtonsSpriteSheetIndex].texture, &sRect, &dRect);
		}

	}
}

//When using list display type, iconTextBlock is mandatory
void displayMenu(string menuVarsName, menuVarsStruct::styleEnum menuStyle, XYStruct textPosition, string title, bool displayTitle, vector<iconStruct> icons, vector<vector<string>> iconTextBlock, WHStruct gridSize, WHStruct iconSize, int listSize, TTF_Font* textFont, SDL_Color colour, iconStruct selectedIconSprite, int layer, bool blockCursorMovement, int backgroundTransparencyPercentage, bool displayCaption, bool allowDisplayTextBlock, bool allowMenuStyleSwitching, vector<menuControlsStruct> controls) {

	//Display background for entire menu
	/*if (displayBackgroundForEntireMenu == true) {
		;;
	}*/

	//Display title
	if (displayTitle == true && title != "") {
		renderText(title, defaultFont, defaultColour, textPosition);
	}

	if ((int)icons.size() > 0) {
		/*if (selectedMenuLayer != layer) { //this is managed outside of this function
			blockCursorMovement = true;
		}*/

		XYStruct originalTextPosition = textPosition;

		//Create icon menu vars
		int menuVarsIndex = getMenuVarsIndex(menuVarsName);
		if (menuVarsIndex == -1) {
			menuVarsStruct currentmenuVars;
			currentmenuVars.name = menuVarsName;
			currentmenuVars.scrollStart = 0;
			int randomStyle = 0;
			if (menuStyle == menuVarsStruct::styleEnum::randomized) {
				randomStyle = randInt(1, 2);
				switch (randomStyle) {
				case 1: {
					menuStyle = menuVarsStruct::styleEnum::icons;
					break;
				}
				case 2: {
					menuStyle = menuVarsStruct::styleEnum::list;
					break;
				}
				}
			}
			switch (menuStyle) {
			case menuVarsStruct::styleEnum::icons: {
				currentmenuVars.style = menuVarsStruct::styleEnum::icons;
				currentmenuVars.scrollEnd = currentmenuVars.scrollStart + (gridSize.w * gridSize.h) - 1;
				break;
			}
			case menuVarsStruct::styleEnum::list: {
				currentmenuVars.style = menuStyle;
				currentmenuVars.scrollEnd = listSize - 1;
				break;
			}
			}
			if (currentmenuVars.scrollEnd > (int)icons.size() - 1) {
				currentmenuVars.scrollEnd = (int)icons.size() - 1;
			}
			currentmenuVars.gridCursor = { 0, 0 };
			currentmenuVars.scrollCursor = 0;
			currentmenuVars.layer = layer;
			menuVars.push_back(currentmenuVars);
			menuVarsIndex = getMenuVarsIndex(menuVarsName);
		}

		//Switch menu style
		if (allowMenuStyleSwitching == true && controllerButtons.select == true && selectedMenuLayer == layer && blockCursorMovement == false /*quickslotSelectedItem == false && displayEquipMenu == false*/) {
			controllerButtons.select = false;
			menuVars[menuVarsIndex].scrollStart = 0;
			menuVars[menuVarsIndex].scrollCursor = menuVars[menuVarsIndex].scrollStart;
			if (menuVars[menuVarsIndex].style == menuVarsStruct::styleEnum::icons) {
				menuVars[menuVarsIndex].style = menuVarsStruct::styleEnum::list;
				menuVars[menuVarsIndex].scrollEnd = listSize - 1;
			}
			else {
				menuVars[menuVarsIndex].style = menuVarsStruct::styleEnum::icons;
				menuVars[menuVarsIndex].scrollEnd = (gridSize.w * gridSize.h) - 1;
			}
			if (menuVars[menuVarsIndex].scrollEnd > (int)icons.size() - 1) {
				menuVars[menuVarsIndex].scrollEnd = (int)icons.size() - 1;
			}
		}

		//Set scroll start and end if not set properly
		if (menuVars[menuVarsIndex].scrollStart < 0 || menuVars[menuVarsIndex].scrollStart >(int)icons.size() - 1
			|| menuVars[menuVarsIndex].scrollEnd < 0 || menuVars[menuVarsIndex].scrollEnd >(int)icons.size() - 1
			|| (int)icons.size() > 0 && menuVars[menuVarsIndex].scrollEnd == 0
			|| (int)icons.size() < gridSize.w && menuVars[menuVarsIndex].scrollEnd < (int)icons.size() - 1
			|| menuVars[menuVarsIndex].scrollEnd - menuVars[menuVarsIndex].scrollStart + 1 < (int)icons.size()) {
			menuVars[menuVarsIndex].scrollStart = 0;
			switch (menuVars[menuVarsIndex].style) {
			case menuVarsStruct::styleEnum::icons: {
				menuVars[menuVarsIndex].scrollEnd = (gridSize.w * gridSize.h) - 1;
				break;
			}
			case menuVarsStruct::styleEnum::list: {
				menuVars[menuVarsIndex].scrollEnd = listSize - 1;
				break;
			}
			}
			if (menuVars[menuVarsIndex].scrollEnd > (int)icons.size() - 1) {
				menuVars[menuVarsIndex].scrollEnd = (int)icons.size() - 1;
			}
		}

		bool displayBackground = false;
		if (backgroundTransparencyPercentage > 0) {
			displayBackground = true;
		}

		if (menuVars[menuVarsIndex].display == true) {
			WHStruct textSize;

			//Render background
			if (backgroundTransparencyPercentage > 0 && menuVars[menuVarsIndex].backgroundArea.x > -1 && menuVars[menuVarsIndex].backgroundArea.y > -1 && menuVars[menuVarsIndex].backgroundArea.w > -1 && menuVars[menuVarsIndex].backgroundArea.h > -1) {
				sRect = convertAreaToSDLRect(menuBackgroundSprite.spriteSheetArea);
				dRect = convertAreaToSDLRect(menuVars[menuVarsIndex].backgroundArea);

				setSDLTextureTransparency(spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture, backgroundTransparencyPercentage);

				SDL_RenderCopy(renderer, spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture, &sRect, &dRect);

				removeSDLTextureTransparency(spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture);
			}

			if (menuVars[menuVarsIndex].backgroundArea.x == -1) {
				menuVars[menuVarsIndex].backgroundArea.x = textPosition.x;
				menuVars[menuVarsIndex].backgroundArea.y = textPosition.y;
			}

			//Display title
			if (displayTitle == true && title != "") {
				renderText(title, defaultFont, defaultColour, textPosition);
				textSize = getTextSize(title, defaultFont);
				textPosition.y += textSize.h * 2;
			}

			//Display icons/list
			switch (menuVars[menuVarsIndex].style) {
			case menuVarsStruct::styleEnum::icons: {
				moveGridCursor(icons, gridSize, menuVars[menuVarsIndex].gridCursor, menuVars[menuVarsIndex].scrollStart, menuVars[menuVarsIndex].scrollEnd, 200, blockCursorMovement, menuVars[menuVarsIndex].gridCursor, menuVars[menuVarsIndex].scrollStart, menuVars[menuVarsIndex].scrollEnd);

				setSDLTextureTransparency(spriteSheets[iconBackgroundSprite.spriteSheetIndex].texture, 75);

				//Display icons
				int iconsCnt = menuVars[menuVarsIndex].scrollStart;
				int iconsDisplayCnt = 0;
				for (int gridYCnt = 0; gridYCnt < gridSize.h; ++gridYCnt) {
					textPosition.x = originalTextPosition.x;
					for (int gridXCnt = 0; gridXCnt < gridSize.w; ++gridXCnt) {

						//Display icon background
						sRect = convertAreaToSDLRect(iconBackgroundSprite.spriteSheetArea);
						dRect = { textPosition.x, textPosition.y, iconSize.w, iconSize.h };
						SDL_RenderCopy(renderer, spriteSheets[iconBackgroundSprite.spriteSheetIndex].texture, &sRect, &dRect);

						if (gridXCnt == menuVars[menuVarsIndex].gridCursor.x && gridYCnt == menuVars[menuVarsIndex].gridCursor.y) {
							menuVars[menuVarsIndex].scrollCursor = iconsCnt;

							//Highlight selected icon
							sRect = convertAreaToSDLRect(selectedIconSprite.spriteSheetArea);
							dRect = { textPosition.x - tileSize.w, textPosition.y - tileSize.h, iconSize.w + (tileSize.w * 2), iconSize.h + (tileSize.h * 2) };
							SDL_RenderCopy(renderer, spriteSheets[selectedIconSprite.spriteSheetIndex].texture, &sRect, &dRect);

						}
						//if ((int)icons.size() - 1 > gridSize.w && iconsCnt < (int)icons.size() || (int)icons.size() - 1 <= gridSize.w && iconsCnt == iconsDisplayCnt && iconsCnt < (int)icons.size() && icons[iconsCnt].spriteSheetIndex > -1) {
						if (iconsCnt < (int)icons.size()) {

							//Display icon
							sRect = convertAreaToSDLRect(icons[iconsCnt].spriteSheetArea);
							dRect = { textPosition.x, textPosition.y, iconSize.w, iconSize.h };
							SDL_RenderCopy(renderer, spriteSheets[icons[iconsCnt].spriteSheetIndex].texture, &sRect, &dRect);

							//Render black transparent background
							sRect = { convertAreaToSDLRect(iconBackgroundSprite.spriteSheetArea) };
							WHStruct captionSize = getTextSize(icons[iconsCnt].caption, textFont);
							dRect = { textPosition.x, textPosition.y + iconSize.h - captionSize.h, captionSize.w, captionSize.h };
							SDL_RenderCopy(renderer, spriteSheets[UISpriteSheetIndex].texture, &sRect, &dRect);

							//Render selected icon caption
							if (displayCaption == true) {
								renderText(icons[iconsCnt].caption, textFont, colour, { textPosition.x, textPosition.y + iconSize.h - captionSize.h });
							}

							//Display iconsCnt
							//renderText(str(iconsCnt), textFont, colour, { textPosition.x, textPosition.y + iconSize.h });

							++iconsDisplayCnt;
						}
						if (iconsCnt <= menuVars[menuVarsIndex].scrollEnd) {
							++iconsCnt;
						}
						textPosition.x += iconSize.w + tileSize.w;
					}
					textPosition.y += iconSize.h + tileSize.h;
				}

				if (menuVars[menuVarsIndex].backgroundArea.w == -1) {
					menuVars[menuVarsIndex].backgroundArea.w = textPosition.x - menuVars[menuVarsIndex].backgroundArea.x;
					menuVars[menuVarsIndex].backgroundArea.h = textPosition.y - menuVars[menuVarsIndex].backgroundArea.y;
				}

				removeSDLTextureTransparency(spriteSheets[iconBackgroundSprite.spriteSheetIndex].texture);
				break;
			}
			case menuVarsStruct::styleEnum::list: {
				moveIconListCursor(icons, listSize, menuVars[menuVarsIndex].scrollCursor, menuVars[menuVarsIndex].scrollStart, menuVars[menuVarsIndex].scrollEnd, 200, blockCursorMovement, menuVars[menuVarsIndex].scrollCursor, menuVars[menuVarsIndex].scrollStart, menuVars[menuVarsIndex].scrollEnd);

				string lengthiestStringInTextBlock = getLengthiestStringInTextBlock(iconTextBlock);

				for (int listCnt = menuVars[menuVarsIndex].scrollStart; listCnt <= menuVars[menuVarsIndex].scrollEnd; ++listCnt) {

					//Create text block string
					string textBlockString;
					for (int iconTextBlockCnt = 0; iconTextBlockCnt < (int)iconTextBlock[listCnt].size(); ++iconTextBlockCnt) {
						if (iconTextBlockCnt == 0) {
							textBlockString += iconTextBlock[listCnt][iconTextBlockCnt];
						}
						else {
							textBlockString += " " + iconTextBlock[listCnt][iconTextBlockCnt];
						}
					}

					if (displayCaption == true) {
						if (textBlockString == "") {
							textBlockString += icons[listCnt].caption;
						}
						else {
							textBlockString += " " + icons[listCnt].caption;
						}
					}

					textSize = getTextSize(textBlockString, textFont);

					//Display icon
					int thirdOfTextHeight = 0;
					if (icons[listCnt].spriteSheetIndex > -1) {
						thirdOfTextHeight = textSize.h / 3;
						sRect = convertAreaToSDLRect(icons[listCnt].spriteSheetArea);
						dRect = { textPosition.x - thirdOfTextHeight, textPosition.y - thirdOfTextHeight, textSize.h + (thirdOfTextHeight * 2), textSize.h + (thirdOfTextHeight * 2) };
						SDL_RenderCopy(renderer, spriteSheets[icons[listCnt].spriteSheetIndex].texture, &sRect, &dRect);
						textPosition.x += (textSize.h + (thirdOfTextHeight * 2) * 2);
					}

					//Highlight selected icon caption
					if (listCnt == menuVars[menuVarsIndex].scrollCursor) {
						sRect = convertAreaToSDLRect(selectedIconSprite.spriteSheetArea);
						dRect = { textPosition.x, textPosition.y, textSize.w, textSize.h };
						SDL_RenderCopy(renderer, spriteSheets[selectedIconSprite.spriteSheetIndex].texture, &sRect, &dRect);
					}

					//Display icon text blocks and caption
					renderText(textBlockString, textFont, colour, textPosition);

					if (menuVars[menuVarsIndex].backgroundArea.w == -1 && textBlockString == lengthiestStringInTextBlock) {
						menuVars[menuVarsIndex].backgroundArea.w = (textPosition.x + getTextSize(textBlockString, defaultFont).w) - menuVars[menuVarsIndex].backgroundArea.x;
					}

					//Display list cnt
					//renderText(str(listCnt), textFont, colour, textPosition);

					textPosition.x -= (textSize.h + (thirdOfTextHeight * 2) * 2);

					textPosition.y += textSize.h * 2;
				}

				if (menuVars[menuVarsIndex].backgroundArea.h == -1) {
					menuVars[menuVarsIndex].backgroundArea.h = textPosition.y - menuVars[menuVarsIndex].backgroundArea.y;
				}

				break;
			}
			}

			//Display text block
			if (allowDisplayTextBlock == true && menuVars[menuVarsIndex].scrollCursor >= 0 && menuVars[menuVarsIndex].scrollCursor <= (int)iconTextBlock.size() - 1) {
				textSize = getTextSize(getLengthiestStringInList(iconTextBlock[menuVars[menuVarsIndex].scrollCursor]), textFont);
				textPosition.x = originalTextPosition.x;
				textPosition.y += textSize.h * 2;
				displayTextBlock(textBlockDisplayStyleEnum::vertical, textBlockAlignmentEnum::left, {  }, iconTextBlock[menuVars[menuVarsIndex].scrollCursor], textPosition, defaultFont, defaultColour, displayBackground, backgroundTransparencyPercentage);
				int textSizeH = getTextSize(iconTextBlock[menuVars[menuVarsIndex].scrollCursor][0], defaultFont).h;
				textPosition.y += (int)iconTextBlock[menuVars[menuVarsIndex].scrollCursor].size() * textSizeH * 2;
				textPosition.y += textSizeH * 2;
			}

		}

		//Display controls
		if (blockCursorMovement == false && (int)controls.size() > 0) {
			vector<iconStruct> controllerIconsToDisplay;
			vector<string> controllerText;
			for (int controlsCnt = 0; controlsCnt < (int)controls.size(); ++controlsCnt) {
				controllerIconsToDisplay.push_back(getControllerButtonIcon(controls[controlsCnt].buttonName));
				controllerText.push_back(controls[controlsCnt].text);
			}
			textPosition = { originalTextPosition.x, textPosition.y };
			displayTextBlock(textBlockDisplayStyleEnum::vertical, textBlockAlignmentEnum::left, controllerIconsToDisplay, controllerText, textPosition, defaultFont, defaultColour, displayBackground, backgroundTransparencyPercentage);
		}

	}
}

void renderTextBackGround(string text, TTF_Font* font, XYStruct position, int transparencyPercentage) {
	sRect = convertAreaToSDLRect(menuBackgroundSprite.spriteSheetArea);
	WHStruct screenBackgroundSize = getTextSize(text, font);
	dRect = { position.x, position.y, screenBackgroundSize.w, screenBackgroundSize.h };
	bool transparencyApplied = false;
	if (transparencyPercentage < 100) {
		setSDLTextureTransparency(spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture, transparencyPercentage);
		transparencyApplied = true;
	}
	SDL_RenderCopy(renderer, spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture, &sRect, &dRect);
	if (transparencyApplied == true) {
		removeSDLTextureTransparency(spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture);
	}
}

bool areaWithinCameraView(areaStruct pixelArea) {
	if (pixelArea.x + pixelArea.w - 1 >= camera.area.x && pixelArea.x <= camera.area.x + camera.area.w - 1 && pixelArea.y + pixelArea.h - 1 >= camera.area.y && pixelArea.y <= camera.area.y + camera.area.h - 1) {
		return true;
	}
	return false;
}

bool SDLRectWithinCameraView(SDL_Rect pixelArea) {
	if (pixelArea.x + pixelArea.w - 1 >= camera.area.x && pixelArea.x <= camera.area.x + camera.area.w - 1 && pixelArea.y + pixelArea.h - 1 >= camera.area.y && pixelArea.y <= camera.area.y + camera.area.h - 1) {
		return true;
	}
	return false;
}

void initPreRenderTexture(WHStruct textureSize) {
	if (preRenderTexture == NULL) {
		preRenderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, textureSize.w, textureSize.h);
	}
}

void destroyPreRenderTexture() {
	if (preRenderTexture != NULL) {
		SDL_DestroyTexture(preRenderTexture);
	}
}

bool compareRenderOrderStructByX(const renderOrderStruct& renderOrderA, const renderOrderStruct& renderOrderB) {
	return renderOrderA.position.x < renderOrderB.position.x;
}

bool compareRenderOrderStructByY(const renderOrderStruct& renderOrderA, const renderOrderStruct& renderOrderB) {
	return renderOrderA.position.y < renderOrderB.position.y;
}

bool compareRenderOrderStructByLayerNum(const renderOrderStruct& renderOrderA, const renderOrderStruct& renderOrderB) {
	return renderOrderA.layerIndex < renderOrderB.layerIndex;
}

void characterRenders() {
	for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
		if (characters[charactersCnt].getDirection() == directionEnum::up || characters[charactersCnt].getDirection() == directionEnum::left || characters[charactersCnt].getDirection() == directionEnum::upLeft || characters[charactersCnt].getDirection() == directionEnum::upRight) {
			characters[charactersCnt].renderEquippedWeapon();
			characters[charactersCnt].renderAbilityAnimations();
		}
		characters[charactersCnt].render();
		if (characters[charactersCnt].getDirection() != directionEnum::up && characters[charactersCnt].getDirection() != directionEnum::left && characters[charactersCnt].getDirection() != directionEnum::upLeft && characters[charactersCnt].getDirection() != directionEnum::upRight) {
			characters[charactersCnt].renderEquippedWeapon();
			characters[charactersCnt].renderAbilityAnimations();
		}
		characters[charactersCnt].renderStatusEffects();
	}
}

//void renderSkillBasedInteractableObjects() {
//	for (int skillBasedInteractableObjectsCnt = 0; skillBasedInteractableObjectsCnt < (int)skillBasedInteractableObjects.size(); ++skillBasedInteractableObjectsCnt) {
//		skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].render();
//	}
//}

void renderObjects() {
	for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
		objects[objectsCnt].render();
	}
}

void renderBackgroundCharactersAndObjects() {
	setSDLRenderTarget(NULL);
	setSDLLogicalSize(cameraLogicalSize);

	vector<renderOrderStruct> renderOrder;

	//Insert characters in renderOrder vector
	if ((int)characters.size() > 0) {
		for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
			XYStruct characterPosition = characters[charactersCnt].getPosition();
			WHStruct characterSpriteTargetSize = characters[charactersCnt].getSpriteTargetSize();
			if (areaWithinCameraView({ characterPosition.x, characterPosition.y, characterSpriteTargetSize.w, characterSpriteTargetSize.h }) == true) {
				renderOrder.push_back({ renderOrderStruct::typeEnum::character, characters[charactersCnt].getLayerIndex(), characters[charactersCnt].getID(), characterPosition });
			}
		}
	}

	//Insert skill based interactable objects in renderOrder vector
	/*for (int skillBasedInteractableObjectsCnt = 0; skillBasedInteractableObjectsCnt < (int)skillBasedInteractableObjects.size(); ++skillBasedInteractableObjectsCnt) {
		if (areaWithinCameraView({ skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].objectDRect.x, skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].objectDRect.y, skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].objectDRect.w, skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].objectDRect.h }) == true) {
			renderOrder.push_back({ renderOrderStruct::typeEnum::skillBasedInteractableObject, skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].layerIndex, skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].index, { skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].objectDRect.x, skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].objectDRect.y } });
		}
	}*/

	//Insert objects in renderOrder vector
	for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
		SDL_Rect objectDRect = objects[objectsCnt].getObjectDRect();

		if (SDLRectWithinCameraView(objectDRect) == true) {
			renderOrder.push_back({ renderOrderStruct::typeEnum::object, objects[objectsCnt].getLayer(), objects[objectsCnt].getID(), { objectDRect.x, objectDRect.y } });
		}
	}

	//Sort renderOrder by x then by y, then by layerNum
	if ((int)renderOrder.size() > 0) {
		sort(renderOrder.begin(), renderOrder.end(), compareRenderOrderStructByX);
		sort(renderOrder.begin(), renderOrder.end(), compareRenderOrderStructByY);
		sort(renderOrder.begin(), renderOrder.end(), compareRenderOrderStructByLayerNum);
	}

	//Define grid camera
	overworldGrid.camera.x = camera.area.x / tileSize.w;
	overworldGrid.camera.y = camera.area.y / tileSize.h;
	overworldGrid.camera.w = (camera.area.w / tileSize.w) + 1;
	overworldGrid.camera.h = (camera.area.h / tileSize.h) + 1;

	//Correct camera area w and h to keep aspect ratio
	cameraLogicalSize.w = camera.area.w;
	cameraLogicalSize.h = camera.area.h;
	decimalNumPartsStruct currentDecimalNumPartsX = getDecimalNumParts((float)cameraLogicalSize.w / aspectRatio.ratio.w);
	decimalNumPartsStruct currentDecimalNumPartsY = getDecimalNumParts((float)cameraLogicalSize.h / aspectRatio.ratio.h);
	if (currentDecimalNumPartsX.fractpart > 0 || currentDecimalNumPartsY.fractpart > 0) {
		int highestIntPart = (int)(currentDecimalNumPartsX.intpart);
		if (currentDecimalNumPartsY.intpart > currentDecimalNumPartsX.intpart) {
			highestIntPart = (int)currentDecimalNumPartsY.intpart;
		}
		cameraLogicalSize.w = highestIntPart * aspectRatio.ratio.w;
		cameraLogicalSize.h = highestIntPart * aspectRatio.ratio.h;
	}

	//Render to pre-render texture
	initPreRenderTexture({ cameraLogicalSize.w, cameraLogicalSize.h });
	setSDLRenderTarget(preRenderTexture);

	for (int layersCnt = 0; layersCnt < (int)overworldGrid.gridTile.size(); ++layersCnt) {

		//Render tiles
		for (int gridXCnt = overworldGrid.camera.x; gridXCnt < overworldGrid.camera.x + overworldGrid.camera.w + 1; ++gridXCnt) {
			for (int gridYCnt = overworldGrid.camera.y; gridYCnt < overworldGrid.camera.y + overworldGrid.camera.h + 1; ++gridYCnt) {
				if (layersCnt >= 0 && layersCnt <= (int)overworldGrid.gridTile.size() - 1 && gridXCnt >= 0 && gridXCnt <= (int)overworldGrid.gridTile[layersCnt].size() - 1 && gridYCnt >= 0 && gridYCnt <= (int)overworldGrid.gridTile[layersCnt][gridXCnt].size() - 1 && overworldGrid.gridTile[layersCnt][gridXCnt][gridYCnt].tileIndex > -1) {

					XYStruct tilePosition = { gridXCnt * tileSize.w, gridYCnt * tileSize.h };

					sRect = convertAreaToSDLRect(tiles[overworldGrid.gridTile[layersCnt][gridXCnt][gridYCnt].tileIndex].spriteSheetArea);

					dRect = { tilePosition.x - camera.area.x, tilePosition.y - camera.area.y, tileSize.w, tileSize.h };

					SDL_RenderCopy(renderer, spriteSheets[tiles[overworldGrid.gridTile[layersCnt][gridXCnt][gridYCnt].tileIndex].spriteSheetIndex].texture, &sRect, &dRect);
				}
			}
		}

		//Render characters and objects
		if ((int)renderOrder.size() > 0) {
			for (int renderOrderCnt = 0; renderOrderCnt < (int)renderOrder.size(); ++renderOrderCnt) {
				if (renderOrder[renderOrderCnt].layerIndex == layersCnt) {
					switch (renderOrder[renderOrderCnt].type) {
					case renderOrderStruct::typeEnum::character: {
						characterRenders();
						break;
					}
															   /*case renderOrderStruct::typeEnum::skillBasedInteractableObject: {
																   renderSkillBasedInteractableObjects();
																   break;
															   }*/
					case renderOrderStruct::typeEnum::object: {
						renderObjects();
						break;
					}
					}
				}
			}
		}

	}

	//Render pre-render texture to screen
	setSDLRenderTarget(NULL);
	WHStruct preRenderTextureSize = getSDLTextureSize(preRenderTexture);
	sRect = { 0, 0, preRenderTextureSize.w, preRenderTextureSize.h };
	dRect = { 0, 0, preRenderTextureSize.w, preRenderTextureSize.h };
	SDL_RenderCopy(renderer, preRenderTexture, &sRect, &dRect);
	clearTexture(preRenderTexture, 0, 0, 0, 255);

}

void moveCamera() {
	if (SDL_GetTicks() - camera.moveStartTicks >= camera.moveDelay) {
		camera.moveStartTicks = SDL_GetTicks();
		if (xDir == -1) { //left
			--camera.area.x;
		}
		if (xDir == 1) { //right
			++camera.area.x;
		}
		if (yDir == -1) { //up
			--camera.area.y;
		}
		if (yDir == 1) { //down
			++camera.area.y;
		}
	}
}

void displayLoadIcon(areaStruct dRectArea, Uint32 controllerButtonStartTicks, int iconSize) {
	if (controllerButtonStartTicks > 0) {
		int iconWidth = lround(((float)(iconSize * 2) * lround((float)((SDL_GetTicks() - controllerButtonStartTicks) * 100) / 1000)) / 100);

		sRect = convertAreaToSDLRect(loadIconBack.spriteSheetArea);
		dRect = convertAreaToSDLRect(dRectArea);
		SDL_RenderCopy(renderer, spriteSheets[loadIconBack.spriteSheetIndex].texture, &sRect, &dRect);

		sRect = convertAreaToSDLRect(loadIconFront.spriteSheetArea);
		dRect = { dRectArea.x, dRectArea.y, iconWidth, dRectArea.h };
		SDL_RenderCopy(renderer, spriteSheets[loadIconFront.spriteSheetIndex].texture, &sRect, &dRect);
	}
}

int getCharacterCnt(int characterID) {
	for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
		if (characters[charactersCnt].getID() == characterID) {
			return charactersCnt;
		}
	}
	return -1;
}

Character getCharacterByID(int characterID) {
	for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
		if (characters[charactersCnt].getID() == characterID) {
			return characters[charactersCnt];
		}
	}

	characterConstructorVarsStruct characterConstructorVars;
	characterConstructorScheduleVarsStruct characterConstructorScheduleVars;
	Character emptyCharacter(characterConstructorVars, characterConstructorScheduleVars);

	return emptyCharacter;
}

int getAbilityCnt(int characterIndex, int abilityIndex) {
	int characterCnt = getCharacterCnt(characterIndex);
	vector<characterConstructorVarsStruct::abilityStruct> characterAbilities = characters[characterCnt].getAbilities();
	for (int abilitiesCnt = 0; abilitiesCnt < (int)characterAbilities.size(); ++abilitiesCnt) {
		if (characterAbilities[abilitiesCnt].index == abilityIndex) {
			return abilitiesCnt;
		}
	}
	return -1;
}

int getAmmoCnt(int characterIndex, string ammoName) {
	int characterCnt = getCharacterCnt(characterIndex);
	vector<characterConstructorVarsStruct::ammoStruct> characterAmmos = characters[characterCnt].getAmmos();
	for (int ammosCnt = 0; ammosCnt < (int)characterAmmos.size(); ++ammosCnt) {
		if (characterAmmos[ammosCnt].name == ammoName) {
			return ammosCnt;
		}
	}
	return -1;
}

void renderHUD() {
	setSDLRenderTarget(NULL);
	setSDLLogicalSize(textLogicalSize);

	setSDLTextureTransparency(spriteSheets[UISpriteSheetIndex].texture, 75);

	//Render transparent background and prompt message
	if (quickslotSelectedItem == true) {

		//Render transparent background
		sRect = convertAreaToSDLRect(menuBackgroundSprite.spriteSheetArea);
		SDL_RenderCopy(renderer, spriteSheets[menuBackgroundSprite.spriteSheetIndex].texture, &sRect, NULL);

		//Init message
		vector<iconStruct> icons = {
			{  },
			getControllerButtonIcon("start"),
			getControllerButtonIcon("select")
		};
		vector<string> text = { "Press quickslot button to quickslot item", "Back", "Empty all slots" };

		//Render load icons
		XYStruct centeredTextPosition = getCenteredTextPosition(text[2], defaultFont, textLogicalSize);
		WHStruct textSize = getTextSize(text[2], defaultFont);
		int iconSize = lround((double)textSize.h * 1.5);
		displayLoadIcon({ centeredTextPosition.x - (iconSize / 2), centeredTextPosition.y + (textSize.h * 4) - (iconSize / 2), iconSize * 2, iconSize * 2 }, controllerButtonStartTicks.select, iconSize);

		//Render message
		displayTextBlock(textBlockDisplayStyleEnum::vertical, textBlockAlignmentEnum::centered, icons, text, getCenteredTextPosition(text[2], defaultFont, textLogicalSize), defaultFont, defaultColour, false, 0);

	}

	//Render quickslots
	int iconSize = tileSize.w * 7;
	struct quickslotDataStruct {
		string name;
		XYStruct gridPosition;
		iconStruct buttonIcon;
		XYStruct iconPosition;
	};
	vector<quickslotDataStruct> quickslotData = {
		{ "up", { 1, 0 }, { getSpriteSheetIndex("controller buttons"), { 28, 195, 22, 19 }, "" }, { iconSize, textLogicalSize.h - (iconSize * 4) } },
		{ "down", { 1, 2 }, { getSpriteSheetIndex("controller buttons"), { 29, 230, 19, 21 }, "" }, { iconSize, textLogicalSize.h - (iconSize * 4) } },
		{ "left", { 0, 1 }, { getSpriteSheetIndex("controller buttons"), { 10, 212, 20, 21 }, "" }, { iconSize, textLogicalSize.h - (iconSize * 4) } },
		{ "right", { 2, 1 }, { getSpriteSheetIndex("controller buttons"), { 46, 212, 22, 21 }, "" }, { iconSize, textLogicalSize.h - (iconSize * 4) } },
		{ "A", { 1, 2 }, { getSpriteSheetIndex("controller buttons"), { 89, 193, 61, 60 }, "" }, { textLogicalSize.w - (iconSize * 4), textLogicalSize.h - (iconSize * 3) } },
		{ "B", { 2, 1 }, { getSpriteSheetIndex("controller buttons"), { 174, 192, 56, 62 }, "" }, { textLogicalSize.w - (iconSize * 4), textLogicalSize.h - (iconSize * 3) } },
		{ "X", { 0, 1 }, { getSpriteSheetIndex("controller buttons"), { 254, 192, 58, 63 }, "" }, { textLogicalSize.w - (iconSize * 4), textLogicalSize.h - (iconSize * 3) } },
		{ "Y", { 1, 0 }, { getSpriteSheetIndex("controller buttons"), { 335, 192, 58, 60 }, "" }, { textLogicalSize.w - (iconSize * 4), textLogicalSize.h - (iconSize * 3) } },
		{ "LB", { 0, 0 }, { getSpriteSheetIndex("controller buttons"), { 368, 56, 69, 52 }, "" }, { textLogicalSize.w / 2 - (iconSize * 1), textLogicalSize.h - iconSize * 3 } },
		{ "RB", { 1, 0 }, { getSpriteSheetIndex("controller buttons"), { 450, 58, 70, 50 }, "" }, { textLogicalSize.w / 2 - (iconSize * 1), textLogicalSize.h - iconSize * 3 } },
		{ "LT", { 0, 1 }, { getSpriteSheetIndex("controller buttons"), { 215, 49, 50, 66 }, "" }, { textLogicalSize.w / 2 - (iconSize * 1), textLogicalSize.h - iconSize * 3 } },
		{ "RT", { 1, 1 }, { getSpriteSheetIndex("controller buttons"), { 296, 51, 50, 65 }, "" }, { textLogicalSize.w / 2 - (iconSize * 1), textLogicalSize.h - iconSize * 3 } }
	};
	for (int elementDisplayCnt = 0; elementDisplayCnt < 4; ++elementDisplayCnt) {
		for (int quickslotDataCnt = 0; quickslotDataCnt < (int)quickslotData.size(); ++quickslotDataCnt) {
			XYStruct iconCurrentPosition = { quickslotData[quickslotDataCnt].iconPosition.x + (quickslotData[quickslotDataCnt].gridPosition.x * iconSize), quickslotData[quickslotDataCnt].iconPosition.y + (quickslotData[quickslotDataCnt].gridPosition.y * iconSize) };

			//Render blank slot icon
			if (elementDisplayCnt == 0) {
				sRect = convertAreaToSDLRect(iconBackgroundSprite.spriteSheetArea);
				dRect = { iconCurrentPosition.x, iconCurrentPosition.y, iconSize, iconSize };
				SDL_RenderCopy(renderer, spriteSheets[iconBackgroundSprite.spriteSheetIndex].texture, &sRect, &dRect);
			}

			//Render slotted item icon
			int characterQuickslotIndex = characters[controlledCharacterIndex].getQuickslotIndex(quickslotData[quickslotDataCnt].name);
			if (elementDisplayCnt == 1) {
				vector<characterConstructorVarsStruct::quickslotsStruct> characterQuickslots = characters[controlledCharacterIndex].getQuickslots();
				if (characterQuickslots[characterQuickslotIndex].slottedItemIndex > -1 && characterQuickslots[characterQuickslotIndex].icon.spriteSheetIndex > -1) {
					sRect = convertAreaToSDLRect(characterQuickslots[characterQuickslotIndex].icon.spriteSheetArea);
					dRect = { iconCurrentPosition.x, iconCurrentPosition.y, iconSize, iconSize };
					SDL_RenderCopy(renderer, spriteSheets[characterQuickslots[characterQuickslotIndex].icon.spriteSheetIndex].texture, &sRect, &dRect);
				}
			}

			//Display ammo count if ability requires ammo
			if (elementDisplayCnt == 2) {
				vector<characterConstructorVarsStruct::quickslotsStruct> characterQuickslots = characters[controlledCharacterIndex].getQuickslots();
				if (characterQuickslots[characterQuickslotIndex].slottedItemType == "ABILITIES") {
					int abilityCnt = getAbilityCnt(controlledCharacterIndex, characterQuickslots[characterQuickslotIndex].slottedItemIndex);

					vector<characterConstructorVarsStruct::abilityStruct> characterAbilities = characters[controlledCharacterIndex].getAbilities();
					if (characterAbilities[abilityCnt].requiredAmmoName != "") {
						int ammoCnt = getAmmoCnt(controlledCharacterIndex, characterAbilities[abilityCnt].requiredAmmoName);
						renderText(str(characters[controlledCharacterIndex].getAmmos()[ammoCnt].quantity), defaultFont, defaultColour, { iconCurrentPosition.x + ((iconSize / 3) * 2), iconCurrentPosition.y + ((iconSize / 3) * 2) });
					}
				}
			}

			//Render button icon
			if (elementDisplayCnt == 3) {
				sRect = convertAreaToSDLRect(quickslotData[quickslotDataCnt].buttonIcon.spriteSheetArea);
				dRect = { iconCurrentPosition.x, iconCurrentPosition.y, iconSize / 2, iconSize / 2 };
				SDL_RenderCopy(renderer, spriteSheets[quickslotData[quickslotDataCnt].buttonIcon.spriteSheetIndex].texture, &sRect, &dRect);
			}

		}
	}

	//Render stats
	vector<characterConstructorVarsStruct::statStruct> characterStats = characters[controlledCharacterIndex].getStats();
	WHStruct textSize = getTextSize(characterStats[0].name, defaultFont);
	iconSize = textSize.h * 2;
	XYStruct position = { textLogicalSize.w / 4, textLogicalSize.h - (textSize.h * 2 * ((int)characterStats.size() + 1)) };
	for (int statsCnt = 0; statsCnt < (int)characterStats.size(); ++statsCnt) {

		//Display icon
		sRect = convertAreaToSDLRect(characterStats[statsCnt].icon.spriteSheetArea);
		dRect = { position.x, position.y, iconSize, iconSize };
		SDL_RenderCopy(renderer, spriteSheets[characterStats[statsCnt].icon.spriteSheetIndex].texture, &sRect, &dRect);
		//renderText(characters[controlledCharacterIndex].stats[statsCnt].name, defaultFont, defaultColour, { position.x + iconSize, position.y });

		//Display bar back icon
		characterStats[statsCnt].bar.backIcon.totalIcons = characterStats[statsCnt].max;
		int barSize = iconSize * 5;
		characterStats[statsCnt].bar.backIcon.dRect = { position.x + iconSize, position.y, barSize, iconSize };
		sRect = convertAreaToSDLRect(characterStats[statsCnt].bar.backIcon.icon.spriteSheetArea);
		dRect = convertAreaToSDLRect(characterStats[statsCnt].bar.backIcon.dRect);
		SDL_RenderCopy(renderer, spriteSheets[characterStats[statsCnt].bar.backIcon.icon.spriteSheetIndex].texture, &sRect, &dRect);

		//Display fore icon
		characterStats[statsCnt].bar.foreIcon.totalIcons = characterStats[statsCnt].current + characterStats[statsCnt].modified;
		int totalIconsPercentage = (characterStats[statsCnt].bar.foreIcon.totalIcons * 100) / characterStats[statsCnt].bar.backIcon.totalIcons;
		characterStats[statsCnt].bar.foreIcon.dRect = { position.x + iconSize, position.y, (barSize * totalIconsPercentage) / 100, iconSize };
		sRect = convertAreaToSDLRect(characterStats[statsCnt].bar.foreIcon.icon.spriteSheetArea);
		dRect = convertAreaToSDLRect(characterStats[statsCnt].bar.foreIcon.dRect);
		SDL_RenderCopy(renderer, spriteSheets[characterStats[statsCnt].bar.foreIcon.icon.spriteSheetIndex].texture, &sRect, &dRect);

		position.y += iconSize;
	}
	characters[controlledCharacterIndex].setStats(characterStats);

	removeSDLTextureTransparency(spriteSheets[UISpriteSheetIndex].texture);

	//Show current position and height in overworld region, and region name
	string currentPositionAndHeight = formatStr("{} - Loc {}, {} - Flr {}", { regionGrid.names[regionGrid.position.x][regionGrid.position.y], str(regionGrid.position.x), str(regionGrid.position.y), str(overworldGrid.height) });
	WHStruct currentPositionAndHeightTextSize = getTextSize(currentPositionAndHeight, defaultFont);
	position = { ((textLogicalSize.w / 4) * 3) - (currentPositionAndHeightTextSize.w / 2), textLogicalSize.h - (currentPositionAndHeightTextSize.h * 6) };
	displayText(currentPositionAndHeight, { ((textLogicalSize.w / 4) * 3) - (currentPositionAndHeightTextSize.w / 2), textLogicalSize.h - (currentPositionAndHeightTextSize.h * 4) }, defaultFont, defaultColour, 75);

	//Display game clock
	position.y += currentPositionAndHeightTextSize.h * 4;
	renderText(formatStr("{}: {}: {}, {}/{}/{}", { str(gameClock.hour), str(gameClock.minute), str(gameClock.second), str(gameClock.day), str(gameClock.month), str(gameClock.year) }), defaultFont, defaultColour, position);

}

void selectQuantity(XYStruct& textPosition, bool& display, string& caption, int& selected, int& min, int& max, Uint32& scrollDelay, bool& blockCursorMovement, bool& centreText, bool& showControlCaptions) {
	if (display == true) {

		//Close menu
		if (controllerButtons.B == true) {
			controllerButtons.B = false;
			display = false;
			blockCursorMovement = false;
		}

		//Select quantity
		if ((hatButtons.left == true && SDL_GetTicks() - hatButtonsStartTicks.left >= scrollDelay) || (hatButtonsPressedDuration.left > 0 && hatButtonsPressedDuration.left < scrollDelay)) {
			hatButtonsStartTicks.left = SDL_GetTicks();
			hatButtonsPressedDuration.left = 0;
			if (selected > min) {
				--selected;
			}
			else {
				selected = max;
			}
		}
		if ((hatButtons.right == true && SDL_GetTicks() - hatButtonsStartTicks.right >= scrollDelay) || (hatButtonsPressedDuration.right > 0 && hatButtonsPressedDuration.right < scrollDelay)) {
			hatButtonsStartTicks.right = SDL_GetTicks();
			hatButtonsPressedDuration.right = 0;
			if (selected < max) {
				++selected;
			}
			else {
				selected = min;
			}
		}
		if (controllerButtons.LB == true) {
			controllerButtons.LB = false;
			selected -= 10;
			if (selected < min) {
				selected = min;
			}
		}
		if (controllerButtons.RB == true) {
			controllerButtons.RB = false;
			selected += 10;
			if (selected > max) {
				selected = max;
			}
		}
		if (leftTrigger.activated == true) {
			leftTrigger.activated = false;
			selected = min;
		}
		if (rightTrigger.activated == true) {
			rightTrigger.activated = false;
			selected = max;
		}

		//Render transparent background on the whole screen
		setSDLTextureTransparency(spriteSheets[UISpriteSheetIndex].texture, 75);
		sRect = { 34, 0, 8, 8 };
		SDL_RenderCopy(renderer, spriteSheets[UISpriteSheetIndex].texture, &sRect, NULL);

		string textTitle = "Select quantity: " + caption;

		//Adjust position
		if (centreText == true) {
			WHStruct currentLogicalSize = { -1, -1 };
			SDL_RenderGetLogicalSize(renderer, &currentLogicalSize.w, &currentLogicalSize.h);
			textPosition = getCenteredTextPosition(textTitle, defaultFont, currentLogicalSize);
		}

		//Display caption
		renderText(textTitle, defaultFont, defaultColour, textPosition);
		WHStruct textSize = getTextSize(caption, defaultFont);

		//Display min, max and selected quantity
		textPosition.y += (textSize.h * 2);
		renderText("(" + str(min) + ") " + str(selected) + " (" + str(max) + ")", defaultFont, defaultColour, textPosition);

		//Display control captions
		if (showControlCaptions == true) {
			vector<menuControlsStruct> controls = {
				{ "dPadLeft", "Decrease" },
				{ "dPadRight", "Increase" },
				{ "LB", "Decrease by 10" },
				{ "RB", "Increase by 10" },
				{ "LT", "Decrease to minimum" },
				{ "RT", "Increase to maximum" },
				{ "A", "Select" },
				{ "B", "Cancel" }
			};
			vector<iconStruct> controllerIconsToDisplay;
			vector<string> controllerText;
			for (int controlsCnt = 0; controlsCnt < (int)controls.size(); ++controlsCnt) {
				controllerIconsToDisplay.push_back(getControllerButtonIcon(controls[controlsCnt].buttonName));
				controllerText.push_back(controls[controlsCnt].text);
			}
			textPosition.y += (textSize.h * 2);
			displayTextBlock(textBlockDisplayStyleEnum::vertical, textBlockAlignmentEnum::left, controllerIconsToDisplay, controllerText, textPosition, defaultFont, defaultColour, true, 75);
		}

		removeSDLTextureTransparency(spriteSheets[UISpriteSheetIndex].texture);
	}
}

void playMusic(string name) {
	if (mute == false) {
		Mix_PlayMusic(music[getMusicIndex(name)].music, -1);
	}
}

void playSoundEffect(string name) {
	if (mute == false) {
		Mix_PlayChannel(-1, soundEffects[getSoundEffectIndex(name)].soundEffect, 0);
	}
}

void characterActions() {
	for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
		characters[charactersCnt].move();
		characters[charactersCnt].activateMenu();
		//characters[charactersCnt].checkObjectInteraction(Character::objectInteractionTypeEnum::skillBasedInteractableObject);
		characters[charactersCnt].attack();
		characters[charactersCnt].animateAbilities();
		characters[charactersCnt].checkTargetHitByAttack();
		characters[charactersCnt].runStatusEffects();
		characters[charactersCnt].removeStatusEffects();
		characters[charactersCnt].animateStatusEffects();
		characters[charactersCnt].stopAbilityAnimations();
		characters[charactersCnt].checkObjectProximity();
		characters[charactersCnt].setGoal();
		characters[charactersCnt].carryOutGoal();
		characters[charactersCnt].followPath();
		characters[charactersCnt].runSleepAnimation();
		characters[charactersCnt].getScheduleFromOrganisation();
	}
}

//void skillBasedInteractableObjectsActions() {
//	for (int skillBasedInteractableObjectsCnt = 0; skillBasedInteractableObjectsCnt < (int)skillBasedInteractableObjects.size(); ++skillBasedInteractableObjectsCnt) {
//		skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].setObjectCollision();
//		skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].animate();
//		skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].interact();
//	}
//}

//void skillBasedInteractableObjectRenders() {
//	for (int skillBasedInteractableObjectsCnt = 0; skillBasedInteractableObjectsCnt < (int)skillBasedInteractableObjects.size(); ++skillBasedInteractableObjectsCnt) {
//		//skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].displaySkillValues();
//		skillBasedInteractableObjects[skillBasedInteractableObjectsCnt].renderContextMenu();
//	}
//}

void objectActions() {
	for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
		objects[objectsCnt].setObjectCollision();
		objects[objectsCnt].animate();
		objects[objectsCnt].interact();
		objects[objectsCnt].setOrganisationDisplayHierarchyBoolToTrue(organisations);
		objects[objectsCnt].updateCharacterSleepState(characters[controlledCharacterIndex]);
	}
}

void objectMenus() {
	for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
		objects[objectsCnt].displayOptionsMenu();
		/*objects[objectsCnt].keypadCodeMenu();
		objects[objectsCnt].keyboardCodeMenu();*/
		objects[objectsCnt].inputDeviceSelectionMenu();
		objects[objectsCnt].inputDeviceMenu();
		objects[objectsCnt].craftingMenu(craftingTable, characters[controlledCharacterIndex], craftingTableCraftedItem);
	}
}

void displayMaps() {
	for (int mapsCnt = 0; mapsCnt < (int)maps.size(); ++mapsCnt) {
		bool mapAlwaysDisplayMap = maps[mapsCnt].getAlwaysDisplayMap();

		if (activeMapIndex > -1 && mapAlwaysDisplayMap == false && maps[mapsCnt].display == true || mapAlwaysDisplayMap == true) {
			maps[mapsCnt].render();
		}
	}
}

void centreCamera(areaStruct position) {
	camera.area.x = position.x + roundDiv(position.w, 2) - roundDiv(camera.area.w, 2);

	camera.area.y = position.y + roundDiv(position.h, 2) - roundDiv(camera.area.h, 2);

	int layerIndex = characters[controlledCharacterIndex].getLayerIndex();

	if (camera.area.x < 0) {
		camera.area.x = 0;
	}
	if (camera.area.x + camera.area.w - 1 > ((int)overworldGrid.gridTile[layerIndex].size() - 1) * tileSize.w) {
		camera.area.x = (((int)overworldGrid.gridTile[layerIndex].size() - 1) * tileSize.w) - camera.area.w;
	}

	if (camera.area.y < 0) {
		camera.area.y = 0;
	}
	if (camera.area.y + camera.area.h - 1 > ((int)overworldGrid.gridTile[layerIndex][0].size() - 1) * tileSize.h) {
		camera.area.y = (((int)overworldGrid.gridTile[layerIndex][0].size() - 1) * tileSize.h) - camera.area.h;
	}
}

headerMenuVarsStruct getHeaderMenuVar(string name) {
	for (int headerMenuVarsCnt = 0; headerMenuVarsCnt < (int)headerMenuVars.size(); ++headerMenuVarsCnt) {
		if (headerMenuVars[headerMenuVarsCnt].name == name) {
			return headerMenuVars[headerMenuVarsCnt];
		}
	}

	headerMenuVarsStruct currentHeaderMenuVars;
	return currentHeaderMenuVars;
}

void displayCharacterMenus(int characterIndex) {
	characters[characterIndex].displayCharacterMenu();
	//characters[characterIndex].displayMenuHeaders();
}

string getNthButtonPressedName(int Nth) {
	struct buttonDataStruct {
		string name;
		bool pressed;
		Uint32 startTicks;
		bool exclude = false;
	};
	vector<buttonDataStruct> buttonData;

	//Insert all button data in buttonData
	buttonData.push_back({ "A", controllerButtons.A, controllerButtonStartTicks.A });
	buttonData.push_back({ "B", controllerButtons.B, controllerButtonStartTicks.B });
	buttonData.push_back({ "X", controllerButtons.X, controllerButtonStartTicks.X });
	buttonData.push_back({ "Y", controllerButtons.Y, controllerButtonStartTicks.Y });
	buttonData.push_back({ "LB", controllerButtons.LB, controllerButtonStartTicks.LB });
	buttonData.push_back({ "RB", controllerButtons.RB, controllerButtonStartTicks.RB });
	buttonData.push_back({ "select", controllerButtons.select, controllerButtonStartTicks.select });
	buttonData.push_back({ "start", controllerButtons.start, controllerButtonStartTicks.start });
	buttonData.push_back({ "LJ", controllerButtons.LJ, controllerButtonStartTicks.LJ });
	buttonData.push_back({ "RJ", controllerButtons.RJ, controllerButtonStartTicks.RJ });
	buttonData.push_back({ "up", hatButtons.up, hatButtonsStartTicks.up });
	buttonData.push_back({ "right", hatButtons.right, hatButtonsStartTicks.right });
	buttonData.push_back({ "rightUp", hatButtons.rightUp, hatButtonsStartTicks.rightUp });
	buttonData.push_back({ "down", hatButtons.down, hatButtonsStartTicks.down });
	buttonData.push_back({ "rightDown", hatButtons.rightDown, hatButtonsStartTicks.rightDown });
	buttonData.push_back({ "left", hatButtons.left, hatButtonsStartTicks.left });
	buttonData.push_back({ "leftUp", hatButtons.leftUp, hatButtonsStartTicks.leftUp });
	buttonData.push_back({ "leftDown", hatButtons.leftDown, hatButtonsStartTicks.leftDown });
	buttonData.push_back({ "LT", leftTrigger.activated, leftTrigger.pressedStartTicks });
	buttonData.push_back({ "RT", rightTrigger.activated, rightTrigger.pressedStartTicks });

	//Get Nth button pressed
	string NthName = "";
	for (int NthCnt = 0; NthCnt < Nth; ++NthCnt) {
		Uint32 highestStartTicks = 0;
		string buttonName = "";
		int buttonDataIndex = -1;
		for (int buttonDataCnt = 0; buttonDataCnt < (int)buttonData.size(); ++buttonDataCnt) {
			if (buttonData[buttonDataCnt].exclude == false && buttonData[buttonDataCnt].pressed == true && buttonData[buttonDataCnt].startTicks > highestStartTicks) {
				buttonDataIndex = buttonDataCnt;
				highestStartTicks = buttonData[buttonDataCnt].startTicks;
				buttonName = buttonData[buttonDataCnt].name;
			}
		}
		if (buttonDataIndex > -1) {
			buttonData[buttonDataIndex].exclude = true;
			NthName = buttonData[buttonDataIndex].name;
		}
		else {
			break;
		}
	}

	return NthName;
}

//int getMenuIndex(string name) {
//	for (int menusCnt = 0; menusCnt < (int)menus.size(); ++menusCnt) {
//		if (menus[menusCnt].menuVarsName == name) {
//			return menusCnt;
//		}
//	}
//	return -1;
//}

void setOverworldGridCollision(vector<vector<vector<gridTileStruct>>>& overworldGridTiles, int layerIndex, areaStruct gridArea, bool collision) {
	if (layerIndex < (int)overworldGridTiles.size() && gridArea.x < (int)overworldGridTiles[layerIndex].size() && gridArea.y < (int)overworldGridTiles[layerIndex][gridArea.x].size()) {
		for (int gridAreaXCnt = gridArea.x; gridAreaXCnt < gridArea.x + gridArea.w; ++gridAreaXCnt) {
			for (int gridAreaYCnt = gridArea.y; gridAreaYCnt < gridArea.y + gridArea.h; ++gridAreaYCnt) {
				if (layerIndex < (int)overworldGridTiles.size() && gridAreaXCnt < (int)overworldGridTiles[layerIndex].size() && gridAreaYCnt < (int)overworldGridTiles[layerIndex][gridAreaXCnt].size()) {
					overworldGridTiles[layerIndex][gridAreaXCnt][gridAreaYCnt].collidable = collision;
				}
			}
		}
	}
}

void setMazeCollision(vector<vector<bool>>& maze, areaStruct gridArea, bool collision) {
	if (gridArea.x < (int)maze.size() && gridArea.y < (int)maze[0].size()) {
		for (int mazeXCnt = gridArea.x; mazeXCnt < gridArea.x + gridArea.w; ++mazeXCnt) {
			for (int mazeYCnt = gridArea.y; mazeYCnt < gridArea.y + gridArea.h; ++mazeYCnt) {
				if (areaWithinArea({ mazeXCnt, mazeYCnt }, { 0, 0, (int)maze.size(), (int)maze[0].size() })) {
					maze[mazeXCnt][mazeYCnt] = collision;
				}
			}
		}
	}
}

void updateSettingsFile() {
	emptyFile("assets\\misc\\settings.txt");
	const vector<string> data = { str(fullscreen), str(aspectRatio.ratio.w), str(aspectRatio.ratio.h), str(windowResolution.w), str(windowResolution.h), str(vSyncOn), str(FPSCap) };
	for (int dataCnt = 0; dataCnt < (int)data.size(); ++dataCnt) {
		appendToFile("assets\\misc\\settings.txt", data[dataCnt]);
	}
}

void loadSettingsFile() {
	vector<string> data = readFile("assets\\misc\\settings.txt");
	if ((int)data.size() == 7) {
		fullscreen = toInt(data[0]);
		aspectRatio.ratio.w = toInt(data[1]);
		aspectRatio.ratio.h = toInt(data[2]);
		windowResolution.w = toInt(data[3]);
		windowResolution.h = toInt(data[4]);
		vSyncOn = toInt(data[5]);
		FPSCap = toInt(data[6]);
	}
}

void mainMenu() {

	//Set option values
	vector<string> optionValueStrings;
	if (fullscreen == true) {
		optionValueStrings.push_back("Fullscreen");
	}
	else {
		optionValueStrings.push_back("Window");
	}
	optionValueStrings.push_back(formatStr("{}:{}", { str(aspectRatio.ratio.w), str(aspectRatio.ratio.h) }));
	optionValueStrings.push_back(formatStr("{} x {}", { str(windowResolution.w), str(windowResolution.h) }));
	if (vSyncOn == true) {
		optionValueStrings.push_back("On");
	}
	else {
		optionValueStrings.push_back("Off");
	}
	optionValueStrings.push_back(str(FPSCap));
	struct optionValueStruct {
		int mainMenuIndex, optionIndex;
		string value;
	};
	vector<optionValueStruct> optionValues = {
		{ 2, 0, "" },
		{ 2, 1, "" },
		{ 2, 2, "" },
		{ 2, 3, "" },
		{ 2, 4, "" }
	};
	for (int optionValueStringsCnt = 0; optionValueStringsCnt < (int)optionValueStrings.size(); ++optionValueStringsCnt) {
		optionValues[optionValueStringsCnt].value = optionValueStrings[optionValueStringsCnt];
	}

	//Init main menus
	if ((int)mainMenus.size() == 0) {
		mainMenus = {
			{
				"Cyberpunk Sim",
				{
					{ "Continue", "", { mainMenuStruct::optionStruct::actionTypeEnum::continueGame, mainMenuStruct::optionStruct::actionTypeEnum::exitMenu }, -1 },
					{ "New Game", "", { mainMenuStruct::optionStruct::actionTypeEnum::newGame, mainMenuStruct::optionStruct::actionTypeEnum::exitMenu }, -1 },
					{ "Options", "", { mainMenuStruct::optionStruct::actionTypeEnum::none }, 1 },
					{ "Exit", "", { mainMenuStruct::optionStruct::actionTypeEnum::exitGame }, -1 }
				},
				-1
			},
			{
				"Options",
				{
					{ "Video", "", { mainMenuStruct::optionStruct::actionTypeEnum::none }, 2 },
					{ "Audio", "", { mainMenuStruct::optionStruct::actionTypeEnum::none }, -1 }
				},
				0
			},
			{
				"Video",
				{
					{ "Screen", "", { mainMenuStruct::optionStruct::actionTypeEnum::none }, 3 },
					{ "Aspect Ratio", "", { mainMenuStruct::optionStruct::actionTypeEnum::none }, 4 },
					{ "Resolution", "", { mainMenuStruct::optionStruct::actionTypeEnum::none }, 5 },
					{ "VSync", "", { mainMenuStruct::optionStruct::actionTypeEnum::none }, 6 },
					{ "Framerate Cap", "", { mainMenuStruct::optionStruct::actionTypeEnum::none }, 7 }
				},
				1
			},
			{
				"Screen",
				{
					{ "Fullscreen", "", { mainMenuStruct::optionStruct::actionTypeEnum::setScreen }, 2 },
					{ "Window", "", { mainMenuStruct::optionStruct::actionTypeEnum::setScreen }, 2 }
				},
				2
			},
			{
				"Aspect Ratio",
				{
					{ "16:9", "", { mainMenuStruct::optionStruct::actionTypeEnum::setAspectRatio }, 2 },
					{ "16:10", "", { mainMenuStruct::optionStruct::actionTypeEnum::setAspectRatio }, 2 },
					{ "4:3", "", { mainMenuStruct::optionStruct::actionTypeEnum::setAspectRatio }, 2 }
				},
				2
			},
			{
				"Resolution",
				{
					{ "3840 x 2160", "", { mainMenuStruct::optionStruct::actionTypeEnum::setResolution }, 2 },
					{ "2560 x 1440", "", { mainMenuStruct::optionStruct::actionTypeEnum::setResolution }, 2 },
					{ "1920 x 1080", "", { mainMenuStruct::optionStruct::actionTypeEnum::setResolution }, 2 },
					{ "1600 x 900", "", { mainMenuStruct::optionStruct::actionTypeEnum::setResolution }, 2 },
					{ "1280 x 720", "", { mainMenuStruct::optionStruct::actionTypeEnum::setResolution }, 2 }
				},
				2
			},
			{
				"VSync",
				{
					{ "On", "", { mainMenuStruct::optionStruct::actionTypeEnum::setVSync }, 2 },
					{ "Off", "", { mainMenuStruct::optionStruct::actionTypeEnum::setVSync }, 2 }
				},
				2
			},
			{
				"Frame rate",
				{
					{ "120", "", { mainMenuStruct::optionStruct::actionTypeEnum::setFPSCap }, 2 },
					{ "60", "", { mainMenuStruct::optionStruct::actionTypeEnum::setFPSCap }, 2 },
					{ "30", "", { mainMenuStruct::optionStruct::actionTypeEnum::setFPSCap }, 2 }
				},
				2
			}
		};
	}

	//Update main menu option values
	for (int optionValuesCnt = 0; optionValuesCnt < (int)optionValues.size(); ++optionValuesCnt) {
		mainMenus[optionValues[optionValuesCnt].mainMenuIndex].options[optionValues[optionValuesCnt].optionIndex].value = optionValues[optionValuesCnt].value;
	}

	//Display current main menu
	vector<iconStruct> icons;
	vector<vector<string>> iconTextBlock;

	for (int optionsCnt = 0; optionsCnt < (int)mainMenus[currentMainMenuIndex].options.size(); ++optionsCnt) {
		icons.push_back(blankIcon);
		iconTextBlock.push_back({ mainMenus[currentMainMenuIndex].options[optionsCnt].name, mainMenus[currentMainMenuIndex].options[optionsCnt].value });
	}

	string menuVarsName = mainMenus[currentMainMenuIndex].title;

	displayMenu(menuVarsName, menuVarsStruct::styleEnum::list, { textLogicalSize.w / 2, textLogicalSize.h / 2 }, menuVarsName, true, icons, iconTextBlock, { 10, 5 }, tileSize, (int)iconTextBlock.size(), defaultFont, defaultColour, selectedIconSprite, 0, false, 75, false, false, false, {  });

	int selectedOption = menuVars[getMenuVarsIndex(menuVarsName)].scrollCursor;

	if (controllerButtons.A == true) {
		controllerButtons.A = false;

		//Perform actions
		for (int actionTypesCnt = 0; actionTypesCnt < (int)mainMenus[currentMainMenuIndex].options[selectedOption].actionTypes.size(); ++actionTypesCnt) {
			switch (mainMenus[currentMainMenuIndex].options[selectedOption].actionTypes[actionTypesCnt]) {
			case mainMenuStruct::optionStruct::actionTypeEnum::continueGame: {

				break;
			}
			case mainMenuStruct::optionStruct::actionTypeEnum::newGame: {

				break;
			}
			case mainMenuStruct::optionStruct::actionTypeEnum::exitGame: {
				exitMainLoop = true;
				break;
			}
			case mainMenuStruct::optionStruct::actionTypeEnum::setScreen: {
				//bool originalFullscreen = fullscreen;
				if (mainMenus[currentMainMenuIndex].options[selectedOption].name == "Fullscreen") {
					fullscreen = true;
				}
				else {
					fullscreen = false;
				}
				destroyWindowAndRenderer();
				initWindowAndRenderer();
				initSpriteSheets();
				destroyMaps();
				initMaps();
				updateSettingsFile();
				//fullscreen = originalFullscreen;
				break;
			}
			case mainMenuStruct::optionStruct::actionTypeEnum::setAspectRatio: {
				//WHStruct originalAspectRatio = aspectRatio.ratio;
				if (mainMenus[currentMainMenuIndex].options[selectedOption].name == "16:9") {
					aspectRatio.ratio.w = 16;
					aspectRatio.ratio.h = 9;
				}
				else if (mainMenus[currentMainMenuIndex].options[selectedOption].name == "16:10") {
					aspectRatio.ratio.w = 16;
					aspectRatio.ratio.h = 10;
				}
				else if (mainMenus[currentMainMenuIndex].options[selectedOption].name == "4:3") {
					aspectRatio.ratio.w = 4;
					aspectRatio.ratio.h = 3;
				}
				initLevel();
				updateSettingsFile();
				//aspectRatio.ratio = originalAspectRatio;
				break;
			}
			case mainMenuStruct::optionStruct::actionTypeEnum::setResolution: {
				//WHStruct originalResolution = windowResolution;
				if (mainMenus[currentMainMenuIndex].options[selectedOption].name == "3840 x 2160") {
					windowResolution.w = 3840;
					windowResolution.h = 2160;
				}
				else if (mainMenus[currentMainMenuIndex].options[selectedOption].name == "2560 x 1440") {
					windowResolution.w = 2560;
					windowResolution.h = 1440;
				}
				else if (mainMenus[currentMainMenuIndex].options[selectedOption].name == "1920 x 1080") {
					windowResolution.w = 1920;
					windowResolution.h = 1080;
				}
				else if (mainMenus[currentMainMenuIndex].options[selectedOption].name == "1600 x 900") {
					windowResolution.w = 1600;
					windowResolution.h = 900;
				}
				else if (mainMenus[currentMainMenuIndex].options[selectedOption].name == "1280 x 720") {
					windowResolution.w = 1280;
					windowResolution.h = 720;
				}
				destroyWindowAndRenderer();
				initWindowAndRenderer();
				initSpriteSheets();
				updateSettingsFile();
				//windowResolution = originalResolution;
				break;
			}
			case mainMenuStruct::optionStruct::actionTypeEnum::setVSync: {
				//bool originalVSyncOn = vSyncOn;
				if (mainMenus[currentMainMenuIndex].options[selectedOption].name == "On") {
					vSyncOn = true;
				}
				else {
					vSyncOn = false;
				}
				destroyWindowAndRenderer();
				initWindowAndRenderer();
				initSpriteSheets();
				updateSettingsFile();
				//vSyncOn = originalVSyncOn;
				break;
			}
			case mainMenuStruct::optionStruct::actionTypeEnum::setFPSCap: {
				if (mainMenus[currentMainMenuIndex].options[selectedOption].name == "120") {
					FPSCap = 120;
				}
				else if (mainMenus[currentMainMenuIndex].options[selectedOption].name == "60") {
					FPSCap = 60;
				}
				else if (mainMenus[currentMainMenuIndex].options[selectedOption].name == "30") {
					FPSCap = 30;
				}
				updateSettingsFile();
				break;
			}
			case mainMenuStruct::optionStruct::actionTypeEnum::exitMenu: {
				displayMainMenu = false;
				break;
			}
			}
		}

		if (mainMenus[currentMainMenuIndex].options[selectedOption].mainMenuIndex > -1) {
			currentMainMenuIndex = mainMenus[currentMainMenuIndex].options[selectedOption].mainMenuIndex;
		}

		mainMenuSelectedOption = selectedOption;
	}
	if (controllerButtons.B == true) {
		if (currentMainMenuIndex == 0) {
			controllerButtons.B = false;
			exitMainLoop = true;
		}
		else {
			if (mainMenus[currentMainMenuIndex].backMainMenuIndex > -1) {
				controllerButtons.B = false;
				currentMainMenuIndex = mainMenus[currentMainMenuIndex].backMainMenuIndex;
			}
		}
	}
}

void foo(int Z) {
	for (int i = 0; i < Z; i++) {
		//cout << "Thread using function pointer as callable\n";
		printStr(formatStr("{} {}", { "foo", str(i) }));
	}
}

class Thread_obj {
public:
	void operator()(int x) {
		for (int i = 0; i < x; i++) {
			//cout << "Thread using function object as callable\n";
			printStrL({ "Thread_obj", str(i) });
		}
	}
};

void changeOverworldRegion() {
	if (changeOverworldRegionBool == true) {
		changeOverworldRegionBool = false;
		XYUnsignedIntStruct originalOverworldRegionPosition = regionGrid.position;

		//Update overworld region position
		if (collisionData.regionCorner == collisionStruct::regionCornerEnum::down && regionGrid.position.y < getMaxUnsignedIntValue()) {
			++regionGrid.position.y;
		}
		else if (collisionData.regionCorner == collisionStruct::regionCornerEnum::up && regionGrid.position.y > 0) {
			--regionGrid.position.y;
		}
		else if (collisionData.regionCorner == collisionStruct::regionCornerEnum::right && regionGrid.position.x < getMaxUnsignedIntValue()) {
			++regionGrid.position.x;
		}
		else if (collisionData.regionCorner == collisionStruct::regionCornerEnum::left && regionGrid.position.x > 0) {
			--regionGrid.position.x;
		}

		//Init new level
		if (regionGrid.position.x != originalOverworldRegionPosition.x || regionGrid.position.y != originalOverworldRegionPosition.y) {
			initLevel();

			//Set player characters' new positions
			for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
				XYStruct characterPosition = characters[charactersCnt].getPosition();
				WHStruct characterSpriteTargetSize = characters[charactersCnt].getSpriteTargetSize();
				switch (collisionData.regionCorner) {
				case collisionStruct::regionCornerEnum::down: {
					characterPosition.y = tileSize.h;
					break;
				}
				case collisionStruct::regionCornerEnum::up: {
					characterPosition.y = ((int)overworldGrid.gridTile[characters[charactersCnt].getLayerIndex()][0].size() * tileSize.h) - characterSpriteTargetSize.h - tileSize.h;
					break;
				}
				case collisionStruct::regionCornerEnum::right: {
					characterPosition.x = tileSize.w;
					break;
				}
				case collisionStruct::regionCornerEnum::left: {
					characterPosition.x = ((int)overworldGrid.gridTile[characters[charactersCnt].getLayerIndex()].size() * tileSize.w) - characterSpriteTargetSize.w - tileSize.w;
					break;
				}
				}
				characters[charactersCnt].setPosition(characterPosition);
			}

		}

	}
}

int getMapIndexByName(string mapName) {
	for (int mapsCnt = 0; mapsCnt < (int)maps.size(); ++mapsCnt) {
		if (maps[mapsCnt].getName() == mapName) {
			return mapsCnt;
		}
	}
	return -1;
}

void activateMap() {
	if (controllerButtons.select == true) {
		controllerButtons.select = false;
		if (activeMapIndex == -1) {
			activeMapIndex = 0;
			maps[activeMapIndex].display = true;
		}
		else {
			if (maps[activeMapIndex].getAlwaysDisplayMap() == false) {
				maps[activeMapIndex].display = false;
			}
			if (activeMapIndex < (int)maps.size() - 1) {
				++activeMapIndex;
				maps[activeMapIndex].display = true;
			}
			else {
				activeMapIndex = -1;
			}
		}
	}
}

void mapActions() {
	activateMap();
}

int getOrganisationIndex(int organisationID) {
	for (int organisationsCnt = 0; organisationsCnt < (int)organisations.size(); ++organisationsCnt) {
		if (organisations[organisationsCnt].getID() == organisationID) {
			return organisationsCnt;
		}
	}
	return -1;
}

void organisationRenders() {
	for (int organisationsCnt = 0; organisationsCnt < (int)organisations.size(); ++organisationsCnt) {
		organisations[organisationsCnt].displayHierarchy();
	}
}

timeStruct updateGameClock(timeStruct gameClock, Uint32 millisecondsPassed) {
	timeStruct addedTime;
	addedTime.second = millisecondsPassed / 1000;
	return addTime(gameClock, addedTime);
}

vector<vector<bool>> createMaze(WHStruct size) {
	vector<vector<bool>> maze;
	maze.resize(size.w);
	for (int mazeXCnt = 0; mazeXCnt < (int)maze.size(); ++mazeXCnt) {
		maze[mazeXCnt].resize(size.h);
	}
	return maze;
}

void initMaze(vector<vector<bool>>& maze, bool nodeValue) {
	for (int mazeXCnt = 0; mazeXCnt < (int)maze.size(); ++mazeXCnt) {
		for (int mazeYCnt = 0; mazeYCnt < (int)maze.size(); ++mazeYCnt) {
			maze[mazeXCnt][mazeYCnt] = nodeValue;
		}
	}
}

void initMazeToOverworldGrid(vector<vector<bool>>& maze, vector<vector<vector<gridTileStruct>>>& overworldGridTiles, int overworldGridLayer, WHStruct nodeGridSize) {
	XYStruct mazeCnt = { 0, 0 };
	for (int overworldGridTilesXCnt = 0; overworldGridTilesXCnt < (int)overworldGridTiles[overworldGridLayer].size(); overworldGridTilesXCnt += nodeGridSize.w) {
		mazeCnt.y = 0;
		for (int overworldGridTilesYCnt = 0; overworldGridTilesYCnt < (int)overworldGridTiles[overworldGridLayer][overworldGridTilesXCnt].size(); overworldGridTilesYCnt += nodeGridSize.h) {
			bool collidable = false;

			//Check if there is a collidable tile
			for (int tileXCnt = overworldGridTilesXCnt; tileXCnt < overworldGridTilesXCnt + nodeGridSize.w; ++tileXCnt) {
				for (int tileYCnt = overworldGridTilesYCnt; tileYCnt < overworldGridTilesYCnt + nodeGridSize.h; ++tileYCnt) {
					if (/*areaWithinGrid({tileXCnt, tileYCnt, 1, 1}, overworldGridLayer) == true && */overworldGridTiles[overworldGridLayer][tileXCnt][tileYCnt].collidable == true) {
						collidable = true;
						goto exitCheckCollidableTile;
					}
				}
			}
		exitCheckCollidableTile:

			//if (areaWithinArea({ mazeCnt.x, mazeCnt.y, 1, 1 }, { 0, 0, (int)maze.size(), (int)maze[0].size() }) == true) {
			maze[mazeCnt.x][mazeCnt.y] = collidable;
			//}
			++mazeCnt.y;
		}
		++mazeCnt.x;
	}
}

void printDirection(directionEnum direction) {
	printStr(formatStr("up {}, down {}, left {}, right {}, upRight {}, downRight {}, downLeft {}, upLeft {}", { str(direction == directionEnum::up), str(direction == directionEnum::down), str(direction == directionEnum::left), str(direction == directionEnum::right), str(direction == directionEnum::upRight), str(direction == directionEnum::downRight), str(direction == directionEnum::downLeft), str(direction == directionEnum::upLeft) }));
}

bool compareFindObjectDataByHeuristic(findObjectDataStruct objectData1, findObjectDataStruct objectData2) {
	return objectData1.heuristic < objectData2.heuristic;
}

closestObjectStruct findClosestObject(vector<Object>& objects, string objectType, XYStruct positionToCompareTo, int nthLowestHeuristic) {
	closestObjectStruct closestObject;
	closestObject.objectType = objectType;

	vector<findObjectDataStruct> objectList;

	//Get all objects of given object type
	for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
		if (objects[objectsCnt].getType() == objectType) {
			findObjectDataStruct currentObjectData;
			currentObjectData.index = objectsCnt;
			currentObjectData.ID = objects[objectsCnt].getID();
			objectList.push_back(currentObjectData);
		}
	}

	//Get heuristics of objects of given type
	for (int objectListCnt = 0; objectListCnt < (int)objectList.size(); ++objectListCnt) {
		SDL_Rect objectDRect = objects[objectList[objectListCnt].index].getObjectDRect();
		objectList[objectListCnt].heuristic = getHeuristic(positionToCompareTo, { objectDRect.x, objectDRect.y });
	}

	//Sort object list by heuristic (lowest to highest)
	sort(objectList.begin(), objectList.end(), compareFindObjectDataByHeuristic);

	//Get object with nth lowest heuristic
	if (nthLowestHeuristic > 0) {
		for (int objectListCnt = 0; objectListCnt < (int)objectList.size(); ++objectListCnt) {
			if (objectListCnt == nthLowestHeuristic) {
				SDL_Rect objectDRect = objects[objectList[objectListCnt].index].getObjectDRect();
				closestObject.position = { objectDRect.x, objectDRect.y };
				closestObject.size = { objectDRect.w, objectDRect.h };
				closestObject.heuristic = objectList[objectListCnt].heuristic;
				closestObject.ID = objectList[objectListCnt].ID;
				return closestObject;
			}
		}
	}

	return closestObject;
}

void createMazeAndGetAStarPath(areaStruct startPixelArea, areaStruct endPixelArea, int overworldLayerIndex, WHStruct mazeNodeGridSize, pathStruct& characterPath, bool startCollision, bool endCollision) {
	WHStruct mazeSize = { (int)overworldGrid.gridTile[overworldLayerIndex].size() / mazeNodeGridSize.w, (int)overworldGrid.gridTile[overworldLayerIndex][0].size() / mazeNodeGridSize.h };
	vector<vector<bool>> maze = createMaze(mazeSize);

	initMazeToOverworldGrid(maze, overworldGrid.gridTile, overworldLayerIndex, mazeNodeGridSize);

	if (characterPath.clearPath == true && (int)characterPath.pathToFollow.size() > 0) {
		characterPath.pathToFollow.clear();
	}

	areaStruct startPixelGridArea = { lround(startPixelArea.x / mazeNodeGridSize.w), lround(startPixelArea.y / mazeNodeGridSize.h), lround(startPixelArea.w / mazeNodeGridSize.w), lround(startPixelArea.h / mazeNodeGridSize.w) };
	areaStruct endPixelGridArea = { lround(endPixelArea.x / mazeNodeGridSize.w), lround(endPixelArea.y / mazeNodeGridSize.h), lround(endPixelArea.w / mazeNodeGridSize.w), lround(endPixelArea.h / mazeNodeGridSize.w) };

	//Remove collision at start pixel area
	setMazeCollision(maze, startPixelGridArea, false);

	//Remove collision at end pixel area
	setMazeCollision(maze, endPixelGridArea, false);

	vector<XYStruct> returnedPath = getAStarPath(maze, { startPixelGridArea.x, startPixelGridArea.y }, { endPixelGridArea.x, endPixelGridArea.y });

	//Add returned path to path to follow
	if (characterPath.clearPath == false && (int)returnedPath.size() > 0 && characterPath.pathFound == false) {
		characterPath.pathToFollow.insert(characterPath.pathToFollow.end(), returnedPath.begin(), returnedPath.end());
	}

	//Check if path found
	if (characterPath.pathFound == false) {
		for (int pathToFollowCnt = 0; pathToFollowCnt < (int)characterPath.pathToFollow.size(); ++pathToFollowCnt) {
			if (characterPath.pathToFollow[pathToFollowCnt].x == endPixelGridArea.x && characterPath.pathToFollow[pathToFollowCnt].y == endPixelGridArea.y) {
				characterPath.pathFound = true;
				break;
			}
		}
	}

}

//functions end

//class functions start

Character::Character(characterConstructorVarsStruct characterConstructorVars, characterConstructorScheduleVarsStruct characterConstructorScheduleVars) {
	ID = characterConstructorVars.ID;
	layerIndex = characterConstructorVars.layerIndex;
	name = characterConstructorVars.name;
	position = characterConstructorVars.position;
	regionPosition = characterConstructorVars.regionPosition;
	direction = characterConstructorVars.direction;
	spriteIndex = characterConstructorVars.spriteIndex;
	spriteSheetIndex = characterConstructorVars.spriteSheetIndex;
	spriteType = characterConstructorVars.spriteType;
	spriteTargetSize = characterConstructorVars.spriteTargetSize;
	sprites = characterConstructorVars.sprites;
	stats = characterConstructorVars.stats;
	misc = characterConstructorVars.misc;
	spriteUpdate = characterConstructorVars.spriteUpdate;
	skills = characterConstructorVars.skills;
	statusEffects = characterConstructorVars.statusEffects;
	abilities = characterConstructorVars.abilities;
	ammos = characterConstructorVars.ammos;
	cyberwares = characterConstructorVars.cyberwares;
	gears = characterConstructorVars.gears;
	weapons = characterConstructorVars.weapons;
	consumableItems = characterConstructorVars.consumableItems;
	miscItems = characterConstructorVars.miscItems;
	blueprints = characterConstructorVars.blueprints;
	craftingItems = characterConstructorVars.craftingItems;
	quickslots = characterConstructorVars.quickslots;
	cyberwareEquipmentSlots = characterConstructorVars.cyberwareEquipmentSlots;
	gearEquipmentSlots = characterConstructorVars.gearEquipmentSlots;
	weaponEquipmentSlots = characterConstructorVars.weaponEquipmentSlots;
	privateCharacterConstructorScheduleVars = characterConstructorScheduleVars;
	sleep = characterConstructorVars.sleep;
}

int Character::getID() {
	return ID;
}

int Character::getLayerIndex() {
	return layerIndex;
}

XYStruct Character::getPosition() {
	return position;
}

void Character::setPosition(XYStruct characterPosition) {
	position = characterPosition;
}

directionEnum Character::getDirection() {
	return direction;
}

WHStruct Character::getSpriteTargetSize() {
	return spriteTargetSize;
}

vector<characterConstructorVarsStruct::statStruct> Character::getStats() {
	return stats;
}

void Character::setStats(vector<characterConstructorVarsStruct::statStruct> characterStats) {
	stats = characterStats;
}

vector<characterConstructorVarsStruct::abilityStruct> Character::getAbilities() {
	return abilities;
}

vector<characterConstructorVarsStruct::ammoStruct> Character::getAmmos() {
	return ammos;
}

vector<characterConstructorVarsStruct::quickslotsStruct> Character::getQuickslots() {
	return quickslots;
}

vector<blueprintStruct> Character::getBlueprints() {
	return blueprints;
}

vector<characterConstructorVarsStruct::cyberwareStruct> Character::getCyberwares() {
	return cyberwares;
}

vector<characterConstructorVarsStruct::gearStruct> Character::getGear() {
	return gears;
}

vector<characterConstructorVarsStruct::weaponStruct> Character::getWeapons() {
	return weapons;
}

vector<characterConstructorVarsStruct::consumableItemStruct> Character::getConsumableItems() {
	return consumableItems;
}

string Character::getName() {
	return name;
}

//int Character::getObjectReachedID() {
//	return objectReachedID;
//}

void Character::setOrganisation(Character::organisationStruct currentOrganisation) {
	organisation = currentOrganisation;
}

void Character::render() {
	if (areaWithinCameraView({ position.x, position.y, spriteTargetSize.w, spriteTargetSize.h }) == true) {
		if (sleep.state == false) {

			//Render character sprite
			switch (spriteType) {
				case characterConstructorVarsStruct::spriteTypeEnum::single: {
					sRect = convertAreaToSDLRect(sprites[(int)direction][spriteIndex]);
					dRect = { position.x - camera.area.x, position.y - camera.area.y, spriteTargetSize.w, spriteTargetSize.h };
					SDL_RenderCopy(renderer, spriteSheets[spriteSheetIndex].texture, &sRect, &dRect);
					break;
				}
				case characterConstructorVarsStruct::spriteTypeEnum::combo: {
					XYStruct bodyPartPosition = position;
					WHStruct bodyPartSize = { spriteTargetSize.w / (int)bodyParts[(int)direction][spriteIndex].size(), spriteTargetSize.h / (int)bodyParts[(int)direction][spriteIndex][0].size() };
					for (int bodyPartsXCnt = 0; bodyPartsXCnt < (int)bodyParts[(int)direction][spriteIndex].size(); ++bodyPartsXCnt) {
						bodyPartPosition.y = position.y;
						for (int bodyPartsYCnt = 0; bodyPartsYCnt < (int)bodyParts[(int)direction][spriteIndex].size(); ++bodyPartsYCnt) {
							dRect = { bodyPartPosition.x, bodyPartPosition.y, bodyPartSize.w, bodyPartSize.h };
							SDL_RenderCopy(renderer, spriteSheets[spriteSheetIndex].texture, &bodyParts[(int)direction][spriteIndex][bodyPartsXCnt][bodyPartsYCnt].bodyPartSRect, &dRect);
							bodyPartPosition.y += dRect.h;
						}
						bodyPartPosition.x = dRect.w;
					}
					break;
				}
			}

		}
		else {

			//Render sleep sprite
			dRect = { position.x - camera.area.x, position.y - camera.area.y, spriteTargetSize.w, spriteTargetSize.h };
			SDL_RenderCopy(renderer, spriteSheets[sleep.spriteSheetIndex].texture, &sleep.spriteSRect, &dRect);

		}

		//Display character ID
		WHStruct previousLogicalSize = { -1, -1 };
		SDL_RenderGetLogicalSize(renderer, &previousLogicalSize.w, &previousLogicalSize.h);
		//setSDLLogicalSize(textLogicalSize);
		/*SDL_Texture* previousRenderTarget = SDL_GetRenderTarget(renderer);
		setSDLRenderTarget(NULL);*/
		//XYStruct textPosition = convertPosition(position, previousLogicalSize, textLogicalSize);
		renderText(str(ID), defaultFont, defaultColour, { position.x - camera.area.x, position.y - camera.area.y - getTextSize(str(ID), defaultFont).h });
		setSDLLogicalSize(previousLogicalSize);
		//setSDLRenderTarget(previousRenderTarget);

	}
}

void Character::renderEquippedWeapon() {
	for (int weaponEquipmentSlotsCnt = 0; weaponEquipmentSlotsCnt < (int)weaponEquipmentSlots.size(); ++weaponEquipmentSlotsCnt) {
		int equippedWeaponIndex = weaponEquipmentSlots[weaponEquipmentSlotsCnt].equipmentIndex;
		if (equippedWeaponIndex > -1) {
			bool renderWeapon = true;

			//Check if any ability from this weapon is running
			if (weapons[equippedWeaponIndex].renderWhenAnimationRunning == false) {
				for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
					if (abilities[abilitiesCnt].source.name == "Weapon" && abilities[abilitiesCnt].source.index == equippedWeaponIndex && abilities[abilitiesCnt].animations[0].running == true) {
						renderWeapon = false;
						break;
					}
				}
			}

			if (renderWeapon == true) {
				weapons[equippedWeaponIndex].position = { position.x + (spriteTargetSize.w / 2), position.y + (spriteTargetSize.h / 2) };
				weapons[equippedWeaponIndex].rotation.centre = { 0, weapons[equippedWeaponIndex].icon.spriteSheetArea.h / 2 };
				if (weapons[equippedWeaponIndex].rangeType == "Melee") {

					//Set melee weapon rotation angle based on character current direction
					switch (direction) {
					case directionEnum::right: {
						/*weapons[equippedWeaponIndex].position.x += spriteTargetSize.w / 2;
						weapons[equippedWeaponIndex].position.y += spriteTargetSize.h / 2;*/
						weapons[equippedWeaponIndex].rotation.angle = 0;
						break;
					}
					case directionEnum::left: {
						weapons[equippedWeaponIndex].rotation.angle = 180;
						break;
					}
					case directionEnum::down: {
						weapons[equippedWeaponIndex].rotation.angle = 90;
						break;
					}
					case directionEnum::up: {
						weapons[equippedWeaponIndex].rotation.angle = -90;
						break;
					}
					case directionEnum::upRight: {
						weapons[equippedWeaponIndex].rotation.angle = -45;
						break;
					}
					case directionEnum::downRight: {
						weapons[equippedWeaponIndex].rotation.angle = 45;
						break;
					}
					case directionEnum::downLeft: {
						weapons[equippedWeaponIndex].rotation.angle = 135;
						break;
					}
					case directionEnum::upLeft: {
						weapons[equippedWeaponIndex].rotation.angle = -135;
						break;
					}
					}

				}
				else if (weapons[equippedWeaponIndex].rangeType == "Ranged") {

					//Set ranged weapon rotation angle based on angle of right stick
					weapons[equippedWeaponIndex].rotation.angle = lround((float)((atan2(rightJoystickAxisX, rightJoystickAxisY) * 180)) / M_PI);

					//If facing left than flip weapon sprite
					if (direction == directionEnum::left || direction == directionEnum::upLeft || direction == directionEnum::downLeft) {
						weapons[equippedWeaponIndex].rotation.flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;
					}
					else {
						weapons[equippedWeaponIndex].rotation.flip = SDL_RendererFlip::SDL_FLIP_NONE;
					}

				}
				sRect = convertAreaToSDLRect(weapons[equippedWeaponIndex].icon.spriteSheetArea);
				dRect = { weapons[equippedWeaponIndex].position.x, weapons[equippedWeaponIndex].position.y, weapons[equippedWeaponIndex].weaponSize.w, weapons[equippedWeaponIndex].weaponSize.h };
				if (SDLRectWithinCameraView(dRect) == true) {
					dRect.x -= camera.area.x;
					dRect.y -= camera.area.y;
					SDL_RenderCopyEx(renderer, spriteSheets[weapons[equippedWeaponIndex].icon.spriteSheetIndex].texture, &sRect, &dRect, weapons[equippedWeaponIndex].rotation.angle, &weapons[equippedWeaponIndex].rotation.centre, weapons[equippedWeaponIndex].rotation.flip);
				}
			}
		}
	}
}

void Character::updateSpriteIndex() {
	if (SDL_GetTicks() - spriteUpdate.startTicks >= spriteUpdate.delay) {
		spriteUpdate.startTicks = SDL_GetTicks();
		if (spriteIndex < (int)sprites[(int)direction].size() - 1) {
			++spriteIndex;
		}
		else {
			spriteIndex = 0;
		}
	}
}

collisionStruct Character::characterCheckCollision() {
	collisionStruct currentCollision;

	//Check if character is out of overworld grid bounds
	areaStruct characterGridArea = getGridAreaFromPixelArea({ position.x, position.y, spriteTargetSize.w, spriteTargetSize.h });
	if (areaWithinGrid(characterGridArea, layerIndex) == false) {
		changeOverworldRegionBool = true;
		currentCollision.collision = true;
		if (position.x < 0) {
			if (currentlyInsideBuilding == false) {
				currentCollision.regionCorner = collisionStruct::regionCornerEnum::left;
			}
			else {
				position.x = 0;
			}
		}
		else if (position.y < 0) {
			if (currentlyInsideBuilding == false) {
				currentCollision.regionCorner = collisionStruct::regionCornerEnum::up;
			}
			else {
				position.y = 0;
			}
		}
		else if (position.x + spriteTargetSize.w - 1 > ((int)overworldGrid.gridTile[layerIndex].size() - 1) * tileSize.w) {
			if (currentlyInsideBuilding == false) {
				currentCollision.regionCorner = collisionStruct::regionCornerEnum::right;
			}
			else {
				position.x = (((int)overworldGrid.gridTile[layerIndex].size() - 1) * tileSize.w) - spriteTargetSize.w + 1;
			}
		}
		else if (position.y + spriteTargetSize.h - 1 > ((int)overworldGrid.gridTile[layerIndex][0].size() - 1) * tileSize.h) {
			if (currentlyInsideBuilding == false) {
				currentCollision.regionCorner = collisionStruct::regionCornerEnum::down;
			}
			else {
				position.y = (((int)overworldGrid.gridTile[layerIndex][0].size() - 1) * tileSize.h) - spriteTargetSize.h + 1;
			}
		}
		return currentCollision;
	}

	//Check collision with grid elements
	/*areaStruct characterGridArea = {
		roundDiv(position.x, tileSize.w),
		roundDiv(position.y, tileSize.h),
		roundDiv(spriteTargetSize.w, tileSize.w),
		roundDiv(spriteTargetSize.h, tileSize.h)
	};*/
	for (int characterGridAreaXCnt = characterGridArea.x; characterGridAreaXCnt < characterGridArea.x + characterGridArea.w; ++characterGridAreaXCnt) {
		for (int characterGridAreaYCnt = characterGridArea.y; characterGridAreaYCnt < characterGridArea.y + characterGridArea.h; ++characterGridAreaYCnt) {
			if (overworldGrid.gridTile[layerIndex][characterGridAreaXCnt][characterGridAreaYCnt].collidable == true) {
				currentCollision.collision = true;
				return currentCollision;
			}
		}
	}

	currentCollision.collision = false;
	return currentCollision;
}

void Character::move() {
	if (path.walkPath == false && disableControls == false && ID == controlledCharacterIndex && SDL_GetTicks() - moveSpeed.startTicks >= moveSpeed.delay / FPSTimerMod && sleep.state == false) {
		moveSpeed.startTicks = SDL_GetTicks();

		//Character walks faster when joystick is tilted fully
		if (abs(joystickAxisX) > (joystickAxisMaxValue / 4) * 3 || abs(joystickAxisY) > (joystickAxisMaxValue / 4) * 3) {
			moveSpeed.pixelIncrement = 2 * FPSTimerMod;
		}
		else {
			moveSpeed.pixelIncrement = 1 * FPSTimerMod;
		}

		//Update direction based on right stick input
		bool directionUpdated = false;
		if (rightStickXDir == 1 && rightStickYDir == 0) {
			direction = directionEnum::down;
			directionUpdated = true;
		}
		else if (rightStickXDir == -1 && rightStickYDir == 0) {
			direction = directionEnum::up;
			directionUpdated = true;
		}
		else if (rightStickXDir == 0 && rightStickYDir == 1) {
			direction = directionEnum::right;
			directionUpdated = true;
		}
		else if (rightStickXDir == 0 && rightStickYDir == -1) {
			direction = directionEnum::left;
			directionUpdated = true;
		}

		//Diagonal directions (right stick)
		if (rightStickXDir == -1 && rightStickYDir == 1) {
			direction = directionEnum::upRight;
			directionUpdated = true;
		}
		else if (rightStickXDir == 1 && rightStickYDir == 1) {
			direction = directionEnum::downRight;
			directionUpdated = true;
		}
		else if (rightStickXDir == 1 && rightStickYDir == -1) {
			direction = directionEnum::downLeft;
			directionUpdated = true;
		}
		else if (rightStickXDir == -1 && rightStickYDir == -1) {
			direction = directionEnum::upLeft;
			directionUpdated = true;
		}

		bool directionPressedLeft = false, directionPressedRight = false, directionPressedUp = false, directionPressedDown = false;

		//Move character
		if (xDir == -1) { //Left
			if (directionUpdated == false) {
				direction = directionEnum::left;
				directionPressedLeft = true;
			}
			position.x -= moveSpeed.pixelIncrement;
			collisionData = characterCheckCollision();
			if (collisionData.collision == true) {
				position.x += moveSpeed.pixelIncrement;
			}
			else {
				updateSpriteIndex();
			}
		}
		else if (xDir == 1) { //Right
			if (directionUpdated == false) {
				direction = directionEnum::right;
				directionPressedRight = true;
			}
			position.x += moveSpeed.pixelIncrement;
			collisionData = characterCheckCollision();
			if (collisionData.collision == true) {
				position.x -= moveSpeed.pixelIncrement;
			}
			else {
				updateSpriteIndex();
			}
		}
		if (yDir == -1) { //Up
			if (directionUpdated == false) {
				direction = directionEnum::up;
				directionPressedUp = true;
			}
			position.y -= moveSpeed.pixelIncrement;
			collisionData = characterCheckCollision();
			if (collisionData.collision == true) {
				position.y += moveSpeed.pixelIncrement;
			}
			else {
				updateSpriteIndex();
			}
		}
		else if (yDir == 1) { //Down
			if (directionUpdated == false) {
				direction = directionEnum::down;
				directionPressedDown = true;
			}
			position.y += moveSpeed.pixelIncrement;
			collisionData = characterCheckCollision();
			if (collisionData.collision == true) {
				position.y -= moveSpeed.pixelIncrement;
			}
			else {
				updateSpriteIndex();
			}
		}

		//Diagonal directions (left stick)
		if (directionPressedUp == true && directionPressedRight == true) {
			direction = directionEnum::upRight;
		}
		else if (directionPressedDown == true && directionPressedRight == true) {
			direction = directionEnum::downRight;
		}
		else if (directionPressedDown == true && directionPressedLeft == true) {
			direction = directionEnum::downLeft;
		}
		else if (directionPressedUp == true && directionPressedLeft == true) {
			direction = directionEnum::upLeft;
		}

	}
}

void Character::activateMenu() {
	if (disableControls == false && quickslotSelectedItem == false) {
		if (controllerButtons.start == true) {
			controllerButtons.start = false;
			if (characterMenuOn == false) {
				characterMenuOn = true;
				displayMenuOn = true;
			}
			else {
				characterMenuOn = false;
				displayMenuOn = false;
				selectedMenuLayer = 0;
			}
		}
		if (controllerButtons.B == true && characterMenuOn == true) {
			controllerButtons.B = false;
			if (selectedMenuLayer > 0) {
				--selectedMenuLayer;
			}
			else {
				if (displayEquipMenu == false) {
					characterMenuOn = false;
					displayMenuOn = false;
					selectedMenuLayer = 0;
				}
				else {
					displayEquipMenu = false;
					blockCursorMovement = false;
				}
			}
		}
	}
}

void Character::displayCharacterMenu() {
	if (displayMenuOn == true) {

		//Init selected menu layer
		if (selectedMenuLayer == -1) {
			selectedMenuLayer = 0;
		}

		//Init headers
		vector<string> headers = { "STATS", "SKILLS", "STATUS EFFECTS", "ABILITIES", "CYBERWARES", "GEAR", "WEAPONS", "CONSUMABLE ITEMS", "MISC ITEMS", "BLUEPRINTS", "CRAFTING ITEMS" };
		vector<iconStruct> headerIcons = convertHeaderSringsToHeaderIcons(headers);
		vector<areaStruct> headerAreas = {
			{ 0, 0, 12, 12 },
			{ 0, 19, 12, 14 }
		};
		vector<int> headerMaxLayers = { 1, 1, 1, 2, 3, 1, 1, 2, 1 };
		int headerAreasAlternateCnt = 0;
		for (int headerIconsCnt = 0; headerIconsCnt < (int)headerIcons.size(); ++headerIconsCnt) {
			headerIcons[headerIconsCnt].spriteSheetIndex = getSpriteSheetIndex("header icons");
			headerIcons[headerIconsCnt].spriteSheetArea = headerAreas[headerAreasAlternateCnt];
			if (headerAreasAlternateCnt == 0) {
				headerAreasAlternateCnt = 1;
			}
			else {
				headerAreasAlternateCnt = 0;
			}
		}

		/*setSDLRenderTarget(NULL);
		setSDLLogicalSize(textLogicalSize);*/

		//Display headers
		string headerMenuName = "character menu - character header";
		XYStruct menuPosition = { tileSize.w, tileSize.h };
		WHStruct iconSize = { tileSize.w * 10, tileSize.h * 10 };
		displayHeaderMenu(headerMenuName, headerStyleEnum::text, menuPosition, headerIcons, 4, iconSize, defaultFont, defaultColour, selectedHeaderSprite, 0, false, 75);
		menuPosition.y += iconSize.h;

		//Init menu layer 0
		vector<iconStruct> icons;
		vector < vector < string>> iconTextBlock;
		string menuVarsName;
		int headerMenuVarsIndex = getHeaderMenuVarsIndex(headerMenuName);
		if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "STATS") {
			for (int statsCnt = 0; statsCnt < (int)stats.size(); ++statsCnt) {
				stats[statsCnt].icon.caption = "";
				icons.push_back(stats[statsCnt].icon);

				iconTextBlock.push_back({ stats[statsCnt].name, formatStr("Level {}/{}/{}", { str(stats[statsCnt].current), str(stats[statsCnt].modified), str(stats[statsCnt].max) }), stats[statsCnt].description });

				menuVarsName = "character menu - stats";
			}
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "SKILLS") {
			for (int skillsCnt = 0; skillsCnt < (int)skills.size(); ++skillsCnt) {
				icons.push_back(skills[skillsCnt].icon);

				iconTextBlock.push_back({ skills[skillsCnt].name, skills[skillsCnt].description, formatStr("Level {}/{}/{}", { str(skills[skillsCnt].current), str(skills[skillsCnt].modified), str(skills[skillsCnt].max) }), formatStr("Experience {}/{}", { strUnsignedInt(skills[skillsCnt].experience.min), strUnsignedInt(skills[skillsCnt].experience.max) }) });

				menuVarsName = "character menu - skills";
			}
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "STATUS EFFECTS") {
			for (int statusEffectsCnt = 0; statusEffectsCnt < (int)statusEffects.size(); ++statusEffectsCnt) {
				icons.push_back(statusEffects[statusEffectsCnt].icon);

				iconTextBlock.push_back({
					statusEffects[statusEffectsCnt].name,
					statusEffects[statusEffectsCnt].modTargetType,
					statusEffects[statusEffectsCnt].modTargetName,
					statusEffects[statusEffectsCnt].modType,
					str(statusEffects[statusEffectsCnt].modValue),
					strUint32(statusEffects[statusEffectsCnt].duration.delay)
					});

				menuVarsName = "character menu - status effects";
			}
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "ABILITIES") {
			for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
				icons.push_back(abilities[abilitiesCnt].icon);

				string sourceSelectedItemName = "";
				if (abilities[abilitiesCnt].source.name == "Cyberware") {
					sourceSelectedItemName = cyberwares[abilities[abilitiesCnt].source.index].name;
				}
				else if (abilities[abilitiesCnt].source.name == "Weapons") {
					sourceSelectedItemName = weapons[abilities[abilitiesCnt].source.index].name;
				}

				iconTextBlock.push_back({
					abilities[abilitiesCnt].name,
					abilities[abilitiesCnt].description,
					abilities[abilitiesCnt].targetType,
					str(abilities[abilitiesCnt].staminaConsumption),
					abilities[abilitiesCnt].source.name,
					sourceSelectedItemName
					});

				menuVarsName = "character menu - abilities";
			}
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "CYBERWARES") {
			for (int cyberwaresCnt = 0; cyberwaresCnt < (int)cyberwares.size(); ++cyberwaresCnt) {
				cyberwares[cyberwaresCnt].icon.caption = "x " + str(cyberwares[cyberwaresCnt].quantity);
				icons.push_back(cyberwares[cyberwaresCnt].icon);

				iconTextBlock.push_back({
					cyberwares[cyberwaresCnt].name,
					cyberwares[cyberwaresCnt].description,
					str(cyberwares[cyberwaresCnt].energyConsumptionPerSecond)
					});

				menuVarsName = "character menu - cyberwares";
			}
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "GEAR") {
			for (int gearsCnt = 0; gearsCnt < (int)gears.size(); ++gearsCnt) {
				gears[gearsCnt].icon.caption = "x " + str(gears[gearsCnt].quantity);
				icons.push_back(gears[gearsCnt].icon);

				iconTextBlock.push_back({
					gears[gearsCnt].name,
					gears[gearsCnt].description
					});

				menuVarsName = "character menu - gear";
			}
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "WEAPONS") {
			for (int weaponsCnt = 0; weaponsCnt < (int)weapons.size(); ++weaponsCnt) {
				weapons[weaponsCnt].icon.caption = "x " + str(weapons[weaponsCnt].quantity);
				icons.push_back(weapons[weaponsCnt].icon);

				iconTextBlock.push_back({
					weapons[weaponsCnt].name,
					weapons[weaponsCnt].description,
					weapons[weaponsCnt].rangeType
					});

				menuVarsName = "character menu - weapons";
			}
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "CONSUMABLE ITEMS") {
			for (int consumableItemsCnt = 0; consumableItemsCnt < (int)consumableItems.size(); ++consumableItemsCnt) {
				consumableItems[consumableItemsCnt].icon.caption = "x " + str(consumableItems[consumableItemsCnt].quantity);
				icons.push_back(consumableItems[consumableItemsCnt].icon);

				vector<string> textBlock = { consumableItems[consumableItemsCnt].name, consumableItems[consumableItemsCnt].description };
				iconTextBlock.push_back(textBlock);

				menuVarsName = "character menu - consumable items";
			}
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "MISC ITEMS") {
			for (int cnt = 0; cnt < (int)miscItems.size(); ++cnt) {
				miscItems[cnt].icon.caption = "x " + str(miscItems[cnt].quantity);
				icons.push_back(miscItems[cnt].icon);

				iconTextBlock.push_back({
					miscItems[cnt].name,
					miscItems[cnt].description
					});

				menuVarsName = "character menu - misc items";
			}
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "BLUEPRINTS") {
			for (int cnt = 0; cnt < (int)blueprints.size(); ++cnt) {
				blueprints[cnt].blueprint.icon.caption = "x " + str(blueprints[cnt].blueprint.quantity);
				icons.push_back(blueprints[cnt].blueprint.icon);

				iconTextBlock.push_back({
					blueprints[cnt].blueprint.name,
					blueprints[cnt].blueprint.description
					});

				menuVarsName = "character menu - blueprints";
			}
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "CRAFTING ITEMS") {
			for (int cnt = 0; cnt < (int)craftingItems.size(); ++cnt) {
				craftingItems[cnt].icon.caption = "x " + str(craftingItems[cnt].quantity);
				icons.push_back(craftingItems[cnt].icon);

				iconTextBlock.push_back({
					craftingItems[cnt].name,
					craftingItems[cnt].description
					});

				menuVarsName = "character menu - crafting items";
			}
		}

		//Display menu layer 0
		displayMenu(menuVarsName, menuVarsStruct::styleEnum::randomized, menuPosition, "", true, icons, iconTextBlock, { 10, 5 }, { tileSize.w * 10, tileSize.h * 10 }, 10, defaultFont, defaultColour, selectedIconSprite, 0, blockCursorMovement, 0, true, true, true, {  });

		//Init menu layer 1
		vector<iconStruct> menuLayer1Icons;
		vector < vector < string>> menuLayer1IconTextBlock;
		string menuLayer1MenuVarsName, menuTitle;
		int selectedMenuItem;
		if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "ABILITIES") {
			selectedMenuItem = menuVars[getMenuVarsIndex(menuVarsName)].scrollCursor;
			for (int abilityEffectsCnt = 0; abilityEffectsCnt < (int)abilities[selectedMenuItem].statusEffects.size(); ++abilityEffectsCnt) {

				menuLayer1Icons.push_back(abilities[selectedMenuItem].statusEffects[abilityEffectsCnt].icon);

				menuLayer1IconTextBlock.push_back({
					abilities[selectedMenuItem].statusEffects[abilityEffectsCnt].name,
					abilities[selectedMenuItem].statusEffects[abilityEffectsCnt].modTargetType,
					abilities[selectedMenuItem].statusEffects[abilityEffectsCnt].modTargetName,
					abilities[selectedMenuItem].statusEffects[abilityEffectsCnt].modType,
					str(abilities[selectedMenuItem].statusEffects[abilityEffectsCnt].modValue),
					strUint32(abilities[selectedMenuItem].statusEffects[abilityEffectsCnt].duration.delay)
					});
			}
			menuLayer1MenuVarsName = "character menu - abilities - status effects";
			menuTitle = "STATUS EFFECTS";
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "CYBERWARES") {
			selectedMenuItem = menuVars[getMenuVarsIndex(menuVarsName)].scrollCursor;
			for (int cyberwareAbilitiesCnt = 0; cyberwareAbilitiesCnt < (int)cyberwares[selectedMenuItem].abilities.size(); ++cyberwareAbilitiesCnt) {

				menuLayer1Icons.push_back(cyberwares[selectedMenuItem].abilities[cyberwareAbilitiesCnt].icon);

				menuLayer1IconTextBlock.push_back({
					cyberwares[selectedMenuItem].abilities[cyberwareAbilitiesCnt].name,
					cyberwares[selectedMenuItem].abilities[cyberwareAbilitiesCnt].description,
					cyberwares[selectedMenuItem].abilities[cyberwareAbilitiesCnt].targetType,
					str(cyberwares[selectedMenuItem].abilities[cyberwareAbilitiesCnt].staminaConsumption)
					});
			}
			menuLayer1MenuVarsName = "character menu - cyberwares - abilities";
			menuTitle = "ABILITIES";
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "GEAR") {
			selectedMenuItem = menuVars[getMenuVarsIndex(menuVarsName)].scrollCursor;
			for (int gearSkillsCnt = 0; gearSkillsCnt < (int)gears[selectedMenuItem].skills.size(); ++gearSkillsCnt) {

				menuLayer1Icons.push_back(gears[selectedMenuItem].skills[gearSkillsCnt].icon);

				menuLayer1IconTextBlock.push_back({
					gears[selectedMenuItem].skills[gearSkillsCnt].name,
					str(gears[selectedMenuItem].skills[gearSkillsCnt].modValue)
					});
			}
			menuLayer1MenuVarsName = "character menu - gear - skills";
			menuTitle = "SKILLS";
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "WEAPONS") {
			selectedMenuItem = menuVars[getMenuVarsIndex(menuVarsName)].scrollCursor;
			for (int cnt = 0; cnt < (int)weapons[selectedMenuItem].abilities.size(); ++cnt) {

				menuLayer1Icons.push_back(weapons[selectedMenuItem].abilities[cnt].icon);

				menuLayer1IconTextBlock.push_back({
					weapons[selectedMenuItem].abilities[cnt].name,
					weapons[selectedMenuItem].abilities[cnt].description,
					weapons[selectedMenuItem].abilities[cnt].targetType,
					str(weapons[selectedMenuItem].abilities[cnt].staminaConsumption)
					});
			}
			menuLayer1MenuVarsName = "character menu - weapons - abilities";
			menuTitle = "ABILITIES";
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "CONSUMABLE ITEMS") {
			selectedMenuItem = menuVars[getMenuVarsIndex(menuVarsName)].scrollCursor;
			for (int consumableItemStatusEffectsCnt = 0; consumableItemStatusEffectsCnt < (int)consumableItems[selectedMenuItem].statusEffects.size(); ++consumableItemStatusEffectsCnt) {

				menuLayer1Icons.push_back(consumableItems[selectedMenuItem].statusEffects[consumableItemStatusEffectsCnt].icon);

				menuLayer1IconTextBlock.push_back({
					consumableItems[selectedMenuItem].statusEffects[consumableItemStatusEffectsCnt].name,
					consumableItems[selectedMenuItem].statusEffects[consumableItemStatusEffectsCnt].modTargetType,
					consumableItems[selectedMenuItem].statusEffects[consumableItemStatusEffectsCnt].modTargetName,
					consumableItems[selectedMenuItem].statusEffects[consumableItemStatusEffectsCnt].modType,
					str(consumableItems[selectedMenuItem].statusEffects[consumableItemStatusEffectsCnt].modValue),
					strUint32(consumableItems[selectedMenuItem].statusEffects[consumableItemStatusEffectsCnt].duration.delay)
					});
			}
			menuLayer1MenuVarsName = "character menu - consumable items - status effects";
			menuTitle = "STATUS EFFECTS";
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "BLUEPRINTS") {

			//Get blueprint misc items required
			selectedMenuItem = menuVars[getMenuVarsIndex(menuVarsName)].scrollCursor;
			for (int requiredMiscItemsCnt = 0; requiredMiscItemsCnt < (int)blueprints[selectedMenuItem].requiredMiscItems.size(); ++requiredMiscItemsCnt) {
				menuLayer1Icons.push_back(blueprints[selectedMenuItem].requiredMiscItems[requiredMiscItemsCnt].icon);

				menuLayer1IconTextBlock.push_back({
					blueprints[selectedMenuItem].requiredMiscItems[requiredMiscItemsCnt].name,
					str(blueprints[selectedMenuItem].requiredMiscItems[requiredMiscItemsCnt].quantity)
					});

				menuLayer1MenuVarsName = "character menu - blueprints";
				menuTitle = "BLUEPRINTS";
			}

		}

		//Add selected index to menuLayer1MenuVarsName
		if (getOccurencesInString("-", menuLayer1MenuVarsName) == 2) {
			menuLayer1MenuVarsName.insert(menuLayer1MenuVarsName.rfind(" - "), " " + str(selectedMenuItem));
		}

		//Update selected menu layer
		if (disableControls == false && controllerButtons.A == true && displayEquipMenu == false && quickslotSelectedItem == false) {
			controllerButtons.A = false;
			if (selectedMenuLayer < headerMaxLayers[headerMenuVars[getHeaderMenuVarsIndex(headerMenuName)].selected]) {
				++selectedMenuLayer;
			}
		}

		//Display menu layer 1
		displayMenu(menuLayer1MenuVarsName, menuVarsStruct::styleEnum::randomized, { textLogicalSize.w / 2, tileSize.h }, menuTitle, true, menuLayer1Icons, menuLayer1IconTextBlock, { 5, 5 }, { tileSize.w * 7, tileSize.h * 7 }, 10, defaultFont, defaultColour, selectedIconSprite, 1, blockCursorMovement, 0, true, true, true, {  });

		//Init menu layer 2
		vector<iconStruct> menuLayer2Icons;
		vector < vector < string>> menuLayer2IconTextBlock;
		string menuLayer2MenuVarsName;
		int menuLayer2SelectedMenuItem;
		if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "CYBERWARES") {
			selectedMenuItem = menuVars[getMenuVarsIndex(menuVarsName)].scrollCursor;
			menuLayer2SelectedMenuItem = menuVars[getMenuVarsIndex(menuLayer1MenuVarsName)].scrollCursor;
			for (int cyberwareAbilityStatusEffectsCnt = 0; cyberwareAbilityStatusEffectsCnt < (int)cyberwares[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects.size(); ++cyberwareAbilityStatusEffectsCnt) {

				menuLayer2Icons.push_back(cyberwares[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cyberwareAbilityStatusEffectsCnt].icon);

				menuLayer2IconTextBlock.push_back({
					cyberwares[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cyberwareAbilityStatusEffectsCnt].name,
					cyberwares[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cyberwareAbilityStatusEffectsCnt].modTargetType,
					cyberwares[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cyberwareAbilityStatusEffectsCnt].modTargetName,
					cyberwares[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cyberwareAbilityStatusEffectsCnt].modType,
					str(cyberwares[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cyberwareAbilityStatusEffectsCnt].modValue),
					strUint32(cyberwares[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cyberwareAbilityStatusEffectsCnt].duration.delay)
					});
			}
			menuLayer2MenuVarsName = menuLayer1MenuVarsName + " - status effects";
			menuTitle = "STATUS EFFECTS";
		}
		else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "WEAPONS") {
			selectedMenuItem = menuVars[getMenuVarsIndex(menuVarsName)].scrollCursor;
			menuLayer2SelectedMenuItem = menuVars[getMenuVarsIndex(menuLayer1MenuVarsName)].scrollCursor;
			for (int cnt = 0; cnt < (int)weapons[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects.size(); ++cnt) {

				menuLayer2Icons.push_back(weapons[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cnt].icon);

				menuLayer2IconTextBlock.push_back({
					weapons[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cnt].name,
					weapons[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cnt].modTargetType,
					weapons[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cnt].modTargetName,
					weapons[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cnt].modType,
					str(weapons[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cnt].modValue),
					strUint32(weapons[selectedMenuItem].abilities[menuLayer2SelectedMenuItem].statusEffects[cnt].duration.delay)
					});
			}
			menuLayer2MenuVarsName = menuLayer1MenuVarsName + " - status effects";
			menuTitle = "STATUS EFFECTS";
		}

		//Add selected index to menuLayer1MenuVarsName
		if (getOccurencesInString("-", menuLayer2MenuVarsName) == 3) {
			menuLayer2MenuVarsName.insert(menuLayer2MenuVarsName.rfind(" - "), " " + str(menuLayer2SelectedMenuItem));
		}

		//Display menu layer 2
		displayMenu(menuLayer2MenuVarsName, menuVarsStruct::styleEnum::randomized, { textLogicalSize.w / 2, textLogicalSize.h / 2 }, menuTitle, true, menuLayer2Icons, menuLayer2IconTextBlock, { 5, 5 }, { tileSize.w * 7, tileSize.h * 7 }, 10, defaultFont, defaultColour, selectedIconSprite, 2, blockCursorMovement, 0, true, true, true, {  });

		//Display button prompts
		icons = {
			{ getSpriteSheetIndex("controller buttons"), { 89, 191, 61, 65 }, "" },
			{ getSpriteSheetIndex("controller buttons"), { 254, 190, 59, 65 }, "" },
			{ getSpriteSheetIndex("controller buttons"), { 336, 191, 58, 62 }, "" },
			{ getSpriteSheetIndex("controller buttons"), { 499, 189, 55, 64 }, "" },
			{ getSpriteSheetIndex("controller buttons"), { 171, 192, 61, 62 }, "" }
		};
		WHStruct textSize = getTextSize("Z", defaultFont);
		displayTextBlock(textBlockDisplayStyleEnum::horizontal, textBlockAlignmentEnum::left, icons, { "Select", "Use/Equip", "Quickslot", "Menu Style", "Exit Menu" }, { tileSize.w, textLogicalSize.h - ((textSize.h * ((int)icons.size() + 1)) * 2) }, defaultFont, defaultColour, false, 0);

		//Activate quickslots
		vector<string> quickslottableTypes = { "ABILITIES", "CONSUMABLE ITEMS" };
		bool canQuickslot = false;
		for (int quickslottableTypesCnt = 0; quickslottableTypesCnt < (int)quickslottableTypes.size(); ++quickslottableTypesCnt) {
			if (quickslottableTypes[quickslottableTypesCnt] == headers[headerMenuVars[headerMenuVarsIndex].selected]) {
				canQuickslot = true;
				break;
			}
		}
		if (disableControls == false) {
			if (controlledCharacterIndex == ID && canQuickslot == true && quickslotSelectedItem == false && controllerButtons.Y == true) {
				controllerButtons.Y = false;
				quickslotSelectedItem = true;
				blockCursorMovement = true;
			}
			if (controlledCharacterIndex == ID && quickslotSelectedItem == true && controllerButtons.start == true) {
				controllerButtons.start = false;
				quickslotSelectedItem = false;
				blockCursorMovement = false;
			}
		}

		//Quickslot selected item
		string NthButtonPressedName = getNthButtonPressedName(1);
		int quickslotIndex = getQuickslotIndex(NthButtonPressedName);
		if (controlledCharacterIndex == ID && quickslotSelectedItem == true && getStringIndex({ "ABILITIES", "CONSUMABLE ITEMS" }, headers[headerMenuVars[headerMenuVarsIndex].selected]) > -1) {
			if (quickslotIndex > -1 && NthButtonPressedName != "" || controllerButtons.select == true) {
				if (quickslotIndex > -1) {

					int abilitiesMenuVarsIndex = getMenuVarsIndex("character menu - abilities");
					int consumableItemsMenuVarsIndex = getMenuVarsIndex("character menu - consumable items");

					//If item is slotted in another slot then unslot it
					for (int quickslotsCnt = 0; quickslotsCnt < (int)quickslots.size(); ++quickslotsCnt) {
						if (quickslots[quickslotsCnt].slottedItemIndex > -1 && quickslots[quickslotsCnt].slottedItemType != "" && quickslots[quickslotsCnt].slottedItemType == headers[headerMenuVars[headerMenuVarsIndex].selected]) {
							if ((headers[headerMenuVars[headerMenuVarsIndex].selected] == "ABILITIES" && quickslots[quickslotsCnt].slottedItemIndex == menuVars[abilitiesMenuVarsIndex].scrollCursor) || (headers[headerMenuVars[headerMenuVarsIndex].selected] == "CONSUMABLE ITEMS" && quickslots[quickslotsCnt].slottedItemIndex == menuVars[consumableItemsMenuVarsIndex].scrollCursor)) {
								quickslots[quickslotsCnt].slottedItemIndex = -1;
								quickslots[quickslotsCnt].slottedItemType = "";
								quickslots[quickslotsCnt].icon = {  };
								break;
							}
						}
					}

					//Quickslot item
					quickslots[quickslotIndex].slottedItemType = headers[headerMenuVars[headerMenuVarsIndex].selected];
					if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "ABILITIES") {
						quickslots[quickslotIndex].slottedItemIndex = abilities[menuVars[abilitiesMenuVarsIndex].scrollCursor].index;
						quickslots[quickslotIndex].icon = abilities[quickslots[quickslotIndex].slottedItemIndex].icon;
					}
					else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "CONSUMABLE ITEMS") {
						quickslots[quickslotIndex].slottedItemIndex = consumableItems[menuVars[consumableItemsMenuVarsIndex].scrollCursor].index;
						quickslots[quickslotIndex].icon = consumableItems[quickslots[quickslotIndex].slottedItemIndex].icon;
					}

					//Set all button presses used for quickslots to false
					hatButtons.up = false;
					hatButtons.down = false;
					hatButtons.left = false;
					hatButtons.right = false;
					controllerButtons.A = false;
					controllerButtons.B = false;
					controllerButtons.X = false;
					controllerButtons.Y = false;
					controllerButtons.LB = false;
					controllerButtons.RB = false;
					leftTrigger.activated = false;
					rightTrigger.activated = false;

					//Deactivate events
					deactivateEvent.startTicks = SDL_GetTicks();
					deactivateEvent.delay = 250;

					quickslotSelectedItem = false;
				}

				//Empty all slots
				if (controllerButtons.select == true && SDL_GetTicks() - controllerButtonStartTicks.select >= (Uint32)(1000 / FPSTimerMod)) {
					controllerButtons.select = false;
					for (int quickslotsCnt = 0; quickslotsCnt < (int)quickslots.size(); ++quickslotsCnt) {
						quickslots[quickslotsCnt].icon = {  };
						quickslots[quickslotsCnt].slottedItemIndex = -1;
						quickslots[quickslotsCnt].slottedItemType = "";
						controllerButtonStartTicks.select = 0;
					}
				}

			}
		}

		//Activate equip menu
		if (disableControls == false && controllerButtons.X == true && displayEquipMenu == false) {
			controllerButtons.X = false;
			displayEquipMenu = true;
			blockCursorMovement = true;
		}

		//Equip cyberware, gear, weapon menu
		if (displayEquipMenu == true) {

			//Exit equip menu
			if (disableControls == false && controllerButtons.B == true) {
				controllerButtons.B = false;
				displayEquipMenu = false;
				blockCursorMovement = false;
			}

			//Init menu vars
			vector<iconStruct> icons;
			vector< vector <string>> iconsTextBlock;
			string menuVarsName;
			if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "CYBERWARES") {
				for (int slotsCnt = 0; slotsCnt < (int)cyberwareEquipmentSlots.size(); ++slotsCnt) {
					vector<int> list;
					for (int cyberwaresCnt = 0; cyberwaresCnt < (int)cyberwares.size(); ++cyberwaresCnt) {
						list.push_back(cyberwares[cyberwaresCnt].index);
					}
					int slotEquipmentIndex = getIntIndex(list, cyberwareEquipmentSlots[slotsCnt].equipmentIndex);
					if (slotEquipmentIndex > -1) {
						cyberwares[slotEquipmentIndex].icon.caption = "x " + str(cyberwares[slotEquipmentIndex].quantity);
						icons.push_back(cyberwares[slotEquipmentIndex].icon);
						iconsTextBlock.push_back({ cyberwares[slotEquipmentIndex].name, cyberwares[slotEquipmentIndex].description, str(cyberwares[slotEquipmentIndex].energyConsumptionPerSecond) });
					}
					else {

						//Insert blank icon
						icons.push_back(blankIcon);
						iconsTextBlock.push_back({ "Empty" });

					}
				}
				menuVarsName = "character menu - equip - cyberwares";
			}
			else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "GEAR") {
				for (int slotsCnt = 0; slotsCnt < (int)gearEquipmentSlots.size(); ++slotsCnt) {
					vector<int> list;
					for (int gearsCnt = 0; gearsCnt < (int)gears.size(); ++gearsCnt) {
						list.push_back(gears[gearsCnt].index);
					}
					int slotEquipmentIndex = getIntIndex(list, gearEquipmentSlots[slotsCnt].equipmentIndex);
					if (slotEquipmentIndex > -1) {
						gears[slotEquipmentIndex].icon.caption = "x " + str(gears[slotEquipmentIndex].quantity);
						icons.push_back(gears[slotEquipmentIndex].icon);
						iconsTextBlock.push_back({ gears[slotEquipmentIndex].name, gears[slotEquipmentIndex].description });
					}
					else {

						//Insert blank icon
						icons.push_back(blankIcon);
						iconsTextBlock.push_back({ "Empty" });

					}
				}
				menuVarsName = "character menu - equip - gear";
			}
			else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "WEAPONS") {
				for (int slotsCnt = 0; slotsCnt < (int)weaponEquipmentSlots.size(); ++slotsCnt) {
					vector<int> list;
					for (int weaponsCnt = 0; weaponsCnt < (int)weapons.size(); ++weaponsCnt) {
						list.push_back(weapons[weaponsCnt].index);
					}
					int slotEquipmentIndex = getIntIndex(list, weaponEquipmentSlots[slotsCnt].equipmentIndex);
					if (slotEquipmentIndex > -1) {
						weapons[slotEquipmentIndex].icon.caption = "x " + str(weapons[slotEquipmentIndex].quantity);
						icons.push_back(weapons[slotEquipmentIndex].icon);
						iconsTextBlock.push_back({ weapons[slotEquipmentIndex].name, weapons[slotEquipmentIndex].description });
					}
					else {

						//Insert blank icon
						icons.push_back(blankIcon);
						iconsTextBlock.push_back({ "Empty" });

					}
				}
				menuVarsName = "character menu - equip - weapons";
			}

			//Display equip menu
			displayMenu(menuVarsName, menuVarsStruct::styleEnum::randomized, { 10, 10 }, "EQUIP " + headers[headerMenuVars[headerMenuVarsIndex].selected], true, icons, iconsTextBlock, { 10, 5 }, { tileSize.w * 7, tileSize.h * 7 }, 10, defaultFont, defaultColour, selectedIconSprite, 0, false, 75, true, true, true, {  });

			//Equip selected cyberware/gear/weapon
			if (disableControls == false && displayEquipMenu == true && controllerButtons.A == true) {
				controllerButtons.A = false;

				//If selected cyberware/gear already equipped in a different slot then remove it before equipping in selected slot
				int selectedSlotIndex = menuVars[getMenuVarsIndex(menuVarsName)].scrollCursor;
				if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "CYBERWARES") {
					int menuVarsIndex = getMenuVarsIndex("character menu - cyberwares");
					for (int cyberwareEquipmentSlotsCnt = 0; cyberwareEquipmentSlotsCnt < (int)cyberwareEquipmentSlots.size(); ++cyberwareEquipmentSlotsCnt) {
						vector<int> list;
						for (int cyberwaresCnt = 0; cyberwaresCnt < (int)cyberwares.size(); ++cyberwaresCnt) {
							list.push_back(cyberwares[cyberwaresCnt].index);
						}
						int equipmentIndex = getIntIndex(list, cyberwareEquipmentSlots[cyberwareEquipmentSlotsCnt].equipmentIndex);
						if (equipmentIndex == menuVars[menuVarsIndex].scrollCursor) {

							//Check if abilities are quickslotted and remove them if so
							for (int quickslotsCnt = 0; quickslotsCnt < (int)quickslots.size(); ++quickslotsCnt) {
								for (int selectedEquipmentSlotAbilitiesCnt = 0; selectedEquipmentSlotAbilitiesCnt < (int)cyberwares[equipmentIndex].abilities.size(); ++selectedEquipmentSlotAbilitiesCnt) {
									if (tolower(*quickslots[quickslotsCnt].slottedItemType.c_str()) == tolower(*cyberwares[equipmentIndex].abilities[selectedEquipmentSlotAbilitiesCnt].source.name.c_str()) && quickslots[quickslotsCnt].slottedItemIndex == cyberwares[equipmentIndex].abilities[selectedEquipmentSlotAbilitiesCnt].source.index) {

										//Remove ability from quickslot
										quickslots[quickslotsCnt].icon = {  };
										quickslots[quickslotsCnt].slottedItemIndex = -1;
										quickslots[quickslotsCnt].slottedItemType = "";

									}
								}
							}

							//Check if current equipment slot item abilities already in abilities
							for (int currentEquipmentSlotItemAbilitiesCnt = 0; currentEquipmentSlotItemAbilitiesCnt < (int)cyberwares[equipmentIndex].abilities.size(); ++currentEquipmentSlotItemAbilitiesCnt) {
								for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
									if (tolower(*abilities[abilitiesCnt].source.name.c_str()) == tolower(*cyberwares[equipmentIndex].abilities[currentEquipmentSlotItemAbilitiesCnt].source.name.c_str()) && abilities[abilitiesCnt].source.index == cyberwareEquipmentSlots[cyberwareEquipmentSlotsCnt].equipmentIndex) {

										//Remove ability
										abilities.erase(abilities.begin() + abilitiesCnt);

										break;
									}
								}
							}

							//Unequip item
							cyberwareEquipmentSlots[cyberwareEquipmentSlotsCnt].equipmentIndex = -1;

							break;
						}
					}

					//Check if ability already added (see if any ability source and index match with any of those on the selected cyberware)
					for (int cyberwareAbilitiesCnt = 0; cyberwareAbilitiesCnt < (int)cyberwares[menuVars[menuVarsIndex].scrollCursor].abilities.size(); ++cyberwareAbilitiesCnt) {
						bool cyberwareAbilityAlreadyAdded = false;
						for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
							if (abilities[abilitiesCnt].source.name == cyberwares[menuVars[menuVarsIndex].scrollCursor].abilities[cyberwareAbilitiesCnt].source.name && abilities[abilitiesCnt].source.index == menuVars[menuVarsIndex].scrollCursor) {
								cyberwareAbilityAlreadyAdded = true;
								break;
							}
						}
						if (cyberwareAbilityAlreadyAdded == false) {

							//Update cyberware ability index
							vector<int> indices;
							for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
								indices.push_back(abilities[abilitiesCnt].index);
							}
							cyberwares[menuVars[menuVarsIndex].scrollCursor].abilities[cyberwareAbilitiesCnt].index = getFreeID(indices);

							//Add ability to abilities
							characterConstructorVarsStruct::abilityStruct currentAbility = cyberwares[menuVars[menuVarsIndex].scrollCursor].abilities[cyberwareAbilitiesCnt];
							indices.clear();
							for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
								indices.push_back(abilities[abilitiesCnt].index);
							}
							currentAbility.index = getFreeID(indices);
							abilities.push_back(currentAbility);

						}
					}

					//Equip item
					cyberwareEquipmentSlots[selectedSlotIndex].equipmentIndex = cyberwares[menuVars[menuVarsIndex].scrollCursor].index;

				}
				else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "GEAR") {
					int menuVarsIndex = getMenuVarsIndex("character menu - gear");
					for (int gearEquipmentSlotsCnt = 0; gearEquipmentSlotsCnt < (int)gearEquipmentSlots.size(); ++gearEquipmentSlotsCnt) {
						vector<int> list;
						for (int gearsCnt = 0; gearsCnt < (int)gears.size(); ++gearsCnt) {
							list.push_back(cyberwares[gearsCnt].index);
						}
						int equipmentIndex = getIntIndex(list, gearEquipmentSlots[gearEquipmentSlotsCnt].equipmentIndex);
						if (equipmentIndex == menuVars[menuVarsIndex].scrollCursor) {

							//Remove mods from skills (update skills modified value where skills match skills on gear in slot)
							for (int gearSkillsCnt = 0; gearSkillsCnt < (int)gears[equipmentIndex].skills.size(); ++gearSkillsCnt) {
								for (int skillsCnt = 0; skillsCnt < (int)skills.size(); ++skillsCnt) {
									if (skills[skillsCnt].name == gears[equipmentIndex].skills[gearSkillsCnt].name) {
										skills[skillsCnt].modified -= gears[equipmentIndex].skills[gearSkillsCnt].modValue;
									}
								}
							}

							//Remove gear from slot
							gearEquipmentSlots[gearEquipmentSlotsCnt].equipmentIndex = -1;

							break;
						}
					}

					//Add mods to skills
					int selectedGear = menuVars[menuVarsIndex].scrollCursor;
					for (int gearSkillsCnt = 0; gearSkillsCnt < (int)gears[selectedGear].skills.size(); ++gearSkillsCnt) {

						//Check if skill already added
						for (int skillsCnt = 0; skillsCnt < (int)skills.size(); ++skillsCnt) {
							if (skills[skillsCnt].name == gears[selectedGear].skills[gearSkillsCnt].name) {

								//Update skill modified value
								skills[skillsCnt].modified += gears[selectedGear].skills[gearSkillsCnt].modValue;

								break;
							}
						}

					}

					//Equip item
					gearEquipmentSlots[selectedSlotIndex].equipmentIndex = gears[menuVars[menuVarsIndex].scrollCursor].index;

				}
				else if (headers[headerMenuVars[headerMenuVarsIndex].selected] == "WEAPONS") {
					int menuVarsIndex = getMenuVarsIndex("character menu - weapons");
					for (int weaponEquipmentSlotsCnt = 0; weaponEquipmentSlotsCnt < (int)weaponEquipmentSlots.size(); ++weaponEquipmentSlotsCnt) {
						vector<int> list;
						for (int weaponsCnt = 0; weaponsCnt < (int)weapons.size(); ++weaponsCnt) {
							list.push_back(weapons[weaponsCnt].index);
						}
						int equipmentIndex = getIntIndex(list, weaponEquipmentSlots[weaponEquipmentSlotsCnt].equipmentIndex);
						if (equipmentIndex == menuVars[menuVarsIndex].scrollCursor) {

							//Check if abilities are quickslotted and remove them if so
							for (int quickslotsCnt = 0; quickslotsCnt < (int)quickslots.size(); ++quickslotsCnt) {
								for (int selectedEquipmentSlotAbilitiesCnt = 0; selectedEquipmentSlotAbilitiesCnt < (int)weapons[equipmentIndex].abilities.size(); ++selectedEquipmentSlotAbilitiesCnt) {
									if (tolower(*quickslots[quickslotsCnt].slottedItemType.c_str()) == tolower(*weapons[equipmentIndex].abilities[selectedEquipmentSlotAbilitiesCnt].source.name.c_str()) && quickslots[quickslotsCnt].slottedItemIndex == weapons[equipmentIndex].abilities[selectedEquipmentSlotAbilitiesCnt].source.index) {

										//Remove ability from quickslot
										quickslots[quickslotsCnt].icon = {  };
										quickslots[quickslotsCnt].slottedItemIndex = -1;
										quickslots[quickslotsCnt].slottedItemType = "";

									}
								}
							}

							//Check if current equipment slot item abilities already in abilities
							for (int currentEquipmentSlotItemAbilitiesCnt = 0; currentEquipmentSlotItemAbilitiesCnt < (int)weapons[equipmentIndex].abilities.size(); ++currentEquipmentSlotItemAbilitiesCnt) {
								for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
									if (tolower(*abilities[abilitiesCnt].source.name.c_str()) == tolower(*weapons[equipmentIndex].abilities[currentEquipmentSlotItemAbilitiesCnt].source.name.c_str()) && abilities[abilitiesCnt].source.index == weaponEquipmentSlots[weaponEquipmentSlotsCnt].equipmentIndex) {

										//Remove ability
										abilities.erase(abilities.begin() + abilitiesCnt);

										break;
									}
								}
							}

							//Unequip item
							weaponEquipmentSlots[weaponEquipmentSlotsCnt].equipmentIndex = -1;

							break;
						}
					}

					//Check if ability already added (see if any ability source and index match with any of those on the selected cyberware)
					for (int weaponAbilitiesCnt = 0; weaponAbilitiesCnt < (int)weapons[menuVars[menuVarsIndex].scrollCursor].abilities.size(); ++weaponAbilitiesCnt) {
						bool weaponAbilityAlreadyAdded = false;
						for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
							if (abilities[abilitiesCnt].source.name == weapons[menuVars[menuVarsIndex].scrollCursor].abilities[weaponAbilitiesCnt].source.name && abilities[abilitiesCnt].source.index == menuVars[menuVarsIndex].scrollCursor) {
								weaponAbilityAlreadyAdded = true;
								break;
							}
						}
						if (weaponAbilityAlreadyAdded == false) {

							//Update weapon ability index
							vector<int> indices;
							for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
								indices.push_back(abilities[abilitiesCnt].index);
							}
							weapons[menuVars[menuVarsIndex].scrollCursor].abilities[weaponAbilitiesCnt].index = getFreeID(indices);

							//Add ability to abilities
							characterConstructorVarsStruct::abilityStruct currentAbility = weapons[menuVars[menuVarsIndex].scrollCursor].abilities[weaponAbilitiesCnt];
							vector<int> indiices;
							for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
								indices.push_back(abilities[abilitiesCnt].index);
							}
							currentAbility.index = getFreeID(indices);
							abilities.push_back(currentAbility);

						}
					}

					//Equip item
					weaponEquipmentSlots[selectedSlotIndex].equipmentIndex = weapons[menuVars[menuVarsIndex].scrollCursor].index;

				}

			}

		}

	}
}

int Character::getQuickslotIndex(string controllerButtonName) {
	for (int quickslotsCnt = 0; quickslotsCnt < (int)quickslots.size(); ++quickslotsCnt) {
		if (quickslots[quickslotsCnt].controllerButtonName == controllerButtonName) {
			return quickslotsCnt;
		}
	}
	return -1;
}

vector<int> Character::getQuickslotButtonsPressedIndices() {
	vector<int> quickslotButtonsPressedIndices;
	if (controllerButtons.B == true) {
		quickslotButtonsPressedIndices.push_back(getQuickslotIndex("B"));
	}
	if (controllerButtons.X == true) {
		quickslotButtonsPressedIndices.push_back(getQuickslotIndex("X"));
	}
	if (controllerButtons.Y == true) {
		quickslotButtonsPressedIndices.push_back(getQuickslotIndex("Y"));
	}
	if (controllerButtons.LB == true) {
		quickslotButtonsPressedIndices.push_back(getQuickslotIndex("LB"));
	}
	if (controllerButtons.RB == true) {
		quickslotButtonsPressedIndices.push_back(getQuickslotIndex("RB"));
	}
	if (leftTrigger.activated == true) {
		quickslotButtonsPressedIndices.push_back(getQuickslotIndex("LT"));
	}
	if (rightTrigger.activated == true) {
		quickslotButtonsPressedIndices.push_back(getQuickslotIndex("RT"));
	}
	if (hatButtons.up == true) {
		quickslotButtonsPressedIndices.push_back(getQuickslotIndex("up"));
	}
	if (hatButtons.down == true) {
		quickslotButtonsPressedIndices.push_back(getQuickslotIndex("down"));
	}
	if (hatButtons.left == true) {
		quickslotButtonsPressedIndices.push_back(getQuickslotIndex("left"));
	}
	if (hatButtons.right == true) {
		quickslotButtonsPressedIndices.push_back(getQuickslotIndex("right"));
	}
	return quickslotButtonsPressedIndices;
}

//void Character::checkObjectInteraction(objectInteractionTypeEnum objectInteractionType) {
//	if (index == controlledCharacterIndex) {
//
//		//Get total objects
//		int totalObjects = 0;
//		switch (objectInteractionType) {
//			case objectInteractionTypeEnum::skillBasedInteractableObject: {
//				totalObjects = (int)skillBasedInteractableObjects.size();
//				break;
//			}
//		}
//
//		//Check object interaction
//		areaStruct characterGridArea = getGridArea({ position.x, position.y }, { spriteTargetSize.w, spriteTargetSize.h });
//		for (int objectsCnt = 0; objectsCnt < totalObjects; ++objectsCnt) {
//			areaStruct objectInteractableArea = getGridAreaFromSDLRect(skillBasedInteractableObjects[objectsCnt].objectDRect);
//
//			//Widened area
//			objectInteractableArea.x -= 1;
//			objectInteractableArea.w += 2;
//			objectInteractableArea.y -= 1;
//			objectInteractableArea.h += 2;
//
//			//Check interaction
//			bool inObjectArea = false;
//			for (int objectXCnt = objectInteractableArea.x; objectXCnt < objectInteractableArea.x + objectInteractableArea.w; ++objectXCnt) {
//				for (int objectYCnt = objectInteractableArea.y; objectYCnt < objectInteractableArea.y + objectInteractableArea.h; ++objectYCnt) {
//					for (int characterXCnt = characterGridArea.x; characterXCnt < characterGridArea.x + characterGridArea.w; ++characterXCnt) {
//						for (int characterYCnt = characterGridArea.y; characterYCnt < characterGridArea.y + characterGridArea.h; ++characterYCnt) {
//							if (characterXCnt == objectXCnt && characterYCnt == objectYCnt) {
//								inObjectArea = true;
//								goto exitCheckInteraction;
//							}
//						}
//					}
//				}
//			}
//		exitCheckInteraction:
//
//			if (inObjectArea == true) {
//				switch (objectInteractionType) {
//					case objectInteractionTypeEnum::skillBasedInteractableObject: {
//						/*if (controllerButtons.A == true && skillBasedInteractableObjects[objectsCnt].interacting == false) {
//							switch (skillBasedInteractableObjects[objectsCnt].state) {
//								case SkillBasedInteractableObject::stateEnum::closed: {
//									controllerButtons.A = false;
//									skillBasedInteractableObjects[objectsCnt].playUseAnimation = true;
//									skillBasedInteractableObjects[objectsCnt].useAnimation.startTicks = SDL_GetTicks();
//									break;
//								}
//								case SkillBasedInteractableObject::stateEnum::opened: {
//									controllerButtons.A = false;
//									skillBasedInteractableObjects[objectsCnt].playCloseAnimation = true;
//									skillBasedInteractableObjects[objectsCnt].closeAnimation.startTicks = SDL_GetTicks();
//									break;
//								}
//							}
//							
//						}*/
//						if (controllerButtons.A == true) {
//							skillBasedInteractableObjects[objectsCnt].interacting == true;
//						}
//
//						//Get character skill values and check if skill checks all pass
//						skillBasedInteractableObjects[objectsCnt].allSkillChecksPassed = true;
//						for (int skillsRequiredCnt = 0; skillsRequiredCnt < (int)skillBasedInteractableObjects[objectsCnt].skillsRequired.size(); ++skillsRequiredCnt) {
//
//							bool skillRequirementMet = false;
//
//							for (int characterSkillsCnt = 0; characterSkillsCnt < (int)characters[index].skills.size(); ++characterSkillsCnt) {
//
//								if (characters[index].skills[characterSkillsCnt].name == skillBasedInteractableObjects[objectsCnt].skillsRequired[skillsRequiredCnt].name) {
//									skillRequirementMet = true;
//									if ((int)skillBasedInteractableObjects[objectsCnt].skillValues.size() < skillBasedInteractableObjects[objectsCnt].skillsRequired.size()) {
//										skillStruct currentSkill = characters[index].skills[characterSkillsCnt];
//										currentSkill.max = skillBasedInteractableObjects[objectsCnt].skillsRequired[skillsRequiredCnt].current;
//										skillBasedInteractableObjects[objectsCnt].skillValues.push_back(currentSkill);
//									}
//
//									//Check if skill check passed
//									if (skillBasedInteractableObjects[objectsCnt].allSkillChecksPassed == true && characters[index].skills[characterSkillsCnt].current < skillBasedInteractableObjects[objectsCnt].skillsRequired[skillsRequiredCnt].current) {
//										skillBasedInteractableObjects[objectsCnt].allSkillChecksPassed = false;
//									}
//
//									break;
//								}
//							}
//
//							if (skillRequirementMet == false) {
//								if ((int)skillBasedInteractableObjects[objectsCnt].skillValues.size() < skillBasedInteractableObjects[objectsCnt].skillsRequired.size()) {
//									skillStruct currentSkill = skillBasedInteractableObjects[objectsCnt].skillsRequired[skillsRequiredCnt];
//									currentSkill.current = 0;
//									skillBasedInteractableObjects[objectsCnt].skillValues.push_back(currentSkill);
//								}
//
//								skillBasedInteractableObjects[objectsCnt].allSkillChecksPassed = false;
//							}
//						}
//
//						//skillBasedInteractableObjects[objectsCnt].displaySkillValuesBool = true;
//						skillBasedInteractableObjects[objectsCnt].interacting = true;
//						characters[controlledCharacterIndex].blockSlottedElementsUse = true;
//
//						//Get required misc item quantities from controlled character
//						if ((int)skillBasedInteractableObjects[objectsCnt].characterMiscItemQuantities.size() == 0) {
//							skillBasedInteractableObjects[objectsCnt].allRequiredItemsPassed = true;
//							for (int skillBasedInteractableObjectsMiscItemsRequiredCnt = 0; skillBasedInteractableObjectsMiscItemsRequiredCnt < (int)skillBasedInteractableObjects[objectsCnt].miscItemsRequired.size(); ++skillBasedInteractableObjectsMiscItemsRequiredCnt) {
//							
//								skillBasedInteractableObjects[objectsCnt].characterMiscItemQuantities.push_back(0);
//
//								for (int characterMiscItemsCnt = 0; characterMiscItemsCnt < (int)characters[controlledCharacterIndex].miscItems.size(); ++characterMiscItemsCnt) {
//								
//									if (characters[controlledCharacterIndex].miscItems[characterMiscItemsCnt].name == skillBasedInteractableObjects[objectsCnt].miscItemsRequired[skillBasedInteractableObjectsMiscItemsRequiredCnt].name) {
//									
//										skillBasedInteractableObjects[objectsCnt].characterMiscItemQuantities[(int)skillBasedInteractableObjects[objectsCnt].characterMiscItemQuantities.size() - 1] = characters[controlledCharacterIndex].miscItems[characterMiscItemsCnt].quantity;
//									
//										if (skillBasedInteractableObjects[objectsCnt].allRequiredItemsPassed == true && characters[controlledCharacterIndex].miscItems[characterMiscItemsCnt].quantity < skillBasedInteractableObjects[objectsCnt].miscItemsRequired[skillBasedInteractableObjectsMiscItemsRequiredCnt].quantity) {
//										
//											skillBasedInteractableObjects[objectsCnt].allRequiredItemsPassed = false;
//										}
//
//										break;
//									}
//
//								}
//
//							}
//						}
//
//						break;
//					}
//				}
//				break;
//			}
//			else if (inObjectArea == false) {
//				//skillBasedInteractableObjects[objectsCnt].displaySkillValuesBool = false;
//				skillBasedInteractableObjects[objectsCnt].interacting = false;
//				characters[controlledCharacterIndex].blockSlottedElementsUse = false;
//				//skillBasedInteractableObjects[objectsCnt].interacting = false;
//				skillBasedInteractableObjects[objectsCnt].skillValues.clear();
//			}
//		}
//
//	}
//}

int Character::getStatIndex(string statName) {
	for (int statsCnt = 0; statsCnt < (int)stats.size(); ++statsCnt) {
		if (stats[statsCnt].name == statName) {
			return statsCnt;
		}
	}
	return -1;
}

void Character::attack() {

	//Check if quickslot button pressed has ability equipped
	if (disableControls == false && blockSlottedElementsUse == false) {
		vector<int> quickslotButtonsPressedIndices = getQuickslotButtonsPressedIndices();
		for (int quickslotButtonsPressedIndicesCnt = 0; quickslotButtonsPressedIndicesCnt < (int)quickslotButtonsPressedIndices.size(); ++quickslotButtonsPressedIndicesCnt) {
			if (quickslots[quickslotButtonsPressedIndices[quickslotButtonsPressedIndicesCnt]].slottedItemIndex > -1 && quickslots[quickslotButtonsPressedIndices[quickslotButtonsPressedIndicesCnt]].slottedItemType == "ABILITIES") {

				//Init ability animation
				int abilityIndex = quickslots[quickslotButtonsPressedIndices[quickslotButtonsPressedIndicesCnt]].slottedItemIndex;
				int sourceIndex = abilities[abilityIndex].source.index;

				//If enough stamina
				if (stats[getStatIndex("Stamina")].current >= abilities[abilityIndex].staminaConsumption) {

					//Update stamina
					stats[getStatIndex("Stamina")].current -= abilities[abilityIndex].staminaConsumption;

					if (abilities[abilityIndex].animations[0].type == "Melee") {

						//Init animation
						abilities[abilityIndex].animations[0].startAngle = weapons[sourceIndex].rotation.angle;
						abilities[abilityIndex].animations[0].endAngle = abilities[abilityIndex].animations[0].startAngle + 90;
						abilities[abilityIndex].animations[0].currentAngle = abilities[abilityIndex].animations[0].startAngle;
						abilities[abilityIndex].animations[0].centre = weapons[sourceIndex].rotation.centre;
						abilities[abilityIndex].animations[0].startTicks = SDL_GetTicks();
						abilities[abilityIndex].animations[0].running = true;
						abilities[abilityIndex].animations[0].spriteDRect = { weapons[sourceIndex].position.x, weapons[sourceIndex].position.y, weapons[sourceIndex].weaponSize.w, weapons[sourceIndex].weaponSize.h };

					}
					if (abilities[abilityIndex].animations[0].type == "Ranged") {

						//Check if enough ammo
						if (abilities[abilityIndex].requiredAmmoName != "" && ammos[getAmmoCnt(ID, abilities[abilityIndex].requiredAmmoName)].quantity > 0 || abilities[abilityIndex].requiredAmmoName == "") {

							//Update ammo quantity
							--ammos[getAmmoCnt(ID, abilities[abilityIndex].requiredAmmoName)].quantity;

							//If this is the first animation
							if ((int)abilities[abilityIndex].animations.size() == 1 && abilities[abilityIndex].animations[0].running == false) {
								abilities[abilityIndex].animations[0].centre = weapons[sourceIndex].rotation.centre;
								abilities[abilityIndex].animations[0].currentAngle = weapons[sourceIndex].rotation.angle;
								abilities[abilityIndex].animations[0].distance = 0;
								abilities[abilityIndex].animations[0].originalPosition = weapons[sourceIndex].position;
								abilities[abilityIndex].animations[0].spriteDRect = { abilities[abilityIndex].animations[0].originalPosition.x + (int)(abilities[abilityIndex].animations[0].distance * cos(((abilities[abilityIndex].animations[0].currentAngle) * M_PI) / 180)), abilities[abilityIndex].animations[0].originalPosition.y + (int)(abilities[abilityIndex].animations[0].distance * sin(((abilities[abilityIndex].animations[0].currentAngle) * M_PI) / 180)), tileSize.w, tileSize.h };
								abilities[abilityIndex].animations[0].startTicks = SDL_GetTicks();
								abilities[abilityIndex].animations[0].running = true;
							}
							else {

								//Create additional animation based on first animation
								animationStruct currentAnimation = abilities[abilityIndex].animations[0];
								currentAnimation.centre = weapons[sourceIndex].rotation.centre;
								currentAnimation.currentAngle = weapons[sourceIndex].rotation.angle;
								currentAnimation.distance = 0;
								currentAnimation.originalPosition = weapons[sourceIndex].position;
								currentAnimation.spriteDRect = { currentAnimation.originalPosition.x + (int)(currentAnimation.distance * cos(((currentAnimation.currentAngle) * M_PI) / 180)), currentAnimation.originalPosition.y + (int)(currentAnimation.distance * sin(((currentAnimation.currentAngle) * M_PI) / 180)), tileSize.w, tileSize.h };
								currentAnimation.startTicks = SDL_GetTicks();
								currentAnimation.running = true;
								abilities[abilityIndex].animations.push_back(currentAnimation);

							}

						}

					}
				}

			}
		}

	}
}

void Character::animateAbilities() {
	for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
		for (int animationsCnt = 0; animationsCnt < (int)abilities[abilitiesCnt].animations.size(); ++animationsCnt) {
			if (abilities[abilitiesCnt].animations[animationsCnt].running == true && SDL_GetTicks() - abilities[abilitiesCnt].animations[animationsCnt].startTicks >= abilities[abilitiesCnt].animations[animationsCnt].delay / FPSTimerMod) {
				abilities[abilitiesCnt].animations[animationsCnt].startTicks = SDL_GetTicks();

				if (abilities[abilitiesCnt].animations[animationsCnt].type == "Melee") {

					//Swing melee weapon
					if (abilities[abilitiesCnt].animations[animationsCnt].currentAngle != abilities[abilitiesCnt].animations[animationsCnt].endAngle) {
						if (abilities[abilitiesCnt].animations[animationsCnt].startAngle < abilities[abilitiesCnt].animations[animationsCnt].endAngle) {
							abilities[abilitiesCnt].animations[animationsCnt].currentAngle += abilities[abilitiesCnt].animations[animationsCnt].pixelIncrement;
							if (abilities[abilitiesCnt].animations[animationsCnt].currentAngle > abilities[abilitiesCnt].animations[animationsCnt].endAngle) {
								abilities[abilitiesCnt].animations[animationsCnt].currentAngle = abilities[abilitiesCnt].animations[animationsCnt].endAngle;
							}
						}
						else {
							abilities[abilitiesCnt].animations[animationsCnt].currentAngle -= abilities[abilitiesCnt].animations[animationsCnt].pixelIncrement;
							if (abilities[abilitiesCnt].animations[animationsCnt].currentAngle < abilities[abilitiesCnt].animations[animationsCnt].startAngle) {
								abilities[abilitiesCnt].animations[animationsCnt].currentAngle = abilities[abilitiesCnt].animations[animationsCnt].startAngle;
							}
						}
					}
					else {
						abilities[abilitiesCnt].animations[animationsCnt].running = false;
					}

				}
				else if (abilities[abilitiesCnt].animations[animationsCnt].type == "Ranged") {

					//Move projectile
					abilities[abilitiesCnt].animations[animationsCnt].distance += abilities[abilitiesCnt].animations[animationsCnt].pixelIncrement;

				}

			}
		}
	}
}

void Character::stopAbilityAnimations() {
	for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
		for (int animationsCnt = 0; animationsCnt < (int)abilities[abilitiesCnt].animations.size(); ++animationsCnt) {

			//If running ability animation is off overworld grid then stop it
			if (abilities[abilitiesCnt].animations[animationsCnt].running == true && areaWithinGrid(getGridAreaFromPixelArea(convertSDLRectToArea(abilities[abilitiesCnt].animations[animationsCnt].spriteDRect)), layerIndex) == false) {
				abilities[abilitiesCnt].animations[animationsCnt].running = false;
			}

		}
	}
}

void Character::renderAbilityAnimations() {
	for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
		for (int animationsCnt = 0; animationsCnt < (int)abilities[abilitiesCnt].animations.size(); ++animationsCnt) {
			if (abilities[abilitiesCnt].animations[animationsCnt].running == true) {
				if (abilities[abilitiesCnt].animations[animationsCnt].type == "Melee") {
					abilities[abilitiesCnt].animations[animationsCnt].spriteDRect.x = position.x + (spriteTargetSize.w / 2);
					abilities[abilitiesCnt].animations[animationsCnt].spriteDRect.y = position.y + (spriteTargetSize.h / 2);
				}
				else if (abilities[abilitiesCnt].animations[animationsCnt].type == "Ranged") {
					abilities[abilitiesCnt].animations[animationsCnt].spriteDRect.x = abilities[abilitiesCnt].animations[animationsCnt].originalPosition.x + (int)(abilities[abilitiesCnt].animations[animationsCnt].distance * cos(((abilities[abilitiesCnt].animations[animationsCnt].currentAngle) * M_PI) / 180));
					abilities[abilitiesCnt].animations[animationsCnt].spriteDRect.y = abilities[abilitiesCnt].animations[animationsCnt].originalPosition.y + (int)(abilities[abilitiesCnt].animations[animationsCnt].distance * sin(((abilities[abilitiesCnt].animations[animationsCnt].currentAngle) * M_PI) / 180));
				}
				if (SDLRectWithinCameraView(abilities[abilitiesCnt].animations[animationsCnt].spriteDRect) == true) {
					abilities[abilitiesCnt].animations[animationsCnt].spriteDRect.x -= camera.area.x;
					abilities[abilitiesCnt].animations[animationsCnt].spriteDRect.y -= camera.area.y;
					SDL_RenderCopyEx(renderer, spriteSheets[abilities[abilitiesCnt].animations[animationsCnt].spriteSheetIndex].texture, &abilities[abilitiesCnt].animations[animationsCnt].spritesSRect[abilities[abilitiesCnt].animations[animationsCnt].spriteIndex], &abilities[abilitiesCnt].animations[animationsCnt].spriteDRect, abilities[abilitiesCnt].animations[animationsCnt].currentAngle, &abilities[abilitiesCnt].animations[animationsCnt].centre, abilities[abilitiesCnt].animations[animationsCnt].flip);
				}
			}
		}
	}
}

void Character::createAdditionalStatusEffect(characterConstructorVarsStruct::abilityStruct& ability, int statusEffectsCnt, int characterHitCnt) {
	if (ability.statusEffects[statusEffectsCnt].cumulativeType.numberOfTimesToAdd == -1 || ability.statusEffects[statusEffectsCnt].cumulativeType.numberOfTimesAdded < ability.statusEffects[statusEffectsCnt].cumulativeType.numberOfTimesToAdd) {
		characterConstructorVarsStruct::statusEffectStruct currentStatusEffect = ability.statusEffects[statusEffectsCnt];
		currentStatusEffect.duration.startTicks = SDL_GetTicks();
		currentStatusEffect.sourceCharacterIndex = characters[characterHitCnt].ID;
		currentStatusEffect.sourceAbilityIndex = ability.index;
		currentStatusEffect.applicationFrequency.startTicks = SDL_GetTicks();

		//Init status effect animation
		currentStatusEffect.animation.running = true;
		currentStatusEffect.animation.spriteIndex = 0;
		currentStatusEffect.animation.startTicks = SDL_GetTicks();

		characters[characterHitCnt].statusEffects.push_back(currentStatusEffect);

		++ability.statusEffects[statusEffectsCnt].cumulativeType.numberOfTimesAdded;
	}
}

void Character::checkTargetHitByAttack() {

	//Check if any running ability has hit a target
	for (int abilitiesCnt = 0; abilitiesCnt < (int)abilities.size(); ++abilitiesCnt) {
		for (int animationsCnt = 0; animationsCnt < (int)abilities[abilitiesCnt].animations.size(); ++animationsCnt) {

			if (abilities[abilitiesCnt].animations[animationsCnt].type == "Melee") {
				abilities[abilitiesCnt].animations[animationsCnt].spriteDRect.x = position.x;
				abilities[abilitiesCnt].animations[animationsCnt].spriteDRect.y = position.y;
			}

			if (abilities[abilitiesCnt].animations[animationsCnt].running == true) {
				areaStruct abilityGridArea = getGridArea({ abilities[abilitiesCnt].animations[animationsCnt].spriteDRect.x, abilities[abilitiesCnt].animations[animationsCnt].spriteDRect.y }, { abilities[abilitiesCnt].animations[animationsCnt].spriteDRect.w, abilities[abilitiesCnt].animations[animationsCnt].spriteDRect.h });
				for (int abilitySpriteGridXCnt = abilityGridArea.x; abilitySpriteGridXCnt < abilityGridArea.x + abilityGridArea.w; ++abilitySpriteGridXCnt) {
					for (int abilitySpriteGridYCnt = abilityGridArea.y; abilitySpriteGridYCnt < abilityGridArea.y + abilityGridArea.h; ++abilitySpriteGridYCnt) {

						//Check if character hit
						for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
							int characterHitCnt = -1;
							if (characters[charactersCnt].ID != ID) {
								areaStruct characterGridArea = getGridArea(characters[charactersCnt].position, { characters[charactersCnt].spriteTargetSize.w, characters[charactersCnt].spriteTargetSize.h });
								for (int characterGridXCnt = characterGridArea.x; characterGridXCnt < characterGridArea.x + characterGridArea.w; ++characterGridXCnt) {
									for (int characterGridYCnt = characterGridArea.y; characterGridYCnt < characterGridArea.y + characterGridArea.h; ++characterGridYCnt) {
										if (abilitySpriteGridXCnt == characterGridXCnt && abilitySpriteGridYCnt == characterGridYCnt) {
											characterHitCnt = charactersCnt;
											goto exitCharacterHitCheck;
										}
									}
								}
							exitCharacterHitCheck:
								int z = 0;
							}
							if (characterHitCnt > -1) {

								//Add status effects from ability to target
								for (int statusEffectsCnt = 0; statusEffectsCnt < (int)abilities[abilitiesCnt].statusEffects.size(); ++statusEffectsCnt) {

									//Create additional effect
									//if (abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.createAdditionalEffect == true) {
									//	if (abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.numberOfTimesToAdd == -1 || abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.numberOfTimesAdded < abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.numberOfTimesToAdd) {
									//		Character::statusEffectStruct currentStatusEffect = abilities[abilitiesCnt].statusEffects[statusEffectsCnt];
									//		currentStatusEffect.duration.startTicks = SDL_GetTicks();
									//		currentStatusEffect.sourceCharacterIndex = characters[characterHitCnt].index;
									//		currentStatusEffect.sourceAbilityIndex = abilities[abilitiesCnt].index;
									//		currentStatusEffect.applicationFrequency.startTicks = SDL_GetTicks();

									//		//Init status effect animation
									//		currentStatusEffect.animation.running = true;
									//		currentStatusEffect.animation.spriteIndex = 0;
									//		currentStatusEffect.animation.startTicks = SDL_GetTicks();

									//		characters[characterHitCnt].statusEffects.push_back(currentStatusEffect);

									//		++abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.numberOfTimesAdded;
									//	}
									//}
									if (abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.createAdditionalEffect == true) {
										createAdditionalStatusEffect(abilities[abilitiesCnt], statusEffectsCnt, characterHitCnt);
									}

									//Add to existing effect
									if (abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.addToExistingEffect == true) {

										//Check if status effect with same character and ability sources exist on character being hit
										bool effectExists = false;
										for (int characterHitAbilityStatusEffectsCnt = 0; characterHitAbilityStatusEffectsCnt < (int)characters[characterHitCnt].statusEffects.size(); ++characterHitAbilityStatusEffectsCnt) {
											if (characters[characterHitCnt].statusEffects[characterHitAbilityStatusEffectsCnt].sourceCharacterIndex == ID && characters[characterHitCnt].statusEffects[characterHitAbilityStatusEffectsCnt].sourceAbilityIndex == abilities[abilitiesCnt].index) {
												if (abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.numberOfTimesToAdd == -1 || abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.numberOfTimesAdded < abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.numberOfTimesToAdd) {
													effectExists = true;

													//Add to mod value
													if (abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.addToModValue == true) {
														characters[characterHitCnt].statusEffects[characterHitAbilityStatusEffectsCnt].modValue += abilities[abilitiesCnt].statusEffects[statusEffectsCnt].modValue;
													}

													//Init start ticks
													if (characters[characterHitCnt].statusEffects[characterHitAbilityStatusEffectsCnt].duration.startTicks == 0) {
														characters[characterHitCnt].statusEffects[characterHitAbilityStatusEffectsCnt].duration.startTicks = SDL_GetTicks();
													}

													//Add to duration
													if (abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.addToDuration == true) {
														characters[characterHitCnt].statusEffects[characterHitAbilityStatusEffectsCnt].duration.delay += abilities[abilitiesCnt].statusEffects[statusEffectsCnt].duration.delay;
													}

													//Init status effect animation
													if (abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.addToModValue == true || abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.addToDuration == true) {
														characters[characterHitCnt].statusEffects[characterHitAbilityStatusEffectsCnt].animation.running = true;
														characters[characterHitCnt].statusEffects[characterHitAbilityStatusEffectsCnt].animation.spriteIndex = 0;
														characters[characterHitCnt].statusEffects[characterHitAbilityStatusEffectsCnt].animation.startTicks = SDL_GetTicks();
													}

													++abilities[abilitiesCnt].statusEffects[statusEffectsCnt].cumulativeType.numberOfTimesAdded;
													break;
												}
											}
										}

										//Create additional effect
										if (effectExists == false) {
											createAdditionalStatusEffect(abilities[abilitiesCnt], statusEffectsCnt, characterHitCnt);
										}

									}

								}

							}
						}

					}
				}
			}
		}
	}

}

int Character::getSkillCntByName(string name) {
	for (int skillsCnt = 0; skillsCnt < (int)skills.size(); ++skillsCnt) {
		if (skills[skillsCnt].name == name) {
			return skillsCnt;
		}
	}
	return -1;
}

int Character::getStatCntByName(string name) {
	for (int statsCnt = 0; statsCnt < (int)stats.size(); ++statsCnt) {
		if (skills[statsCnt].name == name) {
			return statsCnt;
		}
	}
	return -1;
}

void Character::runStatusEffects() {
	for (int statusEffectsCnt = 0; statusEffectsCnt < (int)statusEffects.size(); ++statusEffectsCnt) {
		if (statusEffects[statusEffectsCnt].duration.startTicks > 0) {

			//Apply status effect
			if (SDL_GetTicks() - statusEffects[statusEffectsCnt].duration.startTicks < statusEffects[statusEffectsCnt].duration.delay / FPSTimerMod && SDL_GetTicks() - statusEffects[statusEffectsCnt].applicationFrequency.startTicks >= statusEffects[statusEffectsCnt].applicationFrequency.delay / FPSTimerMod) {
				statusEffects[statusEffectsCnt].applicationFrequency.startTicks = SDL_GetTicks();

				//Get mod value
				int modTypeMod = -1;
				if (statusEffects[statusEffectsCnt].modType == "Damage") {
					modTypeMod = -1;
				}
				else if (statusEffects[statusEffectsCnt].modType == "Boost") {
					modTypeMod = 1;
				}
				int modValue = statusEffects[statusEffectsCnt].modValue * modTypeMod;

				//Update target mod value
				if (statusEffects[statusEffectsCnt].modTargetType == "Skill") {
					int skillCnt = getSkillCntByName(statusEffects[statusEffectsCnt].modTargetName);
					skills[skillCnt].current += modValue;
				}
				else if (statusEffects[statusEffectsCnt].modTargetType == "Stat") {
					int statCnt = getStatCntByName(statusEffects[statusEffectsCnt].modTargetName);
					stats[statCnt].current += modValue;
				}

			}

			//Mark status effect for removal
			if (SDL_GetTicks() - statusEffects[statusEffectsCnt].duration.startTicks >= statusEffects[statusEffectsCnt].duration.delay / FPSTimerMod) {
				statusEffects[statusEffectsCnt].duration.startTicks = 0;
				indicesOfStatusEffectsToRemove.push_back(statusEffects[statusEffectsCnt].index);
			}

		}
	}
}

int Character::getStatusEffectCntByIndex(int index) {
	for (int statusEffectsCnt = 0; statusEffectsCnt < (int)statusEffects.size(); ++statusEffectsCnt) {
		if (statusEffects[statusEffectsCnt].index == index) {
			return statusEffectsCnt;
		}
	}
	return -1;
}

void Character::wakeUp() {
	if (sleep.state == true) {
		if (((int)sleep.delay > -1 && SDL_GetTicks() - sleep.startTicks >= sleep.delay)
			|| sleep.delay == -1) {
			sleep.state = false;
		}
	}
}

bool Character::compareSchedules(scheduleStruct scheduleA, scheduleStruct scheduleB) {
	if ((int)scheduleA.tasks.size() != (int)scheduleB.tasks.size()) {
		return false;
	}
	else {
		for (int tasksCnt = 0; tasksCnt < (int)scheduleA.tasks.size(); ++tasksCnt) {
			if (compareTime(scheduleA.tasks[tasksCnt].startTime, scheduleB.tasks[tasksCnt].startTime) == false) {
				return false;
			}
			else if (compareTime(scheduleA.tasks[tasksCnt].endTime, scheduleB.tasks[tasksCnt].endTime) == false) {
				return false;
			}
			else if (scheduleA.tasks[tasksCnt].name != scheduleB.tasks[tasksCnt].name) {
				return false;
			}
			else if (scheduleA.tasks[tasksCnt].goal != scheduleB.tasks[tasksCnt].goal) {
				return false;
			}
		}
	}
}

void Character::removeStatusEffects() {
	if ((int)indicesOfStatusEffectsToRemove.size() > 0) {
		for (int indicesOfStatusEffectsToRemoveCnt = 0; indicesOfStatusEffectsToRemoveCnt < (int)indicesOfStatusEffectsToRemove.size(); ++indicesOfStatusEffectsToRemoveCnt) {
			statusEffects.erase(statusEffects.begin() + getStatusEffectCntByIndex(indicesOfStatusEffectsToRemove[indicesOfStatusEffectsToRemoveCnt]));
		}
		indicesOfStatusEffectsToRemove.clear();
	}
}

void Character::animateStatusEffects() {
	for (int statusEffectsCnt = 0; statusEffectsCnt < (int)statusEffects.size(); ++statusEffectsCnt) {
		if (statusEffects[statusEffectsCnt].animation.running == true && SDL_GetTicks() - statusEffects[statusEffectsCnt].animation.startTicks >= statusEffects[statusEffectsCnt].animation.delay / FPSTimerMod) {
			statusEffects[statusEffectsCnt].animation.startTicks = SDL_GetTicks();
			if (statusEffects[statusEffectsCnt].animation.spriteIndex < (int)statusEffects[statusEffectsCnt].animation.spritesSRect.size() - 1) {
				++statusEffects[statusEffectsCnt].animation.spriteIndex;
			}
			else {
				statusEffects[statusEffectsCnt].animation.spriteIndex = 0;
			}
		}
	}
}

void Character::renderStatusEffects() {
	for (int statusEffectsCnt = 0; statusEffectsCnt < (int)statusEffects.size(); ++statusEffectsCnt) {
		if (statusEffects[statusEffectsCnt].animation.running == true) {
			statusEffects[statusEffectsCnt].animation.spriteDRect.x = position.x - camera.area.x;
			statusEffects[statusEffectsCnt].animation.spriteDRect.y = position.y - camera.area.y;
			statusEffects[statusEffectsCnt].animation.spriteDRect.w = spriteTargetSize.w;
			statusEffects[statusEffectsCnt].animation.spriteDRect.h = spriteTargetSize.h;

			if (SDLRectWithinCameraView(statusEffects[statusEffectsCnt].animation.spriteDRect) == true) {
				SDL_RenderCopy(renderer, spriteSheets[statusEffects[statusEffectsCnt].animation.spriteSheetIndex].texture, &statusEffects[statusEffectsCnt].animation.spritesSRect[statusEffects[statusEffectsCnt].animation.spriteIndex], &statusEffects[statusEffectsCnt].animation.spriteDRect);
			}
		}
	}
}

void Character::checkObjectProximity() {
	areaStruct characterGridArea = getGridAreaFromPixelArea({ position.x, position.y, spriteTargetSize.w, spriteTargetSize.h });

	//Adjust character grid area
	characterGridArea = { characterGridArea.x - 1, characterGridArea.y - 1, characterGridArea.w + 1, characterGridArea.h + 1 };

	//Check proximity to object
	for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
		/*if (index == controlledCharacterIndex && objects[objectsCnt].type == "Door") {
			objects[objectsCnt].displayOptions = false;
		}*/
		areaStruct doorGridArea = getGridAreaFromSDLRect(objects[objectsCnt].getObjectDRect());

		//Adjust door grid area
		doorGridArea = { doorGridArea.x - 1, doorGridArea.y - 1, doorGridArea.w + 1, doorGridArea.h + 1 };

		if (checkCollision(characterGridArea, doorGridArea) == true) {
			if (ID == controlledCharacterIndex && objects[objectsCnt].displayOptions == false) {
				if (objects[objectsCnt].displayCraftingMenu == false) {
					objects[objectsCnt].displayOptions = true;
				}
				objects[objectsCnt].setCharacterID(ID);
				selectedMenuLayer = 0;
			}
			break;
		}
		else {
			if (ID == controlledCharacterIndex) {
				objects[objectsCnt].displayOptions = false;
				objects[objectsCnt].displayCraftingMenu = false;
				/*objects[objectsCnt].keypad.inputCode = false;
				objects[objectsCnt].keyboard.inputCode = false;*/
				for (int inputDevicesCnt = 0; inputDevicesCnt < (int)objects[objectsCnt].inputDevices.size(); ++inputDevicesCnt) {
					objects[objectsCnt].inputDevices[inputDevicesCnt].inputCode = false;
				}
				objects[objectsCnt].setDisplayInputDeviceSelectionMenu(false);
				if (getOrganisationIndex(objects[objectsCnt].getOptionOrganisationID()) > -1) {
					organisations[getOrganisationIndex(objects[objectsCnt].getOptionOrganisationID())].setDisplayHierarchyBool(false);
				}
			}
		}
	}

}

void Character::removeMiscItems(vector<miscItemsStruct> miscItemsToRemove) {
	for (int miscItemsToRemoveCnt = 0; miscItemsToRemoveCnt < (int)miscItemsToRemove.size(); ++miscItemsToRemoveCnt) {
		for (int miscItemsCnt = 0; miscItemsCnt < (int)miscItems.size(); ++miscItemsCnt) {
			if (miscItems[miscItemsCnt].name == miscItemsToRemove[miscItemsToRemoveCnt].name) {

				//Remove quantity
				miscItems[miscItemsCnt].quantity -= miscItemsToRemove[miscItemsToRemoveCnt].quantity;

				//Remove item
				if (miscItems[miscItemsCnt].quantity <= 0) {
					miscItems.erase(miscItems.begin() + miscItemsCnt);
				}

				break;
			}
		}
	}
}

void Character::addMiscItem(miscItemsStruct currentMiscItem) {

	//Check if misc item already in inventory
	int miscItemsCnt = -1;
	for (miscItemsCnt = 0; miscItemsCnt < (int)miscItems.size(); ++miscItemsCnt) {
		if (miscItems[miscItemsCnt].name == currentMiscItem.name) {
			break;
		}
	}

	if (miscItemsCnt > -1) {

		//Update quantity
		miscItems[miscItemsCnt].quantity += currentMiscItem.quantity;

	}
	else {

		//Add to inventory
		miscItems.push_back(currentMiscItem);

	}
}

void Character::addCraftingItems(miscItemsStruct currentCraftingItem) {

	//Check if crafting item already in inventory
	int craftingItemsCnt = -1;
	for (craftingItemsCnt = 0; craftingItemsCnt < (int)craftingItems.size(); ++craftingItemsCnt) {
		if (craftingItems[craftingItemsCnt].name == currentCraftingItem.name) {
			break;
		}
	}

	if (craftingItemsCnt > -1) {

		//Update quantity
		craftingItems[craftingItemsCnt].quantity += currentCraftingItem.quantity;

	}
	else {

		//Add to inventory
		craftingItems.push_back(currentCraftingItem);

	}
}

void Character::addCyberware(characterConstructorVarsStruct::cyberwareStruct currentCyberware) {

	//Check if cyberware already in inventory
	int cyberwaresCnt = -1;
	for (cyberwaresCnt = 0; cyberwaresCnt < (int)cyberwares.size(); ++cyberwaresCnt) {
		if (cyberwares[cyberwaresCnt].name == currentCyberware.name) {
			break;
		}
	}

	if (cyberwaresCnt > -1) {

		//Update cyberware quantity
		cyberwares[cyberwaresCnt].quantity += currentCyberware.quantity;

	}
	else {

		//Update ID of cyberware to be added
		vector<int> characterCyberwareIDs;
		for (int cyberwaresCnt = 0; cyberwaresCnt < (int)cyberwares.size(); ++cyberwaresCnt) {
			characterCyberwareIDs.push_back(cyberwares[cyberwaresCnt].index);
		}
		currentCyberware.index = getFreeID(characterCyberwareIDs);

		//Add to inventory
		cyberwares.push_back(currentCyberware);

	}
}

void Character::addGear(characterConstructorVarsStruct::gearStruct currentGear) {

	//Check if gear already in inventory
	int gearsCnt = -1;
	for (gearsCnt = 0; gearsCnt < (int)gears.size(); ++gearsCnt) {
		if (gears[gearsCnt].name == currentGear.name) {
			break;
		}
	}

	if (gearsCnt > -1) {

		//Update quantity
		gears[gearsCnt].quantity += currentGear.quantity;

	}
	else {

		//Update index
		vector<int> gearIndices;
		for (int gearsCnt = 0; gearsCnt < (int)gears.size(); ++gearsCnt) {
			gearIndices.push_back(gears[gearsCnt].index);
		}
		currentGear.index = getFreeID(gearIndices);

		//Add to inventory
		gears.push_back(currentGear);

	}
}

void Character::addWeapon(characterConstructorVarsStruct::weaponStruct currentWeapon) {

	//Check if weapon already in inventory
	int weaponsCnt = -1;
	for (weaponsCnt = 0; weaponsCnt < (int)weapons.size(); ++weaponsCnt) {
		if (weapons[weaponsCnt].name == currentWeapon.name) {
			break;
		}
	}

	if (weaponsCnt > -1) {

		//Update quantity
		weapons[weaponsCnt].quantity += currentWeapon.quantity;

	}
	else {

		//Update index
		vector<int> weaponIndices;
		for (int weaponsCnt = 0; weaponsCnt < (int)weapons.size(); ++weaponsCnt) {
			weaponIndices.push_back(weapons[weaponsCnt].index);
		}
		currentWeapon.index = getFreeID(weaponIndices);

		//Add weapon
		weapons.push_back(currentWeapon);

	}
}

void Character::addConsumable(characterConstructorVarsStruct::consumableItemStruct currentConsumableItem) {

	//Check if already in inventory
	int consumableItemsCnt = -1;
	for (consumableItemsCnt = 0; consumableItemsCnt < (int)consumableItems.size(); ++consumableItemsCnt) {
		if (consumableItems[consumableItemsCnt].name == currentConsumableItem.name) {
			break;
		}
	}

	if (consumableItemsCnt > -1) {

		//Update quantity
		consumableItems[consumableItemsCnt].quantity += currentConsumableItem.quantity;

	}
	else {

		//Update index
		vector<int> consumableItemIndices;
		for (int consumableItemsCnt = 0; consumableItemsCnt < (int)consumableItems.size(); ++consumableItemsCnt) {
			consumableItemIndices.push_back(consumableItems[consumableItemsCnt].index);
		}
		currentConsumableItem.index = getFreeID(consumableItemIndices);

		//Add to inventory
		consumableItems.push_back(currentConsumableItem);

	}
}

void Character::addAmmo(characterConstructorVarsStruct::ammoStruct currentAmmo) {

	//Check if already in inventory
	int ammosCnt = -1;
	for (ammosCnt = 0; ammosCnt < (int)ammos.size(); ++ammosCnt) {
		if (ammos[ammosCnt].name == currentAmmo.name) {
			break;
		}
	}

	if (ammosCnt > -1) {

		//Update quantity
		ammos[ammosCnt].quantity += currentAmmo.quantity;

	}
	else {

		//Add to inventory
		ammos.push_back(currentAmmo);

	}
}

void Character::removeCraftingItem(miscItemsStruct currentCraftingItem) {

	//Check if already in inventory
	int craftingItemsCnt = -1;
	for (int craftingItemsCnt = 0; craftingItemsCnt < (int)craftingItems.size(); ++craftingItemsCnt) {
		if (craftingItems[craftingItemsCnt].name == currentCraftingItem.name) {
			break;
		}
	}

	if (craftingItemsCnt > -1) {

		//Update quantity
		craftingItems[craftingItemsCnt].quantity -= currentCraftingItem.quantity;

		//If quantity = 0 then remove from inventory
		if (craftingItems[craftingItemsCnt].quantity == 0) {
			craftingItems.erase(craftingItems.begin() + craftingItemsCnt);
		}

	}
}

void Character::addBlueprint(blueprintStruct currentBlueprint) {

	//Check if already in inventory
	bool blueprintFound = false;
	for (int blueprintsCnt = 0; blueprintsCnt < (int)blueprints.size(); ++blueprintsCnt) {
		if (blueprints[blueprintsCnt].blueprint.name == currentBlueprint.blueprint.name) {
			blueprintFound = true;
			break;
		}
	}

	if (blueprintFound == false) {

		//Add blueprint
		blueprints.push_back(currentBlueprint);

	}
}

void Character::setGoal() {
	if (ID != controlledCharacterIndex) {
		
		//Update current task
		int currentSchedule = privateCharacterConstructorScheduleVars.currentSchedule;

		for (int tasksCnt = 0; tasksCnt < (int)privateCharacterConstructorScheduleVars.schedules[currentSchedule].tasks.size(); ++tasksCnt) {
			if (timeBetweenRange(gameClock, privateCharacterConstructorScheduleVars.schedules[currentSchedule].tasks[tasksCnt].startTime, privateCharacterConstructorScheduleVars.schedules[currentSchedule].tasks[tasksCnt].endTime, { 0, 0, 0, 1, 1, 1 })) {
				privateCharacterConstructorScheduleVars.schedules[currentSchedule].currentTask = tasksCnt;
				break;
			}
		}

		//Update goal and conditions
		int currentTask = privateCharacterConstructorScheduleVars.schedules[currentSchedule].currentTask;
		if (goal != privateCharacterConstructorScheduleVars.schedules[currentSchedule].tasks[currentTask].goal) {
			goal = privateCharacterConstructorScheduleVars.schedules[currentSchedule].tasks[currentTask].goal;

			conditions.clear();
			if (goal == "Sleep") {
				conditions = {
					{ "Check if awake", false},
					{ "Find bed", false },
					{ "Get path to bed", false },
					{ "Follow path", false },
					{ "Sleep", false }
				};
			}
			else if (goal == "Follow controlled character") {
				conditions = {
					{ "Check distance from controlled character", false },
					{ "Get path to controlled character", false },
					{ "Follow path", false }
				};
			}
		}

	}
}

void Character::carryOutGoal() {
	if (ID != controlledCharacterIndex) {

		//Check if all conditions passed
		for (int conditionsCnt = 0; conditionsCnt < (int)conditions.size(); ++conditionsCnt) {
			if (conditions[conditionsCnt].condition == "Check if awake" && sleep.state == false) {
				conditions[conditionsCnt].passed = true;
			}
			else if (conditions[conditionsCnt].condition == "Find bed" && closestObject.ID == -1) {

				////Get closest unoccupied bed
				//bool objectReached = false;
				//closestObjectStruct closestBed;
				//for (int objectsCnt = 0; objectsCnt < (int)objects.size(); ++objectsCnt) {
				//	int objectID = objects[objectsCnt].getID();

				//	//Check if any other character has reached this object
				//	for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
				//		if (characters[charactersCnt].getObjectReachedID() == objectID) {
				//			objectReached = true;
				//			break;
				//		}
				//	}

				//	//Check if can sleep
				//	if (objectReached == false) {
				//		vector<objectConstructorVarsStruct::optionStruct> objectOptions = objects[objectsCnt].getOptions();
				//		for (int optionsCnt = 0; optionsCnt < (int)objectOptions.size(); ++optionsCnt) {
				//			if (objectOptions[optionsCnt].canSleep == true) {
				//				SDL_Rect objectDrect = objects[objectsCnt].getObjectDRect();
				//				XYStruct objectPosition = { objectDrect.x, objectDrect.y };
				//				int currentHeuristic = getHeuristic(getGridPosition(position), getGridPosition(objectPosition));

				//				if (closestBed.heuristic == -1 || currentHeuristic > -1 && currentHeuristic < closestBed.heuristic) {
				//					closestBed.heuristic = currentHeuristic;
				//					closestBed.position = objectPosition;
				//					closestBed.size = { objectDrect.w, objectDrect.h };
				//					closestBed.ID = objectID;
				//				}
				//			}
				//		}
				//	}

				//}

				closestObject = findClosestObject(objects, "Bed", position, 1);
				
				if (closestObject.ID > -1) {
					conditions[conditionsCnt].passed = true;
				}
			}
			else if (conditions[conditionsCnt].condition == "Get path to bed" && closestObject.ID > -1 && path.walkPath == false) {

				////Get node size (= size of whichever is largest between character or bed)
				//WHStruct nodeGridSize = { 1, 1 };
				///*WHStruct nodeGridSize = { -1, -1 };
				//if (spriteTargetSize.w * spriteTargetSize.h > closestBed.size.w * closestBed.size.h) {
				//	nodeGridSize = getGridSize(spriteTargetSize);
				//}
				//else {
				//	nodeGridSize = getGridSize(closestBed.size);
				//}*/

				////Create A star maze
				//vector<vector<bool>> maze = createMaze({ (int)overworldGrid.gridTile[layerIndex].size() / nodeGridSize.w, (int)overworldGrid.gridTile[layerIndex][0].size() / nodeGridSize.h });

				////Init A star maze
				//initMazeToOverworldGrid(maze, overworldGrid.gridTile, layerIndex, nodeGridSize);

				//Set path to closest bed
				if (closestObject.position.x > -1) {
					//XYStruct characterGridPosition = getGridPosition(position);
					//XYStruct characterMazePosition = { characterGridPosition.x / nodeGridSize.w, characterGridPosition.y / nodeGridSize.h };
					//XYStruct closestBedGridPosition = getGridPosition(closestObject.position);
					//XYStruct closestBedMazePosition = { closestBedGridPosition.x / nodeGridSize.w, closestBedGridPosition.y / nodeGridSize.h };

					////Remove collision at start and end nodes
					//setMazeCollision(maze, { characterMazePosition.x, characterMazePosition.y, lround(spriteTargetSize.w / tileSize.w), lround(spriteTargetSize.h / tileSize.h) }, false); //character area
					//setMazeCollision(maze, { closestBedMazePosition.x, closestBedMazePosition.y, lround(closestObject.size.w / tileSize.w), lround(closestObject.size.h / tileSize.h) }, false); //bed area

					////Get path
					////printXYStructL({ characterMazePosition, closestBedMazePosition });
					//path.pathToFollow = getAStarPath(maze, characterMazePosition, closestBedMazePosition);
					//convertPathCoordinates(path.pathToFollow, tileSize.w);
					////printInt((int)path.pathToFollow.size());

					createMazeAndGetAStarPath({ position.x, position.y, spriteTargetSize.w, spriteTargetSize.h }, { closestObject.position.x, closestObject.position.y, closestObject.size.w, closestObject.size.h }, layerIndex, { 1, 1 }, path, false, false);

					if ((int)path.pathToFollow.size() > 0 && path.pathFound == true) {
						path.walkPath = true;
						path.currentPathNode = 0;
						path.walkSpeed = 1 * FPSTimerMod;
						conditions[conditionsCnt].passed = true;
					}

				}

			}
			else if (conditions[conditionsCnt].condition == "Follow path" && (int)path.pathToFollow.size() > 0 && path.walkPath == true && path.currentPathNode == (int)path.pathToFollow.size() - 1) {
				conditions[conditionsCnt].passed = true;
				path.walkPath = false;
				sleep.state = true;
				sleep.startTicks = SDL_GetTicks();
			}
			else if (conditions[conditionsCnt].condition == "Sleep" && sleep.state == true) {
				conditions[conditionsCnt].passed = true;
			}
			else if (conditions[conditionsCnt].condition == "Check distance from controlled character" && path.walkPath == false && path.getPath == false && getHeuristic(position, characters[controlledCharacterIndex].getPosition()) > spriteTargetSize.h * 2) {
				path.getPath = true;
			}
			else if (conditions[conditionsCnt].condition == "Get path to controlled character" && path.walkPath == false && path.getPath == true) {

				//Get non-collidable position next to controlled character
				XYStruct controlledCharacterGridPosition = characters[controlledCharacterIndex].getPosition();
				WHStruct controlledCharacterGridSize = characters[controlledCharacterIndex].getSpriteTargetSize();
				XYStruct characterGridPosition = getGridPosition(position);
				WHStruct characterGridSize = getGridSize(spriteTargetSize);
				areaStruct targetArea = { randInt(controlledCharacterGridPosition.x - (characterGridSize.w * 2), controlledCharacterGridPosition.x + controlledCharacterGridSize.w + (characterGridSize.w * 2)), randInt(controlledCharacterGridPosition.y - (characterGridSize.h * 2), controlledCharacterGridPosition.y + controlledCharacterGridSize.h + (characterGridSize.h * 2)), characterGridSize.w, characterGridSize.h };

				//Get path to controlled character
				if (checkCollisionWithOverworldGrid(targetArea, layerIndex) == false) {
					//vector<vector<bool>> maze = createMaze({ (int)overworldGrid.gridTile[layerIndex].size(), (int)overworldGrid.gridTile[layerIndex][0].size() });
					//initMazeToOverworldGrid(maze, overworldGrid.gridTile, layerIndex, { 1, 1 });

					//if ((int)path.pathToFollow.size() > 0) {
					//	path.pathToFollow.clear();
					//}

					////Remove collision where character is in maze
					//setMazeCollision(maze, { characterGridPosition.x, characterGridPosition.y, characterGridSize.w, characterGridSize.h }, false);

					////Remove collision at target area
					//setMazeCollision(maze, targetArea, false);

					//path.pathToFollow = getAStarPath(maze, characterGridPosition, controlledCharacterGridPosition);

					XYStruct controlledCharacterPosition = characters[controlledCharacterIndex].getPosition();
					WHStruct controlledCharacterSize = characters[controlledCharacterIndex].getSpriteTargetSize();

					//--;;
					printInt(ID);
					printStr("start");
					if (ID == 1) {
						createMazeAndGetAStarPath({ position.x, position.y, spriteTargetSize.w, spriteTargetSize.h }, { controlledCharacterPosition.x, controlledCharacterPosition.y, controlledCharacterSize.w, controlledCharacterSize.h }, layerIndex, { 1, 1 }, path, false, false);
					}
					printStr("end");
					
					if ((int)path.pathToFollow.size() > 0 && path.pathFound == true) {
						
						//Set character to follow path
						path.walkPath = true;
						path.currentPathNode = 0;
						path.walkSpeed = characters[controlledCharacterIndex].getMoveSpeedPixelIncrement();

					}
				}

			}
		}

	}
}

void Character::setCharacterSleepState(sleepStateStruct currentSleepState) {
	sleep.state = currentSleepState.state;
	sleep.startTicks = currentSleepState.startTicks;
}

void Character::followPath() {
	if ((int)path.pathToFollow.size() > 0 && path.walkPath == true && SDL_GetTicks() - moveSpeed.startTicks >= moveSpeed.delay / FPSTimerMod) {
		moveSpeed.startTicks = SDL_GetTicks();

		//Move character to current node position
		if (position.x != path.pathToFollow[path.currentPathNode].x || position.y != path.pathToFollow[path.currentPathNode].y) {
			directionNamesStruct directionNames;

			if (position.x < path.pathToFollow[path.currentPathNode].x) {
				directionNames.right = true;
				position.x += path.walkSpeed;
				if (position.x > path.pathToFollow[path.currentPathNode].x) {
					position.x = path.pathToFollow[path.currentPathNode].x;
				}
			}
			else if (position.x > path.pathToFollow[path.currentPathNode].x) {
				directionNames.left = true;
				position.x -= path.walkSpeed;
				if (position.x < path.pathToFollow[path.currentPathNode].x) {
					position.x = path.pathToFollow[path.currentPathNode].x;
				}
			}

			if (position.y < path.pathToFollow[path.currentPathNode].y) {
				directionNames.down = true;
				position.y += path.walkSpeed;
				if (position.y > path.pathToFollow[path.currentPathNode].y) {
					position.y = path.pathToFollow[path.currentPathNode].y;
				}
			}
			else if (position.y > path.pathToFollow[path.currentPathNode].y) {
				directionNames.up = true;
				position.y -= path.walkSpeed;
				if (position.y < path.pathToFollow[path.currentPathNode].y) {
					position.y = path.pathToFollow[path.currentPathNode].y;
				}
			}

			//Update direction
			if (directionNames.right == true) {
				direction = directionEnum::right;
			}
			if (directionNames.left == true) {
				direction = directionEnum::left;
			}
			if (directionNames.down == true) {
				direction = directionEnum::down;
			}
			if (directionNames.up == true) {
				direction = directionEnum::up;
			}
			if (directionNames.up == true && directionNames.right == true) {
				direction = directionEnum::upRight;
			}
			else if (directionNames.down == true && directionNames.right == true) {
				direction = directionEnum::downRight;
			}
			else if (directionNames.down == true && directionNames.left == true) {
				direction = directionEnum::downLeft;
			}
			else if (directionNames.up == true && directionNames.left == true) {
				direction = directionEnum::upLeft;
			}

			updateSpriteIndex();
		}
		else {

			//Update current path node
			if (path.currentPathNode < (int)path.pathToFollow.size() - 1) {
				++path.currentPathNode;
			}
			else {

				//Stop following path
				path.walkPath = false;

			}

		}

	}
}

void Character::runSleepAnimation() {
	
	//Check if sleep is done
	if (sleep.state == true && (int)sleep.delay > -1 && SDL_GetTicks() - sleep.startTicks >= sleep.delay) {
		sleep.state = false;
	}

}

int Character::getMoveSpeedPixelIncrement() {
	return moveSpeed.pixelIncrement;
}

void Character::getScheduleFromOrganisation() {
	if (SDL_GetTicks() - organisation.checkFrequencyStartTicks >= organisation.checkFrequencyDelay) {
		organisation.checkFrequencyStartTicks = SDL_GetTicks();

		//Get organisation index
		int organisationIndex = -1;
		for (int organisationsCnt = 0; organisationsCnt < (int)organisations.size(); ++organisationsCnt) {
			if (organisations[organisationsCnt].getID() == organisation.ID) {
				organisationIndex = organisationsCnt;
				break;
			}
		}

		//Get organisation role index
		vector<organisationConstructorVarsStruct::rolePositionStruct> organisationRoles = organisations[organisationIndex].getRoles();
		int organisationRoleIndex = -1;
		for (int organisationRolesCnt = 0; organisationRolesCnt < (int)organisationRoles.size(); ++organisationRolesCnt) {
			if (organisationRoles[organisationRolesCnt].ID == organisation.roleID) {
				organisationRoleIndex = organisationRolesCnt;
				break;
			}
		}

		//Check if schedule from organisation is present in character schedules
		bool organisationRolePresentInCharacterSchedules = false;
		for (int schedulesCnt = 0; schedulesCnt < (int)privateCharacterConstructorScheduleVars.schedules.size(); ++schedulesCnt) {
			if (compareSchedules(privateCharacterConstructorScheduleVars.schedules[schedulesCnt], organisationRoles[organisationRoleIndex].schedule) == true) {
				organisationRolePresentInCharacterSchedules = true;
				break;
			}
		}

		//Get schedule from organisation role
		if (organisationRolePresentInCharacterSchedules == false) {
			privateCharacterConstructorScheduleVars.schedules.push_back(organisationRoles[organisationRoleIndex].schedule);
		}

	}
}

Building::Building(buildingConstructorVarsStruct buildingConstructorVars) {
	ID = buildingConstructorVars.ID;
	buildingDoorID = buildingConstructorVars.buildingDoorID;
	minFloors = buildingConstructorVars.minFloors;
	maxFloors = buildingConstructorVars.maxFloors;
	area = buildingConstructorVars.area;
}

int Building::getID() {
	return ID;
}

int Building::getBuildingDoorID() {
	return buildingDoorID;
}

areaStruct Building::getArea() {
	return area;
}

Object::Object(objectConstructorVarsStruct objectConstructorVars) {
	ID = objectConstructorVars.ID;
	layer = objectConstructorVars.layer;
	type = objectConstructorVars.type;
	collision = objectConstructorVars.collision;
	objectDRect = objectConstructorVars.objectDRect;
	currentStateAnimation = objectConstructorVars.currentStateAnimation;
	stateAnimations = objectConstructorVars.stateAnimations;
	inputDevices = objectConstructorVars.inputDevices;
	options = objectConstructorVars.options;
}

int Object::getID() {
	return ID;
}

int Object::getLayer() {
	return layer;
}

void Object::setCharacterID(int objectCharacterID) {
	characterID = objectCharacterID;
}

string Object::getType() {
	return type;
}

SDL_Rect Object::getObjectDRect() {
	return objectDRect;
}

void Object::setDisplayInputDeviceSelectionMenu(bool objectDisplayInputDeviceSelectionMenu) {
	displayInputDeviceSelectionMenu = objectDisplayInputDeviceSelectionMenu;
}

vector<objectConstructorVarsStruct::inputDeviceStruct> Object::getInputDevices() {
	return inputDevices;
}

vector<objectConstructorVarsStruct::optionStruct> Object::getOptions() {
	return options;
}

int Object::getOptionOrganisationID() {
	return optionOrganisationID;
}

void Object::setPosition(XYStruct position) {
	objectDRect.x = position.x;
	objectDRect.y = position.y;
}

void Object::setCollisionSet(bool newCollisionSet) {
	collisionSet = newCollisionSet;
}

void Object::render() {
	if (SDLRectWithinCameraView(objectDRect) == true) {
		dRect = { objectDRect.x - camera.area.x, objectDRect.y - camera.area.y, objectDRect.w, objectDRect.h };
		SDL_RenderCopy(renderer, spriteSheets[stateAnimations[currentStateAnimation].spriteSheetIndex].texture, &stateAnimations[currentStateAnimation].spritesSRect[stateAnimations[currentStateAnimation].spriteIndex], &dRect);
	}
}

void Object::setObjectCollision() {
	if (collisionSet == false) {
		setOverworldGridCollision(overworldGrid.gridTile, layer, getGridAreaFromSDLRect(objectDRect), collision);
		collisionSet = true;
	}
}

void Object::animate() {
	if (SDL_GetTicks() - stateAnimations[currentStateAnimation].startTicks >= stateAnimations[currentStateAnimation].delay / FPSTimerMod) {
		stateAnimations[currentStateAnimation].startTicks = SDL_GetTicks();
		if (stateAnimations[currentStateAnimation].spriteIndex < (int)stateAnimations[currentStateAnimation].spritesSRect.size() - 1) {
			++stateAnimations[currentStateAnimation].spriteIndex;
		}
		else {
			if (stateAnimations[currentStateAnimation].totalLoops == -1 || stateAnimations[currentStateAnimation].totalLoops > 0 && stateAnimations[currentStateAnimation].currentLoops < stateAnimations[currentStateAnimation].totalLoops - 1) {
				stateAnimations[currentStateAnimation].spriteIndex = 0;
				if (stateAnimations[currentStateAnimation].totalLoops > 0 && stateAnimations[currentStateAnimation].currentLoops < stateAnimations[currentStateAnimation].totalLoops - 1) {
					++stateAnimations[currentStateAnimation].currentLoops;
				}
			}
		}
	}
}

void Object::displayOptionsMenu() {
	if (SDLRectWithinCameraView(objectDRect) == true && displayOptions == true) {
		/*setSDLRenderTarget(NULL);
		setSDLLogicalSize(textLogicalSize);*/

		vector<iconStruct> optionsIcons;
		vector<vector<string>> optionsTextBlock;
		for (int optionsCnt = 0; optionsCnt < (int)options.size(); ++optionsCnt) {
			optionsIcons.push_back(options[optionsCnt].icon);
			optionsTextBlock.push_back({ options[optionsCnt].icon.caption });
		}

		//Check if input device menu to enter code is opened
		bool inputDeviceMenuOpened = false;
		for (int inputDevicesCnt = 0; inputDevicesCnt < (int)inputDevices.size(); ++inputDevicesCnt) {
			if (inputDevices[inputDevicesCnt].inputCode == true) {
				inputDeviceMenuOpened = true;
				break;
			}
		}

		bool blockCursorMovement = false;
		if (displayInputDeviceSelectionMenu == true || inputDeviceMenuOpened == true) {
			blockCursorMovement = true;
		}

		string optionsMenuVarsName = "object " + str(ID);

		XYStruct optionsTextPosition = convertPosition({ objectDRect.x - camera.area.x, objectDRect.y - camera.area.y }, cameraLogicalSize, textLogicalSize);

		WHStruct iconSize = { tileSize.w * 2, tileSize.h * 2 };

		vector<menuControlsStruct> controls = {
			{ "A", "Select" },
			{ "B", "Back" },
			{ "X", "Input Device" }
		};

		//Display options
		displayMenu(optionsMenuVarsName, menuVarsStruct::styleEnum::list, optionsTextPosition, type, true, optionsIcons, optionsTextBlock, { 10, 5 }, iconSize, 5, defaultFont, defaultColour, selectedIconSprite, 0, blockCursorMovement, 75, false, false, false, controls);

		currentOption = menuVars[getMenuVarsIndex(optionsMenuVarsName)].scrollCursor;

		vector<iconStruct> icons;
		vector<string> text;

		//Get required input devices code entered status
		text.push_back("-INPUT CODES-");
		for (int inputDeviceRequirementsCnt = 0; inputDeviceRequirementsCnt < (int)options[currentOption].inputDeviceRequirements.size(); ++inputDeviceRequirementsCnt) {
			if (options[currentOption].inputDeviceRequirements[inputDeviceRequirementsCnt].codeFound == true) {
				string codeEntered = "";
				if (options[currentOption].inputDeviceRequirements[inputDeviceRequirementsCnt].codeEntered == true) {
					codeEntered = "Code Entered";
				}
				text.push_back(formatStr("{} [{}] {}", { options[currentOption].inputDeviceRequirements[inputDeviceRequirementsCnt].name, options[currentOption].inputDeviceRequirements[inputDeviceRequirementsCnt].code, codeEntered }));
			}
			else {
				text.push_back(options[currentOption].inputDeviceRequirements[inputDeviceRequirementsCnt].name + " - Code not found");
			}
		}

		//Enter required skills title
		icons.push_back({  });
		text.push_back("-REQUIRED SKILLS-");

		//Get character matching skills
		int characterCnt = getCharacterCnt(characterID);
		for (int requiredSkillsCnt = 0; requiredSkillsCnt < (int)options[currentOption].requiredSkills.size(); ++requiredSkillsCnt) {
			bool skillFound = false;
			for (int characterSkillsCnt = 0; characterSkillsCnt < (int)characters[characterCnt].skills.size(); ++characterSkillsCnt) {
				if (characters[characterCnt].skills[characterSkillsCnt].name == options[currentOption].requiredSkills[requiredSkillsCnt].name) {
					skillFound = true;
					options[currentOption].characterMatchingSkills.push_back(characters[characterCnt].skills[characterSkillsCnt]);
					break;
				}
			}
			if (skillFound == false) {

				//Insert blank skill
				skillStruct currentSkill;
				options[currentOption].characterMatchingSkills.push_back(currentSkill);

			}
		}

		//Get required skills
		for (int requiredSkillsCnt = 0; requiredSkillsCnt < (int)options[currentOption].requiredSkills.size(); ++requiredSkillsCnt) {
			icons.push_back(options[currentOption].requiredSkills[requiredSkillsCnt].icon);
			text.push_back(formatStr("{} {}/{}", { options[currentOption].requiredSkills[requiredSkillsCnt].name, str(options[currentOption].characterMatchingSkills[requiredSkillsCnt].current + options[currentOption].characterMatchingSkills[requiredSkillsCnt].modified), str(options[currentOption].requiredSkills[requiredSkillsCnt].current) }));
		}

		//Enter required misc items title
		icons.push_back({  });
		text.push_back("-REQUIRED MISC ITEMS-");

		//Get character matching misc items
		for (int requiredMiscItemsCnt = 0; requiredMiscItemsCnt < (int)options[currentOption].requiredMiscItems.size(); ++requiredMiscItemsCnt) {
			bool miscItemFound = false;
			for (int characterMiscItemsCnt = 0; characterMiscItemsCnt < (int)characters[characterCnt].miscItems.size(); ++characterMiscItemsCnt) {
				if (options[currentOption].requiredMiscItems[requiredMiscItemsCnt].name == characters[characterCnt].miscItems[characterMiscItemsCnt].name) {
					miscItemFound = true;
					options[currentOption].characterMatchingMiscItems.push_back(characters[characterCnt].miscItems[characterMiscItemsCnt]);
					break;
				}
			}
			if (miscItemFound == false) {
				miscItemsStruct currentMiscItem;
				options[currentOption].characterMatchingMiscItems.push_back(currentMiscItem);
			}
		}

		//Get required misc items
		for (int requiredMiscItemsCnt = 0; requiredMiscItemsCnt < (int)options[currentOption].requiredMiscItems.size(); ++requiredMiscItemsCnt) {
			icons.push_back(options[currentOption].requiredMiscItems[requiredMiscItemsCnt].icon);
			text.push_back(formatStr("{} x {}/{}", { options[currentOption].requiredMiscItems[requiredMiscItemsCnt].name, str(options[currentOption].characterMatchingMiscItems[requiredMiscItemsCnt].quantity), str(options[currentOption].requiredMiscItems[requiredMiscItemsCnt].quantity) }));
		}

		if (options[currentOption].optionChanges.size() > 0) {

			//Set option changes title
			icons.push_back({  });
			if (options[currentOption].optionChanges.size() == 1) {
				text.push_back("-CHANGE-");
			}
			else {
				text.push_back("-CHANGES-");
			}

			//Get option changes
			if (options[currentOption].optionChanges[currentOptionChange].newOption == true) {
				text.push_back("New option");
			}
			else {
				text.push_back("Update option");
			}
			text.push_back("Option to change index: " + str(options[currentOption].optionChanges[currentOptionChange].optionToChangeIndex));
			text.push_back("Option to change icon caption: " + options[currentOption].optionChanges[currentOptionChange].optionToChangeIconCaption);
			text.push_back("New caption: " + options[currentOption].optionChanges[currentOptionChange].newCaption);
			text.push_back("New required state animation: " + str(options[currentOption].optionChanges[currentOptionChange].newRequiredStateAnimation));
			text.push_back("New required skills: " + str((int)options[currentOption].optionChanges[currentOptionChange].newRequiredSkills.size()));
			text.push_back("New required misc items: " + str((int)options[currentOption].optionChanges[currentOptionChange].newRequiredMiscItems.size()));
			for (int iconsCnt = 0; iconsCnt < 7; ++iconsCnt) {
				icons.push_back({  });
			}

		}

		//Display requirements and changes
		XYStruct requirementsAndChangesTextPosition = { optionsTextPosition.x + getTextSize(getLengthiestStringInTextBlock(optionsTextBlock), defaultFont).w + (iconSize.w * 3), optionsTextPosition.y };
		displayTextBlock(textBlockDisplayStyleEnum::vertical, textBlockAlignmentEnum::left, icons, text, requirementsAndChangesTextPosition, defaultFont, defaultColour, true, 75);

	}
}

int Object::getInputDeviceIndex(string inputDeviceName) {
	for (int inputDevicesCnt = 0; inputDevicesCnt < (int)inputDevices.size(); ++inputDevicesCnt) {
		if (inputDevices[inputDevicesCnt].name == inputDeviceName) {
			return inputDevicesCnt;
		}
	}
	return -1;
}

//for testing
void Object::initObjectOptions() {
	if (objectOptionsInitialized == false) {
		objectOptionsInitialized = true;

		vector<objectConstructorVarsStruct::optionStruct> objectOptions = options;

		for (int objectOptionsCnt = 0; objectOptionsCnt < (int)objectOptions.size(); ++objectOptionsCnt) {

			//Insert required skills
			for (int requiredSkillsCnt = 0; requiredSkillsCnt < (int)objectOptions[objectOptionsCnt].requiredSkills.size(); ++requiredSkillsCnt) {

				//If skill already in character skills then update skill stats else add skill
				bool skillFound = false;
				for (int characterSkillsCnt = 0; characterSkillsCnt < (int)characters[controlledCharacterIndex].skills.size(); ++characterSkillsCnt) {
					if (characters[controlledCharacterIndex].skills[characterSkillsCnt].name == objectOptions[objectOptionsCnt].requiredSkills[requiredSkillsCnt].name) {
						skillFound = true;
						characters[controlledCharacterIndex].skills[characterSkillsCnt].current += objectOptions[objectOptionsCnt].requiredSkills[requiredSkillsCnt].current;
						characters[controlledCharacterIndex].skills[characterSkillsCnt].modified += objectOptions[objectOptionsCnt].requiredSkills[requiredSkillsCnt].modified;
						characters[controlledCharacterIndex].skills[characterSkillsCnt].max += objectOptions[objectOptionsCnt].requiredSkills[requiredSkillsCnt].max;
						break;
					}
				}
				if (skillFound == false) {
					characters[controlledCharacterIndex].skills.push_back(objectOptions[objectOptionsCnt].requiredSkills[requiredSkillsCnt]);
				}

			}

			//Insert required misc items
			for (int requiredMiscItemsCnt = 0; requiredMiscItemsCnt < (int)objectOptions[objectOptionsCnt].requiredMiscItems.size(); ++requiredMiscItemsCnt) {

				//If misc item already in character inventory then update quantity else add misc item
				bool miscItemFound = false;
				for (int characterMiscItemsCnt = 0; characterMiscItemsCnt < (int)characters[controlledCharacterIndex].miscItems.size(); ++characterMiscItemsCnt) {
					vector<objectConstructorVarsStruct::optionStruct> objectOptions = options;

					if (characters[controlledCharacterIndex].miscItems[characterMiscItemsCnt].name == objectOptions[objectOptionsCnt].requiredMiscItems[requiredMiscItemsCnt].name) {
						miscItemFound = true;
						characters[controlledCharacterIndex].miscItems[characterMiscItemsCnt].quantity += objectOptions[objectOptionsCnt].requiredMiscItems[requiredMiscItemsCnt].quantity;
						break;
					}
				}
				if (miscItemFound == false) {
					characters[controlledCharacterIndex].miscItems.push_back(objectOptions[objectOptionsCnt].requiredMiscItems[requiredMiscItemsCnt]);
				}

			}

		}
	}
}

void Object::interact() {
	if (displayOptions == true) {
		initObjectOptions(); //for testing

		//Check if any code is currently being inputted
		bool codeBeingInputted = false;
		for (int inputDevicesCnt = 0; inputDevicesCnt < (int)inputDevices.size(); ++inputDevicesCnt) {
			if (inputDevices[inputDevicesCnt].inputCode == true) {
				codeBeingInputted = true;
				break;
			}
		}

		//Check if any input device code is required and has not been entered yet
		for (int inputDeviceRequirementsCnt = 0; inputDeviceRequirementsCnt < (int)options[currentOption].inputDeviceRequirements.size(); ++inputDeviceRequirementsCnt) {
			int inputDeviceIndex = getInputDeviceIndex(options[currentOption].inputDeviceRequirements[inputDeviceRequirementsCnt].name);
			if (controllerButtons.X == true && displayInputDeviceSelectionMenu == false && codeBeingInputted == false && options[currentOption].inputDeviceRequirements[inputDeviceRequirementsCnt].code != "" && options[currentOption].inputDeviceRequirements[inputDeviceRequirementsCnt].codeEntered == false) {
				controllerButtons.X = false;
				displayInputDeviceSelectionMenu = true;
				return;
			}
		}

		if (controllerButtons.A == true && displayInputDeviceSelectionMenu == false && codeBeingInputted == false) {
			controllerButtons.A = false;

			//Check character passes code requirements
			bool allCodeRequirementsPassed = true;
			for (int inputDeviceRequirementsCnt = 0; inputDeviceRequirementsCnt < (int)options[currentOption].inputDeviceRequirements.size(); ++inputDeviceRequirementsCnt) {
				if (options[currentOption].inputDeviceRequirements[inputDeviceRequirementsCnt].code != "" && options[currentOption].inputDeviceRequirements[inputDeviceRequirementsCnt].codeEntered == false) {
					allCodeRequirementsPassed = false;
					break;
				}
			}

			//Check character passes skill requirements
			bool allSkillRequirementsPassed = true;
			for (int requiredSkillsCnt = 0; requiredSkillsCnt < (int)options[currentOption].requiredSkills.size(); ++requiredSkillsCnt) {
				if (options[currentOption].characterMatchingSkills[requiredSkillsCnt].current + options[currentOption].characterMatchingSkills[requiredSkillsCnt].modified < options[currentOption].requiredSkills[requiredSkillsCnt].current) {
					allSkillRequirementsPassed = false;
					break;
				}
			}

			//Check character passes misc item requirements
			bool allMiscItemsRequirementsPassed = true;
			for (int requiredMiscItemsCnt = 0; requiredMiscItemsCnt < (int)options[currentOption].requiredMiscItems.size(); ++requiredMiscItemsCnt) {
				if (options[currentOption].characterMatchingMiscItems[requiredMiscItemsCnt].name == "" || options[currentOption].characterMatchingMiscItems[requiredMiscItemsCnt].quantity < options[currentOption].requiredMiscItems[requiredMiscItemsCnt].quantity) {
					allMiscItemsRequirementsPassed = false;
					break;
				}
			}

			//If all checks pass then change options and set new values for object variables
			if (allSkillRequirementsPassed == true && allMiscItemsRequirementsPassed == true && allCodeRequirementsPassed == true) {
				currentStateAnimation = options[currentOption].newCurrentStateAnimation;

				//Keep copy of current option in case option changes change that option
				objectConstructorVarsStruct::optionStruct currentOptionCopy = options[currentOption];

				for (int optionChangesCnt = 0; optionChangesCnt < (int)options[currentOption].optionChanges.size(); ++optionChangesCnt) {
					int optionToChangeIndex = -1;
					if (options[currentOption].optionChanges[optionChangesCnt].optionToChangeIndex > -1) {
						optionToChangeIndex = options[currentOption].optionChanges[optionChangesCnt].optionToChangeIndex;
					}
					else {

						//Get index of option matching optionToChangeIconCaption
						for (int optionsCnt = 0; optionsCnt < (int)options.size(); ++optionsCnt) {
							if (options[optionsCnt].icon.caption == options[currentOption].optionChanges[optionChangesCnt].optionToChangeIconCaption && optionsCnt != currentOption) {
								optionToChangeIndex = optionsCnt;
								break;
							}
						}

					}

					//Remove required misc items from character's inventory
					if (options[currentOption].removeMiscItems == true) {
						vector<string> itemsToRemove;
						characters[getCharacterCnt(characterID)].removeMiscItems(options[currentOption].requiredMiscItems);
					}

					//Update options
					if (options[currentOption].optionChanges[optionChangesCnt].newOption == false) {
						if (optionToChangeIndex > -1) {

							//Change option caption
							if (options[currentOption].optionChanges[optionChangesCnt].newCaption != "") {
								options[optionToChangeIndex].icon.caption = options[currentOption].optionChanges[optionChangesCnt].newCaption;
							}

							//Change required state animation
							if (options[currentOption].optionChanges[optionChangesCnt].newRequiredStateAnimation > -1) {
								options[optionToChangeIndex].requiredStateAnimation = options[currentOption].optionChanges[optionChangesCnt].newRequiredStateAnimation;
							}

							//Change required skills
							options[optionToChangeIndex].requiredSkills.clear();
							options[optionToChangeIndex].characterMatchingSkills.clear();
							for (int newRequiredSkillsCnt = 0; newRequiredSkillsCnt < (int)options[currentOption].optionChanges[optionChangesCnt].newRequiredSkills.size(); ++newRequiredSkillsCnt) {
								options[optionToChangeIndex].requiredSkills.push_back(options[currentOption].optionChanges[optionChangesCnt].newRequiredSkills[newRequiredSkillsCnt]);
							}

							//Change required misc items
							options[optionToChangeIndex].requiredMiscItems.clear();
							options[optionToChangeIndex].characterMatchingMiscItems.clear();
							for (int newRequiredMiscItemsCnt = 0; newRequiredMiscItemsCnt < (int)options[currentOption].optionChanges[optionChangesCnt].newRequiredMiscItems.size(); ++newRequiredMiscItemsCnt) {
								options[optionToChangeIndex].requiredMiscItems.push_back(options[currentOption].optionChanges[optionChangesCnt].newRequiredMiscItems[newRequiredMiscItemsCnt]);
							}

						}

					}
					else {

						//Add new option to options
						objectConstructorVarsStruct::optionStruct newOption;
						newOption.icon = options[currentOption].optionChanges[optionChangesCnt].newIcon;
						newOption.icon.caption = options[currentOption].optionChanges[optionChangesCnt].newCaption;
						newOption.requiredStateAnimation = options[currentOption].optionChanges[optionChangesCnt].newRequiredStateAnimation;
						newOption.requiredSkills = options[currentOption].optionChanges[optionChangesCnt].newRequiredSkills;
						newOption.requiredMiscItems = options[currentOption].optionChanges[optionChangesCnt].newRequiredMiscItems;
						options.push_back(newOption);

					}
				}

				collision = options[currentOption].newCollision;

				//Init variables to load into or out of building
				currentlyInsideBuilding = currentOptionCopy.loadInsideBuilding;
				if (currentOptionCopy.loadInsideBuilding == true) {
					int buildingIndex = getBuildingIndexByDoorID(ID);

					areaStruct buildingArea = buildings[buildingIndex].getArea();
					buildingDoorEntryRelativePosition = { ((objectDRect.x - buildingArea.x) * ((buildingArea.x + buildingArea.w) - buildingArea.x)) / 100, 100 };

					loadLevel = true;
					overworldDoorEnteredThroughArea = convertSDLRectToArea(objectDRect);
					overworldBuildingEnteredThroughID = getBuildingIDByIndex(buildingIndex);
				}
				else if (currentOptionCopy.loadOverworld == true) {

					//Reposition characters next to building door entered from
					for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
						characters[charactersCnt].setPosition({ overworldDoorEnteredThroughArea.x, overworldDoorEnteredThroughArea.y + overworldDoorEnteredThroughArea.h });
					}

					//stairsPositions.clear();

					loadLevel = true;
				}

				//Go up or down stairs
				if (currentOptionCopy.goUpStairs == true && overworldGrid.height < overworldGrid.heightStartEnd.end) {
					++overworldGrid.height;
					loadLevel = true;
					usedStairs = true;
				}
				else if (currentOptionCopy.goDownStairs == true && overworldGrid.height > overworldGrid.heightStartEnd.start) {
					--overworldGrid.height;
					loadLevel = true;
					usedStairs = true;
				}

				//Open crafting menu
				if (currentOptionCopy.craftingType != "") {
					displayCraftingMenu = true;
					displayOptions = false;
					characters[controlledCharacterIndex].disableControls = true;
				}

				//Open organisation hierarchy menu
				if (currentOptionCopy.organisationID > -1) {
					setOrganisationDisplayHierarchyBoolToTrueBool = true;
					optionOrganisationID = currentOptionCopy.organisationID;
				}

				//Update character sleep state
				if (currentOptionCopy.canSleep == true) {
					updateCharacterSleepStateBool = true;
				}

			}

		}
	}
}

void Object::inputDeviceSelectionMenu() {
	if (displayInputDeviceSelectionMenu == true) {

		//Get input devices
		string menuVarsName = "input device selection";
		vector<string> inputDevicesListText;
		vector<iconStruct> inputDevicesListIcons;
		vector<vector<string>> inputDevicesIconTextBlock;
		for (int inputDevicesCnt = 0; inputDevicesCnt < (int)inputDevices.size(); ++inputDevicesCnt) {
			inputDevicesListText.push_back(inputDevices[inputDevicesCnt].name);
			inputDevicesListIcons.push_back(blankIcon);
			inputDevicesIconTextBlock.push_back({ inputDevices[inputDevicesCnt].name });
		}

		//Set controls
		vector<menuControlsStruct> controls = {
			{ "A", "Select" },
			{ "B", "Back" }
		};

		//Display input devices list
		displayMenu(menuVarsName, menuVarsStruct::styleEnum::list, getCenteredTextPosition(getLengthiestStringInList(inputDevicesListText), defaultFont, textLogicalSize), "-INPUT DEVICES-", true, inputDevicesListIcons, inputDevicesIconTextBlock, { 10, 5 }, { tileSize.w * 4, tileSize.h * 4 }, (int)inputDevices.size(), defaultFont, defaultColour, selectedIconSprite, 0, false, 75, false, false, false, controls);
		selectedInputDevice = menuVars[getMenuVarsIndex(menuVarsName)].scrollCursor;

		//Exit list selection
		if (controllerButtons.B == true) {
			controllerButtons.B = false;
			displayInputDeviceSelectionMenu = false;
		}

		//Select input device if code not already entered
		if (controllerButtons.A == true && options[currentOption].inputDeviceRequirements[getInputDeviceIndex(inputDevices[selectedInputDevice].name)].codeEntered == false) {
			controllerButtons.A = false;
			inputDevices[selectedInputDevice].inputCode = true;
			displayInputDeviceSelectionMenu = false;
			inputDevices[selectedInputDevice].codeEntered = "";
		}

	}
}

int Object::getInputDeviceRequirementIndex(string inputDeviceName) {
	for (int inputDeviceRequirementsCnt = 0; inputDeviceRequirementsCnt < (int)options[currentOption].inputDeviceRequirements.size(); ++inputDeviceRequirementsCnt) {
		if (options[currentOption].inputDeviceRequirements[inputDeviceRequirementsCnt].name == inputDeviceName) {
			return inputDeviceRequirementsCnt;
		}
	}
	return -1;
}

void Object::checkCorrectCodeEntered(int inputDeviceRequirementIndex) {
	if (inputDevices[selectedInputDevice].codeEntered == options[currentOption].inputDeviceRequirements[inputDeviceRequirementIndex].code) {
		options[currentOption].inputDeviceRequirements[inputDeviceRequirementIndex].codeEntered = true;
		inputDevices[selectedInputDevice].inputCode = false;

		//If there are more codes to enter than return to input device selection menu
		for (int inputDeviceRequirementsCnt = 0; inputDeviceRequirementsCnt < (int)options[currentOption].inputDeviceRequirements.size(); ++inputDeviceRequirementsCnt) {
			if (options[currentOption].inputDeviceRequirements[inputDeviceRequirementsCnt].codeEntered == false) {
				displayInputDeviceSelectionMenu = true;
				return;
			}
		}

	}
}

void Object::inputDeviceMenu() {
	if (selectedInputDevice > -1 && inputDevices[selectedInputDevice].inputCode == true) {

		//Get input device icons
		vector<iconStruct> inputDeviceIcons;
		for (int inputDeviceGridYCnt = 0; inputDeviceGridYCnt < (int)inputDevices[selectedInputDevice].grid.size(); ++inputDeviceGridYCnt) {
			for (int inputDeviceGridXCnt = 0; inputDeviceGridXCnt < (int)inputDevices[selectedInputDevice].grid[0].size(); ++inputDeviceGridXCnt) {
				inputDeviceIcons.push_back(inputDevices[selectedInputDevice].grid[inputDeviceGridYCnt][inputDeviceGridXCnt]);
			}
		}

		string menuVarsName = "input device menu - " + inputDevices[selectedInputDevice].name;
		int inputDeviceRequirementIndex = getInputDeviceRequirementIndex(inputDevices[selectedInputDevice].name);

		//Get code entered
		string title = inputDevices[selectedInputDevice].codeEntered;
		for (int dashesCnt = 0; dashesCnt < (int)options[currentOption].inputDeviceRequirements[inputDeviceRequirementIndex].code.length() - (int)inputDevices[selectedInputDevice].codeEntered.length(); ++dashesCnt) {
			title += "-";
		}

		displayMenu(menuVarsName, menuVarsStruct::styleEnum::icons, getCenteredTextPosition(inputDevices[selectedInputDevice].name, defaultFont, textLogicalSize), title, true, inputDeviceIcons, {  }, { (int)inputDevices[selectedInputDevice].grid[0].size(), (int)inputDevices[selectedInputDevice].grid.size() }, { tileSize.w * 4, tileSize.h * 4 }, (int)inputDeviceIcons.size(), defaultFont, defaultColour, selectedIconSprite, 0, false, 75, true, false, false, {  });

		XYStruct gridCursor = menuVars[getMenuVarsIndex(menuVarsName)].gridCursor;
		string selectedKey = inputDevices[selectedInputDevice].grid[gridCursor.y][gridCursor.x].caption;

		//Enter selected key
		if (controllerButtons.A == true) {
			if (getStringIndex({ "SP", "EN", "BK", "DL" }, selectedKey) == -1 && (int)inputDevices[selectedInputDevice].codeEntered.length() < (int)options[currentOption].inputDeviceRequirements[inputDeviceRequirementIndex].code.length()) {
				controllerButtons.A = false;

				//Add selected key
				inputDevices[selectedInputDevice].codeEntered += selectedKey;
				checkCorrectCodeEntered(inputDeviceRequirementIndex);

			}
			else if (selectedKey == "BK") {
				controllerButtons.A = false;

				//Remove last character
				inputDevices[selectedInputDevice].codeEntered = inputDevices[selectedInputDevice].codeEntered.substr(0, (int)inputDevices[selectedInputDevice].codeEntered.length() - 1);

			}
			else if (selectedKey == "DL") {
				controllerButtons.A = false;

				//Remove all characters
				inputDevices[selectedInputDevice].codeEntered = "";

			}
			else if (selectedKey == "SP") {
				controllerButtons.A = false;

				//Enter space character
				inputDevices[selectedInputDevice].codeEntered += " ";

			}
			else if (selectedKey == "EN") {
				controllerButtons.A = false;
				checkCorrectCodeEntered(inputDeviceRequirementIndex);
			}
		}

		//Remove last character
		if (controllerButtons.X == true) {
			controllerButtons.X = false;
			inputDevices[selectedInputDevice].codeEntered = inputDevices[selectedInputDevice].codeEntered.substr(0, (int)inputDevices[selectedInputDevice].codeEntered.length() - 1);
		}

		//Remove all characters
		if (controllerButtons.Y == true) {
			controllerButtons.Y = false;
			inputDevices[selectedInputDevice].codeEntered = "";
		}

		//Exit menu
		if (controllerButtons.B == true) {
			controllerButtons.B = false;
			inputDevices[selectedInputDevice].inputCode = false;
			displayInputDeviceSelectionMenu = true;
		}

		//For testing - remove ;;
		inputDevices[selectedInputDevice].codeEntered = options[currentOption].inputDeviceRequirements[inputDeviceRequirementIndex].code;
		options[currentOption].inputDeviceRequirements[inputDeviceRequirementIndex].codeEntered = true;

	}
}

//for testing
void Object::initCraftingItemsSelected(vector<craftingItemDataStruct>& craftingTable, vector<miscItemsStruct>& characterCraftingItems) {
	if (craftingItemsSelectedInitialized == false) {
		craftingItemsSelectedInitialized = true;

		//Randomly select an item from the crafting table and pre-select all of the crafting items needed
		int craftingTableItemIndex = randInt(0, (int)craftingTable.size() - 1);
		for (int craftingTableRequiredItemsCnt = 0; craftingTableRequiredItemsCnt < (int)craftingTable[craftingTableItemIndex].requiredItems.size(); ++craftingTableRequiredItemsCnt) {
			selectedCraftingItemsStruct currentCraftingItemSelected;

			//Get index
			for (int characterCraftingItemsCnt = 0; characterCraftingItemsCnt < (int)characterCraftingItems.size(); ++characterCraftingItemsCnt) {
				if (characterCraftingItems[characterCraftingItemsCnt].name == craftingTable[craftingTableItemIndex].requiredItems[craftingTableRequiredItemsCnt].name) {
					currentCraftingItemSelected.index = characterCraftingItemsCnt;
					break;
				}
			}

			currentCraftingItemSelected.quantity = craftingTable[craftingTableItemIndex].requiredItems[craftingTableRequiredItemsCnt].quantityRequired;

			craftingItemsSelected.push_back(currentCraftingItemSelected);
		}

	}
}

void Object::craftingMenu(vector<craftingItemDataStruct>& craftingTable, Character& teamCharacter, craftingItemDataStruct::resultingItemStruct& craftingTableCraftedItem) {
	if (displayCraftingMenu == true) {
		initCraftingItemsSelected(craftingTable, teamCharacter.craftingItems); //for testing

		setSDLLogicalSize(textLogicalSize);
		setSDLRenderTarget(NULL);

		//Display header menu
		string craftingMenuHeaderMenuVarsName = "crafting menu header";
		const vector<iconStruct> craftingMenuHeaders = {
			{ blankIcon.spriteSheetIndex, blankIcon.spriteSheetArea, "Experiment" },
			{ blankIcon.spriteSheetIndex, blankIcon.spriteSheetArea, "Blueprints" }
		};
		bool blockCursorMovement = false;
		if (selectQuantityMenu.display == true) {
			blockCursorMovement = true;
		}
		displayHeaderMenu(craftingMenuHeaderMenuVarsName, headerStyleEnum::text, { 10, 10 }, craftingMenuHeaders, (int)craftingMenuHeaders.size(), tileSize, defaultFont, defaultColour, selectedHeaderSprite, 0, blockCursorMovement, 75);
		int selectedMenuVars = headerMenuVars[getHeaderMenuVarsIndex(craftingMenuHeaderMenuVarsName)].selected;

		if (selectedMenuVars > -1 && selectedMenuVars < (int)craftingMenuHeaders.size()) {

			//Define left hand menu
			string leftHandMenuVarsName = "";
			vector<iconStruct> leftHandMenuIcons;
			vector<vector<string>> leftHandMenuIconTextBlock;
			vector<menuControlsStruct> leftHandMenuControls;
			if (craftingMenuHeaders[selectedMenuVars].caption == "Experiment") {
				leftHandMenuVarsName = "crafting menu experiment left";

				//Insert misc items in left hand menu variables
				for (int craftingItemsCnt = 0; craftingItemsCnt < (int)teamCharacter.craftingItems.size(); ++craftingItemsCnt) {
					int quantity = teamCharacter.craftingItems[craftingItemsCnt].quantity;

					//Check if item has been selected in crafting items selected list and if so subtract amount selected from currently selected craftng item quantity to be displayed
					for (int craftingItemsSelectedCnt = 0; craftingItemsSelectedCnt < (int)craftingItemsSelected.size(); ++craftingItemsSelectedCnt) {
						if (craftingItemsSelected[craftingItemsSelectedCnt].index == craftingItemsCnt) {
							quantity -= craftingItemsSelected[craftingItemsSelectedCnt].quantity;
						}
					}

					teamCharacter.craftingItems[craftingItemsCnt].icon.caption = "x" + str(quantity);
					leftHandMenuIcons.push_back(teamCharacter.craftingItems[craftingItemsCnt].icon);
					leftHandMenuIconTextBlock.push_back({
						teamCharacter.craftingItems[craftingItemsCnt].name,
						teamCharacter.craftingItems[craftingItemsCnt].description,
						"x" + str(quantity)
						});
				}

			}
			else if (craftingMenuHeaders[selectedMenuVars].caption == "Blueprints") {
				leftHandMenuVarsName = "crafting menu blueprint left";

				//Insert blueprints in left hand menu variables
				vector<blueprintStruct> characterBlueprints = teamCharacter.getBlueprints();
				for (int blueprintsCnt = 0; blueprintsCnt < (int)characterBlueprints.size(); ++blueprintsCnt) {
					leftHandMenuIcons.push_back(characterBlueprints[blueprintsCnt].blueprint.icon);

					leftHandMenuIconTextBlock.push_back({
						characterBlueprints[blueprintsCnt].blueprint.name,
						characterBlueprints[blueprintsCnt].blueprint.description,
						str(characterBlueprints[blueprintsCnt].blueprint.quantity)
						});
				}

			}

			bool blockCursorMovement = true;
			if (selectedCraftingMenuSection == Object::selectedCraftingMenuSectionEnum::craftingItems && selectQuantityMenu.display == false) {
				blockCursorMovement = false;
				leftHandMenuControls = {
					{ "A", "Select Item" },
					{ "B", "Exit Crafting Menu" },
					{ "Y", "Craft" },
					{ "LT", "Crafting Items" },
					{ "RT", "Selected Crafting Items" }
				};
			}

			displayMenu(leftHandMenuVarsName, menuVarsStruct::styleEnum::icons, { 10, textLogicalSize.h / 6 }, "", true, leftHandMenuIcons, leftHandMenuIconTextBlock, { 10, 5 }, { tileSize.w * 10, tileSize.h * 10 }, (int)leftHandMenuIcons.size(), defaultFont, defaultColour, selectedIconSprite, 0, blockCursorMovement, 75, true, true, true, leftHandMenuControls);
			int leftSelectedCraftingItemIndex = menuVars[getMenuVarsIndex(leftHandMenuVarsName)].scrollCursor;

			//Define right hand menu
			string rightHandMenuVarsName;
			vector<iconStruct> rightHandMenuIcons;
			vector<vector<string>> rightHandMenuIconTextBlock;
			vector<menuControlsStruct> rightHandMenuControls;
			if (craftingMenuHeaders[selectedMenuVars].caption == "Experiment") {
				rightHandMenuVarsName = "crafting menu experiment right";

				//Insert selected crafting items in right hand menu
				for (int craftingItemsSelectedCnt = 0; craftingItemsSelectedCnt < (int)craftingItemsSelected.size(); ++craftingItemsSelectedCnt) {
					teamCharacter.craftingItems[craftingItemsSelected[craftingItemsSelectedCnt].index].icon.caption = str(craftingItemsSelected[craftingItemsSelectedCnt].quantity);
					rightHandMenuIcons.push_back(teamCharacter.craftingItems[craftingItemsSelected[craftingItemsSelectedCnt].index].icon);

					rightHandMenuIconTextBlock.push_back({
						teamCharacter.craftingItems[craftingItemsSelected[craftingItemsSelectedCnt].index].name,
						str(craftingItemsSelected[craftingItemsSelectedCnt].quantity),
						teamCharacter.craftingItems[craftingItemsSelected[craftingItemsSelectedCnt].index].description
					});
				}

			}
			else if (craftingMenuHeaders[selectedMenuVars].caption == "Blueprints") {
				rightHandMenuVarsName = "crafting menu blueprint right";

				//Insert crafting items for blueprint in right hand menu
				vector<blueprintStruct> characterBlueprints = teamCharacter.getBlueprints();
				for (int requiredMiscItemsCnt = 0; requiredMiscItemsCnt < (int)characterBlueprints[leftSelectedCraftingItemIndex].requiredMiscItems.size(); ++requiredMiscItemsCnt) {

					rightHandMenuIcons.push_back(characterBlueprints[leftSelectedCraftingItemIndex].requiredMiscItems[requiredMiscItemsCnt].icon);

					//Get matching item quantity
					int craftingItemsCnt = -1;
					for (craftingItemsCnt = 0; craftingItemsCnt < (int)teamCharacter.craftingItems.size(); ++craftingItemsCnt) {
						if (teamCharacter.craftingItems[craftingItemsCnt].name == characterBlueprints[leftSelectedCraftingItemIndex].requiredMiscItems[requiredMiscItemsCnt].name) {
							break;
						}
					}

					rightHandMenuIconTextBlock.push_back({
						characterBlueprints[leftSelectedCraftingItemIndex].requiredMiscItems[requiredMiscItemsCnt].name,
						characterBlueprints[leftSelectedCraftingItemIndex].requiredMiscItems[requiredMiscItemsCnt].description,
						str(characterBlueprints[leftSelectedCraftingItemIndex].requiredMiscItems[requiredMiscItemsCnt].quantity) + "/" + str(teamCharacter.craftingItems[craftingItemsCnt].quantity)
						});
				}

			}

			blockCursorMovement = true;
			if (selectedCraftingMenuSection == Object::selectedCraftingMenuSectionEnum::selectedCraftingItems && selectQuantityMenu.display == false) {
				blockCursorMovement = false;
				rightHandMenuControls = {
					{ "A", "Unselect Specific Quantity" },
					{ "B", "Exit Crafting Menu" },
					{ "X", "Unselect All Quantity" },
					{ "Y", "Craft" },
					{ "RB", "Unselect All" },
					{ "LT", "Crafting Items" },
					{ "RT", "Selected Crafting Items" }
				};
			}

			displayMenu(rightHandMenuVarsName, menuVarsStruct::styleEnum::icons, { textLogicalSize.w / 2, 10 }, "SELECTED ITEMS", true, rightHandMenuIcons, rightHandMenuIconTextBlock, { 3, 1 }, { tileSize.w * 10, tileSize.h * 10 }, (int)rightHandMenuIcons.size(), defaultFont, defaultColour, selectedIconSprite, 0, blockCursorMovement, 75, true, true, true, rightHandMenuControls);
			int rightSelectedCraftingItemIndex = -1;
			if (getMenuVarsIndex(rightHandMenuVarsName) > -1) {
				rightSelectedCraftingItemIndex = menuVars[getMenuVarsIndex(rightHandMenuVarsName)].scrollCursor;
			};

			selectQuantity(selectQuantityMenu.textPosition, selectQuantityMenu.display, selectQuantityMenu.caption, selectQuantityMenu.selected, selectQuantityMenu.min, selectQuantityMenu.max, selectQuantityMenu.scrollDelay, selectQuantityMenu.blockCursorMovement, selectQuantityMenu.centreText, selectQuantityMenu.showControlCaptions);

			//Get crafting table matching line for crafting items selected
			if (matchingCraftingTableLineIndex == -1) {
				for (int craftingTableListCnt = 0; craftingTableListCnt < (int)craftingTable.size(); ++craftingTableListCnt) {
					bool allCraftingItemsPresent = true;

					for (int craftingTableItemsCnt = 0; craftingTableItemsCnt < (int)craftingTable[craftingTableListCnt].requiredItems.size(); ++craftingTableItemsCnt) {
						bool craftingItemSelectedPassesCheck = false;

						for (int craftingItemsSelectedCnt = 0; craftingItemsSelectedCnt < (int)craftingItemsSelected.size(); ++craftingItemsSelectedCnt) {

							for (int craftingTableRequiredItemsCnt = 0; craftingTableRequiredItemsCnt < (int)craftingTable[craftingTableListCnt].requiredItems.size(); ++craftingTableRequiredItemsCnt) {

								if (teamCharacter.craftingItems[craftingItemsSelected[craftingItemsSelectedCnt].index].name == craftingTable[craftingTableListCnt].requiredItems[craftingTableRequiredItemsCnt].name && craftingItemsSelected[craftingItemsSelectedCnt].quantity >= craftingTable[craftingTableListCnt].requiredItems[craftingTableRequiredItemsCnt].quantityRequired) {
									craftingItemSelectedPassesCheck = true;
									break;
								}

							}

						}

						if (craftingItemSelectedPassesCheck == false) {
							allCraftingItemsPresent = false;
							break;
						}
					}

					if (allCraftingItemsPresent == true) {
						matchingCraftingTableLineIndex = craftingTableListCnt;
						break;
					}
				}
			}

			WHStruct textSize = getTextSize("0", defaultFont);
			XYStruct position = { textLogicalSize.w / 2, textLogicalSize.h / 2 };

			//Display blueprint
			if (matchingCraftingTableLineIndex > -1 && craftingTable[matchingCraftingTableLineIndex].blueprintFound == true && craftingMenuHeaders[selectedMenuVars].caption == "Experiment") {
				renderText("BLUEPRINT", defaultFont, defaultColour, position);
				position.y += getTextSize("BLUEPRINT", defaultFont).h * 2;

				sRect = convertAreaToSDLRect(craftingTable[matchingCraftingTableLineIndex].blueprint.blueprint.icon.spriteSheetArea);
				dRect = { position.x, position.y, tileSize.w * 10, tileSize.h * 10 };
				SDL_RenderCopy(renderer, spriteSheets[craftingTable[matchingCraftingTableLineIndex].blueprint.blueprint.icon.spriteSheetIndex].texture, &sRect, &dRect);
				position.y += dRect.h + (textSize.h * 2);

				renderText(craftingTable[matchingCraftingTableLineIndex].blueprint.blueprint.name, defaultFont, defaultColour, position);
				position.y += textSize.h * 4;
			}

			//Display resulting item
			if (craftingTableCraftedItem.type != "") {
				iconStruct icon;
				vector<string> textBlockText;
				textBlockText.push_back(craftingTableCraftedItem.type);

				//Get icon and text block text
				if (craftingTableCraftedItem.type == "Misc") {
					icon = craftingTableCraftedItem.miscItem.icon;
					textBlockText.push_back(craftingTableCraftedItem.miscItem.name);
					textBlockText.push_back(craftingTableCraftedItem.miscItem.description);
					textBlockText.push_back("Quantity: " + str(craftingTableCraftedItem.miscItem.quantity));
				}
				else if (craftingTableCraftedItem.type == "Crafting") {
					icon = craftingTableCraftedItem.craftingItem.icon;
					textBlockText.push_back(craftingTableCraftedItem.craftingItem.name);
					textBlockText.push_back(craftingTableCraftedItem.craftingItem.description);
					textBlockText.push_back("Quantity: " + str(craftingTableCraftedItem.craftingItem.quantity));
				}
				else if (craftingTableCraftedItem.type == "Cyberware") {
					icon = craftingTableCraftedItem.cyberware.icon;
					textBlockText.push_back(craftingTableCraftedItem.cyberware.name);
					textBlockText.push_back(craftingTableCraftedItem.cyberware.description);
					textBlockText.push_back("Quantity: " + str(craftingTableCraftedItem.cyberware.quantity));
					textBlockText.push_back("Energy consumption per second: " + str(craftingTableCraftedItem.cyberware.energyConsumptionPerSecond));

					//Display abilities
					//;;textBlockText.push_back(craftingTableCraftedItem.cyberware.abilities[);

				}
				else if (craftingTableCraftedItem.type == "Gear") {
					icon = craftingTableCraftedItem.gear.icon;
					textBlockText.push_back(craftingTableCraftedItem.gear.name);
					textBlockText.push_back(craftingTableCraftedItem.gear.description);
					textBlockText.push_back("Quantity: " + str(craftingTableCraftedItem.gear.quantity));

					//Display skills
					//;;textBlockText.push_back(craftingTableCraftedItem.gear.skills[);

				}
				if (craftingTableCraftedItem.type == "Weapon") {
					icon = craftingTableCraftedItem.weapon.icon;
					textBlockText.push_back(craftingTableCraftedItem.weapon.name);
					textBlockText.push_back(craftingTableCraftedItem.weapon.description);
					textBlockText.push_back("Quantity: " + str(craftingTableCraftedItem.weapon.quantity));
					textBlockText.push_back("Range type: " + craftingTableCraftedItem.weapon.rangeType);

					//Display abilities
					//;;textBlockText.push_back(craftingTableCraftedItem.weapon.abilities[);

				}
				if (craftingTableCraftedItem.type == "Consumable") {
					icon = craftingTableCraftedItem.consumableItem.icon;
					textBlockText.push_back(craftingTableCraftedItem.consumableItem.name);
					textBlockText.push_back(craftingTableCraftedItem.consumableItem.description);
					textBlockText.push_back("Quantity: " + str(craftingTableCraftedItem.consumableItem.quantity));

					//Display status effects
					//;;textBlockText.push_back(craftingTableCraftedItem.consumableItem.statusEffects[);

				}
				if (craftingTableCraftedItem.type == "Ammo") {
					icon = craftingTableCraftedItem.ammo.icon;
					textBlockText.push_back(craftingTableCraftedItem.ammo.name);
					textBlockText.push_back("Quantity: " + str(craftingTableCraftedItem.ammo.quantity));
				}

				vector<iconStruct> textBlockIcons;
				for (int textBlockTextCnt = 0; textBlockTextCnt < (int)textBlockText.size(); ++textBlockTextCnt) {
					textBlockIcons.push_back(blankIcon);
				}

				renderText("CRAFTED", defaultFont, defaultColour, position);
				position.y += textSize.h * 2;

				//Display resulting item icon
				sRect = convertAreaToSDLRect(icon.spriteSheetArea);
				dRect = { position.x, position.y, tileSize.w * 10, tileSize.h * 10 };
				SDL_RenderCopy(renderer, spriteSheets[icon.spriteSheetIndex].texture, &sRect, &dRect);
				position.y += dRect.h + (textSize.h * 2);

				//Display resulting item stats
				displayTextBlock(textBlockDisplayStyleEnum::vertical, textBlockAlignmentEnum::left, textBlockIcons, textBlockText, position, defaultFont, defaultColour, true, 75);

			}

			//Switch menu section
			if (selectQuantityMenu.display == false) {
				if (leftTrigger.activated == true) {
					leftTrigger.activated = false;
					selectedCraftingMenuSection = Object::selectedCraftingMenuSectionEnum::craftingItems;
				}
				if (rightTrigger.activated == true) {
					rightTrigger.activated = false;
					selectedCraftingMenuSection = Object::selectedCraftingMenuSectionEnum::selectedCraftingItems;
				}
			}

			//Switch to left menu section if right section is empty
			if ((int)craftingItemsSelected.size() == 0) {
				selectedCraftingMenuSection = Object::selectedCraftingMenuSectionEnum::craftingItems;
			}

			//Select quantity
			if (controllerButtons.A == true && selectedCraftingMenuSection == Object::selectedCraftingMenuSectionEnum::craftingItems && leftSelectedCraftingItemIndex >= 0 && leftSelectedCraftingItemIndex <= (int)teamCharacter.craftingItems.size() - 1) {
				if (selectQuantityMenu.display == false) {
					controllerButtons.A = false;

					//Init select quantity
					selectQuantityMenu.centreText = true;
					selectQuantityMenu.display = true;
					selectQuantityMenu.caption = "Select crafting item quantity";
					selectQuantityMenu.selected = 1;
					selectQuantityMenu.min = 1;
					selectQuantityMenu.max = teamCharacter.craftingItems[leftSelectedCraftingItemIndex].quantity;
					//Max quantity selectable cannot exceed max quantity in character inventory
					for (int craftingItemsSelectedCnt = 0; craftingItemsSelectedCnt < (int)craftingItemsSelected.size(); ++craftingItemsSelectedCnt) {
						if (craftingItemsSelected[craftingItemsSelectedCnt].index == leftSelectedCraftingItemIndex) {
							selectQuantityMenu.max -= craftingItemsSelected[craftingItemsSelectedCnt].quantity;
						}
					}
					if (selectQuantityMenu.max == 0) {
						selectQuantityMenu.display = false;
					}

				}
				else {
					controllerButtons.A = false;
					selectQuantityMenu.display = false;

					//Add selected crafting item to crafting items selected: check if item already added to crafting items selected. If not check there is space left in crafting items selected list
					int matchingItemIndex = -1;
					for (int craftingItemsSelectedCnt = 0; craftingItemsSelectedCnt < (int)craftingItemsSelected.size(); ++craftingItemsSelectedCnt) {
						if (craftingItemsSelected[craftingItemsSelectedCnt].index == leftSelectedCraftingItemIndex) {
							matchingItemIndex = craftingItemsSelectedCnt;
							break;
						}
					}
					if (matchingItemIndex > -1) {

						//Update matching crafting items selected quantity
						craftingItemsSelected[matchingItemIndex].quantity += selectQuantityMenu.selected;

					}
					else {

						//Check if enough space in crafting items selected list
						if ((int)craftingItemsSelected.size() < 3) {

							//Add selected item to list
							selectedCraftingItemsStruct currentCraftingItemsSelected;
							currentCraftingItemsSelected.index = leftSelectedCraftingItemIndex;
							currentCraftingItemsSelected.quantity = selectQuantityMenu.selected;
							craftingItemsSelected.push_back(currentCraftingItemsSelected);

						}

					}

					matchingCraftingTableLineIndex = -1;
					craftingTableCraftedItem.type = "";
				}
			}

			if (selectedCraftingMenuSection == Object::selectedCraftingMenuSectionEnum::selectedCraftingItems && rightSelectedCraftingItemIndex > -1) {

				//Unselect specific quantity
				if (controllerButtons.A == true) {
					if (selectQuantityMenu.display == false) {
						controllerButtons.A = false;

						//Init select quantity menu
						selectQuantityMenu.centreText = true;
						selectQuantityMenu.display = true;
						selectQuantityMenu.caption = "Unselect crafting item quantity";
						selectQuantityMenu.selected = 1;
						selectQuantityMenu.min = 1;
						selectQuantityMenu.max = craftingItemsSelected[rightSelectedCraftingItemIndex].quantity;

					}
					else {
						controllerButtons.A = false;

						//Update selected crafting item quantity
						craftingItemsSelected[rightSelectedCraftingItemIndex].quantity -= selectQuantityMenu.selected;
						if (craftingItemsSelected[rightSelectedCraftingItemIndex].quantity == 0) {
							craftingItemsSelected.erase(craftingItemsSelected.begin() + rightSelectedCraftingItemIndex);
						}

						selectQuantityMenu.display = false;
						matchingCraftingTableLineIndex = -1;
						craftingTableCraftedItem.type = "";
					}
				}

				//Unselect all quantity
				if (controllerButtons.X == true) {
					controllerButtons.X = false;
					craftingItemsSelected.erase(craftingItemsSelected.begin() + rightSelectedCraftingItemIndex);
					matchingCraftingTableLineIndex = -1;
					craftingTableCraftedItem.type = "";
				}

				//Unselect all
				if (controllerButtons.RB == true) {
					controllerButtons.RB = false;
					craftingItemsSelected.clear();
					deactivateEvent.startTicks = SDL_GetTicks();
					deactivateEvent.delay = 200;
					matchingCraftingTableLineIndex = -1;
					craftingTableCraftedItem.type = "";
				}

			}

			//Craft item
			if (controllerButtons.Y == true && (int)craftingItemsSelected.size() == 3 && matchingCraftingTableLineIndex > -1) {
				controllerButtons.Y = false;
				craftingTable[matchingCraftingTableLineIndex].blueprintFound = true;

				//Insert resulting item in character inventory
				craftingTableCraftedItem.type = craftingTable[matchingCraftingTableLineIndex].resultingItem.type;
				if (craftingTable[matchingCraftingTableLineIndex].resultingItem.type == "Misc") {
					teamCharacter.addMiscItem(craftingTable[matchingCraftingTableLineIndex].resultingItem.miscItem);
					craftingTableCraftedItem.miscItem = craftingTable[matchingCraftingTableLineIndex].resultingItem.miscItem;
				}
				else if (craftingTable[matchingCraftingTableLineIndex].resultingItem.type == "Crafting") {
					teamCharacter.addCraftingItems(craftingTable[matchingCraftingTableLineIndex].resultingItem.craftingItem);
					craftingTableCraftedItem.craftingItem = craftingTable[matchingCraftingTableLineIndex].resultingItem.craftingItem;
				}
				else if (craftingTable[matchingCraftingTableLineIndex].resultingItem.type == "Cyberware") {
					teamCharacter.addCyberware(craftingTable[matchingCraftingTableLineIndex].resultingItem.cyberware);
					craftingTableCraftedItem.cyberware = craftingTable[matchingCraftingTableLineIndex].resultingItem.cyberware;
				}
				else if (craftingTable[matchingCraftingTableLineIndex].resultingItem.type == "Gear") {
					teamCharacter.addGear(craftingTable[matchingCraftingTableLineIndex].resultingItem.gear);
					craftingTableCraftedItem.gear = craftingTable[matchingCraftingTableLineIndex].resultingItem.gear;
				}
				else if (craftingTable[matchingCraftingTableLineIndex].resultingItem.type == "Weapon") {
					teamCharacter.addWeapon(craftingTable[matchingCraftingTableLineIndex].resultingItem.weapon);
					craftingTableCraftedItem.weapon = craftingTable[matchingCraftingTableLineIndex].resultingItem.weapon;
				}
				else if (craftingTable[matchingCraftingTableLineIndex].resultingItem.type == "Consumable") {
					teamCharacter.addConsumable(craftingTable[matchingCraftingTableLineIndex].resultingItem.consumableItem);
					craftingTableCraftedItem.consumableItem = craftingTable[matchingCraftingTableLineIndex].resultingItem.consumableItem;
				}
				else if (craftingTable[matchingCraftingTableLineIndex].resultingItem.type == "Ammo") {
					teamCharacter.addAmmo(craftingTable[matchingCraftingTableLineIndex].resultingItem.ammo);
					craftingTableCraftedItem.ammo = craftingTable[matchingCraftingTableLineIndex].resultingItem.ammo;
				}

				//Update selected crafting items quantity
				for (int craftingItemsSelectedCnt = 0; craftingItemsSelectedCnt < (int)craftingItemsSelected.size(); ++craftingItemsSelectedCnt) {
					teamCharacter.removeCraftingItem(teamCharacter.craftingItems[craftingItemsSelected[craftingItemsSelectedCnt].index]);
				}

				//Add blueprint
				if (craftingMenuHeaders[selectedMenuVars].caption == "Experiment") {
					teamCharacter.addBlueprint(craftingTable[matchingCraftingTableLineIndex].blueprint);
				}

				matchingCraftingTableLineIndex = -1;
			}

		}

		//Exit crafting menu
		if (controllerButtons.B == true && selectQuantityMenu.display == false) {
			controllerButtons.B = false;
			displayCraftingMenu = false;
			displayOptions = true;
			characters[controlledCharacterIndex].disableControls = false;
			matchingCraftingTableLineIndex = -1;
			craftingTableCraftedItem.type = "";
		}

	}
}

void Object::setOrganisationDisplayHierarchyBoolToTrue(vector<Organisation>& organisations) {
	if (setOrganisationDisplayHierarchyBoolToTrueBool == true) {
		setOrganisationDisplayHierarchyBoolToTrueBool = false;
		organisations[getOrganisationIndex(optionOrganisationID)].setDisplayHierarchyBool(true);
	}
}

void Object::updateCharacterSleepState(Character& character) {
	if (updateCharacterSleepStateBool == true) {
		updateCharacterSleepStateBool = false;
		Character::sleepStateStruct sleepState;
		sleepState.state = true;
		sleepState.startTicks = SDL_GetTicks();
		character.setCharacterSleepState(sleepState);
	}
}

Map::Map(mapConstructorVarsStruct constructorVars) {
	ID = constructorVars.ID;
	name = constructorVars.name;
	texture = constructorVars.texture;
	textureSRect = constructorVars.textureSRect;
	textureDRect = constructorVars.textureDRect;
	sRectRelativeToControllerCharacter = constructorVars.sRectRelativeToControllerCharacter;
	alwaysDisplayMap = constructorVars.alwaysDisplayMap;
	gridScaleSize = constructorVars.gridScaleSize;
}

int Map::getID() {
	return ID;
}

string Map::getName() {
	return name;
}

bool Map::getAlwaysDisplayMap() {
	return alwaysDisplayMap;
}

void Map::render() {
	setSDLRenderTarget(NULL);
	setSDLLogicalSize(textLogicalSize);

	//Update source rectangle starting coordinates
	if (sRectRelativeToControllerCharacter == true) {
		XYStruct characterPosition = characters[controlledCharacterIndex].getPosition();
		XYStruct controlledCharacterPositionOnMap = { lround((float)characterPosition.x / gridScaleSize.w), lround((float)characterPosition.y / gridScaleSize.h) };
		textureSRect.x = (controlledCharacterPositionOnMap.x + (tileSize.w / 2)) - (textureSRect.w / 2);
		textureSRect.y = (controlledCharacterPositionOnMap.y + (tileSize.h / 2)) - (textureSRect.h / 2);
	}

	//Render map texture
	setSDLTextureTransparency(texture, textureTransparency);
	SDL_RenderCopy(renderer, texture, &textureSRect, &textureDRect);

	//Render character positions on map
	for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
		sRect = { 26, 0, 11, 11 };
		if (name == "local") {
			XYStruct characterPosition = characters[charactersCnt].getPosition();
			dRect = { lround((float)characterPosition.x / gridScaleSize.w), lround((float)characterPosition.y / gridScaleSize.h), tileSize.w, tileSize.h };
		}
		else if (name == "region") {
			dRect = { lround((float)regionGrid.position.x / gridScaleSize.w), lround((float)regionGrid.position.y / gridScaleSize.h), tileSize.w, tileSize.h };
		}
		else if (name == "mini") {
			dRect = { textureDRect.x + (textureDRect.w / 2) - (tileSize.w / 2), textureDRect.y + (textureDRect.h / 2) - (tileSize.h / 2), tileSize.w, tileSize.h };
		}
		SDL_RenderCopy(renderer, spriteSheets[getSpriteSheetIndex("map")].texture, &sRect, &dRect);
	}

}

Organisation::Organisation(organisationConstructorVarsStruct functionOrganisationConstructorVarsStruct) {
	privateOrganisationConstructorVars = functionOrganisationConstructorVarsStruct;
}

Organisation::~Organisation() {
	SDL_DestroyTexture(hierarchyTexture);
	hierarchyTexture = NULL;
}

int Organisation::getID() {
	return privateOrganisationConstructorVars.ID;
}

void Organisation::setDisplayHierarchyBool(bool currentDisplayHierarchyBool) {
	displayHierarchyBool = currentDisplayHierarchyBool;
}

vector<int> Organisation::getRoleIDs() {
	vector<int> roleIDs;

	for (int hierarchyTableXCnt = 0; hierarchyTableXCnt < (int)privateOrganisationConstructorVars.hierarchyTable.size(); ++hierarchyTableXCnt) {
		for (int hierarchyTableYCnt = 0; hierarchyTableYCnt < (int)privateOrganisationConstructorVars.hierarchyTable[hierarchyTableXCnt].size(); ++hierarchyTableYCnt) {
			roleIDs.push_back(privateOrganisationConstructorVars.hierarchyTable[hierarchyTableXCnt][hierarchyTableYCnt].ID);
		}
	}

	return roleIDs;
}

vector<organisationConstructorVarsStruct::rolePositionStruct> Organisation::getRoles() {
	vector<organisationConstructorVarsStruct::rolePositionStruct> roles;

	for (int hierarchyTableXCnt = 0; hierarchyTableXCnt < (int)privateOrganisationConstructorVars.hierarchyTable.size(); ++hierarchyTableXCnt) {
		for (int hierarchyTableYCnt = 0; hierarchyTableYCnt < (int)privateOrganisationConstructorVars.hierarchyTable[hierarchyTableXCnt].size(); ++hierarchyTableYCnt) {
			roles.push_back(privateOrganisationConstructorVars.hierarchyTable[hierarchyTableXCnt][hierarchyTableYCnt]);
		}
	}

	return roles;
}

void Organisation::displayHierarchy() {
	if (displayHierarchyBool == true) {

		//Init hierarchy texture
		if (hierarchyTexture == NULL) {

			//Get texture size
			WHStruct iconSize = { tileSize.w * 10, tileSize.h * 10 };
			WHStruct textureSize = { -1, -1 };
			int maxRoles = -1;
			for (int layersCnt = 0; layersCnt < (int)privateOrganisationConstructorVars.hierarchyTable.size(); ++layersCnt) {
				if (maxRoles == -1 || (int)privateOrganisationConstructorVars.hierarchyTable[layersCnt].size() > maxRoles) {
					maxRoles = (int)privateOrganisationConstructorVars.hierarchyTable[layersCnt].size();
				}
			}
			textureSize.w = maxRoles * (iconSize.w * 4);
			textureSize.h = (int)privateOrganisationConstructorVars.hierarchyTable.size() * (iconSize.h * 4);

			WHStruct convertedIconSize = convertSize(iconSize, textureSize, textLogicalSize);

			//Create texture
			hierarchyTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, textureSize.w, textureSize.h);
			clearTexture(hierarchyTexture, 0, 0, 0, 255);

			setSDLRenderTarget(hierarchyTexture);

			//Set icon positions on texture
			struct iconPositionStruct {
				XYStruct position = { -1, -1 };
				organisationConstructorVarsStruct::rolePositionStruct rolePosition;
			};
			vector<iconPositionStruct> iconPositions;
			XYStruct position = { 0, 0 };
			for (int layersCnt = 0; layersCnt < (int)privateOrganisationConstructorVars.hierarchyTable.size(); ++layersCnt) {
				position.x = 0;
				for (int rolesCnt = 0; rolesCnt < (int)privateOrganisationConstructorVars.hierarchyTable[layersCnt].size(); ++rolesCnt) {

					//Get icon position and role position
					iconPositionStruct currentIconPosition;
					currentIconPosition.position = position;
					currentIconPosition.rolePosition = privateOrganisationConstructorVars.hierarchyTable[layersCnt][rolesCnt];
					iconPositions.push_back(currentIconPosition);

					position.x += iconSize.w * 4;
				}
				position.y += iconSize.h * 4;
			}

			//Render relationships on texture
			for (int relationshipsCnt = 0; relationshipsCnt < (int)privateOrganisationConstructorVars.relationships.size(); ++relationshipsCnt) {

				//Get From and To role positions
				XYStruct fromRolePosition[2] = {
					{ -1, -1 },
					{ -1, -1 }
				};
				XYStruct toRolePosition[2] = {
					{ -1, -1 },
					{ -1, -1 }
				};
				bool breakIconPositionsGet = false;
				for (int iconPositionsCnt = 0; iconPositionsCnt < (int)iconPositions.size(); ++iconPositionsCnt) {

					//Get From and To role positions for each direction
					for (int directionsCnt = 0; directionsCnt < 2; ++directionsCnt) {
						if (fromRolePosition[directionsCnt].x == -1 && iconPositions[iconPositionsCnt].rolePosition.ID == privateOrganisationConstructorVars.relationships[relationshipsCnt].direction[directionsCnt].roleIDFrom) {
							fromRolePosition[directionsCnt] = iconPositions[iconPositionsCnt].position;
						}
						if (toRolePosition[directionsCnt].x == -1 && iconPositions[iconPositionsCnt].rolePosition.ID == privateOrganisationConstructorVars.relationships[relationshipsCnt].direction[directionsCnt].roleIDTo) {
							toRolePosition[directionsCnt] = iconPositions[iconPositionsCnt].position;
						}

						if (fromRolePosition[directionsCnt].x > -1 && toRolePosition[directionsCnt].x > -1) {

							//Draw line between From and To positions and display relationship type for direction
							SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
							SDL_RenderDrawLine(renderer, fromRolePosition[0].x, fromRolePosition[0].y, toRolePosition[0].x, toRolePosition[0].y); //only render one line for the two directions
							renderText(privateOrganisationConstructorVars.relationships[relationshipsCnt].direction[0].relationshipType, defaultFont, defaultColour, { lround((float)(fromRolePosition[0].x + toRolePosition[0].x) / 2), lround((float)(fromRolePosition[0].y + toRolePosition[0].y) / 2) });
							WHStruct textSize = getTextSize("0", defaultFont);
							renderText(privateOrganisationConstructorVars.relationships[relationshipsCnt].direction[1].relationshipType, defaultFont, defaultColour, { lround((float)(fromRolePosition[1].x + toRolePosition[1].x) / 2), lround((float)(fromRolePosition[1].y + toRolePosition[1].y) / 2) + (textSize.h * 2) });

							breakIconPositionsGet = true;
							break;
						}
					}

					if (breakIconPositionsGet == true) {
						break;
					}
				}

			}

			//Render role icons, role name, goal, character name
			for (int iconPositionsCnt = 0; iconPositionsCnt < (int)iconPositions.size(); ++iconPositionsCnt) {

				//Render icon
				setSDLLogicalSize(textureSize);
				SDL_Rect sRect = convertAreaToSDLRect(iconPositions[iconPositionsCnt].rolePosition.icon.spriteSheetArea);
				SDL_Rect dRect = { iconPositions[iconPositionsCnt].position.x, iconPositions[iconPositionsCnt].position.y, iconSize.w, iconSize.h };
				SDL_RenderCopy(renderer, spriteSheets[iconPositions[iconPositionsCnt].rolePosition.icon.spriteSheetIndex].texture, &sRect, &dRect);

				//Render role name, goal and character name
				Character character = getCharacterByID(iconPositions[iconPositionsCnt].rolePosition.characterID);
				//XYStruct textPosition = convertPosition(position, textureSize, textLogicalSize);
				XYStruct textPosition = iconPositions[iconPositionsCnt].position;
				WHStruct textSize = getTextSize("0", defaultFont);
				//textPosition.y += convertedIconSize.h + textSize.h;
				textPosition.y += iconSize.h + textSize.h;
				renderText(iconPositions[iconPositionsCnt].rolePosition.name, defaultFont, defaultColour, textPosition);
				textPosition.y += textSize.h * 2;
				renderText(iconPositions[iconPositionsCnt].rolePosition.goal, defaultFont, defaultColour, textPosition);
				textPosition.y += textSize.h * 2;
				renderText(character.getName(), defaultFont, defaultColour, textPosition);

			}

		}

		//Display hierarchy texture
		if (hierarchyTexture != NULL) {
			setSDLRenderTarget(NULL);
			setSDLLogicalSize(textLogicalSize);
			setSDLTextureTransparency(hierarchyTexture, 75);
			SDL_RenderCopy(renderer, hierarchyTexture, NULL, NULL);
			removeSDLTextureTransparency(hierarchyTexture);
		}

		//Exit hierarchy texture menu
		if (controllerButtons.B == true) {
			controllerButtons.B = false;
			displayHierarchyBool = false;
		}

	}
}

//class functions end

//void test(int& functionNumber) {
//	++functionNumber;
//}

int main(int argc, char* args[]) {
	/*vector<vector<bool>> maze = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	aStarPathTimerStruct aStarPathTimer;
	XYStruct start = { 0, 0 };
	XYStruct end = { 9, 9 };
	vector<XYStruct> path = getAStarPath(maze, start, end, aStarPathTimer);
	printStr("\npath size:");
	printInt((int)path.size());
	printStr("\npath:");
	printVisualAStarPath(maze, path, start, end);*/
	
	/*int number = 1;
	test(number);
	cout << number;
	exit(0);*/

	if (true) {

		//Multithreading example
		/*thread th1(foo, 3);
		thread th2(Thread_obj(), 3);
		th1.join();
		th2.join();*/

		Uint32 initTimerStartTicks = SDL_GetTicks();

		//Init
		srand(playerSeed);
		loadSettingsFile();
		init();
		setSDLRenderTarget(NULL);
		clearScreen(0, 0, 0, 255);
		SDL_RenderPresent(renderer);
		initMusic();
		initSoundEffects();
		playSoundEffect("zapsplat_science_fiction_gunshot_powerful_blaster_003_62939");
		playMusic("Shadowrun (Sega Genesis_MD) - Title Screen_A bunch of cutscenes");
		initFonts();
		initColours();
		displayLoadingMessage();
		initSpriteSheets();
		initGlobalSprites();
		initTiles();
		initFiles();
		initRegions();
		initLevel();
		//initSkillBasedInteractableObjects();
		//initController();
		initCraftingTable(craftingTable, characters[controlledCharacterIndex].miscItems, characters[controlledCharacterIndex].craftingItems, characters[controlledCharacterIndex].getCyberwares(), characters[controlledCharacterIndex].getGear(), characters[controlledCharacterIndex].getWeapons(), characters[controlledCharacterIndex].getConsumableItems(), characters[controlledCharacterIndex].getAmmos());
		initOrganisations();
		initCharacterOrganisation();

		//Reposition characters
		for (int characterCnt = 0; characterCnt < (int)characters.size(); ++characterCnt) {
			if (characterCnt != controlledCharacterIndex) {
				repositionCharacters(repositionCharactersRelativeToEnum::character, objects, "", characters, characterCnt, controlledCharacterIndex, true, directionEnum::down, characters[characterCnt].getSpriteTargetSize().h * 2);
			}
		}
		/*XYStruct characterPosition = characters[controlledCharacterIndex].getPosition();
		WHStruct characterSize = characters[controlledCharacterIndex].getSpriteTargetSize();
		repositionObject(objects, "Bed", { characterPosition.x, characterPosition.y - (characterSize.h * 8) });*/
		//pressAToContinue();

		float FPSCapMilliseconds = (float)lround((float)1000 / FPSCap);
		selectedMenuLayer = 0;

		//printStr(formatStr("level created in: {} seconds", { strUint32((SDL_GetTicks() - initTimerStartTicks) / 1000) }));

		Uint32 gameClockStartTicks = SDL_GetTicks();

		while (exitMainLoop == false) {

			Uint32 FPSStartTicks = SDL_GetTicks();

			//Init new level
			if (loadLevel == true) {
				loadLevel = false;
				initLevel();
			}

			getEvent();

			setSDLRenderTarget(NULL);

			//Draw and display black screen
			clearScreen(0, 0, 0, 255);

			if (displayMainMenu == true) {
				mainMenu();
			}
			else {
				changeOverworldRegion();

				//Actions
				//moveCamera();
				characterActions();
				//skillBasedInteractableObjectsActions();
				objectActions();
				XYStruct characterPosition = characters[controlledCharacterIndex].getPosition();
				WHStruct characterSpriteTargetSize = characters[controlledCharacterIndex].getSpriteTargetSize();
				centreCamera({ characterPosition.x, characterPosition.y, characterSpriteTargetSize.w, characterSpriteTargetSize.h });
				mapActions();

				//Render
				renderBackgroundCharactersAndObjects();
				//skillBasedInteractableObjectRenders();
				if (quickslotSelectedItem == false) {
					renderHUD();
				}

				//Menus
				setSDLRenderTarget(NULL);
				setSDLLogicalSize(textLogicalSize);
				displayMaps();
				displayCharacterMenus(controlledCharacterIndex);
				if (quickslotSelectedItem == true) {
					renderHUD();
				}
				objectMenus();
				organisationRenders();

			}

			//Cap frame rate
			if (!(vSyncOn == true && FPSCap - 1 == refreshRate) && FPSCap > 0) {
				float frameDuration = (float)(SDL_GetTicks() - FPSStartTicks);
				if (frameDuration < FPSCapMilliseconds) {
					SDL_Delay((Uint32)(FPSCapMilliseconds - frameDuration));
				}
			}

			//Show graphics
			SDL_RenderPresent(renderer);

			//Update game clock
			Uint32 gameClockTimePassed = SDL_GetTicks() - gameClockStartTicks;
			if (gameClockTimePassed >= 1000) {
				//printUInt32(gameClockTimePassed);
				gameClockStartTicks = SDL_GetTicks();
				gameClockTimePassed *= gameClockSpeedMultiplier;
				gameClock = updateGameClock(gameClock, gameClockTimePassed);
			}

		}

		destroyMaps();
		destroyPreRenderTexture();
		destroySpriteSheets();
		closeFonts();
		freeSoundEffects();
		freeMusic();
		close();
	}
	return 0;
}
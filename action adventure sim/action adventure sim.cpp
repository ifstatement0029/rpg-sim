#include "variables.h"

using namespace game;

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

void SDLRenderCopyEx(SDL_Rect sRect, SDL_Rect dRect, spriteStruct& sprite) {
	if (sprite.center.x != -1 && sprite.center.y != -1) {
		SDL_RenderCopyEx(renderer, spriteSheets[sprite.spriteSheetIndex].texture, &sRect, &dRect, sprite.angle, &sprite.center, sprite.flip);
	}
	else {
		SDL_RenderCopyEx(renderer, spriteSheets[sprite.spriteSheetIndex].texture, &sRect, &dRect, sprite.angle, NULL, sprite.flip);
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
	/*SDL_BlendMode* blendMode = NULL;
	SDL_GetTextureBlendMode(texture, blendMode);
	if (*blendMode != SDL_BLENDMODE_BLEND) {
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	}

	Uint8* alpha = NULL;
	SDL_GetTextureAlphaMod(texture, alpha);
	if (*alpha != (255 * transparencyPercentage) / 100) {
		SDL_SetTextureAlphaMod(texture, (255 * transparencyPercentage) / 100);
	};*/

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texture, (255 * transparencyPercentage) / 100);
}

void removeSDLTextureTransparency(SDL_Texture* texture) {
	/*SDL_BlendMode* blendMode = NULL;
	SDL_GetTextureBlendMode(texture, blendMode);
	if (*blendMode != SDL_BLENDMODE_NONE) {
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
	}*/

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
}

void setSDLDrawColour(colourStruct newColour) {
	colourStruct colour;
	SDL_GetRenderDrawColor(renderer, &colour.r, &colour.g, &colour.b, &colour.a);
	if (colour.r != newColour.r || colour.g != newColour.g || colour.b != newColour.b || colour.a != newColour.a) {
		SDL_SetRenderDrawColor(renderer, newColour.r, newColour.g, newColour.b, newColour.a);
	}
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
		if (spriteSheets[spriteSheetsCnt].filePathAndName.substr(folderPath.length(), spriteSheets[spriteSheetsCnt].filePathAndName.length() - folderPath.length() - 4) == spriteSheetName) {
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

string getSpriteSheetName(int spriteSheetIndex) {
	for (int spriteSheetsCnt = 0; spriteSheetsCnt < (int)spriteSheets.size(); ++spriteSheetsCnt) {
		if (spriteSheetsCnt == spriteSheetIndex) {
			return spriteSheets[spriteSheetsCnt].filePathAndName;
		}
	}
	return "";
}

void initSpriteSheets() {

	//Load sprite sheets
	//vector<string> spriteSheetFiles = getFilesOrFolders("C:\\Users\\abc003\\source\\repos\\game1\\exploration-game\\assets\\sprite sheets");
	vector<string> spriteSheetFiles = getFilesOrFolders("assets\\sprite sheets");
	for (int spriteSheetFilesCnt = 0; spriteSheetFilesCnt < (int)spriteSheetFiles.size(); ++spriteSheetFilesCnt) {
		spriteSheetStruct currentSpriteSheet;
		currentSpriteSheet.filePathAndName = spriteSheetFiles[spriteSheetFilesCnt];
		currentSpriteSheet.surface = IMG_Load(currentSpriteSheet.filePathAndName.c_str());
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

vector<vector<areaStruct>> getSpriteAreas(XYStruct startPosition, WHStruct spriteSize, int totalDirections, int totalSpritesPerDirection, WHStruct distanceBetweenSprites) {
	vector<vector<areaStruct>> areas;

	XYStruct currentPosition = startPosition;
	for (int directionsCnt = 0; directionsCnt < totalDirections; ++directionsCnt) {
		vector<areaStruct> currentAreas;
		currentPosition.x = startPosition.x;
		for (int spritesCnt = 0; spritesCnt < totalSpritesPerDirection; ++spritesCnt) {
			currentAreas.push_back({ currentPosition.x, currentPosition.y, spriteSize.w, spriteSize.h });
			currentPosition.x += spriteSize.w + distanceBetweenSprites.w;
		}
		currentPosition.y += spriteSize.h + distanceBetweenSprites.h;
		areas.push_back(currentAreas);
	}

	return areas;
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

	//Init shadow sprite
	shadowSprite.spriteSheetIndex = getSpriteSheetIndex("shadow");
	shadowSprite.sRect = { 0, 0, 32, 32 };

	//Init splatter sprite
	bloodSplatterSprite.spriteSheetIndex = getSpriteSheetIndex("splatter");
	bloodSplatterSprite.areas = {
		{
			{
				{ 0, 0, 2, 2 }
			}
		}
	};

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

//void reSizeTexture(SDL_Texture* sTexture, SDL_Texture* resizedTexture, SDL_Rect sRect, SDL_Rect dRect) {
//	setSDLRenderTarget(resizedTexture);
//	SDL_RenderCopy(renderer, sTexture, &sRect, &dRect);
//}

vector<tileStruct> convertSpriteToTiles(int spriteSheetIndex, areaStruct spriteArea, string tileName) {

	vector<tileStruct> tiles;

	int tileCnt = 0;
	for (int tilesXCnt = spriteArea.x; tilesXCnt < spriteArea.x + spriteArea.w; tilesXCnt += tileSize.w) {
		for (int tilesYCnt = spriteArea.y; tilesYCnt < spriteArea.y + spriteArea.h; tilesYCnt += tileSize.h) {
			tileStruct currentTile;
			
			currentTile.spriteSheetIndex = spriteSheetIndex;
			currentTile.tileName = tileName + str(tileCnt);
			++tileCnt;
			currentTile.spriteSheetArea = { tilesXCnt, tilesYCnt, tileSize.w, tileSize.h };

			tiles.push_back(currentTile);
		}
	}

	return tiles;
}

vector<vector<tileStruct>> convertSpriteToTilesMatrix(int spriteSheetIndex, areaStruct spriteArea, string tileName) {
	vector<vector<tileStruct>> tilesMatrix;

	int tileCnt = 0;
	for (int tilesXCnt = spriteArea.x; tilesXCnt < spriteArea.x + spriteArea.w; tilesXCnt += tileSize.w) {
		vector<tileStruct> tilesMatrixColumn;
		for (int tilesYCnt = spriteArea.y; tilesYCnt < spriteArea.y + spriteArea.h; tilesYCnt += tileSize.h) {
			tileStruct currentTile;

			currentTile.spriteSheetIndex = spriteSheetIndex;
			currentTile.tileName = tileName + str(tileCnt);
			++tileCnt;
			currentTile.spriteSheetArea = { tilesXCnt, tilesYCnt, tileSize.w, tileSize.h };

			tilesMatrixColumn.push_back(currentTile);
		}
		tilesMatrix.push_back(tilesMatrixColumn);
	}

	return tilesMatrix;
}

void addNewTilesToTiles(vector<tileStruct>& tiles, vector<tileStruct>& newTiles) {
	tiles.insert(tiles.end(), newTiles.begin(), newTiles.end());
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

string getTileName(int tileIndex) {
	for (int tilesCnt = 0; tilesCnt < (int)tiles.size(); ++tilesCnt) {
		if (tilesCnt == tileIndex) {
			return tiles[tilesCnt].tileName;
		}
	}
	return "";
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

areaStruct getGridAreaFromPixelArea(areaStruct pixelArea) {
	XYStruct gridPosition = getGridPosition({ pixelArea.x, pixelArea.y });
	XYStruct gridSize = getGridPosition({ pixelArea.w, pixelArea.h });
	return { gridPosition.x, gridPosition.y, gridSize.x, gridSize.y };
}

areaStruct getPixelAreaFromGridArea(areaStruct gridArea) {
	return { gridArea.x * tileSize.w, gridArea.y * tileSize.h, gridArea.w * tileSize.w, gridArea.h * tileSize.h };
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

collisionDataStruct checkCollisionWithOverworldGrid(areaStruct gridArea, int gridLayer) {
	collisionDataStruct collisionData;

	for (int areaXCnt = gridArea.x; areaXCnt < gridArea.x + gridArea.w; ++areaXCnt) {
		for (int areaYCnt = gridArea.y; areaYCnt < gridArea.y + gridArea.h; ++areaYCnt) {
			
			if (gridLayer < (int)overworldGrid.gridTile.size() && areaXCnt < (int)overworldGrid.gridTile[gridLayer].size() && areaYCnt < (int)overworldGrid.gridTile[gridLayer][areaXCnt].size() && overworldGrid.gridTile[gridLayer][areaXCnt][areaYCnt].collidable == true) {
				collisionData.collision = true;
				collisionData.collidePosition = { areaXCnt, areaYCnt };

				return collisionData;
			}

		}
	}
	
	return collisionData;
}

collisionDataStruct checkCollisionWithOverworldGridFactoringHeight(areaStruct gridArea, areaStruct previousGridArea, int gridLayer, int height) {
	collisionDataStruct collisionData;

	for (int areaXCnt = gridArea.x; areaXCnt < gridArea.x + gridArea.w; ++areaXCnt) {
		for (int areaYCnt = gridArea.y; areaYCnt < gridArea.y + gridArea.h; ++areaYCnt) {

			if (gridLayer < (int)overworldGrid.gridTile.size() && areaXCnt >= 0 && areaXCnt <= (int)overworldGrid.gridTile[gridLayer].size() - 1 && areaYCnt >= 0 && areaYCnt <= (int)overworldGrid.gridTile[gridLayer][areaXCnt].size() - 1 && overworldGrid.gridTile[gridLayer][areaXCnt][areaYCnt].collidable == true) {
				if ((overworldGrid.gridTile[gridLayer][areaXCnt][areaYCnt].jumpable == true && height < overworldGrid.gridTile[gridLayer][areaXCnt][areaYCnt].height) || overworldGrid.gridTile[gridLayer][areaXCnt][areaYCnt].jumpable == false) {
					collisionData.collision = true;
					collisionData.collidePosition = { areaXCnt, areaYCnt };

					//Get side of grid tile hit
					if (previousGridArea.x > -1 && previousGridArea.y > -1 && previousGridArea.w > -1 && previousGridArea.h > -1) {
						areaStruct tileGridArea = { areaXCnt, areaYCnt, 1, 1 };
						if (previousGridArea.x + previousGridArea.w - 1 < tileGridArea.x) {
							collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::left;
						}
						else if (previousGridArea.x > tileGridArea.x + tileGridArea.w - 1) {
							collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::right;
						}
						else if (previousGridArea.y + previousGridArea.h - 1 < tileGridArea.y) {
							collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::up;
						}
						else if (previousGridArea.y > tileGridArea.y + tileGridArea.h - 1) {
							collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::down;
						}
					}

				}

				return collisionData;
			}

		}
	}

	return collisionData;
}

collisionDataStruct checkSubGridCollisionWithOverworldGridFactoringHeight(areaStruct gridArea, areaStruct pixelArea, int gridLayer, int height) {
	collisionDataStruct collisionData;

	for (int areaXCnt = gridArea.x; areaXCnt < gridArea.x + gridArea.w; ++areaXCnt) {
		for (int areaYCnt = gridArea.y; areaYCnt < gridArea.y + gridArea.h; ++areaYCnt) {

			//Check collisions at grid level
			if (gridLayer < (int)overworldGrid.gridTile.size() && areaXCnt < (int)overworldGrid.gridTile[gridLayer].size() && areaYCnt < (int)overworldGrid.gridTile[gridLayer][areaXCnt].size() && overworldGrid.gridTile[gridLayer][areaXCnt][areaYCnt].collidable == true) {

				//Check collision at pixel level
				areaStruct tilePixelArea = getPixelAreaFromGridArea(gridArea);
				for (int pixelAreaXCnt = pixelArea.x; pixelAreaXCnt < pixelArea.x + pixelArea.w; ++pixelAreaXCnt) {
					for (int pixelAreaYCnt = pixelArea.y; pixelAreaYCnt < pixelArea.y + pixelArea.h; ++pixelAreaYCnt) {
						
						for (int tilePixelAreaXCnt = tilePixelArea.x; tilePixelAreaXCnt < tilePixelArea.x + tilePixelArea.w; ++tilePixelAreaXCnt) {
							for (int tilePixelAreaYCnt = tilePixelArea.y; tilePixelAreaYCnt < tilePixelArea.y + tilePixelArea.h; ++tilePixelAreaYCnt) {
								
								if (pixelAreaXCnt == tilePixelAreaXCnt && pixelAreaYCnt == tilePixelAreaYCnt) {
									
									if ((overworldGrid.gridTile[gridLayer][areaXCnt][areaYCnt].jumpable == true && height < overworldGrid.gridTile[gridLayer][areaXCnt][areaYCnt].height) || overworldGrid.gridTile[gridLayer][areaXCnt][areaYCnt].jumpable == false) {
										collisionData.collision = true;
										collisionData.collidePosition = { areaXCnt, areaYCnt };
									}

									return collisionData;

								}

							}
						}

					}
				}

			}

		}
	}

	return collisionData;
}

bool checkCollisionWithCollidableObject(areaStruct gridArea, int gridLayer) {
	for (int collidableObjectsCnt = 0; collidableObjectsCnt < (int)collidableObjects.size(); ++collidableObjectsCnt) {
		areaStruct collidableObjectGridArea = getGridAreaFromPixelArea(collidableObjects[collidableObjectsCnt].area);

		for (int collidableObjectGridAreaXCnt = collidableObjectGridArea.x; collidableObjectGridAreaXCnt < collidableObjectGridArea.x + collidableObjectGridArea.w; ++collidableObjectGridAreaXCnt) {
			for (int collidableObjectGridAreaYCnt = collidableObjectGridArea.y; collidableObjectGridAreaYCnt < collidableObjectGridArea.y + collidableObjectGridArea.h; ++collidableObjectGridAreaYCnt) {

				for (int gridAreaXCnt = gridArea.x; gridAreaXCnt < gridArea.x + gridArea.w; ++gridAreaXCnt) {
					for (int gridAreaYCnt = gridArea.y; gridAreaYCnt < gridArea.y + gridArea.h; ++gridAreaYCnt) {

						if (collidableObjectGridAreaXCnt == gridAreaXCnt && collidableObjectGridAreaYCnt == gridAreaYCnt) {
							return true;
						}

					}
				}

			}
		}
	}
	return false;
}

bool checkCollisionWithCollidableObjectFactoringHeight(areaStruct gridArea, int gridLayer, int height) {
	for (int collidableObjectsCnt = 0; collidableObjectsCnt < (int)collidableObjects.size(); ++collidableObjectsCnt) {
		areaStruct collidableObjectGridArea = getGridAreaFromPixelArea(collidableObjects[collidableObjectsCnt].area);
		
		if (height < collidableObjects[collidableObjectsCnt].height) {

			for (int collidableObjectGridAreaXCnt = collidableObjectGridArea.x; collidableObjectGridAreaXCnt < collidableObjectGridArea.x + collidableObjectGridArea.w; ++collidableObjectGridAreaXCnt) {
				for (int collidableObjectGridAreaYCnt = collidableObjectGridArea.y; collidableObjectGridAreaYCnt < collidableObjectGridArea.y + collidableObjectGridArea.h; ++collidableObjectGridAreaYCnt) {

					for (int gridAreaXCnt = gridArea.x; gridAreaXCnt < gridArea.x + gridArea.w; ++gridAreaXCnt) {
						for (int gridAreaYCnt = gridArea.y; gridAreaYCnt < gridArea.y + gridArea.h; ++gridAreaYCnt) {

							if (collidableObjectGridAreaXCnt == gridAreaXCnt && collidableObjectGridAreaYCnt == gridAreaYCnt) {
								return true;
							}

						}
					}

				}
			}

		}
	}
	return false;
}

//Need to factor height in areas
collisionDataStruct checkCollisionWithCharacter(areaStruct sourcePixelArea, areaStruct previousPixelArea) {
	collisionDataStruct collisionData;

	for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
		XYStruct characterPosition = characters[charactersCnt].getPosition();
		WHStruct characterSize = characters[charactersCnt].getSize();
		
		if (areaWithinArea(sourcePixelArea, { characterPosition.x, characterPosition.y, characterSize.w, characterSize.h }) == true) {
			collisionData.collision = true;
			collisionData.collidePosition = characterPosition;
			collisionData.instanceID = characters[charactersCnt].getID();

			//Get side of character hit
			if (previousPixelArea.x > -1 && previousPixelArea.y > -1 && previousPixelArea.w > -1 && previousPixelArea.h > -1) {
				if (previousPixelArea.x + previousPixelArea.w - 1 < sourcePixelArea.x) {
					collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::left;
				}
				else if (previousPixelArea.x > sourcePixelArea.x + sourcePixelArea.w - 1) {
					collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::right;
				}
				else if (previousPixelArea.y + previousPixelArea.h - 1 < sourcePixelArea.y) {
					collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::up;
				}
				else if (previousPixelArea.y > sourcePixelArea.y + sourcePixelArea.h - 1) {
					collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::down;
				}
			}

			return collisionData;
		}
	}
	return collisionData;
}

collisionDataStruct checkCollisionWithTable(areaStruct sourcePixelArea, areaStruct previousPixelArea) {
	collisionDataStruct collisionData;
	for (int tablesCnt = 0; tablesCnt < (int)tables.size(); ++tablesCnt) {
		XYStruct tablePosition = tables[tablesCnt].getPosition();
		WHStruct tableSize = tables[tablesCnt].getSize();
		if (areaWithinArea(sourcePixelArea, { tablePosition.x, tablePosition.y, tableSize.w, tableSize.h }) == true) {
			collisionData.collision = true;
			collisionData.collidePosition = tablePosition;
			collisionData.instanceID = tables[tablesCnt].getID();

			//Get side of table hit
			if (previousPixelArea.x > -1 && previousPixelArea.y > -1 && previousPixelArea.w > -1 && previousPixelArea.h > -1) {
				if (previousPixelArea.x + previousPixelArea.w - 1 < sourcePixelArea.x) {
					collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::left;
				}
				else if (previousPixelArea.x > sourcePixelArea.x + sourcePixelArea.w - 1) {
					collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::right;
				}
				else if (previousPixelArea.y + previousPixelArea.h - 1 < sourcePixelArea.y) {
					collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::up;
				}
				else if (previousPixelArea.y > sourcePixelArea.y + sourcePixelArea.h - 1) {
					collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::down;
				}
			}

			return collisionData;
		}
	}
	return collisionData;
}

collisionDataStruct checkCollisionWithBullet(areaStruct sourcePixelArea, areaStruct previousPixelArea) {
	collisionDataStruct collisionData;
	for (int bulletsCnt = 0; bulletsCnt < (int)bullets.size(); ++bulletsCnt) {
		XYStruct bulletPosition = bullets[bulletsCnt].getPosition();
		WHStruct bulletSize = bullets[bulletsCnt].getSize();
		if (areaWithinArea(sourcePixelArea, { bulletPosition.x, bulletPosition.y, bulletSize.w, bulletSize.h }) == true) {
			collisionData.collision = true;
			collisionData.collidePosition = bulletPosition;
			collisionData.instanceID = bullets[bulletsCnt].getID();

			//Get side of bullet hit
			if (previousPixelArea.x > -1 && previousPixelArea.y > -1 && previousPixelArea.w > -1 && previousPixelArea.h > -1) {
				if (previousPixelArea.x + previousPixelArea.w - 1 < sourcePixelArea.x) {
					collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::left;
				}
				else if (previousPixelArea.x > sourcePixelArea.x + sourcePixelArea.w - 1) {
					collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::right;
				}
				else if (previousPixelArea.y + previousPixelArea.h - 1 < sourcePixelArea.y) {
					collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::up;
				}
				else if (previousPixelArea.y > sourcePixelArea.y + sourcePixelArea.h - 1) {
					collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::down;
				}
			}

			return collisionData;
		}
	}
	return collisionData;
}

void displayLoadingMessage() {
	setSDLRenderTarget(NULL);
	clearScreen(0, 0, 0, 255);
	string text = "LOADING";
	renderText(text, defaultFont, defaultColour, { tileSize.w, textLogicalSize.h - (getTextSize(text, defaultFont).h * 2) });
	SDL_RenderPresent(renderer);
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

bool areaWithinGrid(areaStruct gridArea, int gridLayer) {
	if (gridArea.x + gridArea.w - 1 >= 0 && gridArea.x <= (int)overworldGrid.gridTile[gridLayer].size() - 1 && gridArea.y + gridArea.h - 1 >= 0 && gridArea.y <= (int)overworldGrid.gridTile[gridLayer][gridArea.x].size() - 1) {
		return true;
	}
	return false;
}

void initGameClock() {
	gameClock.year = randInt(2021, 2030);
	gameClock.month = randInt(1, 12);
	gameClock.day = randInt(1, 31);
	gameClock.hour = randInt(0, 23);
	gameClock.minute = randInt(0, 59);
	gameClock.second = randInt(0, 59);
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
				printXYStruct(characters[controlledCharacterIndex].getPosition());

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

void insertTilesInOverworldGrid(XYStruct startGridPosition, vector<vector<tileStruct>> tilesMatrix, int overworldGridLayer, int tileHeight, bool tileCollidable, bool tileJumpable) {
	XYStruct gridPosition = startGridPosition;
	for (int tilesMatrixXCnt = 0; tilesMatrixXCnt < (int)tilesMatrix.size(); ++tilesMatrixXCnt) {
		gridPosition.y = startGridPosition.y;
		for (int tilesMatrixYCnt = 0; tilesMatrixYCnt < (int)tilesMatrix[tilesMatrixXCnt].size(); ++tilesMatrixYCnt) {
			overworldGrid.gridTile[overworldGridLayer][gridPosition.x][gridPosition.y].tileIndex = getTileIndex(tilesMatrix[tilesMatrixXCnt][tilesMatrixYCnt].tileName);
			overworldGrid.gridTile[overworldGridLayer][gridPosition.x][gridPosition.y].height = tileHeight;
			overworldGrid.gridTile[overworldGridLayer][gridPosition.x][gridPosition.y].collidable = tileCollidable;
			overworldGrid.gridTile[overworldGridLayer][gridPosition.x][gridPosition.y].jumpable = tileJumpable;
			++gridPosition.y;
		}
		++gridPosition.x;
	}
}

void makeUpperPartOfObjectNonCollidable(vector<vector<bool>>& collidableGridArea, areaStruct objectArea, int objectHeight) {
	areaStruct objectGridArea = getGridAreaFromPixelArea(objectArea);
	int objectGridHeight = lround((float)objectHeight / tileSize.h);

	for (int objectGridAreaXCnt = 0; objectGridAreaXCnt < objectGridArea.w; ++objectGridAreaXCnt) {
		for (int objectGridAreaYCnt = 0; objectGridAreaYCnt < objectGridArea.h; ++objectGridAreaYCnt) {
			if (objectGridAreaYCnt < objectGridArea.h - objectGridHeight) {
				collidableGridArea[objectGridAreaXCnt][objectGridAreaYCnt] = false;
			}
		}
	}
}

void initBoolGrid(vector<vector<bool>>& grid, WHStruct gridSize, bool boolValue) {
	grid.clear();
	for (int boolGridXCnt = 0; boolGridXCnt < gridSize.w; ++boolGridXCnt) {
		grid.resize(boolGridXCnt + 1);
		for (int boolGridYCnt = 0; boolGridYCnt < gridSize.h; ++boolGridYCnt) {
			grid[boolGridXCnt].resize(boolGridYCnt + 1);
			grid[boolGridXCnt][boolGridYCnt] = boolValue;
		}
	}
}

void initTables(int layer) {
	for (int tablesCnt = 0; tablesCnt < randInt(2, 4); ++tablesCnt) {
		
		//Init table
		tableParamsStruct newTableParams;
		newTableParams.ID = tablesCnt;
		newTableParams.layer = layer;
		areaStruct gridArea = alignPixelAreaToGrid({ randInt(0, camera.area.w), randInt(0, camera.area.h), tileSize.w * 3, tileSize.h * 2 });
		newTableParams.position = { gridArea.x, gridArea.y };
		newTableParams.size = { gridArea.w, gridArea.h };
		newTableParams.height = newTableParams.size.h / 2;
		newTableParams.sprite.spriteSheetIndex = getSpriteSheetIndex("table");
		newTableParams.sprite.areas = {
			{
				{ 0, 0, 24, 16 }
			}
		};
		newTableParams.resistance = 1;
		Table newTable(newTableParams);
		tables.push_back(newTable);

		//Init collidable object
		collidableObjectStruct currentCollidableObject;
		currentCollidableObject.area = { newTableParams.position.x, newTableParams.position.y, newTableParams.size.w, newTableParams.size.h };
		currentCollidableObject.height = newTableParams.height;
		areaStruct currentJumpableObjectGridArea = getGridAreaFromPixelArea(currentCollidableObject.area);
		collidableObjects.push_back(currentCollidableObject);

	}
}

void initLevel() {
	displayLoadingMessage();

	//Run through rand
	runThroughRand(playerSeed, { 0, 0, regionGrid.position.x - 0, regionGrid.position.y - 0 }, { overworldGrid.heightStartEnd.start, overworldGrid.height }, regionGrid.position, 0, 0, 1);

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
			overworldGrid.gridTile[overworldGrid.groundLayerIndex][gridXCnt][gridYCnt].tileIndex = getTileIndex("concrete floor");
			overworldGrid.gridTile[overworldGrid.groundLayerIndex][gridXCnt][gridYCnt].collidable = false;
		}
	}

	//Walls
	for (int wallsCnt = 0; wallsCnt < randInt(1000, 2000); ++wallsCnt) {
		WHStruct wallSize = { 1, 1 };
		if (randInt(1, 2) == 1) {
			wallSize.w += randInt(1, 5);
		}
		else {
			wallSize.h += randInt(1, 5);
		}

		XYStruct tilePosition = { randInt(0, (int)overworldGrid.gridTile[1].size() - 1), randInt(0, (int)overworldGrid.gridTile[1][0].size() - 1) };

		for (int wallXCnt = tilePosition.x; wallXCnt < tilePosition.x + wallSize.w; ++wallXCnt) {
			for (int wallYCnt = tilePosition.y; wallYCnt < tilePosition.y + wallSize.h; ++wallYCnt) {
				if (areaWithinGrid({ wallXCnt, wallYCnt, 1, 1 }, 1) == true) {
					overworldGrid.gridTile[1][wallXCnt][wallYCnt].collidable = true;
					overworldGrid.gridTile[1][wallXCnt][wallYCnt].tileIndex = getTileIndex("wall");
					overworldGrid.gridTile[1][wallXCnt][wallYCnt].resistance = 100;
					overworldGrid.gridTile[1][wallXCnt][wallYCnt].stuckTolerancePercentage = 100;
				}
			}
		}
	}

	//Tables (tiles)
	//WHStruct tableSpriteSize = { 24, 16 };
	//vector<tileStruct> newTiles = convertSpriteToTiles(getSpriteSheetIndex("table"), { 0, 0, tableSpriteSize.w, tableSpriteSize.h }, "table");
	//addNewTilesToTiles(tiles, newTiles);
	//vector<vector<tileStruct>> tilesMatrix = convertSpriteToTilesMatrix(getSpriteSheetIndex("table"), { 0, 0, tableSpriteSize.w, tableSpriteSize.h }, "table");
	//for (int tablesCnt = 0; tablesCnt < randInt(2, 4); ++tablesCnt) {
	//	//XYStruct position = { lround((float)randInt(0, (int)overworldGrid.gridTile[1].size() - 1) / tileSize.w), lround((float)randInt(0, (int)overworldGrid.gridTile[1][0].size() - 1) / tileSize.h) };
	//	XYStruct position = { lround((float)randInt(camera.area.x, camera.area.x + camera.area.w - 1) / tileSize.w), lround((float)randInt(camera.area.y, camera.area.y + camera.area.h - 1) / tileSize.h) };
	//	
	//	insertTilesInOverworldGrid(position, tilesMatrix, 1, tableSpriteSize.h / 2, true, true);
	//}

	initTables(1);
}

void initCharacters() {
	controlledCharacterIndex = 0;
	int characterID = 0;
	XYStruct characterPosition = { 191, 193 };
	for (int charactersCnt = 0; charactersCnt < 10; ++charactersCnt) {
		characterParams currentCharacterParams;

		currentCharacterParams.ID = characterID;
		++characterID;

		currentCharacterParams.position = characterPosition;
		currentCharacterParams.groundPosition = currentCharacterParams.position;
		currentCharacterParams.size = { tileSize.w * 4, tileSize.h * 4 };

		currentCharacterParams.sprites.spriteSheetIndex = getSpriteSheetIndex("main character");
		//currentCharacterParams.sprites.areas = getSpriteAreas({ 2, 10 }, { 32, 32 }, 8, 4, { 8, 18 });
		currentCharacterParams.sprites.areas = {
			{
				{ 526, 7, 29, 35 }, { 559, 7, 29, 35 }, { 590, 7, 29, 35 }, { 621, 7, 29, 35 } //up
			},
			{
				{ 5, 7, 29, 35 }, { 45, 7, 29, 35 }, { 78, 7, 29, 35 }, { 117, 7, 29, 35 } //down
			},
			{
				{ 147, 159, 29, 35 }, { 174, 159, 29, 35 }, { 199, 159, 29, 35 }, { 228, 159, 29, 35 } //left
			},
			{
				{ 278, 7, 29, 35 }, { 301, 7, 29, 35 }, { 332, 7, 29, 35 }, { 356, 7, 29, 35 } //right
			},
			{
				{ 388, 7, 29, 35 }, { 422, 7, 29, 35 }, { 461, 7, 29, 35 }, { 492, 7, 29, 35 } //up-right
			},
			{
				{ 151, 7, 29, 35 }, { 181, 7, 29, 35 }, { 214, 7, 29, 35 }, { 246, 7, 29, 35 } //down-right
			},
			{
				{ 255, 159, 29, 35 }, { 291, 159, 29, 35 }, { 321, 159, 29, 35 }, { 354, 159, 29, 35 } //down-left
			},
			{
				{ 9, 159, 29, 35 }, { 40, 159, 29, 35 }, { 76, 159, 29, 35 }, { 114, 159, 29, 35 } //up-left
			}
		};

		currentCharacterParams.layer = 1;

		//Init equipped weapon
		currentCharacterParams.equippedWeaponType = characterParams::equippedWeaponTypeEnum::melee;
		switch (currentCharacterParams.equippedWeaponType) {
			case characterParams::equippedWeaponTypeEnum::ranged: {
				currentCharacterParams.equippedRangedWeapon.name = "Gun";
				currentCharacterParams.equippedRangedWeapon.size = { tileSize.w * 4, tileSize.h * 2 };
				currentCharacterParams.equippedRangedWeapon.sprite.spriteSheetIndex = getSpriteSheetIndex("weapons");
				vector<areaStruct> areas;
				areas.push_back({ 2, 21, 21, 8 });
				currentCharacterParams.equippedRangedWeapon.sprite.areas.push_back(areas);
				currentCharacterParams.equippedRangedWeapon.sprite.center = { 0, currentCharacterParams.equippedRangedWeapon.sprite.areas[0][0].h / 2 };
				currentCharacterParams.equippedRangedWeapon.fireMode = characterParams::rangedWeaponStruct::fireModeEnum::semiAuto;
				currentCharacterParams.equippedRangedWeapon.burst.maxBulletsBeforePause = 3;
				currentCharacterParams.equippedRangedWeapon.burst.delay.delay = 200;
				currentCharacterParams.equippedRangedWeapon.magazine.ammoName = "Blank";
				currentCharacterParams.equippedRangedWeapon.magazine.capacity = 100;
				currentCharacterParams.equippedRangedWeapon.magazine.currentLoad = 90;
				currentCharacterParams.equippedRangedWeapon.reload.delay.delay = 1000;
				currentCharacterParams.equippedRangedWeapon.reload.sprite.spriteSheetIndex = getSpriteSheetIndex("weapons");
				currentCharacterParams.equippedRangedWeapon.reload.sprite.areas = {
					{
						{ 41, 168, 8, 8 },
						{ 52, 168, 8, 8 }
					}
				};
				break;
			}
			case characterParams::equippedWeaponTypeEnum::melee: {
				currentCharacterParams.equippedMeleeWeapon.name = "Katana";
				currentCharacterParams.equippedMeleeWeapon.position = currentCharacterParams.position;
				currentCharacterParams.equippedMeleeWeapon.size = { tileSize.w * 4, tileSize.h * 2 };
				currentCharacterParams.equippedMeleeWeapon.sprite.spriteSheetIndex = getSpriteSheetIndex("weapons");
				currentCharacterParams.equippedMeleeWeapon.sprite.areas = {
					{
						{ 522, 9, 29, 6 }
					}
				};
				currentCharacterParams.equippedMeleeWeapon.sprite.center = { 0, currentCharacterParams.equippedMeleeWeapon.sprite.areas[0][0].h / 2 };
				currentCharacterParams.equippedMeleeWeapon.swing.delay.delay = 1;
				currentCharacterParams.equippedMeleeWeapon.damage = 50;
				currentCharacterParams.equippedMeleeWeapon.resistance = 50;
				break;
			}
		}

		currentCharacterParams.resistance = 100;

		Character currentCharacter(currentCharacterParams);
		characters.push_back(currentCharacter);

		characterPosition.x += currentCharacterParams.size.w;
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

//vector<areaStruct> getSpriteAreas(XYStruct start, WHStruct spriteSize, int totalSprites) {
//
//	//Get areas of each sprite
//	vector<areaStruct> spriteAreas;
//	areaStruct currentSpriteArea = { start.x, start.y, spriteSize.w, spriteSize.h };
//	for (int spritesCnt = 0; spritesCnt < totalSprites; ++spritesCnt) {
//		spriteAreas.push_back(currentSpriteArea);
//		currentSpriteArea.x += spriteSize.w;
//	}
//
//	return spriteAreas;
//}

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

bool compareRenderOrderStructByHeight(const renderOrderStruct& renderOrderA, const renderOrderStruct& renderOrderB) {
	return renderOrderA.height < renderOrderB.height;
}

bool compareRenderOrderStructByLayerNum(const renderOrderStruct& renderOrderA, const renderOrderStruct& renderOrderB) {
	return renderOrderA.layerIndex < renderOrderB.layerIndex;
}

void renderBackgroundCharactersAndObjects() {
	setSDLRenderTarget(NULL);
	setSDLLogicalSize(cameraLogicalSize);

	vector<renderOrderStruct> renderOrder;

	//Insert characters in renderOrder vector
	for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
		renderOrderStruct currentRenderOrderStruct;
		
		currentRenderOrderStruct.type = renderOrderStruct::typeEnum::character;
		currentRenderOrderStruct.layerIndex = characters[charactersCnt].getLayer();
		currentRenderOrderStruct.index = charactersCnt;
		XYStruct characterPosition = characters[charactersCnt].getPosition();
		currentRenderOrderStruct.position = { characterPosition.x, characterPosition.y + characters[charactersCnt].getSize().h / 2 };
		//currentRenderOrderStruct.height = characters[charactersCnt].getCurrentHeight();

		renderOrder.push_back(currentRenderOrderStruct);
	}

	//Insert tables in renderOrder vector
	for (int tablesCnt = 0; tablesCnt < (int)tables.size(); ++tablesCnt) {
		renderOrderStruct currentRenderOrderStruct;

		currentRenderOrderStruct.type = renderOrderStruct::typeEnum::table;
		currentRenderOrderStruct.layerIndex = tables[tablesCnt].getLayer();
		currentRenderOrderStruct.index = tablesCnt;
		currentRenderOrderStruct.position = tables[tablesCnt].getPosition();
		//currentRenderOrderStruct.height = tables[tablesCnt].getHeight(); //height of non-character needs to be 0 so character can appear on top of them if jumped on them

		renderOrder.push_back(currentRenderOrderStruct);
	}

	//Insert bullets in renderOrder vector
	for (int bulletsCnt = 0; bulletsCnt < (int)bullets.size(); ++bulletsCnt) {
		renderOrderStruct newRenderOrderElement;
		
		newRenderOrderElement.type = renderOrderStruct::typeEnum::bullet;
		newRenderOrderElement.layerIndex = bullets[bulletsCnt].getLayer();
		newRenderOrderElement.index = bulletsCnt;
		newRenderOrderElement.position = bullets[bulletsCnt].getPosition();
		
		renderOrder.push_back(newRenderOrderElement);
	}

	//Insert explosion in renderOrder vector
	for (int explosionsCnt = 0; explosionsCnt < (int)explosions.size(); ++explosionsCnt) {
		renderOrderStruct newRenderOrderElement;

		newRenderOrderElement.type = renderOrderStruct::typeEnum::explosion;
		newRenderOrderElement.layerIndex = explosions[explosionsCnt].getOverworldGridLayer();
		newRenderOrderElement.index = explosionsCnt;
		newRenderOrderElement.position = explosions[explosionsCnt].getFragmentPosition(0);;

		renderOrder.push_back(newRenderOrderElement);
	}

	//Sort renderOrder by x then by y, then by layerNum
	if ((int)renderOrder.size() > 0) {
		sort(renderOrder.begin(), renderOrder.end(), compareRenderOrderStructByX);
		sort(renderOrder.begin(), renderOrder.end(), compareRenderOrderStructByY);
		//sort(renderOrder.begin(), renderOrder.end(), compareRenderOrderStructByHeight);
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
	decimalNumPartsStruct currentDecimalNumPartsX = getDecimalNumParts((double)cameraLogicalSize.w / aspectRatio.ratio.w);
	decimalNumPartsStruct currentDecimalNumPartsY = getDecimalNumParts((double)cameraLogicalSize.h / aspectRatio.ratio.h);
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

					SDL_Rect sRect = convertAreaToSDLRect(tiles[overworldGrid.gridTile[layersCnt][gridXCnt][gridYCnt].tileIndex].spriteSheetArea);

					SDL_Rect dRect = { tilePosition.x - camera.area.x, tilePosition.y - camera.area.y, tileSize.w, tileSize.h };

					SDL_RenderCopy(renderer, spriteSheets[tiles[overworldGrid.gridTile[layersCnt][gridXCnt][gridYCnt].tileIndex].spriteSheetIndex].texture, &sRect, &dRect);
				}
			}
		}

		if ((int)renderOrder.size() > 0) {

			//First render (to guarantee graphics that need to are rendered below second render)
			for (int renderOrderCnt = 0; renderOrderCnt < (int)renderOrder.size(); ++renderOrderCnt) {
				if (renderOrder[renderOrderCnt].layerIndex == layersCnt) {
					switch (renderOrder[renderOrderCnt].type) {
						case renderOrderStruct::typeEnum::explosion: {
							explosions[renderOrder[renderOrderCnt].index].render();
							break;
						}
					}
				}
			}

			//Second render
			for (int renderOrderCnt = 0; renderOrderCnt < (int)renderOrder.size(); ++renderOrderCnt) {
				if (renderOrder[renderOrderCnt].layerIndex == layersCnt) {
					switch (renderOrder[renderOrderCnt].type) {
						case renderOrderStruct::typeEnum::character: {

							//If character is facing up then render weapon before character
							directionEnum characterDirection = characters[renderOrder[renderOrderCnt].index].getDirection();
							if (characterDirection == directionEnum::up || characterDirection == directionEnum::upLeft || characterDirection == directionEnum::upRight || characterDirection == directionEnum::left) {
								characters[renderOrder[renderOrderCnt].index].renderEquippedWeapon();
							}
							
							characters[renderOrder[renderOrderCnt].index].render();
							characters[renderOrder[renderOrderCnt].index].renderReloadAnimation();
							
							//If character if facing down then render weapon after character
							if (characterDirection == directionEnum::down || characterDirection == directionEnum::downLeft || characterDirection == directionEnum::downRight || characterDirection == directionEnum::right) {
								characters[renderOrder[renderOrderCnt].index].renderEquippedWeapon();
							}
							
							break;
						}
						case renderOrderStruct::typeEnum::table: {
							tables[renderOrder[renderOrderCnt].index].render();
							break;
						}
						case renderOrderStruct::typeEnum::bullet: {
							bullets[renderOrder[renderOrderCnt].index].render();
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
	SDL_Rect sRect = { 0, 0, preRenderTextureSize.w, preRenderTextureSize.h };
	SDL_Rect dRect = { 0, 0, preRenderTextureSize.w, preRenderTextureSize.h };
	SDL_RenderCopy(renderer, preRenderTexture, &sRect, &dRect);
	clearTexture(preRenderTexture, 0, 0, 0, 255);

}

void renderUI() {
	setSDLRenderTarget(NULL);
	setSDLLogicalSize(textLogicalSize);

	WHStruct textSize = getTextSize("Z", defaultFont);

	//Render equipped weapon magazine ammo
	characterParams::rangedWeaponStruct::magazineStruct magazine = characters[controlledCharacterIndex].getMagazine();
	renderText(characters[controlledCharacterIndex].getEquippedWeaponName(), defaultFont, defaultColour, { 0, textLogicalSize.h - (textSize.h * 6) });
	renderText(magazine.ammoName, defaultFont, defaultColour, {0, textLogicalSize.h - (textSize.h * 4)});
	renderText(formatStr("{}/{}", { str(magazine.currentLoad), str(magazine.capacity) }), defaultFont, defaultColour, { 0, textLogicalSize.h - (textSize.h * 2) });

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

void centreCamera(areaStruct position, int overGridLayerIndex) {
	camera.area.x = (position.x + roundDiv(position.w, 2)) - roundDiv(camera.area.w, 2);

	camera.area.y = (position.y + roundDiv(position.h, 2)) - roundDiv(camera.area.h, 2);

	if (camera.area.x < 0) {
		camera.area.x = 0;
	}
	if (camera.area.x + camera.area.w - 1 > ((int)overworldGrid.gridTile[overGridLayerIndex].size() - 1) * tileSize.w) {
		camera.area.x = (((int)overworldGrid.gridTile[overGridLayerIndex].size() - 1) * tileSize.w) - camera.area.w;
	}

	if (camera.area.y < 0) {
		camera.area.y = 0;
	}
	if (camera.area.y + camera.area.h - 1 > ((int)overworldGrid.gridTile[overGridLayerIndex][0].size() - 1) * tileSize.h) {
		camera.area.y = (((int)overworldGrid.gridTile[overGridLayerIndex][0].size() - 1) * tileSize.h) - camera.area.h;
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

void displayCopyright(XYStruct position, int fontSize) {

	//Display copyright symbol
	SDL_Rect dRect = { position.x, position.y, fontSize, fontSize };
	SDL_RenderCopy(renderer, spriteSheets[getSpriteSheetIndex("copyright symbol")].texture, NULL, &dRect);

	//Display copyright wording
	renderText("Copyright 2021", defaultFont, defaultColour, { position.x + (fontSize * 2), position.y });

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

void characterActions() {
	for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
		if (controlledCharacterIndex == charactersCnt) {
			characters[charactersCnt].move();
			characters[charactersCnt].jump();
			characters[charactersCnt].jumpOnCollidableObject();
			characters[charactersCnt].jumpOnTile();
			characters[charactersCnt].updateEquippedWeaponAngle();
			characters[charactersCnt].useEquippedWeapon();
			characters[charactersCnt].detectEquippedMeleeWeaponHit();
		}
		else {
			characters[charactersCnt].idleAnimation();
		}
	}
}

void tableActions() {
	for (int tablesCnt = 0; tablesCnt < (int)tables.size(); ++tablesCnt) {
		tables[tablesCnt].markForDestruction();
	}
}

void bulletActions() {
	for (int bulletsCnt = 0; bulletsCnt < (int)bullets.size(); ++bulletsCnt) {
		bullets[bulletsCnt].move();
		bullets[bulletsCnt].markForDestruction();
		bullets[bulletsCnt].ricochetPenetrateOrStayStuck();
		bullets[bulletsCnt].explode();
	}
}

void explosionActions() {
	for (int explosionsCnt = 0; explosionsCnt < (int)explosions.size(); ++explosionsCnt) {
		explosions[explosionsCnt].createFragments();
		explosions[explosionsCnt].explode();
		explosions[explosionsCnt].markForDestruction();
	}
}

int getBulletIndexByID(int ID) {
	for (int bulletsCnt = 0; bulletsCnt < (int)bullets.size(); ++bulletsCnt) {
		if (bullets[bulletsCnt].getID() == ID) {
			return bulletsCnt;
		}
	}

	return -1;
}

void destroyBullets() {
	for (int bulletsToDestroyIDsCnt = 0; bulletsToDestroyIDsCnt < (int)bulletsToDestroyIDs.size(); ++bulletsToDestroyIDsCnt) {
		int bulletIndex = getBulletIndexByID(bulletsToDestroyIDs[bulletsToDestroyIDsCnt]);
		if (bulletIndex > -1) {
			bullets.erase(bullets.begin() + bulletIndex);
		}
	}

	bulletsToDestroyIDs.clear();
}

int getExplosionIndexByID(int ID) {
	for (int explosionsCnt = 0; explosionsCnt < (int)explosions.size(); ++explosionsCnt) {
		if (explosions[explosionsCnt].getID() == ID) {
			return explosionsCnt;
		}
	}

	return -1;
}

void destroyExplosions() {
	for (int explosionsToDestroyIDsCnt = 0 ; explosionsToDestroyIDsCnt < (int)explosionsToDestroyIDs.size(); ++explosionsToDestroyIDsCnt) {
		int explosionIndex = getExplosionIndexByID(explosionsToDestroyIDs[explosionsToDestroyIDsCnt]);
		if (explosionIndex > -1) {
			explosions.erase(explosions.begin() + explosionIndex);
		}
	}

	explosionsToDestroyIDs.clear();
}

void renderShadow(SDL_Rect dRect, int transparencyPercentage) {

	/*Update transparencyPercentage based on how lit up the area is.
	The more light in an area, the darker the shadow. The less light, the lighter the shadow.*/
	//;;

	//Render shadow
	SDL_Rect sRect = shadowSprite.sRect;
	setSDLTextureTransparency(spriteSheets[shadowSprite.spriteSheetIndex].texture, transparencyPercentage);
	SDL_RenderCopy(renderer, spriteSheets[shadowSprite.spriteSheetIndex].texture, &sRect, &dRect);

}

const double convertCoordinatesToAngle(int x, int y) {
	return (atan2(y, x)) * (180 / M_PI);
}

XYStruct convertAngleToCoordinates(double angle, int radius) {
	XYStruct coordinates = { -1, -1 };
	coordinates.x = (int)(radius * cos(angle));
	coordinates.y = (int)(radius * sin(angle));
	return coordinates;
}

vector<int> getBulletIDs() {
	vector<int> bulletIDs;

	for (int bulletsCnt = 0; bulletsCnt < (int)bullets.size(); ++bulletsCnt) {
		bulletIDs.push_back(bullets[bulletsCnt].getID());
	}

	return bulletIDs;
}

void initBullet(bulletParamsStruct newParams) {
	Bullet newBullet(newParams);
	bullets.push_back(newBullet);
}

void setStuckBulletsFadeOut() {
	if ((int)bullets.size() > maxStuckBullets) {

		//If earliest bullet is not fading out then set bullet fade out
		if (bullets[0].getFadeOut().delay == 0) {
			delayStruct newFadeOut;
			newFadeOut.startTicks = SDL_GetTicks();
			newFadeOut.delay = 2000;
			bullets[0].setFadeOut(newFadeOut);
		}

	}
}

void setExplosionsFadeOut() {
	if ((int)explosions.size() > maxExplosions) {

		//If earliest explosion is not fading out then set fade out
		if (explosions[0].getFadeOut().delay == 0) {
			delayStruct newFadeOut;
			newFadeOut.startTicks = SDL_GetTicks();
			newFadeOut.delay = 2000;
			explosions[0].setFadeOut(newFadeOut);
		}

	}
}

void initExplosion(explosionParamsStruct newParams) {
	Explosion newExplosion(newParams);
	explosions.push_back(newExplosion);
}

vector<int> getExplosionIDs() {
	vector<int> explosionIDs;

	for (int explosionsCnt = 0; explosionsCnt < (int)explosions.size(); ++explosionsCnt) {
		explosionIDs.push_back(explosions[explosionsCnt].getID());
	}

	return explosionIDs;
}

void initSplatter(explosionParamsStruct explosionParams, spriteStruct splatterSprite, areaStruct impactArea) {
	explosionParamsStruct newSplatter;

	newSplatter = explosionParams;
	newSplatter.ID = getFreeID(getExplosionIDs());
	newSplatter.sprite = splatterSprite;
	newSplatter.sprite.angle = explosionParams.sprite.angle;

	if (impactArea.x > -1 && impactArea.y > -1) {
		newSplatter.collisionData.collidePosition = { impactArea.x, impactArea.y };
	}

	newSplatter.fragmentIsEntireSprite = true;
	newSplatter.totalFragments = { impactArea.w / 2, impactArea.h / 2 };

	newSplatter.enableShadows = false;

	initExplosion(newSplatter);
}

int getCharacterIndexByID(int ID) {
	for (int charactersCnt = 0; charactersCnt < (int)characters.size(); ++charactersCnt) {
		if (characters[charactersCnt].getID() == ID) {
			return charactersCnt;
		}
	}

	return -1;
}

void destroyCharacters() {
	for (int charactersToDestroyIDsCnt = 0; charactersToDestroyIDsCnt < (int)charactersToDestroyIDs.size(); ++charactersToDestroyIDsCnt) {
		int characterIndex = getCharacterIndexByID(charactersToDestroyIDs[charactersToDestroyIDsCnt]);
		if (characterIndex > -1) {
			characters.erase(characters.begin() + characterIndex);
		}
	}

	charactersToDestroyIDs.clear();
}

int getTableIndexByID(int ID) {
	for (int tablesCnt = 0; tablesCnt < (int)tables.size(); ++tablesCnt) {
		if (tables[tablesCnt].getID() == ID) {
			return tablesCnt;
		}
	}

	return -1;
}

void destroyTables() {
	for (int tablesToDestroyIDsCnt = 0; tablesToDestroyIDsCnt < (int)tablesToDestroyIDs.size(); ++tablesToDestroyIDsCnt) {
		int tableIndex = getTableIndexByID(tablesToDestroyIDs[tablesToDestroyIDsCnt]);
		if (tableIndex > -1) {
			tables.erase(tables.begin() + tableIndex);
		}
	}
}

//functions end

//class functions start

Character::Character(characterParams newParams) {
	params = newParams;
};

int Character::getLayer() {
	return params.layer;
}

XYStruct Character::getPosition() {
	return params.position;
}

WHStruct Character::getSize() {
	return params.size;
}

int Character::getCurrentHeight() {
	return params.jump.currentHeight;
}

directionEnum Character::getDirection() {
	return params.direction;
}

int Character::getFrame() {
	return params.frame;
}

characterParams::rangedWeaponStruct::magazineStruct Character::getMagazine() {
	return params.equippedRangedWeapon.magazine;
}

string Character::getEquippedWeaponName() {
	return params.equippedRangedWeapon.name;
}

int Character::getID() {
	return params.ID;
}

int Character::getResistance() {
	return params.resistance;
}

void Character::setResistance(int newResistance) {
	params.resistance = newResistance;
}

int Character::getStuckTolerancePercentage() {
	return params.stuckTolerancePercentage;
}

int Character::getCharacterSpriteSheetIndex() {
	return params.sprites.spriteSheetIndex;
}

areaStruct Character::getSpriteSheetArea(directionEnum direction, int frame) {
	return params.sprites.areas[(int)direction][frame];
}

bool Character::getDisplaySprites() {
	return params.displaySprites;
}

void Character::setDisplaySprites(bool newDisplaySprites) {
	params.displaySprites = newDisplaySprites;
}

void Character::setDestroy(bool newDestroy) {
	params.destroy = newDestroy;
}

vector<int> Character::getBulletsFiredIDs() {
	return params.bulletsFiredIDs;
}

void Character::render() {
	if (params.displaySprites == true) {

		//Render shadow
		WHStruct shadowSize = { params.size.w, params.size.h / 5 };
		XYStruct shadowPosition = { params.position.x - camera.area.x, ((params.position.y - camera.area.y) + params.size.h - 1) - shadowSize.h - params.shadowHeight };
		if (areaWithinCameraView({ shadowPosition.x + camera.area.x, shadowPosition.y + camera.area.y, shadowSize.w, shadowSize.h }) == true) {
			renderShadow({ shadowPosition.x, shadowPosition.y, shadowSize.w, shadowSize.h }, 50);
		}

		//Render character
		if (areaWithinCameraView({ params.position.x, params.position.y - params.jump.currentHeight, params.size.w, params.size.h }) == true) {
			SDL_Rect sRect = convertAreaToSDLRect(params.sprites.areas[(int)params.direction][params.frame]);
			SDL_Rect dRect = { params.position.x - camera.area.x, params.position.y - camera.area.y - params.jump.currentHeight, params.size.w, params.size.h };
			SDL_RenderCopy(renderer, spriteSheets[params.sprites.spriteSheetIndex].texture, &sRect, &dRect);
		}

	}
}

void Character::updateEquippedWeaponAngle() {
	switch (params.equippedWeaponType) {
		case characterParams::equippedWeaponTypeEnum::ranged: {
			if (rightStickXDir != 0 || rightStickYDir != 0) {
				params.equippedRangedWeapon.sprite.angle = convertCoordinatesToAngle(rightJoystickAxisY, rightJoystickAxisX);
			}
			else if (xDir != 0 || yDir != 0) {
				params.equippedRangedWeapon.sprite.angle = convertCoordinatesToAngle(xDir, yDir);
			}
			break;
		}
		case characterParams::equippedWeaponTypeEnum::melee: {
			if (params.equippedMeleeWeapon.swing.swinging == false) {
				if (rightStickXDir != 0 || rightStickYDir != 0) {
					params.equippedMeleeWeapon.sprite.angle = convertCoordinatesToAngle(rightJoystickAxisY, rightJoystickAxisX);
				}
				else if (xDir != 0 || yDir != 0) {
					params.equippedMeleeWeapon.sprite.angle = convertCoordinatesToAngle(xDir, yDir);
				}
			}
			break;
		}
	}
}

void Character::renderEquippedWeapon() {
	if (params.displaySprites == true) {
		switch (params.equippedWeaponType) {
			case characterParams::equippedWeaponTypeEnum::ranged: {

				//Update position
				params.equippedRangedWeapon.position = { params.position.x + (params.size.w / 2), params.position.y - params.jump.currentHeight + (params.size.h / 2) - (params.equippedRangedWeapon.sprite.areas[0][0].h / 2) };

				//Get weapon angle
				/*if (rightStickXDir != 0 || rightStickYDir != 0) {
					params.equippedRangedWeapon.sprite.angle = convertCoordinatesToAngle(rightJoystickAxisY, rightJoystickAxisX);
				}
				else if (xDir != 0 || yDir != 0) {
					params.equippedRangedWeapon.sprite.angle = convertCoordinatesToAngle(xDir, yDir);
				}*/

				//Flip weapon and adjust position
				if (params.equippedRangedWeapon.sprite.angle >= -90 && params.equippedRangedWeapon.sprite.angle <= 90) {

					//Weapon is facing right
					params.equippedRangedWeapon.sprite.flip = SDL_RendererFlip::SDL_FLIP_NONE;

				}
				else {

					//Weapon is facing left
					params.equippedRangedWeapon.sprite.flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;

				}

				//Render
				SDL_Rect sRect = convertAreaToSDLRect(params.equippedRangedWeapon.sprite.areas[0][0]);
				SDL_Rect dRect = { params.equippedRangedWeapon.position.x - camera.area.x, params.equippedRangedWeapon.position.y - camera.area.y, params.equippedRangedWeapon.size.w, params.equippedRangedWeapon.size.h };
				if (areaWithinCameraView({ params.equippedRangedWeapon.position.x, params.equippedRangedWeapon.position.y, params.equippedRangedWeapon.size.w, params.equippedRangedWeapon.size.h }) == true) {
					SDLRenderCopyEx(sRect, dRect, params.equippedRangedWeapon.sprite);
				}

				break;
			}
			case characterParams::equippedWeaponTypeEnum::melee: {

				//Update position
				params.equippedMeleeWeapon.previousPosition = params.equippedMeleeWeapon.position;
				params.equippedMeleeWeapon.position = { params.position.x + (params.size.w / 2), params.position.y - params.jump.currentHeight + (params.size.h / 2) - (params.equippedMeleeWeapon.sprite.areas[0][0].h / 2) };

				//Get weapon angle
				/*if (params.equippedMeleeWeapon.swing.swinging == false) {
					if (rightStickXDir != 0 || rightStickYDir != 0) {
						params.equippedMeleeWeapon.sprite.angle = convertCoordinatesToAngle(rightJoystickAxisY, rightJoystickAxisX);
					}
					else if (xDir != 0 || yDir != 0) {
						params.equippedMeleeWeapon.sprite.angle = convertCoordinatesToAngle(xDir, yDir);
					}
				}*/

				//Flip weapon and adjust position
				if (params.equippedMeleeWeapon.sprite.angle >= -90 && params.equippedMeleeWeapon.sprite.angle <= 90) {

					//Weapon is facing right
					params.equippedMeleeWeapon.sprite.flip = SDL_RendererFlip::SDL_FLIP_NONE;

				}
				else {

					//Weapon is facing left
					params.equippedMeleeWeapon.sprite.flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;

				}

				//Render
				SDL_Rect sRect = convertAreaToSDLRect(params.equippedMeleeWeapon.sprite.areas[0][0]);
				SDL_Rect dRect = { params.equippedMeleeWeapon.position.x - camera.area.x, params.equippedMeleeWeapon.position.y - camera.area.y - params.jump.currentHeight, params.equippedMeleeWeapon.size.w, params.equippedMeleeWeapon.size.h };
				if (areaWithinCameraView({ params.equippedMeleeWeapon.position.x, params.equippedMeleeWeapon.position.y - params.jump.currentHeight, params.equippedMeleeWeapon.size.w, params.equippedMeleeWeapon.size.h }) == true) {

					//Update weapon angle
					if (params.equippedMeleeWeapon.swing.swinging == true) {
						params.equippedMeleeWeapon.sprite.angle = params.equippedMeleeWeapon.swing.currentAngle;
					}

					SDLRenderCopyEx(sRect, dRect, params.equippedMeleeWeapon.sprite);
				}

				break;
			}
		}
	}
}

void Character::renderReloadAnimation() {
	if (params.equippedRangedWeapon.reload.reloading == true) {

		//Position animation on top of character
		areaStruct reloadAnimationArea = { params.position.x, params.position.y - params.jump.currentHeight, params.size.w, params.size.h / 6 };
		if (areaWithinCameraView(reloadAnimationArea) == true) {

			//Render background bar
			SDL_Rect backgroundSRect = { convertAreaToSDLRect(params.equippedRangedWeapon.reload.sprite.areas[0][0]) };
			SDL_Rect backgroundDRect = { reloadAnimationArea.x - camera.area.x, reloadAnimationArea.y - camera.area.y, reloadAnimationArea.w, 3 };
			//SDL_RenderCopy(renderer, spriteSheets[params.equippedRangedWeapon.reload.sprite.spriteSheetIndex].texture, &backgroundSRect, &backgroundDRect);
			colourStruct newColour = { 255, 255, 255, 255 };
			setSDLDrawColour(newColour);
			SDL_RenderDrawLine(renderer, backgroundDRect.x, backgroundDRect.y - 1, backgroundDRect.x, backgroundDRect.y + 1); //left vertical bar
			SDL_RenderDrawLine(renderer, backgroundDRect.x, backgroundDRect.y, backgroundDRect.x + backgroundDRect.w - 1, backgroundDRect.y); //horizontal bar
			SDL_RenderDrawLine(renderer, backgroundDRect.x + backgroundDRect.w, backgroundDRect.y - 1, backgroundDRect.x + backgroundDRect.w, backgroundDRect.y + 1); //right vertical bar

			//Render foreground bar
			SDL_Rect foregroundSRect = { convertAreaToSDLRect(params.equippedRangedWeapon.reload.sprite.areas[0][1]) };
			int delayPercentage = (int)(((SDL_GetTicks() - params.equippedRangedWeapon.reload.delay.startTicks) * 100) / params.equippedRangedWeapon.reload.delay.delay);
			SDL_Rect foregroundDRect = { reloadAnimationArea.x - camera.area.x, reloadAnimationArea.y + 1 - camera.area.y, (reloadAnimationArea.w * delayPercentage) / 100, 1 };
			//SDL_RenderCopy(renderer, spriteSheets[params.equippedRangedWeapon.reload.sprite.spriteSheetIndex].texture, &foregroundSRect, &foregroundDRect);
			SDL_RenderDrawLine(renderer, foregroundDRect.x + foregroundDRect.w - 1, foregroundDRect.y - 3, foregroundDRect.x + foregroundDRect.w - 1, foregroundDRect.y + 1);

		}

	}
}

void Character::swapFrame() {
	if (SDL_GetTicks() - params.move.frameSwap.startTicks >= params.move.frameSwap.delay / FPSTimerMod) {
		params.move.frameSwap.startTicks = SDL_GetTicks();
		if (params.frame < (int)params.sprites.areas[(int)params.direction].size() - 1) {
			++params.frame;
		}
		else {
			params.frame = 0;
		}
	}
}

void Character::move() {
	if (SDL_GetTicks() - params.move.speed.startTicks >= params.move.speed.delay / FPSTimerMod) {
		params.move.speed.startTicks = SDL_GetTicks();

		//Define move pixel increment based on how far left stick is tilted
		if (abs(joystickAxisX) > ((joystickAxisMaxValue - deadZone) / 6) * 5 || abs(joystickAxisY) > ((joystickAxisMaxValue - deadZone) / 6) * 5) {
			params.move.pixelIncrement = 2;
		}
		else {
			params.move.pixelIncrement = 1;
		}

		bool positionUpdated = false;

		//Left
		if (xDir == -1) {
			params.direction = directionEnum::left;
			params.position.x -= params.move.pixelIncrement;

			collisionDataStruct collisionData = checkCollisionWithOverworldGridFactoringHeight(getGridAreaFromPixelArea({ params.position.x, params.position.y + (params.size.h / 2), params.size.w, params.size.h / 2 }), { -1, -1, -1 -1 }, params.layer, params.jump.currentHeight);
			if (collisionData.collision == true || checkCollisionWithCollidableObjectFactoringHeight(getGridAreaFromPixelArea({ params.position.x, params.position.y + (params.size.h / 2), params.size.w, params.size.h / 2 }), params.layer, params.jump.currentHeight) == true) {
				/*XYStruct tilePixelPosition = { collisionData.collidePosition.x * tileSize.w, collisionData.collidePosition.y * tileSize.h };
				params.position.x = tilePixelPosition.x + tileSize.w;*/
				params.position.x += params.move.pixelIncrement;
			}

			positionUpdated = true;
		}

		//Right
		if (xDir == 1) {
			params.direction = directionEnum::right;
			params.position.x += params.move.pixelIncrement;

			collisionDataStruct collisionData = checkCollisionWithOverworldGridFactoringHeight(getGridAreaFromPixelArea({ params.position.x, params.position.y + (params.size.h / 2), params.size.w, params.size.h / 2 }), { -1, -1, -1 - 1 }, params.layer, params.jump.currentHeight);
			if (collisionData.collision == true || checkCollisionWithCollidableObjectFactoringHeight(getGridAreaFromPixelArea({ params.position.x, params.position.y + (params.size.h / 2), params.size.w, params.size.h / 2 }), params.layer, params.jump.currentHeight) == true) {
				/*XYStruct tilePixelPosition = { collisionData.collidePosition.x * tileSize.w, collisionData.collidePosition.y * tileSize.h };
				params.position.x = tilePixelPosition.x - params.size.w;*/
				params.position.x -= params.move.pixelIncrement;
			}

			positionUpdated = true;
		}

		//Up
		if (yDir == -1) {
			params.direction = directionEnum::up;
			params.position.y -= params.move.pixelIncrement;
			
			collisionDataStruct collisionData = checkCollisionWithOverworldGridFactoringHeight(getGridAreaFromPixelArea({ params.position.x, params.position.y + (params.size.h / 2), params.size.w, params.size.h / 2 }), { -1, -1, -1 - 1 }, params.layer, params.jump.currentHeight);
			if (collisionData.collision == true || checkCollisionWithCollidableObjectFactoringHeight(getGridAreaFromPixelArea({ params.position.x, params.position.y + (params.size.h / 2), params.size.w, params.size.h / 2 }), params.layer, params.jump.currentHeight) == true) {
				/*XYStruct tilePixelPosition = { collisionData.collidePosition.x * tileSize.w, collisionData.collidePosition.y * tileSize.h };
				params.position.y = tilePixelPosition.y + tileSize.h;*/
				params.position.y += params.move.pixelIncrement;
			}

			positionUpdated = true;
		}

		//Down
		if (yDir == 1) {
			params.direction = directionEnum::down;
			params.position.y += params.move.pixelIncrement;
			
			collisionDataStruct collisionData = checkCollisionWithOverworldGridFactoringHeight(getGridAreaFromPixelArea({ params.position.x, params.position.y + (params.size.h / 2), params.size.w, params.size.h / 2 }), { -1, -1, -1 - 1 }, params.layer, params.jump.currentHeight);
			if (collisionData.collision == true || checkCollisionWithCollidableObjectFactoringHeight(getGridAreaFromPixelArea({ params.position.x, params.position.y + (params.size.h / 2), params.size.w, params.size.h / 2 }), params.layer, params.jump.currentHeight) == true) {
				/*XYStruct tilePixelPosition = { collisionData.collidePosition.x * tileSize.w, collisionData.collidePosition.y * tileSize.h };
				params.position.y = tilePixelPosition.y - params.size.h;*/
				params.position.y -= params.move.pixelIncrement;
			}

			positionUpdated = true;
		}

		//Up-right
		if (yDir == -1 && xDir == 1) {
			params.direction = directionEnum::upRight;
		}

		//Down-right
		if (yDir == 1 && xDir == 1) {
			params.direction = directionEnum::downRight;
		}

		//Down-left
		if (yDir == 1 && xDir == -1) {
			params.direction = directionEnum::downLeft;
		}

		//Up-left
		if (yDir == -1 && xDir == -1) {
			params.direction = directionEnum::upLeft;
		}

		//Face where weapon is aimed if aiming weapon
		if (rightStickYDir != 0 || rightStickXDir != 0) {
			int angle = 0;
			switch (params.equippedWeaponType) {
				case characterParams::equippedWeaponTypeEnum::ranged: {
					angle = (int)params.equippedRangedWeapon.sprite.angle;
					break;
				}
				case characterParams::equippedWeaponTypeEnum::melee: {
					angle = (int)params.equippedMeleeWeapon.sprite.angle;
					break;
				}
			}
			int selectionAngle = 45, halfSelectionAngle = selectionAngle / 2;
			if (angle >= -90 - halfSelectionAngle && angle <= -90 + halfSelectionAngle) {
				params.direction = directionEnum::up;
			}
			else if (angle >= 90 - halfSelectionAngle && angle <= 90 + halfSelectionAngle) {
				params.direction = directionEnum::down;
			}
			else if ((angle >= -180 && angle <= -180 + halfSelectionAngle) || (angle >= 180 - halfSelectionAngle && angle <= 180)) {
				params.direction = directionEnum::left;
			}
			else if (angle >= -halfSelectionAngle && angle <= halfSelectionAngle) {
				params.direction = directionEnum::right;
			}
			else if (angle >= -90 - halfSelectionAngle - selectionAngle && angle <= -90 - halfSelectionAngle) {
				params.direction = directionEnum::upLeft;
			}
			else if (angle >= -90 + halfSelectionAngle && angle <= -90 + halfSelectionAngle + selectionAngle) {
				params.direction = directionEnum::upRight;
			}
			else if (angle >= 90 + halfSelectionAngle && angle <= 90 + halfSelectionAngle + selectionAngle) {
				params.direction = directionEnum::downLeft;
			}
			else if (angle >= 90 - halfSelectionAngle - selectionAngle && angle <= 90 - halfSelectionAngle) {
				params.direction = directionEnum::downRight;
			}
		}

		//Swap frame and centre camera
		if (positionUpdated == true) {
			if (params.jump.jumping == false) {
				swapFrame();
			}
			//centreCamera({ params.position.x, params.position.y, params.size.w, params.size.h }, params.layer);
		}

		//Reset 
		if (xDir != 0 || yDir != 0) {
			params.idleAnimation.animationRunning = false;
			params.idleAnimation.delayBeforeAnimation.startTicks = SDL_GetTicks();
		}

	}
}

void Character::idleAnimation() {
	
	//Check if need to run idle animation
	if (xDir == 0 && yDir == 0 && params.idleAnimation.animationRunning == false && SDL_GetTicks() - params.idleAnimation.delayBeforeAnimation.startTicks >= params.idleAnimation.delayBeforeAnimation.delay / FPSTimerMod) {
		params.idleAnimation.animationRunning = true;
		params.idleAnimation.frameDuration.startTicks = SDL_GetTicks();
		params.idleAnimation.frameDuration.delay = randInt(1, 2) * 1000;

		//Get random direction
		params.direction = (directionEnum)randInt(0, 7);

	}

	//Run idle animation
	if (params.idleAnimation.animationRunning == true && SDL_GetTicks() - params.idleAnimation.frameDuration.startTicks >= params.idleAnimation.frameDuration.delay / FPSTimerMod) {
		params.idleAnimation.frameDuration.startTicks = SDL_GetTicks();
		params.idleAnimation.frameDuration.delay = randInt(1, 2) * 1000;

		//Get random direction
		params.direction = (directionEnum)randInt(0, 7);

	}

}

void Character::jump() {
	if (controllerButtons.A == true && params.jump.jumping == false) {
		params.jump.jumping = true;
		params.jump.move.startTicks = SDL_GetTicks();
		params.jump.direction = directionEnum::up;
		params.jump.jumpButtonPress.startTicks = SDL_GetTicks();
		params.jump.maxHeight = (params.size.h / 2) + params.jump.currentHeight;
	}

	//If A is pressed for longer the character jumps higher
	if (controllerButtons.A == true && SDL_GetTicks() - params.jump.jumpButtonPress.startTicks > params.jump.jumpButtonPress.delay / FPSTimerMod) {
		params.jump.jumpButtonPress.startTicks = SDL_GetTicks();
		params.jump.addedMaxHeight = params.size.h / 2;
	}

	//Reset added max height
	if (controllerButtons.A == false && params.jump.addedMaxHeight > 0) {
		params.jump.addedMaxHeight = 0;
	}

	if (params.jump.jumping == true && SDL_GetTicks() - params.jump.move.startTicks > params.jump.move.delay / FPSTimerMod) {
		params.jump.move.startTicks = SDL_GetTicks();
		
		switch (params.jump.direction) {
			case directionEnum::up: {
				if (params.jump.currentHeight < params.jump.maxHeight + params.jump.addedMaxHeight) {
					params.jump.currentHeight += params.jump.pixelIncrement;
					if (params.jump.currentHeight > params.jump.maxHeight + params.jump.addedMaxHeight) {
						params.jump.currentHeight = params.jump.maxHeight + params.jump.addedMaxHeight;
					}
				}
				else {
					params.jump.direction = directionEnum::down;
				}
				break;
			}
			case directionEnum::down: {
				if (params.jump.currentHeight > 0) {
					params.jump.currentHeight -= params.jump.pixelIncrement;
					if (params.jump.currentHeight < 0) {
						params.jump.currentHeight = 0;
					}
				}
				else {
					params.jump.jumping = false;
					controllerButtons.A = false;
				}
				break;
			}
		}
	}
}

void Character::jumpOnCollidableObject() {
	if (params.jump.onTileObject == false) {

		//Check if character in collision with jumpable object
		params.jump.onObject = false;
		bool collidedWithObject = false;
		for (int collidableObjectsCnt = 0; collidableObjectsCnt < (int)collidableObjects.size(); ++collidableObjectsCnt) {

			//If character is on top of object
			if (checkCollisionWithCollidableObject(getGridAreaFromPixelArea({ params.position.x, params.position.y + (params.size.h / 2), params.size.w, params.size.h / 2 }), params.layer) == true) {
				if (params.jump.direction == directionEnum::down && params.jump.currentHeight > 0 && params.jump.currentHeight <= collidableObjects[collidableObjectsCnt].height) {

					//Stop jumping
					params.jump.jumping = false;

					params.jump.currentHeight = collidableObjects[collidableObjectsCnt].height;
					params.jump.onObject = true;
					params.shadowHeight = params.jump.currentHeight;
					break;
				}
				else {
					collidedWithObject = true;
				}
			}

			//Set shadow height to 0 if no collision with tile object underneath character
			if (checkCollisionWithCollidableObject(getGridAreaFromPixelArea({ params.position.x, params.position.y + (params.size.h / 2) + params.jump.currentHeight, params.size.w, params.size.h / 2 }), params.layer) == false && params.shadowHeight > 0) {
				params.shadowHeight = 0;
			}

		}

		//Fall
		if (params.jump.onObject == false && params.jump.jumping == false && params.jump.currentHeight > 0 && collidedWithObject == false) {
			params.jump.jumping = true;
			params.shadowHeight = 0;
		}

	}
}

void Character::jumpOnTile() {
	if (params.jump.onObject == false) {

		//If character in collision with tile object and on top of object
		params.jump.onTileObject = false;
		bool collidedWithObject = false;
		collisionDataStruct collisionData = checkCollisionWithOverworldGrid(getGridAreaFromPixelArea({ params.position.x, params.position.y + (params.size.h / 2), params.size.w, params.size.h / 2 }), params.layer);
		if (collisionData.collision == true) {
			if (params.jump.direction == directionEnum::down && params.jump.currentHeight > 0 && params.jump.currentHeight <= overworldGrid.gridTile[params.layer][collisionData.collidePosition.x][collisionData.collidePosition.y].height) {

				//Stop jumping
				params.jump.jumping = false;

				params.jump.currentHeight = overworldGrid.gridTile[params.layer][collisionData.collidePosition.x][collisionData.collidePosition.y].height;
				params.jump.onTileObject = true;
				params.shadowHeight = params.jump.currentHeight;
			}
			else {
				collidedWithObject = true;
			}
		}

		//Fall
		if (params.jump.onTileObject == false && params.jump.jumping == false && params.jump.currentHeight > 0 && collidedWithObject == false) {
			params.jump.jumping = true;
			params.shadowHeight = 0;
		}

		//Set shadow height to 0 if no collision with tile object underneath character
		collisionDataStruct underCharacterCollisionData = checkCollisionWithOverworldGrid(getGridAreaFromPixelArea({ params.position.x, params.position.y + (params.size.h / 2) + params.jump.currentHeight, params.size.w, params.size.h / 2 }), params.layer);
		if (underCharacterCollisionData.collision == false && params.shadowHeight > 0) {
			params.shadowHeight = 0;
		}

	}
}

void Character::useEquippedWeapon() {

	//Use equipped weapon
	if (controllerButtons.RB == true) {
		if (params.equippedRangedWeapon.fireMode == characterParams::rangedWeaponStruct::fireModeEnum::semiAuto) {
			controllerButtons.RB = false;
		}

		switch (params.equippedWeaponType) {
			case characterParams::equippedWeaponTypeEnum::ranged: {
				if (params.equippedRangedWeapon.magazine.currentLoad > 0 && params.equippedRangedWeapon.reload.reloading == false) {

					if (params.equippedRangedWeapon.fireMode != characterParams::rangedWeaponStruct::fireModeEnum::burst || (params.equippedRangedWeapon.fireMode == characterParams::rangedWeaponStruct::fireModeEnum::burst && params.equippedRangedWeapon.burst.pause == false)) {
						
						//Fire bullet
						bulletParamsStruct bulletParams;
						bulletParams.ID = getFreeID(getBulletIDs());
						bulletParams.layer = params.layer;
						bulletParams.height = params.jump.currentHeight;
						bulletParams.position = { params.position.x + (params.size.w / 2), params.position.y + (params.size.h / 2) - params.jump.currentHeight };
						bulletParams.originalPosition = bulletParams.position;
						int characterIndex = getCharacterIndexByID(params.ID);
						XYStruct characterPosition = characters[characterIndex].getPosition();
						WHStruct characterSize = characters[characterIndex].getSize();
						bulletParams.shadowHeight = (characterPosition.y + characterSize.h) - bulletParams.position.y;
						//bulletParams.size = { tileSize.w / 2, tileSize.h / 2 };
						bulletParams.size = tileSize;
						bulletParams.sprite.spriteSheetIndex = getSpriteSheetIndex("bullets");
						bulletParams.sprite.areas = {
							{
								{ 11, 360, 16, 16 }
							}
						};
						bulletParams.sprite.angle = params.equippedRangedWeapon.sprite.angle;
						bulletParams.speed.startTicks = SDL_GetTicks();
						bulletParams.speed.delay = 1;
						bulletParams.movePixelIncrement = 6;
						bulletParams.damage = 90;
						bulletParams.resistance = 100;
						bulletParams.characterID = params.ID;
						initBullet(bulletParams);

						params.bulletsFiredIDs.push_back(bulletParams.ID);

						//Update magazin current load
						if (params.equippedRangedWeapon.magazine.currentLoad > 0) {
							--params.equippedRangedWeapon.magazine.currentLoad;
						}

					}

					//Make weapon fire in bursts
					if (params.equippedRangedWeapon.fireMode == characterParams::rangedWeaponStruct::fireModeEnum::burst) {
						if (params.equippedRangedWeapon.burst.pause == false) {
							if (params.equippedRangedWeapon.burst.bulletsFired < params.equippedRangedWeapon.burst.maxBulletsBeforePause) {
								++params.equippedRangedWeapon.burst.bulletsFired;
							}
							else {
								params.equippedRangedWeapon.burst.pause = true;
								params.equippedRangedWeapon.burst.delay.startTicks = SDL_GetTicks();
							}
						}
						else if (SDL_GetTicks() - params.equippedRangedWeapon.burst.delay.startTicks >= params.equippedRangedWeapon.burst.delay.delay / FPSTimerMod) {
							params.equippedRangedWeapon.burst.pause = false;
							params.equippedRangedWeapon.burst.bulletsFired = 0;
						}
					}

				}
				break;
			}
			case characterParams::equippedWeaponTypeEnum::melee: {
				if (params.equippedMeleeWeapon.swing.swinging == false) {
					params.equippedMeleeWeapon.swing.swinging = true;
					params.equippedMeleeWeapon.swing.originalAngle = params.equippedMeleeWeapon.sprite.angle;
					params.equippedMeleeWeapon.swing.startAngle = (int)params.equippedMeleeWeapon.sprite.angle - (params.equippedMeleeWeapon.swing.angle / 2);
					params.equippedMeleeWeapon.swing.endAngle = params.equippedMeleeWeapon.swing.startAngle + params.equippedMeleeWeapon.swing.angle;
					params.equippedMeleeWeapon.swing.currentAngle = params.equippedMeleeWeapon.swing.startAngle;
					params.equippedMeleeWeapon.swing.delay.startTicks = SDL_GetTicks();
				}
				break;
			}
		}
	}

	//Reload equipped ranged weapon
	if (controllerButtons.X == true && params.equippedRangedWeapon.reload.reloading == false && params.equippedRangedWeapon.magazine.currentLoad < params.equippedRangedWeapon.magazine.capacity) {
		controllerButtons.X = false;
		params.equippedRangedWeapon.reload.reloading = true;
		params.equippedRangedWeapon.reload.delay.startTicks = SDL_GetTicks();
	}
	if (params.equippedRangedWeapon.reload.reloading == true && SDL_GetTicks() - params.equippedRangedWeapon.reload.delay.startTicks >= params.equippedRangedWeapon.reload.delay.delay / FPSTimerMod) {
		params.equippedRangedWeapon.reload.reloading = false;
		params.equippedRangedWeapon.magazine.currentLoad = params.equippedRangedWeapon.magazine.capacity;
	}

	//Swing equipped melee weapon
	if (params.equippedMeleeWeapon.swing.swinging == true && SDL_GetTicks() - params.equippedMeleeWeapon.swing.delay.startTicks >= params.equippedMeleeWeapon.swing.delay.delay / FPSTimerMod) {
		params.equippedMeleeWeapon.swing.delay.startTicks = SDL_GetTicks();
			
		if (params.equippedMeleeWeapon.swing.currentAngle < params.equippedMeleeWeapon.swing.endAngle) {
			params.equippedMeleeWeapon.swing.currentAngle += params.equippedMeleeWeapon.swing.pixelIncrement;
				
			if (params.equippedMeleeWeapon.swing.currentAngle > params.equippedMeleeWeapon.swing.endAngle) {
				params.equippedMeleeWeapon.swing.currentAngle = params.equippedMeleeWeapon.swing.endAngle;
			}
		}
		else {
			params.equippedMeleeWeapon.swing.swinging = false;
			params.equippedMeleeWeapon.sprite.angle = params.equippedMeleeWeapon.swing.originalAngle;
		}
	}

	//Recoil equipped melee weapon
	if (params.equippedMeleeWeapon.swing.recoil == true && SDL_GetTicks() - params.equippedMeleeWeapon.swing.delay.startTicks >= params.equippedMeleeWeapon.swing.delay.delay / FPSTimerMod) {
		params.equippedMeleeWeapon.swing.delay.startTicks = SDL_GetTicks();

		if (params.equippedMeleeWeapon.swing.currentAngle > params.equippedMeleeWeapon.swing.startAngle) {
			params.equippedMeleeWeapon.swing.currentAngle -= params.equippedMeleeWeapon.swing.pixelIncrement;

			if (params.equippedMeleeWeapon.swing.currentAngle < params.equippedMeleeWeapon.swing.startAngle) {
				params.equippedMeleeWeapon.swing.currentAngle = params.equippedMeleeWeapon.swing.startAngle;
			}
		}
		else {
			params.equippedMeleeWeapon.swing.recoil = false;
			params.equippedMeleeWeapon.sprite.angle = params.equippedMeleeWeapon.swing.originalAngle;
		}
	}
}

void Character::markForDestruction() {
	if (params.destroy == true) {
		charactersToDestroyIDs.push_back(params.ID);
	}
}

void Character::detectEquippedMeleeWeaponHit() {
	if (params.equippedMeleeWeapon.swing.swinging == true) {
		collisionDataStruct collisionData = checkCollisionWithCharacter({ params.equippedMeleeWeapon.position.x, params.equippedMeleeWeapon.position.y, params.equippedMeleeWeapon.size.w, params.equippedMeleeWeapon.size.h }, { params.equippedMeleeWeapon.previousPosition.x, params.equippedMeleeWeapon.previousPosition.y, params.equippedMeleeWeapon.size.w, params.equippedMeleeWeapon.size.h });

		if (collisionData.collision == true && collisionData.instanceID != params.ID) {

			//Update equipped melee weapon resistance
			--params.equippedMeleeWeapon.resistance;

			//Get character index
			int characterIndex = getCharacterIndexByID(collisionData.instanceID);

			//If equipped melee weapon damage lower than character resistance then sword recoils
			if (params.equippedMeleeWeapon.damage < characters[characterIndex].getResistance()) {
				params.equippedMeleeWeapon.swing.swinging = false;
				params.equippedMeleeWeapon.swing.recoil = true;
			}

		}
	}
}

Table::Table(tableParamsStruct newParams) {
	params = newParams;
}

void Table::render() {
	if (params.displaySprite == true) {
		SDL_Rect sRect = convertAreaToSDLRect(params.sprite.areas[0][0]);
		SDL_Rect dRect = convertAreaToSDLRect({ params.position.x - camera.area.x, params.position.y - camera.area.y, params.size.w, params.size.h });

		if (areaWithinCameraView({ params.position.x, params.position.y, params.size.w, params.size.h }) == true) {
			SDL_RenderCopy(renderer, spriteSheets[params.sprite.spriteSheetIndex].texture, &sRect, &dRect);
		}
	}
}

int Table::getLayer() {
	return params.layer;
}

XYStruct Table::getPosition() {
	return params.position;
}

WHStruct Table::getSize() {
	return params.size;
}

int Table::getID() {
	return params.ID;
}

int Table::getHeight() {
	return params.height;
}

int Table::getResistance() {
	return params.resistance;
}

void Table::setResistance(int newResistance) {
	params.resistance = newResistance;
}

int Table::getStuckTolerancePercentage() {
	return params.stuckTolerancePercentage;
}

int Table::getTableSpriteSheetIndex() {
	return params.sprite.spriteSheetIndex;
}

areaStruct Table::getSpriteSheetArea() {
	return params.sprite.areas[0][0];
}

void Table::setDisplaySprites(bool newDisplaySprite) {
	params.displaySprite = newDisplaySprite;
}

void Table::setDestroy(bool newDestroy) {
	params.destroy = newDestroy;
}

void Table::markForDestruction() {
	if (params.destroy == true) {
		tablesToDestroyIDs.push_back(params.ID);
	}
}

Bullet::Bullet(bulletParamsStruct newParams) {
	params = newParams;
}

int Bullet::getID() {
	return params.ID;
}

int Bullet::getLayer() {
	return params.layer;
}

XYStruct Bullet::getPosition() {
	return params.position;
}

WHStruct Bullet::getSize() {
	return params.size;
}

int Bullet::getResistance() {
	return params.resistance;
}

void Bullet::setResistance(int newResistance) {
	params.resistance = newResistance;
}

int Bullet::getStuckTolerancePercentage() {
	return params.stuckTolerancePercentage;
}

int Bullet::getBulletSpriteSheetIndex() {
	return params.sprite.spriteSheetIndex;
}

areaStruct Bullet::getSpriteSheetArea() {
	return params.sprite.areas[0][0];
}

void Bullet::setDisplaySprite(bool newDisplaySprite) {
	params.displaySprite = newDisplaySprite;
}

void Bullet::setDestroy(bool newDestroy) {
	params.destroy = newDestroy;
}

int Bullet::getCharacterID() {
	return params.characterID;
}

delayStruct Bullet::getFadeOut() {
	return params.fadeOut;
}

void Bullet::setFadeOut(delayStruct newFadeOut) {
	params.fadeOut = newFadeOut;
}

bool Bullet::getStuck() {
	return params.stuck;
}

void Bullet::render() {
	if (params.displaySprite == true) {
		SDL_Rect sRect = convertAreaToSDLRect(params.sprite.areas[0][0]);
		SDL_Rect dRect = { params.position.x - camera.area.x, params.position.y - camera.area.y - params.height, params.size.w, params.size.h };

		if (areaWithinCameraView({ params.position.x, params.position.y - params.height, params.size.w, params.size.h }) == true && params.displaySprite == true) {
			
			//Set transparency
			int percentageTimePassed = 0;
			if (params.fadeOut.delay > 0) {
				percentageTimePassed = ((SDL_GetTicks() - params.fadeOut.startTicks) * 100) / params.fadeOut.delay;
				setSDLTextureTransparency(spriteSheets[params.sprite.spriteSheetIndex].texture, 100 - percentageTimePassed);
			}

			//Render shadow
			renderShadow({ dRect.x, dRect.y + params.shadowHeight, dRect.w, dRect.h / 5 }, 50 - (percentageTimePassed / 2));

			SDLRenderCopyEx(sRect, dRect, params.sprite);

			//Remove transparency
			if (params.fadeOut.delay > 0) {
				setSDLTextureTransparency(spriteSheets[params.sprite.spriteSheetIndex].texture, 100);
			}

		}
	}
}

void Bullet::move() {
	if (params.stuck == false && SDL_GetTicks() - params.speed.startTicks >= params.speed.delay / FPSTimerMod) {
		params.speed.startTicks = SDL_GetTicks();
		params.distanceTravelled += params.movePixelIncrement;
		params.totalDistanceTravelled += params.movePixelIncrement;
		params.previousPosition = params.position;
		params.position = { lround((double)params.originalPosition.x + ((params.distanceTravelled * cos(((params.sprite.angle) * M_PI) / 180)) * params.directionMods.x)), lround((double)params.originalPosition.y + ((params.distanceTravelled * sin(((params.sprite.angle) * M_PI) / 180)) * params.directionMods.y )) };
	}
}

void Bullet::markForDestruction() {

	//If bullet goes outside of overworld grid or destroy = true then destroy it
	/*if (areaWithinArea({ params.position.x, params.position.y - params.height, params.size.w, params.size.h }, { 0, 0, ((int)overworldGrid.gridTile[params.layer].size() - 1) * tileSize.w, ((int)overworldGrid.gridTile[params.layer][0].size() - 1) * tileSize.h }) == false || params.destroy == true) {
		bulletsToDestroyIDs.push_back(params.ID);
	}*/

	if (params.fadeOut.delay > 0 && SDL_GetTicks() - params.fadeOut.startTicks >= params.fadeOut.delay) {
		bulletsToDestroyIDs.push_back(params.ID);
	}

}

void Bullet::ricochet(collisionDataStruct& collisionData) {
	params.originalPosition = params.position;
	params.distanceTravelled = 0;
	if (collisionData.hitCorner == collisionDataStruct::tileHitCornerEnum::left || collisionData.hitCorner == collisionDataStruct::tileHitCornerEnum::right) {
		params.directionMods.x = -1;
	}
	else {
		params.directionMods.y = -1;
	}
}

void Bullet::ricochetPenetrateOrStayStuck() {
	if (params.stuck == false) {

		//Calculate bullet force (the farther the bullet travels, the less damage it does
		int force = params.damage - params.totalDistanceTravelled;
		if (force < 0) {
			force = 0;
		}

		//Check for collision with wall
		collisionDataStruct overworldGridCollisionData = checkCollisionWithOverworldGridFactoringHeight(getGridAreaFromPixelArea({ params.position.x, params.position.y - params.height, params.size.w, params.size.h }), { -1, -1, -1 - 1 }, params.layer, params.height);

		//Check for collision with characters
		collisionDataStruct characterCollisionData = checkCollisionWithCharacter({ params.position.x, params.position.y - params.height, params.size.w, params.size.h }, { params.previousPosition.x, params.previousPosition.y, params.size.w, params.size.h });

		//Check for collision with tables
		collisionDataStruct tableCollisionData = checkCollisionWithTable({ params.position.x, params.position.y - params.height, params.size.w, params.size.h }, { params.previousPosition.x, params.previousPosition.y, params.size.w, params.size.h });

		//Check for collision with other bullets
		collisionDataStruct otherBulletCollisionData = checkCollisionWithBullet({ params.position.x, params.position.y - params.height, params.size.w, params.size.h }, { params.previousPosition.x, params.previousPosition.y, params.size.w, params.size.h });

		//Overworld grid collision
		if (overworldGridCollisionData.collision == true) {

			//Decrease wall resistance by the amount of force that hits it
			overworldGrid.gridTile[params.layer][overworldGridCollisionData.collidePosition.x][overworldGridCollisionData.collidePosition.y].resistance -= force;

			//Decrease bullet resistance
			params.resistance -= force;

			int resistanceTolerance = (overworldGrid.gridTile[params.layer][overworldGridCollisionData.collidePosition.x][overworldGridCollisionData.collidePosition.y].resistance * overworldGrid.gridTile[params.layer][overworldGridCollisionData.collidePosition.x][overworldGridCollisionData.collidePosition.y].stuckTolerancePercentage) / 100;

			//If bullet force is lower than wall resistance - resitance tolerance then bullet ricochet
			if (force < overworldGrid.gridTile[params.layer][overworldGridCollisionData.collidePosition.x][overworldGridCollisionData.collidePosition.y].resistance - resistanceTolerance) {

				//Bullet ricochets
				/*params.originalPosition = params.position;
				params.distanceTravelled = 0;
				if (overworldGridCollisionData.hitCorner == collisionDataStruct::tileHitCornerEnum::left || overworldGridCollisionData.hitCorner == collisionDataStruct::tileHitCornerEnum::right) {
					params.directionMods.x = -1;
				}
				else {
					params.directionMods.y = -1;
				}*/
				ricochet(overworldGridCollisionData);

			}
			else if (force >= overworldGrid.gridTile[params.layer][overworldGridCollisionData.collidePosition.x][overworldGridCollisionData.collidePosition.y].resistance - resistanceTolerance && force <= overworldGrid.gridTile[params.layer][overworldGridCollisionData.collidePosition.x][overworldGridCollisionData.collidePosition.y].resistance + resistanceTolerance) {

				//If bullet force is within range of stuck tolerance percentage of wall resistance then bullet stays stuck
				params.stuck = true;

			}
			//else if (force > overworldGrid.gridTile[params.layer][overworldGridCollisionData.collidePosition.x][overworldGridCollisionData.collidePosition.y].resistance + resistanceTolerance) {
			//	
			//	//If bullet force is greater than wall resistance + resistance tolerance then bullet penetrates
			//	
			//}

			//If resistance of wall <= 0 then explode
			if (overworldGrid.gridTile[params.layer][overworldGridCollisionData.collidePosition.x][overworldGridCollisionData.collidePosition.y].resistance <= 0) {
				explosionParamsStruct newExplosionParams;
				newExplosionParams.ID = getFreeID(getExplosionIDs());
				newExplosionParams.overworldGridLayer = params.layer;
				newExplosionParams.sprite.spriteSheetIndex = tiles[overworldGrid.gridTile[params.layer][overworldGridCollisionData.collidePosition.x][overworldGridCollisionData.collidePosition.y].tileIndex].spriteSheetIndex;
				areaStruct tileArea = tiles[overworldGrid.gridTile[params.layer][overworldGridCollisionData.collidePosition.x][overworldGridCollisionData.collidePosition.y].tileIndex].spriteSheetArea;
				newExplosionParams.sprite.areas = {
					{
						{
							{ tileArea.x, tileArea.y, tileArea.w, tileArea.h }
						}
					}
				};
				newExplosionParams.sprite.angle = params.sprite.angle;
				newExplosionParams.collisionData = overworldGridCollisionData;
				newExplosionParams.collisionData.collidePosition = { newExplosionParams.collisionData.collidePosition.x * tileSize.w, newExplosionParams.collisionData.collidePosition.y * tileSize.h };
				newExplosionParams.force = force;
				newExplosionParams.shadowHeightRandMinMax = { tileSize.h / 2, tileSize.h };
				//newExplosionParams.totalFragments = { randInt(1, newExplosionParams.sprite.areas[0][0].w), randInt(1, newExplosionParams.sprite.areas[0][0].h) };
				newExplosionParams.totalFragments = { newExplosionParams.sprite.areas[0][0].w / 4, newExplosionParams.sprite.areas[0][0].h / 4 };
				initExplosion(newExplosionParams);

				//Remove tile from overworld grid
				gridTileStruct blankTile;
				overworldGrid.gridTile[params.layer][overworldGridCollisionData.collidePosition.x][overworldGridCollisionData.collidePosition.y] = blankTile;

			}

		}

		//Character collision
		if (characterCollisionData.collision == true && characterCollisionData.instanceID != params.characterID && characters[getCharacterIndexByID(characterCollisionData.instanceID)].getDisplaySprites() == true) {

			//Decrease character resistance by the amount of force that hits
			int characterIndex = getCharacterIndexByID(characterCollisionData.instanceID);
			int characterNewResistance = characters[characterIndex].getResistance() - force;
			characters[characterIndex].setResistance(characterNewResistance);

			//Decrease bullet resistance
			params.resistance -= force;

			int resistanceTolerance = (characterNewResistance * characters[characterIndex].getStuckTolerancePercentage()) / 100;

			//If bullet force is lower than character resistance - resitance tolerance then bullet ricochet
			if (force < characterNewResistance - resistanceTolerance) {

				//Bullet ricochets
				/*params.originalPosition = params.position;
				params.distanceTravelled = 0;
				if (overworldGridCollisionData.hitCorner == collisionDataStruct::tileHitCornerEnum::left || overworldGridCollisionData.hitCorner == collisionDataStruct::tileHitCornerEnum::right) {
					params.directionMods.x = -1;
				}
				else {
					params.directionMods.y = -1;
				}*/
				ricochet(characterCollisionData);

			}
			else if (force >= characterNewResistance - resistanceTolerance && force <= characterNewResistance + resistanceTolerance) {

				//If bullet force is within range of stuck tolerance percentage of character resistance then bullet stays stuck
				params.stuck = true;

			}
			//else if (force > characterNewResistance + resistanceTolerance) {
			//	
			//	//If bullet force is greater than character resistance + resistance tolerance then bullet penetrates
			//	
			//}

			//If resistance of character <= 0 then explode
			if (characterNewResistance <= 0) {
				explosionParamsStruct newExplosionParams;
				newExplosionParams.ID = getFreeID(getExplosionIDs());
				newExplosionParams.overworldGridLayer = params.layer;
				newExplosionParams.sprite.spriteSheetIndex = characters[characterIndex].getCharacterSpriteSheetIndex();
				areaStruct characterArea = characters[characterIndex].getSpriteSheetArea(characters[characterIndex].getDirection(), characters[characterIndex].getFrame());
				newExplosionParams.sprite.areas = {
					{
						{
							{ characterArea.x, characterArea.y, characterArea.w, characterArea.h }
						}
					}
				};
				newExplosionParams.sprite.angle = params.sprite.angle;
				newExplosionParams.collisionData = characterCollisionData;
				newExplosionParams.force = force;
				int characterHeight = characters[characterIndex].getSize().h;
				newExplosionParams.shadowHeightRandMinMax = { characterHeight / 2, characterHeight };
				//newExplosionParams.totalFragments = { randInt(1, newExplosionParams.sprite.areas[0][0].w), randInt(1, newExplosionParams.sprite.areas[0][0].h) };
				newExplosionParams.totalFragments = { newExplosionParams.sprite.areas[0][0].w / 4, newExplosionParams.sprite.areas[0][0].h / 4 };
				initExplosion(newExplosionParams);
				initSplatter(newExplosionParams, bloodSplatterSprite, { params.position.x, params.position.y, params.size.w, params.size.h });

				//Disable character sprite display
				characters[characterIndex].setDisplaySprites(false);
				characters[characterIndex].setDestroy(true);

			}

		}

		//Table collision
		if (tableCollisionData.collision == true) {

			//Decrease table resistance by the amount of force that hits
			int tableIndex = getTableIndexByID(tableCollisionData.instanceID);
			int newTableResistance = tables[tableIndex].getResistance() - force;
			tables[tableIndex].setResistance(newTableResistance);

			//Decrease bullet resistance
			params.resistance -= force;

			int resistanceTolerance = (newTableResistance * tables[tableIndex].getStuckTolerancePercentage()) / 100;

			//If bullet force is lower than table resistance - resitance tolerance then bullet ricochet
			if (force < newTableResistance - resistanceTolerance) {

				//Bullet ricochets
				ricochet(tableCollisionData);

			}
			else if (force >= newTableResistance - resistanceTolerance && force <= newTableResistance + resistanceTolerance) {

				//If bullet force is within range of stuck tolerance percentage of table resistance then bullet stays stuck
				params.stuck = true;

			}
			//else if (force > newTableResistance + resistanceTolerance) {
			//	
			//	//If bullet force is greater than table resistance + resistance tolerance then bullet penetrates
			//	
			//}

			//If resistance of table <= 0 then explode
			if (newTableResistance <= 0) {
				explosionParamsStruct newExplosionParams;
				newExplosionParams.ID = getFreeID(getExplosionIDs());
				newExplosionParams.overworldGridLayer = params.layer;
				newExplosionParams.sprite.spriteSheetIndex = tables[tableIndex].getTableSpriteSheetIndex();
				areaStruct tableArea = tables[tableIndex].getSpriteSheetArea();
				newExplosionParams.sprite.areas = {
					{
						{
							{ tableArea.x, tableArea.y, tableArea.w, tableArea.h }
						}
					}
				};
				newExplosionParams.sprite.angle = params.sprite.angle;
				newExplosionParams.collisionData = tableCollisionData;
				newExplosionParams.force = force;
				int tableHeight = tables[tableIndex].getSize().h;
				newExplosionParams.shadowHeightRandMinMax = { tableHeight / 2, tableHeight };
				//newExplosionParams.totalFragments = { randInt(1, newExplosionParams.sprite.areas[0][0].w), randInt(1, newExplosionParams.sprite.areas[0][0].h) };
				newExplosionParams.totalFragments = { newExplosionParams.sprite.areas[0][0].w / 4, newExplosionParams.sprite.areas[0][0].h / 4 };
				initExplosion(newExplosionParams);

				//Disable table sprite display
				tables[tableIndex].setDisplaySprites(false);
				tables[tableIndex].setDestroy(true);

				//Remove table collision from overworld grid
				XYStruct tablePosition = tables[tableIndex].getPosition();
				WHStruct tableSize = tables[tableIndex].getSize();
				setOverworldGridCollision(overworldGrid.gridTile, params.layer, getGridAreaFromPixelArea({ tablePosition.x, tablePosition.y, tableSize.w, tableSize.h }), false);

			}

		}

		//Other bullet collision
		if (otherBulletCollisionData.collision == true) {
			int otherBulletIndex = getBulletIndexByID(otherBulletCollisionData.instanceID);
			
			//Check if other bullet was fired by same character who fired current bullet
			vector<int> bulletsFiredIDs = characters[bullets[otherBulletIndex].getCharacterID()].getBulletsFiredIDs();
			bool bulletFiredBySameCharacter = false;
			for (int bulletsFiredIDsCnt = 0; bulletsFiredIDsCnt < (int)bulletsFiredIDs.size(); ++bulletsFiredIDsCnt) {
				if (bullets[otherBulletIndex].getID() == bulletsFiredIDs[bulletsFiredIDsCnt]) {
					bulletFiredBySameCharacter = true;
					break;
				}
			}

			//If bullet is not the same as current bullet and is not a bullet that has been fired by same character who fired current bullet
			if (otherBulletIndex > -1 && otherBulletIndex != params.ID && bulletFiredBySameCharacter == false) {

				//Decrease other bullet resistance by the amount of force that hits
				int newOtherBulletResistance = bullets[otherBulletIndex].getResistance() - force;
				bullets[otherBulletIndex].setResistance(newOtherBulletResistance);

				//Decrease bullet resistance
				params.resistance -= force;

				int resistanceTolerance = (newOtherBulletResistance * bullets[otherBulletIndex].getStuckTolerancePercentage()) / 100;

				//If bullet force is lower than other bullet resistance - resitance tolerance then bullet ricochet
				if (force < newOtherBulletResistance - resistanceTolerance) {

					//Bullet ricochets
					ricochet(tableCollisionData);

				}
				else if (force >= newOtherBulletResistance - resistanceTolerance && force <= newOtherBulletResistance + resistanceTolerance) {

					//If bullet force is within range of stuck tolerance percentage of other bullet resistance then bullet stays stuck
					params.stuck = true;

				}
				//else if (force > newTableResistance + resistanceTolerance) {
				//	
				//	//If bullet force is greater than table resistance + resistance tolerance then bullet penetrates
				//	
				//}

				//If resistance of other bullet <= 0 then explode
				if (newOtherBulletResistance <= 0) {
					explosionParamsStruct newExplosionParams;
					newExplosionParams.ID = getFreeID(getExplosionIDs());
					newExplosionParams.overworldGridLayer = params.layer;
					newExplosionParams.sprite.spriteSheetIndex = bullets[otherBulletIndex].getBulletSpriteSheetIndex();
					areaStruct otherBulletArea = bullets[otherBulletIndex].getSpriteSheetArea();
					newExplosionParams.sprite.areas = {
						{
							{
								{ otherBulletArea.x, otherBulletArea.y, otherBulletArea.w, otherBulletArea.h }
							}
						}
					};
					newExplosionParams.sprite.angle = params.sprite.angle;
					newExplosionParams.collisionData = tableCollisionData;
					newExplosionParams.force = force;
					int otherBulletHeight = bullets[otherBulletIndex].getSize().h;
					newExplosionParams.shadowHeightRandMinMax = { otherBulletHeight / 2, otherBulletHeight };
					//newExplosionParams.totalFragments = { randInt(1, newExplosionParams.sprite.areas[0][0].w), randInt(1, newExplosionParams.sprite.areas[0][0].h) };
					newExplosionParams.totalFragments = { newExplosionParams.sprite.areas[0][0].w / 4, newExplosionParams.sprite.areas[0][0].h / 4 };
					initExplosion(newExplosionParams);

					//Disable other bullet sprite display
					bullets[otherBulletIndex].setDisplaySprite(false);
					bullets[otherBulletIndex].setDestroy(true);

				}

			}
		}

	}
}

void Bullet::explode() {
	if (params.resistance <= 0 && params.destroy == false) {
		explosionParamsStruct newExplosionParams;
		newExplosionParams.ID = getFreeID(getExplosionIDs());
		newExplosionParams.overworldGridLayer = params.layer;
		newExplosionParams.sprite = params.sprite;
		newExplosionParams.force = params.damage - params.totalDistanceTravelled;
		newExplosionParams.shadowHeightRandMinMax = { params.size.h / 2, params.size.h };
		newExplosionParams.totalFragments = { randInt(1, newExplosionParams.sprite.areas[0][0].w), randInt(1, newExplosionParams.sprite.areas[0][0].h) };
		//newExplosionParams.totalFragments = { 2, 2 };
		newExplosionParams.collisionData.collidePosition = params.position;
		newExplosionParams.collisionData.collision = true;
		newExplosionParams.collisionData.hitCorner = collisionDataStruct::tileHitCornerEnum::none;
		newExplosionParams.collisionData.instanceID = params.ID;
		initExplosion(newExplosionParams);

		params.displaySprite = false;
		params.destroy = true;
	}
}

Explosion::Explosion(explosionParamsStruct newParams) {
	params = newParams;
}

int Explosion::getID() {
	return params.ID;
}

int Explosion::getOverworldGridLayer() {
	return params.overworldGridLayer;
}

XYStruct Explosion::getFragmentPosition(int fragmentIndex) {
	return params.fragments[fragmentIndex].position;
}

int Explosion::getTotalFragments() {
	return (int)params.fragments.size();
}

vector<explosionParamsStruct::fragmentStruct> Explosion::getFragments() {
	return params.fragments;
}

delayStruct Explosion::getFadeOut() {
	return params.fadeOut;
}

void Explosion::setFadeOut(delayStruct newFadeOut) {
	params.fadeOut = newFadeOut;
}

void Explosion::createFragments() {
	if ((int)params.fragments.size() == 0) {
		WHStruct fragmentSize = { -1, -1 };
		if (params.fragmentIsEntireSprite == false) {
			fragmentSize = { params.sprite.areas[0][0].w / params.totalFragments.x, params.sprite.areas[0][0].h / params.totalFragments.y };
		}
		else {
			fragmentSize = { params.sprite.areas[0][0].w, params.sprite.areas[0][0].h };
		}

		areaStruct fragmentArea = { params.sprite.areas[0][0].x, params.sprite.areas[0][0].y, fragmentSize.w, fragmentSize.h };

		for (int totalFragmentsXCnt = 0; totalFragmentsXCnt < params.totalFragments.x; ++totalFragmentsXCnt) {
			if (params.fragmentIsEntireSprite == false) {
				fragmentArea.y = params.sprite.areas[0][0].y;
			}
			
			for (int totalFragmentsYCnt = 0; totalFragmentsYCnt < params.totalFragments.y; ++totalFragmentsYCnt) {
				explosionParamsStruct::fragmentStruct fragment;

				//Offset collide position to give each fragment a different starting position
				fragment.position = { params.collisionData.collidePosition.x + (fragmentSize.w * totalFragmentsXCnt) - fragmentSize.w, params.collisionData.collidePosition.y + (fragmentSize.h * totalFragmentsYCnt) - fragmentSize.h };

				fragment.originalPosition = fragment.position;
				fragment.size = fragmentSize;
				
				fragment.shadowHeight = randInt(params.shadowHeightRandMinMax.min, params.shadowHeightRandMinMax.max);
				
				//fragment.maxDistance = randInt(fragment.size.w * 4, fragment.size.w * 8);
				fragment.maxDistance = randInt(params.force / 2, params.force);
				
				fragment.sprite.spriteSheetIndex = params.sprite.spriteSheetIndex;
				fragment.sprite.areas = {
					{
						{
							{ fragmentArea.x, fragmentArea.y, fragmentArea.w, fragmentArea.h }
						}
					}
				};
				
				if (params.randomizeFragmentAngle == false) {
					int angleTolerance = (params.sprite.angle * 10) / 100;
					fragment.sprite.angle = randInt(params.sprite.angle - angleTolerance, params.sprite.angle + angleTolerance);
				}
				else {
					fragment.sprite.angle = randInt(0, 360);
				}
				if (fragment.sprite.angle > 180) {
					fragment.sprite.angle = -(180 - (fragment.sprite.angle - 180));
				}

				fragment.sprite.center = { randInt(0, fragmentSize.w), randInt(0, fragmentSize.h) };
				
				int randomFlip = randInt(1, 3);
				if (randomFlip == 1) {
					fragment.sprite.flip = SDL_RendererFlip::SDL_FLIP_NONE;
				}
				else if (randomFlip == 2) {
					fragment.sprite.flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
				}
				else if (randomFlip == 3) {
					fragment.sprite.flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;
				}

				fragment.speed.startTicks = SDL_GetTicks();
				fragment.speed.delay = 1;
				fragment.pixelIncrement = 2;

				params.fragments.push_back(fragment);

				if (params.fragmentIsEntireSprite == false) {
					fragmentArea.y += fragmentArea.h;
				}
			}

			if (params.fragmentIsEntireSprite == false) {
				fragmentArea.x += fragmentArea.w;
			}
		}
	}
}

void Explosion::render() {

	//Render all fragments
	for (int fragmentsCnt = 0; fragmentsCnt < (int)params.fragments.size(); ++fragmentsCnt) {
		SDL_Rect sRect = convertAreaToSDLRect(params.fragments[fragmentsCnt].sprite.areas[0][0]);
		SDL_Rect dRect = { params.fragments[fragmentsCnt].position.x - camera.area.x, params.fragments[fragmentsCnt].position.y - camera.area.y, params.fragments[fragmentsCnt].size.w, params.fragments[fragmentsCnt].size.h };

		if (areaWithinCameraView({ params.fragments[fragmentsCnt].position.x, params.fragments[fragmentsCnt].position.y, params.fragments[fragmentsCnt].size.w, params.fragments[fragmentsCnt].size.h }) == true) {

			//Set transparency
			int percentageTimePassed = 0;
			if (params.fadeOut.delay > 0) {
				percentageTimePassed = ((SDL_GetTicks() - params.fadeOut.startTicks) * 100) / params.fadeOut.delay;
				setSDLTextureTransparency(spriteSheets[params.fragments[fragmentsCnt].sprite.spriteSheetIndex].texture, 100 - percentageTimePassed);
			}

			//Render shadow
			if (params.enableShadows == true) {
				renderShadow({ dRect.x, dRect.y + params.fragments[fragmentsCnt].shadowHeight, dRect.w, dRect.h / 5 }, 50 - (percentageTimePassed / 2));
			}

			SDLRenderCopyEx(sRect, dRect, params.fragments[fragmentsCnt].sprite);

			//Reset transparency
			if (params.fadeOut.delay > 0) {
				setSDLTextureTransparency(spriteSheets[params.fragments[fragmentsCnt].sprite.spriteSheetIndex].texture, 100);
			}

		}
	}

}

void Explosion::explode() {
	for (int fragmentsCnt = 0; fragmentsCnt < (int)params.fragments.size(); ++fragmentsCnt) {
		if (SDL_GetTicks() - params.fragments[fragmentsCnt].speed.startTicks >= params.fragments[fragmentsCnt].speed.delay / FPSTimerMod) {
			params.fragments[fragmentsCnt].speed.startTicks = SDL_GetTicks();

			if (params.fragments[fragmentsCnt].distanceTravelled < params.fragments[fragmentsCnt].maxDistance) {

				//Update fragment position
				params.fragments[fragmentsCnt].distanceTravelled += params.fragments[fragmentsCnt].pixelIncrement;
				params.fragments[fragmentsCnt].position = { lround((double)params.fragments[fragmentsCnt].originalPosition.x + (params.fragments[fragmentsCnt].distanceTravelled * cos(((params.fragments[fragmentsCnt].sprite.angle) * M_PI) / 180))), lround((double)params.fragments[fragmentsCnt].originalPosition.y + (params.fragments[fragmentsCnt].distanceTravelled * sin(((params.fragments[fragmentsCnt].sprite.angle) * M_PI) / 180))) };

				//Rotate fragment
				params.fragments[fragmentsCnt].sprite.angle += params.fragments[fragmentsCnt].pixelIncrement;
				if (params.fragments[fragmentsCnt].sprite.angle > 180) {
					params.fragments[fragmentsCnt].sprite.angle = -(180 - (params.fragments[fragmentsCnt].sprite.angle - 180));
				}

				//Update shadow height
				params.fragments[fragmentsCnt].shadowHeight -= params.fragments[fragmentsCnt].pixelIncrement;

			}
			else {
				
				//Update shadow height
				params.fragments[fragmentsCnt].shadowHeight = params.fragments[fragmentsCnt].size.h / 2;

			}
		}
	}
}

void Explosion::markForDestruction() {
	if (params.fadeOut.delay > 0 && SDL_GetTicks() - params.fadeOut.startTicks >= params.fadeOut.delay) {
		explosionsToDestroyIDs.push_back(params.ID);
	}
}

//class functions end

//void test(int& functionNumber) {
//	++functionNumber;
//}

int main(int argc, char* args[]) {
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
		init();
		setSDLRenderTarget(NULL);
		clearScreen(0, 0, 0, 255);
		SDL_RenderPresent(renderer);
		initMusic();
		initSoundEffects();
		initFonts();
		initColours();
		displayLoadingMessage();
		initSpriteSheets();
		initGlobalSprites();
		initTiles();
		initRegions();
		initLevel();
		initCharacters();

		float FPSCapMilliseconds = (float)lround((float)1000 / FPSCap);
		selectedMenuLayer = 0;

		//printStr(formatStr("level created in: {} seconds", { strUint32((SDL_GetTicks() - initTimerStartTicks) / 1000) }));

		initGameClock();
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
				int fontSize = tileSize.h * 2;
				displayCopyright({ 0, textLogicalSize.h - (fontSize * 2) }, fontSize);
			}
			else {

				//Actions
				//moveCamera();
				characterActions();
				tableActions();
				bulletActions();
				explosionActions();

				//Set objects to be removed
				setStuckBulletsFadeOut();
				setExplosionsFadeOut();

				//Destroy objects
				destroyBullets();
				destroyCharacters();
				destroyTables();
				destroyExplosions();

				//Centre camera on controlled character
				XYStruct characterPosition = characters[controlledCharacterIndex].getPosition();
				WHStruct characterSize = characters[controlledCharacterIndex].getSize();
				centreCamera({ characterPosition.x, characterPosition.y, characterSize.w, characterSize.h }, characters[controlledCharacterIndex].getLayer());

				//Render
				renderBackgroundCharactersAndObjects();
				renderUI();

				//Menus
				setSDLRenderTarget(NULL);
				setSDLLogicalSize(textLogicalSize);
				//;;

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

		destroyPreRenderTexture();
		destroySpriteSheets();
		closeFonts();
		freeSoundEffects();
		freeMusic();
		close();
	}
	return 0;
}
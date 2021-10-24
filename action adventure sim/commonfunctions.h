#pragma once

using namespace std;

void pauseAtConsole();

int roundDiv(int firstNumber, int secondNumber);

int roundInt(int number);

float roundDec(float number, int decimalPoint);

struct decimalNumPartsStruct {
	double fractpart, intpart;
};

decimalNumPartsStruct getDecimalNumParts(double param);

int roundDivUp(double param);

string str(int value);

string strUint32(Uint32 value);

string strUnsignedInt(unsigned int value);

string strRoundDec(float number, int decimalPoint);

int toInt(string currentString);

int randInt(int startInt, int endInt);

string randStringList(vector<string> list);

void printRand();

void printInt(int value);

void printIntL(vector<int> values);

void printFloat(float value);

void printFloatL(vector<float> values);

void printUInt32(Uint32 value);

void printUInt32L(vector<Uint32> values);

void printStr(string value);

void printStrL(vector<string> values);

void printSDLRect(SDL_Rect rect);

void printSDLRectL(vector<SDL_Rect> rects);

struct XYStruct {
	int x, y;
};

void printXYStruct(XYStruct position);

void printXYStructL(vector<XYStruct> positions);

struct XYUnsignedIntStruct {
	unsigned int x, y;
};

void printXYUnsignedIntStruct(XYUnsignedIntStruct position);

void printXYUnsignedIntStructL(vector<XYUnsignedIntStruct> positions);

struct WHStruct {
	int w, h;
};

void printWHStruct(WHStruct size);

void printWHStructL(vector<WHStruct> sizes);

struct areaStruct {
	int x, y, w, h;
};

void printArea(areaStruct area);

void printAreaL(vector<areaStruct> areas);

struct startEndStruct {
	int start, end;
};

void printStartEndStruct(startEndStruct startEnd);

void printStartEndStructL(vector<startEndStruct> startEnds);

int getFreeID(vector<int> IDs);

int getStringIndex(vector<string> list, string element);

int getIntIndex(vector<int> list, int index);

string formatStr(string str, vector<string> values);

int getOccurencesInString(string stringToFind, string stringToSearch);

int getLengthiestStringLength(vector<string> list);

string getLengthiestStringInList(vector<string> list);

string concatenateStringList(vector<string> list);

string getLengthiestStringInTextBlock(vector<vector<string>> textBlock);

void createFile(string filePathAndName);

void appendToFile(string filePathAndName, string data);

vector<string> readFile(string filePathAndName);

void emptyFile(string filePathAndName);

unsigned int getMinUnsignedIntValue();

unsigned int getMaxUnsignedIntValue();

string createBlankString(int stringLength);

struct unsignedIntAreaStruct {
	unsigned int x, y, w, h;
};

void runThroughRand(unsigned int seed, unsignedIntAreaStruct area, startEndStruct heightStartEnd, XYUnsignedIntStruct currentPositionInArea, int currentHeight, int randStart, int randEnd);

int getHeuristic(XYStruct startPosition, XYStruct endPosition);

bool areaWithinArea(areaStruct sourceArea, areaStruct targetArea);

struct timeStruct {
	int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
};

timeStruct addTime(timeStruct time, timeStruct addedTime);

struct timeBetweenRangeVarsToCheckStruct {
	bool checkYear = false, checkMonth = false, checkDay = false, checkHour = false, checkMinute = false, checkSecond = false;
};

bool timeBetweenRange(timeStruct time, timeStruct timeRangeStart, timeStruct timeRangeEnd, timeBetweenRangeVarsToCheckStruct varsToCheck);

bool timeBetweenRange(timeStruct time, timeStruct timeRangeStart, timeStruct timeRangeEnd);

void printTimeStruct(timeStruct time);

void printTimeStructL(vector<timeStruct> timeList);

bool compareTime(timeStruct timeA, timeStruct timeB);

struct nodeStruct {
	XYStruct position = { -1, -1 };
	int g = 0, h = 0, f = 0;
};

struct nodeWithParentStruct {
	nodeStruct parent, node;
};

bool compareNodes(nodeStruct nodeA, nodeStruct nodeB);

bool compareNodesWithParent(nodeWithParentStruct nodeA, nodeWithParentStruct nodeB);

struct aStarPathTimerStruct {
	Uint32 startTicks = -1, delay = -1;
};

void printAStarPath(vector<XYStruct> path);

void printMaze(vector<vector<bool>>& maze, XYStruct start, XYStruct end, XYStruct current);

void printVisualAStarPath(vector<vector<bool>>& maze, vector<XYStruct> path, XYStruct start, XYStruct end);

vector<XYStruct> getAStarPath(vector<vector<bool>>& maze, XYStruct start, XYStruct end);

void convertPathCoordinates(vector<XYStruct>& path, int conversionFactor);
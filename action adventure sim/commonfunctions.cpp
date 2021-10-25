#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <SDL.h>
#include <fstream>
#include <limits>

using namespace std;

void pauseAtConsole() {
	string prompt;
	cout << "\n>";
	cin >> prompt;
	if (prompt == "q") {
		exit(0);
	}
}

int roundDiv(int firstNumber, int secondNumber) {
	return lround((float)firstNumber / secondNumber);
}

int roundInt(int number) {
	return lround(number);
}

float roundDec(float number, int decimalPoint) {
	float value = (float)(number * (10 * decimalPoint) + .5);
	return (float)value / (10 * decimalPoint);
}

struct decimalNumPartsStruct {
	double fractpart = -1, intpart = -1;
};

decimalNumPartsStruct getDecimalNumParts(double param) {
	decimalNumPartsStruct currentDecimalNumParts;
	currentDecimalNumParts.fractpart = modf(param, &currentDecimalNumParts.intpart);
	return currentDecimalNumParts;
}

int roundDivUp(double param) {
	decimalNumPartsStruct decimalNumParts = getDecimalNumParts(param);
	if (decimalNumParts.fractpart != 0) {
		++decimalNumParts.intpart;
	}
	return (int)decimalNumParts.intpart;
}

string str(int value) {
	return to_string(value);
}

string strUint32(Uint32 value) {
	return to_string(value);
}

string strUnsignedInt(unsigned int value) {
	return to_string(value);
}

string strRoundDec(float number, int decimalPoint) {
	return to_string(roundDec(number, decimalPoint));
}

int toInt(string currentString) {
	return stoi(currentString);
}

int randInt(int startInt, int endInt) {
	return startInt + rand() % (endInt - startInt + 1);
}

string randStringList(vector<string> list) {
	return list[rand() % (int)list.size()];
}

void printRand() {
	//printf("%d\n", rand() % 10);
	cout << rand() % 10 << "\n";
}

void printInt(int value) {
	//printf("%d, %d\n", rand() % 10, value);
	//printf("%d\n", value);
	cout << value << "\n";
}

void printIntL(vector<int> values) {
	//string str = to_string(rand() % 10) + ", " + to_string(values[0]);
	string str = to_string(values[0]);
	if ((int)values.size() > 1) {
		for (int valuesCnt = 1; valuesCnt < (int)values.size(); ++valuesCnt) {
			str += ", " + to_string(values[valuesCnt]);
		}
	}
	//printf("%s\n", str.c_str());
	cout << str << "\n";
}

void printFloat(float value) {
	//printf("%d, %f\n", rand() % 10, value);
	//printf("%f\n", value);
	cout << value << "\n";
}

void printFloatL(vector<float> values) {
	//string str = to_string(rand() % 10) + ", " + to_string(values[0]);
	string str = to_string(values[0]);
	if ((int)values.size() > 1) {
		for (int valuesCnt = 1; valuesCnt < (int)values.size(); ++valuesCnt) {
			str += ", " + to_string(values[valuesCnt]);
		}
	}
	//printf("%s\n", str.c_str());
	cout << str << "\n";
}

void printUInt32(Uint32 value) {
	cout << value << "\n";
}

void printUInt32L(vector<Uint32> values) {
	string str = to_string(values[0]);
	if ((int)values.size() > 1) {
		for (int valuesCnt = 1; valuesCnt < (int)values.size(); ++valuesCnt) {
			str += ", " + to_string(values[valuesCnt]);
		}
	}
	//printf("%s\n", str.c_str());
	cout << str << "\n";
}

void printStr(string value) {
	//printf("%d, %s\n", rand() % 10, value.c_str());
	//printf("%s\n", value.c_str());
	cout << value << "\n";
}

void printStrL(vector<string> values) {
	//string str = to_string(rand() % 10);
	//str += ", " + values[0];
	string str = values[0];
	if ((int)values.size() > 1) {
		for (int valuesCnt = 1; valuesCnt < (int)values.size(); ++valuesCnt) {
			str += ", " + values[valuesCnt];
		}
	}
	//printf("%s\n", str.c_str());
	cout << str << "\n";
}

void printSDLRect(SDL_Rect rect) {
	printIntL({ rect.x, rect.y, rect.w, rect.h });
}

void printSDLRectL(vector<SDL_Rect> rects) {
	vector<int> output;
	for (int rectsCnt = 0; rectsCnt < (int)rects.size(); ++rectsCnt) {
		output.push_back(rects[rectsCnt].x);
		output.push_back(rects[rectsCnt].y);
		output.push_back(rects[rectsCnt].w);
		output.push_back(rects[rectsCnt].h);
	}
	printIntL(output);
}

struct XYStruct {
	int x = -1, y = -1;
};

void printXYStruct(XYStruct position) {
	printIntL({ position.x, position.y });
}

void printXYStructL(vector<XYStruct> positions) {
	vector<int> positionsList;
	for (int positionsCnt = 0; positionsCnt < (int)positions.size(); ++positionsCnt) {
		positionsList.push_back(positions[positionsCnt].x);
		positionsList.push_back(positions[positionsCnt].y);
	}
	printIntL(positionsList);
}

struct XYUnsignedIntStruct {
	unsigned int x = -1, y = -1;
};

void printXYUnsignedIntStruct(XYUnsignedIntStruct position) {
	printUInt32L({ position.x, position.y });
}

void printXYUnsignedIntStructL(vector<XYUnsignedIntStruct> positions) {
	vector<unsigned int> positionsList;
	for (int positionsCnt = 0; positionsCnt < (int)positions.size(); ++positionsCnt) {
		positionsList.push_back(positions[positionsCnt].x);
		positionsList.push_back(positions[positionsCnt].y);
	}
	printUInt32L(positionsList);
}

struct WHStruct {
	int w = -1, h = -1;
};

void printWHStruct(WHStruct size) {
	printIntL({ size.w, size.h });
}

void printWHStructL(vector<WHStruct> sizes) {
	vector<int> sizesList;
	for (int sizesCnt = 0; sizesCnt < (int)sizes.size(); ++sizesCnt) {
		sizesList.push_back(sizes[sizesCnt].w);
		sizesList.push_back(sizes[sizesCnt].h);
	}
	printIntL(sizesList);
}

struct areaStruct {
	int x = -1, y = -1, w = -1, h = -1;
};

void printArea(areaStruct area) {
	printIntL({ area.x, area.y, area.w, area.h });
}

void printAreaL(vector<areaStruct> areas) {
	vector<int> output;
	for (int areasCnt = 0; areasCnt < (int)areas.size(); ++areasCnt) {
		output.push_back(areas[areasCnt].x);
		output.push_back(areas[areasCnt].y);
		output.push_back(areas[areasCnt].w);
		output.push_back(areas[areasCnt].h);
	}
	printIntL(output);
}

struct startEndStruct {
	int start = -1, end = -1;
};

void printStartEndStruct(startEndStruct startEnd) {
	printIntL({ startEnd.start, startEnd.end });
}

void printStartEndStructL(vector<startEndStruct> startEnds) {
	vector<int> startEndsList;
	for (int startEndsCnt = 0; startEndsCnt < (int)startEnds.size(); ++startEndsCnt) {
		startEndsList.push_back(startEnds[startEndsCnt].start);
		startEndsList.push_back(startEnds[startEndsCnt].end);
	}
	printIntL(startEndsList);
}

int getFreeID(vector<int> IDs) {

	//Get index number not already used in indices list
	int ID = 0;
	if ((int)IDs.size() > 0) {
		bool getFreeID = true;
		while (getFreeID == true) {
			int IDsCnt = 0;
			for (IDsCnt = 0; IDsCnt < (int)IDs.size(); ++IDsCnt) {
				if (IDs[IDsCnt] == ID) {
					break;
				}
			}
			
			if (IDsCnt < (int)IDs.size() && IDs[IDsCnt] == ID) {
				++ID;
			}
			else {
				return ID;
			}
		}
	}

	return ID;
}

int getStringIndex(vector<string> list, string element) {
	for (int listCnt = 0; listCnt < (int)list.size(); ++listCnt) {
		if (list[listCnt] == element) {
			return listCnt;
		}
	}
	return -1;
}

int getIntIndex(vector<int> list, int value) {
	for (int listCnt = 0; listCnt < (int)list.size(); ++listCnt) {
		if (list[listCnt] == value) {
			return listCnt;
		}
	}
	return -1;
}

//str = "{}, {}"
//values = { "hello", "world" }
string formatStr(string str, vector<string> values) {
	if (str.length() > 0 && (int)values.size() > 0) {
		for (int valuesCnt = 0; valuesCnt < (int)values.size(); ++valuesCnt) {
			str.replace(str.find("{"), 2, values[valuesCnt]);
		}
	}
	return str;
}

struct occurencesInStringStruct {
	int total = 0, position = -1;
};

int getOccurencesInString(string stringToFind, string stringToSearch) {
	if (stringToFind != "" && stringToSearch != "") {
		int occurences = 0;
		string currentStringToSearch = stringToSearch;
		bool getOccurences = true;
		while (getOccurences == true) {
			if ((int)currentStringToSearch.find(stringToFind) > -1) {
				++occurences;
				currentStringToSearch = currentStringToSearch.substr(currentStringToSearch.find(stringToFind) + stringToFind.length());
			}
			else {
				return occurences;
			}
		}
	}
	return -1;
}

int getLengthiestStringLength(vector<string> list) {
	int maxLength = 0;
	for (int listCnt = 0; listCnt < (int)list.size(); ++listCnt) {
		if ((int)list[listCnt].length() > maxLength) {
			maxLength = (int)list[listCnt].length();
		}
	}
	return maxLength;
}

string getLengthiestStringInList(vector<string> list) {
	string lenthiestString = "";
	for (int listCnt = 0; listCnt < (int)list.size(); ++listCnt) {
		if ((int)list[listCnt].length() > (int)lenthiestString.length()) {
			lenthiestString = list[listCnt];
		}
	}
	return lenthiestString;
}

string concatenateStringList(vector<string> list) {
	string concatenatedString = "";
	for (int listCnt = 0; listCnt < (int)list.size(); ++listCnt) {
		concatenatedString += list[listCnt];
	}
	return concatenatedString;
}

string getLengthiestStringInTextBlock(vector<vector<string>> textBlock) {
	string lenthiestString = "";
	for (int textBlockCnt = 0; textBlockCnt < (int)textBlock.size(); ++textBlockCnt) {
		string concatenatedList = concatenateStringList(textBlock[textBlockCnt]);
		if ((int)concatenatedList.length() > (int)lenthiestString.length()) {
			lenthiestString = concatenatedList;
		}
	}
	return lenthiestString;
}

void createFile(string filePathAndName) {
	ofstream myFile(filePathAndName);
	myFile.close();
}

void appendToFile(string filePathAndName, string data) {
	fstream myFile(filePathAndName.c_str(), fstream::in | fstream::out | fstream::app);
	myFile << data << "\n";
	myFile.close();
}

vector<string> readFile(string filePathAndName) {
	vector<string> data;

	ifstream myFile(filePathAndName);
	string myText;
	while (getline(myFile, myText)) {
		data.push_back(myText);
	}

	return data;
}

void emptyFile(string filePathAndName) {
	createFile(filePathAndName);
}

unsigned int getMinUnsignedIntValue() {
	return numeric_limits<unsigned int>::min();
}

unsigned int getMaxUnsignedIntValue() {
	return numeric_limits<unsigned int>::max();
}

string createBlankString(int stringLength) {
	string blankString;
	for (int blankCharacterCnt = 0; blankCharacterCnt < stringLength; ++blankCharacterCnt) {
		blankString += " ";
	}
	return blankString;
}

struct unsignedIntAreaStruct {
	unsigned int x = -1, y = -1, w = -1, h = -1;
};

void runThroughRand(unsigned int seed, unsignedIntAreaStruct area, startEndStruct heightStartEnd, XYUnsignedIntStruct currentPositionInArea, int currentHeight, int randStart, int randEnd) {
	
	//Get total number of times to run rand
	unsigned int total = 0;
	for (int heightStartEndCnt = heightStartEnd.start; heightStartEndCnt <= heightStartEnd.end; ++heightStartEndCnt) {
		for (unsigned int areaXCnt = area.x; areaXCnt < area.x + area.w ; ++areaXCnt) {
			for (unsigned int areaYCnt = area.y; areaYCnt < area.y + area.h; ++areaYCnt) {
				if (heightStartEndCnt == currentHeight && areaXCnt == currentPositionInArea.x && areaYCnt == currentPositionInArea.y) {
					goto exitGetTotal;
				}
				total += 1;
			}
		}
	}
exitGetTotal:

	//Run rand
	srand(seed);
	for (unsigned int totalCnt = 0; totalCnt < total; ++totalCnt) {
		randInt(randStart, randEnd);
	}

}

int getHeuristic(XYStruct startPosition, XYStruct endPosition) {
	return abs(startPosition.x - endPosition.x) + abs(startPosition.y - endPosition.y);
}

bool areaWithinArea(areaStruct sourceArea, areaStruct targetArea) {
	if (sourceArea.x + sourceArea.w - 1 < targetArea.x || sourceArea.x > targetArea.x + targetArea.w - 1 || sourceArea.y + sourceArea.h - 1 < targetArea.y || sourceArea.y > targetArea.y + targetArea.h - 1) {
		return false;
	}
	return true;
}

struct timeStruct {
	int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
};

timeStruct addTime(timeStruct time, timeStruct addedTime) {
	time.second += addedTime.second;
	time.minute += addedTime.minute;
	time.hour += addedTime.hour;
	time.day += addedTime.day;
	time.month += addedTime.month;
	time.year += addedTime.year;

	//Check all time elements are within their range
	bool checkTimeElements = true;
	while (checkTimeElements == true) {
		if (time.second > 59) {
			time.second -= 60;
			++time.minute;
		}
		if (time.minute > 59) {
			time.minute -= 60;
			++time.hour;
		}
		if (time.hour > 23) {
			time.hour -= 24;
			++time.day;
		}
		if (time.day > 31) {
			time.day -= 31;
			++time.month;
		}
		if (time.month > 12) {
			time.month -= 12;
			++time.year;
		}
		
		//printIntL({ randInt(0, 9), time.second, time.minute, time.hour, time.day, time.month });
		if (time.second >= 0 && time.second <= 59
			&& time.minute >= 0 && time.minute <= 59
			&& time.hour >= 0 && time.hour <= 23
			&& time.day >= 1 && time.day <= 31
			&& time.month >= 1 && time.month <= 12) {
			checkTimeElements = false;
		}
	}

	return time;
};

struct timeBetweenRangeVarsToCheckStruct {
	bool checkYear = false, checkMonth = false, checkDay = false, checkHour = false, checkMinute = false, checkSecond = false;
};

bool timeBetweenRange(timeStruct time, timeStruct timeRangeStart, timeStruct timeRangeEnd, timeBetweenRangeVarsToCheckStruct varsToCheck) {
	if ((varsToCheck.checkYear == true && (time.year < timeRangeStart.year || time.year > timeRangeEnd.year))
		|| (varsToCheck.checkMonth == true && (time.month < timeRangeStart.month || time.month > timeRangeEnd.month))
		|| (varsToCheck.checkDay == true && (time.day < timeRangeStart.day || time.day > timeRangeEnd.day))
		|| (varsToCheck.checkHour == true && (time.hour < timeRangeStart.hour || time.hour > timeRangeEnd.hour))
		|| (varsToCheck.checkMinute == true && (time.minute < timeRangeStart.minute || time.minute > timeRangeEnd.minute))
		|| (varsToCheck.checkSecond == true && (time.second < timeRangeStart.second || time.second > timeRangeEnd.second))) {
		return false;
	}
	return true;
}

bool timeBetweenRange(timeStruct time, timeStruct timeRangeStart, timeStruct timeRangeEnd) {
	if (time.year < timeRangeStart.year || time.year > timeRangeEnd.year
		|| time.month < timeRangeStart.month || time.month > timeRangeEnd.month
		|| time.day < timeRangeStart.day || time.day > timeRangeEnd.day
		|| time.hour < timeRangeStart.hour || time.hour > timeRangeEnd.hour
		|| time.minute < timeRangeStart.minute || time.minute > timeRangeEnd.minute
		|| time.second < timeRangeStart.second || time.second > timeRangeEnd.second) {
		return false;
	}
	return true;
}

void printTimeStruct(timeStruct time) {
	printIntL({ time.year, time.month, time.day, time.hour, time.minute, time.second });
}

void printTimeStructL(vector<timeStruct> timeList) {
	string timeListString = "";
	for (int timeListCnt = 0; timeListCnt < (int)timeList.size(); ++timeListCnt) {
		timeListString += formatStr("{}, {}, {}, {}, {}, {}", { str(timeList[timeListCnt].year), str(timeList[timeListCnt].month), str(timeList[timeListCnt].day), str(timeList[timeListCnt].hour), str(timeList[timeListCnt].minute), str(timeList[timeListCnt].second) });
		if (timeListCnt < (int)timeList.size() - 1) {
			timeListString += "; ";
		}
	}
	printStr(timeListString);
}

bool compareTime(timeStruct timeA, timeStruct timeB) {
	if (timeA.year != timeB.year) {
		return false;
	}
	else if (timeA.month != timeB.month) {
		return false;
	}
	else if (timeA.day != timeB.day) {
		return false;
	}
	else if (timeA.hour != timeB.hour) {
		return false;
	}
	else if (timeA.minute != timeB.minute) {
		return false;
	}
	else if (timeA.second != timeB.second) {
		return false;
	}
	return true;
}

struct nodeStruct {
	XYStruct position = { -1, -1 };
	int g = -1, h = -1, f = -1;
};

struct nodeWithParentStruct {
	nodeStruct parent, node;
};

bool compareNodes(nodeStruct nodeA, nodeStruct nodeB) {
	if (nodeA.position.x != nodeB.position.x || nodeA.position.y != nodeB.position.y) {
		return false;
	}
	if (nodeA.g != nodeB.g) {
		return false;
	}
	if (nodeA.h != nodeB.h) {
		return false;
	}
	if (nodeA.f != nodeB.f) {
		return false;
	}
	return true;
}

bool compareNodesWithParent(nodeWithParentStruct nodeA, nodeWithParentStruct nodeB) {
	if (compareNodes(nodeA.node, nodeB.node) == false) {
		return false;
	}
	if (compareNodes(nodeA.parent, nodeB.parent) == false) {
		return false;
	}
	return true;
}

bool compareXYStructs(XYStruct position1, XYStruct position2) {
	if (position1.x == position2.x && position1.y == position2.y) {
		return true;
	}
	return false;
}

struct aStarPathTimerStruct {
	Uint32 startTicks = -1, delay = -1;
};

//start and end positions have to be in the same coordinate system as maze
//vector<XYStruct> getAStarPath(vector<vector<bool>>& maze, XYStruct start, XYStruct end, aStarPathTimerStruct& aStarPathTimer) {
//	vector<XYStruct> path;
//
//	if (areaWithinArea({ start.x, start.y, 1, 1 }, { 0, 0, (int)maze.size(), (int)maze[0].size() }) == true || areaWithinArea({ end.x, end.y, 1, 1 }, { 0, 0, (int)maze.size(), (int)maze[0].size() }) == true) {
//
//		//Remove collision for start and end nodes
//		/*maze[start.x][start.y] = false;
//		maze[end.x][end.y] = false;*/
//
//		//Create start and end node
//		nodeWithParentStruct startNode;
//		startNode.node.position = start;
//		nodeWithParentStruct endNode;
//		endNode.node.position = end;
//
//		//Initialize both open and closed list
//		vector<nodeWithParentStruct> openList, closedList;
//
//		//Add the start node
//		openList.push_back(startNode);
//
//		//Loop until you find the end or run out of time
//		while ((int)openList.size() > 0 && aStarPathTimer.delay == -1 || (int)openList.size() > 0 && aStarPathTimer.delay > -1 && SDL_GetTicks() - aStarPathTimer.startTicks >= aStarPathTimer.delay) {
//
//			//Get the current node
//			nodeWithParentStruct currentNode = openList[0];
//			int currentIndex = 0;
//			for (int index = 0; index < (int)openList.size(); ++index) {
//				nodeWithParentStruct item = openList[index];
//				if (item.node.f < currentNode.node.f) {
//					currentNode = item;
//					currentIndex = index;
//				}
//			}
//
//			//Pop current off open list, add to closed list
//			openList.erase(openList.begin() + currentIndex);
//			closedList.push_back(currentNode);
//
//			//Found the goal
//			//printIntL({ startNode.node.position.x, startNode.node.position.y, endNode.node.position.x, endNode.node.position.y, currentNode.node.position.x, currentNode.node.position.y, maze[startNode.node.position.x][startNode.node.position.y], maze[endNode.node.position.x][endNode.node.position.y], maze[currentNode.node.position.x][currentNode.node.position.y] });
//			/*printStr("");
//			for (int currentNodeXCnt = currentNode.node.position.x - 1; currentNodeXCnt <= currentNode.node.position.x + 1; ++currentNodeXCnt) {
//				for (int currentNodeYCnt = currentNode.node.position.y - 1; currentNodeYCnt <= currentNode.node.position.y + 1; ++currentNodeYCnt) {
//					if (currentNodeXCnt < (int)maze.size() && currentNodeYCnt < (int)maze[currentNodeXCnt].size()) {
//						printIntL({ currentNodeXCnt, currentNodeYCnt, maze[currentNodeXCnt][currentNodeYCnt] });
//					}
//				}
//			}*/
//			//printXYStructL({ currentNode.node.position, startNode.node.position, endNode.node.position });
//			if (compareXYStructs(currentNode.node.position, endNode.node.position) == true) {
//				//printRand();
//
//				//nodeWithParentStruct current = currentNode;
//				/*while (current.node.position.x > -1) {
//					path.push_back(current.node.position);
//					current.node = current.parent;
//				reverse(path.begin(), path.end());
//				}*/
//
//				/*printStr("");
//				for (int closedListCnt = 0; closedListCnt < (int)closedList.size(); ++closedListCnt) {
//					printXYStructL({ endNode.node.position, startNode.node.position, closedList[closedListCnt].node.position, closedList[closedListCnt].parent.position });
//				}*/
//				
//				//Get path
//				XYStruct pathNodePosition = endNode.node.position;
//				path.push_back(pathNodePosition);
//				while (pathNodePosition.x != startNode.node.position.x || pathNodePosition.y != startNode.node.position.y) {
//
//					//Find node on the closed list with parent = path node
//					for (int closedListCnt = 0; closedListCnt < (int)closedList.size(); ++closedListCnt) {
//						if (compareXYStructs(closedList[closedListCnt].node.position, pathNodePosition) == true) {
//							pathNodePosition = closedList[closedListCnt].parent.position;
//							path.push_back(pathNodePosition);
//						}
//					}
//
//				}
//
//				//Reverse path
//				std::reverse(path.begin(), path.end());
//
//				return path;
//			}
//
//			//Generate children
//			vector<nodeWithParentStruct> children;
//			const vector<XYStruct> positions = { {0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
//			for (int positionsCnt = 0; positionsCnt < (int)positions.size(); ++positionsCnt) {
//				XYStruct newPosition = positions[positionsCnt];
//
//				//Get node position
//				XYStruct nodePosition = { currentNode.node.position.x + newPosition.x, currentNode.node.position.y + newPosition.y };
//
//				//Make sure within range
//				if (nodePosition.x > (int)maze.size() - 1 || nodePosition.x < 0 || nodePosition.y >(int)maze[(int)maze.size() - 1].size() - 1 || nodePosition.y < 0) {
//					continue;
//				}
//
//				//Make sure walkable terrain
//				if (maze[nodePosition.x][nodePosition.y] != false) {
//					continue;
//				}
//
//				//Create new node
//				nodeWithParentStruct newNode;
//				newNode.parent = currentNode.node;
//				newNode.node.position = nodePosition;
//
//				//Append
//				children.push_back(newNode);
//
//			}
//
//			//Loop through children
//			for (int childrenCnt = 0; childrenCnt < (int)children.size(); ++childrenCnt) {
//				nodeWithParentStruct child = children[childrenCnt];
//
//				//Child is on the closed list
//				bool childOnClosedList = false;
//				for (int closedListCnt = 0; closedListCnt < (int)closedList.size(); ++closedListCnt) {
//					nodeWithParentStruct closedChild = closedList[closedListCnt];
//					//if (compareNodesWithParent(child, closedChild) == true) {
//					if (child.node.position.x == closedChild.node.position.x && child.node.position.y == closedChild.node.position.y) {
//						//continue;
//						childOnClosedList = true;
//						break;
//					}
//				}
//
//				if (childOnClosedList == false) {
//
//					//Create the f, g and h values
//					child.node.g = currentNode.node.g + 1;
//					child.node.h = (int)pow(child.node.position.x - endNode.node.position.x, 2) + (int)pow(child.node.position.y - endNode.node.position.y, 2);
//					child.node.f = child.node.g + child.node.h;
//
//					//Child is already in the open list
//					bool childOnOpenList = false;
//					for (int openListCnt = 0; openListCnt < (int)openList.size(); ++openListCnt) {
//						nodeWithParentStruct openNode = openList[openListCnt];
//						//if (compareNodesWithParent(child, openNode) == true && child.node.g > openNode.node.g) {
//						if (child.node.position.x == openNode.node.position.x && child.node.position.y == openNode.node.position.y && child.node.g > openNode.node.g) {
//							//continue;
//							childOnOpenList = true;
//							break;
//						}
//					}
//
//					//Add the child to the open list
//					if (childOnOpenList == false) {
//						openList.push_back(child);
//					}
//
//				}
//			}
//
//		}
//
//		//Reset timer start ticks
//		if (aStarPathTimer.delay > -1 && SDL_GetTicks() - aStarPathTimer.startTicks >= aStarPathTimer.delay) {
//			aStarPathTimer.startTicks = SDL_GetTicks();
//		}
//
//	}
//
//	return path;
//}

void printAStarPath(vector<XYStruct> path) {
	for (int pathCnt = 0; pathCnt < (int)path.size(); ++pathCnt) {
		printXYStruct(path[pathCnt]);
	}
}

void printMaze(vector<vector<bool>>& maze, XYStruct start, XYStruct end, XYStruct current) {
	for (int mazeXCnt = 0; mazeXCnt < (int)maze.size(); ++mazeXCnt) {
		string XString = "";
		for (int mazeYCnt = 0; mazeYCnt < (int)maze.size(); ++mazeYCnt) {
			if (compareXYStructs({ mazeXCnt, mazeYCnt }, current) == true) {
				XString += "C, ";
			}
			else if (compareXYStructs({ mazeXCnt, mazeYCnt }, start) == true) {
				XString += "S, ";
			}
			else if (compareXYStructs({ mazeXCnt, mazeYCnt }, end) == true) {
				XString += "E, ";
			}
			else if (maze[mazeXCnt][mazeYCnt] == false) {
				XString += "0, ";
			}
			else if (maze[mazeXCnt][mazeYCnt] == true) {
				XString += "1, ";
			}
		}
		printStr(XString);
	}
}

void printVisualAStarPath(vector<vector<bool>>& maze, vector<XYStruct> path, XYStruct start, XYStruct end) {
	printStr(formatStr("path size: {}", { str((int)path.size()) }));
	for (int pathCnt = 0; pathCnt < (int)path.size(); ++pathCnt) {
		printStr(formatStr("path {}/{}", { str(pathCnt), str((int)path.size()) }));
		printMaze(maze, start, end, path[pathCnt]);
		pauseAtConsole();
	}
}

//vector<XYStruct> getAStarPath(vector<vector<bool>>& maze, XYStruct start, XYStruct end) {
//	vector<XYStruct> path;
//
//	//1.  Initialize the open list
//	vector<nodeWithParentStruct> openList, closedList;
//
//	/*2.  Initialize the closed list
//	put the starting node on the open
//	list(you can leave its f at zero)*/
//	nodeWithParentStruct startingNode;
//	startingNode.node.position = start;
//	openList.push_back(startingNode);
//
//	//3.  while the open list is not empty
//	bool stopSearch = false;
//	aStarPathTimerStruct aStarPathTimer;
//	aStarPathTimer.startTicks = SDL_GetTicks();
//	aStarPathTimer.delay = 5000;
//	while ((int)openList.size() > 0 && stopSearch == false && (int)aStarPathTimer.delay > -1 && SDL_GetTicks() - aStarPathTimer.startTicks < aStarPathTimer.delay) {
//		/*printStr("\nticks:");
//		printUInt32L({ SDL_GetTicks() - aStarPathTimer.startTicks, aStarPathTimer.delay });*/
//
//		/*a) find the node with the least f on
//		the open list, call it "q"*/
//		nodeWithParentStruct q;
//		int qIndex = -1;
//		/*printStr("");
//		printStr("open list size");
//		printInt((int)openList.size());*/
//		for (int openListCnt = 0; openListCnt < (int)openList.size(); ++openListCnt) {
//			/*printStr("");
//			printStr("open list and q nodes f");
//			printIntL({ openList[openListCnt].node.f, q.node.f });*/
//			if (q.node.f == -1 || openList[openListCnt].node.f < q.node.f) {
//				q = openList[openListCnt];
//				qIndex = openListCnt;
//				/*printStr("");
//				printStr("set q");
//				printXYStruct(q.node.position);*/
//			}
//		}
//
//		//Check if q is on closed list
//		/*bool qOnClosedList = false;
//		for (int closedListCnt = 0; closedListCnt < (int)closedList.size(); ++closedListCnt) {
//			if (compareXYStructs(q.node.position, closedList[closedListCnt].node.position) == true) {
//				qOnClosedList = true;
//				break;
//			}
//		}*/
//
//		/*printStr("\nq position");
//		printXYStructL({ q.node.position, start, end });*/
//		if (q.node.position.x != -1 /*&& qOnClosedList == false*/) {
//
//			//b) pop q off the open list
//			openList.erase(openList.begin() + qIndex);
//
//			/*c) generate q's 8 successors and set their
//			parents to q*/
//			/*printStr("\nsuccessors");*/
//			vector<nodeWithParentStruct> successors;
//			for (int mazeXCnt = q.node.position.x - 1; mazeXCnt <= q.node.position.x + 1; ++mazeXCnt) {
//				for (int mazeYCnt = q.node.position.y - 1; mazeYCnt <= q.node.position.y + 1; ++mazeYCnt) {
//					if (mazeXCnt >= 0 && mazeXCnt <= (int)maze.size() - 1 && mazeYCnt >= 0 && mazeYCnt <= (int)maze[mazeXCnt].size() - 1) {
//						if (mazeXCnt != q.node.position.x || mazeYCnt != q.node.position.y) {
//							nodeWithParentStruct currentSuccessor;
//							currentSuccessor.node.position = { mazeXCnt, mazeYCnt };
//							currentSuccessor.parent.position = q.node.position;
//							successors.push_back(currentSuccessor);
//							//printXYStruct(currentSuccessor.node.position);
//						}
//					}
//				}
//			}
//
//			//d) for each successor
//			for (int successorsCnt = 0; successorsCnt < (int)successors.size(); ++successorsCnt) {
//				/*printStrL({ "\n", "successorsCnt", str(successorsCnt) });
//				printXYStruct(successors[successorsCnt].node.position);*/
//
//				//If successor is walkable
//				if (maze[successors[successorsCnt].node.position.x][successors[successorsCnt].node.position.y] == false) {
//					//printStr("walkable");
//
//					/*i) if successor is the goal, stop search
//					successor.g = q.g + distance between
//					successor and q
//					successor.h = distance from goal to
//					successor(This can be done using many
//						ways, we will discuss three heuristics -
//						Manhattan, Diagonaland Euclidean
//						Heuristics)
//
//					successor.f = successor.g + successor.h*/
//					if (compareXYStructs(successors[successorsCnt].node.position, end) == true) {
//						stopSearch = true;
//						//printStr("end node found");
//
//						//Add end node to closed list
//						closedList.push_back(successors[successorsCnt]);
//
//					}
//					int distanceBetweenSuccessorAndQ = -1;
//					if (successors[successorsCnt].node.position.x == q.node.position.x || successors[successorsCnt].node.position.y == q.node.position.y) {
//						distanceBetweenSuccessorAndQ = 10;
//					}
//					else {
//						distanceBetweenSuccessorAndQ = 14;
//					}
//					successors[successorsCnt].node.g = q.node.g + distanceBetweenSuccessorAndQ;
//					successors[successorsCnt].node.h = getHeuristic(successors[successorsCnt].node.position, end) * 10;
//					successors[successorsCnt].node.f = successors[successorsCnt].node.g + successors[successorsCnt].node.h;
//
//					/*ii) if a node with the same position as
//					successor is in the OPEN list which has a
//					lower f than successor, skip this successor*/
//					bool skipSuccessor = false;
//					for (int openListCnt = 0; openListCnt < (int)openList.size(); ++openListCnt) {
//						if (compareXYStructs(openList[openListCnt].node.position, successors[successorsCnt].node.position) == true && openList[openListCnt].node.f < successors[successorsCnt].node.f) {
//							skipSuccessor = true;
//							break;
//						}
//					}
//					//printStrL({ "successor on open list, skipSuccessor", str(skipSuccessor) });
//					if (skipSuccessor == true) {
//						continue;
//					}
//
//					/*iii) if a node with the same position as
//					successor  is in the CLOSED list which has
//					a lower f than successor, skip this successor
//					otherwise, add  the node to the open list
//					end(for loop)*/
//					skipSuccessor = false;
//					for (int closedListCnt = 0; closedListCnt < (int)closedList.size(); ++closedListCnt) {
//						if (compareXYStructs(closedList[closedListCnt].node.position, successors[successorsCnt].node.position) == true && closedList[closedListCnt].node.f < successors[successorsCnt].node.f) {
//							skipSuccessor = true;
//							break;
//						}
//					}
//					//printStrL({ "successor on closed list, skipSuccessor", str(skipSuccessor) });
//					if (skipSuccessor == true) {
//						continue;
//						//printStr("\nskip successor");
//					}
//					else {
//						openList.push_back(successors[successorsCnt]);
//						//printStr("\nadd successor to open list");
//					}
//				}
//
//			}
//
//			/*e) push q on the closed list
//			end(while loop)*/
//			closedList.push_back(q);
//			/*printStr("\nadd q to closed list");
//			printInt((int)closedList.size());
//			printXYStructL({ q.node.position, start, end });*/
//			//pauseAtConsole();
//
//		}
//	}
//
//	//Path found
//	if (stopSearch == true && (int)closedList.size() > 0) {
//		printStr("\npath found");
//		
//		//Get end node index from closed list and add node position to path
//		int currentNodeIndex = -1;
//		for (int closedListCnt = 0; closedListCnt < (int)closedList.size(); ++closedListCnt) {
//			if (compareXYStructs(closedList[closedListCnt].node.position, end) == true) {
//				currentNodeIndex = closedListCnt;
//				break;
//			}
//		}
//		path.push_back(closedList[currentNodeIndex].node.position);
//
//		//Get path from closed list, starting from end node to start node, using parents to trace back
//		while (compareXYStructs(closedList[currentNodeIndex].node.position, start) == false) {
//
//			//Get next node using parent and add it to path
//			for (int closedListCnt = 0; closedListCnt < (int)closedList.size(); ++closedListCnt) {
//				if (compareXYStructs(closedList[closedListCnt].node.position, closedList[currentNodeIndex].parent.position) == true) {
//					currentNodeIndex = closedListCnt;
//					path.push_back(closedList[currentNodeIndex].node.position);
//					break;
//				}
//			}
//
//		}
//
//		//Reverse path so it starts with start node and ends with end node
//		reverse(path.begin(), path.end());
//
//	}
//	else {
//		printStr("\npath not found");
//		printStr(formatStr("closed list size: {}", { str((int)closedList.size()) }));
//		printStr("\npathfinding took too long");
//		//printVisualAStarPath(maze, path, start, end);
//	}
//
//	return path;
//}

//vector<XYStruct> getAStarPath(vector<vector<bool>>& maze, XYStruct start, XYStruct end) {
//	vector<XYStruct> path;
//
//	//make an openlist containing only the starting node
//	vector<nodeWithParentStruct> openList;
//	nodeWithParentStruct startingNode;
//	startingNode.node.position = start;
//	startingNode.node.g = 0; //set g to 0
//	startingNode.node.h = getHeuristic(startingNode.node.position, end); //get heuristic
//	startingNode.node.f = startingNode.node.g + startingNode.node.h; //update f
//	openList.push_back(startingNode);
//
//	//make an empty closed list
//	vector<nodeWithParentStruct> closedList;
//
//	nodeWithParentStruct currentNode, previousCurrentNode;
//
//	//while (the destination node has not been reached) :
//	bool destinationNodeReached = false;
//	while (destinationNodeReached == false) {
//
//		//consider the node with the lowest f score in the open list
//		int nodeWithLowestFScoreIndex = -1, nodeWithLowestFScoreFScore = -1;
//		for (int openListCnt = 0; openListCnt < (int)openList.size(); ++openListCnt) {
//			if (openList[openListCnt].node.f > -1) {
//				if (nodeWithLowestFScoreIndex == -1 || nodeWithLowestFScoreIndex > -1 && openList[openListCnt].node.f < openList[nodeWithLowestFScoreIndex].node.f) {
//					nodeWithLowestFScoreIndex = openListCnt;
//					nodeWithLowestFScoreFScore = openList[openListCnt].node.f;
//				}
//			}
//		}
//		previousCurrentNode = currentNode;
//		currentNode = openList[nodeWithLowestFScoreIndex];
//
//		/*printStr("\nstart, end, current");
//		printXYStructL({ start, end, currentNode.node.position });*/
//
//		//Remove current node from the open list
//		openList.erase(openList.begin() + nodeWithLowestFScoreIndex);
//
//		//if (this node is our destination node) :
//		if (compareXYStructs(currentNode.node.position, end) == true) {
//			
//			//we are finished
//			destinationNodeReached = true;
//
//			//Set parent of current/end node
//			currentNode.parent = previousCurrentNode.node;
//
//			//Add current/end node to closed list
//			closedList.push_back(currentNode);
//
//		}
//		else {
//
//			//put the current node in the closed list and look at all of its neighbors
//			closedList.push_back(currentNode);
//			//printXYStructL({ start, end, currentNode.node.position, currentNode.parent.position });
//			vector<nodeWithParentStruct> neighbors;
//			for (int neighborXCnt = currentNode.node.position.x - 1; neighborXCnt <= currentNode.node.position.x + 1; ++neighborXCnt) {
//				for (int neighborYCnt = currentNode.node.position.y - 1; neighborYCnt <= currentNode.node.position.y + 1; ++neighborYCnt) {
//
//					//If neighbor is within maze, is not the current node and is a walkable node
//					if (neighborXCnt >= 0 && neighborXCnt <= (int)maze.size() - 1 && neighborYCnt >= 0 && neighborYCnt <= (int)maze[0].size() - 1 && compareXYStructs({ neighborXCnt, neighborYCnt }, currentNode.node.position) == false && maze[neighborXCnt][neighborYCnt] == false) {
//						nodeWithParentStruct neighborNode;
//						neighborNode.node.position = { neighborXCnt, neighborYCnt };
//						neighborNode.node.h = getHeuristic({ neighborXCnt, neighborYCnt }, end);
//						neighborNode.node.g = currentNode.node.g;
//						if (neighborNode.node.position.x == currentNode.node.position.x || neighborNode.node.position.y == currentNode.node.position.y) {
//							neighborNode.node.g += 10;
//						}
//						else {
//							neighborNode.node.g += 14;
//						}
//						neighborNode.node.f = neighborNode.node.g + neighborNode.node.h;
//						neighbors.push_back(neighborNode);
//					}
//
//				}
//			}
//
//			//for (each neighbor of the current node) :
//			for (int neighborsCnt = 0; neighborsCnt < (int)neighbors.size(); ++neighborsCnt) {
//				/*printStr("\nneighborsCnt, neighbors size");
//				printIntL({ neighborsCnt, (int)neighbors.size() });*/
//
//				//Check if neighbor is in closed list
//				bool neighborInClosedList = false;
//				int gOfNeighborInClosedList = -1;
//				for (int closedListCnt = 0; closedListCnt < (int)closedList.size(); ++closedListCnt) {
//					if (compareXYStructs(neighbors[neighborsCnt].node.position, closedList[closedListCnt].node.position) == true) {
//						neighborInClosedList = true;
//						gOfNeighborInClosedList = closedList[closedListCnt].node.g;
//						break;
//					}
//				}
//				/*printStr("\nneighbor in closed list");
//				printInt(neighborInClosedList);*/
//
//				//Check if neighbor is in open list
//				bool neighborInOpenList = false;
//				int gOfNeighborInOpenList = -1;
//				for (int openListCnt = 0; openListCnt < (int)openList.size(); ++openListCnt) {
//					if (compareXYStructs(neighbors[neighborsCnt].node.position, openList[openListCnt].node.position) == true) {
//						neighborInOpenList = true;
//						gOfNeighborInOpenList = openList[openListCnt].node.g;
//						break;
//					}
//				}
//				/*printStr("\nneighbor in open list");
//				printInt(neighborInOpenList);*/
//
//				//if (neighbor has lower g value than current and is in the closed list) :
//				//printIntL({ neighbors[neighborsCnt].node.g < currentNode.node.g && neighborInClosedList == true, currentNode.node.g < neighbors[neighborsCnt].node.g && neighborInOpenList == true, neighborInClosedList == false && neighborInOpenList == false });
//				//printIntL({ neighbors[neighborsCnt].node.g, currentNode.node.g, neighborInOpenList, neighborInClosedList });
//				if (neighbors[neighborsCnt].node.g < currentNode.node.g && neighborInClosedList == true) {
//					//printStr("\nneighbor g < current g and neighbor in closed list");
//
//					//replace the neighbor with the new, lower, g value
//					neighbors[neighborsCnt].node.g = gOfNeighborInClosedList;
//					neighbors[neighborsCnt].node.f = neighbors[neighborsCnt].node.g + neighbors[neighborsCnt].node.h; //update f
//
//					//current node is now the neighbor's parent
//					neighbors[neighborsCnt].parent = currentNode.node;
//
//				}
//				else if (currentNode.node.g < neighbors[neighborsCnt].node.g && neighborInOpenList == true) {
//					//else if (current g value is lower and this neighbor is in the open list) :
//					//printStr("\ncurrent g < neighbor g and neighbor in open list");
//
//					//replace the neighbor with the new, lower, g value
//					neighbors[neighborsCnt].node.g = gOfNeighborInOpenList;
//					neighbors[neighborsCnt].node.f = neighbors[neighborsCnt].node.g + neighbors[neighborsCnt].node.h; //update f
//
//					//change the neighbor's parent to our current node
//					neighbors[neighborsCnt].parent = currentNode.node;
//
//				}
//				else if (neighborInClosedList == false && neighborInOpenList == false) {
//					//else if this neighbor is not in both lists :
//					//printStr("\nneighbor not in closed list nor in open list");
//
//					//add it to the open list and set its g
//					neighbors[neighborsCnt].node.g = currentNode.node.g;
//					neighbors[neighborsCnt].node.f = neighbors[neighborsCnt].node.g + neighbors[neighborsCnt].node.h; //update f
//					openList.push_back(neighbors[neighborsCnt]);
//
//				}
//
//			}
//
//		}
//		//pauseAtConsole();
//
//	}
//
//	/*printInt((int)closedList.size());
//	pauseAtConsole();*/
//
//	//Create path
//	if ((int)closedList.size() > 0) {
//		nodeWithParentStruct nodeToFind;
//		nodeToFind.node.position = end;
//		bool startNodeFound = false;
//		while (startNodeFound == false) {
//			printXYStructL({ start, end, nodeToFind.node.position });
//			pauseAtConsole();
//
//			//Find next node
//			int closedListCnt = -1;
//			for (closedListCnt = 0; closedListCnt < (int)closedList.size(); ++closedListCnt) {
//				if (compareXYStructs(closedList[closedListCnt].node.position, nodeToFind.node.position) == true) {
//
//					//Add node to path
//					path.push_back(closedList[closedListCnt].node.position);
//
//					//Set next node to find
//					nodeToFind.node.position = closedList[closedListCnt].parent.position;
//
//					break;
//				}
//			}
//
//			//Check if start node found
//			if (compareXYStructs(closedList[closedListCnt].node.position, startingNode.node.position)) {
//				startNodeFound = true;
//			}
//
//		}
//
//		//Reverse path
//		reverse(path.begin(), path.end());
//
//	}
//
//	//printInt((int)path.size());
//	return path;
//
//	//Algorithm
//	/*make an openlist containing only the starting node
//	make an empty closed list
//	while (the destination node has not been reached) :
//		consider the node with the lowest f score in the open list
//		if (this node is our destination node) :
//			we are finished
//		if not:
//			put the current node in the closed list and look at all of its neighbors
//			for (each neighbor of the current node) :
//				if (neighbor has lower g value than current and is in the closed list) :
//					replace the neighbor with the new, lower, g value
//					current node is now the neighbor's parent
//				else if (current g value is lower and this neighbor is in the open list) :
//					replace the neighbor with the new, lower, g value
//					change the neighbor's parent to our current node
//
//				else if this neighbor is not in both lists :
//					add it to the open list and set its g*/
//}

//vector<XYStruct> getAStarPath(vector<vector<bool>>& maze, XYStruct start, XYStruct end) {
//	vector<XYStruct> path;
//
//	//let the openList equal empty list of nodes
//	//let the closedList equal empty list of nodes
//	vector<nodeWithParentStruct> openList, closedList;
//
//	//put the startNode on the openList(leave it's f at zero)
//	nodeWithParentStruct startNode;
//	startNode.node.position = start;
//	startNode.node.g = 0;
//	startNode.node.h = 0;
//	startNode.node.f = startNode.node.g + startNode.node.h;
//	openList.push_back(startNode);
//
//	bool endFound = false;
//
//	//while the openList is not empty
//	while ((int)openList.size() > 0 && endFound == false) {
//		
//		//	let the currentNode equal the node with the least f value
//		nodeWithParentStruct currentNode;
//		int fValue = -1, indexOfNodeWithLeastFValue = -1;
//		for (int openListCnt = 0; openListCnt < (int)openList.size(); ++openListCnt) {
//			if (fValue == -1 || openList[openListCnt].node.f < openList[indexOfNodeWithLeastFValue].node.f) {
//				fValue = openList[openListCnt].node.f;
//				indexOfNodeWithLeastFValue = openListCnt;
//			}
//		}
//		currentNode = openList[indexOfNodeWithLeastFValue];
//
//		//	remove the currentNode from the openList
//		openList.erase(openList.begin() + indexOfNodeWithLeastFValue);
//
//		//	add the currentNode to the closedList
//		closedList.push_back(currentNode);
//		//printXYStructL({ start, end, currentNode.node.position });
//
//		//	if currentNode is the goal
//		if (compareXYStructs(currentNode.node.position, end) == true) {
//			
//			//		You've found the end!
//			endFound = true;
//
//		}
//		else {
//
//			//	let the children of the currentNode equal the adjacent nodes
//			vector<nodeWithParentStruct> children;
//			for (int currentNodeXCnt = currentNode.node.position.x - 1; currentNodeXCnt <= currentNode.node.position.x + 1; ++currentNodeXCnt) {
//				for (int currentNodeYCnt = currentNode.node.position.y - 1; currentNodeYCnt <= currentNode.node.position.y + 1; ++currentNodeYCnt) {
//					if (currentNodeXCnt >= 0 && currentNodeXCnt <= (int)maze.size() - 1 && currentNodeYCnt >= 0 && currentNodeYCnt <= (int)maze[0].size() - 1) {
//						if (currentNodeXCnt != currentNode.node.position.x || currentNodeYCnt != currentNode.node.position.y) {
//							nodeWithParentStruct childNode;
//							childNode.node.position = { currentNodeXCnt, currentNodeYCnt };
//							children.push_back(childNode);
//						}
//					}
//				}
//			}
//
//			//	for each child in the children
//			for (int childrenCnt = 0; childrenCnt < (int)children.size(); ++childrenCnt) {
//				bool continueToBeginningOfForLoop = false;
//
//				bool childInClosedList = false;
//				for (int closedListCnt = 0; closedListCnt < (int)closedList.size(); ++closedListCnt) {
//					if (compareXYStructs(closedList[closedListCnt].node.position, children[childrenCnt].node.position) == true) {
//						childInClosedList = true;
//						break;
//					}
//				}
//
//				//		if child is in the closedList
//				if (childInClosedList == true) {
//					
//					//			continue to beginning of for loop
//
//				}
//				else {
//
//					//		child.g = currentNode.g + distance between child and current
//					int distanceBetweenChildAndCurrent = 0;
//					if (currentNode.node.position.x == children[childrenCnt].node.position.x || currentNode.node.position.y == children[childrenCnt].node.position.y) {
//						distanceBetweenChildAndCurrent = 10;
//					}
//					else {
//						distanceBetweenChildAndCurrent = 14;
//					}
//					children[childrenCnt].node.g = currentNode.node.g + distanceBetweenChildAndCurrent;
//
//					//		child.h = distance from child to end
//					children[childrenCnt].node.h = getHeuristic(children[childrenCnt].node.position, end);
//
//					//		child.f = child.g + child.h
//					children[childrenCnt].node.f = children[childrenCnt].node.g + children[childrenCnt].node.h;
//
//					for (int openListCnt = 0; openListCnt < (int)openList.size(); ++openListCnt) {
//
//						//		if child.position is in the openList's nodes positions
//						if (compareXYStructs(children[childrenCnt].node.position, openList[openListCnt].node.position) == true) {
//
//							//			if the child.g is higher than the openList node's g
//							if (children[childrenCnt].node.g > openList[openListCnt].node.g) {
//
//								//				continue to beginning of for loop
//								continueToBeginningOfForLoop = true;
//								break;
//
//							}
//
//						}
//
//					}
//				}
//
//				if (continueToBeginningOfForLoop == false) {
//
//					//		add the child to the openList
//					openList.push_back(children[childrenCnt]);
//
//				}
//			}
//
//		}
//
//	}
//
//	//printInt((int)closedList.size());
//
//	//let the openList equal empty list of nodes
//	//let the closedList equal empty list of nodes
//	//put the startNode on the openList(leave it's f at zero)
//	//while the openList is not empty
//	//	let the currentNode equal the node with the least f value
//	//	remove the currentNode from the openList
//	//	add the currentNode to the closedList
//	//	if currentNode is the goal
//	//		You've found the end!
//	//	let the children of the currentNode equal the adjacent nodes
//	//	for each child in the children
//	//		if child is in the closedList
//	//			continue to beginning of for loop
//	//		child.g = currentNode.g + distance between child and current
//	//		child.h = distance from child to end
//	//		child.f = child.g + child.h
//	//		if child.position is in the openList's nodes positions
//	//			if the child.g is higher than the openList node's g
//	//				continue to beginning of for loop
//	//		add the child to the openList
//}

vector<XYStruct> getAStarPath(vector<vector<bool>>& maze, XYStruct start, XYStruct end) {
	vector<XYStruct> path;

	//Algorithm:

}

void convertPathCoordinates(vector<XYStruct>& path, int conversionFactor) {
	for (int pathCnt = 0; pathCnt < (int)path.size(); ++pathCnt) {
		path[pathCnt].x *= conversionFactor;
		path[pathCnt].y *= conversionFactor;
	}
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


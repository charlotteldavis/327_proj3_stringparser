/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"
using namespace std;
using namespace KP_StringParserClass;


char *pStartTag;
char *pEndTag;
bool areTagsSet;

StringParserClass::StringParserClass(void) {
	pStartTag = NULL;
	pEndTag = NULL;
	areTagsSet = false;
}
StringParserClass::~StringParserClass(void) {
	cleanup();
}

int StringParserClass::setTags(const char *pStart, const char *pEnd) {
	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}
	pStartTag = new char[strlen(pStart)];
	pEndTag = new char[strlen(pEnd)];

	strncpy(pStartTag, pStart, strlen(pStart));
	strncpy(pEndTag, pEnd, strlen(pEnd));

	areTagsSet = true;
	return SUCCESS;
}

int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, std::vector<std::string> &myVector) {
	myVector.clear();
	if (pStartTag == NULL || pEndTag == NULL || pStartTag == 0
			|| pEndTag == 0) {
		return ERROR_TAGS_NULL;
	} else if (pDataToSearchThru == NULL) {
		return ERROR_DATA_NULL;
	}

	while (*pDataToSearchThru != '\0') {
		std::string data = "";
		bool found = true;
		char *pStartCopy = new char[strlen(pStartTag)];
		strncpy(pStartCopy, pStartTag, strlen(pStartTag));
		if (*pDataToSearchThru == '<') {
			while (*pStartCopy != '>') {
				if (*pDataToSearchThru != *pStartCopy) {
					found = false;
				}
				pStartCopy++;
				pDataToSearchThru++;
			}
			if (found) {
				pDataToSearchThru++;
				while (*pDataToSearchThru != '\0' && found) {
					if (*pDataToSearchThru == '<') {
						found = false;
						char *pEndCopy = new char[strlen(pEndTag)];
						strncpy(pEndCopy, pEndTag, strlen(pEndTag));
						while (*pEndCopy != '>') {
							if (*pDataToSearchThru != *pEndCopy) {
								found = true;
							}
							pDataToSearchThru++;
							pEndCopy++;
						}
					}
					else {
						data += *pDataToSearchThru;
						pDataToSearchThru++;
					}
				}
				if(!found) {
					myVector.push_back(data);
				}
				data = "";
			}
		} else {
			pDataToSearchThru++;
		}
	}
	return SUCCESS;
}

void StringParserClass::cleanup() {
	*pStartTag = NULL;
	*pEndTag = NULL;
	areTagsSet = false;
}

int StringParserClass::findTag(char *pTagToLookFor, char *&pStart,
		char *&pEnd) {
	int length = strlen(pTagToLookFor);
	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}
	int i = 0;
	while (pStart[i] != 0) {
		bool found = true;
		if (pStart[i] == '<') {
			for (int j = 0; j < length; j++) {
				if (pEnd[i + j] != pTagToLookFor[j]) {
					found = false;
				}
			}
			if (found) {
				*pStart = pStart[i];
				*pEnd = pStart[i + length];
				return SUCCESS;
			}
		}
		i++;
	}
	return FAIL;
}


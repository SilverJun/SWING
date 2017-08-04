#ifndef _LIB_SWING_COLLECTION_H_
#define _LIB_SWING_COLLECTION_H_

#include <string>
#include <vector>
#include <map>

struct String
{
	std::string _rawData;

	String(char* str);
	explicit String(char ch);

	int index(char ch);
	void pushLast(char ch);
	char popLast();
	void insertAt(int index, char ch);
	void insertAt(int index, char* str);
	void insertAt(int index, String str);
	void removeAt(int index);
	void removeAll();
};

#endif

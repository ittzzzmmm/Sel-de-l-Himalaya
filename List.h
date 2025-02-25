#pragma once
#include<vector>
#include<string>

struct List
{
	int tag;
	std::string name;
	int price;
};

void saveListToFile(const std::vector<List>& lists, const std::string& fileName);
std::vector<List>loadListFromFile(const std::string& fileName);


#include "List.h"
#include<string>
#include<vector>
#include<filesystem>
#include<fstream>
#include<algorithm>

void saveListToFile(const std::vector<List>& lists, const std::string& fileName)
{
	std::ofstream ostream(fileName);
	ostream << lists.size();

	for (const List& list : lists) {

		std::string name = list.name;
		std::replace(name.begin(), name.end(), ' ', '_');

		ostream << '\n' << list.tag << ' ' << name << ' ' << list.price;
	}
}

std::vector<List> loadListFromFile(const std::string& fileName)
{
	if (!std::filesystem::exists(fileName)) {
		return std::vector<List>();
	}

	std::vector<List> lists;
	std::ifstream istream(fileName);

	int n;
	istream >> n;

	for (int i = 0; i < n; i++) {
		int tag;
		std::string name;
		int price;

		istream >> tag >> name >> price;
		std::replace(name.begin(), name.end(), '_', ' ');
		lists.push_back(List{ tag,name,price });
	}

	return lists;
}
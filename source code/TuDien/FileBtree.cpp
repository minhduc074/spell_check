#include "FileBtree.h"

char* String2CharArray(string str)
{
	char* ret = new char[str.length()];
	for (int i = 0; i < str.length(); i++)
	{
		ret[i] = str[i];
	}
	ret[str.length()] = '\0';
	return ret;
}

void readFile(BTree &t)
{
	ifstream fi ("dict.txt");
	string line;
	if (fi.is_open())
	{
		while (getline(fi, line))
		{
			t.insert(String2CharArray(line));
		}
		fi.close();
	}

	else cout << "Unable to open file";
}

vector<string> split(string str)
{
	vector<string> SS; //Vector of string 
	while (!str.empty())
	{
		SS.push_back(str.substr(0, str.find(" ")));// add word to vector 
		if (str.find(" ") > str.size()) //Check if found " " (Space) 
		{
			break;
		}
		else
		{
			str.erase(0, str.find(" ") + 1); // Update string 
		}
	}
	return SS;
}

vector<string> Check(vector<string> SS, BTree t)
{
	vector<string> ret;

	string url;
	for (int i = 0; i < SS.size(); i++)
	{
		t.search(String2CharArray(SS[i]), url);
		ret.push_back(url);
		url = "";
	}

	return ret;
}

int heightTree(vector<string> result)
{
	int h = 0;
	for each (string var in result)
	{
		if (h < var.length()) h = var.length();
	}
	return h;
}

void writeFile(BTree t)
{
	vector<string> SS;
	vector<string> result;
	ifstream fi("text.txt");
	string line;

	if (fi.is_open())
	{
		while (getline(fi, line))
		{
			SS = split(line);
		}
		fi.close();
	}

	result = Check(SS, t);

	ofstream fo("result.txt");
	if (fo.is_open())
	{
		fo << "--Tree info" << endl;
		fo << "+ Number of nodes: " << t.countNode() << endl;
		fo << "+ Size of each node: " << t.sizeNode() << endl;
		fo << "+ Max keys in each node: " << t.maxKey() << endl;
		fo << "+ Min keys in each node: " << t.minKey() << endl;
		fo << "+ Average fulfill (%): " << t.Averagefulfill()*100 << endl;
		fo << "+ Number of leaf-nodes: " << t.countLeaf() << endl;
		fo << "+ Height of tree: " << heightTree(result) << endl;
		fo << "--Spelling result " << endl;
		for (int i = 0; i < SS.size(); i++)
		{
			fo << SS[i] << ": R ";
			for (int j = 0; j < result[i].length(); j++)
			{
				if (result[i] == "0");
					
				else fo << result[i][j] << " ";
			}
			fo << endl;
		}
	}

	fo.close();

}

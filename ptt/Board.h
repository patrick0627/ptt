#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

class Board
{
public:
	Board();
	//Board(string absolutedPath);
	Board(string absolutedPath, string _boardName,Board* _parent) 
	{
		path = absolutedPath;
		boardName = _boardName;
		parent = _parent;
	}

	// ���}��ư�
	vector<Board>subBoard; //��vector �� size = 0�� �N��ܩ� �~�|���峹
	Board* parent = NULL;
	vector<string> articalsTitle;
	vector<string> articalsPath;
	vector<string> articalsUserID;
	int count=0;

	//�\��� 
	bool readArticalFile(string absolutedPath);
	void updateForPost(string _title, string _path, string _userID)
	{
		this->articalsTitle.push_back(_title);
		this->articalsPath.push_back(_path);
		this->articalsUserID.push_back(_userID);
	}

	//set data
	void setpath(string a) { path = a; }
	void setboardName(int a) { boardName = a; }

	//get data
	string getpath() { return path; }
	string getboardName() { return boardName; }
	
private:
	string path;
	string boardName;
};

Board::Board()
{
	//path ="C:\\Users\\Weiting\\Desktop\\ptt\\ptt\\DataBase\\BoardInfo";
	//path = "D:\\user\\Desktop\\ptt\\ptt\\DataBase\\BoardInfo";
	path = "./DataBase/BoardInfo";
	boardName = "PTT";
	parent = NULL;
};
//
//Board::Board(string absolutedPath)
//{
//	path = absolutedPath;
//	for (int i = absolutedPath.size(); i >= 0; i--)
//	{
//		if (absolutedPath[i] == '\\')
//		{
//			boardName.assign(absolutedPath,i+1, absolutedPath.size()-i-1);
//		}
//	}
//
//};

bool Board::readArticalFile(string absolutedPath)
{
	fstream file(absolutedPath);
	if (file.good())
	{
		string opcode;
		while (file >> opcode) {
			if (opcode == "user:")
			{
				string _name;
				file >> _name;
				articalsUserID.push_back(_name);
			}
			else if (opcode == "title")
			{
				string _title;
				getline(file,_title);
				//�ഫ������| �� �۹���|
				//**********************************
				string relativePath;
				stringstream ss(absolutedPath);
				string buf;
				while (getline(ss, buf, '\\'))
				{
					if (buf == "DataBase")
					{
						relativePath = "./DataBase";
						while (getline(ss, buf, '\\'))
						{
							relativePath += "/" + buf;
						}
						break;
					}
				}
				//===========================================
				articalsPath.push_back(relativePath);
				articalsTitle.push_back(_title);
				return true;
			}
			else
			{
				cout << "error!!! exception: wrong artical formate => inserting artical to board failed" << endl;
				return false;
			}
		}
	}
	else
	{
		cout << "error!!! exception: wrong path => inserting artical to board failed"<<endl;
		return false;
	}
	return true;
}
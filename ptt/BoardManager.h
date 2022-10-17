#pragma once
//#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<algorithm>
#include <experimental/filesystem>
#include<conio.h>
#include<io.h>
#include"Board.h"
#include"User.h"
#include"Viewer.h"

using namespace std;
//void getFiles(string path, vector<string>& files);

void get_filenames(std::experimental::filesystem::path path, vector<std::string>& _files);

enum BoardState
{
	Leave =0,
	MENU = 1,
	SELECT_BOARD = 2,
	BOARD = 3,
	POST = 4,
	EDIT =5,
	MAIL =6
};

enum KeyBoardASKII
{	
	ENTER=13,
	LEFT=75,
	UP=72,
	RIGHT=77,
	DOWN=80
};

class BoardManager //���Ⱥ޲z�ާ@
{
public:
	BoardManager();
	BoardManager(string);	//readfile
	
	// ���� state
	void logging();
	void selectBoard();
	void selectArtical();
	void postArtical();
	void editArtical();
	void deleteArtical();
	void leaveMsg();
	void readMail();

	// set data
	void setState(int _state) { state = _state; };
	
	//get data
	int getState() { return state; };

private:
	int editArticalIndex=0;
	std::vector <User*> users;
	Board boards;
	Board* nowBoard = &boards;
	int authority;
	int current_user = -1;
	int state;
	Viewer viewer;
};

//void getFiles(string path, vector<string>& files)
//{
//	//�ɮױ���N�X  
//	long   hFile = 0;
//	//�ɮ׸�T  
//	struct _finddata_t fileinfo;
//	string p;
//	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
//	{
//		do
//		{
//			//�p�G�O�ؿ�,���N��  
//				//�p�G���O,�[�J�C��  
//			if ((fileinfo.attrib & _A_SUBDIR))
//			{
//				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
//				{
//					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
//				}
//			}
//			else
//			{
//				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
//			}
//		} while (_findnext(hFile, &fileinfo) == 0);
//		_findclose(hFile);
//	}
//};
void get_filenames(std::experimental::filesystem::path path, vector<std::string>& _files)
{
	namespace stdfs = std::experimental::filesystem;

	// http://en.cppreference.com/w/cpp/experimental/fs/directory_iterator
	const stdfs::directory_iterator end{};

	for (stdfs::directory_iterator iter{ path }; iter != end; ++iter)
	{
		// http://en.cppreference.com/w/cpp/experimental/fs/is_regular_file 
		if (stdfs::is_regular_file(*iter))// comment out if all names (names of directories tc.) are required
		{
			_files.push_back(iter->path().string());
		}
		else
		{
			get_filenames(iter->path(), _files);
		}
	}
}

BoardManager::BoardManager()
{
	users.clear();
	authority = UserAuthority::GUEST;
	state = BoardState::MENU;
	current_user = -1;
	nowBoard = &boards;
}
//BoardManager::BoardManager(string DBpath)
//{
//	//initial
//	//**************************
//	users.clear();
//	authority = UserAuthority::GUEST;
//	state = BoardState::MENU;
//	current_user = 0;
//	nowBoard = &boards;
//	users.push_back(new Guest("guest01","0"));
//	//==============================
//
//	//struct database
//	vector<string> files;
//	//getFiles(DBpath, files);
//	get_filenames(DBpath,files);
//	for (int i = 0; i < files.size(); i++)
//	{
//		string allPath;
//		int startSize = 33;		// the size of (D:\user\Desktop\ptt\ptt\DataBase\)
//		allPath.assign(files[i], startSize, files[i].size() - startSize);
//		stringstream ss(allPath);
//
//
//		string buf;
//		getline(ss, buf, '\\');
//		//��ƳB�z -1.�峹���| 
//		//************************************************
//		if (buf == "BoardInfo")
//		{
//			string boardName;
//			getline(ss, boardName, '\\');
//
//			string extension = "";//���ɦW
//			if (boardName.size() > 4)
//			{
//				extension.assign(boardName, boardName.size() - 4, 4);
//			}
//
//			Board* target = &boards;
//			//�W�Kboard �ç��峹 �ؼ�board
//			while (extension != ".txt")
//			{
//				bool notFound = true;
//				//��O�_�w�s�b��board
//				for (int j = 0; j < target->subBoard.size(); j++)
//				{
//					//�����
//					if (boardName == target->subBoard[j].getboardName())
//					{
//						target = &target->subBoard[j];
//						notFound = false;
//						break;
//					}
//				}
//				//�S���
//				if (notFound)
//				{
//					string tmpPath = target->getpath() + "\\" + boardName;
//					target->subBoard.push_back(Board(tmpPath, boardName,target));
//					target = &target->subBoard.back();
//				}
//
//				getline(ss, boardName, '\\');
//				if (boardName.size() > 4)
//				{
//					extension.assign(boardName, boardName.size() - 4, 4);
//				}
//			}
//			//�峹�ɮ�
//			target->readArticalFile(files[i]);
//		}
//		//=====================================================
//
//		//��ƳB�z -1.�ϥΪ̸�Ƹ��|
//		//*******************************************************
//		else if (buf == "UserInfo")
//		{
//			string name;
//			getline(ss, name, '\\');
//			if (name == "Administrator")
//			{
//				getline(ss, name, '\\');
//				User* tmp = new Administrator(name);
//				tmp->download(files[i]);
//				users.push_back(tmp);
//			}
//			else if (name == "Member")
//			{
//				getline(ss, name, '\\');
//				User* tmp = new Member(name);
//				tmp->download(files[i]);
//				users.push_back(tmp);
//			}
//		}
//		//========================================================
//
//	}
//}
BoardManager::BoardManager(string DBpath)
{
	//initial
	//**************************
	users.clear();
	authority = UserAuthority::GUEST;
	state = BoardState::MENU;
	current_user = 0;
	nowBoard = &boards;
	users.push_back(new Guest("guest01", "0"));
	//==============================

	//struct database
	vector<string> files;
	//getFiles(DBpath, files);
	get_filenames(DBpath, files);
	for (int i = 0; i < files.size(); i++)
	{
		string allPath;
		int startSize = 33;		// the size of (D:\user\Desktop\ptt\ptt\DataBase\)
		allPath.assign(files[i], startSize, files[i].size() - startSize);
		stringstream ss(allPath);


		string buf;
		getline(ss, buf, '\\');
		//��ƳB�z -1.�峹���| 
		//************************************************
		if (buf == "BoardInfo")
		{
			string boardName;
			getline(ss, boardName, '\\');

			string extension = "";//���ɦW
			if (boardName.size() > 4)
			{
				extension.assign(boardName, boardName.size() - 4, 4);
			}

			Board* target = &boards;
			//�W�Kboard �ç��峹 �ؼ�board
			while (extension != ".txt")
			{
				bool notFound = true;
				//��O�_�w�s�b��board
				for (int j = 0; j < target->subBoard.size(); j++)
				{
					//�����
					if (boardName == target->subBoard[j].getboardName())
					{
						target = &target->subBoard[j];
						notFound = false;
						break;
					}
				}
				//�S��� �W�[�ݪO�ܼƾڮw
				if (notFound)
				{
					string tmpPath = target->getpath() + "/" + boardName;
					target->subBoard.push_back(Board(tmpPath, boardName, target));
					target = &target->subBoard.back();
				}

				getline(ss, boardName, '\\');
				if (boardName.size() > 4)
				{
					extension.assign(boardName, boardName.size() - 4, 4);
				}
			}
			//�峹�ɮ�
			target->readArticalFile(files[i]);
		}
		//=====================================================

		//��ƳB�z -1.�ϥΪ̸�Ƹ��|
		//*******************************************************
		else if (buf == "UserInfo")
		{
			string name;
			getline(ss, name, '\\');
			if (name == "Administrator")
			{
				getline(ss, name, '\\');
				User* tmp = new Administrator(name);
				tmp->download(files[i]);
				users.push_back(tmp);
			}
			else if (name == "Member")
			{
				getline(ss, name, '\\');
				User* tmp = new Member(name);
				tmp->download(files[i]);
				users.push_back(tmp);
			}
		}
		//========================================================

	}
}

void BoardManager::logging()
{
	cout << "�п�J�N���A�ΥH guest ���[�A�ΥH new ���U:";
	string opCode;
	cin >> opCode;

	if (opCode == "guest")
	{
		current_user = 0;
		authority = UserAuthority::GUEST;
		state = BoardState::SELECT_BOARD;
		return;
	}
	else if (opCode == "new")
	{
		cout << "Please input your username: ";
		bool flag = 0; //�ݬO�_���U�L
		User* newMember = new Member;
		string name;
		cin >> name;
		for (int i = 0; i < users.size(); i++)
		{
			if (name == users[i]->getUsername())
			{
				cout << "This username has been used, Please try another one" << endl;
				flag = 1; //���U�L��ܬ�1
				break;
			}
		}

		if (flag == 0)
		{
			cout << "Please set Your Password: ";
			newMember->setUsername(name);
			string password;
			cin >> password;
			newMember->setPassword(password);
			users.push_back(newMember);
			cout << "Welcome To ptt" << endl;
			newMember->Established_Data();
		}
	}
	else
	{
		string _userID = opCode;
		bool flag = 0; //�ˬd�O�_���b��
		for (int i = 0; i < users.size(); i++)
		{
			if (_userID == users[i]->getUsername())
			{
				flag = 1;
				cout << "Please input the Password: ";
				string _userPassword;
				cin >> _userPassword;
				if (_userPassword == users[i]->getPassword())
				{
					//�i�J�ݪO
					current_user = i;
					authority = users[i]->getAuthority();
					state = BoardState::SELECT_BOARD;
					return;
				}
				else
				{
					cout << "Wrong Password" << endl;
				}
				break; 
			}
		}

		if (flag == 0)
		{
			cout << "Can't find the account" << endl;
		}
	}
}

//��ܬݪO [N]�s�W�ݪO [D]�R���ݪO (�ȭ��޲z��)
void BoardManager::selectBoard()
{
	char input;
	unsigned int arrowIndex = 0;
	system("CLS");
	viewer.showBoard(nowBoard,0);
	while (input = _getch())
	{
		//��J [N]�s�W�ݪO (�ȭ��޲z��)
		///*******************************************
		if (input == 'N')
		{
			if (this->authority == UserAuthority::ADMIN)
			{
				cout << "�O�_�n�b�i" << nowBoard->getboardName() << "�j���s�W�ݪO (input:y):";
				string answer;
				cin >> answer;
				if (answer == "y")
				{
					//��J�ݪO�W
					string newBoardName;
					cout << "��J�n�s�W���ݪO�W��: ";
					cin >> newBoardName;

					//���ɷs��Ƨ�
					string FolderPath = nowBoard->getpath() +"/"+ newBoardName;
					const char* a = FolderPath.c_str();
					if (_mkdir(a)==0)
					{
						//�O�����s�ݪO
						Board addBoard(FolderPath, newBoardName, nowBoard);
						nowBoard->subBoard.push_back(addBoard);

						//�[�J�ܳ���
						cout << "�{���[�J�ܳ���\n";
						nowBoard = &(nowBoard->subBoard.back());
						state = BoardState::POST;
						return;
					}
					else
					{
						cout << "�w�s�b���ݪO\n";
						continue;
					}
				}
			}
			else
			{
				cout << "�v������ �D�޲z�����o�s�W�ݪO";
				continue;
			}
		}
		//��J [D]�R���ݪO (�ȭ��޲z��)
		///*******************************************
		else if (input == 'D')
		{
			if (this->authority == UserAuthority::ADMIN)
			{
				cout << "�O�_�n�R��" << arrowIndex+1 
					<< ".�i�ݪO:" << nowBoard->subBoard[arrowIndex].getboardName() << "�j(input:y):";
				string answer;
				cin >> answer;
				if (answer == "y")
				{
					std::experimental::filesystem::remove_all(nowBoard->subBoard[arrowIndex].getpath());
					nowBoard->subBoard.erase(nowBoard->subBoard.begin() + arrowIndex);
				}

				system("CLS");
				viewer.showBoard(nowBoard, 0);
				continue;
			}
			else
			{
				cout << "�v������ �D�޲z�����o�R���ݪO";
				continue;
			}
		}
		//��J [M]�H�H
		//**********************************************
		else if (input == 'M')
		{
			if (this->authority != UserAuthority::GUEST)
			{
				cout << "�O�_�n�H�H��(input:y):";
				string answer;
				cin >> answer;
				if (answer == "y")
				{
					string receiver;
					int flag = 0;
					cout << "�п�J����H: " << endl;
					cin >> receiver;
					for (int i = 0; i < users.size(); i++)
					{
						if (receiver == users[i]->getUsername())
						{
							users[current_user]->sendmessage(*users[i]);
							flag = 1;
							break;
						}
					}
					if (flag == 0)
					{
						cout << "This account doesn't exist" << endl;
					}
					break;
				}
				continue;
			}
			else
			{
				cout << "�v�������A�X�Ȥ��o�H�H\n";
				continue;
			}
		}
		//��J [O]�\Ū�H��
		//**********************************************
		else if (input == 'O')
		{
			if (this->authority != UserAuthority::GUEST)
			{
				cout << "�O�_�n�\Ū�H��(input:y):";
				string answer;
				cin >> answer;
				if (answer == "y")
				{
					state = BoardState::MAIL;
					return;
				}
			}
			else
			{
				cout << "�v�������A�X�Ȥ��o���H\n";
				continue;
			}
		}
		//==========================================================
		// ��J�Ʀr���� �ӦC��ݪO ���ަ�m  key num 0~9  
		//****************************************************************************
		else if ((input > 48 && input < 58)/* || (input > 95 && input < 106)*/)
		{
			string jumpIndex;
			cout << "���ܲĴX��:";

			//char tmp = '0'+((input - 95 > 0) ? input - 96 : input - 48);
			char tmp = '0' + (input - 48);
			jumpIndex += tmp;
			cout << tmp;

			while (input = _getch())
			{
				if ((input > 48 && input < 58)/* || (input > 95 && input < 106)*/)
				{
					//char tmp = '0'+((input - 95 > 0) ? input - 96 : input - 48);
					tmp = '0' + (input - 48);
					jumpIndex += tmp;
					cout << tmp;
				}
				else if (input == KeyBoardASKII::ENTER)
				{
					break;
				}
			}
			if (jumpIndex.size() > 4)
			{
				string temp;
				arrowIndex = stoi(temp.assign(jumpIndex, jumpIndex.size() - 6, 6))-1;
			}
			else
			{
				arrowIndex = stoi(jumpIndex)-1;
			}
			if (arrowIndex > nowBoard->subBoard.size())
			{
				arrowIndex = nowBoard->subBoard.size() - 1;
			}
		}
		//=======================================================================
		// ��J��V�� ���s��ptt
		//***********************************************************************
		else
		{
			input = _getch();
			switch (input)
			{
			case KeyBoardASKII::UP:
				(arrowIndex > 0) ? arrowIndex -= 1 : 0;
				break;
			case KeyBoardASKII::DOWN:
				(arrowIndex < nowBoard->subBoard.size() - 1) ? arrowIndex += 1 : arrowIndex;
				break;
			case KeyBoardASKII::LEFT:
				if (nowBoard->parent != NULL)
				{
					nowBoard = nowBoard->parent;
				}
				// �̤ܳW�h�ݪO �߰ݬO�_�n�X
				//********************************************************
				else 
				{
					cout << "�O�_�n�n�XPTT�F(input:y):";
					string answer;
					cin>>answer;
					if (answer == "y")
					{
						state = BoardState::MENU;
						current_user = -1;
						this->authority = -1;
						this->nowBoard = &boards;
						system("CLS");
						return;
					}
				}
				//=========================================================
				arrowIndex = 0;
				break;
			case KeyBoardASKII::RIGHT:
				nowBoard = &nowBoard->subBoard[arrowIndex];
				nowBoard->count += 1;
				break;
			default:
				break;
			}
		}
		//=======================================================================

		// �ܩ��h�ݪ� ����ܤ峹���D ���X��state fuction
		//***********************************************************************
		if (nowBoard->subBoard.size() == 0)
		{
			state = BoardState::BOARD;
			break;
		}
		//=======================================================================

		system("CLS");
		viewer.showBoard(nowBoard,arrowIndex);
	}
}

//��ܤ峹 [->]��ܤ峹 [X]�峹������N��  [P]�o��峹 [E]�s��峹 [d]�R���峹
void BoardManager::selectArtical() 
{
	char input;
	unsigned int arrowIndex = 0;
	system("CLS");
	viewer.showTitle(nowBoard,0);
	while (input = _getch())
	{
		//��J P �o��峹 ���e�ݪO 
		///*******************************************
		if (input == 'P')
		{
			if (this->authority == UserAuthority::GUEST) 
			{
				cout << "�v������ �X�Ȥ��o�o��峹";
				continue;
			}
			cout << "�O�_�n�b�i" << nowBoard->getboardName() << "�j���o��峹 (input:y):";
			string answer;
			cin >> answer;
			if (answer == "y")
			{
				state = BoardState::POST;
				return;
			}
		}
		//��J E �ק�峹 ���e�ݪO 
		///*******************************************
		else if (input == 'E')
		{
			if (nowBoard->articalsUserID[arrowIndex] != users[current_user]->getUsername())
			{
				cout << "�D�o��峹�� ���o�ק�峹";
				continue;
			}
			cout << "�O�_�n�s��" << arrowIndex << ".�i���D:" << nowBoard->articalsTitle[arrowIndex] << "�j(input:y):";
			string answer;
			cin >> answer;
			if (answer == "y")
			{
				state = BoardState::EDIT;
				editArticalIndex = arrowIndex;
				return;
			}
		}
		//��J d �R����e�峹  
		///*******************************************
		else if (input == 'D')
		{
			if (this->authority == UserAuthority::GUEST)
			{
				cout << "�v������ �X�Ȥ��o�R���峹";
				continue;
			}
			else if (this->authority == UserAuthority::MEMBER &&
				nowBoard->articalsUserID[arrowIndex] != users[current_user]->getUsername())
			{
				cout << "�v������ �D�o��峹�� ���o�R���峹";
				continue;
			}
			else if ( (nowBoard->articalsUserID[arrowIndex] == users[current_user]->getUsername()) 
				|| this->authority == UserAuthority::ADMIN)
			{
				cout << "�O�_�n�R��"<< arrowIndex<<".�i���D:" << nowBoard->articalsTitle[arrowIndex] << "�j(input:y):";
				string answer;
				cin >> answer;
				if (answer == "y")
				{
					editArticalIndex = arrowIndex;
					deleteArtical();
				}
				system("CLS");
				viewer.showTitle(nowBoard, 0);
				continue;
			}
		}
		// ��J�Ʀr���� �ӦC��ݪO �峹���ަ�m  key num 0~9  
		//****************************************************************************
		else if ((input > 48 && input < 58)/* || (input > 95 && input < 106)*/)
		{
			string jumpIndex;
			cout << "���ܲĴX��:";

			//char tmp = '0'+((input - 95 > 0) ? input - 96 : input - 48);
			char tmp = '0' + (input - 48);
			jumpIndex += tmp;
			cout << tmp;

			while (input = _getch())
			{
				if ((input > 48 && input < 58)/* || (input > 95 && input < 106)*/)
				{
					//char tmp = '0'+((input - 95 > 0) ? input - 96 : input - 48);
					tmp = '0' + (input - 48);
					jumpIndex += tmp;
					cout << tmp;
				}
				else if (input == KeyBoardASKII::ENTER)
				{
					break;
				}
			}
			if (jumpIndex.size() > 6)
			{
				string temp;
				arrowIndex = stoi(temp.assign(jumpIndex, jumpIndex.size() - 6, 6));
			}
			else
			{
				arrowIndex = stoi(jumpIndex);
			}
			if (arrowIndex > nowBoard->articalsTitle.size())
			{
				arrowIndex = nowBoard->articalsTitle.size() - 1;
			}
		}
		else
		{
			input = _getch();
			switch (input)
			{
			//���W �b�Y���W
			case KeyBoardASKII::UP:
				(arrowIndex > 0) ? arrowIndex -= 1 : 0;
				break;
			//���U �b�Y���U
			case KeyBoardASKII::DOWN:
				(arrowIndex < nowBoard->articalsTitle.size() - 1) ? arrowIndex += 1 : arrowIndex;
				break;
			//���� ���X�ݪO
			case KeyBoardASKII::LEFT:
				state = BoardState::SELECT_BOARD;
				nowBoard = nowBoard->parent;
				return;
			//���k �i�J�峹����
			case KeyBoardASKII::RIGHT:
				//��ܤ峹
				/********************************************************************/
				system("CLS");
				viewer.showArtical(nowBoard->articalsPath[arrowIndex]);
				while (input = _getch())
				{
					//���N��
					//*****************************
					if (input == 'X' || input == 'x')
					{
						if (authority == UserAuthority::MEMBER || authority == UserAuthority::ADMIN)
						{
							editArticalIndex = arrowIndex;
							leaveMsg();
							system("CLS");
							viewer.showArtical(nowBoard->articalsPath[arrowIndex]);
							continue;
						}
						else
						{
							cout<<"�X�Ȥ��o����";
							continue;
						}
					}
					//============================
					input = _getch();
					if (input == KeyBoardASKII::LEFT)
					{
						break;
					}
				}
				/*********************************************************************/
				break;
			default:
				break;
			}
		}
		system("CLS");
		viewer.showTitle(nowBoard,arrowIndex);
	}
}

void BoardManager::postArtical()
{
	string _title;
	string intent;
	if (viewer.postArtical(_title,intent))
	{
		//�g�� �s�J��Ʈw
		
		//�إ߬۹���|
		string _articalPath;
		_articalPath = nowBoard->getpath(); //�o��{�b���ݪO�W
		_articalPath += "/" + to_string(nowBoard->articalsPath.size());
		_articalPath += ".txt";
		while ((find(nowBoard->articalsPath.begin(), nowBoard->articalsPath.end(), _articalPath) != nowBoard->articalsPath.end()))
		{
			//cout << "nono~�����o" << endl;
			_articalPath = nowBoard->getpath() +"/" +to_string(nowBoard->articalsPath.size() + 1) + ".txt";
		}

		ofstream output(_articalPath);

		if (!output.fail())
		{
			//�}�l�g��!
			output << "user: " << users[current_user]->getUsername() << endl;
			output << "title " << _title << endl;
			output << "-STARTARTICAL-" << endl;
			output << intent << endl;
			output << "-ENDARTICAL-" << endl;
			output << "message" << endl;
		}
		else
		{
			cout << "�إߤ峹���� �ˬd�g�ɸ��|";
		}


		//�ݪO��s�ƾ�
		nowBoard->updateForPost(_title,_articalPath,users[current_user]->getUsername());
		//�ϥΪ̧�s�ƾ�
		users[current_user]->updateForPost(_articalPath,_title);

	}
	state = BoardState::BOARD;
}

void BoardManager::editArtical()
{
	string _title;
	string intent;
	if (viewer.postArtical(_title,intent))
	{

		fstream file(nowBoard->articalsPath[editArticalIndex],ios::out | ios::trunc);
		//file.adjustfield(ios::trunc);
		//�ץ��峹 ��Ʈw�ɮ�
		if (file.good())
		{
			//�}�l�g��!
			file << "user: " << users[current_user]->getUsername() << endl;
			file << "title " << _title << endl;
			file << "-STARTARTICAL-" << endl;
			file << intent << endl;
			file << "-ENDARTICAL-" << endl;
			file << "message" << endl;
		}
		else
		{
			cout << "�إߤ峹���� �ˬd�g�ɸ��|";
		}
	}
	editArticalIndex = -1;
	state = BoardState::BOARD;
}

void BoardManager::deleteArtical()
{
	string _title, intent;
	if (users[current_user]->getUsername() == nowBoard->articalsUserID[editArticalIndex])
	{
		_title = "�i����w�Q�@�̧R���j";
	}
	else if (users[current_user]->getAuthority() == UserAuthority::ADMIN)
	{
		string cause;
		cout << "��J�R����]�ιH�Ϩƶ�:";
		getline(cin, cause);
		getline(cin, cause);
		_title = "�i����w�Q�޲z���R���A�R����]:<<"+cause+"�j";
	}
	fstream file(nowBoard->articalsPath[editArticalIndex], ios::out | ios::trunc);
	//�ץ��峹 ��Ʈw�ɮ�
	if (file.good())
	{
		//�}�l�g��!
		file << "user: " << users[current_user]->getUsername() << endl;
		file << "title " << _title << endl;
		file << "-STARTARTICAL-" << endl;
		file << intent << endl;
		file << "-ENDARTICAL-" << endl;
		file << "message" << endl;
		//��s���|
		nowBoard->articalsTitle[editArticalIndex] = _title;
	}
	else
	{
		cout << "�R���峹���� �ˬd�g�ɸ��|\n";
	}

}

void BoardManager::readMail()
{
	char input;
	unsigned int arrowIndex = 0;
	system("CLS");
	vector<pair<string, string>> mailBox = users[current_user]->getMail();
	viewer.showMailList(mailBox, 0);
	while (input = _getch())
	{
		// ��J�Ʀr���� �ӦC��l�� ���ަ�m  key num 0~9  
		//****************************************************************************
		if ((input > 48 && input < 58)/* || (input > 95 && input < 106)*/)
		{
			string jumpIndex;
			cout << "���ܲĴX��:";

			//char tmp = '0'+((input - 95 > 0) ? input - 96 : input - 48);
			char tmp = '0' + (input - 48);
			jumpIndex += tmp;
			cout << tmp;

			while (input = _getch())
			{
				if ((input > 48 && input < 58)/* || (input > 95 && input < 106)*/)
				{
					//char tmp = '0'+((input - 95 > 0) ? input - 96 : input - 48);
					tmp = '0' + (input - 48);
					jumpIndex += tmp;
					cout << tmp;
				}
				else if (input == KeyBoardASKII::ENTER)
				{
					break;
				}
			}
			if (jumpIndex.size() > 6)
			{
				string temp;
				arrowIndex = stoi(temp.assign(jumpIndex, jumpIndex.size() - 6, 6));
			}
			else
			{
				arrowIndex = stoi(jumpIndex);
			}
			if (arrowIndex > mailBox.size())
			{
				arrowIndex = mailBox.size() - 1;
			}
		}
		// ��J��V�� ����
		//***********************************************
		else
		{
			input = _getch();
			string author = mailBox[arrowIndex].second;
			string title = mailBox[arrowIndex].first;
			vector<string> contents = users[current_user]->getmailcontent();
			string content = contents[arrowIndex];
			switch (input)
			{
				//���W �b�Y���W
			case KeyBoardASKII::UP:
				(arrowIndex > 0) ? arrowIndex -= 1 : 0;
				break;
				//���U �b�Y���U
			case KeyBoardASKII::DOWN:
				(arrowIndex < mailBox.size() - 1) ? arrowIndex += 1 : arrowIndex;
				break;
				//���� ���^�ݪO
			case KeyBoardASKII::LEFT:
				state = BoardState::SELECT_BOARD;
				return;
				//���k ��ܫH��
			case KeyBoardASKII::RIGHT:
				//***********************************************
				system("CLS");
				//�v�L�@����
				viewer.SetColor(113);
				std::cout << "�H���";
				viewer.SetColor(23);
				std::cout << author;
				for (int i = author.size(); i < 40; i++) {
					std::cout << " ";
				}
				std::cout << endl;

				//�v�L���D��
				viewer.SetColor(113);
				std::cout << "���D";
				viewer.SetColor(23);
				std::cout << title;
				for (int i = title.size(); i < 40; i++) {
					std::cout << " ";
				}
				std::cout << endl;
				viewer.SetColor(14);
				std::cout << endl;
				viewer.SetColor(7);
				std::cout << content;
				std::cout << endl;
				//���k��^
				while (input = _getch())
				{
					input = _getch();
					if (input == KeyBoardASKII::LEFT)
					{
						break;
					}
				}
				break;
				//***********************************************
			default:
				break;
			}
		}
		system("CLS");
		viewer.showMailList(mailBox,arrowIndex);
	}


	/*string receiver, emailTitle;
	int flag = 0;
	std::cout << "�п�J�l����D: " << endl;
	cin >> emailTitle;
	users[current_user]->openMail(emailTitle);
	break;*/
}
//void BoardManager::leaveMsg()
//{
//	string updateMsgLine;
//	int option;
//	cout << "1.���� 2.�N�� 3.�d�� :";
//	while (cin >> option)
//	{
//		if (option == 1 || option == 2 || option == 3)
//		{
//			break;
//		}
//		cout << "1.���� 2.�N�� 3.�d�� :";
//	}
//	updateMsgLine = ('0'+ option);
//
//	updateMsgLine +=" "+users[current_user]->getUsername() + ' ';
//	string comment;
//	cout << "��J�d��:";
//	getline(cin, comment);
//	getline(cin, comment);
//	updateMsgLine += comment;
//
//	string Path = nowBoard->articalsPath[editArticalIndex];
//	fstream file;
//	file.open(Path, ios::app);
//	file<<updateMsgLine<<endl;
//	file.close();
//}
void BoardManager::leaveMsg()
{
	stringstream ss;

	string current_name = users[current_user]->getUsername(); //��e�ϥΪ̦W��
	string Path = nowBoard->articalsPath[editArticalIndex]; //���ˬd���L���Ưd��
	ifstream in(Path);
	string line;
	while (getline(in, line, '\n')) {
		if (line == "message") {
			break;
		}
	}
	int tmp;
	string used_name;
	while (getline(in, line, '\n')) {
		ss << line;
		ss >> tmp;
		ss >> used_name;
		ss.clear();
		ss.str("");
		if (used_name == current_name) {
			cout << "�Фŭ��Ʊ���!!\n"
				<< "��J���N����H�~��";
			_getch();
			return;
		}
	}

	string updateMsgLine;
	int option;
	cout << "1.���� 2.�N�� 3.�d�� :";
	while (cin >> option)
	{
		if (option == 1 || option == 2 || option == 3)
		{
			break;
		}
	}
	updateMsgLine = ('0' + option);

	updateMsgLine += " " + users[current_user]->getUsername() + ' ';
	string comment;
	cout << "��J�d��:";
	getline(cin, comment);
	getline(cin, comment);
	updateMsgLine += comment;

	fstream file;
	file.open(Path, ios::app);
	file << updateMsgLine << endl;
	file.close();


}
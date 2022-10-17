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

class BoardManager //版務管理操作
{
public:
	BoardManager();
	BoardManager(string);	//readfile
	
	// 執行 state
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
//	//檔案控制代碼  
//	long   hFile = 0;
//	//檔案資訊  
//	struct _finddata_t fileinfo;
//	string p;
//	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
//	{
//		do
//		{
//			//如果是目錄,迭代之  
//				//如果不是,加入列表  
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
//		//資料處理 -1.文章路徑 
//		//************************************************
//		if (buf == "BoardInfo")
//		{
//			string boardName;
//			getline(ss, boardName, '\\');
//
//			string extension = "";//副檔名
//			if (boardName.size() > 4)
//			{
//				extension.assign(boardName, boardName.size() - 4, 4);
//			}
//
//			Board* target = &boards;
//			//增添board 並找到文章 目標board
//			while (extension != ".txt")
//			{
//				bool notFound = true;
//				//找是否已存在此board
//				for (int j = 0; j < target->subBoard.size(); j++)
//				{
//					//有找到
//					if (boardName == target->subBoard[j].getboardName())
//					{
//						target = &target->subBoard[j];
//						notFound = false;
//						break;
//					}
//				}
//				//沒找到
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
//			//文章檔案
//			target->readArticalFile(files[i]);
//		}
//		//=====================================================
//
//		//資料處理 -1.使用者資料路徑
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
		//資料處理 -1.文章路徑 
		//************************************************
		if (buf == "BoardInfo")
		{
			string boardName;
			getline(ss, boardName, '\\');

			string extension = "";//副檔名
			if (boardName.size() > 4)
			{
				extension.assign(boardName, boardName.size() - 4, 4);
			}

			Board* target = &boards;
			//增添board 並找到文章 目標board
			while (extension != ".txt")
			{
				bool notFound = true;
				//找是否已存在此board
				for (int j = 0; j < target->subBoard.size(); j++)
				{
					//有找到
					if (boardName == target->subBoard[j].getboardName())
					{
						target = &target->subBoard[j];
						notFound = false;
						break;
					}
				}
				//沒找到 增加看板至數據庫
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
			//文章檔案
			target->readArticalFile(files[i]);
		}
		//=====================================================

		//資料處理 -1.使用者資料路徑
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
	cout << "請輸入代號，或以 guest 參觀，或以 new 註冊:";
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
		bool flag = 0; //看是否註冊過
		User* newMember = new Member;
		string name;
		cin >> name;
		for (int i = 0; i < users.size(); i++)
		{
			if (name == users[i]->getUsername())
			{
				cout << "This username has been used, Please try another one" << endl;
				flag = 1; //註冊過表示為1
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
		bool flag = 0; //檢查是否有帳號
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
					//進入看板
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

//選擇看板 [N]新增看板 [D]刪除看板 (僅限管理員)
void BoardManager::selectBoard()
{
	char input;
	unsigned int arrowIndex = 0;
	system("CLS");
	viewer.showBoard(nowBoard,0);
	while (input = _getch())
	{
		//輸入 [N]新增看板 (僅限管理員)
		///*******************************************
		if (input == 'N')
		{
			if (this->authority == UserAuthority::ADMIN)
			{
				cout << "是否要在【" << nowBoard->getboardName() << "】版新增看板 (input:y):";
				string answer;
				cin >> answer;
				if (answer == "y")
				{
					//輸入看板名
					string newBoardName;
					cout << "輸入要新增的看板名稱: ";
					cin >> newBoardName;

					//建檔新資料夾
					string FolderPath = nowBoard->getpath() +"/"+ newBoardName;
					const char* a = FolderPath.c_str();
					if (_mkdir(a)==0)
					{
						//記憶體更新看板
						Board addBoard(FolderPath, newBoardName, nowBoard);
						nowBoard->subBoard.push_back(addBoard);

						//加入至頂文
						cout << "現正加入至頂文\n";
						nowBoard = &(nowBoard->subBoard.back());
						state = BoardState::POST;
						return;
					}
					else
					{
						cout << "已存在此看板\n";
						continue;
					}
				}
			}
			else
			{
				cout << "權限不足 非管理員不得新增看板";
				continue;
			}
		}
		//輸入 [D]刪除看板 (僅限管理員)
		///*******************************************
		else if (input == 'D')
		{
			if (this->authority == UserAuthority::ADMIN)
			{
				cout << "是否要刪除" << arrowIndex+1 
					<< ".【看板:" << nowBoard->subBoard[arrowIndex].getboardName() << "】(input:y):";
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
				cout << "權限不足 非管理員不得刪除看板";
				continue;
			}
		}
		//輸入 [M]寄信
		//**********************************************
		else if (input == 'M')
		{
			if (this->authority != UserAuthority::GUEST)
			{
				cout << "是否要寄信件(input:y):";
				string answer;
				cin >> answer;
				if (answer == "y")
				{
					string receiver;
					int flag = 0;
					cout << "請輸入收件人: " << endl;
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
				cout << "權限不足，訪客不得寄信\n";
				continue;
			}
		}
		//輸入 [O]閱讀信件
		//**********************************************
		else if (input == 'O')
		{
			if (this->authority != UserAuthority::GUEST)
			{
				cout << "是否要閱讀信件(input:y):";
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
				cout << "權限不足，訪客不得收信\n";
				continue;
			}
		}
		//==========================================================
		// 輸入數字跳自 該列表看板 索引位置  key num 0~9  
		//****************************************************************************
		else if ((input > 48 && input < 58)/* || (input > 95 && input < 106)*/)
		{
			string jumpIndex;
			cout << "跳至第幾項:";

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
		// 輸入方向鍵 來瀏覽ptt
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
				// 至最上層看板 詢問是否登出
				//********************************************************
				else 
				{
					cout << "是否要登出PTT了(input:y):";
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

		// 至底層看版 需顯示文章標題 跳出此state fuction
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

//選擇文章 [->]顯示文章 [X]文章內推文噓文  [P]發表文章 [E]編輯文章 [d]刪除文章
void BoardManager::selectArtical() 
{
	char input;
	unsigned int arrowIndex = 0;
	system("CLS");
	viewer.showTitle(nowBoard,0);
	while (input = _getch())
	{
		//輸入 P 發表文章 於當前看板 
		///*******************************************
		if (input == 'P')
		{
			if (this->authority == UserAuthority::GUEST) 
			{
				cout << "權限不足 訪客不得發表文章";
				continue;
			}
			cout << "是否要在【" << nowBoard->getboardName() << "】版發表文章 (input:y):";
			string answer;
			cin >> answer;
			if (answer == "y")
			{
				state = BoardState::POST;
				return;
			}
		}
		//輸入 E 修改文章 於當前看板 
		///*******************************************
		else if (input == 'E')
		{
			if (nowBoard->articalsUserID[arrowIndex] != users[current_user]->getUsername())
			{
				cout << "非發表文章者 不得修改文章";
				continue;
			}
			cout << "是否要編輯" << arrowIndex << ".【標題:" << nowBoard->articalsTitle[arrowIndex] << "】(input:y):";
			string answer;
			cin >> answer;
			if (answer == "y")
			{
				state = BoardState::EDIT;
				editArticalIndex = arrowIndex;
				return;
			}
		}
		//輸入 d 刪除當前文章  
		///*******************************************
		else if (input == 'D')
		{
			if (this->authority == UserAuthority::GUEST)
			{
				cout << "權限不足 訪客不得刪除文章";
				continue;
			}
			else if (this->authority == UserAuthority::MEMBER &&
				nowBoard->articalsUserID[arrowIndex] != users[current_user]->getUsername())
			{
				cout << "權限不足 非發表文章者 不得刪除文章";
				continue;
			}
			else if ( (nowBoard->articalsUserID[arrowIndex] == users[current_user]->getUsername()) 
				|| this->authority == UserAuthority::ADMIN)
			{
				cout << "是否要刪除"<< arrowIndex<<".【標題:" << nowBoard->articalsTitle[arrowIndex] << "】(input:y):";
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
		// 輸入數字跳自 該列表看板 文章索引位置  key num 0~9  
		//****************************************************************************
		else if ((input > 48 && input < 58)/* || (input > 95 && input < 106)*/)
		{
			string jumpIndex;
			cout << "跳至第幾項:";

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
			//按上 箭頭往上
			case KeyBoardASKII::UP:
				(arrowIndex > 0) ? arrowIndex -= 1 : 0;
				break;
			//按下 箭頭往下
			case KeyBoardASKII::DOWN:
				(arrowIndex < nowBoard->articalsTitle.size() - 1) ? arrowIndex += 1 : arrowIndex;
				break;
			//按左 跳出看板
			case KeyBoardASKII::LEFT:
				state = BoardState::SELECT_BOARD;
				nowBoard = nowBoard->parent;
				return;
			//按右 進入文章內文
			case KeyBoardASKII::RIGHT:
				//顯示文章
				/********************************************************************/
				system("CLS");
				viewer.showArtical(nowBoard->articalsPath[arrowIndex]);
				while (input = _getch())
				{
					//推噓文
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
							cout<<"訪客不得推文";
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
		//寫檔 存入資料庫
		
		//建立相對路徑
		string _articalPath;
		_articalPath = nowBoard->getpath(); //得到現在的看板名
		_articalPath += "/" + to_string(nowBoard->articalsPath.size());
		_articalPath += ".txt";
		while ((find(nowBoard->articalsPath.begin(), nowBoard->articalsPath.end(), _articalPath) != nowBoard->articalsPath.end()))
		{
			//cout << "nono~重複囉" << endl;
			_articalPath = nowBoard->getpath() +"/" +to_string(nowBoard->articalsPath.size() + 1) + ".txt";
		}

		ofstream output(_articalPath);

		if (!output.fail())
		{
			//開始寫檔!
			output << "user: " << users[current_user]->getUsername() << endl;
			output << "title " << _title << endl;
			output << "-STARTARTICAL-" << endl;
			output << intent << endl;
			output << "-ENDARTICAL-" << endl;
			output << "message" << endl;
		}
		else
		{
			cout << "建立文章失敗 檢查寫檔路徑";
		}


		//看板更新數據
		nowBoard->updateForPost(_title,_articalPath,users[current_user]->getUsername());
		//使用者更新數據
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
		//修正文章 資料庫檔案
		if (file.good())
		{
			//開始寫檔!
			file << "user: " << users[current_user]->getUsername() << endl;
			file << "title " << _title << endl;
			file << "-STARTARTICAL-" << endl;
			file << intent << endl;
			file << "-ENDARTICAL-" << endl;
			file << "message" << endl;
		}
		else
		{
			cout << "建立文章失敗 檢查寫檔路徑";
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
		_title = "【此文已被作者刪除】";
	}
	else if (users[current_user]->getAuthority() == UserAuthority::ADMIN)
	{
		string cause;
		cout << "輸入刪除原因或違反事項:";
		getline(cin, cause);
		getline(cin, cause);
		_title = "【此文已被管理員刪除，刪除原因:<<"+cause+"】";
	}
	fstream file(nowBoard->articalsPath[editArticalIndex], ios::out | ios::trunc);
	//修正文章 資料庫檔案
	if (file.good())
	{
		//開始寫檔!
		file << "user: " << users[current_user]->getUsername() << endl;
		file << "title " << _title << endl;
		file << "-STARTARTICAL-" << endl;
		file << intent << endl;
		file << "-ENDARTICAL-" << endl;
		file << "message" << endl;
		//更新路徑
		nowBoard->articalsTitle[editArticalIndex] = _title;
	}
	else
	{
		cout << "刪除文章失敗 檢查寫檔路徑\n";
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
		// 輸入數字跳自 該列表郵件 索引位置  key num 0~9  
		//****************************************************************************
		if ((input > 48 && input < 58)/* || (input > 95 && input < 106)*/)
		{
			string jumpIndex;
			cout << "跳至第幾項:";

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
		// 輸入方向鍵 控制
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
				//按上 箭頭往上
			case KeyBoardASKII::UP:
				(arrowIndex > 0) ? arrowIndex -= 1 : 0;
				break;
				//按下 箭頭往下
			case KeyBoardASKII::DOWN:
				(arrowIndex < mailBox.size() - 1) ? arrowIndex += 1 : arrowIndex;
				break;
				//按左 跳回看板
			case KeyBoardASKII::LEFT:
				state = BoardState::SELECT_BOARD;
				return;
				//按右 顯示信件
			case KeyBoardASKII::RIGHT:
				//***********************************************
				system("CLS");
				//影印作者欄
				viewer.SetColor(113);
				std::cout << "寄件者";
				viewer.SetColor(23);
				std::cout << author;
				for (int i = author.size(); i < 40; i++) {
					std::cout << " ";
				}
				std::cout << endl;

				//影印標題欄
				viewer.SetColor(113);
				std::cout << "標題";
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
				//按右返回
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
	std::cout << "請輸入郵件標題: " << endl;
	cin >> emailTitle;
	users[current_user]->openMail(emailTitle);
	break;*/
}
//void BoardManager::leaveMsg()
//{
//	string updateMsgLine;
//	int option;
//	cout << "1.推文 2.噓文 3.留言 :";
//	while (cin >> option)
//	{
//		if (option == 1 || option == 2 || option == 3)
//		{
//			break;
//		}
//		cout << "1.推文 2.噓文 3.留言 :";
//	}
//	updateMsgLine = ('0'+ option);
//
//	updateMsgLine +=" "+users[current_user]->getUsername() + ' ';
//	string comment;
//	cout << "輸入留言:";
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

	string current_name = users[current_user]->getUsername(); //當前使用者名稱
	string Path = nowBoard->articalsPath[editArticalIndex]; //先檢查有無重複留言
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
			cout << "請勿重複推文!!\n"
				<< "輸入任意按鍵以繼續";
			_getch();
			return;
		}
	}

	string updateMsgLine;
	int option;
	cout << "1.推文 2.噓文 3.留言 :";
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
	cout << "輸入留言:";
	getline(cin, comment);
	getline(cin, comment);
	updateMsgLine += comment;

	fstream file;
	file.open(Path, ios::app);
	file << updateMsgLine << endl;
	file.close();


}
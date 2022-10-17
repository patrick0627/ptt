//#include"BoardManager.h"
//using namespace std;
//
//void BoardManager::setState(int _state) { state = _state; }
//
//int BoardManager::getState() { return state; };
//
//
//void BoardManager::logging()
//{
//	cout << "請輸入代號，或以 guest 參觀，或以 new 註冊:";
//	string opCode;
//	cin >> opCode;
//
//	if (opCode == "guest")
//	{
//
//	}
//	else if (opCode == "new")
//	{
//
//	}
//	else
//	{
//		string _userID = opCode;
//
//
//
//	}
//}
//void  BoardManager::selectBoard() {}
//void  BoardManager::selectArtical() {}
//void  BoardManager::editArtical() {}
//
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
//				 //如果不是,加入列表  
//			if ((fileinfo.attrib & _A_SUBDIR))
//			{
//				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
//					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
//			}
//			else
//			{
//				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
//			}
//		} while (_findnext(hFile, &fileinfo) == 0);
//		_findclose(hFile);
//	}
//};
//
//BoardManager::BoardManager()
//{
//	users.clear();
//	authority = UserPriority::GUEST;
//	state = BoardState::MENU;
//	current_user = -1;
//}
//
//BoardManager::BoardManager(string DBpath)
//{
//	//initial
//	//**************************
//	users.clear();
//	authority = UserPriority::ADIMIN;
//	state = BoardState::MENU;
//	current_user = 0;
//	//==============================
//
//	//struct database
//	vector<string> files;
//	getFiles(DBpath, files);
//	for (int i = 0; i < files.size(); i++)
//	{
//		string allPath;
//		int startSize = 33;		// the size of (D:\user\Desktop\ptt\ptt\DataBase\)
//		allPath.assign(files[i], startSize, files[i].size() - startSize);
//		stringstream ss(allPath);
//
//		string path;
//		getline(ss, path, '\\');
//		//文章路徑 
//		//************************************************
//		if (path == "BoardInfo")
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
//					target->subBoard.push_back(Board(tmpPath, boardName));
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
//			target->insertArtical(files[i]);
//		}
//		//=====================================================
//
//		//使用者資料路徑
//		//*******************************************************
//		else if (path == "UserInfo")
//		{
//			string name;
//			getline(ss, name, '\\');
//			User* tmp = new User(name);
//			tmp->downlaod(files[i]);
//			users.push_back(tmp);
//		}
//		//========================================================
//
//	}
//}
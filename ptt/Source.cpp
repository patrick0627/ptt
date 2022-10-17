#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<conio.h>
#include <experimental/filesystem>
#include"BoardManager.h"
using namespace std;

/*
 登入(創帳號也在這) -> 選擇看板 -> 閱讀文章(基本b 編輯)
	     		    -> 帳號互動
guest	級別1

member	級別2		    編輯權限

adimin	級別3	可增減      編輯權限
*/
//namespace fs = std::experimental::filesystem;

//BoardManager boardManager("D:\\user\\Desktop\\ptt\\ptt\\DataBase");
//BoardManager boardManager("C:/Users/Weiting/Desktop/ptt/ptt/DataBase");
BoardManager boardManager("D:/user/Desktop/oopLab_project/project3-PTT/ptt/ptt/DataBase");
//BoardManager boardManager;

int main()
{
	//fs::path p = fs::current_path();

	//std::cout << "The current path " << p << " decomposes into:\n"
	//	<< "root-path " << p.root_path() << '\n'
	//	<< "relative path " << p.relative_path() << '\n';
	fstream file;
	file.open("./DataBase/BoardInfo/Favorite/Gossiping/1.txt");
	string str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	char input;
	cout << "請按任意鍵繼續\n";
	input = _getch();


	while (1)
	{
		switch (boardManager.getState())
		{
		case BoardState::MENU:
			//Enter the account
			boardManager.logging();
			break;
		case BoardState::SELECT_BOARD:
			// Display & Select next operation
			boardManager.selectBoard();
			break;
		case BoardState::BOARD:
			// Display each post & select post
			boardManager.selectArtical();
			break;
		case BoardState::POST:
			//Post text
			boardManager.postArtical();
			break;
		case BoardState::EDIT:
			//Post text
			boardManager.editArtical();
			break;
		case BoardState::MAIL:
			//Post text
			boardManager.readMail();
			break;
		case BoardState::Leave:
			cout << "Bye Bye";
			break;
		default:
			break;
		}
	}


	
	return 0;
}
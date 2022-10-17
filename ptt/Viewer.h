#pragma once
#include<iostream>
#include<Windows.h>
#include"User.h"

using namespace std;

class Viewer {
public:
	Viewer() {}
	void showManu() {}

	//顯示 可挑選的版
	void showBoard(Board* board, int index);

	//顯示板上文章
	void showTitle(Board* board, int index);

	//顯示版上文章
	void showArtical(string file_path);

	//設定輸出顏色
	void SetColor(int color = 7);

	void showMailList(vector <pair<string, string>> mailbox, int index);


	//發表文章
	bool postArtical(string& title, string& intent);
private:
	vector<string> view;
};

void Viewer::SetColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Viewer::showBoard(Board* board, int index) {

	SetColor(31);
	cout << "【看板列表】    ";
	SetColor(30);
	cout << "批踢踢實業坊    \n";
	SetColor(14);
	cout << "[←]離開看板 [→]進入看板 [N]新增看板 [D]刪除看板 \n" 
		<< "[M]寄郵件 [O]檢視郵件 輸入數字跳自 編號索引位置\n";

	SetColor(112);
	cout << "   編號     看板            人氣  \n";

	for (int i = 0; i < board->subBoard.size(); i++) {

		SetColor(7);
		if (i == index) {
			cout << (">  ");
		}
		else {
			cout << "   ";
		}

		cout.width(3);
		cout.setf(ios::right);
		cout << i + 1 << " ";
		SetColor(12);
		cout << ("ˇ   ");

		SetColor(11);
		cout << board->subBoard[i].getboardName();
		for (int j = board->subBoard[i].getboardName().size(); j < 17; j++) {
			cout << " ";
		}
		if (board->subBoard[i].getboardName() != "favorite") {
			if (board->subBoard[i].count < 3) {
				SetColor();
				cout << board->subBoard[i].count;
			}
			else if (board->subBoard[i].count < 5) {
				SetColor(14);
				cout << "HOT";
			}
			else {
				SetColor(12);
				cout << "爆!";
			}
		}

		cout << endl;
	}

	SetColor(7);
}

void Viewer::showTitle(Board* board, int index) {
	SetColor(14);
	cout << "               " << board->getboardName() << "               \n";
	cout << "[←]離開 [→]閱讀 [P]發表文章 [E]編輯文章 \n"
		<< " [D] 刪除文章    輸入數字跳自 編號索引位置\n";
	SetColor(112);
	cout << "  編號   作者            文章標題          \n";

	SetColor();

	for (int i = 0; i < board->articalsTitle.size(); i++) {
		if (i == index) {
			cout << (">  ");
		}
		else {
			cout << "   ";
		}
		cout << i + 1 << "     " << board->articalsUserID[i];
		for (int count = board->articalsUserID[i].size(); count < 15; count++) {
			cout << " ";
		}

		cout << board->articalsTitle[i] << endl;
	}

	SetColor();
}

void  Viewer::showArtical(string file_path) {
	ifstream file_ptr;
	file_ptr.open(file_path);

	string tmp;

	file_ptr >> tmp;

	//影印作者欄
	string author;
	getline(file_ptr, author, '\n');
	SetColor(113);
	cout << "作者";
	SetColor(23);
	cout << author;
	for (int i = author.size(); i < 40; i++) {
		cout << " ";
	}
	cout << endl;

	file_ptr >> tmp;

	//影印標題欄
	string title;
	getline(file_ptr, title, '\n');
	SetColor(113);
	cout << "標題";
	SetColor(23);
	cout << title;
	for (int i = title.size(); i < 40; i++) {
		cout << " ";
	}
	cout << endl;
	SetColor(14);
	cout << "[x] 推文\n";

	cout << endl;
	SetColor(7);
	cout << endl;

	file_ptr >> tmp;

	//顯示內文
	string content;
	int count;
	while (getline(file_ptr, content, '\n') && content != "-ENDARTICAL-") {
		for (int i = 0; i < content.size(); i++) {
			cout << content[i];
			if ((i + 1) % 40 == 0) {
				cout << endl;
			}
		}
		cout << endl;
	}
	cout << endl << endl << endl;

	// message
	file_ptr >> tmp;
	int type;
	while (file_ptr >> type)
	{
		switch (type) {
		case 1:
			SetColor(15);
			cout << "推 ";
			break;
		case 2:
			SetColor(12);
			cout << "噓 ";
			break;
		case 3:
			SetColor(12);
			cout << "→ ";
			break;
		default:
			break;
		}

		file_ptr >> author;
		SetColor(14);
		cout << author;
		for (int i = author.size(); i < 12; i++) {
			cout << " ";
		}
		cout << ": ";
		getline(file_ptr, content, '\n');
		SetColor(6);
		cout << content << endl;


	}

	file_ptr.close();
	SetColor();
}

bool  Viewer::postArtical(string& title, string& content) {

	SetColor(112);
	cout << "      輸入#end-結束編輯      \n";
	SetColor(7);

	string title_backup;
	cout << "請輸入標題: ";
	getline(cin, title_backup);
	getline(cin, title_backup);

	string content_backup;
	string tmp;
	cout << "輸入內文:\n";
	while (getline(cin, tmp) && tmp != "#end") {
		content_backup += tmp;
		content_backup += '\n';
	}

	char option;
	cout << "是否發布文章(y/n)\n";
	while (cin >> option) {
		if (option == 'Y' || option == 'y') {
			title = title_backup;
			content = content_backup;
			return true;
		}
		else if (option == 'N' || option == 'n') {
			return false;
		}
	}

	cout << content_backup;

	SetColor();
}

void  Viewer::showMailList(vector<pair<string, string>> mailbox, int index)
{
	SetColor(31);
	cout << "【郵件選單】    ";
	SetColor(30);
	cout << "批踢踢實業坊    \n";
	SetColor(14);
	cout << "輸入數字跳自 編號索引位置\n";

	SetColor(112);
	cout << "  編號   作者       標題        \n";

	for (int i = 0; i < mailbox.size(); i++) {

		SetColor(7);
		if (i == index) {
			cout << ("> ");
		}
		else {
			cout << "  ";
		}

		cout.width(3);
		cout.setf(ios::right);
		cout << i + 1 << "    ";
		cout << mailbox[i].second;
		for (int j = mailbox[i].second.size(); j < 11; j++) {
			cout << " ";
		}
		cout << mailbox[i].first << endl;

	}

	SetColor(7);
}
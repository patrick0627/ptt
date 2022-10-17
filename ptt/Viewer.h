#pragma once
#include<iostream>
#include<Windows.h>
#include"User.h"

using namespace std;

class Viewer {
public:
	Viewer() {}
	void showManu() {}

	//��� �i�D�諸��
	void showBoard(Board* board, int index);

	//��ܪO�W�峹
	void showTitle(Board* board, int index);

	//��ܪ��W�峹
	void showArtical(string file_path);

	//�]�w��X�C��
	void SetColor(int color = 7);

	void showMailList(vector <pair<string, string>> mailbox, int index);


	//�o��峹
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
	cout << "�i�ݪO�C��j    ";
	SetColor(30);
	cout << "�����~�{    \n";
	SetColor(14);
	cout << "[��]���}�ݪO [��]�i�J�ݪO [N]�s�W�ݪO [D]�R���ݪO \n" 
		<< "[M]�H�l�� [O]�˵��l�� ��J�Ʀr���� �s�����ަ�m\n";

	SetColor(112);
	cout << "   �s��     �ݪO            �H��  \n";

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
		cout << ("��   ");

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
				cout << "�z!";
			}
		}

		cout << endl;
	}

	SetColor(7);
}

void Viewer::showTitle(Board* board, int index) {
	SetColor(14);
	cout << "               " << board->getboardName() << "               \n";
	cout << "[��]���} [��]�\Ū [P]�o��峹 [E]�s��峹 \n"
		<< " [D] �R���峹    ��J�Ʀr���� �s�����ަ�m\n";
	SetColor(112);
	cout << "  �s��   �@��            �峹���D          \n";

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

	//�v�L�@����
	string author;
	getline(file_ptr, author, '\n');
	SetColor(113);
	cout << "�@��";
	SetColor(23);
	cout << author;
	for (int i = author.size(); i < 40; i++) {
		cout << " ";
	}
	cout << endl;

	file_ptr >> tmp;

	//�v�L���D��
	string title;
	getline(file_ptr, title, '\n');
	SetColor(113);
	cout << "���D";
	SetColor(23);
	cout << title;
	for (int i = title.size(); i < 40; i++) {
		cout << " ";
	}
	cout << endl;
	SetColor(14);
	cout << "[x] ����\n";

	cout << endl;
	SetColor(7);
	cout << endl;

	file_ptr >> tmp;

	//��ܤ���
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
			cout << "�� ";
			break;
		case 2:
			SetColor(12);
			cout << "�N ";
			break;
		case 3:
			SetColor(12);
			cout << "�� ";
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
	cout << "      ��J#end-�����s��      \n";
	SetColor(7);

	string title_backup;
	cout << "�п�J���D: ";
	getline(cin, title_backup);
	getline(cin, title_backup);

	string content_backup;
	string tmp;
	cout << "��J����:\n";
	while (getline(cin, tmp) && tmp != "#end") {
		content_backup += tmp;
		content_backup += '\n';
	}

	char option;
	cout << "�O�_�o���峹(y/n)\n";
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
	cout << "�i�l����j    ";
	SetColor(30);
	cout << "�����~�{    \n";
	SetColor(14);
	cout << "��J�Ʀr���� �s�����ަ�m\n";

	SetColor(112);
	cout << "  �s��   �@��       ���D        \n";

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
#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<direct.h>
#include<fstream>
using namespace std;

enum UserAuthority
{
	GUEST = 1,
	MEMBER =2,
	ADMIN =3
};

class User //使用者 (base)
{
protected:
	int authority = UserAuthority::GUEST;
	string userName = "";
	string password = "";
	string path = "";
	string MailboxPath_Member = "./DataBase/UserInfo/Member/"; //成員信箱的路徑
	string MailboxPath_Administrator = "./DataBase/UserInfo/Administrator/"; // 管理員
	vector <string> postsPath;	// 紀錄建立過的post
	vector <string> postsTitle; // 紀錄建立過的文章標題
	vector <pair<string, string>> mailbox; //信箱 //前面放的是標題 後面放寄件者
	vector <string> mailcontent;// 信件內容

public:
	User() {}
	User(string username) { userName = username; }
	User(string username, string password)
	{
		this->userName = username;
		this->password = password;
	}
	
	virtual void Established_Data()=0;	//建檔
	void download(string dataPath);
	void updateForPost(string _articalPath, string _title)
	{
		this->postsPath.push_back(_articalPath);
		this->postsTitle.push_back(_title);

		////////在尾部附加
		string Path = this->getPath();
		fstream file;
		file.open(Path, ios::app);
		file << _articalPath << " " << _title << endl;
		file.close();
	}
	void sendmessage(User& receiver)
	{
		cout << "請輸入標題:";
		string Title;
		cin >> Title;

		for (int i = 0; i < receiver.mailbox.size(); i++)
		{
			if (Title == receiver.mailbox[i].first)
			{
				Title += ".";
			}
		}
		pair<string, string> message;
		message.first = Title; //標題
		message.second = this->getUsername(); //寄件者名字
		receiver.mailbox.push_back(message);


		cout << "請輸入內文: " << endl;
		string content;//內文
		cin >> content;
		receiver.mailcontent.push_back(content);

		/*string txtPath;
		if (receiver.authority == UserAuthority::MEMBER)
		{
			txtPath = receiver.getMailboxPath_Member() + "/" + Title + ".txt";
		}
		else if (receiver.authority == UserAuthority::ADMIN)
		{
			txtPath = receiver.getMailboxPath_Administrator() + "/" + Title + ".txt";
		}

		ofstream mail(txtPath);
		mail << "user: " << this->getUsername() << endl;
		mail << "title " << Title << endl;
		mail << "-STARTARTICAL-" << endl;
		mail << content << endl;
		mail << "-ENDARTICAL" << endl;

		mail.close();*/
	}
	void openMail(string name)
	{
		int flag = 0;
		for (int i = 0; i < this->mailbox.size(); i++)
		{
			if (name == mailbox[i].first)
			{
				flag = 1;
				cout << "信件內容是: " << endl;
				cout << mailcontent[i] << endl;
			}
		}
		if (flag == 0)
		{
			cout << "Can't find the mail" << endl;

		}
		_getch();
		return;
	}

	//set data
	void setPath(string a)
	{
		this->path = a;
	}
	void setUsername(string a)
	{
		this->userName = a;
	}
	void setPassword(string a)
	{
		this->password = a;
	}
	void setAuthority(int a)
	{
		this->authority = a;
	}

	//get data
	string getPath()
	{
		return path;
	}
	string getUsername()
	{
		return this->userName;
	}
	string getPassword()
	{
		return this->password;
	}
	int getAuthority()
	{
		return this->authority;
	}
	string getMailboxPath_Member()
	{
		string temp = this->MailboxPath_Member;
		temp += this->userName + "/Mailbox";
		return temp;
	}
	string getMailboxPath_Administrator()
	{
		string temp = this->MailboxPath_Administrator;
		temp += this->userName + "/Mailbox";
		return temp;
	}
	vector<pair<string, string>> getMail()
	{
		return this->mailbox;
	}
	vector<string> getmailcontent()
	{
		return this->mailcontent;
	}
};

void User::download(string dataPath)
{
	fstream file(dataPath);
	if (file.good())
	{
		//轉換絕對路徑 至 相對路徑
		//**********************************
		string relativePath;
		stringstream ss(dataPath);
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
		path = relativePath;
		while (file>>buf)
		{
			if (buf == "password")
			{
				file >> password;
			}
			else if(buf=="level")
			{
				file >> authority;
			}
			else if (buf == "post")
			{
				while (file >> buf)
				{
					// 加入 文章路徑
					postsPath.push_back(buf);
					// 加入文章標題
					string _title;
					getline(file, _title);
					if (_title.front() == '\t' || _title.front() == ' ')
					{
						_title.erase(_title.begin());
					}
					postsTitle.push_back(_title);
				}
			}
		}
	}
}

class Administrator :public User
{
private:
public:
	Administrator() { authority = UserAuthority::ADMIN; };
	Administrator(string username) :User(username) { authority = UserAuthority::ADMIN; }
	Administrator(string username, string password) 
		:User(username,password) { authority = UserAuthority::ADMIN; }
	//建檔
	void Established_Data() override
	{
		string FolderPath = "./DataBase/UserInfo/Administrator/" + userName;
		const char* a = FolderPath.c_str();
		_mkdir(a);
		string Path = "./DataBase/UserInfo/Administrator/" + userName + "/user.txt";
		ofstream file(Path);
		file << "password " << password << endl << "level " << authority << endl << "post";
	}
};

class Member :public User
{
private:
public:
	Member() { authority = UserAuthority::MEMBER; };
	Member(string username) :User(username) { authority = UserAuthority::MEMBER; }
	Member(string username, string password)
		:User(username, password) {
		authority = UserAuthority::MEMBER;
	}

	//建檔
	void Established_Data() override
	{
		string FolderPath = "./DataBase/UserInfo/Member/" + userName;
		const char* a = FolderPath.c_str();
		_mkdir(a);
		string Path = "./DataBase/UserInfo/Member/" + userName + "/user.txt";
		ofstream file(Path);
		file << "password " << password << endl << "level " << authority << endl << "post";
	}

};

class Guest :public User
{
private:
public:
	Guest() {};
	Guest(string username) :User(username) { authority = UserAuthority::GUEST; }
	Guest(string username, string password)
		:User(username, password) {
		authority = UserAuthority::GUEST;
	}
	//建檔
	void Established_Data() override
	{
	}
};
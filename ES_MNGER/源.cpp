/*

	fixing  借书页面无法退出
	fixing  借书后没有记录
	fixing  一本书可以重复借阅
	fixed   借书的时候只能借第一本书

*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <windows.h>

#define Query(COM) cout<<">>> "<<COM<<endl<<">>> "

using namespace std;
const string AdministritorPWD = "1234";
const int MAXTIMES = 100;
struct ES_Book;
struct ES_User;
struct ES_BookMessage;

ES_User * gLoggedUser;

struct ES_Book {
	string name, ID, author, publisher;
	int cost,num;
};
struct ES_User {
	string ID, pwd, name;
	vector<ES_BookMessage>history, borrowing;
};
struct ES_BookMessage {
	ES_Book * book;
	ES_User * user;
	int borrowTime, returnTime, fine;
};
vector<ES_Book>BookLibrary;
vector<ES_User>UserLibrary;
vector<ES_BookMessage>HistoryLibrary, BorrowingLibrary;

/*
*users: 1: 

*users: 1, 2, 3
*books: 1, 2, 3
*bmsgs: 1, 2, 3
*/

void login();
void registerUser();
void userMenu(ES_User * user);
void adminMenu();
void addBook();
void deleteBook();
void changeUser();
void viewBorrowing();
void viewBook();
void borrowingBook(ES_User * user);
void returnBook(ES_User * user);
int main() {
	int i;
	while (1) {
		
		if (gLoggedUser) {
			userMenu(gLoggedUser);
		} else {
			system("cls");
			printf("\t\t\t***********************************************\n");
			printf("\t\t\t************欢迎进入图书信息管理系统***********\n");
			printf("\t\t\t***                                         ***\n");
			printf("\t\t\t***----------------按1，登陆----------------***\n");
			printf("\t\t\t***                                         ***\n");
			printf("\t\t\t***----------------按2，注册----------------***\n");
			printf("\t\t\t***                                         ***\n");
			printf("\t\t\t***----------------按3，退出----------------***\n");
			printf("\t\t\t***                                         ***\n");
			printf("\t\t\t***********************************************\n");
			Query("请选择你的操作");
			cin >> i;
			if (i == 1)      login();
			else if (i == 2) registerUser();
			else if (i == 3) return 0;
			else             cout << "请规范您的输入！" << endl;
		}
	}
	return 0;
}
void login() {
	string ID, passward;
	Query("请输入您的ID");
	cin >> ID;
	Query("请输入您的密码");
	cin >> passward;
	bool login_flag = false;
	if (ID == "admin") {
		if (passward == AdministritorPWD) {
			login_flag = true;
			adminMenu();
		}
	}
	for (int i = 0; i < UserLibrary.size(); i++) {
		if (UserLibrary[i].ID == ID) {
			if (UserLibrary[i].pwd == passward) {
				gLoggedUser = &UserLibrary[i];
				//userMenu();
				login_flag = true;
			}
		}
	}

	if (login_flag == false) {
		cout << ">>> 账户或密码错误" << endl;
		system("pause");
	}
	
}
void registerUser() {
	string name, ID, passward, a;
	Query("请输入ID");
	cin >> ID;
	do {
		Query("请第一次输入密码");
		cin >> passward;
		Query("请第二次输入密码");
		cin >> a;
		if (a == passward)
			break;
		else
			cout << ">>> 请确认您的密码" << endl;
	} while (1);
	Query("请输入您的名字");
	cin >> name;

	ES_User c;
	c.name = name;

	c.ID = ID;
	c.pwd = passward;
	c.borrowing.clear();
	c.history.clear();
	UserLibrary.push_back(c);
	system("pause");
}
void userMenu(ES_User * user) {
	cout<< ">>> 欢迎" << user->name << endl;

	system("pause");
	while (1) {

		int i = -1;
		while (i == -1) {
			system("cls");
			printf("\t\t\t***********************************************\n");
			printf("\t\t\t***                                         ***\n");
			printf("\t\t\t***----------------按1，借书----------------***\n");
			printf("\t\t\t***                                         ***\n");
			printf("\t\t\t***----------------按2，还书----------------***\n");
			printf("\t\t\t***                                         ***\n");
			printf("\t\t\t***----------------按3，查看----------------***\n");
			printf("\t\t\t***                                         ***\n");
			printf("\t\t\t***----------------按0，返回----------------***\n");
			printf("\t\t\t***                                         ***\n");
			printf("\t\t\t***********************************************\n");
			Query("请选择你的操作");
			cin >> i;
			if (i == 1)
				borrowingBook(user);
			else if (i == 2)
				returnBook(user);
			else if (i == 3)
				viewBook();
			else if (i == 0) {
				gLoggedUser = NULL;
				return;
			} else {
				Query("请重新输入");
				i = -1;
				
			}
		}
	}
}
void adminMenu() {
	while (1) {
		cout << ">>> 欢迎admin"<<endl;
		system("pause");
		int i = -1;
		while (1) {
			system("cls");
			printf("\t\t\t***************************************************\n");
			printf("\t\t\t***                                             ***\n");
			printf("\t\t\t***----------------按1，添加信息----------------***\n");
			printf("\t\t\t***                                             ***\n");
			printf("\t\t\t***----------------按2，删除信息----------------***\n");
			printf("\t\t\t***                                             ***\n");
			printf("\t\t\t***----------------按3，修改用户----------------***\n");
			printf("\t\t\t***                                             ***\n");
			printf("\t\t\t***----------------按4，借阅历史----------------***\n");
			printf("\t\t\t***                                             ***\n");
			printf("\t\t\t***----------------按5，图书浏览----------------***\n");
			printf("\t\t\t***                                             ***\n");
			printf("\t\t\t***----------------按0，退出系统----------------***\n");
			printf("\t\t\t***                                             ***\n");
			printf("\t\t\t***************************************************\n");
			Query("请选择你的操作");
			cin >> i;
			if (i == 1)
				addBook();
			else if (i == 2)
				deleteBook();
			else if (i == 3)
				changeUser();
			else if (i == 4)
				viewBorrowing();
			else if (i == 5)
				viewBook();
			else if (i == 0)
				return;
			else {
				Query("请重新输入");
				i = -1;
			}
		}
	}
}
void addBook() {
	ES_Book a;
	Query("请输入书名");
	cin >> a.name;
	Query("请输入编号");
	cin >> a.ID;
	Query("请输入作者");
	cin >> a.author;
	Query("请输入出版社");
	cin >> a.publisher;
	Query("请输入书的个数");
	cin >> a.num;
	Query("请输入价钱");
	cin >> a.cost;
	BookLibrary.push_back(a);
	cout << ">>> 已输入成功" << endl;
	system("pause");
}

void deleteBook() {
	printf("||-------------------------------------\n");
	printf("|| 编号         书名            作者\n");
	printf("||-------------------------------------\n");
	for (int i = 0; i < BookLibrary.size(); i++)  
		printf("|| %3d  |%10s\t|%10s\n", i + 1, BookLibrary[i].name.c_str(), BookLibrary[i].author.c_str());
	int v = -1;
	while (v == -1) {
		Query("请输入您所要删除的图书");
		cin >> v;
		if (v >= 1 && v <= BookLibrary.size())
			break;
		else if (v == 0)
			return;
		else {
			Query("请重新输入");
			v = -1;
		}
	}
	vector<ES_Book>::iterator j;
	for (j = BookLibrary.begin(); j != BookLibrary.end(); j++) {
		if (&(*j) == &BookLibrary[v - 1]) {
			BookLibrary.erase(j);
			break;
		}
	}
	system("pause");
}

void changeUser() {

	for (int i = 0; i < UserLibrary.size(); i++) {
		cout << i + 1 << " " << UserLibrary[i].ID << " " << UserLibrary[i].name << endl;
	}
	int v = -1;
	while (v == -1) {
		cout << ">>> 输入0返回上级" << endl;
		Query("输入您想要改变的用户编号");
		cin >> v;
		if (v >= 1 && v <= UserLibrary.size())
			break;
		else if (v == 0)
			return;
		else {
			Query("请重新输入");
			v = -1;
		}
	}
	int u = -1;
	string a;
	while (u == -1) {
		printf("\t\t\t***********************************************\n");
		printf("\t\t\t***                                         ***\n");
		printf("\t\t\t***--------------按1，修改账户--------------***\n");
		printf("\t\t\t***                                         ***\n");
		printf("\t\t\t***--------------按2，修改密码--------------***\n");
		printf("\t\t\t***                                         ***\n");
		printf("\t\t\t***--------------按3，修改姓名--------------***\n");
		printf("\t\t\t***                                         ***\n");		
		printf("\t\t\t***--------------按4，删除记录--------------***\n");
		printf("\t\t\t***                                         ***\n");
		printf("\t\t\t***--------------按0，返    回--------------***\n");
		printf("\t\t\t***                                         ***\n");
		printf("\t\t\t***********************************************\n");
		Query("请选择你的操作");
		cin >> u;
		if (u == 1) {
			Query("请输入新账户名");
			cin >> UserLibrary[v - 1].ID;
		} else if (u == 2) {
			Query("请输入您所要新密码");
			cin >> UserLibrary[v - 1].pwd;
		} else if (u == 3) {
			Query("请输入新名字");
			cin >> UserLibrary[v - 1].name;
		} else if (u == 4) {
			UserLibrary[v - 1].history.clear();
		} else if (u == 0)
			return;
		else {
			Query("请重新输入");
			u = -1;
		}
	}
	cout << ">>> 修改完成" << endl;
	system("pause");
}
void viewBorrowing() {
	int i = -1;
	while (i == -1) {
		printf("\t\t\t***********************************************\n");
		printf("\t\t\t***                                         ***\n");
		printf("\t\t\t***----------------按1，已还----------------***\n");
		printf("\t\t\t***                                         ***\n");
		printf("\t\t\t***----------------按2，未还----------------***\n");
		printf("\t\t\t***                                         ***\n");
		printf("\t\t\t***----------------按0，返回----------------***\n");
		printf("\t\t\t***                                         ***\n");
		printf("\t\t\t***********************************************\n");
		Query("请选择你的操作");
		cin >> i;
		if (i == 1 || i == 2)
			break;
		else if (i == 0)
			return;
		else {
			Query("请重新输入");
			i == -1;
		}
	}
	
	if (i == 1) {
		printf("||---------------------------------------------------------\n");
		printf("|| 编号         书名            用户ID        归还时间     \n");
		printf("||---------------------------------------------------------\n");
		
		for (int i = 0; i < HistoryLibrary.size(); i++)
			printf("|| %3d  |%10s\t|%18s\t|%d\n", i + 1, (HistoryLibrary[i].book->name).c_str(), (HistoryLibrary[i].user->ID).c_str(), HistoryLibrary[i].borrowTime);
	} else {
		printf("||---------------------------------------------------------\n");
		printf("|| 编号         书名            用户ID        借阅时间     \n");
		printf("||---------------------------------------------------------\n");

		for (int i = 0; i < HistoryLibrary.size(); i++)
			printf("|| %3d  |%10s\t|%18s\t|%d\n", i + 1, (BorrowingLibrary[i].book->name).c_str(), (BorrowingLibrary[i].user->ID).c_str(), BorrowingLibrary[i].borrowTime);
	}
	system("pause");
}
void viewBook() {

	printf("||--------------------------------\n");
	printf("|| 编号       书名           作者    \n");
	printf("||--------------------------------\n");

	for (int i = 0; i < BookLibrary.size(); i++)
		printf("|| %d\t%10s     %10s\n", i + 1, BookLibrary[i].name.c_str(), BookLibrary[i].author.c_str());

	system("pause");
}
void borrowingBook(ES_User * user) {
	printf("||--------------------------------\n");
	printf("|| 编号       书名           作者    \n");
	printf("||--------------------------------\n");

	for (int i = 0; i < BookLibrary.size(); i++)
		printf("|| %d\t%10s     %10s\n", i + 1, BookLibrary[i].name.c_str(), BookLibrary[i].author.c_str());

	int v = -1;
	while (v == -1) {
		Query("请输入您所要借阅的书序号");
		cin >> v;
		if (v >= 1 && v <= BookLibrary.size())
			break;
		else if (v == 0)
			return;
		else {
			Query("请规范您的输入！");
			v = -1;
		}
	}
	ES_BookMessage a;
	a.book = &BookLibrary[v - 1];
	if (!a.book->num) {
		cout << ">>> 该书已被借阅完，无法借阅" << endl;
	} else {
		cout << ">>> 该书剩余本数：" << a.book->num << endl;
		a.user = user;
		Query("请输入您的借书时间");
		cin >> a.borrowTime;
		a.returnTime = -1;
		a.fine = -1;
		a.book->num--;
		user->borrowing.push_back(a);
		BorrowingLibrary.push_back(a);
		cout << ">>> 借阅成功!" << endl;
	}
	system("pause");
}
void returnBook(ES_User * user) {
	printf("||----------------------------------\n");
	printf("|| 编号       书名		   借书时间  \n");
	printf("||----------------------------------\n");

	for (int i = 0; i < user->borrowing.size(); i++)
		printf("|| %d\t%10s     %d\n", i + 1, user->borrowing[i].book->name.c_str(), user->borrowing[i].borrowTime);

	
	int v = -1;
	while (v == -1) {
		Query("请选择您想要归还的书");
		cin >> v;
		if (v >= 1 && v <= user->borrowing.size())
			break;
		else if (v == 0)
			return;
		else {
			cout << "" << endl;
			v = -1;
		}
	}
	ES_BookMessage a = user->borrowing[v - 1];
	vector<ES_BookMessage>::iterator i = user->borrowing.begin();

	i += v - 1;

	auto cost_t = (*i).book->cost;

	user->borrowing.erase(i);
	i = BorrowingLibrary.begin();
	for (; i != BorrowingLibrary.end(); i++) {
		if ((*i).user == a.user && (*i).book == a.book && (*i).borrowTime == a.borrowTime) {
			BorrowingLibrary.erase(i);
			break;
		}
	}
	Query("还书时间");
	cin >> a.returnTime;
	if (a.returnTime - a.borrowTime > MAXTIMES) {
		cout << ">>> 超过时间";
		a.fine = (a.returnTime - a.borrowTime - MAXTIMES)*cost_t;
	}
	user->history.push_back(a);
	HistoryLibrary.push_back(a);
	a.book->num++;
	system("pause");
}

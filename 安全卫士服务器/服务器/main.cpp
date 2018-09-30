#include <stdio.h>
#include <iostream>
using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define CLOUDEKILL 1
#define MD5INFO 2
#define EXIT 0

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include "mysql/include/mysql.h"
#pragma comment(lib, "mysql/lib/libmysql.lib")




struct SENDSTC
{
	int type;
	char md5[33];
	char filePath[MAX_PATH];
};

MYSQL mysql{};

//初始化数据库
//bool padsafaf()
//{
//	if (0 == mysql_library_init(0, NULL, NULL)) {
//		cout << "mysql_library_init() succeed" << endl;
//	}
//	else {
//		cout << "mysql_library_init() failed" << endl;
//		return false;
//	}
//	return true;
//}

DWORD CALLBACK thrProc(LPVOID lp)
{
	SENDSTC ss{};
	while (1)
	{
		recv(SOCKET(lp), (char*)&ss, sizeof(SENDSTC), 0);
		//if (ss.type == EXIT)
		//{
		//	printf("客户端已退出!");
		//}
		if (ss.type == CLOUDEKILL)
		{
			//printf("%s\n%s\n", ss.filePath, ss.md5);
			mysql_query(&mysql, "select * from VirusInfo;");
			MYSQL_RES* pRes = NULL;
			pRes = mysql_use_result(&mysql);
			if (pRes == nullptr) {
				printf("获取结果集错误,原因:%s", mysql_error(&mysql));
				continue;
			}
			//列数
			int nColCount = mysql_num_fields(pRes);
			char* pColName = nullptr;
			// 获取所有列的名字
			//MYSQL_FIELD* pField = nullptr;
			//for (int i = 0; i < nColCount; ++i) {
			//	pField = mysql_fetch_field(pRes);
			//	if (pField == nullptr)continue;
			//	printf("%s | ", pField->name);
			//}
			//printf("\n");

			// 获取每行每列的内容
			MYSQL_ROW pRow = NULL;
			do {

				// 获取一行内容.
				while (pRow = mysql_fetch_row(pRes)) {
					// 打印一行中的每一列
					//for (int i = 0; i < nColCount; ++i) {
					//	//if (pRow[i] != NULL) { // 防止数据为空
					//	//	printf("%s | ", pRow[i]);
					//	//}
					//	//else {
					//	//	printf("    ");
					//	//}
					//	if (nColCount == 1)
					//	{
					//		if (strcmp(pRow[i], ss.md5) == 0)
					//		{
					//			send(SOCKET(lp), (char*)&ss, sizeof(ss), 0);
					//		}
					//	}
					//}
					if (strcmp(pRow[1], ss.md5) == 0)
					{
						send(SOCKET(lp), (char*)&ss, sizeof(ss), 0);
						break;
					}
					printf("\n");
				}
				mysql_free_result(pRes);
				// 再获取一行
			} while ((pRes = mysql_use_result(&mysql)) != nullptr);
		}
		else if (ss.type == MD5INFO)
		{
			char tmp[512]{};
			sprintf(tmp, "insert into VirusInfo(virusname,md5value) values('%s', '%s')", ss.filePath, ss.md5);
			int ret = mysql_real_query(&mysql, tmp, strlen(tmp));
			int ii = 0;
			//mysql_query(&mysql, "insert into VirusInfo(virusname,md5value) values(ss.filePath, ss.md5)");
		}
	}
	return 0;
}


int main()
{
	//3. 初始化mysql库
	mysql_library_init(0, 0, nullptr);

	//4. 初始化mysql结构体对象,在以后的使用中,都是使用这个对象
	
	mysql_init(&mysql);

	//5. 连接到mysql数据库
	mysql_real_connect(&mysql, "127.0.0.1", "root", "root", "virus", 3306, nullptr, 0);
	if (mysql_errno(&mysql) != 0) {
		printf("连接数据库出错: %s\n", mysql_error(&mysql));
		system("pause");
		return 0;
	}
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	WSADATA wd = {};
	if (WSAStartup(MAKEWORD(2, 2), &wd))
	{
		printf("环境初始化失败\n");
		return 0;
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == SOCKET_ERROR)
	{
		printf("SOCKET创建失败!\n");
		return 0;
	}
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	bind(sock, (sockaddr*)&addr, sizeof(sockaddr_in));
	listen(sock, 5);
	//int nLen = 0;
	SOCKET clientSock = accept(sock, 0, 0);
	printf("客户端已连接!\n");
	HANDLE hThr = CreateThread(0, 0, thrProc, LPVOID(clientSock), 0, 0);
	WaitForSingleObject(hThr, -1);
	WSACleanup();
	// 3.1 结束mysql库的使用
	mysql_server_end();
	return 0;
}
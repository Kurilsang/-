#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//数据容器(链表)
//设置成全局变量方便添加
int login_is_continue;//全局变量，用于控制是否退出登录，0为退出，1为登录状态
struct Node* accountList = NULL;//账号链表的全局变量
struct room* roomList = NULL;//房间链表的全局变量
//数据的结构
//账号的结构
struct account {
	char name[20];//用户名
	float money;//余额
	int discount;//打折额度
	//房间
	int room;
	//身份(0普通，1vip，2管理员)
	int character;
};
struct roomClass {
	int number;//房间号
	int situation;//状态：用0表示未出租，用1表示已出租
	int type;//0为普通，1为VIP房
	int price;//价格
};
//节点的结构
//账号
struct Node {
	struct account data;
	struct Node* next;
};
//房间
struct room {
	struct roomClass data;
	struct room* next;
};
//创建头节点的函数
struct Node* CreateHead() {
	//动态内存申请
	struct Node* NodeHead = (struct Node*)malloc(sizeof(struct Node));
	//头节点的指针指向初始化
	NodeHead->next = NULL;
	//函数返回一个头节点结构体
	return NodeHead;
}
//创建房间链表的头节点
struct room* createRoomHead() {
	struct room* Head = (struct room*)malloc(sizeof(struct room));
	Head->next = NULL;
	return Head;
}
//建立账号中间节点的函数
struct Node* createNode(struct account data) {
	struct Node* Node = (struct Node*)malloc(sizeof(struct Node));
	Node->next = NULL;
	//传入这个节点存放的数据
	Node->data = data;
	//返回该节点的结构体
	return Node;
}
//创建房间链表的中间节点函数
struct room* createRoom(struct roomClass data) {
	struct room* newRoom = (struct room*)malloc(sizeof(struct room));
	//初始化
	newRoom->data = data;
	newRoom->next = NULL;
	return newRoom;
}
//从头部插入链表
//账号
void insertListByHead(struct Node* ListHead, struct account data)
{
	//给数据先建立节点结构体
	struct Node* NewNode = createNode(data);
	//把新节点的指针设置在原本头节点指针的位置
	NewNode->next = ListHead->next;
	//把头节点的指针指向新节点
	ListHead->next = NewNode;
}
//房间
void insertRoomByHead(struct room* List, struct roomClass data)
{
	struct room* newRoom = createRoom(data);
	newRoom->next = List->next;
	List->next = newRoom;
}
//从尾部插入链表
void insertListByTail(struct Node* ListHead, struct account data)
{
	struct Node* NewNode = createNode(data);
	struct Node* pMove = ListHead;
	while (pMove->next != NULL)
	{
		pMove = pMove->next;
	}
	pMove->next = NewNode;
}
void insertRoomByTail(struct room* roomHead, struct roomClass room)
{
	struct room* newRoom = createRoom(room);
	struct room* pMove = roomHead;
	while (pMove->next != NULL)
	{
		pMove = pMove->next;
	}
	pMove->next = newRoom;
}
//遍历链表区块--------
//账号
void printList(struct Node* ListHead) {
	struct Node* pMove = ListHead->next;
	printf("\t用户名\t房间号\t身份\t打折\t余额\n");
	while (pMove != NULL)
	{
		printf("\t%s", pMove->data.name);
		if (pMove->data.room == 0)
		{
			printf("\t未入住");
		}
		else {
			printf("\t%d", pMove->data.room);
		}
		int tempCharacter = pMove->data.character;
		if (tempCharacter == 0)
		{
			printf("\t普通");
		}
		else if (tempCharacter == 1)
		{
			printf("\tVIP");
		}
		else if (tempCharacter == 2)
		{
			printf("\t管理员");
		}
		printf("\t%d", pMove->data.discount);
		printf("\t%lf\n", pMove->data.money);

		

		pMove = pMove->next;
	}
}
//房间
void printRooms(struct room* roomList) {
	struct room* pMove = roomList->next;
	printf("\t房间号\t状态\t类型\t价格\n");
	while (pMove != NULL)
	{
		printf("\t%d", pMove->data.number);
		if (pMove->data.situation == 1)
		{
			printf("\t使用中");
		}
		else if (pMove->data.situation == 0)
		{
			printf("\t空闲");
		}
		if (pMove->data.type == 0)
		{
			printf("\t普通");
		}
		else if (pMove->data.type == 1)
		{
			printf("\tVIP");
		}
		printf("\t%d\n", pMove->data.price);
	/*	printf("\t%d\t%d\n", pMove->data.number, pMove->data.situation);*///调试使用
		pMove = pMove->next;
	}
}
//查看当前空闲房间
void printFreeRooms(struct room* roomHead) {
	struct room* pMove = roomHead->next;
	printf("空闲房间列表:\n");
	printf("\t房间号\t状态\t类型\t价格\n");
	while (pMove != NULL)
	{
		if (pMove->data.situation == 0)
		{
			printf("\t%d", pMove->data.number);
			if (pMove->data.situation == 0)
			{
				printf("\t空闲");
			}
			if (pMove->data.type == 0)
			{
				printf("\t普通");
			}
			else if (pMove->data.type == 1)
			{
				printf("\tVIP");
			}
			printf("\t%d\n", pMove->data.price);
		}
		pMove = pMove->next;
	}
}
//链表查找区块-------
//查找账号
struct Node* searchNodeByName(struct Node* ListHead, char* accountName)
{
	struct Node* posNode = ListHead->next;
	while (posNode != NULL && strcmp(posNode->data.name, accountName))
	{
		posNode = posNode->next;
	}
	return posNode;
}
//查找房间
struct room* searchRoomByNumber(struct room* roomHead, int number)
{
	struct room* pMove = roomHead->next;
	while (pMove != NULL && pMove->data.number != number)
	{
		pMove = pMove->next;
	}
	return pMove;
}
//链表删除区块------
//删除特定账号
void deleteAccountByName(struct Node* ListHead, char* accountName)
{
	struct Node* pMoveLeft = ListHead;
	struct Node* pMove = pMoveLeft->next;
	while (pMove != NULL && strcmp(pMove->data.name, accountName))
	{
		//一起前进
		pMoveLeft = pMove;
		pMove = pMoveLeft->next;
	}
	//找不到
	if (pMove == NULL)
	{
		printf("找不到该账号！\n");
	}
	else {
		pMoveLeft->next = pMove->next;
		free(pMove);//释放内存
		pMove = NULL;//防止野指针的出现
	}
}
//删除特定房间
void deleteRoomByNumber(struct room* roomHead, int number) {
	struct room* leftRoom = roomHead;
	struct room* Room = leftRoom->next;
	while (Room != NULL && Room->data.number != number)
	{
		leftRoom = leftRoom->next;
		Room = leftRoom->next;
	}
	if (Room == NULL)
	{
		printf("该房间不存在！\n");
	}
	else {
		leftRoom->next = Room->next;
		free(Room);
		Room = NULL;
		printf("删除成功！\n");
	} 
}
//界面
//最开始的菜单
int Menu() {
	printf("-------欢迎使用旅馆小助手-------\n");
	printf("-------\t1.登录-------\n");
	printf("-------\t2.注册-------\n");
	printf("-------\t0.退出-------\n");
	printf("-------欢迎使用旅馆小助手-------\n");
	printf("请输入操作数(0~2):\n");
	return 0;
}

//登录后界面
int loginedMenu(struct account data) {
	printf("------欢迎使用旅馆小助手-------\n");
	printf(" 欢迎顾客: %s ", data.name);
	printf(" 当前余额: %f ", data.money);
	printf(" 享受折扣: %d折 \n", data.discount);
	printf("------\t1.查看空闲房间-------\n");
	printf("------\t2.开房-------\n");
	printf("------\t3.退房-------\n");
	printf("------\t4.查看我的房卡-------\n");
	printf("------\t5.充值-------\n");
	printf("------\t6.充值vip（500元永久会员,享受七折优惠）-------\n");
	printf("------\t0.退出登录-------\n");
	printf("------欢迎使用旅馆小助手-------\n");
	printf("请输入操作数(0~5):\n");

	return 0;
}
//管理员登录菜单
int loginAdminMenu(struct account data) {
	printf("------欢迎使用旅馆小助手-------\n");
	printf("\t欢迎管理员:%s\n", data.name);
	printf("------\t1.增加其他账号-------\n");
	printf("------\t2.注销其他账号-------\n");
	printf("------\t3.增加房间-------\n");
	printf("------\t4.减少房间-------\n");
	printf("------\t5.改变特定用户的身份-------\n");
	printf("-------\t6.查看账号列表-------\n");
	printf("-------\t7.查看房间列表-------\n");
	printf("------\t0.退出登录-------\n");
	printf("------欢迎使用旅馆小助手-------\n");
	printf("请输入操作数:(0~5)\n");
}
//注册菜单
int registerMenu() {
	printf("------欢迎使用旅馆小助手-------\n");
	printf("\t【注册】\n");
	printf("------\t1.管理员用户-------\n");
	printf("------\t2.普通用户-------\n");
	printf("------欢迎使用旅馆小助手-------\n");
	printf("请输入操作数(1~2):\n");

	return 0;
}
//保存到本地的函数
//账号数据
void saveToFileAccount(const char* fileName, struct Node* headNode) {
	FILE* fp = fopen(fileName, "w");
	struct Node* pMove = headNode->next;
	while (pMove != NULL)
	{
		fprintf(fp, "%s\t%f\t%d\t%d\t%d\n", pMove->data.name, pMove->data.money, pMove->data.discount,
			pMove->data.character, pMove->data.room);
		pMove = pMove->next;
	}
	fclose(fp);
}
//房间
void saveToFileRoom(const char* filename, struct room* headRoom)
{
	FILE* fp = fopen(filename, "w");
	struct room* pMove = headRoom->next;
	while (pMove != NULL)
	{
		fprintf(fp, "\t%d\t%d\t%d\t%d\n", pMove->data.number,pMove->data.situation, pMove->data.type, pMove->data.price);
		pMove = pMove->next;
	}
	fclose(fp);
}
//读取本地数据的函数
//账号
void readFromFileAccount(const char* fileName, struct Node* headNode)
{
	FILE* fp = fopen(fileName, "a+");
	struct account accountInfo;
	while (fscanf(fp, "%s\t%f\t%d\t%d\t%d\n", accountInfo.name, &accountInfo.money,
		&accountInfo.discount, &accountInfo.character, &accountInfo.room) != EOF)
	{
		insertListByTail(headNode, accountInfo);
	}	
	fclose(fp);
}
//房间
void readFromFileRoom(struct room* roomHead) {
	FILE* fp = fopen("room_data.txt", "a+");
	struct roomClass roomData;
	while (fscanf(fp, "\t%d\t%d\t%d\t%d\n", &roomData.number, &roomData.situation, &roomData.type, &roomData.price) != EOF)
	{
		insertRoomByTail(roomHead, roomData);
	}
	fclose(fp);
}
//交互区块----------
// 查看自己的房卡函数
void look(struct Node* account) {
	printf("\t用户名：%s", account->data.name);
	//没房
	if (account->data.room == 0)
	{
		printf("\t房间号：未入住");
	}
	else {
		printf("\t房间号:%d", account->data.room);
		
	}
	//身份判断（管理员账号除外，因为不会进入到这里来）
	int key = account->data.character;
	switch (key)
	{
	case 0:
		printf("\t身份：普通\n");
		break;
	case 1:
		printf("\t身份：VIP\n");
		break;
	default:
		printf("error\n");
		break;
	}
}
// 退房函数
void quitRoom(struct Node* account, int roomNumber) {
	//检查是不是已经有房间
	if (account->data.room == 0)
	{
		printf("您还没有入住房间！\n");
	}
	else {
		//设置账号的房间
		account->data.room = 0;
		//设置房间的状态
		searchRoomByNumber(roomList, roomNumber)->data.situation = 0;
		printf("退房成功！\n");
	}
}
// 开房函数
void openRoom(struct Node* account, int roomNumber) {
	//看有没有房
	if (account->data.room == 0)
	{
		//看是不是vip
		float priceOrigin = searchRoomByNumber(roomList, roomNumber)->data.price;
		float price = priceOrigin * ((double)account->data.discount / 10);
		if (account->data.character == 1)
		{
			printf("您是尊贵的vip，开房仅需%f哦亲~\n", price);
		}
		else if (account->data.character == 0)
		{
			printf("您开房需要%f元哦亲~\n", price);
		}
		//看钱够不够
		if (account->data.money - price >= 0)
		{
			//查找房间并将该房间的situation设置为1
			if (searchRoomByNumber(roomList, roomNumber) == NULL)
			{
				printf("不存在该房间！\n");
			}
			else {
				//判断房间是否空闲
				if (searchRoomByNumber(roomList, roomNumber)->data.situation == 1)
				{
					printf("该房间已有人使用！\n");
				}
				else {
					searchRoomByNumber(roomList, roomNumber)->data.situation = 1;
					//设置该账户的房间
					account->data.room = roomNumber;
					printf("开房成功！\n");
					printf("您的房间号码是%d\n", account->data.room);
					account->data.money -= price;
					printf("已扣除%f,余额为%f\n", price, account->data.money);
				}

			}
		}
		else {
			printf("滚啊，穷逼~\n");
		}
	}
	else {
		printf("一人只能入住一间房间哦~\n");
		printf("如需换房请先退房\n");
	}
}
//显示当前链表状态的函数
// 账号
void AccountList()
{
	printf("此时账号的列表为：\n");
	printRooms(accountList);
}
//房间
void printRoomList()
{
	printf("此时房间的列表为：\n");
	printRooms(roomList);
}
//打折和身份绑定函数
void discount_character(struct Node* account) {
	if (account->data.character == 1)
	{
		account->data.discount = 7;
	}
	else {
		account->data.discount = 10;
	}
}
//升级vip函数
int toVIP(struct Node* account) {
	if (account->data.money - 500 >= 0 && account->data.character == 0)
	{
		account->data.character = 1;
		account->data.discount = 7;
		account->data.money -= 500;
		printf("升级vip成功！\n");
		printf("当前享受折扣%d折\n", account->data.discount);
		printf("余额:%f\n", account->data.money);
	}
	else if (account->data.character != 0)
	{
		printf("您已经是VIP或管理员，无需升级！\n");
	}
	else {
		printf("您的余额不足，请充值！\n");
	}
}
// 登陆后交互（管理员账号）
int loginedAdmin() {
	int key;
	scanf("%d", &key);
	struct account tempAccount;
	struct roomClass roomData;
	switch (key)
	{
	case 1:
		printf("\t【增加其他账号】\n");
		printf("账号列表:\n");
		printList(accountList);
		printf("\t请输入要添加的账户名：\n");
		tempAccount.room = 0;
		scanf("%s", tempAccount.name);
		struct Node* result1 = searchNodeByName(accountList, tempAccount.name);
		if (result1 != NULL)
		{
			printf("已存在相同用户名的账户！\n");
		}
		else {
			printf("\t请输入要添加的账户的身份(0为普通顾客，1为VIP，2为管理员)：\n");
			scanf("%d", &tempAccount.character);
			if (tempAccount.character == 1)
			{
				tempAccount.discount = 7;
			}
			else if (tempAccount.character == 0 || tempAccount.character == 2)
			{
				tempAccount.discount = 10;
			}
			else {
				printf("error/请不要输入0，1，2以外的整数");
			}
			printf("\t请输入要添加的账户的余额：\n");
			scanf("%f", &tempAccount.money);
			if (tempAccount.money >= 0)
			{
				insertListByHead(accountList, tempAccount);
				saveToFileAccount("account_data.txt", accountList);
				printf("添加成功\n");
				printf("该账号的用户名为%s, 身份为%d, 余额为%f\n", tempAccount.name, tempAccount.character, tempAccount.money);
				printf("此时账号列表:\n");
				printList(accountList);
			}
			else {
				printf("error!请输入大于等于0的数\n");
				printf("添加失败,请重新添加并输入正确的账户余额\n");
			}
		}
		system("pause");
		break;
	case 2:
		printf("\t【注销其他账号】\n");
		printf("账号列表:\n");
		printList(accountList);
		printf("请输入要注销的账户的账户名:\n");
		scanf("%s", tempAccount.name);
		deleteAccountByName(accountList, tempAccount.name);
		saveToFileAccount("account_data.txt", accountList);
		printf("注销成功！\n");
		printf("此时的账号列表：\n");
		printList(accountList);
		system("pause");
		break;
	case 3:
		printf("\t【增加房间】\n");
		printRoomList(roomList);
		printf("请输入要添加的房间号（输入一个三位数）：\n");
		scanf("%d", &roomData.number);
		if (roomData.number >= 100 && roomData.number <= 999)
		{

			//防止重复名称
			if (searchRoomByNumber(roomList, roomData.number) != NULL)
			{
				printf("该房间已经存在！\n");
			}
			else
			{
				printf("请输入要添加房间的类型(0为普通，1为VIP)：\n");
				scanf("%d", &roomData.type);
				if (roomData.type == 1 || roomData.type == 0)
				{
					printf("请输入要添加房间的价格：\n");
					scanf("%d", &roomData.price);
					if (roomData.price >= 1)
					{
						roomData.situation = 0;//初始化为空闲状态
						insertRoomByHead(roomList, roomData);
						saveToFileRoom("room_data.txt", roomList);
						printf("添加成功!\n");
						printRoomList(roomList);
					}
					else {
						printf("error/价格应当大于0元！\n");
					}
				}
				else {
					printf("error/请输入1或0\n");
				}
				
			}
		}
		//防止重复名称
		else {
			printf("error/请输入一个三位数！\n");
		}
		system("pause");
		break;
	case 4:
		printf("\t【删除房间】\n");
		printRoomList(roomList);
		printf("请输入你要删除的房间的房间号(输入一个三位数）:\n");
		scanf("%d", &roomData.number);
		if (roomData.number >= 100 && roomData.number <= 999)
		{
			deleteRoomByNumber(roomList, roomData.number);
			printRoomList(roomList);
		}
		else {
			printf("error/请输入一个三位数\n");
		}
		saveToFileRoom("room_data.txt", roomList);
		system("pause");
		break;
	case 5:
		printf("【改变其他账号身份】\n");
		printf("账号列表:\n");
		printList(accountList);
		printf("请输入要改变的账号的账户名:\n");
		scanf("%s", tempAccount.name);
		printf("请输入改变后他的身份（0为普通，1为VIP，2为管理员）\n");
		scanf("%d", &tempAccount.character);
		struct Node* result = searchNodeByName(accountList, tempAccount.name);
		result->data.character = tempAccount.character;
		discount_character(result);
		saveToFileAccount("account_data.txt", accountList);
		printf("更改成功！\n");
		printf("此账号的账户名为%s,此时的身份为%d\n", result->data.name, result->data.character);
		system("pause");
		break;
	case 6://调试用，看此时的账户名总数
		printf("输出链表\n");
		printList(accountList);
		system("pause");
		break;
	case 7:
		printRoomList(roomList);
		system("pause");
		break;
	case 0:
		printf("【退出登录】\n");
		login_is_continue = 0;
		system("pause");
		break;
	default:
		printf("error\n");
		system("pause");
		break;
	}

}
// 登录后界面交互(顾客账号)
int loginedNormal(struct Node* Account) {
	int key;
	struct roomClass tempRoom;
	scanf("%d", &key);
	switch (key)
	{
	case 1:
		printf("\t【查看空闲房间】\n");
		printFreeRooms(roomList);
		system("pause");
		break;
	case 2:
		printf("\t【开房】\n");
		printFreeRooms(roomList);
		printf("请输入您想要开的房间的房间号(输入一个房间):\n");
		scanf("%d", &tempRoom.number);
		openRoom(Account, tempRoom.number);
		saveToFileRoom("room_data.txt", roomList);
		saveToFileAccount("account_data.txt", accountList);
		system("pause");
		break;
	case 3:
		printf("\t【退房】\n");
		tempRoom.number = Account->data.room;
		quitRoom(Account, tempRoom.number);
		saveToFileAccount("account_data.txt", accountList);
		saveToFileRoom("room_data.txt", roomList);
		printf("您的房卡已更新！\n");
		look(Account);
		system("pause");
		break;
	case 4:
		printf("\t【查看我的房卡】\n");
		look(Account);
		system("pause");
		break;
	case 5:
		printf("\t【充值】\n");
		printf("请输入要充值的金额：\n");
		float moneyInput;
		scanf("%f", &moneyInput);
		if (moneyInput > 0)
		{
			Account->data.money += moneyInput;
			printf("充值成功！当前余额为：%f\n", Account->data.money);
		}
		else {
			printf("请输入大于0的金额！\n");
		}
		saveToFileAccount("account_data.txt", accountList);
		system("pause");
		break;
	case 6:
		printf("消耗500元升级为vip\n");
		toVIP(Account);
		saveToFileAccount("account_data.txt", accountList);
		system("pause");
		break;
	case 0:
		printf("\t【退出登录】\n");
		login_is_continue = 0;
		system("pause");
		break;
	default:
		printf("error\n");
		system("pause");
		break;
	}

	return 0;
}
// 注册选择
int registerSelect() {
	int key;
	struct account tempAccount;
	scanf("%d", &key);
	switch (key)
	{
	case 1:
		printf("\t【管理员账号注册】\n");
		printf("\t请输入获取操作权限的密码\n");
		int password = 0;
		scanf("%d", &password);
		if (password == 123456)
		{
			printf("密码正确!\n");
			tempAccount.discount = 10;
			tempAccount.money = 0;
			tempAccount.character = 2;
			tempAccount.room = 0;
			printf("请输入用户名:\n");
			scanf("%s", tempAccount.name);
			struct Node* result = searchNodeByName(accountList, tempAccount.name);
			if (result != NULL)
			{
				printf("已经存在相同用户名的账号！\n");
			}
			else
			{
				insertListByHead(accountList, tempAccount);
				saveToFileAccount("account_data.txt", accountList);
				printf("注册成功！\n");
			}
		}
		else {
			printf("密码错误\n");
		}
		break;
	case 2:
		printf("\t【普通账号注册】\n");
		printf("\t请输入用户名\n");
		//int n1;
		//scanf("%d", &n1);
		tempAccount.discount = 10;
		tempAccount.character = 0;
		tempAccount.money = 0;
		tempAccount.room = 0;
		scanf("%s", tempAccount.name);
		struct Node* result = searchNodeByName(accountList, tempAccount.name);
		if (result != NULL)
		{
			printf("已存在相同用户名的账号!\n");
		}
		else {
			insertListByHead(accountList, tempAccount);
			printf("【注册成功】\n");
			saveToFileAccount("account_data.txt", accountList);
		}
		break;
	default:
		printf("error\n");
		system("pause");
		break;
	}

	return 0;
}
// 登录
int login() {
	printf("请输入用户名\n");
	struct account tempAccount;
	tempAccount.discount = 10;
	tempAccount.money = 0;
	tempAccount.character = 0;
	tempAccount.room = 0;
	scanf("%s", tempAccount.name);
	struct Node* result = NULL;
	result = searchNodeByName(accountList, tempAccount.name);
	if (result != NULL)
	{
		//管理员登录分支
		if (result->data.character == 2)
		{
			printf("\t【登录成功】\n");
			system("pause");
			login_is_continue = 1;
			while (login_is_continue) {
				system("cls");
				loginAdminMenu(result->data);
				loginedAdmin();
			}
		}
		//普通/VIP账号登录分支
		else {
			printf("\t【登录成功】\n");
			system("pause");
			login_is_continue = 1;
			while (login_is_continue) {
				system("cls");
				loginedMenu(result->data);
				loginedNormal(result);
			}
		}
	}
	else
	{
		printf("\t【找不到此账户】\n");
		system("pause");
	}
	return 0;
}
//登录注册
int loginRegister() {
	int key;
	scanf("%d", &key);
	switch (key)
	{
	case 0:
		printf("\t【退出成功】\n");
		system("pause");
		exit(0);
		break;
	case 1:
		printf("\t【登录】\n");
		login();
		break;

	case 2:
		system("cls");
		printf("\t【注册】\n");
		registerMenu();
		registerSelect();
		system("pause");
		break;
	default:
		printf("error\n");
		system("pause");
		break;
	}
	return 0;
}
int main() {
	//初始化链表
	accountList = CreateHead();
	roomList = createRoomHead();
	readFromFileAccount("account_data.txt", accountList);
	readFromFileRoom(roomList);
	while (1)
	{
		Menu();
		loginRegister();
		system("cls");
	}

	return 0;
}
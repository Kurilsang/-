#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//��������(����)
//���ó�ȫ�ֱ����������
int login_is_continue;//ȫ�ֱ��������ڿ����Ƿ��˳���¼��0Ϊ�˳���1Ϊ��¼״̬
struct Node* accountList = NULL;//�˺������ȫ�ֱ���
struct room* roomList = NULL;//���������ȫ�ֱ���
//���ݵĽṹ
//�˺ŵĽṹ
struct account {
	char name[20];//�û���
	float money;//���
	int discount;//���۶��
	//����
	int room;
	//���(0��ͨ��1vip��2����Ա)
	int character;
};
struct roomClass {
	int number;//�����
	int situation;//״̬����0��ʾδ���⣬��1��ʾ�ѳ���
	int type;//0Ϊ��ͨ��1ΪVIP��
	int price;//�۸�
};
//�ڵ�Ľṹ
//�˺�
struct Node {
	struct account data;
	struct Node* next;
};
//����
struct room {
	struct roomClass data;
	struct room* next;
};
//����ͷ�ڵ�ĺ���
struct Node* CreateHead() {
	//��̬�ڴ�����
	struct Node* NodeHead = (struct Node*)malloc(sizeof(struct Node));
	//ͷ�ڵ��ָ��ָ���ʼ��
	NodeHead->next = NULL;
	//��������һ��ͷ�ڵ�ṹ��
	return NodeHead;
}
//�������������ͷ�ڵ�
struct room* createRoomHead() {
	struct room* Head = (struct room*)malloc(sizeof(struct room));
	Head->next = NULL;
	return Head;
}
//�����˺��м�ڵ�ĺ���
struct Node* createNode(struct account data) {
	struct Node* Node = (struct Node*)malloc(sizeof(struct Node));
	Node->next = NULL;
	//��������ڵ��ŵ�����
	Node->data = data;
	//���ظýڵ�Ľṹ��
	return Node;
}
//��������������м�ڵ㺯��
struct room* createRoom(struct roomClass data) {
	struct room* newRoom = (struct room*)malloc(sizeof(struct room));
	//��ʼ��
	newRoom->data = data;
	newRoom->next = NULL;
	return newRoom;
}
//��ͷ����������
//�˺�
void insertListByHead(struct Node* ListHead, struct account data)
{
	//�������Ƚ����ڵ�ṹ��
	struct Node* NewNode = createNode(data);
	//���½ڵ��ָ��������ԭ��ͷ�ڵ�ָ���λ��
	NewNode->next = ListHead->next;
	//��ͷ�ڵ��ָ��ָ���½ڵ�
	ListHead->next = NewNode;
}
//����
void insertRoomByHead(struct room* List, struct roomClass data)
{
	struct room* newRoom = createRoom(data);
	newRoom->next = List->next;
	List->next = newRoom;
}
//��β����������
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
//������������--------
//�˺�
void printList(struct Node* ListHead) {
	struct Node* pMove = ListHead->next;
	printf("\t�û���\t�����\t���\t����\t���\n");
	while (pMove != NULL)
	{
		printf("\t%s", pMove->data.name);
		if (pMove->data.room == 0)
		{
			printf("\tδ��ס");
		}
		else {
			printf("\t%d", pMove->data.room);
		}
		int tempCharacter = pMove->data.character;
		if (tempCharacter == 0)
		{
			printf("\t��ͨ");
		}
		else if (tempCharacter == 1)
		{
			printf("\tVIP");
		}
		else if (tempCharacter == 2)
		{
			printf("\t����Ա");
		}
		printf("\t%d", pMove->data.discount);
		printf("\t%lf\n", pMove->data.money);

		

		pMove = pMove->next;
	}
}
//����
void printRooms(struct room* roomList) {
	struct room* pMove = roomList->next;
	printf("\t�����\t״̬\t����\t�۸�\n");
	while (pMove != NULL)
	{
		printf("\t%d", pMove->data.number);
		if (pMove->data.situation == 1)
		{
			printf("\tʹ����");
		}
		else if (pMove->data.situation == 0)
		{
			printf("\t����");
		}
		if (pMove->data.type == 0)
		{
			printf("\t��ͨ");
		}
		else if (pMove->data.type == 1)
		{
			printf("\tVIP");
		}
		printf("\t%d\n", pMove->data.price);
	/*	printf("\t%d\t%d\n", pMove->data.number, pMove->data.situation);*///����ʹ��
		pMove = pMove->next;
	}
}
//�鿴��ǰ���з���
void printFreeRooms(struct room* roomHead) {
	struct room* pMove = roomHead->next;
	printf("���з����б�:\n");
	printf("\t�����\t״̬\t����\t�۸�\n");
	while (pMove != NULL)
	{
		if (pMove->data.situation == 0)
		{
			printf("\t%d", pMove->data.number);
			if (pMove->data.situation == 0)
			{
				printf("\t����");
			}
			if (pMove->data.type == 0)
			{
				printf("\t��ͨ");
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
//�����������-------
//�����˺�
struct Node* searchNodeByName(struct Node* ListHead, char* accountName)
{
	struct Node* posNode = ListHead->next;
	while (posNode != NULL && strcmp(posNode->data.name, accountName))
	{
		posNode = posNode->next;
	}
	return posNode;
}
//���ҷ���
struct room* searchRoomByNumber(struct room* roomHead, int number)
{
	struct room* pMove = roomHead->next;
	while (pMove != NULL && pMove->data.number != number)
	{
		pMove = pMove->next;
	}
	return pMove;
}
//����ɾ������------
//ɾ���ض��˺�
void deleteAccountByName(struct Node* ListHead, char* accountName)
{
	struct Node* pMoveLeft = ListHead;
	struct Node* pMove = pMoveLeft->next;
	while (pMove != NULL && strcmp(pMove->data.name, accountName))
	{
		//һ��ǰ��
		pMoveLeft = pMove;
		pMove = pMoveLeft->next;
	}
	//�Ҳ���
	if (pMove == NULL)
	{
		printf("�Ҳ������˺ţ�\n");
	}
	else {
		pMoveLeft->next = pMove->next;
		free(pMove);//�ͷ��ڴ�
		pMove = NULL;//��ֹҰָ��ĳ���
	}
}
//ɾ���ض�����
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
		printf("�÷��䲻���ڣ�\n");
	}
	else {
		leftRoom->next = Room->next;
		free(Room);
		Room = NULL;
		printf("ɾ���ɹ���\n");
	} 
}
//����
//�ʼ�Ĳ˵�
int Menu() {
	printf("-------��ӭʹ���ù�С����-------\n");
	printf("-------\t1.��¼-------\n");
	printf("-------\t2.ע��-------\n");
	printf("-------\t0.�˳�-------\n");
	printf("-------��ӭʹ���ù�С����-------\n");
	printf("�����������(0~2):\n");
	return 0;
}

//��¼�����
int loginedMenu(struct account data) {
	printf("------��ӭʹ���ù�С����-------\n");
	printf(" ��ӭ�˿�: %s ", data.name);
	printf(" ��ǰ���: %f ", data.money);
	printf(" �����ۿ�: %d�� \n", data.discount);
	printf("------\t1.�鿴���з���-------\n");
	printf("------\t2.����-------\n");
	printf("------\t3.�˷�-------\n");
	printf("------\t4.�鿴�ҵķ���-------\n");
	printf("------\t5.��ֵ-------\n");
	printf("------\t6.��ֵvip��500Ԫ���û�Ա,���������Żݣ�-------\n");
	printf("------\t0.�˳���¼-------\n");
	printf("------��ӭʹ���ù�С����-------\n");
	printf("�����������(0~5):\n");

	return 0;
}
//����Ա��¼�˵�
int loginAdminMenu(struct account data) {
	printf("------��ӭʹ���ù�С����-------\n");
	printf("\t��ӭ����Ա:%s\n", data.name);
	printf("------\t1.���������˺�-------\n");
	printf("------\t2.ע�������˺�-------\n");
	printf("------\t3.���ӷ���-------\n");
	printf("------\t4.���ٷ���-------\n");
	printf("------\t5.�ı��ض��û������-------\n");
	printf("-------\t6.�鿴�˺��б�-------\n");
	printf("-------\t7.�鿴�����б�-------\n");
	printf("------\t0.�˳���¼-------\n");
	printf("------��ӭʹ���ù�С����-------\n");
	printf("�����������:(0~5)\n");
}
//ע��˵�
int registerMenu() {
	printf("------��ӭʹ���ù�С����-------\n");
	printf("\t��ע�᡿\n");
	printf("------\t1.����Ա�û�-------\n");
	printf("------\t2.��ͨ�û�-------\n");
	printf("------��ӭʹ���ù�С����-------\n");
	printf("�����������(1~2):\n");

	return 0;
}
//���浽���صĺ���
//�˺�����
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
//����
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
//��ȡ�������ݵĺ���
//�˺�
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
//����
void readFromFileRoom(struct room* roomHead) {
	FILE* fp = fopen("room_data.txt", "a+");
	struct roomClass roomData;
	while (fscanf(fp, "\t%d\t%d\t%d\t%d\n", &roomData.number, &roomData.situation, &roomData.type, &roomData.price) != EOF)
	{
		insertRoomByTail(roomHead, roomData);
	}
	fclose(fp);
}
//��������----------
// �鿴�Լ��ķ�������
void look(struct Node* account) {
	printf("\t�û�����%s", account->data.name);
	//û��
	if (account->data.room == 0)
	{
		printf("\t����ţ�δ��ס");
	}
	else {
		printf("\t�����:%d", account->data.room);
		
	}
	//����жϣ�����Ա�˺ų��⣬��Ϊ������뵽��������
	int key = account->data.character;
	switch (key)
	{
	case 0:
		printf("\t��ݣ���ͨ\n");
		break;
	case 1:
		printf("\t��ݣ�VIP\n");
		break;
	default:
		printf("error\n");
		break;
	}
}
// �˷�����
void quitRoom(struct Node* account, int roomNumber) {
	//����ǲ����Ѿ��з���
	if (account->data.room == 0)
	{
		printf("����û����ס���䣡\n");
	}
	else {
		//�����˺ŵķ���
		account->data.room = 0;
		//���÷����״̬
		searchRoomByNumber(roomList, roomNumber)->data.situation = 0;
		printf("�˷��ɹ���\n");
	}
}
// ��������
void openRoom(struct Node* account, int roomNumber) {
	//����û�з�
	if (account->data.room == 0)
	{
		//���ǲ���vip
		float priceOrigin = searchRoomByNumber(roomList, roomNumber)->data.price;
		float price = priceOrigin * ((double)account->data.discount / 10);
		if (account->data.character == 1)
		{
			printf("��������vip����������%fŶ��~\n", price);
		}
		else if (account->data.character == 0)
		{
			printf("��������Ҫ%fԪŶ��~\n", price);
		}
		//��Ǯ������
		if (account->data.money - price >= 0)
		{
			//���ҷ��䲢���÷����situation����Ϊ1
			if (searchRoomByNumber(roomList, roomNumber) == NULL)
			{
				printf("�����ڸ÷��䣡\n");
			}
			else {
				//�жϷ����Ƿ����
				if (searchRoomByNumber(roomList, roomNumber)->data.situation == 1)
				{
					printf("�÷���������ʹ�ã�\n");
				}
				else {
					searchRoomByNumber(roomList, roomNumber)->data.situation = 1;
					//���ø��˻��ķ���
					account->data.room = roomNumber;
					printf("�����ɹ���\n");
					printf("���ķ��������%d\n", account->data.room);
					account->data.money -= price;
					printf("�ѿ۳�%f,���Ϊ%f\n", price, account->data.money);
				}

			}
		}
		else {
			printf("���������~\n");
		}
	}
	else {
		printf("һ��ֻ����סһ�䷿��Ŷ~\n");
		printf("���軻�������˷�\n");
	}
}
//��ʾ��ǰ����״̬�ĺ���
// �˺�
void AccountList()
{
	printf("��ʱ�˺ŵ��б�Ϊ��\n");
	printRooms(accountList);
}
//����
void printRoomList()
{
	printf("��ʱ������б�Ϊ��\n");
	printRooms(roomList);
}
//���ۺ���ݰ󶨺���
void discount_character(struct Node* account) {
	if (account->data.character == 1)
	{
		account->data.discount = 7;
	}
	else {
		account->data.discount = 10;
	}
}
//����vip����
int toVIP(struct Node* account) {
	if (account->data.money - 500 >= 0 && account->data.character == 0)
	{
		account->data.character = 1;
		account->data.discount = 7;
		account->data.money -= 500;
		printf("����vip�ɹ���\n");
		printf("��ǰ�����ۿ�%d��\n", account->data.discount);
		printf("���:%f\n", account->data.money);
	}
	else if (account->data.character != 0)
	{
		printf("���Ѿ���VIP�����Ա������������\n");
	}
	else {
		printf("�������㣬���ֵ��\n");
	}
}
// ��½�󽻻�������Ա�˺ţ�
int loginedAdmin() {
	int key;
	scanf("%d", &key);
	struct account tempAccount;
	struct roomClass roomData;
	switch (key)
	{
	case 1:
		printf("\t�����������˺š�\n");
		printf("�˺��б�:\n");
		printList(accountList);
		printf("\t������Ҫ��ӵ��˻�����\n");
		tempAccount.room = 0;
		scanf("%s", tempAccount.name);
		struct Node* result1 = searchNodeByName(accountList, tempAccount.name);
		if (result1 != NULL)
		{
			printf("�Ѵ�����ͬ�û������˻���\n");
		}
		else {
			printf("\t������Ҫ��ӵ��˻������(0Ϊ��ͨ�˿ͣ�1ΪVIP��2Ϊ����Ա)��\n");
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
				printf("error/�벻Ҫ����0��1��2���������");
			}
			printf("\t������Ҫ��ӵ��˻�����\n");
			scanf("%f", &tempAccount.money);
			if (tempAccount.money >= 0)
			{
				insertListByHead(accountList, tempAccount);
				saveToFileAccount("account_data.txt", accountList);
				printf("��ӳɹ�\n");
				printf("���˺ŵ��û���Ϊ%s, ���Ϊ%d, ���Ϊ%f\n", tempAccount.name, tempAccount.character, tempAccount.money);
				printf("��ʱ�˺��б�:\n");
				printList(accountList);
			}
			else {
				printf("error!��������ڵ���0����\n");
				printf("���ʧ��,��������Ӳ�������ȷ���˻����\n");
			}
		}
		system("pause");
		break;
	case 2:
		printf("\t��ע�������˺š�\n");
		printf("�˺��б�:\n");
		printList(accountList);
		printf("������Ҫע�����˻����˻���:\n");
		scanf("%s", tempAccount.name);
		deleteAccountByName(accountList, tempAccount.name);
		saveToFileAccount("account_data.txt", accountList);
		printf("ע���ɹ���\n");
		printf("��ʱ���˺��б�\n");
		printList(accountList);
		system("pause");
		break;
	case 3:
		printf("\t�����ӷ��䡿\n");
		printRoomList(roomList);
		printf("������Ҫ��ӵķ���ţ�����һ����λ������\n");
		scanf("%d", &roomData.number);
		if (roomData.number >= 100 && roomData.number <= 999)
		{

			//��ֹ�ظ�����
			if (searchRoomByNumber(roomList, roomData.number) != NULL)
			{
				printf("�÷����Ѿ����ڣ�\n");
			}
			else
			{
				printf("������Ҫ��ӷ��������(0Ϊ��ͨ��1ΪVIP)��\n");
				scanf("%d", &roomData.type);
				if (roomData.type == 1 || roomData.type == 0)
				{
					printf("������Ҫ��ӷ���ļ۸�\n");
					scanf("%d", &roomData.price);
					if (roomData.price >= 1)
					{
						roomData.situation = 0;//��ʼ��Ϊ����״̬
						insertRoomByHead(roomList, roomData);
						saveToFileRoom("room_data.txt", roomList);
						printf("��ӳɹ�!\n");
						printRoomList(roomList);
					}
					else {
						printf("error/�۸�Ӧ������0Ԫ��\n");
					}
				}
				else {
					printf("error/������1��0\n");
				}
				
			}
		}
		//��ֹ�ظ�����
		else {
			printf("error/������һ����λ����\n");
		}
		system("pause");
		break;
	case 4:
		printf("\t��ɾ�����䡿\n");
		printRoomList(roomList);
		printf("��������Ҫɾ���ķ���ķ����(����һ����λ����:\n");
		scanf("%d", &roomData.number);
		if (roomData.number >= 100 && roomData.number <= 999)
		{
			deleteRoomByNumber(roomList, roomData.number);
			printRoomList(roomList);
		}
		else {
			printf("error/������һ����λ��\n");
		}
		saveToFileRoom("room_data.txt", roomList);
		system("pause");
		break;
	case 5:
		printf("���ı������˺���ݡ�\n");
		printf("�˺��б�:\n");
		printList(accountList);
		printf("������Ҫ�ı���˺ŵ��˻���:\n");
		scanf("%s", tempAccount.name);
		printf("������ı��������ݣ�0Ϊ��ͨ��1ΪVIP��2Ϊ����Ա��\n");
		scanf("%d", &tempAccount.character);
		struct Node* result = searchNodeByName(accountList, tempAccount.name);
		result->data.character = tempAccount.character;
		discount_character(result);
		saveToFileAccount("account_data.txt", accountList);
		printf("���ĳɹ���\n");
		printf("���˺ŵ��˻���Ϊ%s,��ʱ�����Ϊ%d\n", result->data.name, result->data.character);
		system("pause");
		break;
	case 6://�����ã�����ʱ���˻�������
		printf("�������\n");
		printList(accountList);
		system("pause");
		break;
	case 7:
		printRoomList(roomList);
		system("pause");
		break;
	case 0:
		printf("���˳���¼��\n");
		login_is_continue = 0;
		system("pause");
		break;
	default:
		printf("error\n");
		system("pause");
		break;
	}

}
// ��¼����潻��(�˿��˺�)
int loginedNormal(struct Node* Account) {
	int key;
	struct roomClass tempRoom;
	scanf("%d", &key);
	switch (key)
	{
	case 1:
		printf("\t���鿴���з��䡿\n");
		printFreeRooms(roomList);
		system("pause");
		break;
	case 2:
		printf("\t��������\n");
		printFreeRooms(roomList);
		printf("����������Ҫ���ķ���ķ����(����һ������):\n");
		scanf("%d", &tempRoom.number);
		openRoom(Account, tempRoom.number);
		saveToFileRoom("room_data.txt", roomList);
		saveToFileAccount("account_data.txt", accountList);
		system("pause");
		break;
	case 3:
		printf("\t���˷���\n");
		tempRoom.number = Account->data.room;
		quitRoom(Account, tempRoom.number);
		saveToFileAccount("account_data.txt", accountList);
		saveToFileRoom("room_data.txt", roomList);
		printf("���ķ����Ѹ��£�\n");
		look(Account);
		system("pause");
		break;
	case 4:
		printf("\t���鿴�ҵķ�����\n");
		look(Account);
		system("pause");
		break;
	case 5:
		printf("\t����ֵ��\n");
		printf("������Ҫ��ֵ�Ľ�\n");
		float moneyInput;
		scanf("%f", &moneyInput);
		if (moneyInput > 0)
		{
			Account->data.money += moneyInput;
			printf("��ֵ�ɹ�����ǰ���Ϊ��%f\n", Account->data.money);
		}
		else {
			printf("���������0�Ľ�\n");
		}
		saveToFileAccount("account_data.txt", accountList);
		system("pause");
		break;
	case 6:
		printf("����500Ԫ����Ϊvip\n");
		toVIP(Account);
		saveToFileAccount("account_data.txt", accountList);
		system("pause");
		break;
	case 0:
		printf("\t���˳���¼��\n");
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
// ע��ѡ��
int registerSelect() {
	int key;
	struct account tempAccount;
	scanf("%d", &key);
	switch (key)
	{
	case 1:
		printf("\t������Ա�˺�ע�᡿\n");
		printf("\t�������ȡ����Ȩ�޵�����\n");
		int password = 0;
		scanf("%d", &password);
		if (password == 123456)
		{
			printf("������ȷ!\n");
			tempAccount.discount = 10;
			tempAccount.money = 0;
			tempAccount.character = 2;
			tempAccount.room = 0;
			printf("�������û���:\n");
			scanf("%s", tempAccount.name);
			struct Node* result = searchNodeByName(accountList, tempAccount.name);
			if (result != NULL)
			{
				printf("�Ѿ�������ͬ�û������˺ţ�\n");
			}
			else
			{
				insertListByHead(accountList, tempAccount);
				saveToFileAccount("account_data.txt", accountList);
				printf("ע��ɹ���\n");
			}
		}
		else {
			printf("�������\n");
		}
		break;
	case 2:
		printf("\t����ͨ�˺�ע�᡿\n");
		printf("\t�������û���\n");
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
			printf("�Ѵ�����ͬ�û������˺�!\n");
		}
		else {
			insertListByHead(accountList, tempAccount);
			printf("��ע��ɹ���\n");
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
// ��¼
int login() {
	printf("�������û���\n");
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
		//����Ա��¼��֧
		if (result->data.character == 2)
		{
			printf("\t����¼�ɹ���\n");
			system("pause");
			login_is_continue = 1;
			while (login_is_continue) {
				system("cls");
				loginAdminMenu(result->data);
				loginedAdmin();
			}
		}
		//��ͨ/VIP�˺ŵ�¼��֧
		else {
			printf("\t����¼�ɹ���\n");
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
		printf("\t���Ҳ������˻���\n");
		system("pause");
	}
	return 0;
}
//��¼ע��
int loginRegister() {
	int key;
	scanf("%d", &key);
	switch (key)
	{
	case 0:
		printf("\t���˳��ɹ���\n");
		system("pause");
		exit(0);
		break;
	case 1:
		printf("\t����¼��\n");
		login();
		break;

	case 2:
		system("cls");
		printf("\t��ע�᡿\n");
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
	//��ʼ������
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
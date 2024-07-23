#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define WIDTH 15
#define HEIGHT 12

typedef struct {
	int x, y, ste;
}Ddong; //��

typedef struct {
	int x;
}Player; //�÷��̾�

typedef struct {
	int x, y, ste; // ste=state(����)
}Projectile; //����ü

typedef struct {
	int x, y, ste;
}Projectile2; //����ü2

typedef struct {
	int x, y, ste;
}Projectile3; //����ü3

Ddong ddong[WIDTH];
Player player;
Projectile projectile;
Projectile2 projectile2;
Projectile3 projectile3;

int level = 10;
int n = 0;
float money = 0;

void gotoxy(int x, int y) {
	COORD pos = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int isKeyDown(int key) {
	return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

void init() {
	for (int i = 0; i < WIDTH; i++) {
		ddong[i].ste = 0;
	}
	projectile.ste = 0;
	projectile2.ste = 0;
	projectile3.ste = 0;
	player.x = WIDTH / 2;
}

void Createddong() {
	for (int i = 0; i < WIDTH; i++) {
		if (ddong[i].ste == 0) {
			ddong[i].x = rand() % WIDTH;
			ddong[i].y = 1;
			ddong[i].ste = 1;
			return;
		}
	}
}

void Moveddong() {
	for (int i = 0; i < WIDTH; i++) {
		if (ddong[i].ste == 1) {
			ddong[i].y++;
		}
	}
}

void Removeddong() {
	for (int i = 0; i < WIDTH; i++) {
		if (ddong[i].y == HEIGHT + 1) {
			ddong[i].ste = 0;
		}
	}
}

void CreateProjectile() {
	if (level >= 0) {
		if (projectile.ste == 0) {
			projectile.x = player.x;
			projectile.y = HEIGHT;
			projectile.ste = 1;
		}
		if (level >= 5) {
			if (projectile2.ste == 0) {
				projectile2.x = player.x;
				projectile2.y = HEIGHT;
				projectile2.ste = 1;
			}
			if (level == 10) {
				if (projectile3.ste == 0) {
				projectile3.x = player.x;
				projectile3.y = HEIGHT;
				projectile3.ste = 1;
				}
			}
		}
	}
	return;
}

void MoveProjectile() {
	if (projectile.ste == 1) {
		projectile.y--;
	}
	if (projectile2.ste == 1) {
		projectile2.x--;
		projectile2.y--;
	}
	if (projectile3.ste == 1) {
		projectile3.x++;
		projectile3.y--;
	}
}

void RemoveProjectile() {
	if (projectile.y == 0) {
		projectile.ste = 0;
	}
	if ((projectile2.y == 0) || (projectile2.x < 0 || projectile2.x > WIDTH - 1)) {
		projectile2.ste = 0;
	}
	if ((projectile3.y == 0) || (projectile3.x < 0 || projectile3.x > WIDTH - 1)) {
		projectile3.ste = 0;
	}
}

void PrintMap() {
	system("cls");
	for (int i = 0; i < WIDTH; i++) {
		if (ddong[i].ste == 1) {
			gotoxy(ddong[i].x, ddong[i].y);
			printf("��");
		}
	}
	if (projectile.ste == 1) {
		gotoxy(projectile.x, projectile.y);
		printf("��");
	}
	if (projectile2.ste == 1) {
		gotoxy(projectile2.x, projectile2.y);
		printf("��");
	}
	if (projectile3.ste == 1) {
		gotoxy(projectile3.x, projectile3.y);
		printf("��");
	}

	gotoxy(player.x, HEIGHT);
	printf("��");

	gotoxy(0, HEIGHT + 1);
	for (int i = 0; i < WIDTH; i++) {
		printf("��");
	}
	printf("\n�� : %.1lf��", money);
}

void MovePlayer() {
	if (isKeyDown(VK_LEFT)) {
		player.x -= 1;
	}
	if (isKeyDown(VK_RIGHT)) {
		player.x += 1;
	}
	if (isKeyDown(VK_SPACE)) {
		CreateProjectile();
	}
	if (player.x < 0) {
		player.x = 0;
	}
	if (player.x > WIDTH - 1) {
		player.x = WIDTH - 1;
	}
}

int TouchedPlayer() {
	for (int i = 0; i < WIDTH; i++) {
		if ((ddong[i].y == HEIGHT) && (ddong[i].x == player.x)) {
			return 1;
		}
	}
	return 0;
}

void TouchedProjectile() {
	for (int i = 0; i < WIDTH; i++) {
		if ((ddong[i].x == projectile.x) && 
			(ddong[i].y == projectile.y + 1 || ddong[i].y == projectile.y)) {
			ddong[i].ste = 0;
			projectile.ste = 0;
		}
		if ((ddong[i].x == projectile2.x) && (ddong[i].y == projectile2.y)) {
			ddong[i].ste = 0;
			projectile2.ste = 0;
		}
		if ((ddong[i].x == projectile3.x) && (ddong[i].y == projectile3.y)) {
			ddong[i].ste = 0;
			projectile3.ste = 0;
		}
	}
}

void Upgrade() {
	int SucPer, per, opt = 0;
	float nMoney;
	while (true) {
		system("cls");
		if (level == 10) { // ������ 10�� �� 
			printf("�ְ����Դϴ�!");
			Sleep(1000);
			break;
		}
		else {
			SucPer = 100 - (10 * level); //1������ ���� ������ 10%�� ����
			nMoney = 5 * (level + 1); // 1������ ���� ������ 5���� ����
			per = rand() % 100 + 1; //1 ~ 100������ ���� ��
			printf("-----<��ȭ>-----\n\n");
			printf("��ȭ�� 10���� ������ �����̰� ������ �ö󰥼��� ����Ȯ���� �������ϴ�.\n");
			printf("���� ��ȭ�� 5����, 10�������� ȿ���� ��Ÿ���ϴ�.\n\n");
			printf("���� ���� : %d����\n", level);
			printf("��ȭ Ȯ�� : %d%%\n", SucPer);
			printf("��ȭ ��� : %.1lf��\n", nMoney);
			printf("������ : %.1lf��\n", money);
			printf("���ư��� : 1 ");
			printf("��ȭ�ϱ� : 2\n");
			printf("���� : ");
			scanf_s("%d", &opt);
			if (opt != 1 && opt != 2) printf("�߸� �Է��ϼ̽��ϴ�."); Sleep(1000);
			if (opt == 2) {
				if (money < nMoney) {
					printf("�������� �����մϴ�"); // �ʿ��� ����� �������� ���ڸ� ��
					Sleep(1000);
				}
				else {
				system("cls");
					printf("��ȭ��...");
					Sleep(2000);
					if (per <= SucPer) {
						system("cls");
						printf("�����߽��ϴ�!");
						money -= nMoney; //���� �����ݿ��� ��ȭ�� ����
						level++;
						Sleep(1500);
					}
					else {
						money -= nMoney; //���� �����ݿ��� ��ȭ�� ����
						system("cls");
						printf("�����߽��ϴ�!");
						Sleep(1500);
					}
				}
			}
			else if (opt == 1) break; //���ư��� �������� ��
		}
	}
	n = 0;
}

void ShowMenu() {
	while (n != 1 && n != 2 && n != 3) {
		system("cls");
		printf("-----<���� ����>-----\n\n");
		printf("�����ؼ� ���� ���� ����������!\n");
		printf("�ɼ��� �������ֽʽÿ�.\n");
		printf("���� ���� : 1\n");
		printf("��ȭ�ϱ� : 2\n");
		printf("���� ���� : 3\n");
		printf("���� ������ %.1lf��\n", money);
		printf("���� ���� : %d����\n", level);
		printf("���� : ");
		scanf_s("%d", &n);
		if (n != 1 && n != 2 && n != 3) {
			printf("�߸� �Է��ϼ̽��ϴ�."); 
			Sleep(1000);
		}
	}
}


int main() {
	int flag = 0;
	while (true) {
		init();
		ShowMenu();
		while (true) {
			if (n == 1) {
				printf("3�� �ڿ� �����մϴ�.");
				Sleep(3000);
				break;
			}
			if (n == 2) {
				Upgrade();
				ShowMenu();
			}
			if (n == 3) break;
		}
		if (n == 3) {
			system("cls");
			break;
		}
		while (true) {
			if (TouchedPlayer() == 1) break;
			Createddong();
			Moveddong();
			Removeddong();
			MoveProjectile();
			RemoveProjectile();
			MovePlayer();
			TouchedProjectile();
			PrintMap();
			Sleep(100);
			money += 0.2;
		}
		system("cls");
		n = 0;
	}
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define WIDTH 15
#define HEIGHT 12

typedef struct {
	int x, y, ste;
}Ddong; //똥

typedef struct {
	int x;
}Player; //플레이어

typedef struct {
	int x, y, ste; // ste=state(상태)
}Projectile; //투사체

typedef struct {
	int x, y, ste;
}Projectile2; //투사체2

typedef struct {
	int x, y, ste;
}Projectile3; //투사체3

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
			printf("▼");
		}
	}
	if (projectile.ste == 1) {
		gotoxy(projectile.x, projectile.y);
		printf("▲");
	}
	if (projectile2.ste == 1) {
		gotoxy(projectile2.x, projectile2.y);
		printf("▲");
	}
	if (projectile3.ste == 1) {
		gotoxy(projectile3.x, projectile3.y);
		printf("▲");
	}

	gotoxy(player.x, HEIGHT);
	printf("□");

	gotoxy(0, HEIGHT + 1);
	for (int i = 0; i < WIDTH; i++) {
		printf("■");
	}
	printf("\n돈 : %.1lf원", money);
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
		if (level == 10) { // 레벨이 10일 때 
			printf("최고레벨입니다!");
			Sleep(1000);
			break;
		}
		else {
			SucPer = 100 - (10 * level); //1레벨씩 오를 때마다 10%씩 감소
			nMoney = 5 * (level + 1); // 1레벨씩 오를 때마다 5원씩 증가
			per = rand() % 100 + 1; //1 ~ 100까지의 랜덤 수
			printf("-----<강화>-----\n\n");
			printf("강화는 10렙이 마지막 레벨이고 레벨이 올라갈수록 성공확률이 낮아집니다.\n");
			printf("또한 강화는 5레벨, 10레벨에서 효과가 나타납니다.\n\n");
			printf("현재 레벨 : %d레벨\n", level);
			printf("강화 확률 : %d%%\n", SucPer);
			printf("강화 비용 : %.1lf원\n", nMoney);
			printf("소지금 : %.1lf원\n", money);
			printf("돌아가기 : 1 ");
			printf("강화하기 : 2\n");
			printf("선택 : ");
			scanf_s("%d", &opt);
			if (opt != 1 && opt != 2) printf("잘못 입력하셨습니다."); Sleep(1000);
			if (opt == 2) {
				if (money < nMoney) {
					printf("소지금이 부족합니다"); // 필요한 돈모다 소지금이 모자를 때
					Sleep(1000);
				}
				else {
				system("cls");
					printf("강화중...");
					Sleep(2000);
					if (per <= SucPer) {
						system("cls");
						printf("성공했습니다!");
						money -= nMoney; //현재 소지금에서 강화돈 빼기
						level++;
						Sleep(1500);
					}
					else {
						money -= nMoney; //현재 소지금에서 강화돈 빼기
						system("cls");
						printf("실패했습니다!");
						Sleep(1500);
					}
				}
			}
			else if (opt == 1) break; //돌아가기 선택했을 때
		}
	}
	n = 0;
}

void ShowMenu() {
	while (n != 1 && n != 2 && n != 3) {
		system("cls");
		printf("-----<슈팅 게임>-----\n\n");
		printf("슈팅해서 돈을 벌고 강해지세요!\n");
		printf("옵션을 선택해주십시오.\n");
		printf("게임 시작 : 1\n");
		printf("강화하기 : 2\n");
		printf("게임 종료 : 3\n");
		printf("현재 소지금 %.1lf원\n", money);
		printf("현재 레벨 : %d레벨\n", level);
		printf("선택 : ");
		scanf_s("%d", &n);
		if (n != 1 && n != 2 && n != 3) {
			printf("잘못 입력하셨습니다."); 
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
				printf("3초 뒤에 시작합니다.");
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
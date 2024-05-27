#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> // 인터넷에서 찾은 헤더파일

int card_kind[4][13] = { // 카드 종류
	{101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113},
	{201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213},
	{301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313},
	{401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413}
}; // 스페이드 = 100, 다이아 = 200, 하트 = 300, 클로버 = 400, 컬러조커 = 777, 흑조커 = 666

int max_card = 10, total_card = 0, my_card[15], random_card, random_card_kind, random_card_number;

int max_HP = 5, HP = 5, STR = 1;

int clear = 0;

int wave = 1;

char answer;

enum ColorType { // 색깔 열거형 표시
	BLACK,  	 //0
	DarkBLUE,	 //1
	DarkGreen,	 //2
	DarkSkyBlue, //3
	DarkRed,  	 //4
	DarkPurple,	 //5
	DarkYellow,	 //6
	GRAY,		 //7
	DarkGray,	 //8
	BLUE,		 //9
	GREEN,		 //10
	SkyBlue,	 //11
	RED,		 //12
	PURPLE,		 //13
	YELLOW,		 //14
	WHITE		 //15
} COLOR;

void textcolor(unsigned short text, unsigned short back) { // \033[n;nm이 불편해서 인터넷에서 검색한 텍스트 색 변경 함수
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

void gotoxy(int x, int y) { // \033[y;xf가 불편하여 인터넷에서 검색한 터미널 좌표 이동 함수
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void print_side() { // 태두리 출력
	gotoxy(0, 0);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	for (int i = 1; i <= 58; i++) {
		gotoxy(0, i);
		printf("┃                                                                                                                                                                                                                ┃\n");
	}
	gotoxy(0, 59);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

void print_card(int i, int card) { // 카드 출력
	gotoxy(2 + i * 11, 51);
	textcolor(BLACK, WHITE);
	printf("┏━━━━━━━━┓ ");
	gotoxy(2 + i * 11, 52);
	printf("┃ ");
	if (card != 666 && card != 777) {
		switch (card / 100) {
		case 1:
			printf("♠");
			break;
		case 2:
			textcolor(RED, WHITE);
			printf("◆");
			textcolor(BLACK, WHITE);
			break;
		case 3:
			textcolor(RED, WHITE);
			printf("♥");
			textcolor(BLACK, WHITE);
			break;
		case 4:
			printf("♣");
			break;
		}
	}
	else if (card == 666) {
		printf("¡ ");
	}
	else if (card == 777) {
		textcolor(RED, WHITE);
		printf("¿");
		textcolor(BLACK, WHITE);
	}
	printf("     ┃ ");
	gotoxy(2 + i * 11, 53);
	printf("┃        ┃ ");
	gotoxy(2 + i * 11, 54);
	if (card != 666 && card != 777) {
		printf("┃   ");
		if (card / 100 == 2 || card / 100 == 3)
			textcolor(RED, WHITE);
		if (card % 100 == 1)
			printf(" A");
		else if (card % 100 == 11)
			printf(" J");
		else if (card % 100 == 12)
			printf(" Q");
		else if (card % 100 == 13)
			printf(" K");
		else
			printf("%2d", card % 100);
		textcolor(BLACK, WHITE);
		printf("   ┃ ");
	}
	else if (card == 666) {
		printf("┃  JOKER ┃ ");
	}
	else if (card == 777) {
		printf("┃  ");
		textcolor(RED, WHITE);
		printf("JOKER");
		textcolor(BLACK, WHITE);
		printf(" ┃ ");
	}
	gotoxy(2 + i * 11, 55);
	printf("┃        ┃ ");
	gotoxy(2 + i * 11, 56);
	printf("┃        ┃ ");
	gotoxy(2 + i * 11, 57);
	printf("┃        ┃ ");
	gotoxy(2 + i * 11, 58);
	printf("┗━━━━━━━━┛ ");
	textcolor(WHITE, BLACK);
}

void print_card_back(int i) { // 카드 뒷면 출력
	gotoxy(2 + i * 11, 51);
	printf("┏━━━━━━━━┓ ");
	gotoxy(2 + i * 11, 52);
	printf("┃        ┃ ");
	gotoxy(2 + i * 11, 53);
	printf("┃        ┃ ");
	gotoxy(2 + i * 11, 54);
	printf("┃    ?   ┃ ");
	gotoxy(2 + i * 11, 55);
	printf("┃        ┃ ");
	gotoxy(2 + i * 11, 56);
	printf("┃        ┃ ");
	gotoxy(2 + i * 11, 57);
	printf("┃        ┃ ");
	gotoxy(2 + i * 11, 58);
	printf("┗━━━━━━━━┛ ");
}

void print_chatwindow() { // 대화창 출력
	gotoxy(112, 44);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫");
	gotoxy(112, 45);
	printf("┃");
	gotoxy(112, 46);
	printf("┃");
	gotoxy(112, 47);
	printf("┃");
	gotoxy(112, 48);
	printf("┃");
	gotoxy(112, 49);
	printf("┃");
	gotoxy(112, 50);
	printf("┃");
	gotoxy(112, 51);
	printf("┃");
	gotoxy(112, 52);
	printf("┃");
	gotoxy(112, 53);
	printf("┃");
	gotoxy(112, 54);
	printf("┃");
	gotoxy(112, 55);
	printf("┃");
	gotoxy(112, 56);
	printf("┃");
	gotoxy(112, 57);
	printf("┃");
	gotoxy(112, 58);
	printf("┃");
	gotoxy(112, 59);
	printf("┻");
}

void clear_chatwindow() { // 대화창 초기화
	gotoxy(113, 45);
	printf("                                                                                                ");
	gotoxy(113, 46);
	printf("                                                                                                ");
	gotoxy(113, 47);
	printf("                                                                                                ");
	gotoxy(113, 48);
	printf("                                                                                                ");
	gotoxy(113, 49);
	printf("                                                                                                ");
	gotoxy(113, 50);
	printf("                                                                                                ");
	gotoxy(113, 51);
	printf("                                                                                                ");
	gotoxy(113, 52);
	printf("                                                                                                ");
	gotoxy(113, 53);
	printf("                                                                                                ");
	gotoxy(113, 54);
	printf("                                                                                                ");
	gotoxy(113, 55);
	printf("                                                                                                ");
	gotoxy(113, 56);
	printf("                                                                                                ");
	gotoxy(113, 57);
	printf("                                                                                                ");
	gotoxy(113, 58);
	printf("                                                                                                ");
	gotoxy(114, 45);
}

void print_status() { // HP, 공격력 표기
	gotoxy(3, 47);
	printf("체력 : %d / %d                      공격력 : %d", HP, max_HP, STR);
	gotoxy(3, 49);
	for (int i = 0; i < HP; i++) {
		textcolor(BLACK, RED);
		printf("┃     ");
	}
	if (max_HP - HP != 0)
		printf("┃");
	for (int i = 0; i < max_HP - HP; i++) {
		textcolor(BLACK, DarkGray);
		printf("     ┃");
	}
	if (max_HP - HP == 0)
		printf("┃");
	textcolor(WHITE, BLACK);
}

void get_card() { // 카드 획득
	while (1) {
		random_card_kind = ((rand() % 4) + 1) * 100;
		random_card_number = (rand() % 13) + 1;
		random_card = random_card_kind + random_card_number;
		for (int i = 0; i < total_card; i++) {
			if (my_card[i] == random_card) {
				continue;
			}
		}
		my_card[total_card] = random_card;
		total_card++;
		break;
	}
}

void delete_card(int num) { // 카드 제거
	for (int i = num - 1; i < total_card - 1; i++) {
		my_card[i] = my_card[i + 1];
	}
	my_card[total_card - 1] = 0;
	total_card--;
}

void print_UI() { // 전체 UI 출력
	print_side();
	for (int i = 0; i < total_card; i++) {
		print_card(i, my_card[i]);
	}
	for (int i = total_card; i < max_card; i++) {
		print_card_back(i);
	}
	print_chatwindow();
	print_status();
}

void use_card() { // 카드 사용
	clear_chatwindow();
	printf("카드를 사용하시겠습니까?(y/n) ");
	scanf(" %c", &answer);
	if (answer != 'y' && answer != 'Y') {
		return;
	}
	int first_card = 0, second_card = 0;
	clear = 0;
	clear_chatwindow();
	printf("카드 두 장의 번호를 입력하세요.(n n) ");
	gotoxy(114, 46);
	printf("카드 사용을 취소하기를 원하면 0 0을 입력하세요. ");
	scanf("%d %d", &first_card, &second_card);
	if (first_card == 0 && second_card == 0)
		return;
	else if (first_card == second_card || first_card <= 0 || second_card <= 0 || first_card > total_card || second_card > total_card) {
		clear_chatwindow();
		printf("잘못된 값을 입력하였습니다.");
		use_card();
	}
	if (clear == 0) {
		gotoxy(90, 25);
		textcolor(BLACK, WHITE);
		printf("┏━━━━━━━━┓ ┏━━━━━━━━┓ ");
		gotoxy(90, 26);
		printf("┃ ");
		if (my_card[first_card - 1] != 666 && my_card[first_card - 1] != 777) {
			switch (my_card[first_card - 1] / 100) {
			case 1:
				printf("♠");
				break;
			case 2:
				textcolor(RED, WHITE);
				printf("◆");
				textcolor(BLACK, WHITE);
				break;
			case 3:
				textcolor(RED, WHITE);
				printf("♥");
				textcolor(BLACK, WHITE);
				break;
			case 4:
				printf("♣");
				break;
			}
		}
		else if (my_card[first_card - 1] == 666) {
			printf("¡ ");
		}
		else if (my_card[first_card - 1] == 777) {
			textcolor(RED, WHITE);
			printf("¿");
			textcolor(BLACK, WHITE);
		}
		printf("     ┃ ");
		printf("┃ ");
		if (my_card[second_card - 1] != 666 && my_card[second_card - 1] != 777) {
			switch (my_card[second_card - 1] / 100) {
			case 1:
				printf("♠");
				break;
			case 2:
				textcolor(RED, WHITE);
				printf("◆");
				textcolor(BLACK, WHITE);
				break;
			case 3:
				textcolor(RED, WHITE);
				printf("♥");
				textcolor(BLACK, WHITE);
				break;
			case 4:
				printf("♣");
				break;
			}
		}
		else if (my_card[second_card - 1] == 666) {
			printf("¡ ");
		}
		else if (my_card[second_card - 1] == 777) {
			textcolor(RED, WHITE);
			printf("¿");
			textcolor(BLACK, WHITE);
		}
		printf("     ┃ ");
		gotoxy(90, 27);
		printf("┃        ┃ ┃        ┃ ");
		gotoxy(90, 28);
		if (my_card[first_card - 1] != 666 && my_card[first_card - 1] != 777) {
			printf("┃   ");
			if (my_card[first_card - 1] / 100 == 2 || my_card[first_card - 1] / 100 == 3)
				textcolor(RED, WHITE);
			if (my_card[first_card - 1] % 100 == 1)
				printf(" A");
			else if (my_card[first_card - 1] % 100 == 11)
				printf(" J");
			else if (my_card[first_card - 1] % 100 == 12)
				printf(" Q");
			else if (my_card[first_card - 1] % 100 == 13)
				printf(" K");
			else
				printf("%2d", my_card[first_card - 1] % 100);
			textcolor(BLACK, WHITE);
			printf("   ┃ ");
		}
		else if (my_card[first_card - 1] == 666) {
			printf("┃  JOKER ┃ ");
		}
		else if (my_card[first_card - 1] == 777) {
			printf("┃  ");
			textcolor(RED, WHITE);
			printf("JOKER");
			textcolor(BLACK, WHITE);
			printf(" ┃ ");
		}
		if (my_card[second_card - 1] != 666 && my_card[second_card - 1] != 777) {
			printf("┃   ");
			if (my_card[second_card - 1] / 100 == 2 || my_card[second_card - 1] / 100 == 3)
				textcolor(RED, WHITE);
			if (my_card[second_card - 1] % 100 == 1)
				printf(" A");
			else if (my_card[second_card - 1] % 100 == 11)
				printf(" J");
			else if (my_card[second_card - 1] % 100 == 12)
				printf(" Q");
			else if (my_card[second_card - 1] % 100 == 13)
				printf(" K");
			else
				printf("%2d", my_card[second_card - 1] % 100);
			textcolor(BLACK, WHITE);
			printf("   ┃ ");
		}
		else if (my_card[second_card - 1] == 666) {
			printf("┃  JOKER ┃ ");
		}
		else if (my_card[second_card - 1] == 777) {
			printf("┃  ");
			textcolor(RED, WHITE);
			printf("JOKER");
			textcolor(BLACK, WHITE);
			printf(" ┃ ");
		}
		gotoxy(90, 29);
		printf("┃        ┃ ┃        ┃ ");
		gotoxy(90, 30);
		printf("┃        ┃ ┃        ┃ ");
		gotoxy(90, 31);
		printf("┃        ┃ ┃        ┃ ");
		gotoxy(90, 32);
		printf("┗━━━━━━━━┛ ┗━━━━━━━━┛ ");
		textcolor(WHITE, BLACK);
		clear++;
	}
	if (my_card[first_card - 1] % 100 == my_card[second_card - 1] % 100 || my_card[first_card - 1] == 777 || my_card[second_card - 1] == 777) {
		if (my_card[first_card - 1] / 100 == 1 || my_card[first_card - 1] / 100 == 4) {
			switch (my_card[first_card - 1] % 100) {
			case 77:
				max_HP += 2;
				break;
			case 66:
				max_card++;
				STR *= 2;
				break;
			case 1: case 11: case 12: case 13:
				STR += 2;
				break;
			default:
				STR++;
				break;
			}
		}
		else {
			switch (my_card[first_card - 1] % 100) {
			case 77:
				max_HP += 2;
				break;
			case 66:
				max_card++;
				STR *= 2;
				break;
			case 1: case 11: case 12: case 13:
				HP += 2;
				if (HP > max_HP) {
					HP = max_HP;
				}
				break;
			default:
				HP++;
				if (HP > max_HP) {
					HP = max_HP;
				}
				break;
			}
		}
		if (my_card[second_card - 1] / 100 == 1 || my_card[second_card - 1] / 100 == 4) {
			switch (my_card[second_card - 1] % 100) {
			case 77:
				max_HP += 2;
				break;
			case 66:
				max_card++;
				STR *= 2;
				break;
			case 1: case 11: case 12: case 13:
				STR += 2;
				break;
			default:
				STR++;
				break;
			}
		}
		else {
			switch (my_card[second_card - 1] % 100) {
			case 77:
				max_HP += 2;
				break;
			case 66:
				max_card++;
				STR *= 2;
				break;
			case 1: case 11: case 12: case 13:
				HP += 2;
				if (HP > max_HP) {
					HP = max_HP;
				}
				break;
			default:
				HP++;
				if (HP > max_HP) {
					HP = max_HP;
				}
				break;
			}
		}
		delete_card(first_card);
		if (first_card > second_card) {
			delete_card(second_card);
		}
		else {
			delete_card(second_card - 1);
		}
		clear_chatwindow();
		printf("스탯이 변경됩니다.");
		Sleep(2000);
		print_UI();
		Sleep(2000);
	}
	else {
		clear_chatwindow();
		printf("올바른 카드가 아닙니다.");
		Sleep(2000);
		print_UI();
	}
}

void print_chest() { // 상자 출력
	gotoxy(95, 22);
	printf("         __________");
	gotoxy(95, 23);
	printf("        /\\____;;___\\");
	gotoxy(95, 24);
	printf("       | /         /");
	gotoxy(95, 25);
	printf("       `. ())oo() .");
	gotoxy(95, 26);
	printf("        |\\(%%()*^^()^\\");
	gotoxy(95, 27);
	printf("       %%| |-%%-------|");
	gotoxy(95, 28);
	printf("      %% \\ | %%  ))   |");
	gotoxy(95, 29);
	printf("      %%  \\|%%________|");
	gotoxy(95, 30);
	printf("       %%%%%%%%");
}

void chest() { // 상자
	print_chest();
	clear_chatwindow();
	printf("당신은 신비로운 상자를 발겼했습니다.");
	gotoxy(114, 46);
	printf("\"열어볼까?\" (y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		if (rand() % 10 < 8) {
			clear_chatwindow();
			get_card();
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			printf("카드 한 장을 획득했습니다.");
			Sleep(2000);
			clear_chatwindow();
		}
		else {
			clear_chatwindow();
			HP--;
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			printf("상자로 둔갑한 미믹을 마주쳐서 체력이 1 감소했습니다.");
			Sleep(2000);
			clear_chatwindow();
		}
	}
	else {
		print_UI();
		clear_chatwindow();
		printf("\"저 상자는 분명 미믹일거야.\"");
		Sleep(2000);
		clear_chatwindow();
	}
}

void print_heal_wather() { // 생명의 샘 출력
	gotoxy(75, 15);
	printf("               ,,-  ,             ,,,  -");
	gotoxy(75, 16);
	printf("         .,   .--~--~.          ,---, ---  ");
	gotoxy(75, 17);
	printf("        .,,,- ,-~~:-~,,--- ---,------,-~-,.");
	gotoxy(75, 18);
	printf("       ---------~::~-,-~~~,-~--~-~~----~--~ ");
	gotoxy(75, 19);
	printf("      ~~-----~~~~~-");
	textcolor(SkyBlue, BLACK);
	printf(".............,,..,");
	textcolor(WHITE, BLACK);
	printf("--~--~-");
	gotoxy(75, 20);
	printf("     ,-------");
	textcolor(SkyBlue, BLACK);
	printf(",.........................,");
	textcolor(WHITE, BLACK);
	printf("-~:: ..");
	gotoxy(75, 21);
	printf("   ,~~--~--");
	textcolor(SkyBlue, BLACK);
	printf(".............................");
	textcolor(WHITE, BLACK);
	printf("~..,,,---");
	gotoxy(75, 22);
	printf("  ,~~~~~~--");
	textcolor(SkyBlue, BLACK);
	printf("..............................");
	textcolor(WHITE, BLACK);
	printf("------~:");
	gotoxy(75, 23);
	printf("  .--,,,--");
	textcolor(SkyBlue, BLACK);
	printf(",..............................,");
	textcolor(WHITE, BLACK);
	printf("-------");
	gotoxy(75, 24);
	printf("   ,,-----");
	textcolor(SkyBlue, BLACK);
	printf("................................");
	textcolor(WHITE, BLACK);
	printf("-~:----");
	gotoxy(75, 25);
	printf(" ,----~---");
	textcolor(SkyBlue, BLACK);
	printf(",..........................,,,,,,,");
	textcolor(WHITE, BLACK);
	printf("----,");
	gotoxy(75, 26);
	printf(" ------~~~-");
	textcolor(SkyBlue, BLACK);
	printf(".........................,,,,,,,");
	textcolor(WHITE, BLACK);
	printf("-----");
	gotoxy(75, 27);
	printf(" ,---,-----");
	textcolor(SkyBlue, BLACK);
	printf(",,...................,");
	textcolor(WHITE, BLACK);
	printf("------");
	textcolor(SkyBlue, BLACK);
	printf(",,,");
	textcolor(WHITE, BLACK);
	printf("---~~-");
	gotoxy(75, 28);
	printf("  ------------");
	textcolor(SkyBlue, BLACK);
	printf(",................,,");
	textcolor(WHITE, BLACK);
	printf("-~~-----------.");
	gotoxy(75, 29);
	printf("  ----------~--.,-----");
	textcolor(SkyBlue, BLACK);
	printf(",......,,,,");
	textcolor(WHITE, BLACK);
	printf("-~~-------~~-");
	gotoxy(75, 30);
	printf("  ,-----------~---------");
	textcolor(SkyBlue, BLACK);
	printf(",..,,,,");
	textcolor(WHITE, BLACK);
	printf("--~~~----~~~~~-");
	gotoxy(75, 31);
	printf("  ,----~~-~-~----~------");
	textcolor(SkyBlue, BLACK);
	printf(",.,,");
	textcolor(WHITE, BLACK);
	printf("-,-~-~~:--~-~~~~~");
	gotoxy(75, 32);
	printf("  .,,,,-~~-, -~-~~~~~~-,------~:~:::,");
	gotoxy(75, 33);
	printf("                  ..,~---~~~~::~,..");
}

void heal_wather() { // 생명의 샘
	print_heal_wather();
	clear_chatwindow();
	printf("당신은 생명의 기운이 느껴지는 샘물을 발겼했습니다.");
	gotoxy(114, 46);
	printf("\"잠시 쉬었다가 출발하자.\"");
	int heal = (rand() % 3) + 1;
	HP += heal;
	if (HP > max_HP) {
		HP = max_HP;
	}
	Sleep(2000);
	print_UI();
	clear_chatwindow();
	printf("체력이 %d만큼 회복되었습니다.", heal);
	Sleep(2000);
	print_UI();
}

void print_black_merchant() { // 암상인 출력
	gotoxy(80, 2);
	printf("          *@@@@@@@@@@@@@@@@@@@@-");
	gotoxy(80, 3);
	printf("        ,!$#$$$$$$$$$$$$$$$$$$#*!.");
	gotoxy(80, 4);
	printf("        ~@#==*;;;;;;;;;;;;;;;*=@@,");
	gotoxy(80, 5);
	printf("        ~@#==*;;;;;;;;;;;;;;;!=@@,");
	gotoxy(80, 6);
	printf("        ~@#==*;;;;;;;;;;;;;;;*=@@,");
	gotoxy(80, 7);
	printf("        ~@#==*;;;;;;;;;;;;;;;*=@@,");
	gotoxy(80, 8);
	printf("        ~@$***!;;;;;;;;;;;;;;*=@@,");
	gotoxy(80, 9);
	printf("        ~@$==********!!!!*****=@@,");
	gotoxy(80, 10);
	printf("        ~@#====================@@,");
	gotoxy(80, 11);
	printf("        ~@@@@@#################@@,");
	gotoxy(80, 12);
	printf("        ~@#======================;-");
	gotoxy(80, 13);
	printf("        ~@=;::::::::::::::::::::;#=.");
	gotoxy(80, 14);
	printf("       @@@*::::::::::::::::::::::#$!!!,");
	gotoxy(80, 15);
	printf("  .....@@@=;::::::::::::::::::::;#@@@@:....");
	gotoxy(80, 16);
	printf("  :=***$$$=**********************=$$$$=****.");
	gotoxy(80, 17);
	printf("-~=####===**=====================**=*=#####:-");
	gotoxy(80, 18);
	printf("$$$=====*************===============*====$$$#");
	gotoxy(80, 19);
	printf("@@#####$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$#@@");
	gotoxy(80, 20);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#@@");
	gotoxy(80, 21);
	printf("~::::!@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#~~~~~");
	gotoxy(80, 22);
	printf("     ~@@####@@$#@@@@@@@@@@@@@#$@@@####@#");
	gotoxy(80, 23);
	printf("     ~@=*!!*#@~!@@@@@@@@@@@@@*~#@**===#$");
	gotoxy(80, 24);
	printf("     ~@=!;;;#@:*@@@@@@@@@@@@@=;#@;;!**#$");
	gotoxy(80, 25);
	printf("     ~@=*!;;#@#@@@@@@@@@@@@@@@#@@;;!**#$");
	gotoxy(80, 26);
	printf("     ~@=*!;;#@@@@*;@@@@@@@;*@@@@@;;!**#$");
	gotoxy(80, 27);
	printf("     -#=*!;;#@@@@:,#######-:@@@@#;;!**#$");
	gotoxy(80, 28);
	printf("     .~#=*!!*=@@@==:::::::*=@@@=*!!*=#!-");
	gotoxy(80, 29);
	printf("       @#=*!;;@@@@@~~~~~~~@@@@@;;!*===-");
	gotoxy(80, 30);
	printf("       @@@$*;;@#$#@$######@#$#@!;!=#!,");
	gotoxy(80, 31);
	printf("     .:$==$$==@#=$#######$#$=#@=*=$=:");
	gotoxy(80, 32);
	printf("     ~@!;:*#@@@#=============#@@@@$;~");
	gotoxy(80, 33);
	printf("   -;!=*=$*!!*@#==**********=#@******!,");
	gotoxy(80, 34);
	printf("   ;@$*!=#$!!!@#==***********$#!!!**$#;,");
	gotoxy(80, 35);
	printf("   ;@$*!**$@@@@#==***********==#@=*!*=#$");
	gotoxy(80, 36);
	printf("   ;@$****=####$$************==@@*!!**#$");
	gotoxy(80, 37);
	printf("   ;@$*!*******$@*!*==*******==@@*!!**#$");
	gotoxy(80, 38);
	printf(" .!$=*!!**!!!!*$@=*!!**=******==$#$***#$");
	gotoxy(80, 39);
	printf(" .*$**!!*!!!!!!=@=*;!**==******==@#***$$");
	gotoxy(80, 40);
	printf(" .*$**!!*!!!!!!=@$*;;;!********==@#****=@!");
	gotoxy(80, 41);
	printf(" .*$*!!!!!!!!!!=##$!;;!!***=***==@#**!*=@;");
	gotoxy(80, 42);
	printf(" .*$*!!!!!*******#@!;;;;***=***==@#*!!*=@;");
	gotoxy(80, 43);
	printf("**=**!!!!!!!!*$##@@*!;;;!!*****$#@@$*!**==*,");
	gotoxy(80, 44);
	printf("@#=*!!!!!!!!!*@@@@@**;;;;!*==**");
	gotoxy(80, 45);
	printf("@#=*!!!!!!=###===#@**;;;;!*==**");
	gotoxy(80, 46);
	printf("@@=*!!!**=#@@@*==#@=*!!;!;=====");
	gotoxy(80, 47);
	printf("@@=*!!!#@@@@@@@@@@@@#**!**@@#$$");
	gotoxy(80, 48);
	printf("@@=***==;;;!@@@@@*;;!$*;!!@@@##");
	gotoxy(80, 49);
	printf("@@=**=#;    @@@@@-  ,@=!;!@@@@@");
}

void black_merchant() { // 암상인 조우
	print_black_merchant();
	clear_chatwindow();
	printf("암상인이 나타났습니다.");
	gotoxy(114, 46);
	printf("\"너의 공격력을 5 올려줄테니, 나에게 너의 최대 체력을 1 주겠나?\"");
	gotoxy(114, 47);
	printf("암상인의 제안을 수락하시겠습니까?(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("\"잘 생각했다.....\"");
		max_HP--;
		STR += 5;
		Sleep(2000);
		print_UI();
		clear_chatwindow();
		printf("스탯이 변경되었습니다.");
		Sleep(2000);
		clear_chatwindow();
	}
	else {
		clear_chatwindow();
		printf("\"아쉽게됐군.....\"");
		Sleep(2000);
		print_UI();
	}
}

void print_change_card1() { // 낯선 사람 1 출력
	gotoxy(80, 10);
	printf("    .*\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"*.");
	gotoxy(80, 11);
	printf("   :                          ;");
	gotoxy(80, 12);
	printf("   :                          ;");
	gotoxy(80, 13);
	printf("   :  ......................  ;");
	gotoxy(80, 14);
	printf("   : :                      ; ;");
	gotoxy(80, 15);
	printf("   :_:                      ;_;");
	gotoxy(80, 16);
	printf("  /  :  __...--------...__  ;  \\");
	gotoxy(80, 17);
	printf(" /   :\"'  .*\"*-.  .-*\"*.  '\";   \\");
	gotoxy(80, 18);
	printf(":    ;   /      ;:      \\   :    ;");
	gotoxy(80, 19);
	printf("!    !  ;    *  !!  *    :  !    !");
	gotoxy(80, 20);
	printf(";   ;   :     .'  '.     ;   ;   :");
	gotoxy(80, 21);
	printf(":  .'    '-.-'      '-.-'    '.  ;");
	gotoxy(80, 22);
	printf("'-\"\\                          /\"-'");
	gotoxy(80, 23);
	printf("    '.                      .'");
	gotoxy(80, 24);
	printf("      *,      '-__-'      ,*");
	gotoxy(80, 25);
	printf("      /.'-_            _-' .\\");
	gotoxy(80, 26);
	printf("     /  \"-_\"*-.____.-*\" _-\"  \\");
	gotoxy(80, 27);
	printf("    /      '-_  /'\\  _-'      \\");
	gotoxy(80, 28);
	printf("   :    :   __'\" | \"'__   ;    ;");
	gotoxy(80, 29);
	printf("   |.--.;  |\\/|  |  |\\/|  :.--.|");
	gotoxy(80, 30);
	printf("   (   ()  |__|  |  |__|  ()   )");
	gotoxy(80, 31);
	printf("    '--^_        |        _^--'");
	gotoxy(80, 32);
	printf("       | \"'*--.._I_..--*'\" |");
	gotoxy(80, 33);
	printf("       | __..._  | _..._   |");
	gotoxy(80, 34);
	printf("      .'\"      `\"'\"     ''\"'.");
	gotoxy(80, 35);
	printf("      \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"");
}

void print_change_card2() { // 낯선 사람 2 출력
	gotoxy(80, 10);
	printf("             .-\"\"-.");
	gotoxy(80, 11);
	printf("          _.->    <-._");
	gotoxy(80, 12);
	printf("       .-\"   '-__-'   \"-.");
	gotoxy(80, 13);
	printf("     ,\"                  \",");
	gotoxy(80, 14);
	printf("   .'                      ',");
	gotoxy(80, 15);
	printf("  /    ___...------...___    \\");
	gotoxy(80, 16);
	printf(" /_.-*\"__...--------...__\"*-._\\");
	gotoxy(80, 17);
	printf(":_.-*\"'  .*\"*-.  .-*\"*.  '\"*-._;");
	gotoxy(80, 18);
	printf(";       /      ;:      \\       :");
	gotoxy(80, 19);
	printf(";      ;    *  !!  *    :      :");
	gotoxy(80, 20);
	printf(":      :     .'  '.     ;      ;");
	gotoxy(80, 21);
	printf(" \\      '-.-'      '-.-'      /");
	gotoxy(80, 22);
	printf("  \\                          /");
	gotoxy(80, 23);
	printf("   '.                      .'");
	gotoxy(80, 24);
	printf("     *,      '-__-'      ,*");
	gotoxy(80, 25);
	printf("     /.'-_            _-'.'\\");
	gotoxy(80, 26);
	printf("    /  \"-_\"*-.____.-*\"_-\"   \\");
	gotoxy(80, 27);
	printf("   /      '\"*-.___.-*'       \\");
	gotoxy(80, 28);
	printf("  :    :        |        ;    ;");
	gotoxy(80, 29);
	printf("  |.--.;       *|        :.--.|");
	gotoxy(80, 30);
	printf("  (   ()        |        ()   )");
	gotoxy(80, 31);
	printf("   '--^_       *|        _^--'");
	gotoxy(80, 32);
	printf("      | \"'*--.._I_..--*'\" |");
	gotoxy(80, 33);
	printf("      | __..._  | _..._   |");
	gotoxy(80, 34);
	printf("     .'\"      `\"'\"     ''\"'.");
	gotoxy(80, 35);
	printf("     \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"");
}

void print_change_card3() { // 낯선 사람 3 출력
	gotoxy(75, 10);
	printf("                       _.-**-._");
	gotoxy(75, 11);
	printf("                    _,(        ),_");
	gotoxy(75, 12);
	printf("                 .-\"   '-^----'   \"-.");
	gotoxy(75, 13);
	printf("              .-'                    '-.");
	gotoxy(75, 14);
	printf("            .'                          '.");
	gotoxy(75, 15);
	printf("          .'    __.--**'\"\"\"\"\"\"'**--.__    '.");
	gotoxy(75, 16);
	printf("         /_.-*\"'__.--**'\"\"\"\"\"\"'**--.__'\"*-._\\");
	gotoxy(75, 17);
	printf("        /_..-*\"'   .-*\"*-.  .-*\"*-.   '\"*-.._\\");
	gotoxy(75, 18);
	printf("       :          /       ;:       \\          ;");
	gotoxy(75, 19);
	printf("       :         :     *  !!  *     :         ;");
	gotoxy(75, 20);
	printf("        \\        '.     .'  '.     .'        /");
	gotoxy(75, 21);
	printf("         \\         '-.-'      '-.-'         /");
	gotoxy(75, 22);
	printf("      .-*''.                              .'-.");
	gotoxy(75, 23);
	printf("   .-'      '.                          .'    '.");
	gotoxy(75, 24);
	printf("  :           '-.        _.._        .-'        '._");
	gotoxy(75, 25);
	printf(" ;\"*-._          '-._  --___ `   _.-'        _.*'  '*.");
	gotoxy(75, 26);
	printf(":      '.            `\"*-.__.-*\"`           (        :");
	gotoxy(75, 27);
	printf(" ;      ;                 *|                 '-.     ;");
	gotoxy(75, 28);
	printf("  '---*'                   |                    \"\"--'");
	gotoxy(75, 29);
	printf("   :                      *|                      :");
	gotoxy(75, 30);
	printf("   '.                      |                     .'");
	gotoxy(75, 31);
	printf("     '.._                 *|        ____----.._-'");
	gotoxy(75, 32);
	printf("      \\  \"\"\"----_____------'-----\"\"\"         /");
	gotoxy(75, 33);
	printf("       \\  __..-------.._        ___..---._  /");
	gotoxy(75, 34);
	printf("       :'\"              '-..--''          \"'; ");
	gotoxy(75, 35);
	printf("        '\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"' '\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"'");
}

void print_change_card4() { // 낯선 사람 4 출력
	gotoxy(80, 10);
	printf("          _.-*'\"\"'*-._");
	gotoxy(80, 11);
	printf("       .-\"            \"-.");
	gotoxy(80, 12);
	printf("     ,\"                  \",");
	gotoxy(80, 13);
	printf("   .'      _.-.--.-._      ',");
	gotoxy(80, 14);
	printf("  /     .-'.-\"    \"-.'-.     \\");
	gotoxy(80, 15);
	printf(" /     /  /\"'-.  .-'\"\\  \\     \\");
	gotoxy(80, 16);
	printf(":     :  :     ;:     ;  ;     ;");
	gotoxy(80, 17);
	printf(";     :  ; *   !! *   :  ;     :");
	gotoxy(80, 18);
	printf(";      ; :   .'  '.   ; :      :");
	gotoxy(80, 19);
	printf(":       \\ \\-'      '-/ /       ;");
	gotoxy(80, 20);
	printf(" \\       '.'-_    _-'.'       /");
	gotoxy(80, 21);
	printf("  \\        '*-\"-+\"-*'        /");
	gotoxy(80, 22);
	printf("   '.          /|          .'");
	gotoxy(80, 23);
	printf("     *,       / |        ,*");
	gotoxy(80, 24);
	printf("     / '-_            _-'  \\");
	gotoxy(80, 25);
	printf("    /     \"*-.____.-*\"      \\");
	gotoxy(80, 26);
	printf("   /            |            \\");
	gotoxy(80, 27);
	printf("  :    :        |        ;    ;");
	gotoxy(80, 28);
	printf("  |.--.;        |        :.--.|");
	gotoxy(80, 29);
	printf("  (   ()        |        ()   )");
	gotoxy(80, 30);
	printf("   '--^_        |        _^--'");
	gotoxy(80, 31);
	printf("      | \"'*--.._I_..--*'\" |");
	gotoxy(80, 32);
	printf("      | __..._  | _..._   |");
	gotoxy(80, 33);
	printf("     .'\"      `\"'\"     ''\"'.");
	gotoxy(80, 34);
	printf("     \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"");
}

void change_card() { // 카드 교환
	int print = rand() % 4 + 1;
	switch (print)
	{
	case 1:
		print_change_card1();
		break;
	case 2:
		print_change_card2();
		break;
	case 3:
		print_change_card3();
		break;
	case 4:
		print_change_card4();
		break;
	}
	clear_chatwindow();
	printf("당신처럼 던전에 있는 낯선 사람과 만났습니다.");
	gotoxy(114, 46);
	printf("\"우리 카드를 한 장씩 바꾸지 않을래?\"");
	gotoxy(114, 47);
	printf("낯선 사람의 제안을 수락하시겠습니까?(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("\"제발 내가 필요한 카드...!\"");
		gotoxy(114, 46);
		printf("바꿀 카드 한 장을 고르세요.");
		int pick;
		scanf("%d", &pick);
		delete_card(pick);
		get_card();
		Sleep(2000);
		print_UI();
		clear_chatwindow();
		printf("카드를 교환했습니다.");
		Sleep(2000);
		print_UI();
	}
	else {
		clear_chatwindow();
		printf("\"그럼 다음에는 던전 밖에서 보자고.\"");
		Sleep(2000);
		print_UI();
	}
}

void print_magician() { // 마술사 출력
	gotoxy(80, 10);
	printf("                   ____");
	gotoxy(80, 11);
	printf("                  .'* *.'");
	gotoxy(80, 12);
	printf("               __/_*_*(_");
	gotoxy(80, 13);
	printf("              / _______ \\");
	gotoxy(80, 14);
	printf("             _\\_)/___\\(_/_ ");
	gotoxy(80, 15);
	printf("            / _((\\-  -/))_ \\");
	gotoxy(80, 16);
	printf("            \\ \\())(-)(()/ /");
	gotoxy(80, 17);
	printf("             ' \\(((()))/ '");
	gotoxy(80, 18);
	printf("            / ' \\)).))/ ' \\");
	gotoxy(80, 19);
	printf("           / _ \\ - | - /_  \\");
	gotoxy(80, 20);
	printf("          (   ( .;''';. .'  )");
	gotoxy(80, 21);
	printf("          _\\\"__ /    )\\ __\"/_");
	gotoxy(80, 22);
	printf("            \\/  \\   ' /  \\/");
	gotoxy(80, 23);
	printf("             .'  '...' ' )");
	gotoxy(80, 24);
	printf("              / /  |  \\ \\");
	gotoxy(80, 25);
	printf("             / .   .   . \\");
	gotoxy(80, 26);
	printf("            /   .     .   \\");
	gotoxy(80, 27);
	printf("           /   /   |   \\   \\");
	gotoxy(80, 28);
	printf("         .'   /    b    '.  '.");
	gotoxy(80, 29);
	printf("     _.-'    /     Bb     '-. '-._ ");
	gotoxy(80, 30);
	printf(" _.-'       |      BBb       '-.  '-. ");
	gotoxy(80, 31);
	printf("(________mrf\\____.dBBBb.________)____)");
}

void magician() { // 마술사 조우
	print_magician();
	clear_chatwindow();
	printf("마술사가 나타났습니다.");
	gotoxy(114, 46);
	printf("\"내가 너의 카드 색을 바꿔줄까?\"");
	gotoxy(114, 47);
	printf("마술사의 제안을 수락하시겠습니까?(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("\"좋아, 카드 한 장 골라봐.\" ");
		int pick;
		scanf("%d", &pick);
		clear_chatwindow();
		printf("\"그럼, 내 마술 실력을 잘 보라고...!\"");
		if (my_card[pick - 1] == 666) {
			my_card[pick - 1] += 111;
		}
		else if (my_card[pick - 1] == 777) {
			my_card[pick - 1] -= 111;
		}
		else {
			my_card[pick - 1] += 200;
		}

		if (my_card[pick - 1] > 500 && (my_card[pick - 1] != 666 && my_card[pick - 1] != 777)) {
			my_card[pick - 1] -= 400;
		}
		Sleep(2000);
		print_UI();
		clear_chatwindow();
		printf("카드 색이 변경되었습니다.");
		Sleep(2000);
		clear_chatwindow();
	}
	else {
		clear_chatwindow();
		printf("\"다음 기회에 보자고.\"");
		Sleep(2000);
		print_UI();
	}
}

void print_thief() { // 도둑 출력
	gotoxy(80, 8);
	printf("                       ..,,");
	gotoxy(80, 9);
	printf("                     ;***===!");
	gotoxy(80, 10);
	printf("                   .!****====*");
	gotoxy(80, 11);
	printf("                   ;*****=====!");
	gotoxy(80, 12);
	printf("                  .******======.");
	gotoxy(80, 13);
	printf("                  ;******======!");
	gotoxy(80, 14);
	printf("                  ;******======!");
	gotoxy(80, 15);
	printf("                 ;!******=======!");
	gotoxy(80, 16);
	printf("                .********========,");
	gotoxy(80, 17);
	printf("                .********========.");
	gotoxy(80, 18);
	printf("                  =******=======");
	gotoxy(80, 19);
	printf("                  *=;  :==:  ;=*");
	gotoxy(80, 20);
	printf("                  .==**=~~=**==.");
	gotoxy(80, 21);
	printf("                    ~~~.  .~~~");
	gotoxy(80, 22);
	printf("                      .~~~~.");
	gotoxy(80, 23);
	printf("                     .=!!!!=");
	gotoxy(80, 24);
	printf("                     ,=    =,");
	gotoxy(80, 25);
	printf("                     .=-  -=.");
	gotoxy(80, 26);
	printf("                     ~====~");
	gotoxy(80, 27);
	printf("                    ~; ~**~ ;-");
	gotoxy(80, 28);
	printf("                  ,.!=$,,,,$=!,.");
	gotoxy(80, 29);
	printf("                !================!");
	gotoxy(80, 30);
	printf("             !======================!");
	gotoxy(80, 31);
	printf("            *========================*");
	gotoxy(80, 32);
	printf("           .==========================.");
	gotoxy(80, 33);
	printf("           ,==========================-");
	gotoxy(80, 34);
	printf("           $==========================$");
	gotoxy(80, 35);
	printf("          ,============================,");
	gotoxy(80, 36);
	printf("          .-~~~--~~--~~--~~--~~--~~~-~~");
}

void thief() { // 도둑 조우
	print_thief();
	clear_chatwindow();
	printf("도둑이 나타났습니다.");
	gotoxy(114, 46);
	printf("\"이 카드는 좋은 곳에 써주지.\"");
	delete_card(rand() % (total_card + 1));
	Sleep(2000);
	print_UI();
	clear_chatwindow();
	printf("카드 한 장을 빼앗겼습니다.");
	Sleep(2000);
	clear_chatwindow();
}

void print_fire() { // 모닥불 출력
	gotoxy(75, 12);
	printf(".___________________________________________________________________________.");
	gotoxy(75, 13);
	printf("|                                                                           |");
	gotoxy(75, 14);
	printf("|___________________________________________________________________________|");
	gotoxy(75, 15);
	printf("  |     !           |           |           |           |           |     |");
	gotoxy(75, 16);
	printf("  |_____|__,________|___________|______.____}__,________}___________|_____|");
	gotoxy(75, 17);
	printf("  |         |  \\   \\   \\   \\   \\    |   |    /   /   /   /   /  |         |");
	gotoxy(75, 18);
	printf("  |_________|___\\_,_\\___\\___\\.__|___|___|___|___/___/___/___/___|_________|");
	gotoxy(75, 19);
	printf("  |     |   |      |     \\/ ,\".). ',     \\/. ',          |      |   |     |");
	gotoxy(75, 20);
	printf("  |_____|___|      |. ' ,'|// / (/ ,.  ' ,\\(   / ,       |      |___|_____|");
	gotoxy(75, 21);
	printf("  |         |     ,|  '|\\/ \\|  \\\\,' ,'.' ||  \\\\,' .'    ,|  '   |         |");
	gotoxy(75, 22);
	printf("  |_._______|   \" ,|' .| \\_ |\\/ |#\\_/#| /_|\\_ |#\\_/,) ',.|,'    |_________|");
	gotoxy(75, 23);
	printf("  |     |   |   #|(,'  )  \\\\\\#\\ \\##/  ||/ \\#\\  \\###/\\ \\/ \\/.',  |   |     |");
	gotoxy(75, 24);
	printf("  |_____|__,|   || ) | \\ |/ /#/ |#( \\|\\\\|  |#/ /##(  )|  \\\\'/   |___|_____|");
	gotoxy(75, 25);
	printf("  |         |    \\ |.\\\\ |\\_/#| /#)|##\\ \\\\_/#| |######\\ \\\\/#|    |         |");
	gotoxy(75, 26);
	printf("  |_________|    /\\\\_/# |#\\##/# ####@##### ### ### #@#\\ /#/\\    |_____.___|");
	gotoxy(75, 27);
	printf("  |     |   |   /  ##/#  ##\\/#@####@@###@###\\/#@####@@#Y### \\   |   |     |");
	gotoxy(75, 28);
	printf("  |___._|___|  / :Y##@@##@##@@###@@@###@##@@###@@@###@####:  \\  |___|_____|");
	gotoxy(75, 29);
	printf("  |         | / :;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:  \\ |         |");
	gotoxy(75, 30);
	printf("  |_________|/    ::::::::::::::::::::::::::::::::::::::::     \\|_________|");
}

void fire() { // 모닥불
	print_fire();
	clear_chatwindow();
	printf("당신은 신비로운 불꽃를 발겼했습니다.");
	gotoxy(114, 46);
	printf("\"원하는 카드 한 장을 불태울 수 있을 것 같아. 불태울까?\"(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("불태울 카드를 선택하세요.");
		int pick;
		scanf("%d", &pick);
		delete_card(pick);
		Sleep(2000);
		print_UI();
		clear_chatwindow();
		printf("카드 한 장을 불태웠습니다.");
		Sleep(2000);
		clear_chatwindow();
	}
	else {
		print_UI();
		clear_chatwindow();
		printf("\"내 카드들은 소중해.\"");
		Sleep(2000);
		clear_chatwindow();
	}
}

void print_pickup_card() { // 카드 한 장 출력
	gotoxy(100, 22);
	printf("┏━━━━━━━━┓ ");
	gotoxy(100, 23);
	printf("┃        ┃ ");
	gotoxy(100, 24);
	printf("┃        ┃ ");
	gotoxy(100, 25);
	printf("┃    ?   ┃ ");
	gotoxy(100, 26);
	printf("┃        ┃ ");
	gotoxy(100, 27);
	printf("┃        ┃ ");
	gotoxy(100, 28);
	printf("┃        ┃ ");
	gotoxy(100, 29);
	printf("┗━━━━━━━━┛ ");
}

void pickup_card() { // 카드 줍기
	print_pickup_card();
	clear_chatwindow();
	printf("당신은 바닥에 떨어진 카드 한 장을 발겼했습니다.");
	gotoxy(114, 46);
	printf("\"카드를 주워볼까?\"(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		get_card();
		Sleep(2000);
		print_UI();
		clear_chatwindow();
		printf("카드 한 장을 획득했습니다.");
		Sleep(2000);
		clear_chatwindow();
	}
	else {
		print_UI();
		clear_chatwindow();
		printf("\"저 카드는 분명 필요가 없을거야.\"");
		Sleep(2000);
		clear_chatwindow();
	}
}

void print_joker_merchant() { // 조커 출력
	gotoxy(50, 2);
	printf("                               .#@#.~@@@@@=.");
	gotoxy(50, 3);
	printf("                              :@@@@@@@@@@@@#*.");
	gotoxy(50, 4);
	printf("                              ~@@@=**@@@@@@@@@~");
	gotoxy(50, 5);
	printf("                               #@#     =@@@@@@@@");
	gotoxy(50, 6);
	printf("                                        .;@@@@@@=");
	gotoxy(50, 7);
	printf("                                          !@@@@@@#");
	gotoxy(50, 8);
	printf("                                           ;@@@@@@,");
	gotoxy(50, 9);
	printf("                                   ;;;;:;,  @@@@@@@       ,;;;;~~.");
	gotoxy(50, 10);
	printf("                                ,@@@@#$$@@@=,@@@@@@!   .#@@@@@#@@@#;.");
	gotoxy(50, 11);
	printf("                              ,#@@@@$#@@@@@@@@@@@@@# =#@@@@@@#@@#@@#@=");
	gotoxy(50, 12);
	printf("                             !@@@@@####@@@@@@@@@@@@@@@@@@@@@@@@==$@@$@=");
	gotoxy(50, 13);
	printf("                            .@@@@@##@#@@@@@@@@@@@@@@@@@@@@@@@@@==$$=@@@@");
	gotoxy(50, 14);
	printf("                           ,@@@@@@@$@@@@@@@@@@@@@@@@@@@@@@@@@@@##$=@@@@@~");
	gotoxy(50, 15);
	printf("                           *@@$=;,!=@@@@@@@@@@@@@@@@@@@@@@@@@#@@*;.~==@@@");
	gotoxy(50, 16);
	printf("                          -@@:      .*@@@@@@@@@@@@@@@@@@@@@@@@*.      .@@*");
	gotoxy(50, 17);
	printf("                          =$          ;@@@@@@@@@@@@@@@@@@@@@@!          $#");
	gotoxy(50, 18);
	printf("                          @~           =@@@@@@@@@@@@@#-$@@@@$            #");
	gotoxy(50, 19);
	printf("                         .;             #@@@@@@@@@@@@$ -@@@@,            ~!");
	gotoxy(50, 20);
	printf("                        ::~             ;@@@@@@@@@@@@@*@@@@$             -@:");
	gotoxy(50, 21);
	printf("                       $@@@              @@@@@@@@@@@@@@#@@@;             @@@$");
	gotoxy(50, 22);
	printf("                      .@@@@*             @@@@@@@@@@@@@@@@@@.            *@@@@.");
	gotoxy(50, 23);
	printf("                       #@@@;             -@@@@@@@@@@@@@@@@@             ;@@@$");
	gotoxy(50, 24);
	printf("                       .@@~              .@@@@@@@@@@#@@@@@;              ~@@");
	gotoxy(50, 25);
	printf("                                         .@@@@@@@@@@@@@@@@.");
	gotoxy(50, 26);
	printf("                                          ~~~~~~~~-~~~~~~~");
	gotoxy(50, 27);
	printf("                                         .#######$########:");
	gotoxy(50, 28);
	printf("                                         .@@$,  :@@$:  ;$@@");
	gotoxy(50, 29);
	printf("                                         .@@  ~   *     !@@");
	gotoxy(50, 30);
	printf("                                         -@#  -       , .@@");
	gotoxy(50, 31);
	printf("                                         -@$-.*~    .~* -@@");
	gotoxy(50, 32);
	printf("                                         ,@$#*@#@  ;@#$@=@@");
	gotoxy(50, 33);
	printf("                                          $=:-~@@$ @@@ ;*@.");
	gotoxy(50, 34);
	printf("                                         ~@* #$$$$ @=$$= @:");
	gotoxy(50, 35);
	printf("                                         @=@ *   $ !  ~ ;@@:");
	gotoxy(50, 36);
	printf("                                        !$ @;   -$ $  . =@@#");
	gotoxy(50, 37);
	printf("                                        @  @@,  *= #=  ,@@@@,");
	gotoxy(50, 38);
	printf("                                       ~!  @@@$=;! :@=$@@@@@#");
	gotoxy(50, 39);
	printf("                                       $@**=@@@:~!-* :@@$**##");
	gotoxy(50, 40);
	printf("                                      -@-  :@@=#:   @~@@*   @@");
	gotoxy(50, 41);
	printf("                                      .~   =@@@.~~~~~=@@@   ~~");
	gotoxy(50, 42);
	printf("                                           !=@@@     #@@@:");
	gotoxy(50, 43);
	printf("                                          ,! @@@$,$~#@@@@=");
	gotoxy(50, 44);
	printf("                                          $- -@@@@@@@@@@@$");
	gotoxy(50, 45);
	printf("                                          $,@#!$@@@@@!#@@@.");
	gotoxy(70, 46);
	printf("                      $@,   @~@@,  ,=@.");
	gotoxy(70, 47);
	printf("                     @@     ; $=     *@-");
	gotoxy(70, 48);
	printf("                     @-      $$:     -@");
	gotoxy(70, 49);
	printf("                             :@");
}

void joker_merchant() { // 조커 한 장 획득
	print_joker_merchant();
	clear_chatwindow();
	printf("???이(가) 나타났습니다.");
	gotoxy(114, 46);
	printf("???이(가) 말없이 두 손에 있던 두 카드 중 하나를 건네줍니다.");
	gotoxy(114, 47);
	printf("???의 카드를 받겠습니까?(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("???이(가) 알 수 없는 미소를 짓습니다.");
		if (rand() % 2 == 0) {
			my_card[total_card] = 666;
			total_card++;
			max_card--;
			STR -= 3;
			if (STR < 1) {
				STR = 1;
			}
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			printf("???이(가) 즐거운 표정과 함께 사라집니다.");
			Sleep(2000);
			clear_chatwindow();
		}
		else {
			my_card[total_card] = 777;
			total_card++;
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			printf("???이(가) 아쉬운 표정과 함께 사라집니다.");
			Sleep(2000);
			clear_chatwindow();
		}
	}
	else {
		clear_chatwindow();
		printf("???이(가) 조용히 사라집니다.");
		Sleep(2000);
		print_UI();
	}

}

void print_monster() { // 몬스터 출력
	gotoxy(75, 12);
	printf("            _.------.                        .----.__");
	gotoxy(75, 13);
	printf("           /         \\_.       ._           /---.__  \\");
	gotoxy(75, 14);
	printf("          |  O    O   |\\\\___  //|          /       `\\ |");
	gotoxy(75, 15);
	printf("          |  .vvvvv.  | )   `(/ |         | o     o  \\|");
	gotoxy(75, 16);
	printf("          /  |     |  |/      \\ |  /|   ./| .vvvvv.  |\\");
	gotoxy(75, 17);
	printf("         /   `^^^^^'  / _   _  `|_ ||  / /| |     |  | \\");
	gotoxy(75, 18);
	printf("       ./  /|         | O)  O   ) \\|| //' | `^vvvv'  |/\\\\");
	gotoxy(75, 19);
	printf("      /   / |         \\        /  | | ~   \\          |  \\\\");
	gotoxy(75, 20);
	printf("      \\  /  |        / \\ Y   /'   | \\     |          |   ~");
	gotoxy(75, 21);
	printf("       `'   |  _     |  `._/' |   |  \\     7        /");
	gotoxy(75, 22);
	printf("         _.-'-' `-'-'|  |`-._/   /    \\ _ /    .    |");
	gotoxy(75, 23);
	printf("    __.-'            \\  \\   .   / \\_.  \\ -|_/\\/ `--.|_");
	gotoxy(75, 24);
	printf(" --'                  \\  \\ |   /    |  |              `-");
	gotoxy(75, 25);
	printf("                       \\uU \\UU/     |  /   ");
	gotoxy(75, 26);
	printf("");
}

void monster() { // 몬스터와 전투
	int monster_HP = wave;
	print_monster();
	clear_chatwindow();
	printf("당신은 몬스터와 마주쳤습니다.");
	gotoxy(114, 46);
	printf("\"크르르릉.....\"");
	while (1) {
		if (monster_HP <= 0) {
			clear_chatwindow();
			printf("당신은 무사히 몬스터를 처치하였습니다.");
			gotoxy(114, 46);
			printf("몬스터가 가지고 있던 카드를 한 장 획득합니다.");
			get_card();
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			return;
		}
		else if (HP <= 0) {
			clear_chatwindow();
			printf("당신은 무참히 몬스터에게 살해당하였습니다.");
			gotoxy(114, 46);
			printf("소지 가능한 카드 수가 하나 줄어들었습니다.");
			max_card--;
			HP = 1;
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			return;
		}
		Sleep(2000);
		clear_chatwindow();
		printf("1의 피해를 입고, %d의 피해를 입혔습니다.", STR);
		HP--;
		monster_HP -= STR;
		gotoxy(114, 46);
		printf("몬스터의 체력이 %d 남았습니다.", monster_HP);
		print_status();
		Sleep(2000);
	}
}

int main() {
	srand(time(NULL));
	for (int i = 0; i < 7; i++) {
		get_card();
	}
	printf("\n당신은 여느날과 다름없이 잠에 들고 눈을 뜬 뒤에 주변을 살펴보앗습니다.\n");
	printf("난생 처음 보는 곳에서 눈을 뜬 당신은 잠시 당황하지만, 이내 차분히 상태를 점검합니다.\n");
	printf("바로 옆에 떨어져 있는 종이에는 이 곳에 대해서 자세히 적혀있었습니다.\n");
	printf("\n\"'이세계 카드 던전'에 오신 것을 환영합니다.\"\n");
	printf("\"당신은 '도둑잡기 게임'의 룰을 따라 카드를 모두 소진한 뒤에 이곳에서 나갈 수 있습니다.\"\n");
	printf("\"만약 소지 가능한 카드의 최대치를 넘기게 된다면.....\"\n");
	printf("\n\"뒤는 흐려져 잘 보이지 않지만 좋은 일이 생길 것 같진 않군...\"\n");
	printf("\n\"빨간 카드는 체력 회복, 검은 카드는 힘이 강해집니다.\"\n");
	printf("\"증가 수치는 영문자 카드가 2, 숫자 카드는 1입니다.\"\n");
	printf("\"특수한 방법으로 획득할 수 있는 조커 카드인 컬러 조커는 다른 아무 카드와 조합하여 사용하고 최대 체력을 2 증가시킵니다.\"\n");
	printf("\"흑색 조커는 획득 시에 소지 가능한 카드의 최대치를 1 감소시킵니다.\"\n");
	printf("\"하지만, 다른 조커 카드와 함께 사용할 시, 소지 가능한 카드의 최대치를 회복하고, 공격력이 두 배가 됩니다.\"\n");
	printf("\"몬스터와 조우하여 체력을 모두 소진 하면, 체력이 1이 되고, 소지 가능한 카드의 최대치가 1 감소됩니다.\"\n");
	printf("\"행운을 빕니다.\"\n");
	printf("\n터미널 창을 전체화면으로 바꾸고 크기를 조정했으면 아무 키나 입력하세요.\n");
	getchar();
	print_UI();
	while (1) {
		if (max_card < total_card) {
			clear_chatwindow();
			printf("당신은 카드 소유 자격을 잃고 영원히 갇히게 됩니다...");
			break;
		}
		if (total_card < 1) {
			clear_chatwindow();
			printf("당신은 무사히 카드 던전이라는 미궁을 빠져나왔습니다!!!");
			break;
		}
		use_card();
		clear_chatwindow();
		printf("당신은 천천히 미궁을 돌아다닙니다...");
		Sleep(2000);
		if (wave % 4 == 1) {
			monster();
		}
		else {
			switch (rand() % 20 + 1)
			{
			case 1: case 2: case 3:
				chest();
				break;
			case 4: case 5: case 6:
				pickup_card();
				break;
			case 7: case 8: case 9:
				change_card();
				break;
			case 10: case 11: case 12:
				thief();
				break;
			case 13: case 14:
				heal_wather();
				break;
			case 15: case 16:
				magician();
				break;
			case 17: case 18:
				fire();
				break;
			case 19:
				black_merchant();
				break;
			case 20:
				joker_merchant();
				break;
			}
		}
		wave++;
	}
	return 0;
}
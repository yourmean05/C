#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> // ���ͳݿ��� ã�� �������

int card_kind[4][13] = { // ī�� ����
	{101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113},
	{201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213},
	{301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313},
	{401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413}
}; // �����̵� = 100, ���̾� = 200, ��Ʈ = 300, Ŭ�ι� = 400, �÷���Ŀ = 777, ����Ŀ = 666

int max_card = 10, total_card = 0, my_card[15], random_card, random_card_kind, random_card_number;

int max_HP = 5, HP = 5, STR = 1;

int clear = 0;

int wave = 1;

char answer;

enum ColorType { // ���� ������ ǥ��
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

void textcolor(unsigned short text, unsigned short back) { // \033[n;nm�� �����ؼ� ���ͳݿ��� �˻��� �ؽ�Ʈ �� ���� �Լ�
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

void gotoxy(int x, int y) { // \033[y;xf�� �����Ͽ� ���ͳݿ��� �˻��� �͹̳� ��ǥ �̵� �Լ�
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void print_side() { // �µθ� ���
	gotoxy(0, 0);
	printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
	for (int i = 1; i <= 58; i++) {
		gotoxy(0, i);
		printf("��                                                                                                                                                                                                                ��\n");
	}
	gotoxy(0, 59);
	printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
}

void print_card(int i, int card) { // ī�� ���
	gotoxy(2 + i * 11, 51);
	textcolor(BLACK, WHITE);
	printf("�������������������� ");
	gotoxy(2 + i * 11, 52);
	printf("�� ");
	if (card != 666 && card != 777) {
		switch (card / 100) {
		case 1:
			printf("��");
			break;
		case 2:
			textcolor(RED, WHITE);
			printf("��");
			textcolor(BLACK, WHITE);
			break;
		case 3:
			textcolor(RED, WHITE);
			printf("��");
			textcolor(BLACK, WHITE);
			break;
		case 4:
			printf("��");
			break;
		}
	}
	else if (card == 666) {
		printf("�� ");
	}
	else if (card == 777) {
		textcolor(RED, WHITE);
		printf("��");
		textcolor(BLACK, WHITE);
	}
	printf("     �� ");
	gotoxy(2 + i * 11, 53);
	printf("��        �� ");
	gotoxy(2 + i * 11, 54);
	if (card != 666 && card != 777) {
		printf("��   ");
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
		printf("   �� ");
	}
	else if (card == 666) {
		printf("��  JOKER �� ");
	}
	else if (card == 777) {
		printf("��  ");
		textcolor(RED, WHITE);
		printf("JOKER");
		textcolor(BLACK, WHITE);
		printf(" �� ");
	}
	gotoxy(2 + i * 11, 55);
	printf("��        �� ");
	gotoxy(2 + i * 11, 56);
	printf("��        �� ");
	gotoxy(2 + i * 11, 57);
	printf("��        �� ");
	gotoxy(2 + i * 11, 58);
	printf("�������������������� ");
	textcolor(WHITE, BLACK);
}

void print_card_back(int i) { // ī�� �޸� ���
	gotoxy(2 + i * 11, 51);
	printf("�������������������� ");
	gotoxy(2 + i * 11, 52);
	printf("��        �� ");
	gotoxy(2 + i * 11, 53);
	printf("��        �� ");
	gotoxy(2 + i * 11, 54);
	printf("��    ?   �� ");
	gotoxy(2 + i * 11, 55);
	printf("��        �� ");
	gotoxy(2 + i * 11, 56);
	printf("��        �� ");
	gotoxy(2 + i * 11, 57);
	printf("��        �� ");
	gotoxy(2 + i * 11, 58);
	printf("�������������������� ");
}

void print_chatwindow() { // ��ȭâ ���
	gotoxy(112, 44);
	printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	gotoxy(112, 45);
	printf("��");
	gotoxy(112, 46);
	printf("��");
	gotoxy(112, 47);
	printf("��");
	gotoxy(112, 48);
	printf("��");
	gotoxy(112, 49);
	printf("��");
	gotoxy(112, 50);
	printf("��");
	gotoxy(112, 51);
	printf("��");
	gotoxy(112, 52);
	printf("��");
	gotoxy(112, 53);
	printf("��");
	gotoxy(112, 54);
	printf("��");
	gotoxy(112, 55);
	printf("��");
	gotoxy(112, 56);
	printf("��");
	gotoxy(112, 57);
	printf("��");
	gotoxy(112, 58);
	printf("��");
	gotoxy(112, 59);
	printf("��");
}

void clear_chatwindow() { // ��ȭâ �ʱ�ȭ
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

void print_status() { // HP, ���ݷ� ǥ��
	gotoxy(3, 47);
	printf("ü�� : %d / %d                      ���ݷ� : %d", HP, max_HP, STR);
	gotoxy(3, 49);
	for (int i = 0; i < HP; i++) {
		textcolor(BLACK, RED);
		printf("��     ");
	}
	if (max_HP - HP != 0)
		printf("��");
	for (int i = 0; i < max_HP - HP; i++) {
		textcolor(BLACK, DarkGray);
		printf("     ��");
	}
	if (max_HP - HP == 0)
		printf("��");
	textcolor(WHITE, BLACK);
}

void get_card() { // ī�� ȹ��
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

void delete_card(int num) { // ī�� ����
	for (int i = num - 1; i < total_card - 1; i++) {
		my_card[i] = my_card[i + 1];
	}
	my_card[total_card - 1] = 0;
	total_card--;
}

void print_UI() { // ��ü UI ���
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

void use_card() { // ī�� ���
	clear_chatwindow();
	printf("ī�带 ����Ͻðڽ��ϱ�?(y/n) ");
	scanf(" %c", &answer);
	if (answer != 'y' && answer != 'Y') {
		return;
	}
	int first_card = 0, second_card = 0;
	clear = 0;
	clear_chatwindow();
	printf("ī�� �� ���� ��ȣ�� �Է��ϼ���.(n n) ");
	gotoxy(114, 46);
	printf("ī�� ����� ����ϱ⸦ ���ϸ� 0 0�� �Է��ϼ���. ");
	scanf("%d %d", &first_card, &second_card);
	if (first_card == 0 && second_card == 0)
		return;
	else if (first_card == second_card || first_card <= 0 || second_card <= 0 || first_card > total_card || second_card > total_card) {
		clear_chatwindow();
		printf("�߸��� ���� �Է��Ͽ����ϴ�.");
		use_card();
	}
	if (clear == 0) {
		gotoxy(90, 25);
		textcolor(BLACK, WHITE);
		printf("�������������������� �������������������� ");
		gotoxy(90, 26);
		printf("�� ");
		if (my_card[first_card - 1] != 666 && my_card[first_card - 1] != 777) {
			switch (my_card[first_card - 1] / 100) {
			case 1:
				printf("��");
				break;
			case 2:
				textcolor(RED, WHITE);
				printf("��");
				textcolor(BLACK, WHITE);
				break;
			case 3:
				textcolor(RED, WHITE);
				printf("��");
				textcolor(BLACK, WHITE);
				break;
			case 4:
				printf("��");
				break;
			}
		}
		else if (my_card[first_card - 1] == 666) {
			printf("�� ");
		}
		else if (my_card[first_card - 1] == 777) {
			textcolor(RED, WHITE);
			printf("��");
			textcolor(BLACK, WHITE);
		}
		printf("     �� ");
		printf("�� ");
		if (my_card[second_card - 1] != 666 && my_card[second_card - 1] != 777) {
			switch (my_card[second_card - 1] / 100) {
			case 1:
				printf("��");
				break;
			case 2:
				textcolor(RED, WHITE);
				printf("��");
				textcolor(BLACK, WHITE);
				break;
			case 3:
				textcolor(RED, WHITE);
				printf("��");
				textcolor(BLACK, WHITE);
				break;
			case 4:
				printf("��");
				break;
			}
		}
		else if (my_card[second_card - 1] == 666) {
			printf("�� ");
		}
		else if (my_card[second_card - 1] == 777) {
			textcolor(RED, WHITE);
			printf("��");
			textcolor(BLACK, WHITE);
		}
		printf("     �� ");
		gotoxy(90, 27);
		printf("��        �� ��        �� ");
		gotoxy(90, 28);
		if (my_card[first_card - 1] != 666 && my_card[first_card - 1] != 777) {
			printf("��   ");
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
			printf("   �� ");
		}
		else if (my_card[first_card - 1] == 666) {
			printf("��  JOKER �� ");
		}
		else if (my_card[first_card - 1] == 777) {
			printf("��  ");
			textcolor(RED, WHITE);
			printf("JOKER");
			textcolor(BLACK, WHITE);
			printf(" �� ");
		}
		if (my_card[second_card - 1] != 666 && my_card[second_card - 1] != 777) {
			printf("��   ");
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
			printf("   �� ");
		}
		else if (my_card[second_card - 1] == 666) {
			printf("��  JOKER �� ");
		}
		else if (my_card[second_card - 1] == 777) {
			printf("��  ");
			textcolor(RED, WHITE);
			printf("JOKER");
			textcolor(BLACK, WHITE);
			printf(" �� ");
		}
		gotoxy(90, 29);
		printf("��        �� ��        �� ");
		gotoxy(90, 30);
		printf("��        �� ��        �� ");
		gotoxy(90, 31);
		printf("��        �� ��        �� ");
		gotoxy(90, 32);
		printf("�������������������� �������������������� ");
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
		printf("������ ����˴ϴ�.");
		Sleep(2000);
		print_UI();
		Sleep(2000);
	}
	else {
		clear_chatwindow();
		printf("�ùٸ� ī�尡 �ƴմϴ�.");
		Sleep(2000);
		print_UI();
	}
}

void print_chest() { // ���� ���
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

void chest() { // ����
	print_chest();
	clear_chatwindow();
	printf("����� �ź�ο� ���ڸ� �߰��߽��ϴ�.");
	gotoxy(114, 46);
	printf("\"�����?\" (y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		if (rand() % 10 < 8) {
			clear_chatwindow();
			get_card();
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			printf("ī�� �� ���� ȹ���߽��ϴ�.");
			Sleep(2000);
			clear_chatwindow();
		}
		else {
			clear_chatwindow();
			HP--;
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			printf("���ڷ� �а��� �̹��� �����ļ� ü���� 1 �����߽��ϴ�.");
			Sleep(2000);
			clear_chatwindow();
		}
	}
	else {
		print_UI();
		clear_chatwindow();
		printf("\"�� ���ڴ� �и� �̹��ϰž�.\"");
		Sleep(2000);
		clear_chatwindow();
	}
}

void print_heal_wather() { // ������ �� ���
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

void heal_wather() { // ������ ��
	print_heal_wather();
	clear_chatwindow();
	printf("����� ������ ����� �������� ������ �߰��߽��ϴ�.");
	gotoxy(114, 46);
	printf("\"��� �����ٰ� �������.\"");
	int heal = (rand() % 3) + 1;
	HP += heal;
	if (HP > max_HP) {
		HP = max_HP;
	}
	Sleep(2000);
	print_UI();
	clear_chatwindow();
	printf("ü���� %d��ŭ ȸ���Ǿ����ϴ�.", heal);
	Sleep(2000);
	print_UI();
}

void print_black_merchant() { // �ϻ��� ���
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

void black_merchant() { // �ϻ��� ����
	print_black_merchant();
	clear_chatwindow();
	printf("�ϻ����� ��Ÿ�����ϴ�.");
	gotoxy(114, 46);
	printf("\"���� ���ݷ��� 5 �÷����״�, ������ ���� �ִ� ü���� 1 �ְڳ�?\"");
	gotoxy(114, 47);
	printf("�ϻ����� ������ �����Ͻðڽ��ϱ�?(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("\"�� �����ߴ�.....\"");
		max_HP--;
		STR += 5;
		Sleep(2000);
		print_UI();
		clear_chatwindow();
		printf("������ ����Ǿ����ϴ�.");
		Sleep(2000);
		clear_chatwindow();
	}
	else {
		clear_chatwindow();
		printf("\"�ƽ��ԵƱ�.....\"");
		Sleep(2000);
		print_UI();
	}
}

void print_change_card1() { // ���� ��� 1 ���
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

void print_change_card2() { // ���� ��� 2 ���
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

void print_change_card3() { // ���� ��� 3 ���
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

void print_change_card4() { // ���� ��� 4 ���
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

void change_card() { // ī�� ��ȯ
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
	printf("���ó�� ������ �ִ� ���� ����� �������ϴ�.");
	gotoxy(114, 46);
	printf("\"�츮 ī�带 �� �徿 �ٲ��� ������?\"");
	gotoxy(114, 47);
	printf("���� ����� ������ �����Ͻðڽ��ϱ�?(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("\"���� ���� �ʿ��� ī��...!\"");
		gotoxy(114, 46);
		printf("�ٲ� ī�� �� ���� ������.");
		int pick;
		scanf("%d", &pick);
		delete_card(pick);
		get_card();
		Sleep(2000);
		print_UI();
		clear_chatwindow();
		printf("ī�带 ��ȯ�߽��ϴ�.");
		Sleep(2000);
		print_UI();
	}
	else {
		clear_chatwindow();
		printf("\"�׷� �������� ���� �ۿ��� ���ڰ�.\"");
		Sleep(2000);
		print_UI();
	}
}

void print_magician() { // ������ ���
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

void magician() { // ������ ����
	print_magician();
	clear_chatwindow();
	printf("�����簡 ��Ÿ�����ϴ�.");
	gotoxy(114, 46);
	printf("\"���� ���� ī�� ���� �ٲ��ٱ�?\"");
	gotoxy(114, 47);
	printf("�������� ������ �����Ͻðڽ��ϱ�?(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("\"����, ī�� �� �� ����.\" ");
		int pick;
		scanf("%d", &pick);
		clear_chatwindow();
		printf("\"�׷�, �� ���� �Ƿ��� �� �����...!\"");
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
		printf("ī�� ���� ����Ǿ����ϴ�.");
		Sleep(2000);
		clear_chatwindow();
	}
	else {
		clear_chatwindow();
		printf("\"���� ��ȸ�� ���ڰ�.\"");
		Sleep(2000);
		print_UI();
	}
}

void print_thief() { // ���� ���
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

void thief() { // ���� ����
	print_thief();
	clear_chatwindow();
	printf("������ ��Ÿ�����ϴ�.");
	gotoxy(114, 46);
	printf("\"�� ī��� ���� ���� ������.\"");
	delete_card(rand() % (total_card + 1));
	Sleep(2000);
	print_UI();
	clear_chatwindow();
	printf("ī�� �� ���� ���Ѱ���ϴ�.");
	Sleep(2000);
	clear_chatwindow();
}

void print_fire() { // ��ں� ���
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

void fire() { // ��ں�
	print_fire();
	clear_chatwindow();
	printf("����� �ź�ο� �Ҳɸ� �߰��߽��ϴ�.");
	gotoxy(114, 46);
	printf("\"���ϴ� ī�� �� ���� ���¿� �� ���� �� ����. ���¿��?\"(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("���¿� ī�带 �����ϼ���.");
		int pick;
		scanf("%d", &pick);
		delete_card(pick);
		Sleep(2000);
		print_UI();
		clear_chatwindow();
		printf("ī�� �� ���� ���¿����ϴ�.");
		Sleep(2000);
		clear_chatwindow();
	}
	else {
		print_UI();
		clear_chatwindow();
		printf("\"�� ī����� ������.\"");
		Sleep(2000);
		clear_chatwindow();
	}
}

void print_pickup_card() { // ī�� �� �� ���
	gotoxy(100, 22);
	printf("�������������������� ");
	gotoxy(100, 23);
	printf("��        �� ");
	gotoxy(100, 24);
	printf("��        �� ");
	gotoxy(100, 25);
	printf("��    ?   �� ");
	gotoxy(100, 26);
	printf("��        �� ");
	gotoxy(100, 27);
	printf("��        �� ");
	gotoxy(100, 28);
	printf("��        �� ");
	gotoxy(100, 29);
	printf("�������������������� ");
}

void pickup_card() { // ī�� �ݱ�
	print_pickup_card();
	clear_chatwindow();
	printf("����� �ٴڿ� ������ ī�� �� ���� �߰��߽��ϴ�.");
	gotoxy(114, 46);
	printf("\"ī�带 �ֿ�����?\"(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		get_card();
		Sleep(2000);
		print_UI();
		clear_chatwindow();
		printf("ī�� �� ���� ȹ���߽��ϴ�.");
		Sleep(2000);
		clear_chatwindow();
	}
	else {
		print_UI();
		clear_chatwindow();
		printf("\"�� ī��� �и� �ʿ䰡 �����ž�.\"");
		Sleep(2000);
		clear_chatwindow();
	}
}

void print_joker_merchant() { // ��Ŀ ���
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

void joker_merchant() { // ��Ŀ �� �� ȹ��
	print_joker_merchant();
	clear_chatwindow();
	printf("???��(��) ��Ÿ�����ϴ�.");
	gotoxy(114, 46);
	printf("???��(��) ������ �� �տ� �ִ� �� ī�� �� �ϳ��� �ǳ��ݴϴ�.");
	gotoxy(114, 47);
	printf("???�� ī�带 �ްڽ��ϱ�?(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("???��(��) �� �� ���� �̼Ҹ� �����ϴ�.");
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
			printf("???��(��) ��ſ� ǥ���� �Բ� ������ϴ�.");
			Sleep(2000);
			clear_chatwindow();
		}
		else {
			my_card[total_card] = 777;
			total_card++;
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			printf("???��(��) �ƽ��� ǥ���� �Բ� ������ϴ�.");
			Sleep(2000);
			clear_chatwindow();
		}
	}
	else {
		clear_chatwindow();
		printf("???��(��) ������ ������ϴ�.");
		Sleep(2000);
		print_UI();
	}

}

void print_monster() { // ���� ���
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

void monster() { // ���Ϳ� ����
	int monster_HP = wave;
	print_monster();
	clear_chatwindow();
	printf("����� ���Ϳ� �����ƽ��ϴ�.");
	gotoxy(114, 46);
	printf("\"ũ������.....\"");
	while (1) {
		if (monster_HP <= 0) {
			clear_chatwindow();
			printf("����� ������ ���͸� óġ�Ͽ����ϴ�.");
			gotoxy(114, 46);
			printf("���Ͱ� ������ �ִ� ī�带 �� �� ȹ���մϴ�.");
			get_card();
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			return;
		}
		else if (HP <= 0) {
			clear_chatwindow();
			printf("����� ������ ���Ϳ��� ���ش��Ͽ����ϴ�.");
			gotoxy(114, 46);
			printf("���� ������ ī�� ���� �ϳ� �پ������ϴ�.");
			max_card--;
			HP = 1;
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			return;
		}
		Sleep(2000);
		clear_chatwindow();
		printf("1�� ���ظ� �԰�, %d�� ���ظ� �������ϴ�.", STR);
		HP--;
		monster_HP -= STR;
		gotoxy(114, 46);
		printf("������ ü���� %d ���ҽ��ϴ�.", monster_HP);
		print_status();
		Sleep(2000);
	}
}

int main() {
	srand(time(NULL));
	for (int i = 0; i < 7; i++) {
		get_card();
	}
	printf("\n����� �������� �ٸ����� �ῡ ��� ���� �� �ڿ� �ֺ��� ���캸�ѽ��ϴ�.\n");
	printf("���� ó�� ���� ������ ���� �� ����� ��� ��Ȳ������, �̳� ������ ���¸� �����մϴ�.\n");
	printf("�ٷ� ���� ������ �ִ� ���̿��� �� ���� ���ؼ� �ڼ��� �����־����ϴ�.\n");
	printf("\n\"'�̼��� ī�� ����'�� ���� ���� ȯ���մϴ�.\"\n");
	printf("\"����� '������� ����'�� ���� ���� ī�带 ��� ������ �ڿ� �̰����� ���� �� �ֽ��ϴ�.\"\n");
	printf("\"���� ���� ������ ī���� �ִ�ġ�� �ѱ�� �ȴٸ�.....\"\n");
	printf("\n\"�ڴ� ����� �� ������ ������ ���� ���� ���� �� ���� �ʱ�...\"\n");
	printf("\n\"���� ī��� ü�� ȸ��, ���� ī��� ���� �������ϴ�.\"\n");
	printf("\"���� ��ġ�� ������ ī�尡 2, ���� ī��� 1�Դϴ�.\"\n");
	printf("\"Ư���� ������� ȹ���� �� �ִ� ��Ŀ ī���� �÷� ��Ŀ�� �ٸ� �ƹ� ī��� �����Ͽ� ����ϰ� �ִ� ü���� 2 ������ŵ�ϴ�.\"\n");
	printf("\"��� ��Ŀ�� ȹ�� �ÿ� ���� ������ ī���� �ִ�ġ�� 1 ���ҽ�ŵ�ϴ�.\"\n");
	printf("\"������, �ٸ� ��Ŀ ī��� �Բ� ����� ��, ���� ������ ī���� �ִ�ġ�� ȸ���ϰ�, ���ݷ��� �� �谡 �˴ϴ�.\"\n");
	printf("\"���Ϳ� �����Ͽ� ü���� ��� ���� �ϸ�, ü���� 1�� �ǰ�, ���� ������ ī���� �ִ�ġ�� 1 ���ҵ˴ϴ�.\"\n");
	printf("\"����� ���ϴ�.\"\n");
	printf("\n�͹̳� â�� ��üȭ������ �ٲٰ� ũ�⸦ ���������� �ƹ� Ű�� �Է��ϼ���.\n");
	getchar();
	print_UI();
	while (1) {
		if (max_card < total_card) {
			clear_chatwindow();
			printf("����� ī�� ���� �ڰ��� �Ұ� ������ ������ �˴ϴ�...");
			break;
		}
		if (total_card < 1) {
			clear_chatwindow();
			printf("����� ������ ī�� �����̶�� �̱��� �������Խ��ϴ�!!!");
			break;
		}
		use_card();
		clear_chatwindow();
		printf("����� õõ�� �̱��� ���ƴٴմϴ�...");
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
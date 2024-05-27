#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> // 檣攪喘縑憮 瓊擎 ④渦だ橾

int card_kind[4][13] = { // 蘋萄 謙盟
	{101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113},
	{201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213},
	{301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313},
	{401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413}
}; // 蝶む檜萄 = 100, 棻檜嬴 = 200, жお = 300, 贗煎幗 = 400, 鏽楝褻醴 = 777, �碻傭� = 666

int max_card = 10, total_card = 0, my_card[15], random_card, random_card_kind, random_card_number;

int max_HP = 5, HP = 5, STR = 1;

int clear = 0;

int wave = 1;

char answer;

enum ColorType { // 儀梃 翮剪⑽ ル衛
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

void textcolor(unsigned short text, unsigned short back) { // \033[n;nm檜 碳らп憮 檣攪喘縑憮 匐儀и 臢蝶お 儀 滲唳 л熱
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

void gotoxy(int x, int y) { // \033[y;xf陛 碳らж罹 檣攪喘縑憮 匐儀и 攪嘐割 謝ル 檜翕 л熱
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void print_side() { // 鷓舒葬 轎溘
	gotoxy(0, 0);
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	for (int i = 1; i <= 58; i++) {
		gotoxy(0, i);
		printf("早                                                                                                                                                                                                                早\n");
	}
	gotoxy(0, 59);
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭\n");
}

void print_card(int i, int card) { // 蘋萄 轎溘
	gotoxy(2 + i * 11, 51);
	textcolor(BLACK, WHITE);
	printf("旨收收收收收收收收旬 ");
	gotoxy(2 + i * 11, 52);
	printf("早 ");
	if (card != 666 && card != 777) {
		switch (card / 100) {
		case 1:
			printf("Ⅳ");
			break;
		case 2:
			textcolor(RED, WHITE);
			printf("﹣");
			textcolor(BLACK, WHITE);
			break;
		case 3:
			textcolor(RED, WHITE);
			printf("Ⅵ");
			textcolor(BLACK, WHITE);
			break;
		case 4:
			printf("Ⅷ");
			break;
		}
	}
	else if (card == 666) {
		printf("╳ ");
	}
	else if (card == 777) {
		textcolor(RED, WHITE);
		printf("０");
		textcolor(BLACK, WHITE);
	}
	printf("     早 ");
	gotoxy(2 + i * 11, 53);
	printf("早        早 ");
	gotoxy(2 + i * 11, 54);
	if (card != 666 && card != 777) {
		printf("早   ");
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
		printf("   早 ");
	}
	else if (card == 666) {
		printf("早  JOKER 早 ");
	}
	else if (card == 777) {
		printf("早  ");
		textcolor(RED, WHITE);
		printf("JOKER");
		textcolor(BLACK, WHITE);
		printf(" 早 ");
	}
	gotoxy(2 + i * 11, 55);
	printf("早        早 ");
	gotoxy(2 + i * 11, 56);
	printf("早        早 ");
	gotoxy(2 + i * 11, 57);
	printf("早        早 ");
	gotoxy(2 + i * 11, 58);
	printf("曲收收收收收收收收旭 ");
	textcolor(WHITE, BLACK);
}

void print_card_back(int i) { // 蘋萄 萌賊 轎溘
	gotoxy(2 + i * 11, 51);
	printf("旨收收收收收收收收旬 ");
	gotoxy(2 + i * 11, 52);
	printf("早        早 ");
	gotoxy(2 + i * 11, 53);
	printf("早        早 ");
	gotoxy(2 + i * 11, 54);
	printf("早    ?   早 ");
	gotoxy(2 + i * 11, 55);
	printf("早        早 ");
	gotoxy(2 + i * 11, 56);
	printf("早        早 ");
	gotoxy(2 + i * 11, 57);
	printf("早        早 ");
	gotoxy(2 + i * 11, 58);
	printf("曲收收收收收收收收旭 ");
}

void print_chatwindow() { // 渠�倥� 轎溘
	gotoxy(112, 44);
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收朽");
	gotoxy(112, 45);
	printf("早");
	gotoxy(112, 46);
	printf("早");
	gotoxy(112, 47);
	printf("早");
	gotoxy(112, 48);
	printf("早");
	gotoxy(112, 49);
	printf("早");
	gotoxy(112, 50);
	printf("早");
	gotoxy(112, 51);
	printf("早");
	gotoxy(112, 52);
	printf("早");
	gotoxy(112, 53);
	printf("早");
	gotoxy(112, 54);
	printf("早");
	gotoxy(112, 55);
	printf("早");
	gotoxy(112, 56);
	printf("早");
	gotoxy(112, 57);
	printf("早");
	gotoxy(112, 58);
	printf("早");
	gotoxy(112, 59);
	printf("朴");
}

void clear_chatwindow() { // 渠�倥� 蟾晦��
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

void print_status() { // HP, 奢問溘 ル晦
	gotoxy(3, 47);
	printf("羹溘 : %d / %d                      奢問溘 : %d", HP, max_HP, STR);
	gotoxy(3, 49);
	for (int i = 0; i < HP; i++) {
		textcolor(BLACK, RED);
		printf("早     ");
	}
	if (max_HP - HP != 0)
		printf("早");
	for (int i = 0; i < max_HP - HP; i++) {
		textcolor(BLACK, DarkGray);
		printf("     早");
	}
	if (max_HP - HP == 0)
		printf("早");
	textcolor(WHITE, BLACK);
}

void get_card() { // 蘋萄 �僱�
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

void delete_card(int num) { // 蘋萄 薯剪
	for (int i = num - 1; i < total_card - 1; i++) {
		my_card[i] = my_card[i + 1];
	}
	my_card[total_card - 1] = 0;
	total_card--;
}

void print_UI() { // 瞪羹 UI 轎溘
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

void use_card() { // 蘋萄 餌辨
	clear_chatwindow();
	printf("蘋萄蒂 餌辨ж衛啊蝗棲梱?(y/n) ");
	scanf(" %c", &answer);
	if (answer != 'y' && answer != 'Y') {
		return;
	}
	int first_card = 0, second_card = 0;
	clear = 0;
	clear_chatwindow();
	printf("蘋萄 舒 濰曖 廓�ㄧ� 殮溘ж撮蹂.(n n) ");
	gotoxy(114, 46);
	printf("蘋萄 餌辨擊 鏃模ж晦蒂 錳ж賊 0 0擊 殮溘ж撮蹂. ");
	scanf("%d %d", &first_card, &second_card);
	if (first_card == 0 && second_card == 0)
		return;
	else if (first_card == second_card || first_card <= 0 || second_card <= 0 || first_card > total_card || second_card > total_card) {
		clear_chatwindow();
		printf("澀跤脹 高擊 殮溘ж艘蝗棲棻.");
		use_card();
	}
	if (clear == 0) {
		gotoxy(90, 25);
		textcolor(BLACK, WHITE);
		printf("旨收收收收收收收收旬 旨收收收收收收收收旬 ");
		gotoxy(90, 26);
		printf("早 ");
		if (my_card[first_card - 1] != 666 && my_card[first_card - 1] != 777) {
			switch (my_card[first_card - 1] / 100) {
			case 1:
				printf("Ⅳ");
				break;
			case 2:
				textcolor(RED, WHITE);
				printf("﹣");
				textcolor(BLACK, WHITE);
				break;
			case 3:
				textcolor(RED, WHITE);
				printf("Ⅵ");
				textcolor(BLACK, WHITE);
				break;
			case 4:
				printf("Ⅷ");
				break;
			}
		}
		else if (my_card[first_card - 1] == 666) {
			printf("╳ ");
		}
		else if (my_card[first_card - 1] == 777) {
			textcolor(RED, WHITE);
			printf("０");
			textcolor(BLACK, WHITE);
		}
		printf("     早 ");
		printf("早 ");
		if (my_card[second_card - 1] != 666 && my_card[second_card - 1] != 777) {
			switch (my_card[second_card - 1] / 100) {
			case 1:
				printf("Ⅳ");
				break;
			case 2:
				textcolor(RED, WHITE);
				printf("﹣");
				textcolor(BLACK, WHITE);
				break;
			case 3:
				textcolor(RED, WHITE);
				printf("Ⅵ");
				textcolor(BLACK, WHITE);
				break;
			case 4:
				printf("Ⅷ");
				break;
			}
		}
		else if (my_card[second_card - 1] == 666) {
			printf("╳ ");
		}
		else if (my_card[second_card - 1] == 777) {
			textcolor(RED, WHITE);
			printf("０");
			textcolor(BLACK, WHITE);
		}
		printf("     早 ");
		gotoxy(90, 27);
		printf("早        早 早        早 ");
		gotoxy(90, 28);
		if (my_card[first_card - 1] != 666 && my_card[first_card - 1] != 777) {
			printf("早   ");
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
			printf("   早 ");
		}
		else if (my_card[first_card - 1] == 666) {
			printf("早  JOKER 早 ");
		}
		else if (my_card[first_card - 1] == 777) {
			printf("早  ");
			textcolor(RED, WHITE);
			printf("JOKER");
			textcolor(BLACK, WHITE);
			printf(" 早 ");
		}
		if (my_card[second_card - 1] != 666 && my_card[second_card - 1] != 777) {
			printf("早   ");
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
			printf("   早 ");
		}
		else if (my_card[second_card - 1] == 666) {
			printf("早  JOKER 早 ");
		}
		else if (my_card[second_card - 1] == 777) {
			printf("早  ");
			textcolor(RED, WHITE);
			printf("JOKER");
			textcolor(BLACK, WHITE);
			printf(" 早 ");
		}
		gotoxy(90, 29);
		printf("早        早 早        早 ");
		gotoxy(90, 30);
		printf("早        早 早        早 ");
		gotoxy(90, 31);
		printf("早        早 早        早 ");
		gotoxy(90, 32);
		printf("曲收收收收收收收收旭 曲收收收收收收收收旭 ");
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
		printf("蝶囌檜 滲唳腌棲棻.");
		Sleep(2000);
		print_UI();
		Sleep(2000);
	}
	else {
		clear_chatwindow();
		printf("螢夥艇 蘋萄陛 嬴椎棲棻.");
		Sleep(2000);
		print_UI();
	}
}

void print_chest() { // 鼻濠 轎溘
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

void chest() { // 鼻濠
	print_chest();
	clear_chatwindow();
	printf("渡褐擎 褐綠煎遴 鼻濠蒂 嫦啣ц蝗棲棻.");
	gotoxy(114, 46);
	printf("\"翮橫獐梱?\" (y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		if (rand() % 10 < 8) {
			clear_chatwindow();
			get_card();
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			printf("蘋萄 и 濰擊 �僱磈蔇懂炴�.");
			Sleep(2000);
			clear_chatwindow();
		}
		else {
			clear_chatwindow();
			HP--;
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			printf("鼻濠煎 菩骨и 嘐嗶擊 葆輿藥憮 羹溘檜 1 馬模ц蝗棲棻.");
			Sleep(2000);
			clear_chatwindow();
		}
	}
	else {
		print_UI();
		clear_chatwindow();
		printf("\"盪 鼻濠朝 碟貲 嘐嗶橾剪撿.\"");
		Sleep(2000);
		clear_chatwindow();
	}
}

void print_heal_wather() { // 儅貲曖 價 轎溘
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

void heal_wather() { // 儅貲曖 價
	print_heal_wather();
	clear_chatwindow();
	printf("渡褐擎 儅貲曖 晦遴檜 替硫雖朝 價僭擊 嫦啣ц蝗棲棻.");
	gotoxy(114, 46);
	printf("\"濡衛 蓮歷棻陛 轎嫦ж濠.\"");
	int heal = (rand() % 3) + 1;
	HP += heal;
	if (HP > max_HP) {
		HP = max_HP;
	}
	Sleep(2000);
	print_UI();
	clear_chatwindow();
	printf("羹溘檜 %d虜躑 �蛹僱Ц�蝗棲棻.", heal);
	Sleep(2000);
	print_UI();
}

void print_black_merchant() { // 懍鼻檣 轎溘
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

void black_merchant() { // 懍鼻檣 褻辦
	print_black_merchant();
	clear_chatwindow();
	printf("懍鼻檣檜 釭顫陬蝗棲棻.");
	gotoxy(114, 46);
	printf("\"傘曖 奢問溘擊 5 螢溥還纔棲, 釭縑啪 傘曖 譆渠 羹溘擊 1 輿啊釭?\"");
	gotoxy(114, 47);
	printf("懍鼻檣曖 薯寰擊 熱塊ж衛啊蝗棲梱?(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("\"澀 儅陝ц棻.....\"");
		max_HP--;
		STR += 5;
		Sleep(2000);
		print_UI();
		clear_chatwindow();
		printf("蝶囌檜 滲唳腎歷蝗棲棻.");
		Sleep(2000);
		clear_chatwindow();
	}
	else {
		clear_chatwindow();
		printf("\"嬴蔣啪腑捱.....\"");
		Sleep(2000);
		print_UI();
	}
}

void print_change_card1() { // 雩摹 餌塋 1 轎溘
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

void print_change_card2() { // 雩摹 餌塋 2 轎溘
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

void print_change_card3() { // 雩摹 餌塋 3 轎溘
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

void print_change_card4() { // 雩摹 餌塋 4 轎溘
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

void change_card() { // 蘋萄 掖��
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
	printf("渡褐籀歲 湍瞪縑 氈朝 雩摹 餌塋婁 虜陬蝗棲棻.");
	gotoxy(114, 46);
	printf("\"辦葬 蘋萄蒂 и 濰噶 夥紱雖 彊擊楚?\"");
	gotoxy(114, 47);
	printf("雩摹 餌塋曖 薯寰擊 熱塊ж衛啊蝗棲梱?(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("\"薯嫦 頂陛 в蹂и 蘋萄...!\"");
		gotoxy(114, 46);
		printf("夥羚 蘋萄 и 濰擊 堅腦撮蹂.");
		int pick;
		scanf("%d", &pick);
		delete_card(pick);
		get_card();
		Sleep(2000);
		print_UI();
		clear_chatwindow();
		printf("蘋萄蒂 掖�納蔇懂炴�.");
		Sleep(2000);
		print_UI();
	}
	else {
		clear_chatwindow();
		printf("\"斜歲 棻擠縑朝 湍瞪 夤縑憮 爾濠堅.\"");
		Sleep(2000);
		print_UI();
	}
}

void print_magician() { // 葆獎餌 轎溘
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

void magician() { // 葆獎餌 褻辦
	print_magician();
	clear_chatwindow();
	printf("葆獎餌陛 釭顫陬蝗棲棻.");
	gotoxy(114, 46);
	printf("\"頂陛 傘曖 蘋萄 儀擊 夥脯還梱?\"");
	gotoxy(114, 47);
	printf("葆獎餌曖 薯寰擊 熱塊ж衛啊蝗棲梱?(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("\"謠嬴, 蘋萄 и 濰 埤塭瑭.\" ");
		int pick;
		scanf("%d", &pick);
		clear_chatwindow();
		printf("\"斜歲, 頂 葆獎 褒溘擊 澀 爾塭堅...!\"");
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
		printf("蘋萄 儀檜 滲唳腎歷蝗棲棻.");
		Sleep(2000);
		clear_chatwindow();
	}
	else {
		clear_chatwindow();
		printf("\"棻擠 晦�蛾� 爾濠堅.\"");
		Sleep(2000);
		print_UI();
	}
}

void print_thief() { // 紫舜 轎溘
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

void thief() { // 紫舜 褻辦
	print_thief();
	clear_chatwindow();
	printf("紫舜檜 釭顫陬蝗棲棻.");
	gotoxy(114, 46);
	printf("\"檜 蘋萄朝 謠擎 夠縑 賦輿雖.\"");
	delete_card(rand() % (total_card + 1));
	Sleep(2000);
	print_UI();
	clear_chatwindow();
	printf("蘋萄 и 濰擊 貍憾啣蝗棲棻.");
	Sleep(2000);
	clear_chatwindow();
}

void print_fire() { // 賅款碳 轎溘
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

void fire() { // 賅款碳
	print_fire();
	clear_chatwindow();
	printf("渡褐擎 褐綠煎遴 碳粒蒂 嫦啣ц蝗棲棻.");
	gotoxy(114, 46);
	printf("\"錳ж朝 蘋萄 и 濰擊 碳鷓選 熱 氈擊 匙 偽嬴. 碳鷓選梱?\"(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("碳鷓選 蘋萄蒂 摹鷗ж撮蹂.");
		int pick;
		scanf("%d", &pick);
		delete_card(pick);
		Sleep(2000);
		print_UI();
		clear_chatwindow();
		printf("蘋萄 и 濰擊 碳鷓錫蝗棲棻.");
		Sleep(2000);
		clear_chatwindow();
	}
	else {
		print_UI();
		clear_chatwindow();
		printf("\"頂 蘋萄菟擎 模醞п.\"");
		Sleep(2000);
		clear_chatwindow();
	}
}

void print_pickup_card() { // 蘋萄 и 濰 轎溘
	gotoxy(100, 22);
	printf("旨收收收收收收收收旬 ");
	gotoxy(100, 23);
	printf("早        早 ");
	gotoxy(100, 24);
	printf("早        早 ");
	gotoxy(100, 25);
	printf("早    ?   早 ");
	gotoxy(100, 26);
	printf("早        早 ");
	gotoxy(100, 27);
	printf("早        早 ");
	gotoxy(100, 28);
	printf("早        早 ");
	gotoxy(100, 29);
	printf("曲收收收收收收收收旭 ");
}

void pickup_card() { // 蘋萄 鄹晦
	print_pickup_card();
	clear_chatwindow();
	printf("渡褐擎 夥款縑 雲橫霞 蘋萄 и 濰擊 嫦啣ц蝗棲棻.");
	gotoxy(114, 46);
	printf("\"蘋萄蒂 輿錶獐梱?\"(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		get_card();
		Sleep(2000);
		print_UI();
		clear_chatwindow();
		printf("蘋萄 и 濰擊 �僱磈蔇懂炴�.");
		Sleep(2000);
		clear_chatwindow();
	}
	else {
		print_UI();
		clear_chatwindow();
		printf("\"盪 蘋萄朝 碟貲 в蹂陛 橈擊剪撿.\"");
		Sleep(2000);
		clear_chatwindow();
	}
}

void print_joker_merchant() { // 褻醴 轎溘
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

void joker_merchant() { // 褻醴 и 濰 �僱�
	print_joker_merchant();
	clear_chatwindow();
	printf("???檜(陛) 釭顫陬蝗棲棻.");
	gotoxy(114, 46);
	printf("???檜(陛) 蜓橈檜 舒 槳縑 氈湍 舒 蘋萄 醞 ж釭蒂 勒啻鄹棲棻.");
	gotoxy(114, 47);
	printf("???曖 蘋萄蒂 嫡啊蝗棲梱?(y/n) ");
	scanf(" %c", &answer);
	if (answer == 'y' || answer == 'Y') {
		clear_chatwindow();
		printf("???檜(陛) 憲 熱 橈朝 嘐模蒂 騁蝗棲棻.");
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
			printf("???檜(陛) 闌剪遴 ル薑婁 л眷 餌塭餵棲棻.");
			Sleep(2000);
			clear_chatwindow();
		}
		else {
			my_card[total_card] = 777;
			total_card++;
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			printf("???檜(陛) 嬴蓮遴 ル薑婁 л眷 餌塭餵棲棻.");
			Sleep(2000);
			clear_chatwindow();
		}
	}
	else {
		clear_chatwindow();
		printf("???檜(陛) 褻辨�� 餌塭餵棲棻.");
		Sleep(2000);
		print_UI();
	}

}

void print_monster() { // 跨蝶攪 轎溘
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

void monster() { // 跨蝶攪諦 瞪癱
	int monster_HP = wave;
	print_monster();
	clear_chatwindow();
	printf("渡褐擎 跨蝶攪諦 葆輿蟻蝗棲棻.");
	gotoxy(114, 46);
	printf("\"觼腦腦葵.....\"");
	while (1) {
		if (monster_HP <= 0) {
			clear_chatwindow();
			printf("渡褐擎 鼠餌�� 跨蝶攪蒂 籀纂ж艘蝗棲棻.");
			gotoxy(114, 46);
			printf("跨蝶攪陛 陛雖堅 氈湍 蘋萄蒂 и 濰 �僱磈桭炴�.");
			get_card();
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			return;
		}
		else if (HP <= 0) {
			clear_chatwindow();
			printf("渡褐擎 鼠霤�� 跨蝶攪縑啪 髦п渡ж艘蝗棲棻.");
			gotoxy(114, 46);
			printf("模雖 陛棟и 蘋萄 熱陛 ж釭 還橫菟歷蝗棲棻.");
			max_card--;
			HP = 1;
			Sleep(2000);
			print_UI();
			clear_chatwindow();
			return;
		}
		Sleep(2000);
		clear_chatwindow();
		printf("1曖 Яп蒂 殮堅, %d曖 Яп蒂 殮⑼蝗棲棻.", STR);
		HP--;
		monster_HP -= STR;
		gotoxy(114, 46);
		printf("跨蝶攪曖 羹溘檜 %d 陴懊蝗棲棻.", monster_HP);
		print_status();
		Sleep(2000);
	}
}

int main() {
	srand(time(NULL));
	for (int i = 0; i < 7; i++) {
		get_card();
	}
	printf("\n渡褐擎 罹替陳婁 棻葷橈檜 濡縑 菟堅 換擊 嗤 菴縑 輿滲擊 髦よ爾憾蝗棲棻.\n");
	printf("陪儅 籀擠 爾朝 夠縑憮 換擊 嗤 渡褐擎 濡衛 渡�笞狫鷏�, 檜頂 離碟�� 鼻鷓蒂 薄匐м棲棻.\n");
	printf("夥煎 蕙縑 雲橫螳 氈朝 謙檜縑朝 檜 夠縑 渠п憮 濠撮�� 瞳⑵氈歷蝗棲棻.\n");
	printf("\n\"'檜撮啗 蘋萄 湍瞪'縑 螃褐 匙擊 �紊腎桭炴�.\"\n");
	printf("\"渡褐擎 '紫舜濩晦 啪歜'曖 瑙擊 評塭 蘋萄蒂 賅舒 模霞и 菴縑 檜夠縑憮 釭陞 熱 氈蝗棲棻.\"\n");
	printf("\"虜擒 模雖 陛棟и 蘋萄曖 譆渠纂蒂 剩晦啪 脹棻賊.....\"\n");
	printf("\n\"菴朝 �撌謠� 澀 爾檜雖 彊雖虜 謠擎 橾檜 儅望 匙 偽霞 彊捱...\"\n");
	printf("\n\"說除 蘋萄朝 羹溘 �蛹�, 匐擎 蘋萄朝 ��檜 鬼п餵棲棻.\"\n");
	printf("\"隸陛 熱纂朝 艙僥濠 蘋萄陛 2, 璋濠 蘋萄朝 1殮棲棻.\"\n");
	printf("\"か熱и 寞徹戲煎 �僱磈� 熱 氈朝 褻醴 蘋萄檣 鏽楝 褻醴朝 棻艇 嬴鼠 蘋萄諦 褻мж罹 餌辨ж堅 譆渠 羹溘擊 2 隸陛衛霾棲棻.\"\n");
	printf("\"�皛� 褻醴朝 �僱� 衛縑 模雖 陛棟и 蘋萄曖 譆渠纂蒂 1 馬模衛霾棲棻.\"\n");
	printf("\"ж雖虜, 棻艇 褻醴 蘋萄諦 л眷 餌辨й 衛, 模雖 陛棟и 蘋萄曖 譆渠纂蒂 �蛹嘎炾�, 奢問溘檜 舒 寡陛 腌棲棻.\"\n");
	printf("\"跨蝶攪諦 褻辦ж罹 羹溘擊 賅舒 模霞 ж賊, 羹溘檜 1檜 腎堅, 模雖 陛棟и 蘋萄曖 譆渠纂陛 1 馬模腌棲棻.\"\n");
	printf("\"ч遴擊 綢棲棻.\"\n");
	printf("\n攪嘐割 璽擊 瞪羹�飛橉虞� 夥紱堅 觼晦蒂 褻薑ц戲賊 嬴鼠 酈釭 殮溘ж撮蹂.\n");
	getchar();
	print_UI();
	while (1) {
		if (max_card < total_card) {
			clear_chatwindow();
			printf("渡褐擎 蘋萄 模嶸 濠問擊 檠堅 艙錳�� 陘�鱁� 腌棲棻...");
			break;
		}
		if (total_card < 1) {
			clear_chatwindow();
			printf("渡褐擎 鼠餌�� 蘋萄 湍瞪檜塭朝 嘐掙擊 緒螳釭諮蝗棲棻!!!");
			break;
		}
		use_card();
		clear_chatwindow();
		printf("渡褐擎 繭繭�� 嘐掙擊 給嬴棻椎棲棻...");
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
#pragma warning(disable:4996)
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <Windows.h>
#include "myMethod.h"
/* 数の桁数 */
#define NUM_DIGIT 4		//正解の桁数
#define CHARBUFF 124
#define BUFFSIZE 1024
//構造体
struct Num
{
	int num1;	//入力された数字４つ
	int num2;
	int num3;
	int num4;
	int hit;	//hit数
	int blow;	//blow数
};
Num num[5];		//1ゲームにつき5チャンスなので５回分

void getGurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

int main() {
	//iniファイルの読み込み
	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);
	char section[CHARBUFF];
	sprintf_s(section, "section1");
	char keyWord[CHARBUFF];
	sprintf_s(keyWord, "keyword1");
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
	char keyValue[CHARBUFF];
	if (GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile) != 0) {
		fprintf(stdout, "%s , %s\n", settingFile, keyValue);
	}
	else {
		fprintf(stdout, "%s doesn't contain [$s] %s\n", settingFile, section, keyWord);
	}
	//iniファイルの読み込み終了

	FILE* fp;		//出力用のファイルをresultを開く
	errno_t error;
	//ファイルの出力
	error = fopen_s(&fp, "result.csv", "w");

	int  x, y, w, h;
	int judge1 = 1;	//ゲーム回数を判断する

jump_again:		//ゲームをもう一度遊ぶ際のjump地点
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, h, w);
	y = h / 2;			//画面の中央のy軸の点
	x = w / 2;			//画面の中央のx軸の点

	//最初のルール説明を表示　開始
	move(y - 10, x - 4);
	addstr("Hit & Blow");
	move(y + 2, 1);
	addstr("Hit & Blow is a guessing game.");
	move(y + 3, 1);
	addstr("The player tries to guess a secret code of digits. ");
	move(y + 4, 1);
	addstr("The number of digits in the secret number is 4.");
	move(y + 5, 1);
	addstr("If a guessed digit is both in the correct position and correct value, it's a Hit.");
	move(y + 6, 1);
	addstr("If a digit is correct but in the wrong position, it's a Blow.");
	move(y + 7, 1);
	addstr("You have 5 chances.");
	move(y + 8, 1);
	addstr("Lets Try.");
	move(y + 9, 1);
	addstr("push q START.");
	//終了

	while (1) {				//タイトル画面からqを押すとゲーム画面へ移動
		int key;
		key = getch();
		if (key == 'q') {
			break;
		}
	}
	erase();

	char answer[NUM_DIGIT];		//正解の４桁を格納する配列
	int num_hit, num_blow;		//hit数、blow数を格納する配列

	srand((unsigned int)time(NULL));		//現在時刻から乱数を生成

	/* 1.正解を用意する */
	char nums[] = {
		'6', '1', '2', '3', '4',
		'5' };

	int num_num = sizeof(nums) / sizeof(nums[0]);	//nums配列の要素数

	shuffle(nums, num_num);					//shuffle関数を用いてnims配列を混ぜてanswr配列に代入
	for (int i = 0; i < NUM_DIGIT; i++) {
		answer[i] = nums[i];
	}

	/*	答え
	move(y , (x / 3) - 2);
	attrset(COLOR_PAIR(0));
	printw("%d", answer[0]);
	move(y+1, (x / 3) - 2);
	printw("%d", answer[1]);
	move(y+2, (x / 3) - 2);
	printw("%d", answer[2]);
	move(y+3, (x / 3) - 2);
	printw("%d", answer[3]);
	*/

	start_color();		//色の設定
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_BLUE, COLOR_BLUE);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);
	init_pair(4, COLOR_CYAN, COLOR_CYAN);
	init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(7, COLOR_BLACK, COLOR_BLACK);

	//ゲーム画面の説明表示　開始
	move(1, w - 17);
	addstr("name:");
	move(1, w - 10);
	printw("%s", keyValue);
	move(1, x - 5);
	addstr("SELECT COLOR");
	move(3, x - 10);
	addstr("you have 5 chances.");
	move(5, x - 10);
	addstr("push 1～6 change color.");
	move(6, x - 10);
	addstr("push ↑、↓ change place.");
	move(7, x - 10);
	addstr("push Enter decide colors.");
	move(8, x - 10);
	addstr("H = Hit , B = Blow");

	move(y, x / 3 + 2);
	addstr("←");
	move(y, x / 3 - 5);
	addstr("1");
	move(y + 2, x / 3 - 5);
	addstr("2");
	move(y + 4, x / 3 - 5);
	addstr("3");
	move(y + 6, x / 3 - 5);
	addstr("4");

	move(y - 5, x / 3 - x / 6);
	attrset(COLOR_PAIR(0));
	addstr("1:");
	move(y - 5, x / 3 - x / 6 + 2);
	attrset(COLOR_PAIR(1));
	addstr("　");

	move(y - 5, 2 * x / 3 - x / 6);
	attrset(COLOR_PAIR(0));
	addstr("2:");
	move(y - 5, 2 * x / 3 - x / 6 + 2);
	attrset(COLOR_PAIR(2));
	addstr("　");

	move(y - 5, 3 * x / 3 - x / 6);
	attrset(COLOR_PAIR(0));
	addstr("3:");
	move(y - 5, 3 * x / 3 - x / 6 + 2);
	attrset(COLOR_PAIR(3));
	addstr("　");

	move(y - 5, 4 * x / 3 - x / 6);
	attrset(COLOR_PAIR(0));
	addstr("4:");
	move(y - 5, 4 * x / 3 - x / 6 + 2);
	attrset(COLOR_PAIR(4));
	addstr("　");

	move(y - 5, 5 * x / 3 - x / 6);
	attrset(COLOR_PAIR(0));
	addstr("5:");
	move(y - 5, 5 * x / 3 - x / 6 + 2);
	attrset(COLOR_PAIR(5));
	addstr("　");

	move(y - 5, 6 * x / 3 - x / 6);
	attrset(COLOR_PAIR(0));
	addstr("6:");
	move(y - 5, 6 * x / 3 - x / 6 + 2);
	attrset(COLOR_PAIR(6));
	addstr("　");
	//終了

	int count = y;	//↑、↓押して動く判定
	int judge = 0;	//エラー処理をを行ったか判断する　１でエラー
	for (int a = 1; a < 6; a++) {	//ゲームを5回繰り返すためのfor文
		while (1) {
		jump_label:			//エラー発生の際のjump地点
			int key = getch();
			if (judge == 1) {	//エラーが発生した場合警告文の消去する
				move(y + 8, x);
				attrset(COLOR_PAIR(7));
				addstr("　　　　　　　　　　　　　　　　　　　　");
				judge = 0;
			}

			if (key == KEY_UP) {	//↑が押された場合対象の場所を上にずらす
				move(count, x * a / 3 + 2);	//前回の←を消す
				attrset(COLOR_PAIR(7));
				addstr("　");

				count = count - 2;	//上にずらす
				if (count == y - 2) {
					count = y;
				}
				move(count, x * a / 3 + 2);	//対象の場所の右に←を表示
				attrset(COLOR_PAIR(0));
				addstr("←");
			}

			if (key == KEY_DOWN) {		//KEY_UPとほぼ同じ処理
				move(count, x * a / 3 + 2);
				attrset(COLOR_PAIR(7));
				addstr("　");

				count = count + 2;

				if (count == y + 8) {
					count = y + 6;
				}
				move(count, x * a / 3 + 2);
				attrset(COLOR_PAIR(0));
				addstr("←");
			}

			if (key == '1') {		//1が押されたら指定の場所を赤にする
				move(count, x * a / 3);
				attrset(COLOR_PAIR(1));
				addstr("　");
			}

			if (key == '2') {		//2なら青
				move(count, x * a / 3);
				attrset(COLOR_PAIR(2));
				addstr("　");
			}

			if (key == '3') {		//3なら緑
				move(count, x * a / 3);
				attrset(COLOR_PAIR(3));
				addstr("　");
			}

			if (key == '4') {		//4ならシアン
				move(count, x * a / 3);
				attrset(COLOR_PAIR(4));
				addstr("　");
			}

			if (key == '5') {		//５なら黄色
				move(count, x * a / 3);
				attrset(COLOR_PAIR(5));
				addstr("　");
			}

			if (key == '6') {		//6ならマゼンタ
				move(count, x * a / 3);
				attrset(COLOR_PAIR(6));
				addstr("　");
			}

			if (key == '\n') {		//Enterを押すと色を決定しwhileを抜ける
				move(count, x * a / 3 + 2);
				attrset(COLOR_PAIR(7));
				addstr("←");
				break;
			}

		}
		char input[4];	//プレイヤーの入力を格納する配列
		for (int A = 0; A < 4; A++) {		//色を塗った場所のペア番号から値を入手し代入
			attr_t attr = mvwinch(stdscr, y + A * 2, x * a / 3);
			short pair;
			pair = PAIR_NUMBER(attr) + 48;	//charで宣言してしまったためASCIIコードから+48
			input[A] = pair;
		}

		for (int B = 0; B < 4; B++) {		//入力された番号が今回の1-6(49-54)であった場合（エラー処理）
			if (input[B] < 49 || input[B] > 54) {
				move(y + 8, x);
				attrset(COLOR_PAIR(0));
				addstr("色が４つ選択されていません。もう一度");	//発生するのは"　"の場合のみ
				judge = 1;
				goto jump_label;	//211行目へ
			}
		}

		if (!is_allDifferent(input, NUM_DIGIT)) {	//重複のエラー処理
			move(y + 8, x);
			attrset(COLOR_PAIR(0));
			addstr("同じ文字が入力されています。もう一度");
			judge = 1;
			goto jump_label;	//211へ
		}

		num_hit = countHit(answer, input, NUM_DIGIT);	//hit数の入手
		num_blow = countBlow(answer, input, NUM_DIGIT);		//blow数の入手
		//hit数とblow数の表示　開始
		move(y - 3, (x * a / 3) - 2);
		attrset(COLOR_PAIR(0));
		printw("%dH %dB", num_hit, num_blow);
		//終了

		num[a - 1] = { input[0] - 48,input[1] - 48 ,input[2] - 48 ,input[3] - 48,num_hit,num_blow };	//構造体に今回のあなたの回答とhit数blow数を入れる

		if (num_hit == NUM_DIGIT) {	//ヒット数と答えの桁数が同じ（クリアした場合）
			erase();				//画面を消去しファイルの出力を行う
			move(y, x);
			attrset(COLOR_PAIR(0));
			addstr("clear");

			if (error != 0) {
				fprintf_s(stderr, "failed to open");
				return 1; // エラーコード1を返してプログラムを終了
			}
			if (judge1 == 1) {
				fputs("Result of Hit & Blow ", fp);
				fprintf(fp, " name:%s\n", keyValue);
			}
			//fputs("Result of Hit & Blow  \n", fp);
			//fprintf(fp, "　%d回目のゲーム　name:%s \n",judge1,keyValue);
			fprintf(fp, "　%d回目のゲーム　 \n", judge1);
			int A;
			for (int A = 0; A < a; A++) {
				fprintf(fp, "%d回目の入力した数字は,%d,%d,%d,%d \n", A + 1, num[A].num1, num[A].num2, num[A].num3, num[A].num4);
				fprintf(fp, "%d回目のHit数とBlow数は,%d,%d\n", A + 1, num[A].hit, num[A].blow);
			}
			fprintf(fp, "成功\n");
			goto jump_end;	//380へ
		}
		//５回行い失敗した場合 ファイルの主力を行う
		if (a == 5) {
			if (error != 0) {
				fprintf_s(stderr, "failed to open");
				return 1; // エラーコード1を返してプログラムを終了
			}
			if (judge1 == 1) {
				fputs("Result of Hit & Blow ", fp);
				fprintf(fp, " name:%s\n", keyValue);
			}
			//fputs("Result of Hit & Blow  \n", fp);
			//fprintf(fp, "　%d回目のゲーム　name:%s \n",judge1,keyValue);
			fprintf(fp, "　%d回目のゲーム　 \n", judge1);
			int A;
			for (int A = 0; A < a; A++) {
				fprintf(fp, "%d回目の入力した数字は,%d,%d,%d,%d \n", A + 1, num[A].num1, num[A].num2, num[A].num3, num[A].num4);
				fprintf(fp, "%d回目のHit数とBlow数は,%d,%d\n", A + 1, num[A].hit, num[A].blow);
			}
			fprintf(fp, "失敗\n");
		}
	}

	erase();
	move(y, x - 5);
	attrset(COLOR_PAIR(0));
	addstr("Game Over");	//game overの表示
jump_end:
	//リトライの説明
	move(y + 2, x - 20);
	attrset(COLOR_PAIR(0));
	addstr("The answer will change in the next game");
	move(y + 4, x - 8);
	addstr("again → push  a");
	move(y + 6, x - 8);
	addstr("end → push  buttons other than a");

	int key = getch();
	if (key == 'a') {	//aを押したらもう一度 again
		judge1 = judge1 + 1;
		erase();
		goto jump_again;	//57行目へ
	}
	endwin();
	return(0);
}
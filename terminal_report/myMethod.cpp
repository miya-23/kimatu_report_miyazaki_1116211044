#include "myMethod.h"

/***************************
 * 数字の並びをシャッフルする
 * nums[in,out]:数字が格納される配列
 * num_num[in]:数字の枚数
 * *************************/
void shuffle(char nums[], int num_num) {
	int i, j;
	char tmp;

	/* シャッフル対象の末尾を設定 */
	i = num_num - 1;

	while (i > 0) {
		/* シャッフル対象(0〜i)から位置をランダム決定 */
		j = rand() % (i + 1);

		/* ランダムに決めた位置と
		   シャッフル対象の末尾の位置のデータを交換 */
		tmp = nums[j];
		nums[j] = nums[i];
		nums[i] = tmp;

		/* シャッフル対象の範囲を狭める */
		i--;
	}
}

/***************************
 * Hit数を数える
 * input[in]:入力された数が格納された配列
 * answer[in]:正解の数が格納された配列
 * num_digit[in]:数の桁数
 * 返却値：Hit数
 * *************************/
int countHit(char input[], char answer[], int num_digit) {
	int num_hit = 0;

	for (int i = 0; i < num_digit; i++) {
		for (int j = 0; j < num_digit; j++) {
			if (answer[i] == input[j]) {
				if (i == j) {
					num_hit++;
				}
			}
		}
	}

	return num_hit;
}

/***************************
 * Blow数を数える
 * input[in]:入力された数が格納された配列
 * answer[in]:正解の数が格納された配列
 * num_digit[in]:数の桁数
 * 返却値：Blow数
 * *************************/
int countBlow(char input[], char answer[], int num_digit) {

	int num_blow = 0;

	for (int i = 0; i < num_digit; i++) {
		for (int j = 0; j < num_digit; j++) {
			if (answer[i] == input[j]) {
				if (i != j) {
					num_blow++;
				}
			}
		}
	}

	return num_blow;
}

/***************************
 * 入力された文字が重複していないかを判断する
 * input_str[in]:入力された文字が格納された配列
 * len[in]:文字数
 * 返却値：1（全ての文字が重複していない場合）
 *      ：0（それ以外）
 * *************************/
int is_allDifferent(char input_str[], int len) {
	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j < len; j++) {
			if (input_str[i] == input_str[j]) {
				return 0;
			}
		}
	}
	return 1;
}
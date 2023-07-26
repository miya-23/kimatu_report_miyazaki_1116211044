#pragma once
#pragma once
#ifndef MYMETHOD_H  // 重複インクルードを防ぐため
#define MYMETHOD_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void shuffle(char nums[], int num_num);
int countHit(char input[], char answer[], int num_digit);
int countBlow(char input[], char answer[], int num_digit);
int is_allDifferent(char input_str[], int len);

#endif
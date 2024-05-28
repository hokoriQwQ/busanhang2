//2-1 정리 못함
//2-2 완료
//2-3 완료
//2-4 좀비 붙들기 못함

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<Windows.h>

//파라미터
#define LEN_MIN 15 //기차 길이
#define LEN_MAX 50
#define STM_MIN 0 //마동석 체력
#define STM_MAX 5
#define PROB_MIN 10 //확률
#define PROB_MAX 90
#define AGGRO_MIN 0
#define AGGRO_MAX 5

//마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

//좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

//마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

int intro() {
	printf("		             ___________________________________\n");
	printf("        /_\\_____/|\\ |__||__|   |______________]_[__|-------------|\n");
	printf("   ____/__/|_|_| | \\     --------------------------|-------------|\n");
	printf("   |\\   \\_________|__\\    \\          8606            \\|||||||||||/|\n");
	printf("     | \\            |        \\                                     ||\n");
	printf("   |  | |\\___________|_________\\                         [] [] [] []|| |\n");
	printf("   |__|_|____________|______________________________________________||_|\n");
	printf("  _|__|  ______________  |_______________________|  ______________  |__|_\n");
	printf(" |_|__| (______________) |_______________________| (______________) |__|_|\n");
	printf("__/______(__)_(__)_(__)_____________________________(__)_(__)_(__)______\\___\n\n");
	printf("			Seoul-------------->Busan\n\n");
	return 0;
}

int train_first(int len, int cv, int zb,int md) {

	int plus_train = 0, minus_train = 1;

	for (int i = 0; i < len; i++) printf("#");
	//---------------------------------------------------------------------------------
	printf("\n#");
	for (int i = 0; i < cv - minus_train; i++) printf(" ");
	printf("C");
	for (int i = 0; i < zb - cv - 1 + plus_train; i++) printf(" ");
	printf("Z");
	for (int i = 0; i < md - zb - minus_train; i++) printf(" ");
	printf("M");
	
	printf("#\n");
	//---------------------------------------------------------------------------------
	for (int i = 0; i < len; i++) printf("#");
	printf("\n\n\n\n");
	return 0;
}
int train_md(int len, int cv, int zb, int md,int md2) {

	int plus_train = 0, minus_train = 1;

	for (int i = 0; i < len; i++) printf("#");
	//---------------------------------------------------------------------------------
	printf("\n#");
	for (int i = 0; i < cv - minus_train; i++) printf(" ");
	printf("C");
	for (int i = 0; i < zb - cv - 1 + plus_train; i++) printf(" ");
	printf("Z");
	for (int i = 0; i < md - zb-1; i++) printf(" ");
	printf("M");
	for (int i = 0; i < md2-md; i++) printf(" ");

	printf("#\n");
	//---------------------------------------------------------------------------------
	for (int i = 0; i < len; i++) printf("#");
	printf("\n\n\n");
	return 0;
}
int md_rest(int md, int md_aggro2, int md_aggro, int md_st2, int md_st) {
	printf("madongseok rests...\n\n");
	printf("madongseok: % d(aggro : % d -> % d, stamina : % d -> % d)\n\n\n", md, md_aggro2, md_aggro, md_st2, md_st);
	return 0;
}
int train_turn1(int len, int cv, int zb, int md) {
	for (int i = 0; i < len; i++) printf("#");
	printf("\n#");
	for (int i = 0; i < cv - 1; i++) printf(" ");
	printf("C");
	for (int i = 0; i < zb - cv - 1 + 0; i++) printf(" ");
	printf("Z");
	for (int i = 0; i < md - zb - 1; i++) printf(" ");
	printf("M");
	printf("#\n");
	for (int i = 0; i < len; i++) printf("#");
	printf("\n\n\n\n");
	return 0;
}
int md_pv(int md,int md_aggro2, int md_aggro,int md_st) {
	printf("madongseok provoked zombie...\n\n");
	printf("madongseok: %d (aggro: %d -> %d, stamina: %d)\n\n\n)", md, md_aggro2, md_aggro, md_st);
	return 0;
}

int main() {
	srand((unsigned int)time(NULL));
	//인트로

	intro();
	//Sleep(4000);

	//게임시작
	int len, pb, md_st, cv_aggro = 1, md_aggro = 1, turn = 1, m_move, m_act;
	int cv_aggro2 = cv_aggro, md_aggro2 = md_aggro;
	int cv, zb, md, train;
	int cv2, zb2, md2, train2, md_st2;

	while (1) {
		printf("train length(15~50)>> ");
		scanf_s("%d", &len);
		if (len >= LEN_MIN && len <= LEN_MAX) break;
	}
	while (1) {
		printf("madongseok stamina(0~5)>> ");
		scanf_s("%d", &md_st);
		if (md_st >= STM_MIN && md_st <= STM_MAX) break;
	}
	while (1) {
		printf("percentile probability 'p'(10~90)>> ");
		scanf_s("%d", &pb);
		if (pb >= PROB_MIN && pb <= PROB_MAX) break;
	}

	printf("\n\n");
	//기차안
	train = len - 2; //열차길이-2 13

	// 시민
	cv = len - 6; //열차길이-6 9

	// 좀비
	zb = len - 3; //열차길이-3 12

	// 마동석
	md = len - 2; //열차길이-2 13

	int minus_train = 1, plus_train = 0;

	cv2 = cv;
	zb2 = zb;
	md2 = md;
	md_st2 = md_st;
	train2 = train;
	//열차 초기상태
	train_first(len, cv, zb, md);
	//열차출발
	while (1) {
		int percent = rand() % 100;

		if (turn % 2 != 0) {//2번째턴 아님
			if (percent < 100 - pb) {//동작 동작
				if (percent < 100 - (100 - pb)) {
					cv_aggro++;
					if (cv_aggro > AGGRO_MAX) cv_aggro = cv_aggro - 1;
					cv--;
					if (cv_aggro >= md_aggro) zb--;
					else if (md_aggro > cv_aggro && md - zb == 1);
					else zb++;
					train_md(len, cv, zb, md, md2);
					printf("citizen: %d -> %d (aggro: %d)\n", cv2, cv, cv_aggro);
					printf("zombie: %d -> %d\n\n", zb2, zb);
					cv2 = cv;
					zb2 = zb;
					cv_aggro2 = cv_aggro;
				}
				else {//동작 대기
					cv_aggro++;
					if (cv_aggro > AGGRO_MAX) cv_aggro = cv_aggro - 1;
					cv--;
					train_md(len, cv, zb, md, md2);
					printf("citizen: %d -> %d (aggro: %d)\n", cv2, cv, cv_aggro);
					printf("zombie: (stay) %d\n\n", zb);
					cv2 = cv;
					cv_aggro2 = cv_aggro;
				}
			}
			else {
				if (percent < 100 - (100 - pb)) {//대기 동작
					cv_aggro--;
					if (cv_aggro < AGGRO_MIN) cv_aggro = cv_aggro + 1;
					else if (md_aggro > cv_aggro && md - zb == 1);
					else if (md - zb == 0);
					else zb++;
					train_md(len, cv, zb, md, md2);
					printf("citizen: (stay) %d (aggro: %d -> %d)\n", cv, cv_aggro2, cv_aggro);
					printf("zombie: %d -> %d\n\n", zb2, zb);
					zb2 = zb;
					cv_aggro2 = cv_aggro;
				}
				else {//대기 대기
					cv_aggro--;
					if (cv_aggro < AGGRO_MIN) cv_aggro = cv_aggro + 1;
					train_md(len, cv, zb, md, md2);
					printf("citizen: (stay) %d (aggro: %d -> %d)\n", cv, cv_aggro2, cv_aggro);
					printf("zombie:  (stay) %d\n\n", zb);
					cv_aggro2 = cv_aggro;
				}
			}
		}

		else {//2번째턴
			if (percent < 100 - pb) {//동작 못움직임
				cv_aggro++;
				if (cv_aggro > AGGRO_MAX) cv_aggro = cv_aggro - 1;
				cv--;
				train_md(len, cv, zb, md, md2);
				printf("citizen: %d -> %d (aggro: %d)\n", cv2, cv, cv_aggro);
				printf("zombie: (cannot move) %d\n\n", zb);
				cv2--;
				cv_aggro2 = cv_aggro;
			}
			else {//대기 못움직임
				cv_aggro--;
				if (cv_aggro < AGGRO_MIN) cv_aggro = cv_aggro + 1;
				train_md(len, cv, zb, md, md2);
				printf("citizen: (stay) %d (aggro: %d -> %d)\n", cv, cv_aggro2, cv_aggro);
				printf("zombie: (cannot move) %d\n\n", zb);
				cv_aggro2 = cv_aggro;
			}
		}
		if (turn % 2 == 0) {
			//마동석 움직임결정
			while (1) {
				if (md - zb == 1) {//좀비랑 붙어있음
					printf("madongseok move(0:stay)>> ");
					scanf_s("%d", &m_move);
					if (m_move == 0) break;
				}
				else {//안붙어있음
					printf("madongseok move(0:stay, 1:left)>> ");
					scanf_s("%d", &m_move);
					if (m_move == 0 || m_move == 1) break;
				}
			}
			printf("\n");
			//마동석 움직임
			if (m_move == 1) {
				md_aggro++;
				md--;
				train_md(len, cv, zb, md, md2);
				md_aggro2 = md_aggro;
			}
			//마동석 안움직임
			if (m_move == 0) {
				md_aggro--;
				if (md_aggro < AGGRO_MIN) md_aggro = md_aggro + 1;
				train_md(len, cv, zb, md, md2);
				printf("madongseok: stay %d(aggro : %d -> %d, stamina : %d)\n\n", md, md_aggro2, md_aggro, md_st);
				md_aggro2 = md_aggro;
			}
			//마동석 동작결정
			printf("citizen does nothing.\n");
			printf("zombie attcked nobody.\n");

			if (md - zb == 1) {
				while (1) {
					printf("madongseok action(0.rest, 1.provoke, 2. pull) >> ");
					scanf_s("%d", &m_act);
					if (m_act == 1 || m_act == 0||m_act==2) break;
				}
				switch (m_act)
				{
				case 0://휴식
					md_aggro--, md_st++;
					if (md_aggro < AGGRO_MIN) md_aggro = md_aggro + 1;
					if (md_st > STM_MAX) md_st = md_st - 1;
					md_rest(md, md_aggro2, md_aggro, md_st2, md_st);
					md_aggro2 = md_aggro, md_st2 = md_st;
					break;
				case 1://도발
					md_aggro = AGGRO_MAX;
					md_pv(md, md_aggro2, md_aggro, md_st);
					md_aggro2 = md_aggro;
					break;
				case 2://잡기
					md_aggro = md_aggro + 2;
					md_st--;
					if (md_aggro > AGGRO_MAX) md_aggro = md_aggro - (md_aggro - AGGRO_MAX);
					if (percent < 100 - pb){
						printf("madongseok pulled zombie... Next turn, it can't move\n\n");
						printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n\n\n", md, md_aggro2, md_aggro, md_st2, md_st);
					}
					else {
						printf("madongseok failed to pull zombie\n\n");
						printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n\n\n", md, md_aggro2, md_aggro, md_st2, md_st);
					}
					md_aggro2 = md_aggro;
					md_st2 = md_st;
					break;
				}
			}
			else {
				while (1) {
					printf("madongseok action(0.rest, 1.provoke) >> ");
					scanf_s("%d", &m_act);
					if (m_act == 1 || m_act == 0) break;
				}
				switch (m_act) {
				case 0://휴식
					md_aggro--, md_st++;
					if (md_aggro < AGGRO_MIN) md_aggro = md_aggro + 1;
					if (md_st > STM_MAX) md_st = md_st - 1;
					md_rest(md, md_aggro2, md_aggro, md_st2, md_st);
					md_aggro2 = md_aggro, md_st2 = md_st;
					break;
				case 1://도발
					md_aggro = AGGRO_MAX;
					md_pv(md, md_aggro2, md_aggro, md_st);
					md_aggro2 = md_aggro;
					break;
				}
			}
		}
			turn++;

			if (md_st < STM_MIN) {
				printf("GAME OVER! madongseok dead...!\n");
				break;
			}
			if (zb - cv - 1 + plus_train == 0) {
				printf("GAME OEVER! citizen dead...! \n");
				break;
			}
			if (cv == 1) {
				printf("SUCCESS!\n");
				printf("citizen(s) escaped to the next train\n");
				break;
			}
			//Sleep(4000);
		}
		//아웃트로

		return 0;

	}
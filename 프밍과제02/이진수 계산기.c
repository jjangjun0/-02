#include <stdio.h>

void B_transform(int binary_num);		//2진수 -> 10진수
int binary_add(int binary_num, int binary_num2);	// a+b
int binary_up_process(int binary_NUM);	// 올림처리
int binary_minus(int binary_num2);	// b -> -b

int main(void)
{
	int key_n, binary_num, binary_num2, x, y;
	printf("1. 이진수 변환기	2. 이진수 덧셈기	3. 이진수 뺄셈기\n\n");
	printf("번호를 선택하세요 : "); scanf_s("%d", &key_n);

	switch (key_n) {
	case 1:		// 1. 이진수 변환기
		printf("8비트 이진수를 입력하세요 : "); scanf_s("%d", &binary_num);
		B_transform(binary_num); // 2진수를 10진수로 출력
		break;

	case 2:		// 2. 이진수 덧셈기
		printf("첫 번째 8비트 이진수를 입력하세요 : "); scanf_s("%d", &binary_num);
		printf("두 번째 8비트 이진수를 입력하세요 : "); scanf_s("%d", &binary_num2);
		x = binary_add(binary_num, binary_num2);	// num+num2
		for (int i = 1; i <= 8; i++)
			x = binary_up_process(x);	// 올림처리 반복
		printf("두 이진수의 합은 %08d 이고, ", x);
		B_transform(x);	// 2진수를 10진수로 출력
		break;

	case 3:		// 3. 이진수 뺄셈기
		printf("첫 번째 8비트 이진수를 입력하세요 : "); scanf_s("%d", &binary_num);
		printf("두 번째 8비트 이진수를 입력하세요 : "); scanf_s("%d", &binary_num2);
		y = binary_minus(binary_num2);	// (-num2)
		x = binary_add(binary_num, y);	// num + (-num2)
		for (int i = 1; i <= 8; i++)
			x = binary_up_process(x);	// 올림처리 반복
		printf("두 이진수의 차는 %08d 이고, ", x);
		B_transform(x);	// 2진수를 10진수로 출력
		break;

	default:
		break;	// default는 else랑 비슷한 맥락으로 생략할 수 있다.
	}

	return 0;
}

void B_transform(int binary_num)
{
	int var, sum = 0, add2 = 1;
	int trans_n;
	trans_n = binary_num / 10000000;	// 위의 trans_n은 몫의 값이다.
	trans_n %= 10;		// 10으로 나눠 정수만 갖게 한다.
	//	printf("부호 비트 (1 : 음수, 0 : 양수)\ntrans_n = %d\n", trans_n);
	if (trans_n == 0) { 		// 십진수가 양수인 경우
		for (int i = 1; i <= 8; i++) {	// 각 자리에 해당하는 수 뽑아내기
			var = binary_num % 10;
			binary_num /= 10;
			// 2의 거듭제곱의 합으로 표현하기
			var *= add2;
			sum += var;
			add2 = add2 * 2;
		}
		printf("십진수로 %d 입니다.\n", sum);
	}
	else {	// 십진수가 음수인 경우
		for (int i = 1; i <= 8; i++) {
			if (i < 8) {
				var = binary_num % 10;
				binary_num /= 10;
				var *= add2;
				sum += var;
				add2 = add2 * 2;
			}
			else {
				var = binary_num % 10;
				binary_num /= 10;
				var *= add2;
				var *= -1;
				sum += var;
			}
		}
		printf("십진수로 %d 입니다.\n", sum);
	}
}

int binary_add(int binary_num, int binary_num2)
{
	int binary_sum;
	binary_sum = binary_num + binary_num2;	// sum = 0002 1212
	binary_sum = binary_up_process(binary_sum);		// 올림처리
	return binary_sum;
}

int binary_up_process(int binary_NUM)
{
	int temp_num1, mul_n1 = 2, mul_n2 = 10;
	temp_num1 = binary_NUM;	// temp = 0002 1212		// temp = 0002 122
	for (int i = 1; i <= 8; i++) {
		if (temp_num1 % 10 >= 2) {	// 1. temp % 10 = 2 >= 2	// 2. temp % 10 = 2 >= 2	// 3.
			binary_NUM -= mul_n1;	// 1. NUM = 0002 1210		// 2. NUM = 0002 1200
			binary_NUM += mul_n2;	// 1. NUM = 0002 1220		// 2. NUM = 0002 1300
			temp_num1 = temp_num1 + 10;	// 1. temp = 0002 1222	// 2. temp = 0002 132		

			// temp_num1 = temp_num1 + mul_n2;	
			// 아 여기서 오류 temp는 계속 10으로 나누니 +mul_n2가 아닌 +10으로 생각해야함
		}
		mul_n1 *= 10;	// 1. mul_n1 = 20	// 2. mul_n1 = 200
		mul_n2 *= 10;	// 1. mul_n2 = 100	// 2. mul_n2 = 1000
		temp_num1 /= 10;	// 1. temp_num1 = 0002 122	// 2. temp_num1 = 0002 13
	}
	if (binary_NUM >= 100000000) binary_NUM = binary_NUM % 100000000;	// 8비트만 받음
	return binary_NUM;
}

int binary_minus(int binary_num2)
{
	int temp_num, mul_n3 = 1;
	temp_num = binary_num2;	// temp = num2
	// num2의 1의 보수
	for (int i = 1; i <= 8; i++) {
		// 1. mul_n3 = 1	// 2. mul_n3 = 10	// 3. mul_n3 = 100
		if (temp_num % 10 == 1) binary_num2 = binary_num2 - mul_n3;	// 1 -> 0
		else binary_num2 = binary_num2 + mul_n3;	// 0 -> 1
		mul_n3 *= 10;	// 1. mul_n3 = 10		// 2. mul_n3 = 100
		temp_num /= 10;	// 1. temp = temp / 10	// 2. temp = temp / 10
	}
	// num2의 1의 보수 +1
	binary_num2 += 1;
	binary_num2 = binary_up_process(binary_num2);	// 올림처리
	return binary_num2;
}
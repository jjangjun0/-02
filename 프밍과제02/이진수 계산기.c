#include <stdio.h>

void B_transform(int binary_num);		//2���� -> 10����
int binary_add(int binary_num, int binary_num2);	// a+b
int binary_up_process(int binary_NUM);	// �ø�ó��
int binary_minus(int binary_num2);	// b -> -b

int main(void)
{
	int key_n, binary_num, binary_num2, x, y;
	printf("1. ������ ��ȯ��	2. ������ ������	3. ������ ������\n\n");
	printf("��ȣ�� �����ϼ��� : "); scanf_s("%d", &key_n);

	switch (key_n) {
	case 1:		// 1. ������ ��ȯ��
		printf("8��Ʈ �������� �Է��ϼ��� : "); scanf_s("%d", &binary_num);
		B_transform(binary_num); // 2������ 10������ ���
		break;

	case 2:		// 2. ������ ������
		printf("ù ��° 8��Ʈ �������� �Է��ϼ��� : "); scanf_s("%d", &binary_num);
		printf("�� ��° 8��Ʈ �������� �Է��ϼ��� : "); scanf_s("%d", &binary_num2);
		x = binary_add(binary_num, binary_num2);	// num+num2
		for (int i = 1; i <= 8; i++)
			x = binary_up_process(x);	// �ø�ó�� �ݺ�
		printf("�� �������� ���� %08d �̰�, ", x);
		B_transform(x);	// 2������ 10������ ���
		break;

	case 3:		// 3. ������ ������
		printf("ù ��° 8��Ʈ �������� �Է��ϼ��� : "); scanf_s("%d", &binary_num);
		printf("�� ��° 8��Ʈ �������� �Է��ϼ��� : "); scanf_s("%d", &binary_num2);
		y = binary_minus(binary_num2);	// (-num2)
		x = binary_add(binary_num, y);	// num + (-num2)
		for (int i = 1; i <= 8; i++)
			x = binary_up_process(x);	// �ø�ó�� �ݺ�
		printf("�� �������� ���� %08d �̰�, ", x);
		B_transform(x);	// 2������ 10������ ���
		break;

	default:
		break;	// default�� else�� ����� �ƶ����� ������ �� �ִ�.
	}

	return 0;
}

void B_transform(int binary_num)
{
	int var, sum = 0, add2 = 1;
	int trans_n;
	trans_n = binary_num / 10000000;	// ���� trans_n�� ���� ���̴�.
	trans_n %= 10;		// 10���� ���� ������ ���� �Ѵ�.
	//	printf("��ȣ ��Ʈ (1 : ����, 0 : ���)\ntrans_n = %d\n", trans_n);
	if (trans_n == 0) { 		// �������� ����� ���
		for (int i = 1; i <= 8; i++) {	// �� �ڸ��� �ش��ϴ� �� �̾Ƴ���
			var = binary_num % 10;
			binary_num /= 10;
			// 2�� �ŵ������� ������ ǥ���ϱ�
			var *= add2;
			sum += var;
			add2 = add2 * 2;
		}
		printf("�������� %d �Դϴ�.\n", sum);
	}
	else {	// �������� ������ ���
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
		printf("�������� %d �Դϴ�.\n", sum);
	}
}

int binary_add(int binary_num, int binary_num2)
{
	int binary_sum;
	binary_sum = binary_num + binary_num2;	// sum = 0002 1212
	binary_sum = binary_up_process(binary_sum);		// �ø�ó��
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
			// �� ���⼭ ���� temp�� ��� 10���� ������ +mul_n2�� �ƴ� +10���� �����ؾ���
		}
		mul_n1 *= 10;	// 1. mul_n1 = 20	// 2. mul_n1 = 200
		mul_n2 *= 10;	// 1. mul_n2 = 100	// 2. mul_n2 = 1000
		temp_num1 /= 10;	// 1. temp_num1 = 0002 122	// 2. temp_num1 = 0002 13
	}
	if (binary_NUM >= 100000000) binary_NUM = binary_NUM % 100000000;	// 8��Ʈ�� ����
	return binary_NUM;
}

int binary_minus(int binary_num2)
{
	int temp_num, mul_n3 = 1;
	temp_num = binary_num2;	// temp = num2
	// num2�� 1�� ����
	for (int i = 1; i <= 8; i++) {
		// 1. mul_n3 = 1	// 2. mul_n3 = 10	// 3. mul_n3 = 100
		if (temp_num % 10 == 1) binary_num2 = binary_num2 - mul_n3;	// 1 -> 0
		else binary_num2 = binary_num2 + mul_n3;	// 0 -> 1
		mul_n3 *= 10;	// 1. mul_n3 = 10		// 2. mul_n3 = 100
		temp_num /= 10;	// 1. temp = temp / 10	// 2. temp = temp / 10
	}
	// num2�� 1�� ���� +1
	binary_num2 += 1;
	binary_num2 = binary_up_process(binary_num2);	// �ø�ó��
	return binary_num2;
}
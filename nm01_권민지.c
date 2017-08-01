//��ǻ���к� 2015117662 �ǹ���
#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <math.h>

#define MAX_TERMS 100
#pragma warning(disable : 4996)


typedef struct{
	float coef;
	int expon;
}term;
//���׽��� ������ ����ü
term terms[MAX_TERMS];

float f(int start, int finish, float x);
void bisection(float *x, float xl, float xu, int *itr);
void newton(int start, int finish, float x0);

int main()
{
	int i, numA;
	int startP, finishP;
	float xl, xu;
	float x0;
	float temp;
	int itr = 0;
	float x, x1;

	//������ ���� �о ���׽��� �����
	FILE *fin = fopen("in.txt", "r");

	fscanf(fin, "%f %f %f", &xl, &xu, &x0);
	fscanf(fin, "%d", &numA);

	startP = 0;
	finishP = numA - 1;

	for (i = startP; i <= finishP; i++)
		fscanf(fin, "%f %d", &terms[i].coef, &terms[i].expon);

	//���׽��� �� ����Ǿ����� Ȯ���ϱ� ���� ����غ�
	//printf("P(x) = ");
	/*for (i = startP; i <= finishP; i++)
	{
	if (i == finishP && terms[i].expon == 0)
	printf("%.0f\n", terms[i].coef);
	else if (i == finishP && terms[i].expon != 0)
	printf("%.0fx^%d", terms[i].coef, terms[i].expon);
	else
	printf("%.0fx^%d + ", terms[i].coef, terms[i].expon);
	}
	*/

	//f(xl)*f(xu) > 0�̸� xl�� xu���̿� ���� ���� ���� �����Ƿ� ���и޼����� ����
	if (f(startP, finishP, xl) * f(startP, finishP, xu) > 0)
		printf("Bisection : Failed\n");

	else {
		//ù��° bisection �ǽ�
		bisection(&x, xl, xu, &itr);

		do
		{   //ù��° �ǽõ� bisection�� ���� ���� x���� xl���̿� ���� ������ xu = x
			if (f(startP, finishP, xl)*f(startP, finishP, x) < 0)
				xu = x;
			//f(x)=0 �� �߱��϶�
			else if (f(startP, finishP, xl)*f(startP, finishP, x) == 0) {
				xu = x;
				xl = x;
			}
			// x�� xu���̿� ���� ���� ��
			else
				xl = x;

			bisection(&x1, xl, xu, &itr);
			//approximation error��  threshold���� �� �� ���� bisection�ݺ�
			if (fabs(x1 - x) / x1 <= 0.00001)
			{
				printf("Bisection : %f ( %d iterations )\n", x1, itr);
				break;
			}
			x = x1;
		}

		while (itr < 10000000);

	}

	newton(startP, finishP, x0);

	return 0;
}

//�Լ� ���� ����ϴ� �Լ�
float f(int start, int finish, float x)
{
	int i;
	float sum = 0;

	for (i = start; i <= finish; i++)
	{
		if (terms[i].expon == 0)
			sum = sum + terms[i].coef;

		else
			sum = sum + (terms[i].coef * (float)pow((double)x, (double)terms[i].expon));
	}

	return sum;
}

//bisetion �ǽ��ϴ� �Լ�
void bisection(float *x, float xl, float xu, int *itr) {

	*x = (xl + xu) / 2; //�߰����� ã�� �ǽ��Ҷ����� itr�� ������Ų��
	++(*itr);

	if (xl == xu)
		--(*itr);

}

//newton-raphson�� �ǽ��ϴ� �Լ�
void newton(int start, int finish, float x0) {

	int cnt = 0;
	float fx1 = 0, fdx1 = 0; //fx1�� �Լ��� �����ϴ� ��, f'(x)�� �Լ��� ����
	int i;
	float temp = 0, temp2 = 0;

	do
	{
		cnt++;
		fx1 = fdx1 = 0;

		fx1 = f(start, finish, x0);

		//f'(x)�� �Լ��� ���
		for (i = start; i <= finish; i++)
		{
			fdx1 += terms[i].coef * (terms[i].expon*(float)pow((double)x0, (double)terms[i].expon - 1));
		}
		temp = temp2;
		temp2 = (x0 - (fx1 / fdx1));

		x0 = temp2;
		//approximation error�� threshold ���� �϶����� �ݺ�
	} while ((fabs(temp - x0) / temp) >= 0.00001);

	printf("Newton-Raphson : %f ( %d iterations )\n", temp, cnt);

}


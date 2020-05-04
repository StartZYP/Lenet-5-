#pragma once
#include<opencv2/opencv.hpp>
#include <windows.h>
#include<iostream>
#include<time.h>
#include<math.h>
#include <thread>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;
#define db double
int showPD;

//���ز���Ԫ
db input[32][32];      //32*32����
db z1[6][28][28];         //6��28*28����
db a1[6][28][28];         //6��28*28����

db z2[6][14][14];      //6��14*14����

db z3[16][10][10];     //16��10*10����
db a3[16][10][10];     //16��10*10����

db z4[16][5][5];      //16��5*5����
db z4_dimReduc[400];  //һά���������ȫ����

db z5[120];
db a5[120];

db z6[84];
db a6[84];

db a7[10];
db z7[10];

db output[10];
int maxPi;

db w1[6][5][5];        //6��5*5�����
db b1[6];

db w3[16][5][5];      //16��5*5�����
db b3[16];

db w5[120][400];   //120*400������
db b5[120];

db w6[84][120];      //84*120������
db b6[84];

db w7[10][84];       //10*84������


//���򴫲��м�ֵ   

db J;//��ʧ����
db pd7[10];
db pd6[84];
db pd5[120];
db pd4[16][5][5];
db pd3[16][10][10];
db pd2[6][14][14];
db pd1[6][28][28];


db pd7_w[10][84];

db pd6_w[84][120];
db pd6_b[84];

db pd5_w[120][400];
db pd5_b[120];

db pd3_w[16][5][5];
db pd3_b[16];

db pd1_w[6][5][5];
db pd1_b[6];

double LearnProcess;
db leaky = 0.2;
//����

void lenet();
void init();
void setInput(int _input[28][28]);
void forward();
void backward();

//part
void fw_INtoL1();
void fw_L1toL2();
void fw_L2toL3();
void fw_L3toL4();
void fw_L4toL5();
void fw_L5toL6();
void fw_L6toL7();
void bw_L7();
void bw_L6();
void bw_L5();
void bw_L4();
void bw_L3();
void bw_L2();
void bw_L1();

void func(int inputN, int corN);
void func1(int inputN, int corN);
void visual();
db Max(db x1, db x2, db x3, db x4);
int maxP(db x1, db x2, db x3, db x4);




void lenet()
{
	srand((unsigned)time(NULL));

	//�����ʼ��Ȩֵ
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				w1[i][j][k] = rand() * (2. / RAND_MAX) - 1;
		b1[i] = rand() * (2. / RAND_MAX) - 1;
	}

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				w3[i][j][k] = rand() * (2. / RAND_MAX) - 1;
		b3[i] = rand() * (2. / RAND_MAX) - 1;
	}

	for (int i = 0; i < 120; i++)
	{
		for (int j = 0; j < 400; j++)
			w5[i][j] = rand() * (2. / RAND_MAX) - 1;
		b5[i] = rand() * (2. / RAND_MAX) - 1;
	}

	for (int i = 0; i < 84; i++)
	{
		for (int j = 0; j < 120; j++)
			w6[i][j] = rand() * (2. / RAND_MAX) - 1;
		b6[i] = rand() * (2. / RAND_MAX) - 1;
	}

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 84; j++)
			w7[i][j] = rand() * (2. / RAND_MAX) - 1;


	LearnProcess = 0.1;

}
void init()
{

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 28; j++)
			for (int k = 0; k < 28; k++)
			{
				z1[i][j][k] = 0;
				pd1[i][j][k] = 0;
			}
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 14; j++)
			for (int k = 0; k < 14; k++)
				pd2[i][j][k] = 0;


	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 10; k++)
			{
				z3[i][j][k] = 0;
				pd3[i][j][k] = 0;
			}
	for (int i = 0; i < 120; i++)
	{
		z5[i] = 0;
		pd5[i] = 0;
	}

	for (int i = 0; i < 84; i++)
	{
		z6[i] = 0;
		pd6[i] = 0;
	}

	for (int i = 0; i < 10; i++)
	{
		z7[i] = 0;
		pd7[i] = 0;
	}

	//��ʼ�������м�ֵ

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				pd1_w[i][j][k] = 0;
		pd1_b[i] = 0;
	}

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				pd3_w[i][j][k] = 0;
		pd3_b[i] = 0;
	}

	for (int i = 0; i < 120; i++)
	{
		for (int j = 0; j < 400; j++)
			pd5_w[i][j] = 0;
		pd5_b[i] = 0;
	}

	for (int i = 0; i < 84; i++)
	{
		for (int j = 0; j < 120; j++)
			pd6_w[i][j] = 0;
		pd6_b[i] = 0;
	}

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 84; j++)
			pd7_w[i][j] = 0;

}

void forward()
{
	init();//��ʼ�м�ֵ
	fw_INtoL1();
	fw_L1toL2();
	fw_L2toL3();
	fw_L3toL4();
	fw_L4toL5();
	fw_L5toL6();
	fw_L6toL7();


	db max = 0;
	for (int i = 0; i < 10; i++)
		if (a7[i] > max)
		{
			max = a7[i];
			maxPi = i;
		}

}
void fw_INtoL1()
{
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 28; j++)
			for (int k = 0; k < 28; k++)
			{
				for (int m = 0; m < 5; m++)
					for (int n = 0; n < 5; n++)
					{
						z1[i][j][k] += input[j + m][k + n] * w1[i][m][n];
					}
				z1[i][j][k] += b1[i];
				if (z1[i][j][k] > 0)
					a1[i][j][k] = z1[i][j][k];
				else
					a1[i][j][k] = leaky * z1[i][j][k];
			}
}
void fw_L1toL2()
{
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 14; j++)
			for (int k = 0; k < 14; k++)
			{
				z2[i][j][k] = Max(a1[i][j * 2][k * 2], a1[i][j * 2][k * 2 + 1], a1[i][j * 2 + 1][k * 2], a1[i][j * 2 + 1][k * 2 + 1]);
			}
}
void fw_L2toL3()
{

	//0�� 0 4 5 6 9 10 11 12 14 15
	func(0, 0); func(0, 4); func(0, 5); func(0, 6); func(0, 9);
	func(0, 10); func(0, 11); func(0, 12); func(0, 14); func(0, 15);
	//1��0 1 5 6 7 10 11 12 13 15
	func(1, 0); func(1, 1); func(1, 5); func(1, 6); func(1, 7); func(1, 10);
	func(1, 11); func(1, 12); func(1, 13); func(1, 15);
	//2��0 1 2 6 7 8 11 13 14 15
	func(2, 0); func(2, 1); func(2, 2); func(2, 6); func(2, 7);
	func(2, 8); func(2, 11); func(2, 13); func(2, 14); func(2, 15);
	//3��1 2 3 6 7 8 9 12 14 15
	func(3, 1); func(3, 2); func(3, 3); func(3, 6); func(3, 7);
	func(3, 8); func(3, 9); func(3, 12); func(3, 14); func(3, 15);
	//4��2 3 4 7 8 9 10 12 13 15
	func(4, 2); func(4, 3); func(4, 4); func(4, 7); func(4, 8);
	func(4, 9); func(4, 10); func(4, 12); func(4, 13); func(4, 15);
	//5��3 4 5 8 9 10 11 13 14 15
	func(5, 3); func(5, 4); func(5, 5); func(5, 8); func(5, 9);
	func(5, 10); func(5, 11); func(5, 13); func(5, 14); func(5, 15);

	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 10; k++)
			{
				z3[i][j][k] += b3[i];

				if (z3[i][j][k] > 0)
					a3[i][j][k] = z3[i][j][k];
				else
					a3[i][j][k] = leaky * z3[i][j][k];
			}
}
void fw_L3toL4()
{
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
			{
				z4[i][j][k] = Max(a3[i][j * 2][k * 2], a3[i][j * 2][k * 2 + 1], a3[i][j * 2 + 1][k * 2], a3[i][j * 2 + 1][k * 2 + 1]);
			}
}
void fw_L4toL5()
{
	//չ��z4���õ�400����Ԫ
	int p = 0;
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
			{
				z4_dimReduc[p++] = z4[i][j][k];
			}
	//����
	for (int i = 0; i < 120; i++)
	{
		for (int d = 0; d < 400; d++)
		{
			z5[i] += z4_dimReduc[d] * w5[i][d];
		}
		z5[i] += b5[i];
		if (z5[i] > 0)
			a5[i] = z5[i];
		else
			a5[i] = leaky * z5[i];
	}

}
void fw_L5toL6()
{

	for (int i = 0; i < 84; i++)
	{
		for (int d = 0; d < 120; d++)
			z6[i] += a5[i] * w6[i][d];

		z6[i] += b6[i];
	}
	db tMax = z6[0];
	for (int i = 0; i < 84; i++)
		if (a6[i] > tMax)
			tMax = a6[i];
	int Pow = log10(tMax);
	Pow = pow(10, Pow);
	for (int i = 0; i < 84; i++)
	{
		a6[i] = z6[i] / Pow;
		if (a6[i] > 0)
		{
			db ep = exp(-2 * a6[i]);
			a6[i] = 1.7159 * (1 - ep) / (1 + ep);
		}
		else
		{
			db ep = exp(2 * a6[i]);
			a6[i] = 1.7159 * (ep - 1) / (ep + 1);
		}
	}
}
void fw_L6toL7()
{
	for (int i = 0; i < 10; i++)
		for (int d = 0; d < 84; d++)
			z7[i] += (a6[d] - w7[i][d]) * (a6[d] - w7[i][d]) / 2;


	db SUM = 0;
	db tMax = 0;
	//�ҳ�z7����
	for (int i = 0; i < 10; i++)
		if (z7[i] > tMax)
			tMax = z7[i];
	for (int i = 0; i < 10; i++)
	{
		z7[i] -= tMax;
		SUM += exp(z7[i]);
	}

	for (int i = 0; i < 10; i++)
		a7[i] = exp(z7[i]) / SUM;
}


void backward()
{
	bw_L7();
	bw_L6();
	bw_L5();
	bw_L4();
	bw_L3();
	bw_L2();
	bw_L1();

}
void bw_L7()
{

	for (int i = 0; i < 10; i++)
		pd7[i] = (a7[i] - output[i]) * (a7[i] - a7[i] * a7[i]);

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 84; j++)
			pd7_w[i][j] = -pd7[i] * (a6[j] - w7[i][j]);


	//�鿴�м���
	if (showPD)
	{
		cout << "pd7:" << endl;
		for (int i = 0; i < 10; i++)
			cout << pd7[i] << endl;
		cout << "pd7_w:" << endl;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 84; j++)
				cout << pd7_w[i][j] << "  ";
			cout << endl;
		}


	}

}
void bw_L6()
{
	db _tPd6[84] = { 0 };
	for (int j = 0; j < 84; j++)
		for (int i = 0; i < 10; i++)
			_tPd6[j] += pd7[i] * (a6[j] - w7[i][j]);

	db tMax = z6[0];
	for (int i = 0; i < 84; i++)
		if (a6[i] > tMax)
			tMax = a6[i];
	int Pow = log10(tMax);
	Pow = pow(10, Pow);
	for (int j = 0; j < 84; j++)
	{
		int kjkj = -1;
		if (z6[j] > 0)
			kjkj = 1;
		pd6[j] = _tPd6[j] * (1.7159 - a6[j] * a6[j] / 1.7159) / Pow;

	}

	for (int i = 0; i < 84; i++)
	{
		for (int j = 0; j < 120; j++)
			pd6_w[i][j] = pd6[i] * a5[j];
		pd6_b[i] = pd6[i];
	}

	//�鿴�м���
	if (showPD)
	{
		cout << "_tPd6:" << endl;
		for (int j = 0; j < 84; j++)
			cout << _tPd6[j] << endl;
		cout << "pd6:" << endl;
		for (int j = 0; j < 84; j++)
			cout << pd6[j] << endl;

		cout << "pd6_w:" << endl;
		for (int i = 0; i < 84; i++)
		{
			for (int j = 0; j < 120; j++)
				cout << pd6_w[i][j] << " ";
			cout << endl;
		}
	}
}
void bw_L5()
{
	db _tPd5[120] = { 0 };
	for (int j = 0; j < 120; j++)
		for (int i = 0; i < 84; i++)
			_tPd5[j] += pd6[i] * w6[i][j];


	for (int j = 0; j < 120; j++)
	{
		if (z5[j] > 0)
			pd5[j] = _tPd5[j];
		else
			pd5[j] = _tPd5[j] * leaky;
	}
	for (int i = 0; i < 120; i++)
	{
		for (int j = 0; j < 400; j++)
			pd5_w[i][j] = pd5[i] * z4_dimReduc[j];
		pd5_b[i] = pd5[i];
	}

	//�鿴�м���
	if (showPD)
	{
		cout << "_tPd5:" << endl;
		for (int j = 0; j < 120; j++)
			cout << _tPd5[j] << endl;
		cout << "pd5:" << endl;
		for (int j = 0; j < 120; j++)
			cout << pd5[j] << endl;

		cout << "pd5_w:" << endl;
		for (int i = 0; i < 120; i++)
		{
			for (int j = 0; j < 400; j++)
				cout << setprecision(20) << pd5_w[i][j] << endl;
			cout << endl;
		}
	}
}
void bw_L4()
{
	db _tPd4[400] = { 0 };
	for (int j = 0; j < 400; j++)
		for (int i = 0; i < 120; i++)
			_tPd4[j] += pd5[i] * w5[i][j];

	int p = 0;
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				pd4[i][j][k] = _tPd4[p++];
}
void bw_L3()
{
	db _tPd3[16][10][10] = { 0 };
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
			{
				int p = maxP(a3[i][j * 2][k * 2], a3[i][j * 2][k * 2 + 1], a3[i][j * 2 + 1][k * 2], a3[i][j * 2 + 1][k * 2 + 1]);
				_tPd3[i][j * 2 + p / 2][k * 2 + p % 2] = pd4[i][j][k];
			}
	}
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 10; k++)
			{
				if (z3[i][j][k] > 0)
					pd3[i][j][k] = _tPd3[i][j][k];
				else
					pd3[i][j][k] = leaky * _tPd3[i][j][k];
			}
	}
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 10; k++)
				pd3_b[i] += pd3[i][j][k];


	
	

}
void bw_L2()
{
	//0�� 0 4 5 6 9 10 11 12 14 15
	func1(0, 0); func1(0, 4); func1(0, 5); func1(0, 6); func1(0, 9);
	func1(0, 10); func1(0, 11); func1(0, 12); func1(0, 14); func1(0, 15);
	//1��0 1 5 6 7 10 11 12 13 15
	func1(1, 0); func1(1, 1); func1(1, 5); func1(1, 6); func1(1, 7); func1(1, 10);
	func1(1, 11); func1(1, 12); func1(1, 13); func1(1, 15);
	//2��0 1 2 6 7 8 11 13 14 15
	func1(2, 0); func1(2, 1); func1(2, 2); func1(2, 6); func1(2, 7);
	func1(2, 8); func1(2, 11); func1(2, 13); func1(2, 14); func1(2, 15);
	//3��1 2 3 6 7 8 9 12 14 15
	func1(3, 1); func1(3, 2); func1(3, 3); func1(3, 6); func1(3, 7);
	func1(3, 8); func1(3, 9); func1(3, 12); func1(3, 14); func1(3, 15);
	//4��2 3 4 7 8 9 10 12 13 15
	func1(4, 2); func1(4, 3); func1(4, 4); func1(4, 7); func1(4, 8);
	func1(4, 9); func1(4, 10); func1(4, 12); func1(4, 13); func1(4, 15);
	//5��3 4 5 8 9 10 11 13 14 15
	func1(5, 3); func1(5, 4); func1(5, 5); func1(5, 8); func1(5, 9);
	func1(5, 10); func1(5, 11); func1(5, 13); func1(5, 14); func1(5, 15);
	

	if (showPD)
	{
		cout << endl << "pd3:" << endl;
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				for (int k = 0; k < 10; k++)
					cout << pd3[i][j][k] << " ";
				cout << endl;
			}
			cout << endl;
		}
		cout << endl << "pd3_w:" << endl;
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < 5; k++)
					cout << pd3_w[i][j][k] << " ";
				cout << endl;
			}
			cout << endl;
		}
	}
}
void bw_L1()
{
	db _tPd1[6][28][28] = { 0 };
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 14; j++)
			for (int k = 0; k < 14; k++)
			{
				int p = maxP(a1[i][j * 2][k * 2], a1[i][j * 2][k * 2 + 1], a1[i][j * 2 + 1][k * 2], a1[i][j * 2 + 1][k * 2 + 1]);
				_tPd1[i][j * 2 + p / 2][k * 2 + p % 2] = pd2[i][j][k];
			}

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 28; j++)
			for (int k = 0; k < 28; k++)
			{
				if (z1[i][j][k] > 0)
					pd1[i][j][k] = _tPd1[i][j][k];
				else
					pd1[i][j][k] = _tPd1[i][j][k] * leaky;
			}
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 28; j++)
			for (int k = 0; k < 28; k++)
			{
				for (int m = 0; m < 5; m++)
					for (int n = 0; n < 5; n++)
						pd1_w[i][m][n] += pd1[i][j][k] * input[j + m][k + n];

				pd1_b[i] += pd1[i][j][k];
			}
	if (showPD)
	{
		cout << endl << "pd1:" << endl;
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 28; j++)
			{
				for (int k = 0; k < 28; k++)
					cout << pd1[i][j][k] << " ";
				cout << endl;
			}
			cout << endl;
		}
		cout << endl << "pd1_w:" << endl;
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < 5; k++)
					cout << pd1_w[i][j][k] << " ";
				cout << endl;
			}
			cout << endl;
		}
	}
}

void update()
{
	//���²����ݶ�
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 84; j++)
			w7[i][j] -= LearnProcess * pd7_w[i][j];

	for (int i = 0; i < 84; i++)
	{
		for (int j = 0; j < 120; j++)
			w6[i][j] -= LearnProcess * pd6_w[i][j];
		b6[i] -= LearnProcess * pd6_b[i];
	}
	for (int i = 0; i < 120; i++)
	{
		for (int j = 0; j < 400; j++)
			w5[i][j] -= LearnProcess * pd5_w[i][j];
		b5[i] -= LearnProcess * pd5_b[i];
	}
	for (int i = 0; i < 16; i++)
	{
		for (int m = 0; m < 5; m++)
			for (int n = 0; n < 5; n++)
				w3[i][m][n] -= LearnProcess * pd3_w[i][m][n];

		b3[i] -= LearnProcess * pd3_b[i];
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
			{
				w1[i][j][k] -= pd1_w[i][j][k];
			}
		b1[i] -= LearnProcess * pd1_b[i];
	}
}

//���ܺ���
void visual()
{
	//�����
	cout << "����㣺" << endl;
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
			cout << input[i][j] << " ";
		cout << endl;
	}cout << endl;
	cout << endl;

	//L1��
	cout << "L1�㼤��ǰ:" << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << "��" << i << "����" << endl;
		for (int j = 0; j < 28; j++)
		{
			for (int k = 0; k < 28; k++)
				cout << z1[i][j][k] << " ";
			cout << endl;
		}
	}
	cout << "L1�㼤���:" << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << "��" << i << "����" << endl;
		for (int j = 0; j < 28; j++)
		{
			for (int k = 0; k < 28; k++)
				cout << a1[i][j][k] << " ";
			cout << endl;
		}
	}
	cout << endl;

	//L2��
	cout << "L2��:" << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << "��" << i << "����" << endl;
		for (int j = 0; j < 14; j++)
		{
			for (int k = 0; k < 14; k++)
				cout << z2[i][j][k] << " ";
			cout << endl;
		}
	}
	cout << endl;

	//L3��
	cout << "L3�㼤��ǰ:" << endl;
	for (int i = 0; i < 16; i++)
	{
		cout << "��" << i << "����" << endl;
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
				cout << z3[i][j][k] << " ";
			cout << endl;
		}
		cout << endl;
	}
	cout << "L3�㼤���:" << endl;
	for (int i = 0; i < 16; i++)
	{
		cout << "��" << i << "����" << endl;
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
				cout << a3[i][j][k] << " ";
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;

	//L4��
	cout << "L4��:" << endl;
	for (int i = 0; i < 16; i++)
	{
		cout << "��" << i << "����" << endl;
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
				cout << z4[i][j][k] << " ";
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;

	//L5��
	cout << "L5�㼤��ǰ��" << endl;
	for (int i = 0; i < 120; i++)
		cout << z5[i] << endl;
	cout << "L5�㼤���" << endl;
	for (int i = 0; i < 120; i++)
		cout << a5[i] << endl;
	cout << endl;

	//L6��
	cout << "L6�㼤��ǰ��" << endl;
	for (int i = 0; i < 84; i++)
		cout << z6[i] << endl;
	cout << "L6�㼤���" << endl;
	for (int i = 0; i < 84; i++)
		cout << a6[i] << endl;
	cout << endl;

	//L7��
	cout << "L7���һǰ��" << endl;
	for (int i = 0; i < 10; i++)
		cout << z7[i] << endl;

	cout << "���ս����" << endl;
	for (int i = 0; i < 10; i++)
		cout << a7[i] << " ";
	cout << endl;
}


void setInput(int _input[28][28])
{

	for (int i = 0; i < 10; i++)
		output[i] = 0;

	for (int i = 0; i < 32; i++)
		for (int j = 0; j < 32; j++)
			input[i][j] = 0;
	for (int i = 0; i < 28; i++)
		for (int j = 0; j < 28; j++)
			input[i + 2][j + 2] = (db)_input[i][j] / 255;
}
void func(int inputN, int corN)
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			for (int m = 0; m < 5; m++)
				for (int n = 0; n < 5; n++)
				{
					z3[corN][i][j] += z2[inputN][i + m][j + n] * w3[corN][m][n];
				}

		}
}
void func1(int inputN, int corN)
{
	for(int i=0;i<14;i++)
		for(int j=0;j<14;j++)
			for(int m=0;m<5;m++)
				for (int n = 0; n < 5; n++)
				{
					if((i-m)>-1&&(j-n)>-1&&(i-m)<10&&(j-n)<10)
					  pd2[inputN][i][j] += pd3[corN][i - m][j - n] * w3[corN][m][n];
				}
	for (int m = 0; m < 5; m++)
for (int n = 0; n < 5; n++)
	for (int j = 0; j < 10; j++)
		for (int k = 0; k < 10; k++)
		
					pd3_w[corN][m][n] += pd3[corN][j][k] * z2[inputN][j + m][k + n];


}

db Max(db x1, db x2, db x3, db x4)
{
	db tMax = -999999;
	if (x1 > tMax)
		tMax = x1;
	if (x2 > tMax)
		tMax = x2;
	if (x3 > tMax)
		tMax = x3;
	if (x4 > tMax)
		tMax = tMax;
	return tMax;
}
int maxP(db x1, db x2, db x3, db x4)
{
	int p = 0;
	db tMax = -999999;
	if (x1 > tMax)
	{
		tMax = x1;
		p = 0;
	}
	if (x2 > tMax)
	{
		tMax = x2;
		p = 1;
	}
	if (x3 > tMax)
	{
		tMax = x3;
		p = 2;
	}
	if (x4 > tMax)
	{
		tMax = x4;
		p = 3;
	}
	return p;
}

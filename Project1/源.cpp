#include"��ͷ.h"
#include"����.h"

typedef byte unsignedchar;


int main()
{
	cout << "leaky!:" << endl;
	leaky = 0.2;
	//cin >> leaky;

	cout << "LearnProcess:" << endl;
	LearnProcess = 0.1;
	//cin >> LearnProcess;

	showPD =0;
	lenet();//��ʼ������������
	int maxN = 0;
		for (int i = 0; i < 1000; i++)
		{
			readImages();//��ȡͼ��
			int arr[28][28];
			int label;
			int right1 = 0;
			int right2 = 0;
			for(int num=0;num<5999;num++)
			{
				//���������Լ���ǩ
				label = func(arr);//��ȡͼ����󼰱�ǩ
				setInput(arr);//��������
				output[label] = 1;//���ñ�ǩ


				forward();//��ǰ����
				if (i > 1111111111111)
				{
					string str;
					cin >> str;
					cout << endl << "����ͼ��" << endl;
	
					for (int i = 0; i < 6; i++)
					{
						for (int j = 0; j < 28; j++)
						{
							for (int k = 0; k < 28; k++)
								cout << z1[i][j][k] << " ";
							cout << endl;
						}
						cout << endl;
					}
					cout << endl << "�����" << endl;
					for (int i = 0; i < 6; i++)
					{
						for (int j = 0; j < 28; j++)
						{
							for (int k = 0; k < 28; k++)
								cout << a1[i][j][k] << " ";
							cout << endl;
						}
						cout << endl;
					}
					visual();
					showPD = 1;
				}
				backward();//���򴫲�
				update();//���²���

				if (num < 1000 && label == maxPi)
					right1++;
				if (num > 5000 && label == maxPi)
					right2++;
	
			}
			if (right1 > maxN)
				maxN = right1;
			if (right2 > maxN)
				maxN = right2;
			cout << "ǰ1000����ȷ����:" << right1 << ",   " << "��1000����ȷ����:" << right2 << ",   ";
			cout << "Ŀǰ���1000����ȷ����:" << maxN << endl;
		}



	return 0;
	
	
}
/*
	//Mat mat(28,28, CV_8UC1);
	//Lenet.visual();
	//imshow("1", mat);
	//waitKey(0);
namedWindow("Example2", WINDOW_AUTOSIZE);
	VideoCapture cap;
	cap.open("D:\\12.mp4");
	Mat frame;
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		imshow("Exameple2", frame);
		if (waitKey(400) >= 0) break;
	}

	return 0;*/
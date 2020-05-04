#include"标头.h"
#include"导入.h"

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
	lenet();//初始化参数及其它
	int maxN = 0;
		for (int i = 0; i < 1000; i++)
		{
			readImages();//读取图像
			int arr[28][28];
			int label;
			int right1 = 0;
			int right2 = 0;
			for(int num=0;num<5999;num++)
			{
				//设置输入以及标签
				label = func(arr);//获取图像矩阵及标签
				setInput(arr);//设置输入
				output[label] = 1;//设置标签


				forward();//向前传播
				if (i > 1111111111111)
				{
					string str;
					cin >> str;
					cout << endl << "特征图：" << endl;
	
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
					cout << endl << "激活后：" << endl;
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
				backward();//反向传播
				update();//更新参数

				if (num < 1000 && label == maxPi)
					right1++;
				if (num > 5000 && label == maxPi)
					right2++;
	
			}
			if (right1 > maxN)
				maxN = right1;
			if (right2 > maxN)
				maxN = right2;
			cout << "前1000张正确个数:" << right1 << ",   " << "后1000张正确个数:" << right2 << ",   ";
			cout << "目前最大1000张正确个数:" << maxN << endl;
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
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#define trainN 6000

int ReverseInt(int i)
{
	unsigned char ch1, ch2, ch3, ch4;
	ch1 = i & 255;
	ch2 = (i >> 8) & 255;
	ch3 = (i >> 16) & 255;
	ch4 = (i >> 24) & 255;
	return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void read_Mnist_Label(string filename, vector<int>& labels)
{
	ifstream file(filename, ios::binary);
	if (file.is_open())
	{
		int magic_number = 0;
		int number_of_images = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		file.read((char*)&number_of_images, sizeof(number_of_images));
		magic_number = ReverseInt(magic_number);
		number_of_images = ReverseInt(number_of_images);
		for (int i = 0; i < trainN; i++)
		{
			unsigned char label = 0;
			file.read((char*)&label, sizeof(label));
			labels.push_back((int)label);
		}

	}
	else
	{
		cout << "û���ҵ��ļ�..." << endl;
		while (1);
	}
	file.close();

}

void read_Mnist_Images(string filename, vector<vector<int>>& images)
{
	ifstream file(filename, ios::binary);
	if (file.is_open())
	{
		int magic_number = 0;
		int number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;
		unsigned char label;
		file.read((char*)&magic_number, sizeof(magic_number));
		file.read((char*)&number_of_images, sizeof(number_of_images));
		file.read((char*)&n_rows, sizeof(n_rows));
		file.read((char*)&n_cols, sizeof(n_cols));
		magic_number = ReverseInt(magic_number);
		number_of_images = ReverseInt(number_of_images);
		n_rows = ReverseInt(n_rows);
		n_cols = ReverseInt(n_cols);

		for (int i = 0; i < trainN; i++)
		{
			vector<int>tp;
			for (int r = 0; r < n_rows; r++)
			{
				for (int c = 0; c < n_cols; c++)
				{
					unsigned char image = 0;
					file.read((char*)&image, sizeof(image));
					tp.push_back(image);
				}
			}
			images.push_back(tp);
		}
	}
	else
	{
		cout << "û���ҵ��ļ�..." << endl;
		while (1);
	}
	file.close();

}
vector<int>labels;
vector<vector<int>>images;

void readImages()
{
	read_Mnist_Label("train-labels-idx1-ubyte", labels);
	read_Mnist_Images("train-images-idx3-ubyte", images);
	cout << "���ͼƬ����:" << endl;
}
int func(int arr[28][28])
{
for (int i = 0; i < 28; i++)
		for (int j = 0; j < 28; j++)
			arr[i][j] = images[images.size()-1][i * 28 + j];
int label = labels[labels.size() - 1];
images.pop_back();
labels.pop_back();
	return label;
}
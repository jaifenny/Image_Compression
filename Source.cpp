#include<opencv2/opencv.hpp>
#include<math.h>
#include<iostream>
#include<string>
#include <fstream>
using namespace std;
using namespace cv;
Mat img, dst, dst2;
string path, filename;
string p;
fstream fin;
long length;
int row, col;
#define WINDOW_NAME "Original"
#define WINDOW_NAME1 "Compression"
#define WINDOW_NAME2 "Unzip"
void compression1(void) {
	int* compression = new int[length * 6];//RGB
	int tmp = 0;
	int num = 1;
	int n1 = 0, n2 = 0;
	int rgb = 0;
	while (rgb < 3) {
		for (int i = 0;i < row;i++)
		{
			for (int j = 1;j < col;j++)
			{
				n1 = img.at<Vec3b>(i, j)[rgb];
				n2 = img.at<Vec3b>(i, j - 1)[rgb];
				if (n1 != n2)
				{
					compression[tmp] = num;
					compression[tmp+1] = n2;//pre color
					num = 1;
					tmp += 2;
				}
				else
				{
					num++;
				}
				if (j == col - 1)
				{
					if (i < row - 1)
					{
						n2 = img.at<Vec3b>(i+1, 0)[rgb]; //next row first pixel
						if (n1 != n2)
						{
							compression[tmp] = num;
							compression[tmp + 1] = n1;//color now
							tmp += 2;
							num = 1;
						}
						else
							num++;
					}
					else if(i == row - 1)
					{
						compression[tmp] = num;
						compression[tmp + 1] = n1;//color now
						tmp += 2;
						num = 1;
					}
				}
			}
		}
		rgb++;//b,g,r
	}
	ofstream fout(path + "compression_" + filename + ".txt", ios::trunc| ios::out);
	fout << row << " " << col << " ";
	int tmp2 = 0;
	while (tmp2 < tmp)
	{
		fout << compression[tmp2] << " ";
		tmp2++;
	}
	fout.close();
	cout << "done"; 
}
void unzip1(void) {
	fin >> row;
	fin >> col;
	length = row * col;
	int* unzip = new int[length * 6];
	int k = 0;
	while (!fin.eof())  
	{
		fin >> unzip[k];
		k++;
	}
	fin.close();//compression_img1.bmp.txt

	dst2 = Mat::zeros(row,col, CV_8UC3);//圖片還原
	int rgb = 0;
	int n3 = 0, n4 = 0, color = 0, num = 0;
	while (rgb < 3) {
		num = unzip[n3];
		color = unzip[n3 + 1];
		n3 += 2;
		n4 = 0;
		for (int i = 0;i < row;i++)
		{
			for (int j = 0;j < col;j++)
			{
				if (n4 < num)
				{
					dst2.at<Vec3b>(i, j)[rgb] = color;
					n4++;
				}
				else
				{
					n4 = 0;
					num = unzip[n3];
					color = unzip[n3 + 1];
					n3 += 2;
					dst2.at<Vec3b>(i, j)[rgb] = color;
					n4++;
				}
			}
		}
		rgb++;
	}

	int l = filename.length();
	filename.erase(l - 4); //delete .txt
	path = path + "unzip_" + filename;
	cout << path << endl;
	namedWindow(WINDOW_NAME2, WINDOW_NORMAL);
	imshow(WINDOW_NAME2, dst2);
	imwrite(path, dst2);//test
}
int main()
{
	path = "C:\\Users\\user\\Desktop\\image processing\\hw\\Assignment6\\";
	cout << "Please enter a file name.(file type): ";
	getline(cin, filename);
	string b = "bmp", c = "compression";
	string::size_type idx;
	idx = filename.find(b);
	int x = 0;
	if (!(idx == string::npos))
	{
		idx = filename.find(c);
		if (!(idx == string::npos))//解壓縮 x=1		
			x = 1;
		else//壓縮 x=2	
			x = 2;
	}
	p = path + filename;
	if (x == 1) {
		fin.open(p, ios::in);
		if (!fin) {
			cout << "Could not find this file." << endl;
			system("pause");
			return -1;
		}
		unzip1();
	}
	else if (x == 2) {
		img = imread(p);
		if (img.empty())
		{
			cout << "Could not find this file." << endl;
			system("pause");
			return -1;
		}
		row = img.rows;
		col = img.cols;
		length = row * col;
		namedWindow(WINDOW_NAME, WINDOW_NORMAL); //output original
		imshow(WINDOW_NAME, img);
		compression1();
	}
	waitKey(0);
	if (x == 2)destroyWindow(WINDOW_NAME);
	if (x == 1)destroyWindow(WINDOW_NAME2);
	system("pause");
	return 0;
}
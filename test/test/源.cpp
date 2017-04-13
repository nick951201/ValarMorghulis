#include <iostream>
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching.hpp"

#include <Windows.h>

using namespace std;
using namespace cv;

bool try_use_gpu = true;
//Stitcher::Mode mode = Stitcher::PANORAMA;
vector<Mat> imgs;
string result_name = "r32.jpg";
vector<string> source;


int main(int argc, char* argv[])
{
	cout << CV_VERSION << "\n";
	DWORD start, end;
	start = GetTickCount();
	//这里是2个要拼接的图片的文件名
	string img1 = "DSC00003.jpg";
	string img2 = "DSC00002.jpg";
	
	source.push_back(img1);
	source.push_back(img2);

	vector<string>::iterator iter;
	for (iter = source.begin(); iter != source.end(); iter++)
	{
		
		Mat img = imread(*iter);
		if (img.empty())
		{
			cout << "Can't read image '" << *iter << "'\n";
			return -1;
		}
		imgs.push_back(img);
	}
	

	Mat pano;
	Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
	Stitcher::Status status = stitcher.stitch(imgs, pano);

	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		return -1;
	}

	imwrite(result_name, pano);

	end = GetTickCount();
	printf("time: %d ms\n", end - start);
	return 0;
}



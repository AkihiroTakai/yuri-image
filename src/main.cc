#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iostream>
#include <fstream>

/*
 *ゆりOSのソースコード(include/kernel.h)より引用
 */
#define __RGB256COL__(r, g, b) (16+(r/51)+(6*(g/51))+(36*(b/51)))

int main(int argc, char **argv){
	
	std::ofstream yim;
	cv::Mat src_img = cv::imread(argv[1]);
	char color_number;
	yim.open(argv[2], std::ios::out | std::ios::binary | std::ios::trunc);

	if(!yim){
		std::cout << "ERROR";
		exit(0);
	}

	/*
	 *シグネチャ
	 */
	yim.write("yim", 3);

      /*
	 *画像の基本情報を記述
	 */
	//画像の幅
	yim.write((char *)(&src_img.cols), 4);
	//画像の高さ
	yim.write((char *)(&src_img.rows), 4);

	/*
	 *画素をビットマップ的に書き込む
	 */
	for(int y = 0;y < src_img.rows;y++){
		for(int x = 0;x < src_img.cols;x++){
			color_number = __RGB256COL__(
				src_img.at<cv::Vec3b>(y, x)[2],   //RED
				src_img.at<cv::Vec3b>(y, x)[1],   //GREEN
				src_img.at<cv::Vec3b>(y, x)[0]    //BLUE
				);
			yim.write((char *)&color_number, sizeof(char));
		}
	}

	yim.close();

	return 0;
}

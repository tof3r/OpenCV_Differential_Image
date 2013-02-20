#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"

using namespace cv;

int main(int argc, char** argv)
{
	/*Obiekt zostanie automatcznie zwolniony 
	przy wywo³aniu destruktora VideoCapture*/
	VideoCapture z_kamerki(0);

	if(!z_kamerki.isOpened()) return -1;

	Mat ramka, ramka_gs, ramka_binary;

	while(true){
		/*pobranie kolejnej ramki z kamery*/
		z_kamerki >> ramka;

		/*ka¿da klatka z kamery jest zamieniona na odcieñ szaroœci*/
		cvtColor(ramka,ramka_gs,CV_BGR2GRAY);

		/*progowanie obrazu w skali szaroœci do binarnego*/
		ramka_binary = ramka_gs > 50;
	
		imshow("Z kamery",ramka);
		imshow("Greyscale",ramka_gs);
		imshow("Binary",ramka_binary);

		int listener = cv::waitKey(40);

		if(listener == 27)break;
	}

	return 0;
}

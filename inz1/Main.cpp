#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"

using namespace cv;

int main(int argc, char** argv)
{
	/*Obiekt zostanie automatcznie zwolniony 
	przy wywo³aniu destruktora VideoCapture*/
	VideoCapture z_kamerki(0);

	if(!z_kamerki.isOpened()) return -1;

	Mat ramka, ramka_gs, ramka_poprzednia, roznica, binary;

	bool pierwsza_ramka = true;

	while(true){
		/*pobranie kolejnej ramki z kamery*/
		z_kamerki >> ramka;

		/*ka¿da klatka z kamery jest zamieniona na odcieñ szaroœci*/
		cvtColor(ramka,ramka_gs,CV_BGR2GRAY);

		/*zapamiêtanie pierwszej ramki, do dalszych porównañ*/
		if(pierwsza_ramka){
			ramka_poprzednia = ramka_gs.clone();
			pierwsza_ramka = false;
			continue;
		}

		absdiff(ramka_gs, ramka_poprzednia, roznica);

		threshold(roznica,binary, 50, 255,THRESH_BINARY);

		erode(binary, binary,Mat(),Point(-1,-1),1);
		dilate(binary, binary,Mat(),Point(-1,-1),1);
	
		imshow("Z kamery",ramka);
		imshow("Greyscale",ramka_gs);
		imshow("Binary",binary);

		ramka_poprzednia=ramka_gs.clone();

		int listener = cv::waitKey(40);

		if(listener == 27)break;
	}

	z_kamerki.release();

	return 0;
}

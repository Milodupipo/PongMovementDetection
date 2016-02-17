#ifndef Detection_H
#define Detection_H

#include <opencv2/opencv.hpp>

using namespace cv;

class Detection
{
public:
	Detection(){
		std::cout << "par defaut" << std::endl;
		this->capture = cvCreateCameraCapture(CV_CAP_ANY);
		this->rng = RNG(12345);
	};
	explicit Detection(const Detection& d){
		std::cout << "par copie" << std::endl;
	};
	explicit Detection(Detection&& autre) : capture(std::move(autre.capture)), frame(autre.frame), thresh(autre.thresh), rng(autre.rng),
		tmp(autre.tmp), canny_output(autre.canny_output), contours(autre.contours), hierarchy(autre.hierarchy) {
		std::cout << "par deplacement" << std::endl;
	};
	const Detection& operator=(const Detection &d){
		std::cout << "affectation par defaut" << std::endl;
		this->capture = d.capture;
		this->frame = d.frame;
		this->thresh = d.thresh;
		this->rng = d.rng;
		this->tmp = d.tmp;
		this->canny_output = d.canny_output;
		this->contours = d.contours;
		this->hierarchy = d.hierarchy;
		return *this;
	};
	const Detection& operator=(Detection&& d) {
		std::cout << "affectation par deplacement" << std::endl;
		if (this != &d)
		{
			delete this->capture;
			this->capture = d.capture;
			d.capture = nullptr;
			this->frame = d.frame;
			this->thresh = d.thresh;
			this->rng = d.rng;
			this->tmp = d.tmp;
			this->canny_output = d.canny_output;
			this->contours = d.contours;
			this->hierarchy = d.hierarchy;
		}
		return *this;
	};
	~Detection(){
		delete this->capture;
	};
	inline const int analyseImage(){
		frame = cvQueryFrame(capture);
		cv::cvtColor(frame, tmp, CV_RGB2GRAY);
		// Threshold the HSV image, keep only the red pixels
		cv::threshold(tmp, tmp, 191, 255, THRESH_BINARY);
		Mat element = getStructuringElement(MORPH_RECT, Size(2 * MORPH_RECT + 1, 1), Point(0, 0));
		cv::erode(tmp, tmp, element, Point(-1, -1), 5);
 
		/// Detect edges using canny
		Canny(tmp, canny_output, thresh, thresh * 2, 5);
		/// Find contours
		findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

		/// Get the moments
		vector<Moments> mu(contours.size());
		//for (int i = 0; i < contours.size(); i++)
		//{
		if (!contours.empty()) mu[0] = moments(contours[0], false);
		//}
		///  Get the mass centers:
		vector<Point2f> mc(contours.size());
		//for (int i = 0; i < contours.size(); i++)
		//{
		if (!mu.empty()) mc[0] = Point2f(mu[0].m10 / mu[0].m00, mu[0].m01 / mu[0].m00);
		//}
		imshow("Sortie", frame);
		imshow("Noir et Blanc", tmp);
		imshow("Contour", canny_output);
		if (!mc.empty()) return mc[0].y;
		else return -1;		
		
	};
protected:

	CvCapture* capture;
	Mat frame;
	int thresh = 100;
	RNG rng;
	Mat tmp;
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
};
#endif // !Detection_H

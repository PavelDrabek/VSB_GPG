// GaussianMixture.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

cv::Mat graph;
cv::Point points[4];
int pIndex;

float Ft0(float t) { return 2 * t*t*t - 3 * t*t + 1; }
float Ft1(float t) { return -2 * t*t*t + 3 * t*t; }
float Ft2(float t) { return t*t*t - 2 * t*t + t; }
float Ft3(float t) { return t*t*t - t*t; }

void showGraph(cv::Mat& graph)
{
	graph = cv::Mat(400, 400, CV_32FC3);

	for (int i = 0; i < 1000; i++)
	{
		float t = i / 1000.0f;
		cv::Point p = points[0] * Ft0(t) + points[1] * Ft1(t) + points[2] * Ft2(t) + points[3] * Ft3(t);
		graph.at<cv::Vec3f>(p) = cv::Vec3f(1, 1, 1);
	}

	// draw points and vectors
	for (int i = 0; i < 2; i++)
	{
		cv::circle(graph, points[i], 2, cv::Scalar(1, 0, 0), 2);
		cv::line(graph, points[i], points[i + 2], cv::Scalar(0, 1, 0), 1);
	}

	cv::imshow("graph", graph);
}


void CallBackFunc(int event, int x, int y, int flags, void *userdata) {
	if (event == CV_EVENT_LBUTTONDOWN) {
		points[pIndex].x = x;
		points[pIndex].y = y;
		printf("Point[%d] = [%d, %d]\n", pIndex, x, y);
		pIndex = (pIndex + 1) % 4;
		showGraph(graph);
	}
}

int main()
{
	graph = cv::Mat(400, 400, CV_32FC3);

	cv::imshow("graph", graph);
	cv::setMouseCallback("graph", CallBackFunc, NULL);

	cv::waitKey(0);
	return 0;
}


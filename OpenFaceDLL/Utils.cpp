#pragma once
#include <opencv2/opencv.hpp>

typedef struct _FACE_INFO
{
	float certainty;
	bool detection_success;
	double landmarks2D[136] = { 0.0 };
	double landmarks3D[204] = { 0.0 };
	double head_rotation[3] = { 0.0 };
	double head_position[3] = { 0.0 };
	double aus_intensity[17] = { 0.0 };
	double aus_presence[18] = { 0.0 };
} FACE_INFO;

inline bool pair_compare(const std::pair<std::string, double>& i, const std::pair<std::string, double>& j)
{
	return (std::stoi(i.first) < std::stoi(j.first));
}
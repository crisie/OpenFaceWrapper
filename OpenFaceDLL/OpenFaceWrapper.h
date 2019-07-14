#pragma once
#ifndef OPEN_FACE_WRAPPER_H_
#define OPEN_FACE_WRAPPER_H_

#include <FaceAnalyser.h>
#include <LandmarkCoreIncludes.h>

struct _FACE_INFO;
using FACE_INFO = _FACE_INFO;

class OpenFaceWrapper
{
public:
	OpenFaceWrapper();
	~OpenFaceWrapper();

	bool TrackFace(const std::string& img_file, const double* camera_matrix, FACE_INFO* info);


private:
	LandmarkDetector::FaceModelParameters det_parameters_;
	LandmarkDetector::CLNF* face_model_;
	FaceAnalysis::FaceAnalyserParameters face_analysis_params_;
	FaceAnalysis::FaceAnalyser* face_analyzer_;
}; 
#endif // OPEN_FACE_WRAPPER_H_
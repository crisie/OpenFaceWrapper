#include "LandmarkCoreIncludes.h"
#include <FaceAnalyser.h>
#include "Utils.cpp"

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

#include "OpenFaceWrapper.h"

#include "OpenFaceDLL.h"

#include <memory>

inline bool pair_compare(const std::pair<std::string, double>& i, const std::pair<std::string, double>& j)
{
	return (std::stoi(i.first) < std::stoi(j.first));
}

OpenFaceWrapper::OpenFaceWrapper()
{
	//Load landmark detector
	//LandmarkDetector::FaceModelParameters det_parameters;
	face_model_ = new LandmarkDetector::CLNF(det_parameters_.model_location);

	//Load facial feature extractor and AU analyzer
	face_analysis_params_.OptimizeForVideos();
	//FaceAnalysis::FaceAnalyser face_analyzer(face_analysis_params_);
	face_analyzer_ = new FaceAnalysis::FaceAnalyser(face_analysis_params_);
}


OpenFaceWrapper::~OpenFaceWrapper()
{
}

bool OpenFaceWrapper::TrackFace(const std::string& img_file, const double* camera_matrix, FACE_INFO* info)
{	
	bool success = false;
	cv::Mat tmp;
	try{
		// Load image
		tmp = cv::imread(img_file, cv::IMREAD_COLOR);
		// Detect landmarks in video, has to be called prior to the following methods
		cv::Mat dummy;
		success = LandmarkDetector::DetectLandmarksInVideo(tmp, *face_model_, det_parameters_, dummy);
	}
	catch (...) {
		return false;
	}

	// Face detection success (0 or 1) 
	info->detection_success = success;

	// Landmarks detection certainty (from 0 to 1)
	info->certainty = 0.5 * (1 - face_model_->detection_certainty);

	//Landmarks 2D
	cv::Mat_<double> lndmks2D = face_model_->detected_landmarks;
	for (int i = 0; i < lndmks2D.cols * lndmks2D.rows; ++i)
	{
		info->landmarks2D[i] = lndmks2D.at<double>(i);
	}

	//	Landmarks 3D
	cv::Mat_<double> lndmks3D = face_model_->GetShape(camera_matrix[0], camera_matrix[4], camera_matrix[2], camera_matrix[5]);
	for (int i = 0; i < lndmks3D.cols * lndmks3D.rows; ++i)
	{
		info->landmarks3D[i] = lndmks3D.at<double>(i);
	}

	//Head pose (with appropriate correction for perspective)
	cv::Vec6d pose = LandmarkDetector::GetPose(*face_model_, camera_matrix[0], camera_matrix[4], camera_matrix[2], camera_matrix[5]);
	for (size_t i = 0; i < 3; ++i)
	{
		info->head_position[i] = pose[i];
		info->head_rotation[i] = pose[i + 3];

	}

	//AUs
	face_analyzer_->PredictStaticAUsAndComputeFeatures(tmp, face_model_->detected_landmarks);

	auto aus_intensity = face_analyzer_->GetCurrentAUsReg();
	for (size_t i = 0; i < aus_intensity.size(); ++i)
	{
		aus_intensity[i].first = aus_intensity[i].first.erase(0, 2);
	}
	std::sort(std::begin(aus_intensity), std::end(aus_intensity), pair_compare);
	for (size_t i = 0; i < aus_intensity.size(); ++i)
	{
		info->aus_intensity[i] = aus_intensity[i].second;
	}

	auto aus_presence = face_analyzer_->GetCurrentAUsClass();
	for (size_t i = 0; i < aus_presence.size(); ++i)
	{
		aus_presence[i].first = aus_presence[i].first.erase(0, 2);
	}
	std::sort(std::begin(aus_presence), std::end(aus_presence), pair_compare);
	for (size_t i = 0; i < aus_presence.size(); ++i)
	{
		info->aus_presence[i] = aus_presence[i].second;
	}

	return true;
}
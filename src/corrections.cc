//
// Created by mikhail on 7/2/20.
//

#include "corrections.h"

namespace HadesUtils{

Corrections* Corrections::instance_= nullptr;

Corrections* Corrections::Instance(){
  if(!instance_)
	instance_ = new Corrections();
  return instance_;
}
double Corrections::GetEfficiency(int cent_class, double pt, double y) {
  try {
	size_t bin_x =  Instance()->efficiency_maps_.at(cent_class).GetXaxis()->FindBin(y);
	size_t bin_y =  Instance()->efficiency_maps_.at(cent_class).GetYaxis()->FindBin(pt);
	float efficiency = Instance()->efficiency_maps_.at(cent_class).GetBinContent(bin_x, bin_y);
	return efficiency;
  } catch (const std::exception &exception) {
	std::cout << "Corrections::GetEfficiency(): " << std::endl;
	throw exception;
  }
}
double Corrections::GetMismatch(int cent_class, double pt, double y) {
  try {
	int bin = Instance()->contamination_maps_.at(cent_class).FindBin(pt, y);
	return Instance()->contamination_maps_.at(cent_class).GetBinContent(bin);
  } catch (const std::exception &exception) {
	std::cout << "Error in Corrections::GetMismatch()" << std::endl;
	std::cout << "Mismatch maps are not initialized" << std::endl;
	std::cout << exception.what() << std::endl;
	abort();
  }
}
void Corrections::ReadMaps(const std::string &file_name) {
  auto *file = TFile::Open(file_name.c_str());
  if (!file) {
	throw std::runtime_error("Corrections::ReadMaps(): No such file "+file_name);
  }
  TH2F *histo{nullptr};
  int percentile = 2;
  while (percentile < 40) {
	std::string name = "efficiency_" + std::to_string(percentile);
	file->GetObject(name.c_str(), histo);
	if (!histo) {
	  throw std::runtime_error("Corrections::ReadMaps(): No such obj "+name);
	}
	Instance()->efficiency_maps_.emplace_back(*histo);
	name = "contamination_" + std::to_string(percentile);
	file->GetObject(name.c_str(), histo);
	if (!histo) {
	  throw std::runtime_error("Corrections::ReadMaps(): No such obj "+name);
	}
	Instance()->contamination_maps_.emplace_back(*histo);
	percentile += 5;
  }
}
}
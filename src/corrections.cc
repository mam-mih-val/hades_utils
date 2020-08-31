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
	int bin = Instance()->efficiency_maps_.at(cent_class).FindBin(pt, y);
	return Instance()->efficiency_maps_.at(cent_class).GetBinContent(bin);
  } catch (const std::exception &exception) {
	std::cout << "Error in Corrections::GetEfficiency()" << std::endl;
	std::cout << exception.what() << std::endl;
	abort();
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
	std::cout << "No param file for acceptance correction" << std::endl;
	abort();
  }
  TH2F *histo{nullptr};
  int percentile = 2;
  while (percentile < 40) {
	std::string name = "efficiency_" + std::to_string(percentile);
	file->GetObject(name.c_str(), histo);
	if (!histo) {
	  std::cout << "No such obj: " << name << std::endl;
	  abort();
	}
	Instance()->efficiency_maps_.emplace_back(*histo);
	name = "contamination_" + std::to_string(percentile);
	file->GetObject(name.c_str(), histo);
	if (!histo) {
	  std::cout << "No such obj: " << name << std::endl;
	  abort();
	}
	Instance()->contamination_maps_.emplace_back(*histo);
	percentile += 5;
  }
}
}
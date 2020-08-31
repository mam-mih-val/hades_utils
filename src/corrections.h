//
// Created by mikhail on 7/2/20.
//

#ifndef HADES_FLOW_SRC_ACCEPTANCE_CORRECTION_H_
#define HADES_FLOW_SRC_ACCEPTANCE_CORRECTION_H_

#include <TFile.h>
#include <TH2F.h>
#include <iostream>

namespace HadesUtils {
class Corrections {
 public:
  static double GetEfficiency(int cent_class, double pt, double y);
  static double GetMismatch(int cent_class, double pt, double y);
  static void ReadMaps(const std::string &file_name);

 private:
  Corrections() = default;
  virtual ~Corrections() = default;
  static Corrections* instance_;
  static Corrections* Instance();
  std::vector<TH2F> efficiency_maps_;
  std::vector<TH2F> contamination_maps_;
};
}// namespace HadesUtils
#endif // HADES_FLOW_SRC_ACCEPTANCE_CORRECTION_H_

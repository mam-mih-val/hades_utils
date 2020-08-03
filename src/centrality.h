
#ifndef CENTRALITY_H
#define CENTRALITY_H

#include <iostream>
#include <string>

#include "TH1F.h"

#include "constants.h"

namespace HadesUtils {
class Centrality {
 public:
  // returns centrality class value in 5% bins
  // for example, returned number 1.0 is equal to (0-5)% centrality
  [[maybe_unused]] static double GetClass(double multiplicity, DATA_TYPE data_type);
  // returns the center of centrality bin in percents
  // for example, returned value of 22.5 means (20-25)% centrality
  [[maybe_unused]] static double GetValue(double multiplicity, DATA_TYPE data_type);

 private:
  static Centrality* instance_;
  Centrality() : au123_centrality_5pc_{nullptr},
				 ag123_centrality_5pc_{nullptr},
				 ag158_centrality_5pc_{nullptr} {};
  ~Centrality() = default;
  static Centrality* Instance();

  [[maybe_unused]] void LoadCentralityAuAu123();
  [[maybe_unused]] void LoadCentralityAgAg123();
  [[maybe_unused]] void LoadCentralityAgAg158();

  [[maybe_unused]] double inline GetAuAu123CentralityClass(double multiplicity);
  [[maybe_unused]] double inline GetAuAu123Centrality(double multiplicity);
  [[maybe_unused]] double inline GetAgAg123CentralityClass(double multiplicity);
  [[maybe_unused]] double inline GetAgAg123Centrality(double multiplicity);
  [[maybe_unused]] double inline GetAgAg158CentralityClass(double multiplicity);
  [[maybe_unused]] double inline GetAgAg158Centrality(double multiplicity);

  TH1F *au123_centrality_5pc_;// Centrality for apr 12 data of Au+Au@1.23AGeV
  TH1F *ag123_centrality_5pc_;// Centrality for mar 19 data of Ag+Ag@1.23AGeV
  TH1F *ag158_centrality_5pc_;// Centrality for mar 19 data of Ag+Ag@1.58AGeV
};
}// namespace HadesUtils
#endif // CENTRALITY_H
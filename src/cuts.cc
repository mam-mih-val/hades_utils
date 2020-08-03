//
// Created by mikhail on 8/2/20.
//

#include "cuts.h"

namespace HadesUtils{

AnalysisTree::Cuts* Cuts::Get( BRANCH_TYPE branch, DATA_TYPE data){
  switch ( data ) {
	case DATA_TYPE::AuAu_1_23AGeV:
	  return GetAuAu123(branch);
	case DATA_TYPE::AgAg_1_23AGeV:
	  return GetAgAg123(branch);
	case DATA_TYPE::AgAg_1_58AGeV:
	  return GetAgAg158(branch);
	default:
	  std::cout << "HadesUtils::Cuts::Get() Error: Unknown data type" << std::endl;
	  abort();
  }
}
AnalysisTree::Cuts* Cuts::GetAuAu123(BRANCH_TYPE branch) {
  switch (branch) {
	case Cuts::BRANCH_TYPE::EVENT_HEADER:
	  return AuAu123AGeV::EventCuts( event_header_name );
	case Cuts::BRANCH_TYPE::MDC_TRACKS:
	  return AuAu123AGeV::TrackCuts(reco_track_branch_name);
	case Cuts::BRANCH_TYPE::META_HITS:
	  return AuAu123AGeV::MetaHitsCuts(meta_hits_branch_name);
	case Cuts::BRANCH_TYPE::WALL_HITS:
	  return AuAu123AGeV::WallHitsCuts(wall_hits_branch_name);
	default:
	  std::cout << "HadesUtils::Cuts::GetAuAu123 Error: Unknown branch type" << std::endl;
	  abort();
  }
}
AnalysisTree::Cuts* Cuts::GetAgAg123(BRANCH_TYPE branch) {
  switch (branch) {
	case Cuts::BRANCH_TYPE::EVENT_HEADER:
	  return AgAg123AGeV::EventCuts( event_header_name );
	case Cuts::BRANCH_TYPE::MDC_TRACKS:
	  return AgAg123AGeV::TrackCuts(reco_track_branch_name);
	case Cuts::BRANCH_TYPE::META_HITS:
	  return AgAg123AGeV::MetaHitsCuts(meta_hits_branch_name);
	case Cuts::BRANCH_TYPE::WALL_HITS:
	  return AgAg123AGeV::WallHitsCuts(wall_hits_branch_name);
	default:
	  std::cout << "HadesUtils::Cuts::GetAuAu123 Error: Unknown branch type" << std::endl;
	  abort();
  }
}
AnalysisTree::Cuts* Cuts::GetAgAg158(BRANCH_TYPE branch) {
  return GetAgAg123(branch);
}
}
#ifndef HADES_UTILS_SRC_AU123_CUTS_H_
#define HADES_UTILS_SRC_AU123_CUTS_H_

#include <cmath>
#include "AnalysisTree/Cuts.hpp"
#include "AnalysisTree/SimpleCut.hpp"

namespace AuAu123AGeV {

AnalysisTree::Cuts *EventCuts(const std::string &branch, const std::string &name = "HadesGoodEvent") {
//  AnalysisTree::SimpleCut vtx_xy_cut{{{branch, "vtx_x"},
//									  {branch, "vtx_y"}}, [](std::vector<double> r) {
//									   return sqrt(r.at(0) * r.at(0) + r.at(1) * r.at(1)) < 3.0;
//									 }};
  AnalysisTree::SimpleCut vtx_x_cut({branch, "vtx_x"}, -3.0, 3.0);
  AnalysisTree::SimpleCut vtx_y_cut({branch, "vtx_y"}, -3.0, 3.0);
  AnalysisTree::SimpleCut vtx_z_cut({branch, "vtx_z"}, -60.0, 0.0);
  AnalysisTree::SimpleCut vtx_chi2_cut({branch, "vtx_chi2"}, 0.5, 40);
  AnalysisTree::SimpleCut good_vertex_cut({branch, "good_vertex_cluster"}, 0.5, 1.5);
  AnalysisTree::SimpleCut good_vertex_candidate_cut({branch, "good_vertex_candidate"}, 0.5, 1.5);
  AnalysisTree::SimpleCut good_start_cut({branch, "good_start"}, 0.5, 1.5);
  AnalysisTree::SimpleCut no_pile_up_start_cut({branch, "no_pile_up_start"}, 0.5, 1.5);
  AnalysisTree::SimpleCut no_veto_cut({branch, "no_veto"}, 0.5, 1.5);
  AnalysisTree::SimpleCut good_start_veto_cut({branch, "good_start_veto"}, 0.5, 1.5);
  AnalysisTree::SimpleCut good_start_meta_cut({branch, "good_start_meta"}, 0.5, 1.5);
  AnalysisTree::SimpleCut minimum_bias({branch, "physical_trigger_2"}, 0.5, 1.5);
  auto *event_cuts = new AnalysisTree::Cuts(name, {
	  vtx_x_cut,
	  vtx_y_cut,
	  vtx_z_cut,
	  vtx_chi2_cut,
	  good_vertex_cut,
	  good_vertex_candidate_cut,
	  good_start_cut,
	  no_pile_up_start_cut,
	  no_veto_cut,
	  good_start_veto_cut,
	  good_start_meta_cut,
//	  minimum_bias
  });
  return event_cuts;
}

AnalysisTree::Cuts *TrackCuts(const std::string &branch, const std::string &name = "HadesGoodVertexTrack") {
  AnalysisTree::SimpleCut dca_xy_cut({branch, "dca_xy"}, -10, 10);
  AnalysisTree::SimpleCut dca_z_cut({branch, "dca_z"}, -10, 10);
  AnalysisTree::SimpleCut chi2_rk_cut({branch, "chi2"}, 0, 100);
  auto *vertex_tracks_cuts = new AnalysisTree::Cuts(name, {
	  dca_xy_cut,
	  dca_z_cut,
	  chi2_rk_cut
  });
  return vertex_tracks_cuts;
};

AnalysisTree::Cuts *MetaHitsCuts(const std::string &branch, const std::string &name = "HadesGoodMetaHit") {
  AnalysisTree::SimpleCut meta_match_chi2_cut({branch, "match_quality"}, 0, 3.0);
  auto *tof_cuts = new AnalysisTree::Cuts(name, {meta_match_chi2_cut});
  return tof_cuts;
};
AnalysisTree::Cuts *WallHitsCuts(const std::string &branch, const std::string &name = "HadesGoodWallHit") {
  AnalysisTree::SimpleCut beta_cut({branch, "beta"}, 0, 1.0);
  AnalysisTree::SimpleCut ring_by_ring_cuts({{branch, "ring"}, {branch, "beta"}, {branch, "signal"}},
											[](std::vector<double> vars) {
											  if (1.0 <= vars.at(0) && vars.at(0) <= 5)
												return vars.at(1) > 0.84
													&& vars.at(2) > 80.0;
											  if (vars.at(0) >= 6.0 && vars.at(0) <= 7.0)
												return vars.at(1) > 0.85
													&& vars.at(2) > 85.0;
											  if (8.0 <= vars.at(0) && vars.at(0) <= 10.0)
												return vars.at(1) > 0.80
													&& vars.at(2) > 88.0;
											  return false;
											});
  auto *wall_cuts = new AnalysisTree::Cuts(name, {beta_cut, ring_by_ring_cuts});
  return wall_cuts;
};

}// namespace AuAu_1_23_AGeV

#endif // HADES_UTILS_SRC_AU123_CUTS_H_
#include <cmath>
#include "AnalysisTree/Cuts.hpp"
#include "AnalysisTree/SimpleCut.hpp"

namespace AgAg123AGeV {

AnalysisTree::Cuts *EventCuts(const std::string &branch, const std::string &name = "HadesGoodEvent") {
  AnalysisTree::SimpleCut vtx_xy_cut{{{branch, "vtx_x"},
									  {branch, "vtx_y"}}, [](std::vector<double> r) {
									   auto r_x = r.at(0) - -6.26652e-01;
									   auto r_y = r.at(1) - -1.67751e-01;
									   auto d_x = 8.35689e-01;
									   auto d_y = 7.49888e-01;
									   auto d = (d_x+d_y)/2;
									   return sqrt(r_x*r_x + r_y*r_y) < 3.0*d;
									 }};
  AnalysisTree::SimpleCut vtx_z_cut({branch, "vtx_z"}, -70.0, -5.0);
  AnalysisTree::SimpleCut vtx_chi2_cut({branch, "vtx_chi2"}, 0.5, 40);
  AnalysisTree::SimpleCut good_vertex_cut({branch, "good_vertex_cluster"}, 0.5, 1.5);
  AnalysisTree::SimpleCut good_vertex_candidate_cut({branch, "good_vertex_candidate"}, 0.5, 1.5);
  AnalysisTree::SimpleCut good_start_cut({branch, "good_start"}, 0.5, 1.5);
  AnalysisTree::SimpleCut no_pile_up_start_cut({branch, "no_pile_up_start"}, 0.5, 1.5);
  AnalysisTree::SimpleCut no_veto_cut({branch, "no_veto"}, 0.5, 1.5);
  AnalysisTree::SimpleCut good_start_veto_cut({branch, "good_start_veto"}, 0.5, 1.5);
  AnalysisTree::SimpleCut good_start_meta_cut({branch, "good_start_meta"}, 0.5, 1.5);
  std::vector<AnalysisTree::SimpleCut> vector_cuts{
	  vtx_xy_cut,
	  vtx_z_cut,
	  vtx_chi2_cut,
	  good_vertex_cut,
	  good_vertex_candidate_cut,
	  good_start_cut,
	  no_pile_up_start_cut,
	  no_veto_cut,
	  good_start_veto_cut,
	  good_start_meta_cut
  };
  auto *event_cuts = new AnalysisTree::Cuts(name, vector_cuts);
  return event_cuts;
}

AnalysisTree::Cuts *TrackCuts(const std::string &branch, const std::string &name = "HadesGoodVertexTrack") {

  AnalysisTree::SimpleCut dca_xy_cut({branch, "dca_xy"}, -10, 10);
  AnalysisTree::SimpleCut dca_z_cut({branch, "dca_z"}, -10, 10);
  AnalysisTree::SimpleCut chi2_rk_cut({branch, "chi2"}, 0, 100);
  std::vector<AnalysisTree::SimpleCut> vector_cuts{
	  dca_xy_cut,
	  dca_z_cut,
	  chi2_rk_cut
  };
  auto *vertex_tracks_cuts = new AnalysisTree::Cuts(name, vector_cuts);
  return vertex_tracks_cuts;
};

AnalysisTree::Cuts *MetaHitsCuts(const std::string &branch, const std::string &name = "HadesGoodMetaHit") {
  AnalysisTree::SimpleCut meta_match_chi2_cut({branch, "match_quality"}, 0, 3.0);
  auto *tof_cuts = new AnalysisTree::Cuts(name, {meta_match_chi2_cut});
  return tof_cuts;
};
AnalysisTree::Cuts *WallHitsCuts(const std::string &branch, const std::string &name = "HadesGoodWallHit") {
  AnalysisTree::SimpleCut ring_by_ring_cuts({{branch, "ring"}, {branch, "beta"}, {branch, "signal"},
											 {branch, "time"}},
											[](std::vector<double> vars) {
											  double ring = vars.at(0);
											  [[maybe_unused]] double beta = vars.at(1);
											  double signal = vars.at(2);
											  double time = vars.at(3);
											  double c = 2.998e-1; // speed of light in m/s*E+9
											  double time_low = 6.8 / c;
											  if( time < time_low )
												return false;
											  if (1.0 <= ring && ring <= 5) {
												if(signal < 80.0)
												  return false;
												auto time_up = 6.8/0.84/c;
												if( time > time_up )
												  return false;
											  }
											  if ( 6.0 <= ring && ring <= 7.0) {
												if(signal < 85.0)
												  return false;
												auto time_up = 6.8/0.85/c;
												if( time > time_up )
												  return false;
											  }
											  if (8.0 <= ring && ring <= 10.0) {
												if (signal < 88.0)
												  return false;
												auto time_up = 6.8/0.80/c;
												if( time > time_up )
												  return false;
											  }
											  return true;
											});
  auto *wall_cuts = new AnalysisTree::Cuts(name, {ring_by_ring_cuts});
  return wall_cuts;
};

}// namespace AuAu_1_23_AGeV
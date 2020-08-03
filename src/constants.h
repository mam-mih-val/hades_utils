//
// Created by mikhail on 8/2/20.
//

#ifndef HADES_UTILS_SRC_CONSTANTS_H_
#define HADES_UTILS_SRC_CONSTANTS_H_

namespace HadesUtils{
enum class DATA_TYPE {
  AuAu_1_23AGeV, // Apr, 12 data
  AgAg_1_23AGeV, // Mar, 19 data
  AgAg_1_58AGeV, // Mar, 19 data
};

const std::string reco_track_branch_name{ "mdc_vtx_tracks" };
const std::string meta_hits_branch_name{ "meta_hits" };
const std::string wall_hits_branch_name{ "forward_wall_hits" };
const std::string event_header_name{ "event_header" };
const std::string sim_event_header_name{ "sim_header" };
const std::string sim_track_branch_name{ "sim_tracks" };
}

#endif//HADES_UTILS_SRC_CONSTANTS_H_

//
// Created by mikhail on 8/2/20.
//

#ifndef HADES_UTILS_SRC_CUTS_H_
#define HADES_UTILS_SRC_CUTS_H_

#include <AnalysisTree/Cuts.hpp>

#include "au123_cuts.h"
#include "ag123_cuts.h"
#include "constants.h"

namespace HadesUtils {
class Cuts {
public:
 enum class BRANCH_TYPE{
   EVENT_HEADER,
   MDC_TRACKS,
   META_HITS,
   WALL_HITS,
 };
 static AnalysisTree::Cuts* Get( BRANCH_TYPE branch, DATA_TYPE data);
private:
 static AnalysisTree::Cuts* GetAuAu123( BRANCH_TYPE branch);
 static AnalysisTree::Cuts* GetAgAg123( BRANCH_TYPE branch);
 static AnalysisTree::Cuts* GetAgAg158( BRANCH_TYPE branch);
};
}// namespace HadesUtils
#endif//HADES_UTILS_SRC_CUTS_H_

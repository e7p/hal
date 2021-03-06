#pragma once

#include "dataflow_analysis/evaluation/result.h"
#include "dataflow_analysis/output_generation/json.hpp"
#include "dataflow_analysis/processing/result.h"
#include "hal_core/defines.h"

namespace hal
{
    namespace dataflow
    {
        namespace svg_output
        {
            void save_state_to_svg(const std::shared_ptr<Grouping>& state, const std::string m_path, const std::string file_namey);
        }    // namespace svg_output
    }        // namespace dataflow
}    // namespace hal
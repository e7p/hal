#include "netlist/gate_library/gate_type/gate_type_latch.h"

gate_type_latch::gate_type_latch(const std::string& name) : gate_type(name)
{
    m_base_type = base_type::latch;
}

bool gate_type_latch::doCompare(const gate_type& other) const
{
    bool equal                = false;
    const gate_type_latch* gt = dynamic_cast<const gate_type_latch*>(&other);

    if (gt)
    {
        equal = m_data_in_f == gt->get_data_in_function();
        equal &= m_enable_f == gt->get_enable_function();
        equal &= m_set_f == gt->get_set_function();
        equal &= m_reset_f == gt->get_reset_function();
        equal &= m_state_pins == gt->get_state_output_pins();
        equal &= m_inverted_state_pins == gt->get_inverted_state_output_pins();
        equal &= m_special_behavior == gt->get_special_behavior();
    }

    return equal;
}

void gate_type_latch::set_data_in_function(const boolean_function& data_in_f)
{
    m_data_in_f = data_in_f;
}
void gate_type_latch::set_enable_function(const boolean_function& enable_f)
{
    m_enable_f = enable_f;
}

void gate_type_latch::set_set_function(const boolean_function& set_f)
{
    m_set_f = set_f;
}

void gate_type_latch::set_reset_function(const boolean_function& reset_f)
{
    m_reset_f = reset_f;
}

void gate_type_latch::add_state_output_pin(std::string output_pin_name)
{
    m_state_pins.insert(output_pin_name);
}

void gate_type_latch::add_inverted_state_output_pin(std::string output_pin_name)
{
    m_inverted_state_pins.insert(output_pin_name);
}

void gate_type_latch::set_special_behavior(special_behavior sb1, special_behavior sb2)
{
    m_special_behavior = {sb1, sb2};
}

boolean_function gate_type_latch::get_data_in_function() const
{
    return m_data_in_f;
}

boolean_function gate_type_latch::get_enable_function() const
{
    return m_enable_f;
}

boolean_function gate_type_latch::get_set_function() const
{
    return m_set_f;
}

boolean_function gate_type_latch::get_reset_function() const
{
    return m_reset_f;
}

std::unordered_set<std::string> gate_type_latch::get_state_output_pins() const
{
    return m_state_pins;
}

std::unordered_set<std::string> gate_type_latch::get_inverted_state_output_pins() const
{
    return m_inverted_state_pins;
}

std::pair<gate_type::special_behavior, gate_type::special_behavior> gate_type_latch::get_special_behavior() const
{
    return m_special_behavior;
}
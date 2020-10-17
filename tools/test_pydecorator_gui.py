import pydecorator_gui

# create some convenient variables to use later
g_l = [g for g in netlist.get_gates()]
n_l = [n for n in netlist.get_nets()]
m_l = [m for m in netlist.get_modules()]

g = netlist.get_gate_by_id(2)
n = netlist.get_net_by_id(5)
m = netlist.get_module_by_id(1)

# ~~~~~~~~specific select methods

print("------ select_gate ------")
gui.select_gate(g)
gui.select_gate(3)
gui.select_gate([1,2])
gui.select_gate(g_l)
print("------ select_gate named------")
gui.select_gate(gate = g)
gui.select_gate(gate_id = 3)
gui.select_gate(gate_ids = [1,2])
gui.select_gate(gates = g_l)

print("------ select_net ------")
gui.select_net(n)
gui.select_net(6)
gui.select_net([7,8])
gui.select_net(n_l)
print("------ select_net named------")
gui.select_net(net = n)
gui.select_net(net_id = 6)
gui.select_net(net_ids = [7,8])
gui.select_net(nets = n_l)

print("------ select_module ------")
gui.select_module(m)
gui.select_module(1)
gui.select_module([1])
gui.select_module(m_l)
print("------ select_module named------")
gui.select_module(module = m)
gui.select_module(module_id = 1)
gui.select_module(module_ids = [1])
gui.select_module(modules = m_l)

# ~~~~~~~~specific deselect methods

print("------ deselect_gate ------")
gui.deselect_gate(g)
gui.deselect_gate(3)
gui.deselect_gate([1,2])
gui.deselect_gate(g_l)
print("------ deselect_gate named------")
gui.deselect_gate(gate = g)
gui.deselect_gate(gate_id = 3)
gui.deselect_gate(gate_ids = [1,2])
gui.deselect_gate(gates = g_l)

print("------ deselect_net ------")
gui.deselect_net(n)
gui.deselect_net(6)
gui.deselect_net([7,8])
gui.deselect_net(n_l)
print("------ deselect_net named------")
gui.deselect_net(net = n)
gui.deselect_net(net_id = 6)
gui.deselect_net(net_ids = [7,8])
gui.deselect_net(nets = n_l)

print("------ deselect_module ------")
gui.deselect_module(m)
gui.deselect_module(1)
gui.deselect_module([1])
gui.deselect_module(m_l)
print("------ deselect_module named------")
gui.deselect_module(module = m)
gui.deselect_module(module_id = 1)
gui.deselect_module(module_ids = [1])
gui.deselect_module(modules = m_l)

# ~~~~~~~~select method
print("------ select ------")
gui.select(g)
gui.select(net = n)
gui.select(m)
gui.select([1,2,3],[5],[1])
gui.select([1,2,3], module_ids = [1], net_ids = [5,6,4])
gui.select(g_l, modules = [m], nets = n_l)
gui.select(g_l, n_l, m_l)


# ~~~~~~~~getter methods
print("------ getter methods ------")
gui.get_selected_module_ids()
gui.get_selected_gate_ids()
gui.get_selected_net_ids()
gui.get_selected_gates()
gui.get_selected_nets()
gui.get_selected_modules()
gui.get_selected_item_ids()
gui.get_selected_items()

# ~~~~~~~~deselect method
print("------ deselect ------")
gui.deselect(g)
gui.deselect(net = n)
gui.deselect(m)
gui.deselect([1,2,3],[5],[1])
gui.deselect([1,2,3], module_ids = [1], net_ids = [5,6,4])
gui.deselect(g_l, modules = [m], nets = n_l)
gui.deselect(g_l, n_l, m_l)
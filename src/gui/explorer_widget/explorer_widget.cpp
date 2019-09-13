#include "gui/explorer_widget/explorer_widget.h"

#include "gui/gui_globals.h"
#include "gui/netlist_model/netlist_item.h"
#include "gui/netlist_model/netlist_model.h"
#include "gui/netlist_model/netlist_proxy_model.h"
#include "gui/searchbar/searchbar.h"

#include <QHeaderView>
#include <QItemSelectionModel>
#include <QMenu>
#include <QModelIndex>
#include <QRegExp>
#include <QShortcut>
#include <QTreeView>
#include <QVBoxLayout>

explorer_widget::explorer_widget(QWidget* parent) : content_widget("Explorer", parent),
    m_tree_view(new QTreeView(this)),
    m_searchbar(new searchbar(this)),
    m_netlist_proxy_model(new netlist_proxy_model(this)),
    m_show_gates(true),
    m_show_nets(true)
{
    connect(m_tree_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &explorer_widget::handle_intern_selection_changed);
    connect(m_tree_view, &QTreeView::customContextMenuRequested, this, &explorer_widget::handle_custom_context_menu_requested);
    connect(m_searchbar, &searchbar::text_edited, this, &explorer_widget::filter);

    m_netlist_proxy_model->setFilterKeyColumn(-1);
    m_netlist_proxy_model->setRecursiveFilteringEnabled(true);
    m_netlist_proxy_model->setSourceModel(g_netlist_relay.get_netlist_model());

    //m_tree_view->setAnimated(true); ADD TO SETTINGS
    m_tree_view->setModel(m_netlist_proxy_model);
    //m_tree_view->setModel(g_netlist_relay.get_netlist_model());
    m_tree_view->setContextMenuPolicy(Qt::CustomContextMenu);
    m_tree_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tree_view->setFrameStyle(QFrame::NoFrame);
    m_tree_view->setHeaderHidden(true);
    m_tree_view->setUniformRowHeights(true);

    m_content_layout->addWidget(m_tree_view);
    m_content_layout->addWidget(m_searchbar);

    m_searchbar->hide();

    m_ignore_selection_change = false;

    g_selection_relay.register_sender(this, name());
}

void explorer_widget::setup_toolbar(toolbar* toolbar)
{
    Q_UNUSED(toolbar)

    //toolbar->addAction(m_filter_action);
}

QList<QShortcut*> explorer_widget::create_shortcuts()
{
    QShortcut* search_shortcut = new QShortcut(QKeySequence(tr("Ctrl+f")), this);
    connect(search_shortcut, &QShortcut::activated, this, &explorer_widget::toggle_searchbar);

    QList<QShortcut*> list;
    list.append(search_shortcut);

    return list;
}

bool explorer_widget::show_gates() const
{
    return m_show_gates;
}

bool explorer_widget::show_nets() const
{
    return m_show_nets;
}

void explorer_widget::toggle_searchbar()
{
    if (m_searchbar->isHidden())
    {
        m_searchbar->show();
        m_searchbar->setFocus();
    }
    else
        m_searchbar->hide();
}

void explorer_widget::filter(const QString& text)
{
    QRegExp regex(text);

    if (regex.isValid())
        m_netlist_proxy_model->setFilterRegExp(regex);
}

void explorer_widget::handle_intern_selection_changed(const QItemSelection& selected, const QItemSelection& deselected)
{
    Q_UNUSED(selected)
    Q_UNUSED(deselected)

//    if (m_ignore_selection_change)
//    {
//        m_ignore_selection_change = false;
//        return;
//    }

//    QModelIndexList current_selections = selected.indexes();
//    QSet<tree_navigation_item*> already_processed_items;
//    QList<u32> net_ids;
//    QList<u32> gate_ids;
//    QList<u32> submod_ids;
//    for (const QModelIndex& index : current_selections)
//    {
//        auto item = static_cast<tree_navigation_item*>(m_tree_navigation_proxy_model->mapToSource(index).internalPointer());
//        if (item && !already_processed_items.contains(item))
//        {
//            already_processed_items.insert(item);
//            switch (item->get_type())
//            {
//                case tree_navigation_item::item_type::gate:
//                    gate_ids.append(item->data(tree_navigation_model::ID_COLUMN).toInt());
//                    break;
//                case tree_navigation_item::item_type::net:
//                    net_ids.append(item->data(tree_navigation_model::ID_COLUMN).toInt());
//                    break;
//                case tree_navigation_item::item_type::module:
//                    submod_ids.append(item->data(tree_navigation_model::ID_COLUMN).toInt());
//                    break;
//                case tree_navigation_item::item_type::structure:
//                    break;
//                case tree_navigation_item::item_type::ignore:
//                    break;
//                default:
//                    break;
//            }
//        }
//    }
//    g_selection_relay.relay_combined_selection(this, gate_ids, net_ids, submod_ids);
}

void explorer_widget::handle_custom_context_menu_requested(const QPoint& point)
{
    QModelIndex index = m_tree_view->indexAt(point);

    if (!index.isValid())
        return;

    if (g_netlist_relay.get_netlist_model()->get_item(m_netlist_proxy_model->mapToSource(index))->type() != hal::item_type::module)
        return;

    QMenu context_menu;

    QAction select_action("Select Module", &context_menu);
    QAction add_selection_action("Add Selection to Module", &context_menu);
    QAction add_child_action("Add Child Module", &context_menu);
    QAction change_name_action("Change Module Name", &context_menu);
    QAction change_color_action("Change Module Color", &context_menu);
    QAction delete_action("Delete Module", &context_menu);

    context_menu.addAction(&select_action);
    context_menu.addAction(&add_selection_action);
    context_menu.addAction(&add_child_action);
    context_menu.addAction(&change_name_action);
    context_menu.addAction(&change_color_action);
    context_menu.addAction(&delete_action);

    QAction* clicked = context_menu.exec(m_tree_view->viewport()->mapToGlobal(point));

    if (!clicked)
        return;

    if (clicked == &add_selection_action)
        g_netlist_relay.debug_add_selection_to_module(g_netlist_relay.get_netlist_model()->get_item(m_netlist_proxy_model->mapToSource(index))->id());

    if (clicked == &add_child_action)
        g_netlist_relay.debug_add_child_module(g_netlist_relay.get_netlist_model()->get_item(m_netlist_proxy_model->mapToSource(index))->id());

    if (clicked == &change_color_action)
        g_netlist_relay.debug_change_module_color(g_netlist_relay.get_netlist_model()->get_item(m_netlist_proxy_model->mapToSource(index))->id());
}
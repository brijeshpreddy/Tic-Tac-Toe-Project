#include "agent_graph_search.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

  tic_tac_graph_search::tic_tac_graph_search(tic_tac_database x) {
    present_game_state = x;
  }

  tic_tac_graph_search::

  graph_node::graph_node(tic_tac_database x) {
    tmp = x;
  }

  graph_edge graph_node::add_edge() {
    graph_edge *root;
    root = new graph_edge;
  }

  void graph_node::connect_edge(graph_node next) {
    graph_edge tmp = add_edge();
    graph_edge *traverse;
    tmp->original_node = this;
    tmp->destination_node = next;
    traverse = edge_table_forward;
    while (traverse->next_node != NULL)
      traverse = traverse->next_node;
    traverse->next_node = tmp;
    tmp->prev_edge = traverse;
    tmp->next_edge = NULL;
  }

  graph_edge::graph_edge() {
    cost = 100;
    next_edge = NULL;
    prev_edge = NULL;
    original_edge = NULL;
    destination_node = NULL;
  }

  

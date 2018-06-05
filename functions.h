/**
 * @file functions.h
 * @brief C library containing the functions used by the program.
 */
#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>

void insert_queue(int v);
int delete_queue();
int isEmpty_queue();
void create_graph();
int indegree(int v);
void procedure_1();
void procedure_2();
void graph_dfs(struct a_graph *graph,int no_nodes,int start_node,int prenum);
int pop_end_list(struct a_list_node *head);
int pop_begining_list(struct a_list_node *head);
void push_begining_list(struct a_list_node *head,int new_element_value);
void print_adj_matrix(graph);
void init_graph(graph);
int get_adj_matrix_value(graph,  row_index, column_index);
void set_adj_matrix_value(graph,  row_index, column_index, element_value);
options(choice);
#endif // MAIN_FUNCTIONS_H

/**
 * @file functions.c
 * @brief C library containing the functions used for topological sort.
 * @author Popescu Cristina-Maria
 */
#include <stdio.h>
#include "functions.h"
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#define MAX 100
#include <assert.h>
#include <limits.h>

int n;
int adj[MAX][MAX];

int queue[MAX], front = -1,rear = -1;

void insert_queue(int vertex)
{/**
     * @fn void insert_queue(int vertex)
     * @brief Inserts queue in the program.
     * @param vertex The number of nodes.
     *
     * The function inserts a queue based on the number of vertices.
     */
	if (rear == MAX-1)
		printf("\nQueue Overflow\n");
	else
	{
		if (front == -1)
			front = 0;
		rear = rear+1;
		queue[rear] = vertex ;
	}
}

int isEmpty_queue()
{/**
     * @fn int isEmpty_queue()
     * @brief Empties the queue.
     *
     * The function empties the queue.
     */
	if(front == -1 || front > rear )
		return 1;
	else
		return 0;
}

int delete_queue()
{/**
     * @fn int delete_queue()
     * @brief Deletes the queue.
     *
     * The function deletes the queue.
     */
	int del_item;
	if (front == -1 || front > rear)
	{
		printf("\nQueue Underflow\n");
		exit(1);
	}
	else
	{
		del_item = queue[front];
		front = front+1;
		return del_item;
	}
}

int indegree(int v)
{/**
     * @fn int indegree(int v)
     * @brief Intern grade of a vertex.
     * @param v
     *
     * The function determines the inner grade of a vertex.
     */
	int i,in_deg = 0;
	for(i=0; i<n; i++)
		if(adj[i][v] == 1)
			in_deg++;
	return in_deg;
}

void create_graph()
{/**
     * @fn void create_graph()
     * @brief Creates a graph.
     *
     * The function creates a graph.
     */
	int i,max_edges,origin,destin;

	printf("\nEnter number of vertices : ");
	scanf("%d",&n);
	max_edges = n*(n-1);

	for(i=1; i<=max_edges; i++)
	{
		printf("\nEnter edge %d(-1 -1 to quit): ",i);
		scanf("%d %d",&origin,&destin);

		if((origin == -1) && (destin == -1))
			break;

		if( origin >= n || destin >= n || origin<0 || destin<0)
		{
			printf("\nInvalid edge!\n");
			i--;
		}
		else
			adj[origin][destin] = 1;
	}
}

void procedure_1()
{/**
     * @fn void procedure_1()
     * @brief Sorts the graph using a topological sort.
     * @param i,v,count,topo_order[MAX],indeg[MAX].
     *
     * The function sorts the graph using a topological sort based on the intern grade of the vertices.
     */
	int i,v,count,topo_order[MAX],indeg[MAX];

	create_graph();

	for(i=0;i<n;i++)
	{
		indeg[i] = indegree(i);
		if( indeg[i] == 0 )
			insert_queue(i);
	}

	count = 0;

	while(  !isEmpty_queue( ) && count < n )
	{
		v = delete_queue();
    	topo_order[++count] = v;
		for(i=0; i<n; i++)
		{
			if(adj[v][i] == 1)
			{
				adj[v][i] = 0;
				indeg[i] = indeg[i]-1;
				if(indeg[i] == 0)
					insert_queue(i);
			}
		}
	}

	if( count < n )
	{
		printf("\nNo topological ordering possible, graph contains cycle\n");
		exit(1);
	}
	printf("\nVertices in topological order are :\n");
	for(i=1; i<=count; i++)
		printf( "%d ",topo_order[i] );
	printf("\n");

}

struct a_graph {
    int no_nodes;
    int init;
    int *adj_matrix;
};

struct a_list_node{
    int info;
    struct a_list_node *next;
};

void set_adj_matrix_value(struct a_graph* graph,int row_index,int column_index,int element_value){
    /**
     * @fn void set_adj_matrix_value(struct a_graph* graph,int row_index,int column_index,int element_value)
     * @brief Adjacent matrix.
     * @param struct a_graph* graph,int row_index,int column_index,int element_value.
     *
     * The function makes the adjacent matrix of the graph.
     */
    int position;
    assert(row_index <= graph->no_nodes);
    assert(column_index <= graph->no_nodes);
    position = row_index * graph->no_nodes + column_index;
    *(graph->adj_matrix + position) = element_value;
}


int get_adj_matrix_value(struct a_graph *graph, int row_index, int column_index) {
    /**
     * @fn int get_adj_matrix_value(struct a_graph *graph, int row_index, int column_index)
     * @brief Adjacent matrix.
     * @param struct a_graph *graph, int row_index, int column_index.
     *
     * The function returns a position from the matrix.
     */
    int position;

    assert(row_index < graph->no_nodes);
    assert(column_index < graph->no_nodes);
    if (graph->init == 1){
        position = row_index * graph->no_nodes + column_index;
        return *(graph->adj_matrix + position);
    }else{
        printf("Please read the graph first");
        return -1;
    }
}

void init_graph(struct a_graph *graph){
   /**
     * @fn void init_graph(struct a_graph *graph)
     * @brief Creates a graph.
     * @param struct a_graph *graph.
     * The function creates a graph.
     */
    int iterator_rows;
    int iterator_columns;
    int aux;

    printf("\nGive no nodes = ");
    scanf("%d", &graph->no_nodes);
    graph->init = 1;
    graph->adj_matrix = calloc(graph->no_nodes * graph->no_nodes,sizeof(int));

    assert((graph->no_nodes * graph->no_nodes) > 0);

    for (iterator_rows = 0; iterator_rows < graph->no_nodes; iterator_rows++ ){
        for (iterator_columns = 0; iterator_columns < graph->no_nodes; iterator_columns++ ){
            printf(" graph[%d][%d]= ",iterator_rows, iterator_columns);
            scanf("%d", &aux);
            set_adj_matrix_value(graph, iterator_rows, iterator_columns, aux);
        }
    }
}

void print_adj_matrix(struct a_graph *graph){
   /**
     * @fn void print_adj_matrix(struct a_graph *graph)
     * @brief Prints the adjacent matrix.
     * @param struct a_graph *graph.
     * The function prints the adjacent matrix of the graph.
     */
    int iterator_rows;
    int iterator_columns;
    int aux;

    if (graph->init == 1){
        printf("=== Printing adj_matrix ===\n");
        for (iterator_rows = 0; iterator_rows < graph->no_nodes; iterator_rows++ ){
            for (iterator_columns = 0; iterator_columns < graph->no_nodes; iterator_columns++ ){
                aux = get_adj_matrix_value(graph, iterator_rows, iterator_columns);
                printf(" %d ", aux);
            }
            printf("\n");
        }
    }else{
        printf("\nPlease read the adj_matrix first");
    }
}

void push_begining_list(struct a_list_node *head,int new_element_value){
    /**
     * @fn void push_begining_list(struct a_list_node *head,int new_element_value)
     * @brief Adds an element to the beggining.
     * @param struct a_list_node *head,int new_element_value.
     * The function adds an element to the beggining of the list.
     */
    struct a_list_node *next_element;
    struct a_list_node *new_element;

    next_element = head->next;
    new_element = malloc(sizeof(struct a_list_node));
    new_element->info = new_element_value;
    new_element->next = head->next;
    head->next = new_element;
}

int pop_begining_list(struct a_list_node *head){
    /**
     * @fn int pop_begining_list(struct a_list_node *head)
     * @brief Deletes an element from the beggining.
     * @param struct a_list_node *head.
     * The function deletes an element from the beggining of the list.
     */
    struct a_list_node *deleted_element;
    int aux;

    if (head->next != NULL) {
        deleted_element = head->next;
        aux = deleted_element->info;
        head->next = deleted_element->next;
        free(deleted_element);
        return aux;
    }else{
        printf("\n The list is empty");
        return -1;
    }
}

int pop_end_list(struct a_list_node *head) {
    /**
     * @fn int pop_end_list(struct a_list_node *head)
     * @brief Deletes an element from the end.
     * @param struct a_list_node *head.
     * The function deletes an element from the end of the list.
     */
    struct a_list_node *deleted_element;
    struct a_list_node *iterator;
    int aux;

    if (head->next != NULL) {
        for (iterator = head; iterator->next->next != NULL; iterator = iterator->next);
        deleted_element = iterator->next;
        aux = deleted_element->info;
        iterator->next = deleted_element->next;
        free(deleted_element);
        return aux;
    } else {
        printf("\n The list is empty");
        return -1;
    }
}

void graph_dfs(struct a_graph *graph,int no_nodes, int start_node, int prenum[1000]){
    /**
     * @fn void graph_dfs(struct a_graph *graph,int no_nodes, int start_node, int prenum[1000])
     * @brief Algorithm used to traverse the graph.
     * @param struct a_graph *graph,int no_nodes, int start_node, int prenum[1000].
     * The function traverses the graph using the DFS method(depth first search).
     */
    struct a_list_node *head_stack;
    int *visited;
    int column_index;
    int row_index;
    int aux;
    int current_node;
    int count = 0;

    head_stack = calloc(1, sizeof(struct a_list_node));
    head_stack->next = NULL;
    head_stack->info = 0;
    visited = calloc((no_nodes), sizeof(int));
    push_begining_list(head_stack, start_node);
    visited[start_node] = 1;

    while (head_stack->next != NULL){
        current_node = pop_begining_list(head_stack);
        prenum[current_node] = prenum[current_node] + 1;
        for(column_index = 0; column_index < no_nodes; column_index++){
            aux = get_adj_matrix_value(graph, current_node, column_index);
            if ( (aux != 0) && ( (visited[column_index]) == 0 )){
                push_begining_list(head_stack, column_index);
                visited[column_index] = 1;
            }
        }
    }

    free(head_stack);
    free(visited);


}

void procedure_2()
{/**
     * @fn void procedure_2()
     * @brief  Sorts the graph using a topological sort.
     * @param int final_vector[1000],j,imax,max,m,k,struct a_graph *graph_1.
     * The function sorts the graph using a topological sort based on DFS.
     */
int final_vector[1000],j,imax,max;
    struct a_graph *graph_1;
    graph_1 = calloc(1, sizeof(struct a_graph));
    init_graph(graph_1);
    int m;
    m = graph_1->no_nodes;
    print_adj_matrix(graph_1);
    int k,prenum[1000],postnum[1000];
    for(k = 0; k < m; k++)
        {
        prenum[k]=0;
        postnum[k]=0;
        }
    for(k = 0; k < m; k++)
            graph_dfs(graph_1,m,k,prenum);
    for(k = 0; k < m; k++)
        if ( prenum[k] != 0)
             postnum[k] = 2*m-1-prenum[k];
            else {
                prenum[k] = 2*n-1;
                postnum[k] = 2*n;
                }
    printf("Prenum: ");
    for(k = 0; k < m;k++ )
        printf("%d,",prenum[k]);
    printf("\n");
    printf("Postnum: ");
    for(k = 0; k < m;k++ )
        printf("%d,",postnum[k]);
    printf("\n");
    for(k = 0; k < m; k++)
    {
        max = -1;
        imax = -1;
        for (j = 0; j < m; j++)
            if ( postnum[j] > max )
            {
             max = postnum[j];
             imax = j;
            }
        postnum[imax]=0;
        final_vector[k] = imax++;
    }
    for(k = 0; k < m; k++)
        printf("%d,",final_vector[k]+1);
}
options(choice)
{
  while( 1 > 0 )
    {
        printf("\nPress 1 for using the first procedure:");
        printf("\nPress 2 for using the second procedure:");
        printf("\nPress 3 to exit :");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice){

            case 1:
                printf("\nExecuting first procedure");
                Sleep(500);
                printf(".");
                Sleep(500);
                printf(".");
                Sleep(500);
                printf(".\n");
                procedure_1;
                break;

            case 2:
                printf("\nExecuting second procedure");
                Sleep(500);
                printf(".");
                Sleep(500);
                printf(".");
                Sleep(500);
                printf(".\n");
                procedure_2;
                printf("\n");
                break;

            case 3:
                 printf("\nFarewell.");
                 printf("\n");
                 exit(0);
                break;
            default: printf("\nYou have entered an invalid choice. Please try again");
        }
    }
}



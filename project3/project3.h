//
//  project3.h
//  
//
//  Created by Yi on 15/4/18.
//
//

#ifndef project3_h
#define project3_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct vertex{
    int ID;
    int age;
    int gender;
    int marital_status;
    int race;
    int birthplace;
    int language;
    int occupation;
    int income;
    struct vertex * * vert_dense; //array of neighbor vertedx in dense graph
    struct vertex * * vert_sparse; //array of neighbor vertedx in sparse graph
    struct edge * * ed_dense;//array of its edge in dense graph
    struct edge * * ed_sparse; //array of its edge in sparse graph
    int visited;
}Vertex;

typedef struct edge{
    int weight;
    struct vertex * vert1;
    struct vertex * vert2;
    int visited;
}Edge;

typedef struct friend_value{
    float UED; //un-normalized Euclidean Distance
    struct vertex * vert1; //vertex it have
    struct vertex * vert2; //vertex it have
}Frd_value;

typedef struct node_query1{
    int length;
    struct vertex * node;;
    struct node_query1 * next;
}Node_query1;

typedef struct output_query1{
    int length;
    int vertex_id;
    struct output_query1 * next;
}Output_query1;

Vertex * vertex_create(int id, int age,int gender, int marital_status, int race, int birthplace,int language, int occupation, int income, int number_user);
Vertex * * vertexbus_load(FILE * fp, char * buffer, int number_user);
Frd_value * * frd_calculate(Vertex * * vertex_bus, int number_user, float * most_UED);
void traverse_UED(float *most_UED, int number_user, int dense_parameter, int sparse_parameter, Frd_value * * frd_list, Vertex ** vertex_bus);
void addNeighbor_dense(Vertex * vertex_add, Vertex * vertex_beingadd);
void addNeighbor_sparse(Vertex * vertex_add, Vertex * vertex_beingadd);
void addedge_dense(Vertex * vertex_add, Edge * edge_beingadd);
void addedge_sparse(Vertex * vertex_add, Edge * edge_beingadd);
void query1(int source_id, Vertex * * vertex_bus, int number_user,Output_query1 * output_head_den, Output_query1 * output_spar);
Node_query1 * create_node(Edge * edge, Vertex * source, int length);
Node_query1 * add_node(Node_query1 * node, Node_query1 * head);
Output_query1 * create_ouputnode(int length, int id);
Output_query1 * add_outputnode(Output_query1 * node, Output_query1 * head);
Node_query1 * delete_node(Node_query1 * node, Node_query1 * head);
void query2(Output_query1 * output_dense, Output_query1 * output_sparse, int query_a, int* larger_dense, int* larger_sparse);
void query3(int source_id, Vertex ** vertex_bus, int number_user, int* neighbor_dense_id, int* neighbor_sparse_id, int *dense_neighbor_num, int* sparse_neighbor_num);
void query4(int source_id, Vertex ** vertex_bus, int number_user, int *twohop_dense, int * twohop_sparse, int * twohop_dense_num, int * twohop_sparse_num);
float UED_value_help(Vertex * pointer1, Vertex * pointer2);
Edge * create_edge(int distance, Frd_value* edge);
void * sort(int* array_need_sort, int number);

#endif

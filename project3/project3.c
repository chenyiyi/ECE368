//
//  main.c
//  project3_version2
//
//  Created by Yi on 15/4/21.
//  Copyright (c) 2015年 Yi. All rights reserved.
//

//Student name :Chen Yiyi  
//ID : 0026406971

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



int main(int argc, const char * argv[]) {
    // insert code here...
    if(argc != 2){
        fprintf(stderr, "Need input file.\n");
        return 0; //EXIT_FAILURE CHECK!
    }
    
    FILE * vertex_file = fopen(argv[1], "r");
    if (!vertex_file) {
        fprintf(stderr, "Fail to open source file.\n");
    }
    
    //get some initial value
    char * basic_value = malloc(400 * sizeof(char));
    fgets(basic_value, 399, vertex_file);
    int number_user = atoi(strtok(basic_value, " ,")); //number of users
    float dense_parameter = atof(strtok(NULL, " ,")); //dense parameter to create map
    float sparse_parameter = atof(strtok(NULL, " ,")); //sparse parameter to create map
    int source_id = atoi(strtok(NULL, " ,")); //source id needed for query 1
    float query_a = atof(strtok(NULL, " ,")); //a value needed for query 2
    
    int dense_para_int = (int)(dense_parameter*100); //convert to int to for rest of the project
    int spar_para_int = (int)(sparse_parameter*100); //convert to int to for rest of the project
    int query_int = (int)(query_a*100); //convert to int to for rest of the project
    
    
    //load vertex version1
    char * buffer = malloc(400 * sizeof(char)); //to store one line of input file;
    Vertex * * vertex_bus = vertexbus_load(vertex_file, buffer, number_user);
    
    //calculate un-normalized Euclidean Distance and store it
    float * most_UED = malloc(sizeof(int));
    *most_UED = 0;
    Frd_value * * ued_list = malloc(sizeof(Frd_value*)*((number_user*(number_user-1))/2+1)); //list to store ued value
    ued_list = frd_calculate(vertex_bus, number_user, most_UED);
    
    //traverse UED_list and create edge and build social network
    traverse_UED(most_UED, number_user, dense_para_int, spar_para_int, ued_list, vertex_bus);
    
    //query one
    Output_query1 * output_head_den = (Output_query1*)malloc(sizeof(Output_query1)); //to store output
    Output_query1 * output_head_spar = (Output_query1*)malloc(sizeof(Output_query1)); //to store output
    query1(source_id, vertex_bus, number_user, output_head_den, output_head_spar);
    
    //query two //need to check!!!!!!!!!!!!!!!!!!!!!!!!
    int * larger_dense = (int*)malloc(sizeof(int));
    int * larger_sparse = (int*)malloc(sizeof(int));
    query2(output_head_den, output_head_spar, query_int, larger_dense, larger_sparse);
    
    //query three
    int * store_id_dense = malloc(sizeof(int)*number_user);
    int * store_id_sparse = malloc(sizeof(int)*number_user);
    int * dense_neighbor_number = malloc(sizeof(int));
    int * sparse_neighbor_number = malloc(sizeof(int));
    query3(source_id, vertex_bus, number_user, store_id_dense, store_id_sparse, dense_neighbor_number, sparse_neighbor_number);
    
    //query four
    int * storetwohop_id_dense = malloc(sizeof(int)*number_user);
    int * storetwohop_id_sparse = malloc(sizeof(int)*number_user);
    int * dense_twohop_number = malloc(sizeof(int));
    int * sparse_twohop_number = malloc(sizeof(int));
    query4(source_id, vertex_bus, number_user, storetwohop_id_dense, storetwohop_id_sparse, dense_twohop_number, sparse_twohop_number);
    
    //query five
    int count_five=1;
    int total_five_dense=0;
    int total_five_sparse=0;
    while (count_five<=number_user) {
        int * store_id_dense_temp = malloc(sizeof(int)*number_user);
        int * store_id_sparse_temp = malloc(sizeof(int)*number_user);
        int * dense_neighbor_number_temp = malloc(sizeof(int));
        int * sparse_neighbor_number_temp = malloc(sizeof(int));
        query3(count_five, vertex_bus, number_user, store_id_dense_temp, store_id_sparse_temp, dense_neighbor_number_temp, sparse_neighbor_number_temp);
        total_five_dense = total_five_dense + *dense_neighbor_number_temp;
        total_five_sparse = total_five_sparse + *sparse_neighbor_number_temp;
        count_five++;
    }
    
    //!!!!!

    
    //query six
    int count_six=1;
    int total_six_dense=0;
    int total_six_sparse=0;
    while (count_six<=number_user) {
        int * store_twoid_dense_temp = malloc(sizeof(int)*number_user);
        int * store_twoid_sparse_temp = malloc(sizeof(int)*number_user);
        int * dense_twoneighbor_number_temp = malloc(sizeof(int));
        int * sparse_twoneighbor_number_temp = malloc(sizeof(int));
        query4(count_six, vertex_bus, number_user, store_twoid_dense_temp, store_twoid_sparse_temp, dense_twoneighbor_number_temp, sparse_twoneighbor_number_temp);
        total_six_dense = total_six_dense + *dense_twoneighbor_number_temp;
        total_six_sparse = total_six_sparse + *sparse_twoneighbor_number_temp;
        count_six++;
    }
    
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //OUTPUT SECTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //PRINT OUT THE ANSWER!!!!!!!!!!!!!!!!!!!!!!!
    
    //OUTPUT FOR QUERY ONE
    //output_head_den              //output_head_spar
    float shortest_den = output_head_den->length;
    Output_query1 * temp;
    temp = output_head_den;
    while (temp != 0) {
        if (temp->length < shortest_den) {
            shortest_den = temp->length;
        }
        temp = temp->next;
    }
    int * query1_output = malloc(sizeof(int)*number_user);
    int q=0;
    temp = output_head_den;
    while (temp != 0) {
        if (temp->length == shortest_den) {
            query1_output[q] = temp->vertex_id;
	    q++;
        }
        temp = temp->next;
    }
    printf("%.2f",(float)shortest_den/100);
    sort(query1_output, number_user);
    
    
    //OUTPUT FOR QUERY TWO
    //larger_dense            //larger_sparse
    printf("%d\n", *larger_dense);
    
    //OUTPUT FOR QUERY THREE
    //store_id_dense          //store_id_sparse
    //dense_neighbor_number   //sparse_neighbor_number
    printf("%d", *dense_neighbor_number);
    sort(store_id_dense, number_user);
    
    //OUTPUT FOR QUERY FOUR
    //storetwohop_id_dense    //storetwohop_id_sparse
    //dense_twohop_number     //sparse_twohop_number
    printf("%d", *dense_twohop_number);
    sort(storetwohop_id_dense, number_user);
    
    
    //OUTPUT FOR QUERY FIVE
    //total_five_dense
    //total_five_sparse
    float query5_output = (float)total_five_dense/number_user;
    printf("%.2f\n", query5_output);
    
    //OUTPUT FOR QUERY SIX
    //total_six_dense
    //total_six_sparse
    printf("%.2f\n", (float)total_six_dense/number_user);
    printf("\n");


    //output section for sparse graph 
    //OUTPUT FOR QUERY ONE
    //output_head_spar
    float shortest_spar = output_head_spar->length;
    Output_query1 * temp_spar;
    temp_spar = output_head_spar;
    while (temp_spar!= 0) {
        if (temp_spar->length < shortest_spar) {
            shortest_spar = temp_spar->length;
        }
        temp_spar = temp_spar->next;
    }
    int * query1_output_spar = malloc(sizeof(int)*number_user);
    int p=0;
    temp_spar = output_head_spar;
    while (temp_spar != 0) {
        if (temp_spar->length == shortest_spar) {
            query1_output_spar[p] = temp_spar->vertex_id;
	    p++;
        }
        temp_spar = temp_spar->next;
    }
    printf("%.2f",(float)shortest_spar/100);
    sort(query1_output_spar, number_user);
    
    //OUTPUT FOR QUERY TWO
    //larger_dense            //larger_sparse
    printf("%d\n", *larger_sparse);
    
    //OUTPUT FOR QUERY THREE
    //store_id_dense          //store_id_sparse
    //dense_neighbor_number   //sparse_neighbor_number
    printf("%d", *sparse_neighbor_number);
    sort(store_id_sparse, number_user);
    
    //OUTPUT FOR QUERY FOUR
    //storetwohop_id_dense    //storetwohop_id_sparse
    //dense_twohop_number     //sparse_twohop_number
    printf("%d", *sparse_twohop_number);
    sort(storetwohop_id_sparse, number_user);
    
    
    //OUTPUT FOR QUERY FIVE
    //total_five_dense
    //total_five_sparse
    float query5_output_sparse = (float)total_five_sparse/number_user;
    printf("%.2f\n", query5_output_sparse);
    
    //OUTPUT FOR QUERY SIX
    //total_six_dense
    //total_six_sparse
    printf("%.2f\n", (float)total_six_sparse/number_user);
    printf("\n");
    
    return 0;
}

Vertex * * vertexbus_load(FILE * fp, char * buffer, int number_user)
{
    Vertex * * vertex_bus = (Vertex**)malloc( (number_user+1) * sizeof(Vertex *));
    fgets(buffer, 399, fp);
    int i =0;
    int vertex_position = 0;
    while (i<number_user) {
        int id = atoi(strtok(buffer, " ,"));
        int age = atoi(strtok(NULL, " ,"));
        int gender = atoi(strtok(NULL, " ,"));
        int marital_status = atoi(strtok(NULL, " ,"));
        int race = atoi(strtok(NULL, " ,"));
        int birthplace = atoi(strtok(NULL, " ,"));
        int language = atoi(strtok(NULL, " ,"));
        int occupation = atoi(strtok(NULL, " ,"));
        int income = atoi(strtok(NULL, " ,"));
        Vertex * vertex_ini = vertex_create(id, age, gender, marital_status, race, birthplace, language, occupation, income, number_user); //create vertex with initial status
        vertex_bus[vertex_position] = vertex_ini; //put initial vertex into the array of vertex
        vertex_position ++; //move to next place to hold vertex
        fgets(buffer, 399, fp);
        i++;
    }
    return vertex_bus;
}

Vertex * vertex_create(int id, int age,int gender, int marital_status, int race, int birthplace,int language, int occupation, int income, int number_user)
{
    int i;
    //create vertex
    Vertex * intial_ver = (Vertex*)malloc(sizeof(Vertex));
    intial_ver->ID =id;
    intial_ver->age =age;
    intial_ver->gender =gender;
    intial_ver->marital_status =marital_status;
    intial_ver->race =race;
    intial_ver->birthplace =birthplace;
    intial_ver->language =language;
    intial_ver->occupation =occupation;
    intial_ver->income =income;
    intial_ver->vert_dense = (Vertex**)malloc( (number_user+1) * sizeof(Vertex *));
    for (i=0; i<number_user; i++) {
        intial_ver->vert_dense[i] = (Vertex*)malloc(sizeof(Vertex));
        intial_ver->vert_dense[i] = 0;
    }
    intial_ver->vert_sparse = (Vertex**)malloc( (number_user+1) * sizeof(Vertex *));
    for (i=0; i<number_user; i++) {
        intial_ver->vert_sparse[i] = (Vertex*)malloc(sizeof(Vertex));
        intial_ver->vert_sparse[i] = 0;
    }
    intial_ver->ed_dense = (Edge**)malloc( (number_user+1) * sizeof(Edge *));
    for (i=0; i<number_user; i++) {
        intial_ver->ed_dense[i] = (Edge*)malloc(sizeof(Edge));
        intial_ver->ed_dense[i] = 0;
    }
    intial_ver->ed_sparse = (Edge**)malloc( (number_user+1) * sizeof(Edge *));
    for (i=0; i<number_user; i++) {
        intial_ver->ed_sparse[i] = (Edge*)malloc(sizeof(Edge));
        intial_ver->ed_sparse[i] = 0;
    }
    intial_ver->visited = 0; //not visited
    return intial_ver;
}

Frd_value * *frd_calculate(Vertex * * vertex_bus, int number_user, float * most_UED){
    Frd_value * * frd_list = (Frd_value **)malloc(sizeof(Frd_value*)* ((number_user*(number_user-1))/2)+1); //list to store ued value
    Vertex * pointer_1; //used to calculate distance between two vertex
    Vertex * pointer_2;
    int index_list =0; //index to put edge into the list
    int index_calculate_po1 = 0;
    int index_calculate_po2 = index_calculate_po1+1;
    float ued_largest = 0;
    float UED_value=0; //un-normalized value
    pointer_1 = vertex_bus[index_calculate_po1];
    pointer_2 = vertex_bus[index_calculate_po2];
    while (pointer_1 != NULL) {
        while(pointer_2 != NULL){
            UED_value = UED_value_help(pointer_1, pointer_2);
            if (UED_value > ued_largest) {
                ued_largest = UED_value;
            }
            frd_list[index_list] = (Frd_value*)malloc(sizeof(Frd_value));
            frd_list[index_list]->UED = UED_value;
            frd_list[index_list]->vert1 = pointer_1;
            frd_list[index_list]->vert2 = pointer_2;
            index_calculate_po2++;
            pointer_2 = vertex_bus[index_calculate_po2];
            index_list++;
        }
        index_calculate_po1++;
        index_calculate_po2 = index_calculate_po1+1;
        pointer_1 = vertex_bus[index_calculate_po1];
        pointer_2 = vertex_bus[index_calculate_po2];
    }
    *most_UED = ued_largest;
    return frd_list;
}

float UED_value_help(Vertex * pointer1, Vertex * pointer2){
    float age = (pointer1->age - pointer2->age) * (pointer1->age - pointer2->age);
    float gender = (pointer1->gender - pointer2->gender) * (pointer1->gender - pointer2->gender);
    float marital_status = (pointer1->marital_status - pointer2->marital_status) * (pointer1->marital_status - pointer2->marital_status);
    float race = (pointer1->race - pointer2->race) * (pointer1->race- pointer2->race);
    float birthplace = (pointer1->birthplace - pointer2->birthplace) * (pointer1->birthplace - pointer2->birthplace);
    float language = (pointer1->language - pointer2->language) * (pointer1->language - pointer2->language);
    float occupation = (pointer1->occupation - pointer2->occupation) * (pointer1->occupation - pointer2->occupation);
    float income = (pointer1->income - pointer2->income) * (pointer1->income - pointer2->income);
    float ued;
    ued = sqrt(age+gender+marital_status+race+birthplace+language+occupation+income);
    return ued;
}

void traverse_UED(float *most_UED, int number_user, int dense_parameter, int sparse_parameter, Frd_value * * frd_list, Vertex ** vertex_list){
    int i;
    int vertex_count1;
    int vertex_count2;
    float friend_distance; //parameter to build graph
    //Edge * * edge_list_dense = malloc(sizeof(Edge*)*((number_user*(number_user-1))/2+1)); //list to store edge in dense
    //Edge * * edge_list_sparse = malloc(sizeof(Edge*)*((number_user*(number_user-1))/2+1)); //list to store edge in sparse
    for (i=0; i<((number_user*(number_user-1))/2); i++) {
        friend_distance = 1-((frd_list[i]->UED)/(*most_UED));
        if ((int)(friend_distance*100) > dense_parameter) {
            //create edge for dense graph
            Edge * edge_dense = create_edge((int)(friend_distance*100), frd_list[i]);
            vertex_count1 = (frd_list[i]->vert1->ID)-1;
            addNeighbor_dense(vertex_list[vertex_count1], edge_dense->vert2);
            addedge_dense(vertex_list[vertex_count1], edge_dense);
            vertex_count2 = (frd_list[i]->vert2->ID)-1;
            addNeighbor_dense(vertex_list[vertex_count2], edge_dense->vert1);
            addedge_dense(vertex_list[vertex_count2], edge_dense);
            
            /*for (vertex_count=0; vertex_count<number_user; vertex_count++) {
                if (vertex_list[vertex_count]->ID == edge_dense->vert1->ID) {
                    addNeighbor_dense(vertex_list[vertex_count], edge_dense->vert2);
                    addedge_dense(vertex_list[vertex_count], edge_dense);
                }
                if (vertex_list[vertex_count]->ID == edge_dense->vert2->ID) {
                    addNeighbor_dense(vertex_list[vertex_count], edge_dense->vert1);
                    addedge_dense(vertex_list[vertex_count], edge_dense);
                }
            }*/
        }
        if ((int)(friend_distance*100) > sparse_parameter) {
            //create edge for sparse graph
            Edge * edge_sparse = create_edge((int)(friend_distance*100), frd_list[i]);
            vertex_count1 = (frd_list[i]->vert1->ID)-1;
            addNeighbor_sparse(vertex_list[vertex_count1], edge_sparse->vert2);
            addedge_sparse(vertex_list[vertex_count1], edge_sparse);
            vertex_count2 = (frd_list[i]->vert2->ID)-1;
            addNeighbor_sparse(vertex_list[vertex_count2], edge_sparse->vert1);
            addedge_sparse(vertex_list[vertex_count2], edge_sparse);
            /*for (vertex_count=0; vertex_count<number_user; vertex_count++) {
                if (vertex_list[vertex_count]->ID == edge_sparse->vert1->ID) {
                    addNeighbor_sparse(vertex_list[vertex_count], edge_sparse->vert2);
                    addedge_sparse(vertex_list[vertex_count], edge_sparse);
                }
                if (vertex_list[vertex_count]->ID == edge_sparse->vert2->ID) {
                    addNeighbor_sparse(vertex_list[vertex_count], edge_sparse->vert1);
                    addedge_sparse(vertex_list[vertex_count], edge_sparse);
                }
            }*/
        }
    }
}

Edge * create_edge(int distance, Frd_value* edge){
    Edge * edge_dense = (Edge*)malloc(sizeof(Edge*));
    edge_dense->weight = distance;
    edge_dense->vert1 = (Vertex*)malloc(sizeof(Vertex));
    edge_dense->vert2 = (Vertex*)malloc(sizeof(Vertex));
    edge_dense->vert1 = edge->vert1;
    edge_dense->vert2 = edge->vert2;
    edge_dense->visited = 0;
    return edge_dense;
}

void addNeighbor_dense(Vertex * vertex_add, Vertex * vertex_beingadd){
    int i=0;
    while (vertex_add->vert_dense[i] !=0) {
        i++;
    }
    vertex_add->vert_dense[i] = vertex_beingadd;
}

void addNeighbor_sparse(Vertex * vertex_add, Vertex * vertex_beingadd){
    int i=0;
    while (vertex_add->vert_sparse[i] !=0) {
        i++;
    }
    vertex_add->vert_sparse[i] = vertex_beingadd;
}

void addedge_dense(Vertex * vertex_add, Edge * edge_beingadd){
    int i=0;
    while (vertex_add->ed_dense[i] !=0) {
        i++;
    }
    vertex_add->ed_dense[i] = edge_beingadd;
}

void addedge_sparse(Vertex * vertex_add, Edge * edge_beingadd){
    int i=0;
    while (vertex_add->ed_sparse[i] !=0) {
        i++;
    }
    vertex_add->ed_sparse[i] = edge_beingadd;
}

//DOING PART2!!!!!!!!!!!!!!
//query1!!!!!!!!!!!!!!!!!!!!!!!!
void query1(int source_id, Vertex * * vertex_bus, int number_user, Output_query1 * output_head_den, Output_query1 * output_spar ){
    Vertex * source_ver = malloc(sizeof(Vertex));
    int i=0; //index for vertex_bus
    int h=0; //index for edge
    int shortest = 100000; //to find shortes path
    Node_query1 * search_node = (Node_query1*)malloc(sizeof(Node_query1)); //traverse list to find shortest path
    Node_query1 * head = (Node_query1*)malloc(sizeof(Node_query1));
    Output_query1 * output_head = (Output_query1*)malloc(sizeof(Output_query1)); //to store output
    Output_query1 * output_node;
    output_head = NULL;
    head = NULL;
    int finish=0; //announce finishing status
    while (vertex_bus[i]->ID != source_id) {
        i++;
    }
    source_ver = vertex_bus[i];
    vertex_bus[i]->visited =1;
    //for dense graph!!!!!!!
    while (source_ver->ed_dense[h]!= 0) {
        Node_query1 * node;
        node = create_node(source_ver->ed_dense[h], source_ver, 0);
        head = add_node(node, head);
        source_ver->ed_dense[h]->visited =1;
        h++;
    }
    //above finish the initial linked list for shortest path search loop needed below!!!!!!!
    while (head != NULL ) {
        search_node = head;
        while (search_node != NULL) {
            if (search_node->length < shortest) {
                shortest = search_node->length;
            }
            search_node = search_node->next;
        }
        search_node = head;
        while (search_node->length != shortest) {
            search_node = search_node->next;
        }
        i=0;
        h=0;
        while (search_node->node->ID != vertex_bus[i]->ID) {
            i++;
        }
        if (vertex_bus[i]->visited ==0) {
            output_node = create_ouputnode(search_node->length, search_node->node->ID);
            output_head = add_outputnode(output_node, output_head);//put shortest length & vertex id to output
            finish++;
            vertex_bus[i]->visited =1; //already visited
            head = delete_node(search_node, head);//delete node
            while (vertex_bus[i]->ed_dense[h]!= 0) {
                if(vertex_bus[i]->ed_dense[h]->visited == 0){
                    Node_query1 * node ;
                    node = create_node(vertex_bus[i]->ed_dense[h], vertex_bus[i], search_node->length);
                    head = add_node(node, head);
                    vertex_bus[i]->ed_dense[h]->visited =1;
                }
                h++;
            }
        }
        else{
            head = delete_node(search_node, head);//delete node
            while (vertex_bus[i]->ed_dense[h]!= 0 ) {
                if(vertex_bus[i]->ed_dense[h]->visited == 0){
                    Node_query1 * node;
                    node = create_node(vertex_bus[i]->ed_dense[h], vertex_bus[i], search_node->length);
                    head = add_node(node, head);
                    vertex_bus[i]->ed_dense[h]->visited =1;
                }
                h++;
            }
        }
        shortest = 100000;
    }
    *output_head_den = *output_head;
    //for sparse graph!!!!!!!!
    i=0;
    h=0;
    shortest = 100000;
    Node_query1 * search_node_sparse = (Node_query1*)malloc(sizeof(Node_query1)); //traverse list to find shortest path
    Node_query1 * head_sparse = (Node_query1*)malloc(sizeof(Node_query1));
    Output_query1 * output_head_sparse = (Output_query1*)malloc(sizeof(Output_query1)); //to store output
    Output_query1 * output_node_sparse;
    output_head_sparse = NULL;
    head_sparse = NULL;
    int finish_sparse =0;
    while (source_ver->ed_sparse[h]!= 0) {
        Node_query1 * node_sparse;
        node_sparse = create_node(source_ver->ed_sparse[h], source_ver, 0);
        head_sparse = add_node(node_sparse, head_sparse);
        source_ver->ed_sparse[h]->visited =1;
        h++;
    }
    //!!!!!CLEAR VISITED
    int clear;
    for (clear=0; clear<number_user; clear++) {
        if (vertex_bus[clear]->ID != source_id) {
            vertex_bus[clear]->visited =0;
        }
    }
    //above finish the initial linked list for shortest path search loop needed below!!!!!!!
    while (head_sparse != NULL) {
        search_node_sparse = head_sparse;
        while (search_node_sparse != NULL) {
            if (search_node_sparse->length < shortest) {
                shortest = search_node_sparse->length;
            }
            search_node_sparse = search_node_sparse->next;
        }
        search_node_sparse = head_sparse;
        while (search_node_sparse->length != shortest) {
            search_node_sparse = search_node_sparse->next;
        }
        i=0;
        h=0;
        while (search_node_sparse->node->ID != vertex_bus[i]->ID) {
            i++;
        }
        if (vertex_bus[i]->visited ==0) {
            output_node_sparse = create_ouputnode(search_node_sparse->length, search_node_sparse->node->ID);
            output_head_sparse = add_outputnode(output_node_sparse, output_head_sparse);//put shortest length & vertex id to output
            finish_sparse++;
            vertex_bus[i]->visited =1; //already visited
            head_sparse = delete_node(search_node_sparse, head_sparse);//delete node
            while (vertex_bus[i]->ed_sparse[h]!= 0) {
                if(vertex_bus[i]->ed_sparse[h]->visited == 0){
                    Node_query1 * node;
                    node = create_node(vertex_bus[i]->ed_sparse[h], vertex_bus[i], search_node_sparse->length);
                    head_sparse = add_node(node, head_sparse);
                    vertex_bus[i]->ed_sparse[h]->visited=1;
                }
                h++;
            }
        }
        else{
            head_sparse = delete_node(head_sparse, search_node_sparse);//delete node
            while (vertex_bus[i]->ed_sparse[h]!= 0 ) {
                if(vertex_bus[i]->ed_sparse[h]->visited == 0){
                    Node_query1 * node;
                    node = create_node(vertex_bus[i]->ed_sparse[h], vertex_bus[i], search_node_sparse->length);
                    head_sparse = add_node(node, head_sparse);
                    vertex_bus[i]->ed_sparse[h]->visited=1;
                }
                h++;
            }
        }
        shortest = 100000;
    }
    *output_spar = *output_head_sparse;
}

Node_query1 * create_node(Edge * edge, Vertex * source, int length_usededge){
    Node_query1 * node = (Node_query1*)malloc(sizeof(Node_query1));
    node->length =(edge->weight+length_usededge);
    if (edge->vert1->ID != source->ID) {
        node->node = edge->vert1;
    }
    else{
        node->node = edge->vert2;
    }
    node->next = NULL;
    return node;
}

Node_query1 * add_node(Node_query1 * node, Node_query1 * head){
    if (head == NULL) {
        return node;
    }
    node->next = head;
    return node;
}

Node_query1 * delete_node(Node_query1 * node, Node_query1 * head){
    if (head->next == NULL) {
        return NULL;
    }
    if (head == node) {
        return head->next;
    }
    Node_query1 * temp = head;
    while (temp->next != NULL && temp->next != node) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        return NULL;
    }
    temp->next = temp->next->next;

    return head;
}

Output_query1 * create_ouputnode(int length, int id){
    Output_query1 * node = (Output_query1*)malloc(sizeof(Output_query1));
    node->length =length;
    node->vertex_id = id;
    node->next = NULL;
    return node;
}

Output_query1 * add_outputnode(Output_query1 * node, Output_query1 * head){
    if (head == NULL) {
        return node;
    }
    node->next = head;
    return node;
}

//query2!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void  query2(Output_query1 * output_dense, Output_query1 * output_sparse, int query_a, int* larger_dense, int* larger_sparse){
    int value = query_a;
    int number_nodes_dense=0;
    int number_nodes_sparse=0;
    while (output_dense != NULL) {
        if (output_dense->length < value) {
            number_nodes_dense++;
        }
        output_dense = output_dense->next;
    }
    *larger_dense = number_nodes_dense;
    while (output_sparse != NULL) {
        if (output_sparse->length < value) {
            number_nodes_sparse++;
        }
        output_sparse = output_sparse->next;
    }
    *larger_sparse = number_nodes_sparse;
    //put the number of nodes to the output file!!!!!!!!!
}

//query3!!!!!!!!!!!!!!!!!!!!!
void query3(int source_id, Vertex ** vertex_bus, int number_user, int *neighbor_dense, int * neighbor_sparse, int * neighbor_dense_num, int * neighbor_sparse_num){
    int i=0;
    int h=0;
    int number_neighbor_dense=0;
    int number_neighbor_sparse=0;
    int * store_id_dense = malloc(sizeof(int)*number_user);
    int * store_id_sparse = malloc(sizeof(int)*number_user);
    while (vertex_bus[i]->ID != source_id) {
        i++;
    }
    while (vertex_bus[i]->vert_dense[h]!=NULL) {
        store_id_dense[h] = vertex_bus[i]->vert_dense[h]->ID;
        number_neighbor_dense++;
        h++;
    }
    h=0;
    while (vertex_bus[i]->vert_sparse[h]!=NULL) {
        store_id_sparse[h] = vertex_bus[i]->vert_sparse[h]->ID;
        number_neighbor_sparse++;
        h++;
    }
    for (h =0;  store_id_dense[h]!=0; h++) {
        neighbor_dense[h] = store_id_dense[h];
    }
    for (h =0;  store_id_sparse[h]!=0; h++) {
        neighbor_sparse[h] = store_id_sparse[h];
    }
    *neighbor_dense_num = number_neighbor_dense;
    *neighbor_sparse_num = number_neighbor_sparse;
    //output the result to the file!!!!!!!!!!!!!!!!!!
    //!!!!!!!!!!!!!!!!!!!!!!!!
}

//query4!!!!!!!!!!!!!!!!!!!
void query4(int source_id, Vertex ** vertex_bus, int number_user, int *twohop_dense, int * twohop_sparse, int * twohop_dense_num, int * twohop_sparse_num){
    int i=0;
    int h=0;//first neighbor
    int two=0; //jump neighbor
    int index =0; //index to store id
    int number_twoneighbor_dense=0;
    int number_twoneighbor_sparse=0;
    int clear;
    for (clear=0; clear<number_user; clear++) {
        if (vertex_bus[clear]->ID == source_id) {
            vertex_bus[clear]->visited =1;
        }else{
            vertex_bus[clear]->visited =0;}
    }
    int * store_id_dense = malloc(sizeof(int)*number_user);
    while (index < number_user-1) {
        store_id_dense[index] =0;
        index++;
    }
    index = 0;
    int * store_id_sparse = malloc(sizeof(int)*number_user);
    while (index < number_user-1) {
        store_id_sparse[index] =0;
        index++;
    }
    index =0;
    while (vertex_bus[i]->ID != source_id) {
        i++;
    }
    while (vertex_bus[i]->vert_dense[h]!=NULL) {
        while(vertex_bus[i]->vert_dense[h]->vert_dense[two] != NULL ){
            if (vertex_bus[i]->vert_dense[h]->vert_dense[two]->visited !=1 ) {
                //&& vertex_bus[i]->vert_dense[h]->vert_dense[two]->ID != vertex_bus[i]->ID
                store_id_dense[index] =vertex_bus[i]->vert_dense[h]->vert_dense[two]->ID;
                vertex_bus[i]->vert_dense[h]->vert_dense[two]->visited =1;
                number_twoneighbor_dense++;
                two++;
                index++;
            }else{
                two++;
            }
        }
        h++;
        two =0;
    }
    int clear_visited;
    for (clear_visited=0; clear_visited<number_user; clear_visited++) {
        if (vertex_bus[clear_visited]->ID==source_id) {
            vertex_bus[clear_visited]->visited=1;
        }else{
            vertex_bus[clear_visited]->visited =0;}
    }
    h=0;//first neighbor
    two=0; //jump neighbor
    index =0; //index to store id
    while (vertex_bus[i]->vert_sparse[h]!=NULL) {
        while(vertex_bus[i]->vert_sparse[h]->vert_sparse[two] != NULL ){
            if (vertex_bus[i]->vert_sparse[h]->vert_sparse[two]->visited !=1) {
                //&& vertex_bus[i]->vert_sparse[h]->vert_sparse[two]->ID != vertex_bus[i]->ID
                store_id_sparse[index] =vertex_bus[i]->vert_sparse[h]->vert_sparse[two]->ID;
                vertex_bus[i]->vert_sparse[h]->vert_sparse[two]->visited =1;
                number_twoneighbor_sparse++;
                two++;
                index++;
            }else{
                two++;
            }
        }
        h++;
        two =0;
    }
    for (h =0;  store_id_dense[h]!=0; h++) {
        twohop_dense[h] = store_id_dense[h];
    }
    for (h =0;  store_id_sparse[h]!=0; h++) {
        twohop_sparse[h] = store_id_sparse[h];
    }
    *twohop_dense_num = number_twoneighbor_dense;
    *twohop_sparse_num = number_twoneighbor_sparse;
    //output file needed!!!!!!!!!!!!!!!!!!!!!!
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

//sort function
void * sort(int* array_need_sort, int number){
    int i;
    int j;
    int a;
    for (i = 0; i < number; ++i)
    {
        for (j = i + 1; j < number; ++j)
        {
            if (array_need_sort[i] > array_need_sort[j])
            {
                a =  array_need_sort[i];
                array_need_sort[i] = array_need_sort[j];
                array_need_sort[j] = a;
            }
        }
    }
    for (i = 0; i < number; ++i){
        if (array_need_sort[i] != 0) {
            printf(",%d", array_need_sort[i]);
        }
    }
    printf("\n");
    return NULL;
}

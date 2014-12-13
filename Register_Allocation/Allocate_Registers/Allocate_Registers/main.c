#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>


// adjacency list implementation of graph using linked list in c
static int max_alloc_num = 0;

typedef struct adj_node {
	int index;
	int reg_assigned;
	struct adj_node * next;
}adj_node;

typedef struct tmp_info{
	int tmp_amt;
	int first_val;
	char first_ascii_rep[3];
	int second_val;
	char second_ascii_rep[3];
	int third_val;
	char third_ascii_rep[3];
}tmp_info;

void makeadj(struct adj_node *nod, int adj, int register_assigned) {
	adj_node *newadj = (adj_node *)malloc(sizeof(adj_node));
	newadj->index = adj;
	newadj->next = NULL;
	newadj->reg_assigned = register_assigned;
	while (nod->next != NULL)nod = nod->next;
	nod->next = newadj;
}


// function declerations
int findFreeReg(adj_node* graph, adj_node* vertx_adj);
int allocate_free_reg(int* status_array);
static void replaceAllString(char *buf, const char *orig, const char *replace);
tmp_info get_tmp_info(char* buf);
int calc_temp_decimal_val(char* buf, int offset);
int myFree(adj_node* graph, int num_vertex);

void allocate_reg_to_temp(adj_node* graph);

int main(int argc, char *argv[])
{
	FILE* fp;
	adj_node* graph;
	int init_first_iteration = 0;
	int num1, num2;
	char buf[256];

	fp = fopen("../../Liveness_Analysis/VerifyCodeGen/InterferenceGraph.txt", "r");
	if (NULL == fp){
		perror("ERROR");
		return -1;
	}

	fscanf(fp, "%s", buf);
	fscanf(fp, "%s", buf);
	while (EOF != fscanf(fp, "%d %s %d %s", &num1, buf, &num2, buf)){
		if (init_first_iteration == 0){
			max_alloc_num = num1;
			init_first_iteration = 1;
		}
		if (-1 == num1){										//for this we have to "place" -1 at the end of InterferenceGraph.txt
			break;
		}

		if ((num1 > num2) && (num1 > max_alloc_num)){
			max_alloc_num = num1;
		}
		else if ((num2 > num1) && (num2 > max_alloc_num)){
			max_alloc_num = num2;
		}
	}

	max_alloc_num++;
	graph = (adj_node*)malloc(sizeof(adj_node)*max_alloc_num); // we increment max_alloc_num to as to get X+1 cells in our allocated array. 
															   // we will not be using cell [0] as of all regular c prog's, we'll start from 1 to max_alloc_num+1 

	int i;
	for (i = 1; i < max_alloc_num; i++){
		graph[i].index = i;
		graph[i].next = NULL;
	}

	// set file-pointer to the start of the file. 
	fseek(fp, 0, SEEK_SET);
	fscanf(fp, "%s", buf);
	fscanf(fp, "%s", buf);

	int vertex_handled = 0;		// It's ok to init this variable to 0, code is self-explainatory 

	while (EOF != fscanf(fp, "%d %s %d %s", &num1, buf, &num2, buf)){
		if (-1 == num1){		//for this we have to "place" -1 at the end of InterferenceGraph.txt
			break;
		}

		if (vertex_handled < num1){
			vertex_handled = num1;
		}
		makeadj(&graph[vertex_handled], num2, -1);	//add the num2 vertex to the current vertex_handled adj-list
		makeadj(&graph[num2], vertex_handled, -1);
	}

	for (i = 1; i < max_alloc_num; i++){
		graph[i].reg_assigned = -1;
	}
	for (i = 1; i < max_alloc_num; i++){
		if (-1 == findFreeReg(graph, &(graph[i]))){
			printf("Error, can't allocate registers properly, not enoguh registers to meet the demands, Quitting\n\n");
			fclose(fp);
			return -1;
		}

	}

	for (i = 1; i < max_alloc_num; i++){
		if (NULL == graph[i].next){
			graph[i].reg_assigned = 0;
		}
	}


	allocate_reg_to_temp(graph);
	if (-1 == myFree(graph, max_alloc_num)){
		printf("Error freeing allocated memory, exiting\n");
		exit(-1);
	} //free is successful

	fclose(fp);

	return(1);
}



int findFreeReg(adj_node* graph, adj_node* vertx_adj){

	int free_status_array[8]; //used for t0 - t7 bitmap status
	int i;
	int free_register;

	adj_node* temp_vertx = NULL;

	// initalize the status array
	for (i = 0; i < 8; i++){
		free_status_array[i] = 0; 
	}

// set up a updated status of the reg-allocation of the current register being handled, after this section our free_status_array will represent
// avillable register (that we can allocate) as cells with value '0', cells with value '1' cannot be allocated for this vertex.

	int curr_vertex_neighbours_num = 0;
	temp_vertx = vertx_adj;
	
	while (temp_vertx->next != NULL){
		curr_vertex_neighbours_num++;
		temp_vertx = temp_vertx->next;
	}

	temp_vertx = vertx_adj;
	adj_node *curr_neighbour = NULL;
	for (i = 0; i < curr_vertex_neighbours_num; i++){
		temp_vertx = temp_vertx->next;
		curr_neighbour = &(graph[temp_vertx->index]);
		while (curr_neighbour != NULL){
			if ((graph[curr_neighbour->index]).reg_assigned != -1){
				free_status_array[(graph[curr_neighbour->index]).reg_assigned] = 1;
			}
			curr_neighbour = curr_neighbour->next;
		}
	}

	// now let's allocate our vertex a new register, if we fail we return -1 and exit with a failure notice to the user.
	if ((free_register = allocate_free_reg(&free_status_array)) == -1){
		printf("Error, can't allocate registers properly, not enoguh registers to meet the demands, Quitting\n\n");
		return -1;
	}

	// If we reached here, it means we found an avillable register to allocate for our currently handled vertex, lets allocate it
	vertx_adj->reg_assigned = free_register;

	return (1);
}

int allocate_free_reg(int* status_array){
	int i;

	// If we reached here, it means that the temp we're working on has collided with atleast one other temp
	for (i = 0; i < 8; i++){
		if (status_array[i] == 0){
			return i;
		}
	}
	
	// if we reach here, it means that for our current vertex being handled, his "neigbours" are occupping all avillable registers (t0 to t7)
	// which means we cannot allocate him an avilalble register, so we FAIL
	return -1; 
}


void allocate_reg_to_temp(adj_node* graph){

	FILE* fp = fopen("../../../IR_&_MIPS_Gen/CodeGen/CodeGeneration/tiger_prog.s", "r");
	if (fp == NULL){
		perror("ERROR");
	}
	FILE* outf = fopen("temp.txt", "w+");
	if (outf == NULL){
		perror("ERROR");
	}
	FILE* outf_final = fopen("MIPS_ASM_Prog.s", "w");
	if (outf_final == NULL){
		perror("ERROR");
	}
	int temp_asm_line_cnt;
	tmp_info temp_info;
	int temp_dec_val;
	char r;

	char workbuf[512];
	char replace_buf[4] = "$t ";
	char origin_buf[9] = "Temp_";

	if (!fp || !outf){
		perror("ERROR");
		exit; 
	}

	/* Psuedo-code:
	   1. for each line of the input file, read the file
		1.1 parse and how many TEMP are there in our current line. there could be no more then 3
		1.2 for each of these TEMP's understand what is their DECIMAL value
		1.3 run the replace for each of the TEMP'S
		1.4 write modified line to outputfile
	*/

	while (NULL != fgets(workbuf, 255, fp)){
		temp_info = get_tmp_info(workbuf);

		int i;
		for (i = 1; i <= temp_info.tmp_amt; i++){
			if (i == 1){
				//set origin buf
				origin_buf[5] = temp_info.first_ascii_rep[0];
				origin_buf[6] = temp_info.first_ascii_rep[1];
				origin_buf[7] = temp_info.first_ascii_rep[2]; //at this place, our origin buffer we wish to replace is set
				origin_buf[8] = '\0';
				temp_dec_val = temp_info.first_val;
				if ((temp_dec_val - 100) < max_alloc_num){
					r = ((char)graph[temp_dec_val - 100].reg_assigned) + '0';
					replace_buf[2] = r;
					replace_buf[3] = '\0';
					replaceAllString(workbuf, origin_buf, replace_buf);
				}
			
			} else if (i == 2){
				//set origin buf
				origin_buf[5] = temp_info.second_ascii_rep[0];
				origin_buf[6] = temp_info.second_ascii_rep[1];
				origin_buf[7] = temp_info.second_ascii_rep[2]; //at this place, our origin buffer we wish to replace is set
				origin_buf[8] = '\0';
				temp_dec_val = temp_info.second_val;
				if ((temp_dec_val - 100) < max_alloc_num){
					r = ((char)graph[temp_dec_val - 100].reg_assigned) + '0';
					replace_buf[2] = r;
					replace_buf[3] = '\0';
					replaceAllString(workbuf, origin_buf, replace_buf);
				}
			} else {
				//set origin buf
				origin_buf[5] = temp_info.third_ascii_rep[0];
				origin_buf[6] = temp_info.third_ascii_rep[1];
				origin_buf[7] = temp_info.third_ascii_rep[2]; //at this place, our origin buffer we wish to replace is set
				origin_buf[8] = '\0';
				temp_dec_val = temp_info.third_val;
				if ((temp_dec_val - 100) < max_alloc_num){
					r = ((char)graph[temp_dec_val - 100].reg_assigned) + '0';
					replace_buf[2] = r;
					replace_buf[3] = '\0';
					replaceAllString(workbuf, origin_buf, replace_buf);
				}
			}
		}
		// after the for-loop, our workbuf from the current line we were working on is updated and replaced, now all that is left 
		// is to write it to our output file
		fputs(workbuf, outf);
		
	}


	// Scan the file one more time, and replace all "lonely" vertex's (represented as Temp_***) with $t9
	fseek(outf, SEEK_SET, 0);
	replace_buf[0] = '$';
	replace_buf[1] = 't';
	replace_buf[2] = '9';
	replace_buf[3] = '\0';

	while (NULL != fgets(workbuf, 255, outf)){
		temp_info = get_tmp_info(workbuf);

		int i;
		for (i = 1; i <= temp_info.tmp_amt; i++){
			if (i == 1){
				//set origin buf
				origin_buf[5] = temp_info.first_ascii_rep[0];
				origin_buf[6] = temp_info.first_ascii_rep[1];
				origin_buf[7] = temp_info.first_ascii_rep[2]; //at this place, our origin buffer we wish to replace is set
				origin_buf[8] = '\0';
				replaceAllString(workbuf, origin_buf, replace_buf);
			}
		}
		// after the for-loop, our workbuf from the current line we were working on is updated and replaced, now all that is left 
		// is to write it to our output file
		fputs(workbuf, outf_final);
	}

	// end file scan
	fclose(fp);
	fclose(outf);
	fclose(outf_final);
}

tmp_info get_tmp_info(char* buf){

	char ch = buf[0];
	int offset = 0;
	int char_cnt = 0;
	int temp_cnt;
	tmp_info temp_info;


	// count number of chars in the string provided (alt: use strlen)
	offset = 0;
	while (buf[offset] != '\n'){
		char_cnt++;
		offset++;
	}
	offset = 0;

	temp_info.tmp_amt = 0;
	temp_info.first_val = 0;
	temp_info.second_val = 0;
	temp_info.third_val = 0;

	while ((offset + 5) <= char_cnt){
		if ((buf[offset] == 'T') && (buf[offset + 1] == 'e') && (buf[offset + 2] == 'm') && (buf[offset + 3] == 'p') && (buf[offset + 4] == '_')){
			temp_info.tmp_amt++;

			if (temp_info.first_val == 0){				//this is the first temp we encounter
				temp_info.first_val = calc_temp_decimal_val(buf, offset + 5);
				temp_info.first_ascii_rep[0] = buf[offset + 5];
				temp_info.first_ascii_rep[1] = buf[offset + 6];
				temp_info.first_ascii_rep[2] = buf[offset + 7];
			}
			else if (temp_info.second_val == 0){		//this is the 2nd temp we encounter
				temp_info.second_val = calc_temp_decimal_val(buf, offset + 5);
				temp_info.second_ascii_rep[0] = buf[offset + 5];
				temp_info.second_ascii_rep[1] = buf[offset + 6];
				temp_info.second_ascii_rep[2] = buf[offset + 7];
			}
			else{										//third temp we encounter
				temp_info.third_val = calc_temp_decimal_val(buf, offset + 5);
				temp_info.third_ascii_rep[0] = buf[offset + 5];
				temp_info.third_ascii_rep[1] = buf[offset + 6];
				temp_info.third_ascii_rep[2] = buf[offset + 7];
			}

			offset += 5;
		}
		offset++;
	}

	return temp_info;

}


int calc_temp_decimal_val(char* buf, int offset) {

	int hundrads, tens, units;

	hundrads = (buf[offset] - '0') * 100;
	tens = (buf[offset + 1] - '0') * 10;
	units = (buf[offset + 2] - '0');

	return (hundrads + tens + units);
}




static void replaceAllString(char *buf, const char *orig, const char *replace)
{
	int olen, rlen;
	char *s, *d;
	char *tmpbuf;

	if (!buf || !*buf || !orig || !*orig || !replace)
		return;

	tmpbuf = malloc(strlen(buf) + 1);
	if (tmpbuf == NULL)
		return;


	olen = strlen(orig);
	rlen = strlen(replace);

	s = buf;
	d = tmpbuf;

	while (*s) {
		if (strncmp(s, orig, olen) == 0) {
			strcpy(d, replace);
			s += olen;
			d += rlen;
		}
		else
			*d++ = *s++;
	}

	*d = '\0';

	strcpy(buf, tmpbuf);
	free(tmpbuf);
}

int myFree(adj_node* graph, int num_vertex){
	adj_node* nodeptr, *nodeptr2;
	int i;

	for (i = 1; i < num_vertex; i++){
		nodeptr = graph[i].next;
		while (nodeptr){
			nodeptr2 = nodeptr;
			nodeptr = nodeptr->next;
			free(nodeptr2);
		}
	}

	free(graph);
	return(1);
}
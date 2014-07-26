#include "gunrock_clusters.h"
#include <string.h>

// Forward declaration for testing.
int _ij_to_csc(int num_nodes, int num_edges, int* ij_mat, 
	       int* csc_col_offsets, int* csc_row_indices);
int _csr_to_ij(int num_nodes, int num_edges, 
	       int* csr_row_offsets, int *csr_col_indicies, 
	       int* ij_mat);


int _create_simple_td_graph(graph_t *graph)
{
  size_t num_nodes = 7;
  size_t num_edges = 15;
  size_t top_nodes = 3;

  unsigned int row_offsets[8] = {0,3,6,9,11,14,15,15};
  int col_indices[15] = {1,2,3,0,2,4,3,4,5,5,6,2,5,6,6};
  
  graph->numNodes = num_nodes;
  graph->numValues = num_edges;
  graph->rowValueOffsets = (int*) malloc(sizeof(int) * num_nodes+1);
  graph->colOffsets = (int*) malloc(sizeof(int) * num_edges);

  memcpy(graph->rowValueOffsets, (int*)row_offsets, (num_nodes+1) * sizeof(int));
  memcpy(graph->colOffsets, (int*)col_indices, num_edges * sizeof(int));

  return 0;  
}

int _destroy_simple_td_graph(graph_t *graph)
{
  if(graph->rowValueOffsets) free(graph->rowValueOffsets);
  if(graph->colOffsets) free(graph->colOffsets);
  return 0;
}

int _print_small_array(int* arr, int len){
  printf("{ ");
  for(int i=0; i < len; ++i) {
    printf("%d", arr[i]);
    if (i < len - 1)
      printf(", ");
    else
      printf("}");
  }

  return 0;
}

int test_csr_to_ij()
{
  graph_t td_graph;

  printf("Test CSR to IJ\n");
  int num_nodes = 7;
  int num_edges = 15;

  unsigned int row_offsets[8] = {0,3,6,9,11,14,15,15};
  int col_indices[15] = {1,2,3,0,2,4,3,4,5,5,6,2,5,6,6};
  int ij_mat[30];
  
  printf("---> row_offsets\n");
  printf("-------> ");
  _print_small_array((int*)row_offsets, num_nodes+1);
  printf("\n");

  printf("---> col_indices\n");
  printf("-------> ");
  _print_small_array((int*)col_indices, num_edges);
  printf("\n");

  _csr_to_ij(num_nodes, num_edges, row_offsets, col_indices, ij_mat);
  printf("---> ij_mat\n");
  printf("------> ");
  _print_small_array(ij_mat, 30);
  printf("\n");

  return 0;
}


int test_gunrock_graph_convert()
{
  graph_t td_graph;
  struct GunrockGraph gr_graph;

  printf("Test Gunrock Graph Convert\n");

  _create_simple_td_graph(&td_graph);
  td_to_gunrock(&td_graph, &gr_graph);

  printf("---> gunrock row_offsets\n");
  printf("-----------> ");
  _print_small_array((int*)gr_graph.row_offsets, gr_graph.num_nodes+1);
  printf("\n");

  printf("---> gunrock col_indices\n");
  printf("-----------> ");
  _print_small_array((int*)gr_graph.col_indices, gr_graph.num_edges);
  printf("\n");


  printf("---> gunrock col_offsets\n");
  printf("-----------> ");
  _print_small_array((int*)gr_graph.col_offsets, gr_graph.num_nodes+1);
  printf("\n");

  printf("---> gunrock row_indices\n");
  printf("-----------> ");
  _print_small_array((int*)gr_graph.row_indices, gr_graph.num_edges);
  printf("\n");


  return 0;
}


int test_gunrock_topk()
{
  int top_nodes = 10;

  // malloc output result arrays
  struct GunrockGraph *graph_output =
    (struct GunrockGraph*)malloc(sizeof(struct GunrockGraph));
  int *node_ids          = (int*)malloc(sizeof(int) * top_nodes);
  int *centrality_values = (int*)malloc(sizeof(int) * top_nodes);

  return 0;
}


int main(int argc, char** argv)
{
  int ret = 0;
  ret |= test_csr_to_ij();
  ret |= test_gunrock_graph_convert();
  ret |= test_gunrock_topk();
  return ret;
}

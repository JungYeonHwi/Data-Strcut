#include <stdio.h>

#include "graph.h"

int main() {
   Graph g;
   construct(&g, "input.txt");
   print_graph(&g);
   /*
   List 0 = [1, 9]
   List 1 = [2, 3]
   List 2 = [1, 4]
   List 3 = [5, 8]
   List 4 = [6, 7]
   0 1 1 1 1
   1 0 1 0 0
   1 1 0 0 0
   1 0 0 0 1
   1 0 0 1 0
   */

   interval v = {5, 8};
   interval u = {2, 4};
   int is_adj = adjacent(&g, v, u);  // Error (vertex u is not in g)
   if (is_adj) {
      printf("is adj : %d\n", is_adj);
   }

   interval x = {1, 9};
   is_adj = adjacent(&g, v, x);
   if (is_adj) {
      printf("is adj : %d\n", is_adj);  // is adj : 1
   }

   interval t = {1, 8};
   int d = degree(&g, t);  // Error
   if (d) {
      printf("degree : %d\n", d);
   }

   d = degree(&g, x);  // {1, 9}
   if (d) {
      printf("degree : %d\n", d);  // degree : 4
   }

   interval newInterval = {1, 9};
   add_vertex(&g, newInterval);  // Error (newInterval already exists in g)

   interval newInterval2 = {3, 6};
   add_vertex(&g, newInterval2);

   interval deleteInterval = {5, 8};
   delete_vertex(&g, deleteInterval);

   print_graph(&g);
   /*
   List 0 = [1, 9]
   List 1 = [2, 3]
   List 2 = [1, 4]
   List 3 = [6, 7]
   List 4 = [3, 6]
   0 1 1 1 1
   1 0 1 0 1
   1 1 0 0 1
   1 0 0 0 1
   1 1 1 1 0
   */

   // revert to origin graph
   add_vertex(&g, deleteInterval);
   delete_vertex(&g, newInterval2);

   printf("is connected : %d\n", connectivity(&g));  // is connected : 1
   printf("is 2-connected : %d\n", two_connectivity(&g));
   // CUT VERTEX = [1, 9]
   // is 2-connected : 0

   printf("2-edge-connected : %d\n", two_edge_connectivity(&g));
   // 2-edge-connected : 1

   interval from = {1, 4};
   interval to = {6, 7};
   int len = shortest_path(&g, from, to);
   // Shortest path from [1, 4] to [6, 7] : [1, 4] [1, 9] [6, 7]
   printf("len : %d\n", len);  // len : 2
   return 0;
}
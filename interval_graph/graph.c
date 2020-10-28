#define _CRT_SECURE_NO_WARNINGS

#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"

/****************************Pre-defined functions : TO NOT TOUCH ******************************************/
/*Add a node from the linked list*/
node* add_node(node* n, interval v) {
   node* head = n;
   node* newNode = (node*)malloc(sizeof(node));
   if (newNode == NULL) {
      printf("alloc error");
      exit(-1);
   }

   newNode->item = v;
   newNode->next = NULL;
   // if first node (head == null)
   if (head == NULL) {
      head = newNode;
   }
   // after second node
   else {
      node* tail = n;
      // find tail
      while (tail->next) {
         tail = tail->next;
      }
      tail->next = newNode;
   }

   return head;
}
/*Delete the node with item v from the linked list*/
node* delete_node(node* n, interval v) {
   node* head = n;
   node* cur = n;
   node* prev = n;
   int found = 0;
   while (cur) {
      if (cur->item.leftmost == v.leftmost &&
          cur->item.rightmost == v.rightmost) {
         found = 1;
         break;
      }
      prev = cur;
      cur = cur->next;
   }

   // if v is in adj_list : delete cur node
   if (found) {
      // if first node
      if (cur == prev) {
         head = cur->next;
      } else {
         node* nextNode = cur->next;
         prev->next = nextNode;
      }
      free(cur);
   }

   return head;
}

/*Print an error message*/
void print_error(void) { printf("Error\n"); }
/*************************************************************************************************************/

/*Constrcut the interval graph*/
void construct(Graph* g, char* file) {
//implement your function in here
	
	FILE* fp = NULL;
	fp = fopen(file, "r");

	if (fp != NULL)
	{
		char buffer[100];

		fgets(buffer, sizeof(buffer), fp);
		g->num_vertices = atoi(buffer);

		// vertex수가 MAX_VERTICES를 넘는 경우
		if (MAX_VERTICES < g->num_vertices)
		{
			print_error();
			g = NULL;
			return;
		}

		int index = 0;

		while (fgets(buffer, sizeof(buffer), fp) != NULL)
		{	
			if (index >= g->num_vertices)
			{
				print_error();
				g = NULL;
				return;
			}

			char seps[] = ",";
			char* token = strtok(buffer, seps);

			if (token != NULL)
			{
				g->map_interval[index].leftmost = atoi(token);
			}

			else
			{
				print_error();
			}

			token = strtok(NULL, seps);

			if (token != NULL)
			{
				g->map_interval[index].rightmost = atoi(token);
			}

			else
			{
				print_error();
			}

			index++;
		}

		if (index != g->num_vertices)
		{
			print_error();
			g = NULL;
			return;
		}

		for (index = 0; index < g->num_vertices; index++)
		{
			g->adj_list[index] = NULL;

			for (int i = 0; i < g->num_vertices; i++)
			{
				if (i != index)
				{
					if ((g->map_interval[index].leftmost <= g->map_interval[i].rightmost) && (g->map_interval[index].rightmost >= g->map_interval[i].leftmost))
						g->adj_list[index] = add_node(g->adj_list[index], g->map_interval[i]);
				}
			}
		}
	}
}


/*Print map_interval array and adjacency matrix*/
void print_graph(Graph* g) {
//implement your function in here
	
	for (int index = 0; index < g->num_vertices; index++)
	{
		printf("List %d = [%d, %d]\n", index, g->map_interval[index].leftmost, g->map_interval[index].rightmost);
	}

	for (int index = 0; index < g->num_vertices; index++)
	{
		for (int i = 0; i < g->num_vertices; i++)
		{
			if ((index != i) && (g->map_interval[index].leftmost <= g->map_interval[i].rightmost) && (g->map_interval[index].rightmost >= g->map_interval[i].leftmost))
				printf("1 ");
			else
				printf("0 ");
		}
		printf("\n");
	}
}


/*Check the adjacency between vertex v and u*/
int adjacent(Graph* g, interval v, interval u) {
//implement your function in here
	
	int check1 = 0;
	int check2 = 0;

	for (int index = 0; index < g->num_vertices; index++)
	{
		if ((v.leftmost == g->map_interval[index].leftmost) && (v.rightmost == g->map_interval[index].rightmost))
		{
			check1 = 1;
			break;
		}
	}

	if (check1 == 0)
	{
		print_error();
		return 0;
	}

	for (int index = 0; index < g->num_vertices; index++)
	{
		if ((u.leftmost == g->map_interval[index].leftmost) && (u.rightmost == g->map_interval[index].rightmost))
		{
			check2 = 1;
			break;
		}
	}

	if (check2 == 0)
	{
		print_error();
		return 0;
	}

	if ((v.leftmost <= u.rightmost) && (v.rightmost >= u.leftmost))
		return 1;
	else
		return 0;
}


/*Return the degree of vertex v*/
int degree(Graph* g, interval v) {
//implement your function in here
	
	int indexV = -1;
	
	for (int index = 0; index < g->num_vertices; index++)
	{
		if ((v.leftmost == g->map_interval[index].leftmost) && (v.rightmost == g->map_interval[index].rightmost))
		{
			indexV = index;
			break;
		}
	}

	if (indexV == -1)
	{
		print_error();
		return 0;
	}

	int degree = 0;

	node* head;
	head = g->adj_list[indexV];
			
	while (head != NULL)
	{
		degree++;
		head = head->next;
	}
	return degree;
}


/* Add a vertex v to g*/
void add_vertex(Graph* g, interval v) {
//implement your function in here
	
	if (g->num_vertices + 1 > MAX_VERTICES)
	{
		print_error();
		return;
	}

	int indexV = -1;

	for (int index = 0; index < g->num_vertices; index++)
	{
		if ((v.leftmost == g->map_interval[index].leftmost) && (v.rightmost == g->map_interval[index].rightmost))
		{
			indexV = index;
			break;
		}
	}

	if (indexV != -1)
	{
		print_error();
		return;
	}

	else
	{

		g->map_interval[g->num_vertices].leftmost = v.leftmost;
		g->map_interval[g->num_vertices].rightmost = v.rightmost;

		g->adj_list[g->num_vertices] = NULL;

		for (indexV = 0; indexV < g->num_vertices; indexV++)
		{
			// adjacent한 경우 -> 추가
			if ((g->map_interval[indexV].leftmost <= v.rightmost) && (g->map_interval[indexV].rightmost >= v.leftmost))
			{
				g->adj_list[g->num_vertices] = add_node(g->adj_list[g->num_vertices], g->map_interval[indexV]);
				g->adj_list[indexV] = add_node(g->adj_list[indexV], v);
			}
		}
		g->num_vertices++;
	}
}


/*Delete a vertex v from g*/
void delete_vertex(Graph* g, interval v) {
	//implement your function in here

	int indexV = -1;

	for (int index = 0; index < g->num_vertices; index++)
	{
		if ((v.leftmost == g->map_interval[index].leftmost) && (v.rightmost == g->map_interval[index].rightmost))
		{
			indexV = index;
			break;
		}
	}

	if (indexV == -1)
	{
		print_error();
		return;
	}

	// v가 g에 속하는 경우
	else
	{
		g->map_interval[indexV].leftmost = NULL;
		g->map_interval[indexV].rightmost = NULL;

		for (int index = 0; index < g->num_vertices; index++)
		{
			// adjacent 한 경우 -> 삭제
			if ((g->map_interval[index].leftmost <= v.rightmost) && (g->map_interval[index].rightmost >= v.leftmost))
			{
				g->adj_list[index] = delete_node(g->adj_list[index], v);
				g->adj_list[indexV] = delete_node(g->adj_list[indexV], g->map_interval[index]);
			}
		}

		for (int num = indexV + 1; num < g->num_vertices; ++num)
		{
			g->adj_list[num - 1] = g->adj_list[num];
			
			g->map_interval[num - 1].leftmost = g->map_interval[num].leftmost;

			g->map_interval[num - 1].rightmost = g->map_interval[num].rightmost;

		}

		g->num_vertices--;
	}
}


/*Check connectivity*/
int connectivity(Graph* g) {
//implement your function in here

	int visit_array[MAX_VERTICES];
	interval next_vertex;

	Queue Q;
	queueInit(&Q);

	for (int index = 0; index < g->num_vertices; index++)
	{
		next_vertex = g->map_interval[index];
		enqueue(&Q, g->map_interval[index]);
		visit_array[index] = 1;
	}
	
	while (!queueIsEmpty(&Q))
	{
		next_vertex = dequeue(&Q);

		for (int index = 0; index < g->num_vertices; index++)
		{
			if (g->adj_list[index] == 1)
			{
				enqueue(&Q, g->map_interval[index]);
				visit_array[index] = 1;
			}
		}
	}

	return 1;
}

/*Check 2-connectivity*/
int two_connectivity(Graph* g) {
//implement your function in here

	for (int index = 0; index < g->num_vertices; index++)
	{
		delete_node(g, g->map_interval[index]);

		int check = connectivity(g);

		if (check == 1)
		{
			return 1;
			break;
		}
		else
		{
			printf("[%d, %d]", g->map_interval[index].leftmost, g->map_interval[index].rightmost);
			return 0;
		}

		add_node(g, g->map_interval[index]);
	}
}

/*Check 2-edge-connectivity*/
int two_edge_connectivity(Graph* g) {
//implement your function in here

	for (int index = 0; index < g->num_vertices; index++)
	{
		int Degree = degree(g, g->map_interval[index]);

		if (Degree != 1)
		{
			return 1;
			break;
		}

		else
		{
			printf("CUT EDGE = (");
			printf("[%d, %d]", g->map_interval[index].leftmost, g->map_interval[index].rightmost);
			printf(")");
		}

	}
}


/*i) Print the shortest path from v to u, and ii) return the length of the path*/
int shortest_path(Graph* g, interval v, interval u) {
//implement your function in here

	int check1 = 0;
	int check2 = 0;

	int len = 1;

	for (int index = 0; index < g->num_vertices; index++)
	{
		if ((v.leftmost == g->map_interval[index].leftmost) && (v.rightmost == g->map_interval[index].rightmost))
		{
			check1 = 1;
			break;
		}
	}

	if (check1 == 0)
	{
		print_error();
	}

	for (int index = 0; index < g->num_vertices; index++)
	{
		if ((u.leftmost == g->map_interval[index].leftmost) && (u.rightmost == g->map_interval[index].rightmost))
		{
			check2 = 1;
			break;
		}
	}

	if (check2 == 0)
	{
		print_error();
	}

	if ((check1 != 0) && (check2 != 0))
	{
		printf("Shortest path from [%d, %d] to [%d, %d] : ", v.leftmost, v.rightmost, u.leftmost, u.rightmost);
		printf("[%d, %d]", v.leftmost, v.rightmost);

		if (adjacent(g, v, u) == 1)
		{
			printf("[%d, %d]", u.leftmost, u.rightmost);
			len = 1;
		}

		else
		{
			len++;

			int indexV = -1;

			for (int index = 0; index < g->num_vertices; index++)
			{
				if ((v.leftmost == g->map_interval[index].leftmost) && (v.rightmost == g->map_interval[index].rightmost))
				{
					indexV = index;
					break;
				}
			}

			if (indexV == -1)
			{
				print_error();
				return 0;
			}

			node* head;
			head = g->adj_list[indexV];

			while (head != NULL)
			{	
				if (adjacent(g, u, head->item) == 1)
				{
					
					printf("[%d, %d]", head->item.leftmost, head->item.rightmost);
				}

				head = head->next;
			}

			printf("[%d, %d]", u.leftmost, u.rightmost);

		}
		printf("\n");
	}

	return len;
}
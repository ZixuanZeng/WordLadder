#pragma once
/*graph-dijkstra.h*/

#include "queue.h"

int PopMin(Queue *unvisitedQ, int distance[]);
int *Dijkstra_distance(Graph *G, Vertex v);
Vertex *Dijkstra_predecessor(Graph *G, Vertex v);
Vertex *Dijkstra(Graph *G, Vertex src, Vertex dest);
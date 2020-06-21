/*graph-dijkstra.c*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "avl.h"
#include "stack.h"
#include "queue.h"
#include "set.h"
#include "graph.h"
#include "mymem.h"

int PopMin(Queue *unvisitedQ, int distance[])
{
	int N = unvisitedQ->NumElements;
	Stack *S = CreateStack(N);

	assert(!isEmptyQueue(unvisitedQ));

	int minV = Dequeue(unvisitedQ);

	while (!isEmptyQueue(unvisitedQ)) {
		int v = Dequeue(unvisitedQ);

		if (distance[v] < distance[minV]) {
			Push(S, minV);
			minV = v;
		}
		else
			Push(S, v);
	}

	while (!isEmptyStack(S)) {
		Enqueue(unvisitedQ, Pop(S));
	}

	assert(unvisitedQ->NumElements == (N - 1));

	DeleteStack(S);
	return minV;
}

//
// Performs Dijkstra's shortest path algorithm from the given
// starting vertex v.  Returns a dynamically-allocated array
// of distances from v; the array contains G->NumVertices
// distances.  If a vertex cannot be reached from v, it's 
// distance is INT_MAX.
//
// NOTE: returns NULL if v is not a valid vertex id.
//
// NOTE: it is the responsibility of the CALLER to free the 
// returned array when they are done.
//
int *Dijkstra_distance(Graph *G, Vertex v)
{
	int  INF = INT_MAX;

	if (v < 0 || v >= G->NumVertices)  // invalid vertex #:
		return NULL;

	//
	// allocate distances array:
	//
	int N = G->NumVertices;

	int *distance = (int *)mymalloc(N * sizeof(int));
	if (distance == NULL)
	{
		printf("\n**Error in Dijkstra: malloc failed to allocate\n\n");
		exit(-1);
	}

	//
	// for each vertex, add to Queue to be visited, and
	// initialize distance to Infinity:
	//
	Queue *unvisitedQ = CreateQueue(N);
	int currentV;

	for (currentV = 0; currentV < N; ++currentV)
	{
		Enqueue(unvisitedQ, currentV);
		distance[currentV] = INF;
	}

	//
	// starting vertex has a distance of 0 from itself:
	//
	distance[v] = 0;


	//
	// Now run Dijkstra's algorithm:
	//

	//
	// TODO:
	//
	while (!isEmptyQueue(unvisitedQ)) {
		int EdgeWeight = 0; // Initialize
		int alternativePathDistance = 0;
		Vertex adj = 0;
		currentV = PopMin(unvisitedQ, distance);
		if (distance[currentV] == INF) {
			break;
		}

		Vertex *neighbor = Neighbors(G, currentV);// Get the neighbors of
												  //  current vertex

		int i = 0;
		while (neighbor[i] != -1) { // loop through the neighbors
			adj = neighbor[i];
			EdgeWeight = getEdgeWeight(G, currentV, adj); // Get the weight
														  // of all the neighbors
			alternativePathDistance = distance[currentV] + EdgeWeight;

			if (alternativePathDistance < distance[adj]) {
				distance[adj] = alternativePathDistance;
			}
			i++;
		}


	}

	//
	// done!
	//
	DeleteQueue(unvisitedQ);

	return distance;

}

//
// Performs Dijkstra's shortest path algorithm from the given
// starting vertex v.  Returns a dynamically-allocated array
// of vertices, denoting the path from every vertex
// back to v; the array contains G->NumVertices values.  
// If there is no path from a vertex X back to v, the array
// contains -1.  Likewise, the predecessor of the start
// vertex v is also -1.
//
// NOTE: returns NULL if v is not a valid vertex id.
//
// NOTE: it is the responsibility of the CALLER to free the 
// returned array when they are done.
//
Vertex *Dijkstra_predecessor(Graph *G, Vertex v)
{
	int  INF = INT_MAX;

	if (v < 0 || v >= G->NumVertices)  // invalid vertex #:
		return NULL;

	//
	// allocate distances array:
	//
	int N = G->NumVertices;

	int *distance = (int *)mymalloc(N * sizeof(int));
	if (distance == NULL)
	{
		printf("\n**Error in Dijkstra: malloc failed to allocate\n\n");
		exit(-1);
	}

	//
	// allocate predecessor array:
	//

	int *predecessor = (int *)mymalloc(N * sizeof(int));
	if (predecessor == NULL)
	{
		printf("\n**Error in Dijkstra: malloc failed to allocate\n\n");
		exit(-1);
	}

	//
	// for each vertex, add to Queue to be visited, and
	// initialize distance to Infinity:
	//
	Queue *unvisitedQ = CreateQueue(N);
	int currentV;

	for (currentV = 0; currentV < N; ++currentV)
	{
		Enqueue(unvisitedQ, currentV);
		distance[currentV] = INF;
		predecessor[currentV] = -1;
	}

	//
	// starting vertex has a distance of 0 from itself:
	//
	distance[v] = 0;


	//
	// Now run Dijkstra's algorithm:
	//

	//
	// TODO:
	//
	while (!isEmptyQueue(unvisitedQ)) {
		int EdgeWeight = 0; // Initialize
		int alternativePathDistance = 0;
		Vertex adj = 0;
		currentV = PopMin(unvisitedQ, distance);
		if (distance[currentV] == INF) {
			break;
		}

		Vertex *neighbor = Neighbors(G, currentV);// Get the neighbors of
												  //  current vertex

		int i = 0;
		while (neighbor[i] != -1) { // loop through the neighbors
			adj = neighbor[i];
			EdgeWeight = getEdgeWeight(G, currentV, adj); // Get the weight
														  // of all the neighbors
			alternativePathDistance = distance[currentV] + EdgeWeight;

			if (alternativePathDistance < distance[adj]) {
				distance[adj] = alternativePathDistance;
				predecessor[adj] = currentV;
			}
			i++;
		}
		myfree(neighbor);

	}

	//
	// done!
	//
	DeleteQueue(unvisitedQ);
	myfree(distance);
	/*for (int i = 0; i < N; i++)
	{
		myfree(distance);
	}*/

	return predecessor;
}

//
// Performs Dijkstra's shortest path algorithm to find the shortest path
// from src to dest.  Returns a dynamically-allocated array of vertices
// denoting this path; the array will start with src, contain 0 or more
// vertices that lead to dest, followed by dest, and ending with -1.  
// If there is no pat from src to dest, the array will contain only -1.
//
// NOTE: returns NULL if src or dest are not valid vertex ids.
//
// NOTE: it is the responsibility of the CALLER to free the 
// returned array when they are done.
//
Vertex *Dijkstra(Graph *G, Vertex src, Vertex dest)
{
	//
	// TODO!
	//
	int v = 0;
	//
	// allocate path array:
	//
	int N = G->NumVertices;

	int *path = (int *)mymalloc(N * sizeof(int));
	if (path == NULL)
	{
		printf("\n**Error in Dijkstra: malloc failed to allocate\n\n");
		exit(-1);
	}

	int *back = (int *)mymalloc(N * sizeof(int));
	if (back == NULL)
	{
		printf("\n**Error in Dijkstra: malloc failed to allocate\n\n");
		exit(-1);
	}


	Vertex *predecessor = Dijkstra_predecessor(G, src); //get the predecessor from src to all other vertexes

	if (src == dest) {
		path[0] = -1;
		return path;
	}
	else {
		int i = 0;
		int j = 0;
		int d = dest;// Make the dest value changes every time
		while (predecessor[d] != src) {
			v = predecessor[d];// easy to debug, assign v to that value
			if (v == -1) {
				path[0] = -1;
				return path;
			}
			back[i] = v; // put all the vertexs in an array in backward
			d = predecessor[d];// go to next predecessor
			i++;
		}

		i--;
		path[j] = src;
		j++;
		// go through the array
		while (i >= 0) {
			path[j] = back[i];
			j++;
			i--;
		}
		path[j] = dest;
		path[j + 1] = -1;
		myfree(back);
		myfree(predecessor);
	}

	return path;
}
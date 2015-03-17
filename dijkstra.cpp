/**
 * ------------------------------------------------------------------------
 *
 *
 * 
 * Alunos: Silvana Trindade e Maurício André Cinelli
 * Ano: 2015
 * ------------------------------------------------------------------------
 */
#include <iostream>
#include <deque>
#include <iterator>
#include <algorithm> 
#include <limits> //limites numéricos
#include <stdexcept> // for std::runtime_error
#include <vector>
#include <random>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>

#define LIMIT 1000

using namespace std;

typedef struct _e
{
	int target;
	int weight;
	struct _e *next;
}Edge;

typedef struct
{
	Edge  *edges[LIMIT];
	int degree[LIMIT];
	int numberOfEdges;
	int numberOfNodes;

}Graph;

void InsertEdge(Graph *graph,int source, int target, bool directed)
{
	Edge *e;
	e = ( Edge* ) malloc ( sizeof(Edge) );

	if (e == NULL)
	{
		return;
	}

	e->weight = 1;//peso da arestas 
	e->target = target;
	e->next = graph->edges[source];

	graph->edges[source] = e; 
	graph->degree[source] += 1;
	
	if (directed == false)
	{
		InsertEdge(graph,target,source,true);
	}
	else
	{
		graph->numberOfEdges++;
	}
}

/**
 * Implementação para encontrar um caminho mínimo de u até v
 */
void shortestPath( Graph *graph, int source, int target) 
{
	Edge *p; 					//vetor temporário
	vector<bool> inTree;				//O nó já esta na árvore?
	vector<int> distance;				//armazena distância para source
	int v;						//nó atual
	int w;						//candidato a próximo nó
	int current;					//recebe próximo nó
	int weight;					//peso da aresta
	int dist;					//melhor distância atual para o nó de partida
	vector<int> path;

	inTree = vector<bool> ( graph->numberOfNodes, false);
	distance = vector<int> ( graph->numberOfNodes, std::numeric_limits<int>::max() );
	
	v = source;

	distance[v] = 0;
	inTree[v] = true;
	cout<<"source "<<source<<" target "<<target<<endl;

	while( inTree[target] == false )
	{
		current = source;
		

		p = graph->edges[v];//p recebe os nós adjacentes de v

		if (p == NULL)
		{
			cout<<"Grafo com nó "<<v<<" desconexo."<<endl;
			return;
		}

		dist =  std::numeric_limits<int>::max();

		while( p != NULL )
		{
			w = p->target; 
			weight = p->weight;

			/**
			 * Verificação de caminho
			 */
			if ( distance[w] > ( distance[v] + weight ) && inTree[w] == false)
			{
				distance[w] = distance[v] + weight;
			}

			if (target == w)	
			{
				break;
			}

			p = p->next;
		}

		v = 1;
		dist = std::numeric_limits<int>::max();

		for (int i = 1; i < graph->numberOfNodes; i++) 
		{
			if ( (inTree[i] == false) && (dist > distance[i]) ) {
				dist = distance[i];
				v = i;
			}
		}

		inTree[v] = true;
	}
}

int main(int argc, const char * argv[])
{
  if(argc <= 2)
  {
    help();
    return EXIT_FAILURE;
  }

  string arquivoTrafego = argv[2];

  Graph *graph;

  graph = (Graph*) malloc ( sizeof(Graph) );

  if (graph == NULL)
  {
  	return EXIT_FAILURE;
  }

  readGraph(graph,string(argv[1]));

  vector< vector<int> > trafficMatrix = readTrafficMatrix(graph->numberOfNodes, string(argv[2]));

	
	Edge *p;  

  for (int i = 1; i < graph->numberOfNodes; i++) 
  {
    printf("Node %d: ", i);
   	
   	p = graph->edges[i];

   	while(p != NULL)
   	{
   		cout<<p->target<<"\t";
   		p = p->next;
   	}


    printf("\n---------------\n");
  }


	for (int u = 1; u < graph->numberOfNodes-1; u++)
	{
	  	for (int v = u+1; v < graph->numberOfNodes; v++)
	  	{

		  	shortestPath(graph,u,v);
	  		
	  	}
	}

  return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>

int adj_wmat[30][30]={0}, d[30], pi[30], v, e, s;

void initialize_single_source(){
    for(int i=1; i<=v; ++i){
        d[i] = 999999;     // distance from source to other vertices at first is infinity = 999999
        pi[i] = 0;          // pi array holds the predecessor vertices for the vertices corresponding to the indices
    }
    d[s] = 0;       // distance from source to itself is 0
}

void Relax(int u, int v){                   // this function checks if there is a new shortest path between the vertices in consideration. if there is it updates
    if(d[v] > d[u] + adj_wmat[u][v]){
        d[v] = d[u] + adj_wmat[u][v];
        pi[v] = u;
    }
}

int Bellman_Ford_algo(){
    initialize_single_source();
    int i, j, k;
    for(k=1; k<=v-1; ++k)       //  Relaxing every edge in the graph v-1 times gives the shortest path
        for(i=1; i<=v; ++i)
            for(j=1; j<=v; ++j)
                if(adj_wmat[i][j])
                    Relax(i, j);

    for(i=1; i<=v; ++i)                         //  this logic checks the presence of negative cycles in the graph and reports them
        for(j=1; j<=v; ++j)
            if(adj_wmat[i][j] != 0 && d[j] > d[i] + adj_wmat[i][j])
                return -1;
    return 1;
}

int main()
{
    int i, v1, v2, w, neg_cycle, choice;
    printf("Do you want to work with:\n1. Directed Graph\n2. Undirected Graph(Only Positive weights)\nEnter your choice: ");
    scanf("%d", &choice);
    printf("How many number of vertices do you want to enter: ");
    scanf("%d", &v);
    printf("\nHow many number of edges do you want to enter: ");
    scanf("%d", &e);

    printf("\nEnter %d edges and their corresponding edge weights: \n", e);
    for(i=1; i<=e; ++i){
        printf("Edge %d: ", i);
        scanf("%d %d", &v1, &v2);
        printf("Edge weight: ");
        scanf("%d", &w);
        if(choice == 1)
            adj_wmat[v1][v2] = w;
        else
            adj_wmat[v1][v2] = adj_wmat[v2][v1] = w;
    }

    printf("\nEnter the source from which the shortest paths have to be calculated: ");
    scanf("%d", &s);

    neg_cycle = Bellman_Ford_algo();

    if(neg_cycle != -1){
        printf("\n\nThe shortest paths from the single source %d are: ", s);
        for(i=1; i<=v; ++i)
            if(i != s)
                printf("\nDistance %d --> %d : %d\tPrevious Vertex : %d", s, i, d[i], pi[i]);
    }
    else
        printf("\nThe given Graph contains negative cycles. Hence, shortest paths cannot be found.");
    return 0;
}

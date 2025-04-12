/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct NODE
{
    int data;
    struct NODE *next;
}NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa
typedef struct 
{
    int nodes; 
    int *vis; 
    NODE **alst; // alst - pointer catre capatul unei liste de adiacente
} GPH;

typedef struct 
{
    int top; // t - top
    int capacity; // scap - capacity 
    int *v; // arr - v
} STK;

NODE *create_node(int v)
{
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

// graf neorientat 
GPH *create_g(int nodes)
{
    int i;
    GPH *g = (GPH*)malloc(sizeof(GPH));
    g->nodes = nodes;
    g->alst = (NODE**)malloc(sizeof(NODE *) * nodes);
    g->vis = (int*)malloc(sizeof(int) * nodes);

    for (int i = 0; i < nodes; i++)
    {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STK *create_s(int capacity)
{
    STK *s = (STK*)malloc(sizeof(STK));
    s->v = (int*)malloc(capacity * sizeof(int));
    s->top = -1;
    s->capacity = capacity;

    return s;
}

void push(int i, STK *s)
{
    s->top = s->top + 1;
    s->v[s->top] = i;
}

void add_edge(GPH *g, int start, int end)
{
    NODE *nn = create_node(end);
    nn->next = g->alst[start];
    g->alst[start] = nn;

    nn = create_node(start);
    nn->next = g->alst[end];
    g->alst[end] = nn;
}


void insert_edges(GPH *g, int edges, int nodes)
{
    int start, end, i;
    printf("adauga %d munchii (de la 0 la %d)\n", edges, nodes);
    for (i = 0; i < edges; i++)
    {
        scanf("%d%d", &start, &end);
        add_edge(g, start, end);
    }
}

void DFS(GPH *g, STK *s, int i)
{
    NODE *adj_list = g->alst[i];
    g->vis[i] = 1;
    printf("%d ", i);
    push(i, s);
    while (adj_list != NULL)
    {
        int con_ver = adj_list->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        adj_list = adj_list->next;
    }
}

void wipe(GPH *g, int nodes)
{
    for (int i = 0; i < nodes; i++)
    {
        g->vis[i] = 0;
    }
} 

int canbe(GPH *g, STK *s1, int start, int end)
{
    int canbe = 0;
    s1->top = -1;
    wipe(g, g->nodes);
    DFS(g, s1, start);

    for (int i = 0; i <= s1->top; i++) {
        if (s1->v[i] == end)
            return 1;
    }

    return 0;
}

int main()
{
    int nodes; // nrv - nodes
    int edges; // edg_nr - edges
    int start, end; // schimb numele variabilelor pt claritate src - start dest - end
    int i;
    int vortex_1;
    int vortex_2;

    printf("cate noduri are graful?");
    scanf("%d", &nodes);

    printf("cate muchii are graful?");
    scanf("%d", &edges);

    GPH *g = create_g(nodes);
    STK *s1 = create_s(2 * nodes); // avem nev doar de un stack pentru a retine drumul de noduri 
    insert_edges(g, edges, nodes);
    
    printf("introdu primul restaurant: ");
    scanf("%d", &vortex_1);
    printf("introdu al doilea restaurant: ");
    scanf("%d", &vortex_2);

    if (canbe(g, s1, vortex_1, vortex_2))
    printf("Exista drum intre restaurantul %d si %d.\n", vortex_1, vortex_2);
    else
    printf("NU exista drum intre restaurantul %d si %d.\n", vortex_1, vortex_2);

return 0;
}
#include "include/main.h"

int main(){
    srand(time(0));

    Graph g;
    init_graph(&g);
    generate_user(&g, 100000);
    generate_edge(&g, 500000);
    //graph_print(&g);
    mutual(&g, 0);
    dijkstra(&g, 1, 200);

    p_table t;
    init_table(&t);
    generate_profile(&t, &g, 50000);
    Profile *result = search_profile(&t, 1222);
    print_profile(result);

    free_graph(&g);
    free_table(&t);

    return 0;
}
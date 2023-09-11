#include <iostream>
#include "conditions.h"
#include "knapsack.h"
#include  <vector>
#include <algorithm>

  
 
unsigned optimal2 (std::vector<bool> &in_or_not, int i, std::vector<unsigned> costs, std::vector<unsigned> weights, Knapsack &knapsack) {
    unsigned sum = 0, c = 0, w = 0, d = 0, n = in_or_not.size();
    int k = 0;
    std::vector<float> density(n);
    std::vector<int> index(n);
    for (k = 0; k < n; k++) {
        density[k] = (float)costs[k]/weights[k];
        index[k] = k;
        if (k >= i) in_or_not[k] = 1;
    }
    
    sort(index.begin(), index.end(), [&](int u,int j){return density[u] < density[j];} );
    
    for (k = n - 1; k >= 0; k--){
        if (in_or_not[index[k]] && weights[index[k]] + w <= knapsack.capacity){
        sum += costs[index[k]];
        index[k] = -1;
        w += weights[index[k]];
        }
    }
    
    if (knapsack.get_current_weight() < knapsack.capacity) {
        k = 0;
        while(index[k] != -1 && k < n){
            if(in_or_not[index[k]]){ c = costs[index[k]]; d = density[k];}
            ++k;
        }
        sum = sum + d * (- knapsack.get_current_weight() + knapsack.capacity);
    }
    for (k = 0; k < n; k++) {
        if (k >= i) in_or_not[k] = 0;
    }
    return sum;
}
    

unsigned optimal (std::vector<bool> &in_or_not, int i, std::vector<unsigned> costs) {
    unsigned sum = 0, n = in_or_not.size();
    //if (i => n) i = n - 1;
    for (int j = 0; j < i; j++)  { if(in_or_not[j]) sum += costs[j];}
    for (int j = i++; j < n; j++) sum += costs[j];
    
    return sum;
}

int last_one_to_zero(std::vector<bool> &vec, unsigned i) {
    unsigned n = vec.size();
    if (i == n) i = n - 1;
    int j = i - 1;
    while (j >=0 && vec[j] == false) {
        j--;
    }
    return j;
}

void dfs (Conditions &conditions, unsigned i, Knapsack &knapsack, bool &flag1, bool &flag2, unsigned &k) {
    //std::cout << " hey " << std::endl;
   // std::cout << optimal(knapsack.items, i, conditions.costs) <<" " << max << " "<< optimal2(knapsack.items, i, conditions.costs, conditions.weights, knapsack) << std::endl;
    /*std::cout << " hey 6" << std::endl;
    for (int l = 0; l < knapsack.items.size(); l++) {
        std::cout << knapsack.items[l] <<" " ;
        }*/
    //p++;
    //if(p > 25) flag2 = 1;
    //if(knapsack.get_current_value() > max) max = knapsack.get_current_value();
    if (k > 1000) return;
    if (flag2) return;
    unsigned opt_value = optimal2(knapsack.items, i, conditions.costs, conditions.weights, knapsack);
    if(opt_value < knapsack.max) {
        
    //    std::cout << " hey ";
        
        i = last_one_to_zero((knapsack.items), i);
        if (i == -1) { 
            flag2 = 1; return;
            }
        knapsack.take_out(i, conditions.weights[i], conditions.costs[i]);
        flag1 = 1;
    }

    if(knapsack.get_current_value() == opt_value) {
    //    std::cout << " one ";
        if(knapsack.get_current_value() > knapsack.max){ 
            knapsack.max = knapsack.get_current_value(); 
            for (int y = 0; y < knapsack.answer.size(); y++) {
                knapsack.answer[y] = knapsack.items[y];
            }
        }
        i = last_one_to_zero((knapsack.items), i);
    //    std::cout << "ou " << i << "my ";
        if (i == -1) { 
            flag2 = 1; return;
            }
        knapsack.take_out(i, conditions.weights[i], conditions.costs[i]);
        flag1 = 1;
    }

    if (conditions.weights[i] + knapsack.get_current_weight() <= knapsack.capacity && !(flag1)) {
    //    std::cout << " h ";
    //    if(knapsack.get_current_value() > max) max = knapsack.get_current_value();
        knapsack.put_item(i, conditions.weights[i], conditions.costs[i]);
        dfs(conditions, ++i, knapsack, flag1, flag2, ++k);
    }

    else {
        flag1 = 0;
    //    std::cout << " two ";
        
        dfs(conditions, ++i, knapsack, flag1, flag2, ++k);
    }

}


int main() {

    unsigned i, n, capacity, p = 0, max = 0, j = 0, k = 0;
    bool flag1 = 0; 
    bool flag2 = 0;
    std::cin >> n >> capacity;
    std::vector
    <unsigned> weights(n);
    std::vector
    <unsigned> costs(n);
    for (i = 0; i < n; i++) {
        std::cin >> costs[i] >> weights[i];
    }
    Knapsack knapsack(capacity, n);
    Conditions conditions(weights, costs);
    
    dfs(conditions, j, knapsack, flag1, flag2, k);
    for (i = 0; i < n; i++) {
        std::cout << knapsack.answer[i] << " ";
    }
    std::cout << std::endl << knapsack.max << " " << k << std::endl;
    return 0;
}
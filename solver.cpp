#include <iostream>
#include "solver.h"
#include  <vector>
#include <algorithm>

Solver::Solver(unsigned n_items, unsigned capacity, std::vector<unsigned> &weights, std::vector<unsigned> &costs) 
    :knapsack(capacity, n_items),
     conditions(weights, costs)
    {}

unsigned Solver::get_max() {
    return knapsack.max;
}
 
unsigned Solver::optimal2 (int i) {
    unsigned sum = 0, c = 0, w = 0, d = 0, n = knapsack.items.size();
    int k = 0;
    std::vector<float> density(n);
    std::vector<int> index(n);
    for (k = 0; k < n; k++) {
        density[k] = (float)conditions.costs[k]/conditions.weights[k];
        index[k] = k;
        if (k >= i) knapsack.items[k] = 1;
    }
    
    sort(index.begin(), index.end(), [&](int u,int j){return density[u] < density[j];} );
    
    for (k = n - 1; k >= 0; k--){
        if (knapsack.items[index[k]] && conditions.weights[index[k]] + w <= knapsack.capacity){
        sum += conditions.costs[index[k]];
        index[k] = -1;
        w += conditions.weights[index[k]];
        }
    }
    
    if (knapsack.get_current_weight() < knapsack.capacity) {
        k = 0;
        while(index[k] != -1 && k < n){
            if(knapsack.items[index[k]]){ c =conditions.costs[index[k]]; d = density[k];}
            ++k;
        }
        sum = sum + d * (- knapsack.get_current_weight() + knapsack.capacity);
    }
    for (k = 0; k < n; k++) {
        if (k >= i) knapsack.items[k] = 0;
    }
    return sum;
}

int Solver::last_one_to_zero(std::vector<bool> &vec, unsigned i) {
    unsigned n = vec.size();
    if (i == n) i = n - 1;
    int j = i - 1;
    while (j >=0 && vec[j] == false) {
        j--;
    }
    return j;
}

void Solver::solve(unsigned i, bool &flag1, bool &flag2, unsigned &k, unsigned depth) {
    if (k > depth) return;
    if (flag2) return;
    unsigned opt_value = optimal2(i);
    if(opt_value < knapsack.max) {
        i = last_one_to_zero((knapsack.items), i);
        if (i == -1) { 
            flag2 = 1; return;
            }
        knapsack.take_out(i, conditions.weights[i], conditions.costs[i]);
        flag1 = 1;
    }

    if(knapsack.get_current_value() == opt_value) {
        if(knapsack.get_current_value() > knapsack.max){ 
            knapsack.max = knapsack.get_current_value(); 
            for (int y = 0; y < knapsack.answer.size(); y++) {
                knapsack.answer[y] = knapsack.items[y];
            }
        }
        i = last_one_to_zero((knapsack.items), i);
        if (i == -1) { 
            flag2 = 1; return;
            }
        knapsack.take_out(i, conditions.weights[i], conditions.costs[i]);
        flag1 = 1;
    }

    if (conditions.weights[i] + knapsack.get_current_weight() <= knapsack.capacity && !(flag1)) {
        knapsack.put_item(i, conditions.weights[i], conditions.costs[i]);
        solve(++i, flag1, flag2, ++k, depth);
    }

    else {
        flag1 = 0;
        solve(++i, flag1, flag2, ++k, depth);
    }
}

void Solver::print_ans()
{
	std::cout << knapsack.max << std::endl;
	for (int i = 0; i < knapsack.items.size(); ++i) {
		std::cout << knapsack.answer[i] << " ";
	} 
	std::cout << std::endl;
}
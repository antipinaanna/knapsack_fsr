#pragma once
#include <vector>

class Knapsack {
    public:
        Knapsack(const unsigned capacity, unsigned n_items);
        const unsigned capacity;
        bool put_item (unsigned item_index, unsigned item_weight, unsigned item_cost);
        bool take_out (unsigned item_index, unsigned item_weight, unsigned item_cost);
        unsigned get_current_weight();
        unsigned get_current_value();
        std::vector<bool> items;
        std::vector<unsigned> answer;
        unsigned max;
    private:
        unsigned current_value;
        unsigned current_weight;
};
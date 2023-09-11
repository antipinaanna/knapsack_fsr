#include "knapsack.h"

Knapsack::Knapsack(const unsigned capacity, unsigned n_items) 
: items(n_items, 0),
  answer(n_items, 0),
  current_weight(0),
  capacity(capacity),
  current_value(0),
  max(0)
{}

unsigned Knapsack::get_current_weight(){
    return current_weight;
}

unsigned Knapsack::get_current_value(){
    return current_value;
}

bool Knapsack::put_item(unsigned item_index, unsigned item_weight, unsigned item_cost) {
    if (current_weight + item_weight <= capacity) {
        current_value += item_cost;
        current_weight += item_weight;
        items[item_index] = 1;
        return 1;
    } else 
        return 0;
    
}

bool Knapsack::take_out(unsigned item_index, unsigned item_weight, unsigned item_cost) {
    if (items[item_index] == 1) {
        current_weight -= item_weight;
        current_value -= item_cost;
        items[item_index] = 0;
        return 1;
    } else 
        return 0;
}
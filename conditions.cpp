#include "conditions.h"
#include <vector>

Conditions::Conditions(std::vector<unsigned> &weights, std::vector<unsigned> &costs) {
    this->weights = weights;
    this->costs = costs;
}
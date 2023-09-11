#pragma once
#include <vector>

class Conditions {
    public:
        Conditions (std::vector<unsigned>  &weights, std::vector<unsigned> &costs);
        std::vector<unsigned> weights;
        std::vector<unsigned> costs; 
                                                                                        
};
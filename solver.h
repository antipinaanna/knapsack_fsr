#include "knapsack.h"
#include "conditions.h"
#include <vector>


class Solver {
    public:
        Solver(unsigned n_items, unsigned capacity, std::vector<unsigned> &weights, std::vector<unsigned> &costs);
        void solve(unsigned i, bool &flag1, bool &flag2, unsigned &k, unsigned depth);
        unsigned optimal2 (int i);
        int last_one_to_zero(std::vector<bool> &vec, unsigned i);
        std::vector<bool> get_answer();
        bool is_solution_ready();
        void print_ans();
        unsigned get_max();
    private:
        Knapsack knapsack;
        Conditions conditions;
};
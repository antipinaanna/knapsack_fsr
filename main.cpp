#include "conditions.h"
#include "knapsack.h"
#include "solver.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{

	std::string folderPath = "./data";
    std::ofstream file_out("output_dataframe");
	if (file_out.is_open())
	{
		for (const auto &entry : fs::directory_iterator(folderPath)) 
		{
			if (entry.is_regular_file())
			{
				std::string filePath = entry.path().string();
				unsigned depth;
				if (filePath == "./data/ks_10000_0") depth = 10000;
				else depth = 1000;
				std::ifstream file(filePath);
				if (file.is_open())
				{
					unsigned capacity; // максимально допустимый вес
					unsigned n_items;  
					file >> n_items >> capacity;
					std::vector<unsigned> costs(n_items); 
					std::vector<unsigned> weights(n_items);
					for (int i = 0; i < n_items; i++)
					{
						file >> costs[i] >> weights[i];
					}
					Solver solver(n_items, capacity, weights, costs);
					unsigned j = 0, k = 0;
					bool flag1 = 0;
					bool flag2 = 0;
					solver.solve(j, flag1, flag2, k, depth);
					solver.print_ans();
					file_out << filePath << ", "<< solver.get_max() << std::endl;
					file.close();
				}
				else
					std::cout << "Не удалось открыть файл" << std::endl;
			}
		}
		file_out.close();
	}
}

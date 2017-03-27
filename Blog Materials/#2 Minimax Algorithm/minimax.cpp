#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>

void MiniMax(std::vector<int>* pBf, int* scores, int size)
{

}

template<typename T>
void PrintArray(const char* name, std::vector<T>* pArr)
{
	for(unsigned int i = 0; i < pArr->size(); ++i)
	{
		if(i == 0)
			std::cout << name << " = {";
		std::cout << (*pArr)[i];
		if(i != pArr->size() - 1)
			std::cout << ", ";	
		else
			std::cout << "}" << std::endl;
	}
}	

void InitializeArrays()
{
	std::vector<unsigned int> bfs;
	std::vector<unsigned int> nodeqty;
	std::vector<int> vals;
	
	unsigned int bfmin = 2, bfmax = 4;
	unsigned int depth = 3, bfsum = 0;
	for(unsigned int i = 1; i <= depth; ++i)
	{
		if(nodeqty.empty())
			nodeqty.push_back(1);
		else
		{
			nodeqty.push_back(bfsum);
			bfsum = 0;
		}

		for(unsigned int j = 1; j <= nodeqty.back(); ++j)
		{
			bfs.push_back((rand() % (bfmax - bfmin + 1)) + bfmin);
			bfsum += bfs.back();
		}
	}
	nodeqty.push_back(bfsum);
	
	unsigned int vmin = -10, vmax = 10;
	for(unsigned int i = 1; i <= nodeqty.back(); ++i)
		vals.push_back((rand() % (vmax - vmin + 1)) + vmin);
	
	PrintArray<unsigned int>("bfs", &bfs);
	PrintArray<unsigned int>("nodeqty", &nodeqty);
	PrintArray<int>("vals", &vals);
}

int main(void)
{
	//Initialize random seed.
	srand(time(NULL));
	
	InitializeArrays();
	
	return 0;
}
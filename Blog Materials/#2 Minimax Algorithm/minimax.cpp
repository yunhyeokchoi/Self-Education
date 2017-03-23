#include <vector>

int MiniMax(std::vector<int>* pBf, int* scores, int size)
{
	int bfSize = pBf->size;
	for(std::vector<int>::iterator it = pBf->begin();
		it != pBf->end();
		++it)
	{
		pBf
	}
}

int main(void)
{
	//Container for storing branching factors for the trees.
	std::vector<int> bf = {3,
						   //3 branches in ply 1.
						   2, 3, 5,
						   //2 branches in the leftmost branch from ply 2.
						   1, 2
						   //3 branches in the center branch from ply 2.
						   2, 3, 3,
						   //5 branches in the rightmost branch from ply 2.
						   1, 3, 3, 2, 4};
	//(1 + 2) + (2 + 3 + 3) + (1 + 3 + 3 + 2 + 4) = 3 + 8 + 13 = 24
	int scores[24] = {1, 3, 4, 
					  5, 2, 7, 8, 9, 13, 2, 3, 
					  4, 5, 6, 7, 8, 2, 3, 8, 2, 4, 5, 2, 7};
	
	return 0;
}
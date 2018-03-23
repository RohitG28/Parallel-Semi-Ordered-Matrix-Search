#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

void divideMatrix(int index, int *rowLow, int* rowHigh, int* colLow, int* colHigh, int p)
{
	// printf("index %d\n",index);
	if(p>1)
	{
		int indexHigh = index + p/2;
		if((colHigh[index] - colLow[index]) > (rowHigh[index] - rowLow[index]))
		{	
			colHigh[indexHigh] = colHigh[index];
			colHigh[index] = (colLow[index] + colHigh[index])/2;
			rowLow[indexHigh] = rowLow[index];
			rowHigh[indexHigh] = rowHigh[index];
			colLow[indexHigh] = colHigh[index]+1;
		}	
		else
		{
			rowHigh[indexHigh] = rowHigh[index];
			rowHigh[index] = (rowLow[index] + rowHigh[index])/2;
			colLow[indexHigh] = colLow[index];
			colHigh[indexHigh] = colHigh[index];
			rowLow[indexHigh] = rowHigh[index]+1;
		}
		divideMatrix(index,rowLow,rowHigh,colLow,colHigh,p/2);
		divideMatrix(indexHigh,rowLow,rowHigh,colLow,colHigh,p/2);
	}
}

int main(int argc, char** argv)
{	
	int n,p;
	cin >> n >> p;
	int rowLow[p],rowHigh[p],colLow[p],colHigh[p];
	rowLow[0] = 0;
	rowHigh[0] = n-1;
	colLow[0] = 0;
	colHigh[0] = n-1;

	divideMatrix(0,rowLow,rowHigh,colLow,colHigh,p);

	for(int i=0;i<p;i++)
	{
		cout << rowLow[i] << " " << rowHigh[i] << " " << colLow[i] << " " << colHigh[i] << endl;
	}
	return 0;
}
#include <stdio.h>

//Prototypes the following six lines must 
//be here or the program will not compile
double getIntArrayAverage(int[], int); //done
int getIntArrayMax(int[], int); //done
int getIntArrayMin(int[], int);//done
int getValueCount(int[], int, int); //done
int getMaxCount(int[], int);

double getIntArrayAverage(int avgArr[], int num)
{
	double total = 0;
	for(int i = 0; i < num; i++)
	{
		total += avgArr[i];
	}
	return total/num;
}


int getIntArrayMax(int maxArr[], int num)
{
	int maxValue = maxArr[0];
	for(int i = 0; i < num; i++)
	{
		if(maxArr[i] > maxValue)
			maxValue = maxArr[i];
	}
	if(num!=0)
	return maxValue;
	return -2147483648;
}


int getIntArrayMin(int minArr[], int num)
{
	int minValue = minArr[0];
	for(int i = 0; i < num; i++)
	{
		if(minArr[i] < minValue)
			minValue = minArr[i];
	}
	if(num!=0)
	return minValue;
	return 2147483647;
}


int getValueCount(int countArr[], int num, int value)
{
	
	int valueCount = 0;
	for(int i = 0; i < num; i++)
	{
		if(countArr[i] == value)
			valueCount++;	
	}
	return valueCount;
}

int getMaxCount(int arrMax[], int num)
{
	int max_value = getIntArrayMax(arrMax, num);
	return getValueCount(arrMax, num, max_value);
}

















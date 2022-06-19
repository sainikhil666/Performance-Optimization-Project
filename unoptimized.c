#include<stdio.h>
#include<stdlib.h>
#include <time.h>
float average(float *DataSet,int DataSetSize);
float maximum(float *DataSet,int DataSetSize);
float minimum(float *DataSet,int DataSetSize);
int create_dataset(int DataSetSize, char* filename);
int loadDataset (char *filename,int buffer,int DataSet,float *DataSetSize);
int writeDataset (float *DataSetSize, int DataSet, int buffer, char *filename);

//for generating a random number
float generateRand(float rmax){
    return ((float)rand()/(float)RAND_MAX)*rmax;
}

//function for creating dataset
int create_dataset(int DataSetSize, char* filename)
{
	FILE *f;

	f = fopen(filename, "wb");
	srand((unsigned int)time(NULL)); 
	float *Random = (float *)malloc(sizeof(float)*DataSetSize);
	for(int i=0;i<DataSetSize;i++)
	{
		Random[i]=generateRand(100);

	}
	fwrite(Random, sizeof(float), DataSetSize, f);
	fclose(f);
    return 0;
}

//same code considered for the load dataset which is given in assignment pseudo code
int loadDataset (char *filename,int buffer,int DataSet,float *DataSetSize) 
{ 
	FILE *fp;
	fp = fopen( filename , "rb" ); 
	for(int i=0;i<DataSet;i+=buffer)
	{
		if(i+buffer>DataSet)
		{
			buffer=DataSet-i;
		}
		fread(DataSetSize, sizeof(float), buffer, fp ); 
		DataSetSize+=buffer;
	}
	
	fclose(fp);
    return 0;
}

//same code considered for the write dataset which is given in assignment pseudo code
int writeDataset (float *DataSetSize, int DataSet, int buffer, char *filename)
{
	FILE *fp;
	fp = fopen( filename , "wb+" ); 
	for(int i=0; i<DataSet; i+=buffer)
	{
		
		if(i+buffer>DataSet)
		{
			buffer=DataSet-i;
		}
		fwrite(DataSetSize , sizeof(float), buffer, fp );	
		DataSetSize+=buffer;
	}
	
	fclose(fp);
    return 0;
}


float average(float *DataSet,int DataSetSize)

{
	float average_value, add = 0;
	for(int i=0;i<DataSetSize;i++)
	{
		add+=DataSet[i];
	}
	average_value = (float)add/DataSetSize;
	return average_value;
}

float maximum(float *DataSet,int DataSetSize)

{
	float maximum_value= DataSet[0];
	for(int i=0;i<DataSetSize;i++)
	{
		if(DataSet[i]>maximum_value)
		{
			maximum_value=DataSet[i];
		}
	}
	return maximum_value;
}

float minimum(float *DataSet,int DataSetSize)

{
	float minimum_value = DataSet[0];
	for(int i=0;i<DataSetSize;i++)
	{
		if(DataSet[i]<minimum_value)
		{
			minimum_value=DataSet[i];
		}
	}
	return minimum_value;
}


void swap(float *xp, float *yp){
float temp = *xp;
*xp = *yp;
*yp = temp;
}



//same code considered for the selection sort which is given in assignment pseudo code
void selectionSort(float *DataSet, int DataSetSize)
{
    int i, j, min_idx;
    for (int i = 0; i < DataSetSize-1; i++)
    {
        min_idx = i;
        for (int j = i+1; j < DataSetSize; j++)
            if (DataSet[j] < DataSet[min_idx])
                min_idx = j;
        swap(&DataSet[min_idx], &DataSet[i]);
    }
}


int main(int argc,char *argv[])
{	
    char *input_filename, *output_filename;
    int datasize, buffer;
    clock_t initial_load_time,final_load_time, initial_sort_time, final_sort_time, initial_write_time,final_write_time;

    datasize = atoi(argv[1]);
    buffer = atoi(argv[2]);
    input_filename = argv[3];
    output_filename = argv[4];

 
    float *dataset= malloc(sizeof(float)* datasize);
    printf("creating a Data set.\n");
    create_dataset(datasize, input_filename);
    initial_load_time = clock();
    printf("Loading the data set.\n");
    loadDataset(input_filename, buffer, datasize, dataset);
    final_load_time = clock();

    printf("Sorting the data set.\n ");
    printf("Maximum Value: %f \n", maximum(dataset,datasize));
    printf("Minimum Value: %f \n", minimum(dataset,datasize));
    printf("Average Value: %f \n", average(dataset,datasize));
    initial_sort_time = clock();
    selectionSort(dataset, datasize);
    final_sort_time = clock();


    printf("Writing the data set.\n ");
    initial_write_time = clock();
    writeDataset(dataset, datasize, buffer, output_filename);
    final_write_time = clock();
    
    free(dataset);

    double total_load_time = (double)(final_load_time - initial_load_time)/CLOCKS_PER_SEC;
    printf("Total loading data time: %f sec\n", total_load_time);
    double total_sorting_time = (double)(final_sort_time-initial_sort_time)/CLOCKS_PER_SEC;
    printf("Total sorting time: %f sec \n", total_sorting_time);
    double total_writing_time = (double)(final_write_time - initial_write_time)/CLOCKS_PER_SEC;
    printf("Total writing time: %f sec \n", total_writing_time);
    double total_time = total_load_time + total_writing_time + total_sorting_time;
    printf("Total time: %f sec\n", total_time);
    
    return 0;

}
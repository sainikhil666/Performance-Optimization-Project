# Performance-Optimization-Project
The goal of the project is to optimize the functionality of RESOW, a simple C program. It performs different types of operations such as reading data from a file, sorting the data, and writing the sorted data to a new file. The dataset consists of records, each of which is of the datatype float. The values are generated with the help of the generateRand function. The buffer is a physical memory space where data is temporarily stored. The application's scalability is determined by changing the buffer size. The standard buffer size for Scalability test and analysis is 1024. 

Execution: 
For executing unoptimized code, 

gcc unoptimized.c 

./a.out Datasetsize buffersize inputfilename outputfilename 

For executing optimized code, 

gcc -o3 unoptimized.c 

./3 Datasetsize buffersize inputfilename outputfilename 

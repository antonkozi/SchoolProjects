//-----------------------------------------------------------------------------
// Simulation.c
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include"Job.h"
#include"IntegerQueue.h"

//-----------------------------------------------------------------------------
// The following function may be of use in assembling the initial backup array.
// You may use it as is, alter it as you see fit, or delete it altogether.
//-----------------------------------------------------------------------------

// getjob()
// Reads two numbers from file in, and returns a new Job with those numbers
// as arrival and duration.
Job getJob(FILE* in) {
	int a, d;
	fscanf(in, "%d %d\n", &a, &d);
	return newJob(a, d);
}

//returns index of the shortest queue
//l = 2
int getShortest(int l, IntegerQueue* queue)
{
	int shortest = 1;
	for (int i = 2; i <= l; i++)
	{
		if (length(queue[i]) < length(queue[shortest]))
		{
			shortest = i;
		}
	}

	return shortest;
}


//-----------------------------------------------------------------------------
// The following stub for function main() contains a possible algorithm for 
// this project.  Follow it if you like.  Note that there are no instructions 
// included below for writing to either of the output files.  You must 
// intersperse those commands as necessary.
//-----------------------------------------------------------------------------

// main()
int main(int argc, char* argv[]) {

	FILE* in;
	FILE* trace;
	FILE* report;
	IntegerQueue* pQue;
	Job* jobs;
	char* strA;
	int* nums;
	int m = 0;   //size of job array
	int time = 0;
	int shortindex;
	int totalWait = 0;
	int maxWait = 0;
	double averageWait = 0;
	int tempWait;
	int eventHappening = 0;
	char inp[100] = "";
	char rpt[100] = "";
	char trc[100] = "";
	


	// check command line arguments
	if (argc != 2) {
		printf("Usage: %s inputfile output-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// open files for reading and writing
	if ((in = fopen(argv[1], "r")) == NULL) {
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	strcpy(inp, argv[1]);
	strcat(inp, ".trc");
	strcpy(trc, inp);


	if ((trace = fopen(inp, "w")) == NULL) {
		printf("Unable to write to file %s\n", trc);
		exit(EXIT_FAILURE);
	}

	strcpy(inp, argv[1]);
	strcat(inp, ".rpt");
	strcpy(rpt, inp);
	

	if ((report = fopen(inp,  "w")) == NULL) {
		printf("Unable to write to file %s\n", rpt);
		exit(EXIT_FAILURE);
	}

	// read in m jobs from input file and place them in backup array
	fscanf(in, "%d", &m);

	//get jobs from file
	jobs = (Job*)calloc(m, sizeof(Job));
	for (int i = 0; i < m; i++)
	{
		jobs[i] = getJob(in);

	}


	// declare and initialize an array of m-1 processor Queues along with
	//any necessary storage queues
	pQue =  (IntegerQueue*)calloc(m, sizeof(IntegerQueue));

	//nums will be used to convert strings to ints for printing purposes
	nums = (int*)calloc(m, sizeof(int));

	for (int i = 0; i < m; i++)
	{
		pQue[i] = newIntegerQueue();
	}

	fprintf(trace, "Trace File: %s\n" , trc);
	fprintf(trace, "%d Jobs:\n", m);
	fprintf(report, "Report File: %s\n" , rpt);
	fprintf(report, "%d Jobs:\n", m);

	for (int i = 0; i < m; i++)
	{
		printJob(trace, jobs[i]);
		printJob(report, jobs[i]);
	}
	fprintf(trace, "\n");
	fprintf(report, "\n\n");
	fprintf(report, "***********************************************************\n");

	// loop: run simulation with n processors for n=1 to n=m-1 {
	for (int n = 1; n < m; n++) {
		
		fprintf(trace, "*****************************\n");
		if (n == 1)
		{
			fprintf(trace, "%d processor:\n", n);
		}
		else
		{
			fprintf(trace, "%d processors:\n", n);
		}
		fprintf(trace, "*****************************\n");

		//    place Job indices from backup array into storage queue
		for (int i = 0; i < m; i++)
		{
			enqueue(pQue[0], i);
		}

		


		fprintf(trace, "\n");
		//loop will run until all three elements are finished
	
		while (length(pQue[0]) == 0 || getFinish(jobs[peek(pQue[0])]) == UNDEF || length(pQue[0]) != m  )
		{
			
			//       if any Jobs finish now, then complete them in the order they appear in 
			//       the queue array, i.e. lowest index first.
			
			for (int i = 1; i <= n; i++)
			{
				if (isEmpty(pQue[i]) == 0) 
				{
					//check the job at the front of the ith queue for finish
					if (getFinish(jobs[peek(pQue[i])]) == time)
					{
						//printJob(trace, jobs[peek(pQue[i])]);
						enqueue(pQue[0], dequeue(pQue[i]));
						eventHappening = 1;
					}
				}
			}

			//deals with arrivals
				while (!(isEmpty(pQue[0])) && getArrival(jobs[peek(pQue[0])]) == time)
				{
					shortindex = getShortest(n, pQue);
					//print out the short index 
					enqueue(pQue[shortindex], dequeue(pQue[0]));
					eventHappening = 1;

				}
			

				//set finish times if the item at the front of the queue does not have one
				for (int i = 1; i <= n; i++)
				{
					if (!(isEmpty(pQue[i]) ) )
					{
						if (getFinish(jobs[peek(pQue[i])]) == UNDEF)
						{
							//compute finish and wait time
							computeFinishTime(jobs[peek(pQue[i])], time);
							tempWait = getWaitTime(jobs[peek(pQue[i])]);
							if (tempWait > maxWait)
							{
								maxWait = tempWait;
							}
							totalWait += tempWait;
						}
					}
				}

				//print the state of the queues if an event has occured
				if(eventHappening == 1 || time == 0)
				{
					fprintf(trace, "time=%d\n", time);
					for (int i = 0; i <= n; i++)
					{
						//holds position of next scan
						int position;
						
						//turn the queue into a string then reverse it and print out the jobs at those indicies 
						    fprintf(trace, "%d: ", i);
							strA = IntegerQueueToString(pQue[i]);
							

							
							for (int j = 0; j < length(pQue[i]); j++)
							{
								sscanf(strA, "%d %n", &nums[j], &position);
								printJob(trace, jobs[nums[j]]);
								strA += position;
							}
					
							
							strA = IntegerQueueToString(pQue[i]);
							free(strA);
						
				
						fprintf(trace, "\n");
					}
					fprintf(trace, "\n");
				}

				//increment time and reset the event watcher
				time++;	
				eventHappening = 0;
				

		}

	    //compute wait time
		averageWait = (double) totalWait / m;
		
		if (n == 1)
		{
			fprintf(report, "%d processor: totalWait=%d, maxWait=%d, averageWait=%.2f\n", n, totalWait, maxWait, averageWait);
		}
		else
		{
			fprintf(report, "%d processors: totalWait=%d, maxWait=%d, averageWait=%.2f\n", n, totalWait, maxWait, averageWait);
		}

		//reset times and queues
		for (int i = 0; i < m; i++)
		{
			resetFinishTime(jobs[i]);
		}
		dequeueAll(pQue[0]);
		maxWait = 0;
		totalWait = 0;
		time = 0;
	}

	//close files and free all heap memory
	fclose(report);
	fclose(trace);
	fclose(in);
	free(nums);
	free(pQue);
	free(jobs);
	return EXIT_SUCCESS;
}


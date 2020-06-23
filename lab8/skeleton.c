#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LRU 0
#define FIFO 1
#define SECOND_CHANCE 2

typedef struct {//to 
    int pageno;
} ref_page;

int page_replacement = SECOND_CHANCE;

int hit;
int clock_hand = 0;								//initializes the clock hand to position 0

int main(int argc, char *argv[]){
	int i, j;
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file
	int oldest;
	int max;							//max variable to see which page is the oldest
    int totalFaults = 0; // keeps track of the total page faults
    int parallel_array[C_SIZE];					//allocates a parallel array for the LRU or second chance page replacement and initializes eachvalue to 0
    for (i = 0; i < C_SIZE; i++){//initialise cache array and parallel array  
        cache[i].pageno = -1;
	parallel_array[i] = 0;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
	oldest = 0;
	max = 0;						//initializes max to be the newest
	hit = 0;						//initializes the hit to 0 each time there's an input
	if(page_replacement == FIFO) { 				//FIFO page replacement
		for(i=0; i<C_SIZE; i++) {			//traverses the cache array to find if the number was found
			if(cache[i].pageno == page_num) {		//if number was found, don't need to replace so we just break out of the loop
				hit = 1;
				break;
			}	
		}
		if(hit == 0) {					//number was not found
			totalFaults++;				//increments the number of faults
			while((cache[i].pageno!=-1) && (i!=C_SIZE)){
				i++;
			}
			if(i==C_SIZE) {
				for(i=0; i<(C_SIZE-1); i++) {
					cache[i].pageno = cache[i+1].pageno;		//shift everything
				}
			}
			cache[i].pageno = page_num;			//set last entry as the page_num
		}
	}

	else if((page_replacement == LRU)) {				//LRU page replacement
		i=0;
		while((cache[i].pageno!=-1)&&(i!=C_SIZE)) {				//traverses the cache array in search of the page number
			if(parallel_array[i]>max) {
				max = parallel_array[i];
				oldest = i;
			}		
			if(cache[i].pageno == page_num) {
				parallel_array[i] = 0;			//sets parallel array value at the index to 0 to show it is the newest
				hit = 1;
				break;
			}
			i++;
		}						
		if(hit == 0) { 						//number was not found (could be that the array is full or not full)
			totalFaults++;					//increments number of faults
			if(cache[i].pageno == -1) {	//if array is not full and the value of the element is -1
				cache[i].pageno = page_num;		//theres an empty slot and we can add the page_num
			} else {					//otherwise, the array is full and we need to get rid of the oldest element
				cache[oldest].pageno = page_num;
				parallel_array[oldest] = 0;
			}
		}

		for(i=0; i<C_SIZE; i++) {
			if(cache[i].pageno != -1) {
				parallel_array[i]=parallel_array[i]+1;			//if there is a page number in the cache it increments the value in the parallel array which symbolizes which pages was there the longest;
			}
		}	
	}

	else {								//Second chance page replacement where the parallel_array represents the chance 0=new, 1=shes gotta go
		i=0;
		while((cache[i].pageno!=-1)&&(i!=C_SIZE)) { 		//traverses the array while there's not an empty slot or until it reaches the end
			if(cache[i].pageno == page_num) { 			//if we found the page_num
				hit=1;
				parallel_array[i] = 1;
				break;
			}
			i++;
		}
		if(hit==0) {						//if there was no hit
			totalFaults++;					//increment the number of faults
			if(cache[i].pageno==-1) {		//if theres an empty slot
				cache[i].pageno = page_num;		//set cache value at i to page_num
				parallel_array[i] = 0;
				clock_hand = (clock_hand+1)%C_SIZE;
			} else {					//theres no room left on the array so we gotta traverse using the clock_hand
				while(parallel_array[clock_hand]==1){
					parallel_array[clock_hand]=0;
					clock_hand = (clock_hand+1)%C_SIZE;	//increments the clockhand
				}
				cache[clock_hand].pageno = page_num;
				parallel_array[clock_hand]=1;
			}
		}
									
	}
    	/*
	
		
		Page Replacement Implementation Goes Here 


    	*/
    
	}
    printf("\n%d Total Page Faults\n", totalFaults);
    return 0;



}

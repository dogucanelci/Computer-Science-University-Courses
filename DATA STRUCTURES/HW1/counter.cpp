/*
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/
/* @Author
Student Name: <Dogu Can ELCI>
Student ID : <504201516>
Date: <11.10.20> */

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "counter.h"

using namespace std;

	
int Counter::findindex(Token *arr,char elem[]){
	for(int i=0;i<ARRAY_SIZE;i++){
		if(*(arr[i].token)==*(elem) and *(arr[i].token+1)==*(elem+1) ){
			return i;
		}
	}
	return -1;
} 

bool Counter::contains(char *token, char target){
	if(*token==target){
		return true;
	}
	return false;
}

void Counter::read_and_count(){
		Token k;
		char k1[1];
		const char* file1;
		file1="pi_approximate";
		FILE *pi = fopen( file1, "r+" );
		fread( &k1, 1, 1, pi);
		int acc=0;	
			
		for(int i=0;i<ARRAY_SIZE-1;i++){
			
			for(int j=0;j<2;j++){
				
				if (contains(k1,'.')){
					fread( &k1, 1, 1, pi);
					break;
					
				}
				k.token[0]=*k1;
				fread( &k1, 1, 1, pi);
				if(contains(k1,'.')){
					fread( &k1, 1, 1, pi);
					break;
				}
				k.token[1]=*k1;
				token_array[acc].token[0]=k.token[0];
				token_array[acc].token[1]=k.token[1];
				*(token_array[acc].token)=*(k.token);
				*(token_array[acc].token+1)=*(k.token+1);
				acc++;
				
				
			} // end of creating array process

			if(acc>ARRAY_SIZE-2){
					break;
				}

			}			
		for(int i=0;i<ARRAY_SIZE;i++){
			for(int j=0;j<ARRAY_SIZE;j++){
				if(*(token_array[i].token)==*(token_array[j].token) and *(token_array[i].token+1)==*(token_array[j].token+1)) {
					int count1=token_array[i].count;
					count1++;
					*(&token_array[i].count)=count1;
					count1=0;
					
				}
			}
		
		} //end of count process
	}
		

Token *Counter::get_most_common_three(){
Token swap;
for(int i=0;i<ARRAY_SIZE;i++){
	for(int j=0;j<ARRAY_SIZE;j++){
		if(i<=j){
		if(token_array[i].count<token_array[j].count){
			swap.count=token_array[i].count;
			*(swap.token)=*(token_array[i].token);
			*(swap.token+1)=*(token_array[i].token+1);
			token_array[i].count=token_array[j].count;
			*(token_array[i].token)=*(token_array[j].token);
			*(token_array[i].token+1)=*(token_array[j].token+1);
			token_array[j].count=swap.count;
			*(token_array[j].token)=*(swap.token);
			*(token_array[j].token+1)=*(swap.token+1);
}
continue; 
		}

		}

	}
	int *ptr;
	for(int j=0;j<3;j++){
			int rr=(*ptr)*(j);
			most_common_array[j].count=token_array[rr].count;
			*(most_common_array[j].token)=*(token_array[rr].token);
			*(most_common_array[j].token+1)=*(token_array[rr].token+1);
			ptr=(&token_array[j].count);
	}
				
	return most_common_array;
}






#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
char name[25];
int grade;
char gradeLetter;
};

int readGraderFile(char* gradedFileName){
int compile = 1;
int headers = 0;
int ptsOff = 0;
char fileLine[100];
char fileLineA[100];
printf(gradedFileName);
//Opening anwser code file
FILE *fpAns;
fpAns = fopen("answer_code.c", "r");
//Opening student file
FILE *fpStu;
fpStu = fopen(gradedFileName, "r");
if((fpAns == NULL) || (fpStu == NULL)){
perror("File error.");
exit(EXIT_FAILURE);
}
else{
printf(" file opened\n");
}
//check max line length and update
// Reads file line by line
  int i = 1;
  while(fgets(fileLine, 53, fpStu) && fgets(fileLineA, 53, fpAns)) {
  //printf("%s",fileLineA);
  if(strstr(fileLine, "<") != NULL){
  if(strstr(fileLine, "<stdio.h>") != NULL || strstr(fileLine, "<errno.h>") != NULL){
  }
  else{
  //compile = 0;
  }
  }
  //if(strstr(fileLine, ";") != NULL){
  //if(strstr(fileLine, ";;") != NULL || strstr(fileLine, "};") != NULL){
  //compile = 0;
  //}
  //}
   
  if(strcmp(fileLine, fileLineA) == 0){
  //printf("%d\n", i);
  //grade++;
  } 
  else{
  ptsOff++;
  //debugging info below
  //printf("No match\n");
  printf("line 1 is %s\n", fileLine);
  printf("line 2 is %s\n", fileLineA);
  }
}
fclose(fpAns);
fclose(fpStu);
//printf("did compile %d\n", compile);
if(compile == 0){
return -1;
}
else{
return (100 - ptsOff);
}
}

const char* num2Lett(int grade){
	int newGrade = (int)(grade * 10);
	switch(newGrade){
		//200 to account for extra cred
		case 940 ... 2000:
			return "A";
			break;
		case 890 ... 939:
			return "A-";
			break;
		case 860 ... 889:
                        return "B+";
                        break;
		case 820 ... 859:
                        return "B";
                        break;
		case 780 ... 819:
                        return "B-";
                        break;
		case 750 ... 779:
                        return "C+";
                        break;
		case 710 ... 749:
                        return "C";
                        break;
		case 680 ... 709:
                        return "C-";
                        break;
		case 650 ... 679:
                        return "D+";
                        break;
		case 610 ... 649:
                        return "D";
                        break;
		case 580 ... 609:
                        return "D-";
                        break;
		default:
			return "F";
			break;
	}
}

void printGradeLs(int sorted[], int order[], int dncInd[]){
FILE *fp;
fp = fopen("student_grades", "w");
for(int i = 0; i < 4; i++){
if(dncInd[i] == 0){
fprintf(fp, "student%d %d %s\n", order[i] + 1, sorted[i], num2Lett(sorted[i]));
}
else{
fprintf(fp, "student%d DNC %s\n", order[i] + 1, num2Lett(sorted[i]));
}
}
fclose(fp);
}


void printArr(int key[]){
for(int i = 0; i < 4; i++){
printf("%d\n", key[i]);
}
}

void sortArray(int *key, int *sorted, int *order){
int index;
//outer loop controls sorted array
for(int j = 0; j < 4; j++){
int maxValue = -1;
index = -1;
//inner looks through key vals
for(int i = 0; i < 4; i++){
if(key[i] == -1){
continue;
}
else if(maxValue < key[i]){
maxValue = key[i];
index = i;
}
}
sorted[j] = maxValue;
order[j] = index;
if(index < 0){
break;
}
key[index] = -1;
}

}



int main(){
	//calling it a key because its holding the value of the actual gradeit represents
	//first element grade, second element student num
	int dncInd[4];
	int order[4];
	int key[4];
	int sorted[4];
	int s1Grade = readGraderFile("student1-hw1.c");
	key[0] = s1Grade;
        int s2Grade = readGraderFile("student2-hw1.c");
	key[1] = s2Grade;
	int s3Grade = readGraderFile("student3-hw1.c");
	key[2] = s3Grade;
	int s4Grade = readGraderFile("student4-hw1.c");
	key[3] = s4Grade;
	//key[0] = 79;
	//key[1] = 97;
	//key[2] = -1;
        //key[3] = -1;
	printf("%d", key[2]);
	
	for(int i = 0; i < 4; i++){
	if(key[i] == -1){
	key[i] = 0;
	//printf("%d\n", i);
	dncInd[i] = i;
	}
	else{
	dncInd[i] = 0;
	}
	}	
	sortArray(key, sorted, order);
	//printArr(dncInd);
	printGradeLs(sorted, order, dncInd);
        	
	return 0;
}


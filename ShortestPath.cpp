#include <stdio.h>
#include <stdlib.h>
#include <deque>
#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include <cstdlib>

using namespace std;

FILE *finput;//The file pointer to read file
FILE *foutput;//The file pointer for writing the result

//the function declaration
bool inLIST( int);

//global variable
deque< int > LIST;//The dequeue to stroe the current node

int main(void){

	//variable declaration
	int i,j;//the for loop counter
	int vertices, edges, v1, v2, weight;//variable for graph(adjacent list)
	int temp,temp2,temp3;
		
	//read the file network which contain a direct network data
    if((finput = fopen("network.txt","r")) == NULL)
    {
        fprintf(foutput,"The file could not be opened!\n");
        exit(0);
    }
	else{
		fscanf(finput,"%d %d",&vertices,&edges);
	}//the end of if-else
	bool* PASS = new bool[vertices];//as the bool PASS[vertices];
	for(i=0;i<vertices;i++){
		PASS[i]=false;
	}
	
	vector< list< pair<int, int> > > adjacencyList(vertices);//adjacent list
	//prepare data to start the label-correcting
	int* d = new int[vertices];//int d[vertices];
	int* pred = new int[vertices];//int pred[vertices]={0};//pred(s)<-0
	d[0]=0;//d(s)<-0
	pred[0]=0;///pred(s)<-0
	for (j=1;j<vertices;j++){//d(j)<-infinite for each j(N-{S})
		d[j]=999999;//999999 stand for the infinite
	}
	LIST.push_front(0);//LIST<-{s}
	PASS[0]=true;//the node 0 have entered the dequeue(LIST)
	
		//create a file to store the result of calculation of Label correcting algorithm 
    if((foutput = fopen("shortestPath.txt","w")) == NULL)
    {
        fprintf(foutput,"The file could not be opened!(shorestPath.txt)\n");
        exit(0);
    }
	else{
		for(i=0;i<edges;i++){
			fscanf(finput,"%d %d %d\n",&v1,&v2,&weight);
			adjacencyList[v1].push_back(make_pair(v2, weight));
		}
		
		while(!LIST.empty()){//while LIST != (empty set) then do while loop
			temp=LIST.front();//know what element remove from deque
			LIST.pop_front();//remove first element
			/*fprintf(foutput,"The element pop from deque %d",temp);
			test that get the right thing
			*/
			
			list< pair<int, int> >::iterator itr = adjacencyList[temp].begin();
			if (adjacencyList[temp].empty()){
				//fprintf(foutput,"empty");
				++itr;
				}
			else 
				while ( itr != adjacencyList[temp].end()) {//for each arc (i,j) do
				//fprintf(foutput,"The distance from %d to %d is %d \t", i ,(*itr).first, (*itr).second);
				temp2=(*itr).first;//temp2 is j
				temp3=(*itr).second;//temp3 is Cij
				//fprintf(foutput,"%d %d\n",temp2,temp3);
				
				if(d[temp2]>(d[temp]+temp3)){
					d[temp2]=d[temp]+temp3;
					pred[temp2]=temp;
					//fprintf(foutput,"%d %d\n",d[temp2],pred[temp2]);					
					if( ! (inLIST(temp2)) ){//if j not in dequeue then add node to
						//have ever pass should push_front into the dequeue(LIST)
						if(PASS[temp2]==true){
							LIST.push_front(temp2);
						}else{	
						LIST.push_back(temp2);
						PASS[temp2]=true;
						//fprintf(foutput,"Add node %d into deque\n",temp3);
						}
					}//the end of if
				}//the end of if
				++itr;
				}//the end of inner-while

		}//the end of outer-while
		//fprintf(foutput,"The result of d[] and pred[] \n");
	for (j=0;j<vertices;j++){
		fprintf(foutput,"%d %d %d\n",j,pred[j],d[j]);
	}
	
}
return 0;//the end of main
}




bool inLIST(int node){//parameter for check whether this Node is in deque
	bool result=false;
	int i;
	for (i=0;i<LIST.size();i++){
		if(node==LIST[i]){
			result || true;
		}
	}
	return result;
}


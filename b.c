#include<stdio.h>
int main(){
	int array[20][20];
	int counter3=0,counter4=0;
	int i=0,j=0,k=0,l=0,x=0,y=0,z;
	int command,move;
	
	for(i=0;i<20;i++){
		for(j=0;j<20;j++)
			array[i][j]='0';
	}
		scanf("%d",&command);
		
	if(command==2){
		while(1){
			scanf("%d",&command);
			if(command==9){
				break;
			}
			else if(command==6){
				for(i=0;i<20;i++){
					for(j=0;j<20;j++){
					    if(array[i][j]=='*'){
						    printf("%c ",array[i][j]);
						}
						else 
						    printf(" ");
					}
					printf("\n");
				}	
			}
			else if(command==3){
			    counter3++;
			   // printf("counter3:%d",counter3);
			}
			else if(command==4){
			    counter4++;
			    //printf("counter4:%d",counter4);
			}
			else if(command==5){
				
				scanf("%d",&move);
				
				if(counter3==counter4){
				    for(j=y;j<move+y;j++){
				        array[x][j]='*';
				    }
				    //x=i;
				    y+=move;
				}
				else if((counter3>counter4)&&((counter3-counter4)%2==0)){    
				    //düz
				    for(j=y;j<move+y;j++){
				        array[x][j]='*';
				    }
				        y+=move;
				        //x=i;
				    
				    //i=0 j=0 -> i=0 j=1
				    //y=j+move; x=i;
				     
			    }
			    else if((counter3>counter4)&&((counter3-counter4)%2!=0)){    
				    //asagı     
				    for(i=x;i<move+x;i++){
				        array[i][y]='*';
				    }
				        //y=j;
				        x+=move;
				    
				    //i=1 j=0 -> i=2 j=0
				    //x=i+move; y=j;
			    }
			    else if((counter4>counter3)&&((counter4-counter3)%2==0)){    
				   //ters
				    for(j=y;j<y-move;j--){
				        array[x][j]='*';
				     }
				        y-=move;
				       // x=i;
				      
				   //i=1 j=2 -> i=1 j=1
				    //y=j-move; x=i;      
			    }
			    else if((counter4>counter3)&&((counter4-counter3)%2!=0)){    
				    //yukarı
				     for(i=x;i<x-move;i--){
				        array[i][y]='*';
				     }
				       // y=j;
				        x-=move;
				    //i=2 j=2 -> i=1 j=2
				    //x=i-move; y=j;    
			    
			    }
			
			
			
		}
		
	}

 }
	return 0;
}

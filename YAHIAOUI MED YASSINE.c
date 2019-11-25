/***
	YAHIAOUI MED YASSINE
						***/

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <time.h> 
#include<math.h>
#include<omp.h>

#define LigneA 4
#define  ColonneA 4
#define LigneB 4
#define  ColonneB 4
int A [LigneA] [ColonneA];
int B [LigneB] [ColonneB];
int C [LigneA] [ColonneB]; 

int main(int argc, char *argv[]){

	double debutPar,finPar,debutSeq,finSeq;
	int i,j,k;
	
	//initialisation des matrices
	for ( i = 0; i < LigneA; i++) { 
        for (j = 0; j < ColonneA; j++) { 
            A[i][j] = rand() % 10; 
        } 
    } 
	for ( i = 0; i < LigneB; i++) { 
        for (j = 0; j < ColonneB; j++) {  
            B[i][j] = rand() % 10; 
        } 
    } 
    
    // affichage des matrice 
	printf("matrice A :\n") ;
	for (i = 0; i < LigneA; i++) { 
        for (j = 0; j < ColonneA; j++) { 
 			printf("%d  ",A[i][j]) ;
         	
		}
		printf("\n");
	}
 
	printf("matrice B :\n") ;
	for (i = 0; i < LigneB; i++) { 
        for (j = 0; j < ColonneB; j++) { 
 			printf("%d  ",B[i][j]) ;
         	
		}
		printf("\n");
	}

    //calcul parallel
    debutPar=clock();
    #pragma omp parallel for
        for( i = 0;i < LigneA; i++){
        	for(j = 0; j < ColonneB; j++) {
				for(k = 0; k < ColonneB; k++)
                	C[i][j] =C[i][j] + A[i][k] * B[k][j]; 
            }

        }
         
        
    finPar=clock(); 
    // afficahge de resultat parallel
    printf("Matrice C parallel : \n ");
	for (i = 0; i < LigneA; ++i){
       for ( j = 0; j < ColonneB; ++j){
           printf("%d  ", C[i][j]); 
       }
       printf("\n"); 
   }
    printf("temps parallele = %f \n", (double)(finPar-debutPar)/CLOCKS_PER_SEC);
        
    //calcule sequenciel 
    debutSeq=clock();
	for ( i = 0; i < LigneA; ++i){
       for ( j = 0; j < ColonneB; ++j){
          C[i][j]=0;
          for (k = 0; k < ColonneB; ++k)
          {    
             C[i][j]=C[i][j]+A[i][k]*B[k][j];
          }
       } 
   } 
        
    finSeq=clock();

    
    // afficahge de resultat sequenciel  
    printf("Matrice C sequenciel : \n ");
	for ( i = 0; i < LigneA; ++i){
       for (j = 0; j < ColonneB; ++j){
           printf("%d  ", C[i][j]); 
       }
       printf("\n"); 
   }
    	 
    printf("temps sequenciel= %f\n", (double)(finSeq-debutSeq)/CLOCKS_PER_SEC);
	  
    return 0;

    }
  


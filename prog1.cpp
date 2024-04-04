#include <iostream>
#include <cmath>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{
	double ti,tf;
	if (MPI_Init(&argc,&argv) != MPI_SUCCESS) 
	{
		MPI_Finalize();
		exit(-1);
	}

	int nprocs,idproc;
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&idproc);
	long int N=120000000000;
	if (idproc == 0) 
	{
		if (N%nprocs != 0) 
		{
			cout << endl << endl << endl
				<< "N deve ser multiplo de nprocs"
				<< endl << endl << endl;
			N=-1;
		}
	}
	MPI_Bcast(&N, 1, MPI_LONG, 0, MPI_COMM_WORLD);

	int tag=1;

	double h=1.0/N,sum=0.0;
	long int r=N/nprocs;
	for (long int i=1+idproc*r; i <= (idproc+1)*r; i++) 
	{
		double x=h*(i-0.5);
		sum+=1.0/(1.0+x*x);
	}
	sum*=h;
	double result=0.0;

	MPI_Reduce(&sum,&result,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

		// manda o valor da soma para o mestre	

	if(idproc==0)
	{
		double Pi=3.141592653589793238462643;
		tf=MPI_Wtime();
		std::cout << endl << tf <<" "<< fabs(result-0.25*Pi) <<endl;
	}
	MPI_Finalize();
	return 0;
}				

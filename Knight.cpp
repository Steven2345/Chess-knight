#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <cstdlib>
using namespace std;

int n;
mutex mtx;
int nr_sol;

void show(int id, int **a)
{
    mtx.lock();
    nr_sol++;
    cout<<"I'm thread no. "<<id<<'\n';
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            cout<<setw(3)<<a[i][j]<<' ';
        cout<<'\n';
    }
    cout<<'\n';
    mtx.unlock();
}

void back(int id, int k, int lin, int col, int **a)
{
    if(k==n*n)
    {
        // display solution
        show(id, a);
    }
    else
    {
        if(lin-2 >= 0)
        {
            if(col-1 >= 0 && !a[lin-2][col-1])
            {
                a[lin-2][col-1]=k+1;
                back(id, k+1, lin-2, col-1, a);
                a[lin-2][col-1]=0;
            }
            if(col+1 <= n-1 && !a[lin-2][col+1])
            {
                a[lin-2][col+1]=k+1;
                back(id, k+1, lin-2, col+1, a);
                a[lin-2][col+1]=0;
            }
        }
        if(lin+2 <= n-1)
        {
            if(col-1 >= 0 && !a[lin+2][col-1])
            {
                a[lin+2][col-1]=k+1;
                back(id, k+1, lin+2, col-1, a);
                a[lin+2][col-1]=0;
            }
            if(col+1 <= n-1 && !a[lin+2][col+1])
            {
                a[lin+2][col+1]=k+1;
                back(id, k+1, lin+2, col+1, a);
                a[lin+2][col+1]=0;
            }
        }
        if(col-2 >= 0)
        {
            if(lin-1 >= 0 && !a[lin-1][col-2])
            {
                a[lin-1][col-2]=k+1;
                back(id, k+1, lin-1, col-2, a);
                a[lin-1][col-2]=0;
            }
            if(lin+1 <= n-1 && !a[lin+1][col-2])
            {
                a[lin+1][col-2]=k+1;
                back(id, k+1, lin+1, col-2, a);
                a[lin+1][col-2]=0;
            }
        }
        if(col+2 <= n-1)
        {
            if(lin-1 >= 0 && !a[lin-1][col+2])
            {
                a[lin-1][col+2]=k+1;
                back(id, k+1, lin-1, col+2, a);
                a[lin-1][col+2]=0;
            }
            if(lin+1 <= n-1 && !a[lin+1][col+2])
            {
                a[lin+1][col+2]=k+1;
                back(id, k+1, lin+1, col+2, a);
                a[lin+1][col+2]=0;
            }
        }
    }
}

int main()
{
    cout<<"Give dimension of the board: ";
    cin>>n;

    thread th[n][n];
    int** mat[n][n];

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            mat[i][j] = new int*[n];
            for(int k=0; k<n; k++)
                mat[i][j][k] = new int[n];

            for(int i1=0; i1<n; i1++)
                for(int i2=0; i2<n; i2++)
                    mat[i][j][i1][i2] = 0;
            mat[i][j][i][j] = 1;

            th[i][j] = thread(back, i*n+j, 1, i, j, mat[i][j]);
        }

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            th[i][j].join();

    cout<<"There are "<<nr_sol<<" solutions.\n";

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            for(int k=0; k<n; k++)
                delete[] mat[i][j][k];
            delete[] mat[i][j];
        }cin.get();
    cin.get();

    return 0;
}

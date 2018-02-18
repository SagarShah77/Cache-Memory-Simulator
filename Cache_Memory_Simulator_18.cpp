#include<iostream>
#include<fstream>
#include<cstdlib>

#define N 9

using namespace std;

int lru[500][20];

//Function to change the tag order in the lru algo
int bringtotop(int set, int assoc, int x)
{
    int i, pos;
    for(i = 0;i < assoc;i++)
        if(lru[set][i] == x)
            pos = i;
    for(i = pos;i < assoc-1;i++)
        lru[set][i] = lru[set][i + 1];
    lru[set][assoc - 1] = x;
}

void plot(int Total_18, int Hit_18, int Miss_18);
long int changebase(char hex[], int Base_18);
int convert(char);

int main()
{
 int Main_Memory_18, Cache_Size_18, Cache_Placement_18, Associativity_18, Block_Size_18, i, j, Number_Of_Blocks_18, Base_18, Write_Policy_18, r, alg, x, pos;
 long int Address_18;
 float Hit_Rate_18, Miss_Rate_18;
 char hex[20], Tracefile_18[20];
 int Number_Of_Set_18;
 int Check_18=0, Hit_18=0, Miss_18=0;
 int Sum_18=0;
 int A_Vector_18[9] = {0, 1, 1, 4, 2, 6, 8, 1, 8},
	 B_Vector_18[9] = {2, 3, 3, 6, 4, 8, 0, 3, 0};
	 
 cout<<"\nVALUE OF A VECTOR : {0, 1, 1, 4, 2, 6, 8, 1, 8}\n";
 
 cout<<"\nVALUE OF B VECTOR : {2, 3, 3, 6, 4, 8, 0, 3, 0}\n";
 
 cout<<"\nENTER THE MAIN MEMORY SIZE : \n ";
 cin>>Main_Memory_18;
 
 cout<<"\nENTER THE CACHE MEMORY SIZE : \n ";
 cin>>Cache_Size_18;
 
 cout<<"\nENTER THE BLOCK SIZE : \n ";
 cin>>Block_Size_18;
 
 cout<<"\nENTER THE CACHE PLACEMENT ALGORITHM : 1. FOR DIRECT MAPPED   2. FOR SET-ASSOCIATIVE \n ";
 cin>>Cache_Placement_18;

 cout<<"\nENTER THE SET ASSOCIATIVITY : \n ";
 cin>>Associativity_18;

 cout<<"\nENTER TRACE FILE NAME : \n ";
 cin>>Tracefile_18;

 cout<<"\nENTER THE BASE OF NUMBER IN TRACE FILE : \n ";
 cin>>Base_18;

 cout<<"\nENTER THE CACHE REPLACEMENT ALGORITHM : \n1. FIFO  2.LRU  3. RANDOM \n ";
 cin>>alg;
 
 cout<<"\nENTER THE WRITE POLICY : \n1. WRITE THROUGH  2.WRITE BACK  3. WRITE ONCE \n ";
 cin>>Write_Policy_18;

 Number_Of_Blocks_18 = Cache_Size_18 / Block_Size_18;
 Number_Of_Set_18 = Cache_Size_18 / (Associativity_18 * Block_Size_18);

 for(int i = 0; i <= N; i++)
  	Sum_18 += A_Vector_18[i] * B_Vector_18[i];
  	
 int cache[Number_Of_Set_18][Associativity_18];
 
 for(i = 0;i < Number_Of_Set_18;i++)
  for(j =0;j < Associativity_18;j++)
   cache[i][j] = -10; // Eliminating all garbage values in in the cache...

 int fifo[Number_Of_Set_18];
 for(i = 0;i < Number_Of_Set_18;i++)
  fifo[i] = 0;

    for(i = 0;i < Number_Of_Set_18;i++)
        for(j =0;j < Associativity_18;j++)
            lru[i][j] = j;

 ifstream infile;
 infile.open(Tracefile_18,ios::in);
 if(!infile)
 {
     cout<<"Error! File not found...";
     exit(0);
 }
 
 int set, tag, found;
 while(!infile.eof()) //Reading each address from trace file
 {

        if(Base_18 != 10)
        {
            infile >> hex;
            Address_18 = changebase(hex, Base_18);
        }
        else
            infile >> Address_18;

  set = (Address_18 / Block_Size_18) % Number_Of_Set_18;
  tag = Address_18 / (Block_Size_18 * Number_Of_Set_18);


  Check_18++;
  found = 0;
  for(i = 0;i < Associativity_18;i++)
   if(cache[set][i] == tag)
    {
        found = 1;
        pos = i;
    }

  if(found)
  {
      Hit_18++;
      if(alg == 2)
      {
                bringtotop(set, Associativity_18, pos);
      }
  }

  else
  {
            if(alg == 1)
            {
             i = fifo[set];

   			 cache[set][i] = tag;
   			 fifo[set]++;

   			 if(fifo[set] == Associativity_18)
    		 fifo[set] = 0;

            }
            else if(alg == 2)
            {
                i = lru[set][0];
                cache[set][i] = tag;
                bringtotop(set, Associativity_18, i);
            }
            else
            {
                r = rand() % Associativity_18;
                cache[set][r] = tag;

            }

  }

 }
 
 infile.close();
 system("clear");
 cout<<"\nNUMBER OF CHECKS : "<<Check_18;
 cout<<"\nNUMBER OF HITS : "<<Hit_18;
 cout<<"\nNUMBER OF MISSES : "<<Check_18 - Hit_18;
 Hit_Rate_18 = float(Hit_18) / float(Check_18);
 Miss_Rate_18 = float(Check_18 - Hit_18) / float(Hit_18);
 cout<<"\nHit Rate : "<<Hit_Rate_18;
 cout<<"\nMiss Rate : "<<Miss_Rate_18;
 cout<<"\nFINAL DOT PRODUCT OF TWO VECTOR IS : "<<Sum_18;
 plot(Check_18,Hit_18, Check_18-Hit_18);
    
 return 0;

}


int convert(char c)
{
    if(c == '1')
        return 1;

    else if(c == '2')
        return 2;

    else if(c == '3')
        return 3;

    else if(c == '4')
        return 4;

    else if(c =='5')
        return 5;

    else if(c == '6')
        return 6;

    else if(c == '7')
        return 7;

    else if(c == '8')
        return 8;

    else if(c == '9')
        return 9;

    else if(c == '0')
        return 0;

    else if( (c == 'a') || (c == 'A') )
        return 10;

    else if( (c == 'b') || (c == 'B') )
        return 11;

    else if( (c == 'c') || (c == 'C') )
        return 12;

    else if( (c == 'd') || (c == 'D') )
        return 13;

    else if( (c == 'e') || (c == 'E') )
        return 14;

    else if( (c == 'f') || (c == 'F') )
        return 15;

    else
        return 0;

}

//Function to change the Base of a number system to Decimal
long int changebase(char hex[], int Base_18)
{
    int pow = 1, len, i, j;
    char temp;
    long int dec;
    
    for(len = 0;hex[len] != '\0';len++);

    for(i = 0,j = (len - 1);i < j;i++,j--)
    {
        temp = hex[i];
        hex[i] = hex[j];
        hex[j] = temp;
    }

    pow = 1;
    dec = 0;
    for(i = 0;i < len;i++)
    {
        if(convert(hex[i] == -1))
        {
            dec = 0;
            break;
        }
        dec = dec + (pow* convert(hex[i]));
        pow*= Base_18;

    }
    return dec;

}


//Function to plot a graph...
void plot(int Total_18, int Hit_18, int Miss_18)
{

    cout<<"\n\n\n\n\t*********************HIT AND MISS RESULT THROUGH GRAPH***********************\n\n";

    int Hit_Limit_18, Miss_Limit_18, i;
    Hit_Limit_18 = (float (Hit_18) / Total_18) * 30;
    Miss_Limit_18 = (float(Miss_18) / Total_18) * 30;

    cout<<"\n\t^";
    cout<<"\n\t|\n";
    for(i = 30;i >= 0;i--)
    {
        cout<<"\t";
        cout<<"|";
        cout<<"\t\t";

        //Total hit bar
        cout<<"|";
        if(i == 30)
            cout<<"----";
        else
            cout<<"    ";
        cout<<"|";

        cout<<"\t\t";

        //Hit Bar...
        if(i <= Hit_Limit_18)
            cout<<"|";
        else
            cout<<" ";

        if(i == Hit_Limit_18)
            cout<<"----";
        else
            cout<<"    ";

        if(i <= Hit_Limit_18)
            cout<<"|";
        else
            cout<<" ";
         cout<<"\t\t";
      
	    //Miss Bar...
        if(i <= Miss_Limit_18)
            cout<<"|";
        else
            cout<<" ";

        if(i == Miss_Limit_18)
            cout<<"----";
        else
            cout<<"    ";

        if(i <= Miss_Limit_18)
            cout<<"|";
        else
            cout<<" ";

        cout<<"\n";

    }
    cout<<"\t------------------------------------------------------------------------------>";
    cout<<"\n\t\t\tTotal\t\t Hits\t\tMisses\n";
    cout<<"\t--------------------------SAGAR_SHAH_011426818-------------------------------->\n\n\n";

}


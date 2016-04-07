#include "BST.h"
#include  "AVL.h"
using namespace std;
#include <stdlib.h>
#include <iostream>
#include <fstream>


/*void shuffleArray( int a[], int size)
{
   int rand_num, temp, last;
   

   for (last = size; last > 1; last--)
   {
      rand_num = rand() % last;
      temp = a[rand_num];
      a[rand_num] = a[last - 1];
      a[last - 1] = temp;
   }

}


int main()
{
	AVL *avl = new AVL();    
	BST * bst = new BST();         
	        

	clock_t beginTime;

	ofstream file;     
	file.open("testing.txt");
	file << "Run Times for avl and bst\n";



	file << "1st test: inserting numbers in increasing order up to 10,000 \n";
	for(int n = 1000; n <=10000; n+=1000){
		file << "N = " << n << endl;

        // BST
		file << "Binary Search Tree: ";
		beginTime = clock();
		for(int i = 0; i < n; i++)
			bst->insert(i);
		for(int i = 0; i < n; i++)
			bst->access(i);
		for(int i = 0; i < n; i++)
			bst->delete_value(i);
	    file << double( clock() - beginTime ) / (double)CLOCKS_PER_SEC << " seconds \n";

	    // AVL                                                                                                                                                                    
        file << "AVL Tree: ";
        beginTime = clock();
        for(int i = 0 ; i < n ; i++)
            avl->insert(i);
        for(int i = 0 ; i < n ; i++)
            avl->access(i);
        for(int i = 0 ; i < n ; i++)
            avl->delete_value(i);
        file << double( clock() - beginTime ) / (double)CLOCKS_PER_SEC << " seconds \n";

       
	}


    file << "2nd test: inserting numbers in increasing order and deleting them in the reverse order";
    for(int n = 1000; n <= 10000; n+= 1000)
    {
        file << "N = " << n << "\n";
                                                                                                                                                                
        file << "Binary Search Tree: ";                                                                                                                                                       
        beginTime = clock();                                                                                                                      
        for(int i = 0; i < n ; i++)
            bst->insert(i);                                                                                                       
        for(int i = n - 1; i >= 0 ; i--)
            bst->access(i);                                                                                                   
        for(int i = n - 1; i >= 0 ; i--)
            bst->delete_value(i);                                                                                                                                         
        file << double( clock() - beginTime ) / (double)CLOCKS_PER_SEC << " seconds \n";
		file << "\n";

        file << "AVL Tree: ";                                                                                                                                                      
        beginTime = clock();                                                                                                                      
        for(int i = 0; i < n ; i++)
            avl->insert(i);                                                                                                      
        for(int i = n - 1; i >= 0 ; i--)
            avl->access(i);                                                                                                     
        for(int i = n - 1; i >= 0 ; i--)
            avl->delete_value(i);                                                                                                                                          
        file << double( clock() - beginTime ) / (double)CLOCKS_PER_SEC << " seconds \n";
		file << "\n";

    } 



    file << "3rd test: inserting numbers in rand_numom order and deleting the in rand_numom order";
    for(int n = 1000; n <= 10000; n+=1000){
        file << "N = " << n << "\n";

        // create array of #s from 0 to n-1                               
        int insertArray[n];
        for(int i = 0 ; i < n ; i++)
            insertArray[i] = i;                    
        shuffleArray(insertArray, n);
                                                                     
        file << "bst/n ";                                                         
        beginTime = clock();                        
        for(int i = 0; i < n ; i++)
            bst->insert(insertArray[i]);                          
        for(int i = 0; i < n ; i++)
            bst->access(insertArray[i]);
        for(int i = 0; i < n ; i++)
            bst->delete_value(insertArray[i]);                                               
        file << double( clock() - beginTime ) / (double)CLOCKS_PER_SEC << " seconds \n";
		file << "\n";

                                                                        
        file << "AVL Tree: ";
        beginTime = clock();                         
        for(int i = 0 ; i < n ; i++)
            avl->insert(insertArray[i]);                       
        for(int i = 0 ; i < n ; i++)
            avl->access(insertArray[i]);                        
        for(int i = 0 ; i < n ; i++)
            avl->delete_value(insertArray[i]);
        file << double( clock() - beginTime ) / (double)CLOCKS_PER_SEC << " seconds \n";
		file << "\n";

       
    }

    file.close();
    ifstream ifile("testing.txt", ifstream::in);
    string l;
    while(!ifile.eof())
    {
        getline(ifile,l);
        cout << l << endl;
    }
    ifile.close();
}*/

void shuffleArray( int a[], int size)
{
   int temporary;
   int randomNum;
   int last;

   for (last = size; last > 1; last--)
   {
      randomNum = rand() % last;
      temporary = a[randomNum];
      a[randomNum] = a[last - 1];
      a[last - 1] = temporary;
   }

}


int main()
{
	BST * bst = new BST();         // create BST
	AVL *avl = new AVL();          // create AVL
	

	clock_t beginTime;

	ofstream file;     
	file.open("testing.txt");
	file << "Run Times for BST, AVL, and Splay Tree: \n";



	file << "1st test: inserting numbers in increasing order up to 10,000 \n";
	for(int n = 1000; n <=10000; n+=1000){
		file << "N = " << n << endl;

        // BST
		file << "Binary Search Tree: ";
		beginTime = clock();
		for(int i = 0; i < n; i++)
			bst->insert(i);
		for(int i = 0; i < n; i++)
			bst->access(i);
		for(int i = 0; i < n; i++)
			bst->delete_value(i);
	    file << double( clock() - beginTime ) / (double)CLOCKS_PER_SEC << " seconds \n";

	    // AVL                                                                                                                                                                    
        file << "AVL Tree: ";
        beginTime = clock();
        for(int i = 0 ; i < n ; i++)
            avl->insert(i);
        for(int i = 0 ; i < n ; i++)
            avl->access(i);
        for(int i = 0 ; i < n ; i++)
            avl->delete_value(i);
        file << double( clock() - beginTime ) / (double)CLOCKS_PER_SEC << " seconds \n";

        
		
	}



    file << "2nd test: inserting numbers in increasing order and deleting them in the reverse order";
    for(int n = 1000; n <= 10000; n+= 1000)
    {
        file << "N = " << n << "\n";
                                                                                                                                                                
        file << "Binary Search Tree: ";                                                                                                                                                       
        beginTime = clock();                                                                                                                      
        for(int i = 0; i < n ; i++)
            bst->insert(i);                                                                                                       
        for(int i = n - 1; i >= 0 ; i--)
            bst->access(i);                                                                                                   
        for(int i = n - 1; i >= 0 ; i--)
            bst->delete_value(i);                                                                                                                                         
        file << double( clock() - beginTime ) / (double)CLOCKS_PER_SEC << " seconds \n";
		file << "\n";

        file << "AVL Tree: ";                                                                                                                                                      
        beginTime = clock();                                                                                                                      
        for(int i = 0; i < n ; i++)
            avl->insert(i);                                                                                                      
        for(int i = n - 1; i >= 0 ; i--)
            avl->access(i);                                                                                                     
        for(int i = n - 1; i >= 0 ; i--)
            avl->delete_value(i);                                                                                                                                          
        file << double( clock() - beginTime ) / (double)CLOCKS_PER_SEC << " seconds \n";
		file << "\n";

        
    }



    file << "3rd test: inserting numbers in random order and deleting the in random order";
    for(int n = 1000; n <= 10000; n+=1000){
        file << "N = " << n << "\n";

        // create array of #s from 0 to n-1                               
        int insertArray[n];
        for(int i = 0 ; i < n ; i++)
            insertArray[i] = i;                    
        shuffleArray(insertArray, n);
                                                                     
        file << "BST: ";                                                         
        beginTime = clock();                        
        for(int i = 0; i < n ; i++)
            bst->insert(insertArray[i]);                          
        for(int i = 0; i < n ; i++)
            bst->access(insertArray[i]);
        for(int i = 0; i < n ; i++)
            bst->delete_value(insertArray[i]);                                               
        file << double( clock() - beginTime ) / (double)CLOCKS_PER_SEC << " seconds \n";
		file << "\n";

                                                                        
        file << "AVL Tree: ";
        beginTime = clock();                         
        for(int i = 0 ; i < n ; i++)
            avl->insert(insertArray[i]);                       
        for(int i = 0 ; i < n ; i++)
            avl->access(insertArray[i]);                        
        for(int i = 0 ; i < n ; i++)
            avl->delete_value(insertArray[i]);
        file << double( clock() - beginTime ) / (double)CLOCKS_PER_SEC << " seconds \n";
		file << "\n";

                                                                     
        
    }

    file.close();
    ifstream ifile("testing.txt", ifstream::in);
    string l;
    while(!ifile.eof())
    {
        getline(ifile,l);
        cout << l << endl;
    }
    ifile.close();
}




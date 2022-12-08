//Seoyoon Park
//CECS 325-01
//Prog 7 - Memory Manager
//12/07/2022
//
//I certify that this program is my own original work. I did not copy any part of this program from
//any other source. I further certify that I typed each and every line of code in this program.
#include "MemoryManager.h"

#include <iomanip>
#include <iostream>
using namespace std;

namespace MemoryManager
{
	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT 
	//
	// This is the only static memory that you may use, no other global variables may be
	// created, if you need to save data make it fit in MM_pool
	//
	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT


	const int MM_POOL_SIZE = 65536;
	char MM_pool[MM_POOL_SIZE];

	// I have provided this tool for your use
	void memView(int start, int end)
	{

		const unsigned int SHIFT = 8;
		const unsigned int MASK = 1 << SHIFT - 1;

		unsigned int value;	// used to facilitate bit shifting and masking

		cout << endl; // start on a new line
		cout << "               Pool                     Unsignd  Unsigned " << endl;
		cout << "Mem Add        indx   bits   chr ASCII#  short      int    " << endl;
		cout << "-------------- ---- -------- --- ------ ------- ------------" << endl;

		for (int i = start; i <= end; i++)
		{
			cout << (long*)(MM_pool + i) << ':';	// the actual address in hexadecimal
			cout << '[' << setw(2) << i << ']';				// the index into MM_pool

			value = MM_pool[i];
			cout << " ";
			for (int j = 1; j <= SHIFT; j++)		// the bit sequence for this byte (8 bits)
			{
				cout << ((value & MASK) ? '1' : '0');
				value <<= 1;
			}
			cout << " ";

            if (MM_pool[i] < 32)   // non-printable character so print a blank
            	cout << '|' << ' ' << "| (";	
            else                    // characger is printable so print it
				cout << '|' << *(char*)(MM_pool + i) << "| (";		// the ASCII character of the 8 bits (1 byte)

			cout << setw(4) << ((int)(*((unsigned char*)(MM_pool + i)))) << ")";	// the ASCII number of the character

			cout << " (" << setw(5) << (*(unsigned short*)(MM_pool + i)) << ")";	// the unsigned short value of 16 bits (2 bytes)
			cout << " (" << setw(10) << (*(unsigned int*)(MM_pool + i)) << ")";	// the unsigned int value of 32 bits (4 bytes)

																				//  cout << (*(unsigned int*)(MM_pool+i)) << "|";	// the unsigned int value of 32 bits (4 bytes)

			cout << endl;
		}
	}

	// Initialize set up any data needed to manage the memory pool
	void initializeMemoryManager(void)
	{

		int freeHead = 0; // starting index of the freelist
		int inUseHead = 2; // starting index of the inUselist
		int usedHead = 4; // starting index for the used list - deallocated memory

		int nextLink = 2; // offset index of the next link
		int prevLink = 4; // offset index for the prev link

		*(unsigned short*)(MM_pool + freeHead) = 6; // freelist starts at byte 6
		*(unsigned short*)(MM_pool + inUseHead) = 0;	// nothing in the inUse list yet
		*(unsigned short*)(MM_pool + usedHead) = 0; // nothing in the used list yet

	}

	// return a pointer inside the memory pool
	void* allocate(int aSize)
	{
		// If no chunk can accommodate aSize call onOutOfMemory()
		if ((int)(*(unsigned short*)(MM_pool)) + aSize + 6 > 65536)
			onOutOfMemory();

		// TBD
		int addressIndex = *(unsigned short*)(MM_pool);
		(*(unsigned short*)(MM_pool + addressIndex)) = aSize;
		(*(unsigned short*)(MM_pool + addressIndex + 2))
			= (*(unsigned short*)(MM_pool + 2));
		(*(unsigned short*)(MM_pool + addressIndex + 4)) = 0;

		(*(unsigned short*)(MM_pool + 2)) = addressIndex;
		(*(unsigned short*)(MM_pool)) += aSize + 6;
		
		if (addressIndex != 6) {
			(*(unsigned short*)(MM_pool + (*(unsigned short*)(MM_pool + addressIndex + 2)) + 4))
				= (*(unsigned short*)(MM_pool + 2));
		}
		return (void*)(MM_pool + (addressIndex + 6));

	}

	// Free up a chunk previously allocated
	void deallocate(void* aPointer)
	{
		int prev = *(unsigned short*)((char*)aPointer - 2);
		int next = *(unsigned short*)((char*)aPointer - 4);
		int addressIndex = *(unsigned short*)(MM_pool + prev +2);
		*(unsigned short*)(MM_pool + prev + 2) = *(unsigned short*)(MM_pool + addressIndex + 2);
		//
	}

	int size(void *ptr)
	{
		int prev = *(unsigned short*)((char*)ptr - 2);
		int addressIndex = *(unsigned short*)(MM_pool + prev + 2);

		return inUseMemory() - addressIndex;
	}
	
	//---
	//--- support routines
	//--- 

	// Will scan the memory pool and return the total free space remaining
	int freeMemory(void)
	{
		int num = MM_POOL_SIZE - (*(unsigned short*)(MM_pool));
		return num;
	}


	// Will scan the memory pool and return the total used memory - memory that has been deallocated
	int usedMemory(void)
	{
		int num = 0;
		int next = 0;
		int addressIndex = (*(unsigned short*)((char*)MM_pool + 4));
		if (addressIndex != 0) {
			next = (*(unsigned short*)((char*)MM_pool + 4));
		}
		while (next != 0) {
			addressIndex = next;
			next = (*(unsigned short*)((char*)MM_pool + addressIndex + 2));
			num += (*(unsigned short*)((char*)MM_pool + addressIndex)) + 6;
		}
		return num;
	}

	// Will scan the memory pool and return the total in use memory - memory being curretnly used
	int inUseMemory(void)
	{
		int num = 0;
		int next = 0;
		int addressIndex = (*(unsigned short*)((char*)MM_pool + 2));
		if (addressIndex != 0) {
			next = (*(unsigned short*)((char*)MM_pool + 2));
		}
		while (next != 0) {
			addressIndex = next;
			next = (*(unsigned short*)((char*)MM_pool + addressIndex + 2));
			num += (*(unsigned short*)((char*)MM_pool + addressIndex)) + 6;
		}
		return num;
	}

	// helper function to see teh InUse list in memory
	void traverseInUse()
	{
		int cur = *(unsigned short*)&MM_pool[2];
		int size = *(unsigned short*)&MM_pool[cur];
		int next = *(unsigned short*)&MM_pool[cur+2];
		int prev = *(unsigned short*)&MM_pool[cur+4];
		cout << "\nTraversing InUse Memory....";
		cout << "\n      InUse Head:"<<cur;
		while (cur != 0)
		{
			cout << "\n        Index:"<<cur<<" Size:"<<size<<" Next:"<<next<<" Prev:"<<prev;
			cur = next;
			size = *(unsigned short*)&MM_pool[cur];
			next = *(unsigned short*)&MM_pool[cur+2];
			prev = *(unsigned short*)&MM_pool[cur+4];
		}
	}

	//Helper function to seet eh Used list in memory
	void traverseUsed()
	{
		int cur = *(unsigned short*)&MM_pool[4];
		int size = *(unsigned short*)&MM_pool[cur];
		int next = *(unsigned short*)&MM_pool[cur+2];
		int prev = *(unsigned short*)&MM_pool[cur+4];
		cout << "\nTraversing Used Memory....";
		cout << "\n      Used Head:"<<cur;
		while (cur != 0)
		{
			cout << "\n        Index:"<<cur<<" Size:"<<size<<" Next:"<<next<<" Prev:"<<prev;
			cur = next;
			size = *(unsigned short*)&MM_pool[cur];
			next = *(unsigned short*)&MM_pool[cur+2];
			prev = *(unsigned short*)&MM_pool[cur+4];
		}
		
	}


	// this is called from Allocate if there is no more memory availalbe
	void onOutOfMemory(void)
  	{
    	std::cout << "\nMemory pool out of memory\n" << std::endl;
    	std::cout << "\n---Press \"Enter\" key to end program---:";

		cin.get();

    	exit( 1 );
  }
}

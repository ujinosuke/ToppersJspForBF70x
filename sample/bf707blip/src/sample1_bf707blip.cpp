/*****************************************************************************
 * sample1_bf707blip.cpp
 *****************************************************************************/

#include <sys/platform.h>
#include "adi_initialize.h"
#include "sample1_bf707blip.h"

//--- global functions

extern "C" void StartJspKernel(void);


/** 
 * If you want to use command program arguments, then place them in the following string. 
 */
char __argv_string[] = "";

int main(int argc, char *argv[])
{
	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
	
	/* Begin adding your custom code here */

	StartJspKernel();

	return 0;
}


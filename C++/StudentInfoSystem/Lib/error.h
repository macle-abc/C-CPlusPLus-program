#pragma once
#define error do \
				{	  \
						fprintf(stderr, "#Error in %s file, in %s function %ld\n", __FILE__, __FUNCTION__, __LINE__);	\
				}\
				while(0) 
			
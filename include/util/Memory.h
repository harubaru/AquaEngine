#ifndef AQUA2D_MEMORY_H
#define AQUA2D_MEMORY_H

#include <stdlib.h>

namespace Memory 
{
	template<typename T>
	void Delete(T t)
	{
		if(t == NULL) {
			return;
		} else {
			delete t;
			t = NULL;
		}
	}

	template<typename T>
	void ReleaseModule(T t)
	{
		if(t == NULL) {
			return;
		} else {
			t->Release();
			delete t;
			t = NULL;
		}
	}
}

#endif


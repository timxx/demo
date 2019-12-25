#include "common.h"

#ifdef _USING_ASAN

_ASAN_EXPORT const char* __asan_default_options()
{
	return "abort_on_error=1:detect_odr_violation=2:"
			"detect_stack_use_after_return=1:"
			"detect_leaks=1:alloc_dealloc_mismatch=1:"
			"check_initialization_order=1:strict_init_order=1";
}

#endif

struct GloalData
{
	GloalData()
	{
		n = 2020;
	}

	int n;
};

static GloalData g_data;

int globalData()
{
	return g_data.n;
}

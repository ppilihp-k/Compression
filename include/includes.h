#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <memory>
#include "emmintrin.h"
#include "immintrin.h"
#include <stdlib.h>
#include <assert.h>
#include <cstdlib>
#include <set>
#include <unordered_map>
#include <list>
#include <functional>
#include <string>
#include <memory>
#include <vector>

#define DEBUG 1
//#define SIMD 1

#ifdef LINUX
	
	#define aligned_alloc(x, y) (aligned_alloc(x, y))
	
	#define free(x) (free(x))
	
	#define cast64(x) (uint64_t(x))
	
	#define cast32(x) (uint32_t(x))
	
	#define cast128(x) (__uint128_t(x))
#else
	#include <malloc.h>
	
	#define aligned_alloc(x, y) (_aligned_malloc(y, x))
	
	#define free(x) (_aligned_free(x))
	
	#define cast64(x) (((uint64_t)x))
	
	#define cast32(x) (((uint32_t)x))
	
	#define cast128(x) (((__uint128_t)x))
#endif

#endif

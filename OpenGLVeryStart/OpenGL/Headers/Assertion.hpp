#pragma once
#include <cassert>

namespace Core::Debug
{
	#define assertion(expression) if(!(expression)) {assert(expression);} 
}
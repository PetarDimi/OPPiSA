#pragma once
#include "Types.h"
#include "InterferenceGraph.h"
#include "SimplificationStack.h"

#include <stack>

bool doResourceAllocation(SimplificationStack* simplificationStack, InterferenceGraph* interferenceGraph);

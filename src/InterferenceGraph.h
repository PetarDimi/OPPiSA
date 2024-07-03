#pragma once
#include "IR.h"

InterferenceGraph& doInterferenceGraph(Instructions* instructions, Variables* variables);

void printInterferenceGraph();
#include <stdio.h>
#include "simu_script.h"

int main(int argc, char ** argv)
{
	os::CommandLine	cmd(argc, argv);
	int ret = oxd::SimulatorMain(cmd);
	return ret;
}
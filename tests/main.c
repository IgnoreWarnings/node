/** Custom main() for Criterion
 *
 * @author Steffen Vogel <stvogel@eonerc.rwth-aachen.de>
 * @copyright 2014-2016, Institute for Automation of Complex Power Systems, EONERC
 *   This file is part of VILLASnode. All Rights Reserved. Proprietary and confidential.
 *   Unauthorized copying of this file, via any medium is strictly prohibited.
 *********************************************************************************/

#include <criterion/criterion.h>

#include <villas/log.h>
#include <villas/memory.h>

int main(int argc, char *argv[]) {
	struct criterion_test_set *tests = criterion_initialize();
	
	info("Initialize memory system");
	memory_init();

	int result = 0;
	if (criterion_handle_args(argc, argv, true))
		result = !criterion_run_all_tests(tests);

	criterion_finalize(tests);
	return result;
}
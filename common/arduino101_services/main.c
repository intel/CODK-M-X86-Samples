/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <zephyr.h>
#include "main.h"


/* size of stack area used by each thread */
#define MAIN_STACKSIZE      2048
#define SKETCH_STACKSIZE    2048



/* scheduling priority used by each thread */
#define PRIORITY 7
#define TASK_PRIORITY 8

char __noinit __stack sketch_stack_area[SKETCH_STACKSIZE];

void threadMain(void *dummy1, void *dummy2, void *dummy3)
{
	
	// start ARC core
	/** Uncomment this lines if you want to start the ARC core
	uint32_t *reset_vector;
	reset_vector = (uint32_t *)RESET_VECTOR;
	start_arc(*reset_vector);
	**/
	
	k_thread_spawn(sketch_stack_area, SKETCH_STACKSIZE, sketch, NULL, NULL,
			NULL, TASK_PRIORITY, 0, K_NO_WAIT);
	
}

K_THREAD_DEFINE(threadMain_id, MAIN_STACKSIZE, threadMain, NULL, NULL, NULL,
		PRIORITY, 0, K_NO_WAIT);


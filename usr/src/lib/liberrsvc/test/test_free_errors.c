/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright 2010 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#include <stdio.h>
#include <string.h>
#include <Python.h>

#include "../liberrsvc.h"

#define	REFCOUNT(o) (((PyObject *)o)->ob_refcnt)


/*
 * Test 5: es_free_errors
 */
boolean_t
test5(void)
{
	boolean_t	retval = B_FALSE;
	err_info_t	*rv1 = NULL;
	err_info_t	*rv2 = NULL;
	int		start_refcnt_1;
	err_info_list_t *list = NULL;
	err_info_list_t *item = NULL;
	int		count = 0;

	printf("\nTest 5: es_free_errors\n");
	rv1 = es_create_err_info("TD", ES_ERR);
	if (rv1 == NULL) {
		printf("test FAILED\n");
	} else {
		rv2 = es_create_err_info("TI", ES_CLEANUP_ERR);
		if (rv2 == NULL) {
			printf("test FAILED\n");
		}
	}

	if (rv2 != NULL) {
		/*
		 * The reference count returned is typically 1 higher than
		 * expected, due to iternal Python issues.
		 * For testing purposes, we will just confirm that the
		 * ref. count is correctly adjusted relative to the
		 * starting value.
		 */
		start_refcnt_1 = REFCOUNT(rv1);

		count = 0;

		list = es_get_all_errors();
		if (REFCOUNT(rv1) != (start_refcnt_1 + 1)) {
			printf("test FAILED\n");
			printf("ref count = [%d], should be [%d]\n",
			    REFCOUNT(rv1), (start_refcnt_1 + 1));
			es_free_err_info_list(list);
		} else {
			es_free_err_info_list(list);

			if (REFCOUNT(rv1) != start_refcnt_1) {
				printf("test FAILED\n");
				printf("ref count = [%d], should be [%d]\n",
				    REFCOUNT(rv1), start_refcnt_1);
			} else {
				es_free_errors();

				/*
				 * Confirm that calling es_free_errors
				 * decrements to 0 the reference count of
				 * an ErrorInfo object.
				 */
				if (REFCOUNT(rv1) != 0) {
					printf("test FAILED\n");
					printf("ref count = [%d], should be "
					    "[%d]\n", REFCOUNT(rv1), 0);
				} else {
					/*
					 * Confirm that after calling
					 * es_free_errors there are no
					 * ErrorInfo objects in the global
					 * list.
					 */
					count = 0;
					list = es_get_all_errors();
					item = list;

					while (item != NULL) {
						count++;
						item = item->ei_next;
					}

					if (count != 0) {
						printf("test FAILED\n");
					} else {
						printf("test PASSED\n");
						retval = B_TRUE;
					}

					es_free_err_info_list(list);
				}
			}
		}
	}

	es_free_errors();

	return (retval);
}

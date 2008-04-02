/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _LIBBE_H
#define _LIBBE_H

#include <libnvpair.h>
#include <libzfs.h>

#define	BE_ATTR_ORIG_BE_NAME	"orig_be_name"
#define	BE_ATTR_ORIG_BE_POOL	"orig_be_pool"
#define	BE_ATTR_SNAP_NAME	"snap_name"

#define	BE_ATTR_NEW_BE_NAME	"new_be_name"
#define	BE_ATTR_NEW_BE_POOL	"new_be_pool"
#define	BE_ATTR_NEW_BE_DESC	"new_be_desc"
#define	BE_ATTR_POLICY		"policy"
#define	BE_ATTR_ZFS_PROPERTIES	"zfs_properties"

#define	BE_ATTR_FS_NAMES	"fs_names"
#define	BE_ATTR_FS_NUM		"fs_num"
#define	BE_ATTR_SHARED_FS_NAMES	"shared_fs_names"
#define	BE_ATTR_SHARED_FS_NUM	"shared_fs_num"

#define	BE_ATTR_MOUNTPOINT	"mountpoint"
#define	BE_ATTR_MOUNT_FLAGS	"mount_flags"

/*
 * libbe error codes
 */
enum {
	BE_SUCCESS = 0,
	BE_ERR_ACCESS = 4000,	/* permission denied */
	BE_ERR_BUSY,		/* mount busy */
	BE_ERR_EXISTS,		/* BE exists */
	BE_ERR_INVAL,		/* invalid argument */
	BE_ERR_NAMETOOLONG, 	/* name > BUFSIZ */
	BE_ERR_NOENT,		/* No such BE */
	BE_ERR_NOMEM,		/* not enough memory */
	BE_ERR_PERM,		/* Not owner */
} be_errno_t;

/*
 * Data structures used to return the listing and information of BEs.
 */
typedef struct be_dataset_list {
	uint64_t	be_ds_space_used;
	boolean_t	be_ds_mounted;
	char		*be_dataset_name;
	time_t		be_ds_creation;	/* Date/time stamp when created */
	char		*be_ds_mntpt;
	char		*be_ds_plcy_type;	/* cleanup policy type */
	struct be_dataset_list	*be_next_dataset;
} be_dataset_list_t;

typedef struct be_snapshot_list {
	char	*be_snapshot_name;
	time_t	be_snapshot_creation;	/* Date/time stamp when created */
	char	*be_snapshot_type;		/* cleanup policy type */
	struct	be_snapshot_list *be_next_snapshot;
} be_snapshot_list_t;

typedef struct be_node_list {
	boolean_t be_mounted;		/* is BE currently mounted */
	boolean_t be_active_on_boot;	/* is this BE active on boot */
	boolean_t be_active;		/* is this BE active currently */
	uint64_t be_space_used;
	char *be_node_name;
	char *be_rpool;
	char *be_root_ds;
	char *be_mntpt;
	char *be_policy_type;		/* cleanup policy type */
	time_t	be_node_creation;	/* Date/time stamp when created */
	struct be_dataset_list *be_node_datasets;
	uint_t be_node_num_datasets;
	struct be_snapshot_list *be_node_snapshots;
	uint_t be_node_num_snapshots;
	struct be_node_list *be_next_node;
} be_node_list_t;

/* Flags used with mounting a BE */
#define	BE_MOUNT_FLAG_SHARED_FS		0x00000001
#define	BE_MOUNT_FLAG_SHARED_RW		0x00000010

/*
 * BE functions
 */
int be_init(nvlist_t *);
int be_destroy(nvlist_t *);
int be_copy(nvlist_t *);

int be_mount(nvlist_t *);
int be_unmount(nvlist_t *);

int be_rename(nvlist_t *);

int be_activate(nvlist_t *);

int be_create_snapshot(nvlist_t *);
int be_destroy_snapshot(nvlist_t *);
int be_rollback(nvlist_t *);

/*
 * Functions for listing and getting information about existing BEs.
 */
int be_list(char *, be_node_list_t **);
void be_free_list(be_node_list_t *);
int be_max_avail(char *, uint64_t *);

/* be_list.c - XXX temporary debug stuff*/
void be_list_print(be_node_list_t *);

#endif	/* _LIBBE_H */

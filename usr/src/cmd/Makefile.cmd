#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2007, 2010, Oracle and/or its affiliates. All rights reserved.
#
include $(SRC)/Makefile.master

FILEMODE = 0755

# Definitions of common installation directories
ROOTADMINBIN	= $(ROOT)/usr/snadm/bin
ROOTEXECATTR	= $(ROOT)/etc/security/exec_attr.d
ROOTLIBSVCMETHOD	= $(ROOT)/lib/svc/method
ROOTLIBSVCSHARE	= $(ROOT)/lib/svc/share
ROOTMANIFEST	= $(ROOTVAR)/svc/manifest
ROOTMANAPP	= $(ROOTMANIFEST)/application
ROOTMANSYS	= $(ROOTMANIFEST)/system
ROOTMANSYSFIL	= $(ROOTMANSYS)/filesystem
ROOTMANSYSSVC	= $(ROOTMANSYS)/svc
ROOTMANSYSINS	= $(ROOTMANSYS)/install
ROOTPROFATTR	= $(ROOT)/etc/security/prof_attr.d
ROOTUSRLIBINSTALLADM	= $(ROOT)/usr/lib/installadm
ROOTVARSADM	= $(ROOT)/var/sadm
ROOTVARINSTADM	= $(ROOT)/var/installadm
ROOTVARAIWEB	= $(ROOT)/var/installadm/ai-webserver
ROOTETCSVCPROFILE	= $(ROOT)/etc/svc/profile

# Derived installation rules
ROOTUSRBINPROG	= $(PROG:%=$(ROOTUSRBIN)/%)

ROOTUSRSBINFILES = $(FILES:%=$(ROOTUSRSBIN)/%)

ROOTSBINFILES	= $(FILES:%=$(ROOTSBIN)/%)

ROOTEXECATTRFILES	= $(EXECATTRFILES:exec_attr.%=$(ROOTEXECATTR)/%)
ROOTPROFATTRFILES	= $(PROFATTRFILES:prof_attr.%=$(ROOTPROFATTR)/%)

# Basic linkage macro
LDLIBS.cmd	= -L$(ROOTUSRLIB) -L$(ONLIBDIR) -L$(ONUSRLIBDIR)


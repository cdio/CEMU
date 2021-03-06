#
# Copyright (C) 2020 Claudio Castiglia
#
# This file is part of CEMU.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, see http://www.gnu.org/licenses/
#
ROOT=		${abspath ..}

BIN=		cemu

LN_BINS=	c64

CONFIG=		cemu.conf

DST_BIN=	${DST_BINDIR}/${BIN}

DST_LINKS=	${LN_BINS:%=${DST_BINDIR}/%}

DST_CONFIG=	${DST_SYSCONFDIR}/${CONFIG}

include ${ROOT}/mk/config.mk

CXXSRCS=	cemu_cmdline.cpp \
		c64_cmdline.cpp \
		c64_main.cpp \
		main.cpp

include ${ROOT}/mk/bin.mk

install: ${DST_LINKS} ${DST_CONFIG} ${DST_README}

${DST_LINKS}: ${DST_BIN}
	${LN} ${LN_FLAGS} $< $@

${DST_BIN}: ${BIN}
	[ -d ${dir $@} ] || ${INSTALL} -d -m ${MODE_BINDIR} -o ${OWNER_BINDIR} -g ${GROUP_BINDIR} ${dir $@}
	${INSTALL} -s -m ${MODE_BIN} -o ${OWNER_BIN} -g ${GROUP_BIN} ${notdir $@} $@

${DST_CONFIG}: ${CONFIG}
	[ -d ${dir $@} ] || ${INSTALL} -d -m ${MODE_DATADIR} -o ${OWNER_DATADIR} -g ${GROUP_DATADIR} ${dir $@}
	${INSTALL} -m ${MODE_DATA} -o ${OWNER_DATA} -g ${GROUP_DATA} ${notdir $@} $@

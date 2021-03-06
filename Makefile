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
ROOT=		${abspath .}

DIRS=		3rdparty \
		icons \
		lib \
		bin \
		bin/roms \
		bin/palette \
		bin/keymaps \
		images

NAME=		cemu-v${VERSION}

FMT=		tgz

PKG=		${NAME}.${FMT}

.PHONY: package

include ${ROOT}/mk/config.mk
include ${ROOT}/mk/dir.mk

package:
ifndef RELEASE
	@echo
	@echo "==> Please specify RELEASE=<branch>"
	@echo
	@exit 1
else
	${GIT} archive --format=${FMT} --prefix=${NAME}/ ${RELEASE} > ${PKG}
endif

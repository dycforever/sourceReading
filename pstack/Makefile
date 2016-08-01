#
# This file is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#

WHO := $(shell whoami)

pstack : pstack.c
	gcc -o pstack -Wall pstack.c

install : pstack
ifeq ($(WHO),root)
	chown root pstack
	chmod 755 pstack
	mv pstack /usr/local/bin
	cp -p man1/pstack.1 /usr/local/man/man1
	chmod -w /usr/local/man/man1/pstack.1
else
	@echo "you must be root to install pstack"
endif

uninstall :
ifeq ($(WHO),root)
	rm -f /usr/local/bin/pstack
	rm -f /usr/local/man/man1/pstack.1
else
	@echo "you must be root to uninstall pstack"
endif

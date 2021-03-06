/*
** cap.c - Capabilities file parsing stuff (termcap, /etc/remote etc...)
**
** Copyright (c) 2002 Peter Eriksson <pen@lysator.liu.se>
**
** This file is part of psmsd.
**
** psmsd is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** 
** psmsd is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with psmsd.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CAP_H
#define CAP_H

extern int
cap_getent(FILE *fp,
	   char *buf,
	   int bufsize);

extern char *
cap_getstr(const char *path,
	   const char *entname,
	   const char *strname,
	   char *buf,
	   int bufsize);

extern int
cap_getint(const char *path,
	   const char *entname,
	   const char *strname,
	   int *val);

#endif

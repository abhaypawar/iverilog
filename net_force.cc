/*
 * Copyright (c) 2000-2004 Stephen Williams (steve@picturel.com)
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */
#ifdef HAVE_CVS_IDENT
#ident "$Id: net_force.cc,v 1.13 2004/12/11 02:31:26 steve Exp $"
#endif

# include  "config.h"
# include  "compiler.h"

/*
 * This file contains implementation of the NetForce, NetRelease,
 * NetCAssign and NetDeassign classes. These are similar or related in
 * that they handle the procedural continuous assign and force
 * statements.
 */

# include  "netlist.h"
# include  <assert.h>


/*
 * $Log: net_force.cc,v $
 * Revision 1.13  2004/12/11 02:31:26  steve
 *  Rework of internals to carry vectors through nexus instead
 *  of single bits. Make the ivl, tgt-vvp and vvp initial changes
 *  down this path.
 *
 * Revision 1.12  2004/02/18 17:11:56  steve
 *  Use perm_strings for named langiage items.
 *
 * Revision 1.11  2003/03/06 00:28:41  steve
 *  All NetObj objects have lex_string base names.
 *
 * Revision 1.10  2003/01/27 05:09:17  steve
 *  Spelling fixes.
 *
 * Revision 1.9  2002/08/19 00:06:12  steve
 *  Allow release to handle removal of target net.
 *
 * Revision 1.8  2002/08/12 01:34:59  steve
 *  conditional ident string using autoconfig.
 *
 * Revision 1.7  2002/01/19 19:02:08  steve
 *  Pass back target errors processing conditionals.
 *
 * Revision 1.6  2001/11/14 03:28:49  steve
 *  DLL target support for force and release.
 *
 * Revision 1.5  2001/10/31 05:24:52  steve
 *  ivl_target support for assign/deassign.
 *
 * Revision 1.4  2001/10/28 01:14:53  steve
 *  NetObj constructor finally requires a scope.
 *
 * Revision 1.3  2001/07/25 03:10:49  steve
 *  Create a config.h.in file to hold all the config
 *  junk, and support gcc 3.0. (Stephan Boettcher)
 *
 * Revision 1.2  2000/05/12 01:22:41  steve
 *  NetCAssign needs to incr_eref its lval to lock it down.
 *
 * Revision 1.1  2000/05/11 23:37:27  steve
 *  Add support for procedural continuous assignment.
 *
 */


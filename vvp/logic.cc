/*
 * Copyright (c) 2001-2004 Stephen Williams (steve@icarus.com)
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
#ident "$Id: logic.cc,v 1.14 2004/12/11 02:31:29 steve Exp $"
#endif

# include  "logic.h"
# include  "compile.h"
# include  "bufif.h"
# include  "npmos.h"
# include  "statistics.h"
# include  <string.h>
# include  <assert.h>
# include  <stdlib.h>
#ifdef HAVE_MALLOC_H
# include  <malloc.h>
#endif


/*
 *   Implementation of the table functor, which provides logic with up
 *   to 4 inputs.
 */

table_functor_s::table_functor_s(truth_t t)
: table(t)
{
      count_functors_table += 1;
}

table_functor_s::~table_functor_s()
{
}

/*
 * The parser calls this function to create a logic functor. I allocate a
 * functor, and map the name to the vvp_ipoint_t address for the
 * functor. Also resolve the inputs to the functor.
 */

void compile_functor(char*label, char*type,
		     vvp_delay_t delay, unsigned ostr0, unsigned ostr1,
		     unsigned argc, struct symb_s*argv)
{
      table_functor_s* obj = 0;

      if (strcmp(type, "OR") == 0) {
	    obj = new table_functor_s(ft_OR);

      } else if (strcmp(type, "AND") == 0) {
	    obj = new table_functor_s(ft_AND);

      } else if (strcmp(type, "BUF") == 0) {
	    obj = new table_functor_s(ft_BUF);
#if 0
      } else if (strcmp(type, "BUFIF0") == 0) {
	    obj = new vvp_bufif_s(true,false, ostr0, ostr1);

      } else if (strcmp(type, "BUFIF1") == 0) {
	    obj = new vvp_bufif_s(false,false, ostr0, ostr1);
#endif
      } else if (strcmp(type, "BUFZ") == 0) {
	    obj = new table_functor_s(ft_BUFZ);
#if 0
      } else if (strcmp(type, "PMOS") == 0) {
	    obj = new vvp_pmos_s;

      } else if (strcmp(type, "NMOS") == 0) {
	    obj= new vvp_nmos_s;

      } else if (strcmp(type, "RPMOS") == 0) {
	    obj = new vvp_rpmos_s;

      } else if (strcmp(type, "RNMOS") == 0) {
	    obj = new vvp_rnmos_s;
#endif
      } else if (strcmp(type, "MUXX") == 0) {
	    obj = new table_functor_s(ft_MUXX);

      } else if (strcmp(type, "MUXZ") == 0) {
	    obj = new table_functor_s(ft_MUXZ);

      } else if (strcmp(type, "EEQ") == 0) {
	    obj = new table_functor_s(ft_EEQ);

      } else if (strcmp(type, "NAND") == 0) {
	    obj = new table_functor_s(ft_NAND);

      } else if (strcmp(type, "NOR") == 0) {
	    obj = new table_functor_s(ft_NOR);

      } else if (strcmp(type, "NOT") == 0) {
	    obj = new table_functor_s(ft_NOT);
#if 0
      } else if (strcmp(type, "NOTIF0") == 0) {
	    obj = new vvp_bufif_s(true,true, ostr0, ostr1);

      } else if (strcmp(type, "NOTIF1") == 0) {
	    obj = new vvp_bufif_s(false,true, ostr0, ostr1);
#endif
      } else if (strcmp(type, "XNOR") == 0) {
	    obj = new table_functor_s(ft_XNOR);

      } else if (strcmp(type, "XOR") == 0) {
	    obj = new table_functor_s(ft_XOR);

      } else {
	    yyerror("invalid functor type.");
	    free(type);
	    free(argv);
	    free(label);
	    return;
      }

      free(type);

      assert(argc <= 4);
      vvp_net_t*net = new vvp_net_t;

      define_functor_symbol(label, net);
      free(label);

      inputs_connect(net, argc, argv);
      free(argv);
}


/*
 * $Log: logic.cc,v $
 * Revision 1.14  2004/12/11 02:31:29  steve
 *  Rework of internals to carry vectors through nexus instead
 *  of single bits. Make the ivl, tgt-vvp and vvp initial changes
 *  down this path.
 *
 */


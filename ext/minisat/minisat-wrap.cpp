/******************************************************************************

  ruby-minisat -- ruby binding for MiniSat

*******************************************************************************

The MIT License

Copyright (c) 2007 Yusuke Endoh

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

******************************************************************************/


#ifdef HAVE_MINISAT_CORE_SOLVER_H
#include "minisat/core/Solver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/mtl/Alloc.h"
#include "minisat/mtl/IntTypes.h"
#include "minisat/mtl/Alg.h"
#include "minisat/mtl/Vec.h"
#include "minisat/mtl/Map.h"
#else
#include "core/Solver.h"
#include "core/SolverTypes.h"
#include "mtl/Alloc.h"
#include "mtl/IntTypes.h"
#include "mtl/Alg.h"
#include "mtl/Vec.h"
#include "mtl/Map.h"
#endif
#include "minisat.h"
#include <iostream>
using namespace Minisat;



/***** variable **************************************************************/

extern "C" int wrap_lit_pos_var(int v) {
    return toInt(mkLit(v, false));
}

extern "C" int wrap_lit_neg_var(int v) {
    return toInt(mkLit(v, true));
}

/***** solver ****************************************************************/

extern "C" wrap_solver wrap_solver_new() {
    return (wrap_solver) new Solver();
}

extern "C" void wrap_solver_free(wrap_solver slv) {
    delete (Solver*) slv;
}

extern "C" int wrap_solver_new_var(wrap_solver slv) {
    return ((Solver*) slv)->newVar();
}

extern "C" int wrap_solver_add_clause(wrap_solver slv, int *lits, int len) {
    vec<Lit> lit_vec;
    for(int i = 0; i < len; i++) lit_vec.push(toLit(lits[i]));
    ((Solver*) slv)->addClause(lit_vec);
    return ((Solver*) slv)->okay() ? 1 : 0;
}

extern "C" int wrap_solver_ref_var(wrap_solver slv, int var) {
    lbool b = ((Solver*) slv)->model[var];
    return (b == l_False) ? 0 : (b == l_True) ? 1 : 2;
}

extern "C" int wrap_solver_solve(wrap_solver slv, int *lits, int len) {
    vec<Lit> lit_vec;
    for(int i = 0; i < len; i++) lit_vec.push(toLit(lits[i]));
    return ((Solver*) slv)->solve(lit_vec) ? 1 : 0;
}

extern "C" int wrap_solver_simplify(wrap_solver slv) {
    ((Solver*) slv)->simplify();
    return ((Solver*) slv)->okay() ? 1 : 0;
}

extern "C" int wrap_solver_var_size(wrap_solver slv) {
    return ((Solver*) slv)->nVars();
}

extern "C" int wrap_solver_clause_size(wrap_solver slv) {
    return ((Solver*) slv)->nClauses();
}

extern "C" int wrap_solver_trail(wrap_solver slv) {
    return (((Solver*) slv)->trail).size();
}

extern "C" int wrap_solver_trail_lim(wrap_solver slv,int index) {
    return (((Solver*) slv)->trail_lim)[index];
}
extern "C" int wrap_solver_trail_lim_size(wrap_solver slv) {
    return (((Solver*) slv)->trail_lim).size();
}

extern "C" int wrap_solver_vardata_size(wrap_solver slv) {
    return (((Solver*) slv)->vardata).size();
}
extern "C" uint32_t wrap_solver_vardata_elem_size(wrap_solver slv,int index) {
    return (((Solver*) slv)->vardata)[index].reason;
}
extern "C" uint32_t wrap_solver_vardata_elem_wasted(wrap_solver slv,int index) {
    return (((Solver*) slv)->vardata)[index].reason;
}
extern "C" int wrap_solver_vardata_elem_level(wrap_solver slv,int index) {
    return (((Solver*) slv)->vardata)[index].level;
}
extern "C" uint32_t wrap_solver_vardata_elem_index(wrap_solver slv,int index, int ind) {
    CRef reason = (((Solver*) slv)->vardata)[index].reason;
    return reason;
}

extern "C" int wrap_solver_qhead(wrap_solver slv) {
    return ((Solver*) slv)->qhead;
}

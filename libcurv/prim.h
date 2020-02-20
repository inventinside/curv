// Copyright 2016-2020 Doug Moen
// Licensed under the Apache License, version 2.0
// See accompanying file LICENSE or https://www.apache.org/licenses/LICENSE-2.0

#ifndef LIBCURV_PRIM_H
#define LIBCURV_PRIM_H

// Curv primitive operations which are implemented using the Prim framework.

#include <libcurv/array_op.h>
#include <cmath>

namespace curv {

struct Add_Prim : public Binary_Num_SCMat_Prim
{
    static const char* name() {return "+";};
    static Value zero() { return {0.0}; }
    static Value call(double x, double y, const Context&) { return {x + y}; }
    static SC_Value sc_call(SC_Frame& f, SC_Value x, SC_Value y)
        { return sc_binop(f, x.type, x, "+", y); }
};
using Add_Op = Binary_Array_Op<Add_Prim>;
using Add_Expr = Infix_Op_Expr<Add_Op>;

struct Multiply_Prim : public Binary_Num_SCMat_Prim
{
    static const char* name() { return "*"; }
    static Value zero() { return {1.0}; }
    static Value call(double x, double y, const Context&) { return {x * y}; }
    static SC_Value sc_call(SC_Frame& f, SC_Value x, SC_Value y) {
        if (x.type.is_mat() && y.type.is_mat())
            return sc_bincall(f, x.type, "matrixCompMult", x, y);
        else
            return sc_binop(f, x.type, x, "*", y);
    }
};
using Multiply_Op = Binary_Array_Op<Multiply_Prim>;
using Multiply_Expr = Infix_Op_Expr<Multiply_Op>;

struct Subtract_Prim : public Binary_Num_SCMat_Prim
{
    static const char* name() {return "-";};
    static Value call(double x, double y, const Context&) { return {x - y}; }
    static SC_Value sc_call(SC_Frame& f, SC_Value x, SC_Value y)
        { return sc_binop(f, x.type, x, "-", y); }
};
using Subtract_Op = Binary_Array_Op<Subtract_Prim>;
using Subtract_Expr = Infix_Op_Expr<Subtract_Op>;

struct Divide_Prim : public Binary_Num_SCMat_Prim
{
    static const char* name() {return "/";};
    static Value call(double x, double y, const Context&) { return {x / y}; }
    static SC_Value sc_call(SC_Frame& f, SC_Value x, SC_Value y)
        { return sc_binop(f, x.type, x, "/", y); }
};
using Divide_Op = Binary_Array_Op<Divide_Prim>;
using Divide_Expr = Infix_Op_Expr<Divide_Op>;

struct Power_Prim : public Binary_Num_SCVec_Prim
{
    static const char* name() {return "^";};
    static Value call(double x, double y, const Context&) { return {pow(x,y)}; }
    static SC_Value sc_call(SC_Frame& f, SC_Value x, SC_Value y)
        { return sc_bincall(f, x.type, "pow", x, y); }
};
using Power_Op = Binary_Array_Op<Power_Prim>;
using Power_Expr = Infix_Op_Expr<Power_Op>;

} // namespace
#endif // header guard
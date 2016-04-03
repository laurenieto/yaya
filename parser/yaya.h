/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_YAYA_TAB_H_INCLUDED
# define YY_YY_YAYA_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tPRINTF = 258,
    tMAIN = 259,
    tCST = 260,
    tINT = 261,
    tRET = 262,
    tID = 263,
    tNB = 264,
    tPV = 265,
    tV = 266,
    tPO = 267,
    tPF = 268,
    tAO = 269,
    tAF = 270,
    tTEXT = 271,
    tG = 272,
    tOU = 273,
    tET = 274,
    tEG = 275,
    tPLUSPLUS = 276,
    tMOINSMOINS = 277,
    tWHILE = 278,
    tIF = 279,
    tERROR = 280,
    tNOT = 281,
    tAND = 282,
    tOR = 283,
    tINFEG = 284,
    tSUPEG = 285,
    tINF = 286,
    tSUP = 287,
    tEGEG = 288,
    tNOTEG = 289,
    tPLUS = 290,
    tMOINS = 291,
    tFOIS = 292,
    tDIV = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 28 "parser/yaya.y" /* yacc.c:1909  */
int nb; char * str;

#line 96 "yaya.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YAYA_TAB_H_INCLUDED  */

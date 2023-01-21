/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    DB = 258,
    FIND = 259,
    INSERT = 260,
    DELETE = 261,
    UPDATE = 262,
    PARENT = 263,
    STRING = 264,
    SET = 265,
    OR = 266,
    LT = 267,
    LET = 268,
    GT = 269,
    GET = 270,
    NE = 271,
    OPBRACE = 272,
    CLBRACE = 273,
    OPCBRACE = 274,
    CLCBRACE = 275,
    OPSQBRACE = 276,
    CLSQBRACE = 277,
    COLON = 278,
    DOLLAR = 279,
    COMMA = 280,
    QUOTE = 281,
    FALSE = 282,
    TRUE = 283,
    INT_NUMBER = 284,
    FLOAT_NUMBER = 285
  };
#endif
/* Tokens.  */
#define DB 258
#define FIND 259
#define INSERT 260
#define DELETE 261
#define UPDATE 262
#define PARENT 263
#define STRING 264
#define SET 265
#define OR 266
#define LT 267
#define LET 268
#define GT 269
#define GET 270
#define NE 271
#define OPBRACE 272
#define CLBRACE 273
#define OPCBRACE 274
#define CLCBRACE 275
#define OPSQBRACE 276
#define CLSQBRACE 277
#define COLON 278
#define DOLLAR 279
#define COMMA 280
#define QUOTE 281
#define FALSE 282
#define TRUE 283
#define INT_NUMBER 284
#define FLOAT_NUMBER 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 38 "mongo.y"
uint64_t num; char *string; float fnum;

#line 120 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

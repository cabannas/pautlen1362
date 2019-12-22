/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "alfa.y"

#include <stdio.h>
#include <string.h>

#include "alfa.h"
#include "tabla_hash.h"
#include "tabla_simbolos.h"
#include "generacion.h"
#include "y.tab.h"

extern FILE * fpasm;
extern FILE * yyout;
extern int yylex();
extern int yyleng;
extern int linea, columna, error;
void yyerror(char* s);

TABLA_HASH * tabla_global = NULL;
TABLA_HASH * tabla_local = NULL;

INFO_SIMBOLO* valor;

/* para los ids */
AMBITO ambito_actual;
CATEGORIA categoria_actual;
CLASE clase_actual;
TIPO tipo_actual;

/* para los parametros */
int adicional1;
int declarar;
int tipo_retorno;
int en_exp_list;

/* para los vectores */

/* tamano del vector actual */
int tamano_vector_actual = 1;
/* nombre del vector actual*/
char nombre_vector_actual[MAX_LON_ID];


/* para las funciones */

/* numero de variables locales */
int n_variables_locales_actual;
 /* posicion de la variable local */
int pos_variable_local_actual;
/* numero parametros actual */
int n_parametros_actual;
/* numero de parametros que se llama actualmente */
int n_parametros_llamada_actual;
/* posicion del parametro */
int pos_parametros_actual;
/* el retorno de la funcion */
int fn_retorno;
/* flag que nos dice si estamos dentro de una función o no */
int es_funcion = 0;
/* numero de etiquetas para nasm */
int etiqueta = 1;
/* identificador string de la funcion */
char nombre_funcion_actual[MAX_LON_ID];



#line 136 "y.tab.c"

# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    TOK_MAIN = 258,
    TOK_LLAVEIZQUIERDA = 259,
    TOK_LLAVEDERECHA = 260,
    TOK_PUNTOYCOMA = 261,
    TOK_INT = 262,
    TOK_BOOLEAN = 263,
    TOK_ARRAY = 264,
    TOK_CORCHETEIZQUIERDO = 265,
    TOK_CORCHETEDERECHO = 266,
    TOK_COMA = 267,
    TOK_FUNCTION = 268,
    TOK_PARENTESISIZQUIERDO = 269,
    TOK_PARENTESISDERECHO = 270,
    TOK_ASIGNACION = 271,
    TOK_IF = 272,
    TOK_ELSE = 273,
    TOK_WHILE = 274,
    TOK_SCANF = 275,
    TOK_PRINTF = 276,
    TOK_RETURN = 277,
    TOK_MAS = 278,
    TOK_MENOS = 279,
    TOK_DIVISION = 280,
    TOK_ASTERISCO = 281,
    TOK_AND = 282,
    TOK_OR = 283,
    TOK_NOT = 284,
    TOK_IGUAL = 285,
    TOK_DISTINTO = 286,
    TOK_MENORIGUAL = 287,
    TOK_MAYORIGUAL = 288,
    TOK_MENOR = 289,
    TOK_MAYOR = 290,
    TOK_TRUE = 291,
    TOK_FALSE = 292,
    TOK_CONSTANTE_ENTERA = 293,
    TOK_IDENTIFICADOR = 294,
    TOK_ERROR = 295,
    NEG = 296
  };
#endif
/* Tokens.  */
#define TOK_MAIN 258
#define TOK_LLAVEIZQUIERDA 259
#define TOK_LLAVEDERECHA 260
#define TOK_PUNTOYCOMA 261
#define TOK_INT 262
#define TOK_BOOLEAN 263
#define TOK_ARRAY 264
#define TOK_CORCHETEIZQUIERDO 265
#define TOK_CORCHETEDERECHO 266
#define TOK_COMA 267
#define TOK_FUNCTION 268
#define TOK_PARENTESISIZQUIERDO 269
#define TOK_PARENTESISDERECHO 270
#define TOK_ASIGNACION 271
#define TOK_IF 272
#define TOK_ELSE 273
#define TOK_WHILE 274
#define TOK_SCANF 275
#define TOK_PRINTF 276
#define TOK_RETURN 277
#define TOK_MAS 278
#define TOK_MENOS 279
#define TOK_DIVISION 280
#define TOK_ASTERISCO 281
#define TOK_AND 282
#define TOK_OR 283
#define TOK_NOT 284
#define TOK_IGUAL 285
#define TOK_DISTINTO 286
#define TOK_MENORIGUAL 287
#define TOK_MAYORIGUAL 288
#define TOK_MENOR 289
#define TOK_MAYOR 290
#define TOK_TRUE 291
#define TOK_FALSE 292
#define TOK_CONSTANTE_ENTERA 293
#define TOK_IDENTIFICADOR 294
#define TOK_ERROR 295
#define NEG 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 66 "alfa.y"

	tipo_atributos atributos;

#line 265 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   153

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

#define YYUNDEFTOK  2
#define YYMAXUTOK   296

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   152,   152,   154,   163,   166,   168,   176,   177,   179,
     181,   188,   194,   196,   201,   211,   227,   228,   230,   231,
     233,   246,   257,   288,   290,   292,   293,   295,   298,   309,
     310,   312,   313,   315,   316,   318,   319,   320,   321,   323,
     324,   326,   353,   363,   387,   393,   398,   410,   416,   422,
     433,   440,   474,   480,   493,   506,   519,   532,   545,   558,
     571,   584,   598,   641,   648,   655,   662,   674,   695,   717,
     723,   725,   731,   734,   748,   762,   776,   790,   804,   819,
     826,   834,   845,   860,   874
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_MAIN", "TOK_LLAVEIZQUIERDA",
  "TOK_LLAVEDERECHA", "TOK_PUNTOYCOMA", "TOK_INT", "TOK_BOOLEAN",
  "TOK_ARRAY", "TOK_CORCHETEIZQUIERDO", "TOK_CORCHETEDERECHO", "TOK_COMA",
  "TOK_FUNCTION", "TOK_PARENTESISIZQUIERDO", "TOK_PARENTESISDERECHO",
  "TOK_ASIGNACION", "TOK_IF", "TOK_ELSE", "TOK_WHILE", "TOK_SCANF",
  "TOK_PRINTF", "TOK_RETURN", "TOK_MAS", "TOK_MENOS", "TOK_DIVISION",
  "TOK_ASTERISCO", "TOK_AND", "TOK_OR", "TOK_NOT", "TOK_IGUAL",
  "TOK_DISTINTO", "TOK_MENORIGUAL", "TOK_MAYORIGUAL", "TOK_MENOR",
  "TOK_MAYOR", "TOK_TRUE", "TOK_FALSE", "TOK_CONSTANTE_ENTERA",
  "TOK_IDENTIFICADOR", "TOK_ERROR", "NEG", "$accept", "programa",
  "abrir_ambitos", "escrituraTS", "escritura_inicio_main",
  "cerrar_ambitos", "declaraciones", "declaracion", "clase",
  "clase_escalar", "tipo", "clase_vector", "identificadores", "funciones",
  "funcion", "fn_declaracion", "fn_name", "parametros_funcion",
  "resto_parametros_funcion", "parametro_funcion", "idpf",
  "declaraciones_funcion", "sentencias", "sentencia", "sentencia_simple",
  "bloque", "asignacion", "elemento_vector", "condicional", "if_exp",
  "if_exp_sentencias", "bucle", "while_exp", "while", "lectura",
  "escritura", "retorno_funcion", "exp", "idf_llamada_funcion",
  "lista_expresiones", "resto_lista_expresiones", "comparacion",
  "constante", "constante_logica", "constante_entera", "identificador", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

#define YYPACT_NINF -45

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-45)))

#define YYTABLE_NINF -69

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -45,     4,    10,   -45,    13,    27,   -45,   -45,     0,   -45,
      27,   -17,   -45,   -45,   -45,    21,    12,   -45,   -45,    26,
      25,     5,     0,   -45,    12,    49,    24,   -45,   -17,    31,
       7,    49,   -45,    33,    35,    11,    15,    15,    -5,    50,
      49,    51,   -45,   -45,    40,   -45,    49,    54,   -45,    49,
      15,   -45,   -45,   -45,     0,   -45,   -45,   -45,    53,    15,
     -45,   -45,    15,    15,    15,   -45,   -45,   -45,    -4,   -45,
     116,    59,   -45,   -45,   -45,   116,    15,    15,   -45,   -45,
     -45,    15,    62,    70,    71,   109,    36,    65,    81,   -45,
     123,    86,    74,   -45,   -45,    15,    15,    15,    15,    15,
      15,    15,    68,   116,   116,    79,    49,   -45,    73,   -45,
     -45,    94,     0,   -45,   -45,    95,   -45,    15,    15,    15,
      15,    15,    15,   -45,    -8,    -8,    -8,    -8,   -45,   -45,
     103,    85,   -45,    97,   -45,    27,    81,   -45,   116,   116,
     116,   116,   116,   116,    15,   -45,   -45,   -45,   -45,   -45,
     -45,   103,   -45
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,    13,    14,     0,     4,
       7,     0,    10,    12,    11,     0,    19,     8,    84,     0,
      16,     0,     0,     5,    19,     0,     0,     9,     0,     0,
       0,     0,    18,     0,     0,     0,     0,     0,     0,     0,
      31,     0,    34,    35,     0,    39,     0,     0,    40,     0,
       0,    36,    37,    38,    24,    17,    15,    22,     0,     0,
      50,    51,     0,     0,     0,    81,    82,    83,    62,    66,
      52,     0,    63,    79,    80,    53,     0,     0,    20,    32,
      33,     0,     0,     0,     0,     0,     0,     0,    26,     6,
       0,     0,     0,    58,    61,     0,     0,     0,     0,     0,
       0,    70,     0,    41,    42,    44,     0,    48,     0,    28,
      27,     0,     0,    23,     2,     0,    64,     0,     0,     0,
       0,     0,     0,    65,    54,    55,    56,    57,    59,    60,
      72,     0,    43,     0,    49,    30,    26,    46,    73,    74,
      75,    76,    77,    78,     0,    69,    67,    45,    29,    21,
      25,    72,    71
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -45,   -45,   -45,   -45,   -45,   -45,   -10,   -45,   -45,   -45,
      -6,   -45,    75,    80,   -45,   -45,   -45,   -45,   -31,    41,
     -45,   -45,   -28,   -45,   -45,   -45,   -45,   -16,   -45,   -45,
     -45,   -45,   -45,   -45,   -45,   -45,   -45,   -36,   -45,   -45,
     -44,   -45,   -45,   -45,   -45,   -45
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    16,    31,   114,     9,    10,    11,    12,
      13,    14,    19,    23,    24,    25,    26,    87,   113,    88,
     110,   149,    39,    40,    41,    42,    43,    69,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    70,    71,   131,
     145,    92,    72,    73,    74,    20
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,    75,    15,    58,     3,    76,    76,     6,     7,    44,
     -68,    77,    79,     4,    85,    44,    30,     5,    82,    99,
     100,    84,    18,    90,    44,    22,    91,    93,    94,    62,
      44,    21,    27,    44,     6,     7,     8,    28,    54,    63,
     102,   103,    56,    29,    64,   104,    57,    59,    86,    60,
      61,    65,    66,    67,    68,    78,    81,    80,    89,   124,
     125,   126,   127,   128,   129,   130,    33,   105,    34,    35,
      36,    37,    83,   101,   106,   109,   107,   134,   133,   132,
     111,   138,   139,   140,   141,   142,   143,   112,    38,   123,
      44,    95,    96,    97,    98,    99,   100,   -47,   135,   137,
     146,   116,   147,    55,    32,   150,    86,   152,   151,    95,
      96,    97,    98,    99,   100,   144,   117,   118,   119,   120,
     121,   122,     0,     0,   108,   148,    95,    96,    97,    98,
      99,   100,    95,    96,    97,    98,    99,   100,   115,    95,
      96,    97,    98,    99,   100,     0,    95,    96,    97,    98,
      99,   100,     0,   136
};

static const yytype_int16 yycheck[] =
{
      10,    37,     8,    31,     0,    10,    10,     7,     8,    25,
      14,    16,    40,     3,    50,    31,    22,     4,    46,    27,
      28,    49,    39,    59,    40,    13,    62,    63,    64,    14,
      46,    10,     6,    49,     7,     8,     9,    12,    14,    24,
      76,    77,    11,    38,    29,    81,    39,    14,    54,    14,
      39,    36,    37,    38,    39,     5,    16,     6,     5,    95,
      96,    97,    98,    99,   100,   101,    17,     5,    19,    20,
      21,    22,    18,    14,     4,    39,     5,     4,   106,    11,
      15,   117,   118,   119,   120,   121,   122,     6,    39,    15,
     106,    23,    24,    25,    26,    27,    28,    18,     4,     4,
      15,    15,     5,    28,    24,   136,   112,   151,   144,    23,
      24,    25,    26,    27,    28,    12,    30,    31,    32,    33,
      34,    35,    -1,    -1,    15,   135,    23,    24,    25,    26,
      27,    28,    23,    24,    25,    26,    27,    28,    15,    23,
      24,    25,    26,    27,    28,    -1,    23,    24,    25,    26,
      27,    28,    -1,   112
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    43,    44,     0,     3,     4,     7,     8,     9,    48,
      49,    50,    51,    52,    53,    52,    45,    48,    39,    54,
      87,    10,    13,    55,    56,    57,    58,     6,    12,    38,
      52,    46,    55,    17,    19,    20,    21,    22,    39,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    14,    54,    11,    39,    64,    14,
      14,    39,    14,    24,    29,    36,    37,    38,    39,    69,
      79,    80,    84,    85,    86,    79,    10,    16,     5,    64,
       6,    16,    64,    18,    64,    79,    52,    59,    61,     5,
      79,    79,    83,    79,    79,    23,    24,    25,    26,    27,
      28,    14,    79,    79,    79,     5,     4,     5,    15,    39,
      62,    15,     6,    60,    47,    15,    15,    30,    31,    32,
      33,    34,    35,    15,    79,    79,    79,    79,    79,    79,
      79,    81,    11,    64,     4,     4,    61,     4,    79,    79,
      79,    79,    79,    79,    12,    82,    15,     5,    48,    63,
      60,    79,    82
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    45,    46,    47,    48,    48,    49,
      50,    50,    51,    52,    52,    53,    54,    54,    55,    55,
      56,    57,    58,    59,    59,    60,    60,    61,    62,    63,
      63,    64,    64,    65,    65,    66,    66,    66,    66,    67,
      67,    68,    68,    69,    70,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    80,    81,
      81,    82,    82,    83,    83,    83,    83,    83,    83,    84,
      84,    85,    85,    86,    87
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,    10,     0,     0,     0,     0,     1,     2,     3,
       1,     1,     1,     1,     1,     5,     1,     3,     2,     0,
       3,     6,     3,     2,     0,     3,     0,     2,     1,     1,
       0,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     4,     3,     5,     5,     3,     3,     4,
       2,     2,     2,     2,     3,     3,     3,     3,     2,     3,
       3,     2,     1,     1,     3,     3,     1,     4,     1,     2,
       0,     3,     0,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 152 "alfa.y"
    {fprintf(yyout, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> } \n");}
#line 1480 "y.tab.c"
    break;

  case 3:
#line 154 "alfa.y"
    {

	tabla_global = crear_tabla(TAM_MAX_TABLA);
	tabla_local = crear_tabla(TAM_MAX_TABLA);

	escribir_subseccion_data(fpasm);
	escribir_cabecera_bss(fpasm);
}
#line 1493 "y.tab.c"
    break;

  case 4:
#line 163 "alfa.y"
    {
  escribir_segmento_codigo(fpasm);}
#line 1500 "y.tab.c"
    break;

  case 5:
#line 166 "alfa.y"
    {escribir_inicio_main(fpasm);}
#line 1506 "y.tab.c"
    break;

  case 6:
#line 168 "alfa.y"
    {
	if(tabla_local){
		liberar_tabla(tabla_local);
	}
	liberar_tabla(tabla_global);
	escribir_fin(fpasm);
}
#line 1518 "y.tab.c"
    break;

  case 7:
#line 176 "alfa.y"
    {fprintf(yyout, ";R2:\t<declaraciones> ::= <declaracion> \n");}
#line 1524 "y.tab.c"
    break;

  case 8:
#line 177 "alfa.y"
    {fprintf(yyout, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones> \n");}
#line 1530 "y.tab.c"
    break;

  case 9:
#line 179 "alfa.y"
    {fprintf(yyout, ";R4:\t<declaracion> ::= <clase> <identificadores> ; \n");}
#line 1536 "y.tab.c"
    break;

  case 10:
#line 181 "alfa.y"
    {

		tamano_vector_actual = 1;
		clase_actual = ESCALAR;

		fprintf(yyout, ";R5:\t<clase> ::= <clase_escalar> \n");
	}
#line 1548 "y.tab.c"
    break;

  case 11:
#line 188 "alfa.y"
    {

		clase_actual = VECTOR;
		fprintf(yyout, ";R7:\t<clase> ::= <clase_vector> \n");
	}
#line 1558 "y.tab.c"
    break;

  case 12:
#line 194 "alfa.y"
    {fprintf(yyout, ";R9:\t<clase_escalar> ::= <tipo> \n");}
#line 1564 "y.tab.c"
    break;

  case 13:
#line 196 "alfa.y"
    {

    tipo_actual=ENTERO;
    fprintf(yyout, ";R10:\t<tipo> ::= int \n");
  }
#line 1574 "y.tab.c"
    break;

  case 14:
#line 201 "alfa.y"
    {

    tipo_actual=BOOLEANO;
    fprintf(yyout, ";R11:\t<tipo> ::= boolean \n");
  }
#line 1584 "y.tab.c"
    break;

  case 15:
#line 211 "alfa.y"
    {

    tamano_vector_actual = (yyvsp[-1].atributos).valor_entero;

		if(tamano_vector_actual < 1 || tamano_vector_actual > MAX_TAM_VECTOR){
			printf("****Error semantico en lin %d: El tamanio del vector <%s> excede los limites permitidos (1,64).\n",linea, nombre_vector_actual);
			return 0;
		}

    fprintf(yyout, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ] \n");
  }
#line 1600 "y.tab.c"
    break;

  case 16:
#line 227 "alfa.y"
    {fprintf(yyout, ";R18:\t<identificadores> ::= <identificador> \n");}
#line 1606 "y.tab.c"
    break;

  case 17:
#line 228 "alfa.y"
    {fprintf(yyout, ";R19:\t<identificadores> ::= <identificador> , <identificadores> \n");}
#line 1612 "y.tab.c"
    break;

  case 18:
#line 230 "alfa.y"
    {fprintf(yyout, ";R20:\t<funciones> ::= <funcion> <funciones> \n");}
#line 1618 "y.tab.c"
    break;

  case 19:
#line 231 "alfa.y"
    {fprintf(yyout, ";R21:\t<funciones> ::= \n");}
#line 1624 "y.tab.c"
    break;

  case 20:
#line 233 "alfa.y"
    {

  ambito_actual=GLOBAL;
  valor = busqueda_global((yyvsp[-2].atributos).lexema, tabla_global);
  valor->adicional1 = n_parametros_actual;

  if(fn_retorno==0){
    printf("****Error semantico en lin %d: Funcion %s sin sentencia de retorno\n", linea, (yyvsp[-2].atributos).lexema);
    return 0;
  }
  fprintf(yyout, ";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> } \n");
  }
#line 1641 "y.tab.c"
    break;

  case 21:
#line 246 "alfa.y"
    {

  valor = busqueda_global((yyvsp[-5].atributos).lexema, tabla_global);
  valor->adicional1=n_parametros_actual;
  strcpy((yyval.atributos).lexema, (yyvsp[-5].atributos).lexema);

	/* llamamos a declararFuncion (GC) */
	declararFuncion(fpasm, (yyvsp[-5].atributos).lexema, n_variables_locales_actual);

 }
#line 1656 "y.tab.c"
    break;

  case 22:
#line 257 "alfa.y"
    {

  valor = busqueda_global((yyvsp[0].atributos).lexema, tabla_global);

  if(valor){
    printf("****Error semantico en lin %d: Declaracion dupliacada", linea);
    return 0;
  }


  if(declarar_funcion(tabla_global, tabla_local, (yyvsp[0].atributos).lexema, FUNCION, tipo_actual, ESCALAR, adicional1, 0)==OK){
    ambito_actual=LOCAL;
  }

  adicional1++;

  n_variables_locales_actual = 0;
  pos_variable_local_actual = 1;
  n_parametros_actual = 0;
  pos_parametros_actual = 0;
  fn_retorno = 0;

  strcpy((yyval.atributos).lexema, (yyvsp[0].atributos).lexema);
  es_funcion=1;

  tipo_retorno=tipo_actual;

  strcpy(nombre_funcion_actual, (yyvsp[0].atributos).lexema);
}
#line 1690 "y.tab.c"
    break;

  case 23:
#line 288 "alfa.y"
    {
fprintf(yyout, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion> \n");}
#line 1697 "y.tab.c"
    break;

  case 24:
#line 290 "alfa.y"
    {fprintf(yyout, ";R24:\t<parametros_funcion> ::= \n");}
#line 1703 "y.tab.c"
    break;

  case 25:
#line 292 "alfa.y"
    {fprintf(yyout, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion> \n");}
#line 1709 "y.tab.c"
    break;

  case 26:
#line 293 "alfa.y"
    {fprintf(yyout, ";R26:\t<resto_parametros_funcion> ::= \n");}
#line 1715 "y.tab.c"
    break;

  case 27:
#line 295 "alfa.y"
    {
fprintf(yyout, ";R27:\t<parametro_funcion> ::= <tipo> <identificador> \n");}
#line 1722 "y.tab.c"
    break;

  case 28:
#line 298 "alfa.y"
    {
if (declarar_variable_local(tabla_local, (yyvsp[0].atributos).lexema,PARAMETRO, tipo_actual, ESCALAR, adicional1, pos_parametros_actual) == ERR) {
	printf("****Error semantico en lin %d: Declaracion dupliacada", linea);
	return 0;
}

  adicional1++;
  pos_parametros_actual++;
  n_parametros_actual++;
}
#line 1737 "y.tab.c"
    break;

  case 29:
#line 309 "alfa.y"
    {fprintf(yyout, ";R28:\t<declaraciones_funcion> ::= <declaraciones> \n");}
#line 1743 "y.tab.c"
    break;

  case 30:
#line 310 "alfa.y"
    {fprintf(yyout, ";R29:\t<declaraciones_funcion> ::= \n");}
#line 1749 "y.tab.c"
    break;

  case 31:
#line 312 "alfa.y"
    {fprintf(yyout, ";R30:\t<sentencias> ::= <sentencia> \n");}
#line 1755 "y.tab.c"
    break;

  case 32:
#line 313 "alfa.y"
    {fprintf(yyout, ";R31:\t<sentencias> ::= <sentencia> <sentencias> \n");}
#line 1761 "y.tab.c"
    break;

  case 33:
#line 315 "alfa.y"
    {fprintf(yyout, ";R32:\t<sentencia> ::= <sentencia_simple> ; \n");}
#line 1767 "y.tab.c"
    break;

  case 34:
#line 316 "alfa.y"
    {fprintf(yyout, ";R33:\t<sentencia> ::= <bloque> \n");}
#line 1773 "y.tab.c"
    break;

  case 35:
#line 318 "alfa.y"
    {fprintf(yyout, ";R34:\t<sentencia_simple> ::= <asignacion> \n");}
#line 1779 "y.tab.c"
    break;

  case 36:
#line 319 "alfa.y"
    {fprintf(yyout, ";R35:\t<sentencia_simple> ::= <lectura> \n");}
#line 1785 "y.tab.c"
    break;

  case 37:
#line 320 "alfa.y"
    {fprintf(yyout, ";R36:\t<sentencia_simple> ::= <escritura> \n");}
#line 1791 "y.tab.c"
    break;

  case 38:
#line 321 "alfa.y"
    {fprintf(yyout, ";R38:\t<sentencia_simple> ::= <retorno_funcion> \n");}
#line 1797 "y.tab.c"
    break;

  case 39:
#line 323 "alfa.y"
    {fprintf(yyout, ";R40:\t<bloque> ::= <condicional> \n");}
#line 1803 "y.tab.c"
    break;

  case 40:
#line 324 "alfa.y"
    {fprintf(yyout, ";R41:\t<bloque> ::= <bucle> \n");}
#line 1809 "y.tab.c"
    break;

  case 41:
#line 326 "alfa.y"
    {
  if (ambito_actual == GLOBAL) {
	valor = busqueda_global((yyvsp[-2].atributos).lexema, tabla_global);
  }else {
	valor = busqueda_local((yyvsp[-2].atributos).lexema, tabla_global,tabla_local);
  }
  if(valor == NULL){
	printf("****Error semantico en lin %d: Acceso a variable no declarada (%s)\n", linea, (yyvsp[-2].atributos).lexema);
	return 0;
  }
  if(valor->tipo != (yyvsp[0].atributos).tipo || valor->clase == VECTOR || valor->categoria == FUNCION ){
	printf("****Error semantico en lin %d: Asignacion incompatible\n", linea);
	return 0;
  }


if(valor->categoria == PARAMETRO){
	escribirParametro(fpasm, valor->adicional2, n_parametros_actual);
}
else if(valor->adicional2 == 0){
	asignar(fpasm, (yyvsp[-2].atributos).lexema, (yyvsp[0].atributos).es_direccion);
}
else {
	escribirVariableLocal(fpasm, valor->adicional2);
}

  fprintf(yyout, ";R43:\t<asignacion> ::= <identificador> = <exp> \n");}
#line 1841 "y.tab.c"
    break;

  case 42:
#line 353 "alfa.y"
    {

  if((yyvsp[-2].atributos).tipo != (yyvsp[0].atributos).tipo){
	printf("****Error semantico en lin %d: Asignacion no compatible\n", linea);
	return 0;
  }

  asignarVector(fpasm, (yyvsp[0].atributos).es_direccion);
  fprintf(yyout, ";R44:\t<asignacion> ::= <elemento_vector> = <exp> \n");}
#line 1855 "y.tab.c"
    break;

  case 43:
#line 363 "alfa.y"
    {
  if (ambito_actual == GLOBAL) {
	valor = busqueda_global((yyvsp[-3].atributos).lexema, tabla_global);
  }else {
	valor = busqueda_local((yyvsp[-3].atributos).lexema, tabla_global,tabla_local);
  }
  if(valor == NULL){
	printf("****Error semantico en lin %d: Acceso a variable sin declarar (%s)\n", linea, (yyvsp[-3].atributos).lexema);
	return 0;
  }
  if(valor->clase != VECTOR){
	printf("****Error semantico en lin %d: Indexacion de una variable que no es de tipo vector (%s)\n", linea, (yyvsp[-3].atributos).lexema);
	return 0;
  }
  if((yyvsp[-1].atributos).tipo != ENTERO){
	printf("****Error semantico en lin %d: El indice en una indexacion debe ser de tipo entero (%s)\n", linea, (yyvsp[-3].atributos).lexema);
	return 0;
  }
  (yyval.atributos).es_direccion = 1;
  (yyval.atributos).tipo = valor->tipo;

	escribir_elemento_vector(fpasm, (yyvsp[-3].atributos).lexema, valor->adicional1, (yyvsp[-1].atributos).es_direccion);
  fprintf(yyout, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ] \n");}
#line 1883 "y.tab.c"
    break;

  case 44:
#line 387 "alfa.y"
    {

	ifthen_fin(fpasm, (yyvsp[-2].atributos).etiqueta);

  fprintf(yyout, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> } \n");}
#line 1893 "y.tab.c"
    break;

  case 45:
#line 393 "alfa.y"
    {
	  ifthenelse_fin(fpasm, (yyvsp[-4].atributos).etiqueta);
    fprintf(yyout, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> } \n");
  }
#line 1902 "y.tab.c"
    break;

  case 46:
#line 398 "alfa.y"
    {
  if((yyvsp[-2].atributos).tipo != BOOLEANO){
    printf("****Error semantico en lin %d: Condicional sin elemento booleano\n", linea);
    return 0;
  }
  (yyval.atributos).etiqueta = etiqueta ++;

	ifthen_inicio(fpasm, (yyvsp[-2].atributos).es_direccion, (yyval.atributos).etiqueta);

}
#line 1917 "y.tab.c"
    break;

  case 47:
#line 410 "alfa.y"
    {

  (yyval.atributos).etiqueta = (yyvsp[-2].atributos).etiqueta;
	ifthenelse_fin_then(fpasm, (yyvsp[-2].atributos).etiqueta);
}
#line 1927 "y.tab.c"
    break;

  case 48:
#line 416 "alfa.y"
    {

	while_fin(fpasm, (yyvsp[-2].atributos).etiqueta);
  fprintf(yyout, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> } \n");
}
#line 1937 "y.tab.c"
    break;

  case 49:
#line 422 "alfa.y"
    {

  if((yyvsp[-2].atributos).tipo != BOOLEANO){
    printf("****Error semantico en lin %d: Bucle con condicion de tipo int\n", linea);
    return 0;
  }
  (yyval.atributos).etiqueta = (yyvsp[-3].atributos).etiqueta;

	while_exp_pila (fpasm, (yyvsp[-2].atributos).es_direccion, (yyval.atributos).etiqueta);
}
#line 1952 "y.tab.c"
    break;

  case 50:
#line 433 "alfa.y"
    {

  (yyval.atributos).etiqueta = etiqueta++;

	while_inicio(fpasm, (yyval.atributos).etiqueta);
}
#line 1963 "y.tab.c"
    break;

  case 51:
#line 440 "alfa.y"
    {

  if(ambito_actual == GLOBAL){
    valor = busqueda_global((yyvsp[0].atributos).lexema, tabla_global);
  }else{
    valor = busqueda_local((yyvsp[0].atributos).lexema, tabla_global, tabla_local);
  }

  if(valor == NULL){
  		printf("****Error semantico en lin %d: Acceso a variable sin declarar (%s).\n", linea, (yyvsp[0].atributos).lexema);
  		return 0;
  }

  /*Comprobaciones semanticas*/
  if(valor->categoria == FUNCION){
    printf("****Error semantico en lin %d: Asignacion no compatible.\n", linea);
    return 0;
  }
  if(valor->clase == VECTOR){
    printf("****Error semantico en lin %d: Asignacion no compatible.\n", linea);
    return 0;
  }

	if(valor->categoria == PARAMETRO){
		leerParametro(fpasm, valor->tipo, n_parametros_actual, valor->adicional2);
	} else if(valor->adicional2 == 0){
		leer(fpasm, valor->lexema, valor->tipo);
	} else{
		leerLocal(fpasm, valor->tipo, valor->adicional2);
	}

  fprintf(yyout, ";R54:\t<lectura> ::= scanf <identificador> \n");
}
#line 2001 "y.tab.c"
    break;

  case 52:
#line 474 "alfa.y"
    {

  escribir(fpasm, (yyvsp[0].atributos).es_direccion, (yyvsp[0].atributos).tipo);
  fprintf(yyout, ";R56:\t<escritura> ::= printf <exp> \n");
}
#line 2011 "y.tab.c"
    break;

  case 53:
#line 480 "alfa.y"
    {

  if((((yyvsp[0].atributos).es_direccion != 1) && ((yyvsp[0].atributos).es_direccion != 0)) || (yyvsp[0].atributos).tipo != tipo_retorno){
  	printf("****Error semantico en lin %d: Sentencia de retorno fuera de una función.\n", linea);
  	return 0;
  }

  retornarFuncion(fpasm, (yyvsp[0].atributos).es_direccion);
  fn_retorno++;
  fprintf(yyout, ";R61:\t<retorno_funcion> ::= return <exp> \n");
}
#line 2027 "y.tab.c"
    break;

  case 54:
#line 493 "alfa.y"
    {

		if((yyvsp[-2].atributos).tipo !=  ENTERO || (yyvsp[0].atributos).tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  (yyval.atributos).tipo = ENTERO;
	  (yyval.atributos).es_direccion = 0;

	  sumar(fpasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);

		fprintf(yyout, ";R72:\t<exp> ::= <exp> + <exp> \n");
	}
#line 2045 "y.tab.c"
    break;

  case 55:
#line 506 "alfa.y"
    {

		if((yyvsp[-2].atributos).tipo !=  ENTERO || (yyvsp[0].atributos).tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  (yyval.atributos).tipo = ENTERO;
	  (yyval.atributos).es_direccion = 0;

	  restar(fpasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);

		fprintf(yyout, ";R73:\t<exp> ::= <exp> - <exp> \n");
	}
#line 2063 "y.tab.c"
    break;

  case 56:
#line 519 "alfa.y"
    {

		if((yyvsp[-2].atributos).tipo !=  ENTERO || (yyvsp[0].atributos).tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  (yyval.atributos).tipo = ENTERO;
	  (yyval.atributos).es_direccion = 0;

	  dividir(fpasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);

		fprintf(yyout, ";R74:\t<exp> ::= <exp> / <exp> \n");
	}
#line 2081 "y.tab.c"
    break;

  case 57:
#line 532 "alfa.y"
    {

		if((yyvsp[-2].atributos).tipo !=  ENTERO || (yyvsp[0].atributos).tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  (yyval.atributos).tipo = ENTERO;
	  (yyval.atributos).es_direccion = 0;

	  multiplicar(fpasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);

		fprintf(yyout, ";R75:\t<exp> ::= <exp> * <exp> \n");
	}
#line 2099 "y.tab.c"
    break;

  case 58:
#line 545 "alfa.y"
    {

		if((yyvsp[0].atributos).tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  (yyval.atributos).tipo = ENTERO;
	  (yyval.atributos).es_direccion = 0;

	  cambiar_signo(fpasm, (yyvsp[0].atributos).es_direccion);

		fprintf(yyout, ";R76:\t<exp> ::= - <exp> \n");
	}
#line 2117 "y.tab.c"
    break;

  case 59:
#line 558 "alfa.y"
    {

		if((yyvsp[-2].atributos).tipo !=  BOOLEANO || (yyvsp[0].atributos).tipo !=  BOOLEANO){
	    printf("****Error semantico en lin %d: Operacion logica con operandos int.\n", linea);
	    return 0;
	  }
	  (yyval.atributos).tipo = BOOLEANO;
	  (yyval.atributos).es_direccion = 0;

	  y(fpasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);

		fprintf(yyout, ";R77:\t<exp> ::= <exp> && <exp> \n");
		}
#line 2135 "y.tab.c"
    break;

  case 60:
#line 571 "alfa.y"
    {

		if((yyvsp[-2].atributos).tipo !=  BOOLEANO || (yyvsp[0].atributos).tipo !=  BOOLEANO){
		 printf("****Error semantico en lin %d: Operacion logica con operandos int.\n", linea);
		 return 0;
	 	}
		 (yyval.atributos).tipo = BOOLEANO;
		 (yyval.atributos).es_direccion = 0;

		 o(fpasm, (yyvsp[-2].atributos).es_direccion,(yyvsp[0].atributos).es_direccion);

		fprintf(yyout, ";R78:\t<exp> ::= <exp> || <exp> \n");
	}
#line 2153 "y.tab.c"
    break;

  case 61:
#line 584 "alfa.y"
    {

		if((yyvsp[0].atributos).tipo !=  BOOLEANO){
	    printf("****Error semantico en lin %d: Operacion logica con operandos int.\n", linea);
	    return 0;
	  }
	  (yyval.atributos).tipo = BOOLEANO;
	  (yyval.atributos).es_direccion = 0;

	  no(fpasm, (yyvsp[0].atributos).es_direccion, etiqueta);
	  etiqueta++;

		fprintf(yyout, ";R79:\t<exp> ::= ! <exp> \n");
	}
#line 2172 "y.tab.c"
    break;

  case 62:
#line 598 "alfa.y"
    {
	      /*Se comprueba que el identificador no exista en el ambito actual. Si existiera, se genera un
	      mensaje de error semantico y se termina el proceso de compilacion con error.*/
	    if(ambito_actual == GLOBAL){
	      valor = busqueda_global((yyvsp[0].atributos).lexema, tabla_global);
	    }else{
	      valor = busqueda_local((yyvsp[0].atributos).lexema, tabla_global, tabla_local);
	    }
	    if(valor == NULL){
	      printf("****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", linea, (yyvsp[0].atributos).lexema);
	      return 0;
	    }

	    if(valor->clase == VECTOR || valor->categoria == FUNCION){
	    	printf("****Error semantico en lin %d: Asignacion incompatible\n", linea);
	    	return 0;
	    }
	    (yyval.atributos).tipo = valor->tipo;
	    (yyval.atributos).es_direccion=1;

		/*GENERACION DE CODIGO*/
		if(valor->categoria == PARAMETRO){
			(yyval.atributos).es_direccion = 0;
			/* TODO puede que haya que revisar escribirParametro */
			escribirParametro(fpasm, valor->adicional2, n_parametros_actual);
		}else if(valor->adicional2 == 0){
			if(en_exp_list == 0){/*si no es una direccion en la lista de parametros d la fn en_exp_list = 1*/
				(yyval.atributos).es_direccion = 1;
				/*TODO: escribir operando a lo mejor deber revisarse*/
				/* TODO: a lo mejor está al reves el 0 y el 1 */
				escribir_operando(fpasm, (yyvsp[0].atributos).lexema, 0);
			}else{
				(yyval.atributos).es_direccion = 0;
				escribir_operando(fpasm, (yyvsp[0].atributos).lexema, 1);
			}
		}else{
			(yyval.atributos).es_direccion = 0;
			/* puede que haya que revisar escribirVariableLocal */
			escribirVariableLocal(fpasm, valor->adicional2);
		}

		fprintf(yyout, ";R80:\t<exp> ::= <identificador> \n");
	}
#line 2220 "y.tab.c"
    break;

  case 63:
#line 641 "alfa.y"
    {

		(yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
	  (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;

		fprintf(yyout, ";R81:\t<exp> ::= <constante> \n");
	}
#line 2232 "y.tab.c"
    break;

  case 64:
#line 648 "alfa.y"
    {

		(yyval.atributos).tipo = (yyvsp[-1].atributos).tipo;
	  (yyval.atributos).es_direccion = (yyvsp[-1].atributos).es_direccion;

		fprintf(yyout, ";R82:\t<exp> ::= ( <exp> ) \n");
	}
#line 2244 "y.tab.c"
    break;

  case 65:
#line 655 "alfa.y"
    {

		(yyval.atributos).tipo = (yyvsp[-1].atributos).tipo;
	  (yyval.atributos).es_direccion = (yyvsp[-1].atributos).es_direccion;

		fprintf(yyout, ";R83:\t<exp> ::= ( <comparacion> ) \n");
	}
#line 2256 "y.tab.c"
    break;

  case 66:
#line 662 "alfa.y"
    {

		(yyval.atributos).tipo = (yyvsp[0].atributos).tipo;

		if(en_exp_list == 0){
			(yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
		}else{
			(yyval.atributos).es_direccion = 0;
		}

		fprintf(yyout, ";R85:\t<exp> ::= <elemento_vector> \n");
	}
#line 2273 "y.tab.c"
    break;

  case 67:
#line 674 "alfa.y"
    {

		valor = busqueda_global((yyvsp[-3].atributos).lexema, tabla_global);
		if (valor == NULL) {
			printf("****Error semantico en lin %d: Acceso a variable no declarada (%s)\n", linea, (yyvsp[-3].atributos).lexema);
			return 0;
		}
		if(valor->adicional1 != n_parametros_llamada_actual){
			printf("****Error semantico en lin %d: Numero incorrecto de parametros en llamada a funcion (%s)\n", linea, (yyvsp[-3].atributos).lexema);
			return 0;
		}

	llamarFuncion(fpasm, (yyvsp[-3].atributos).lexema, n_parametros_llamada_actual);

	en_exp_list = 0;
	(yyval.atributos).tipo = valor->tipo;
	(yyval.atributos).es_direccion = 0;

	fprintf(yyout, ";R88:\t<exp> ::= <identificador> ( <lista_expresiones> ) \n");
}
#line 2298 "y.tab.c"
    break;

  case 68:
#line 695 "alfa.y"
    {
	valor = busqueda_global((yyvsp[0].atributos).lexema, tabla_global);
	if (valor == NULL) {
		printf("****Error semantico en lin %d: Acceso a variable no declarada (%s)\n", linea, (yyvsp[0].atributos).lexema);
		return 0;
	}
	if(valor->categoria != FUNCION){
		printf("****Error semantico en lin %d: Asignacion incompatible\n", linea);
		return 0;
	}
	/*no podemos pasar una funcion por parametro a otra funcion*/
	if(en_exp_list == 1){
		printf("****Error semantico en lin %d: No esta permitido el uso de llamadas a funciones como parametros de otras funciones\n", linea);
		return 0;
	}
	n_parametros_llamada_actual = 0;
	en_exp_list = 1;
	strcpy((yyval.atributos).lexema, (yyvsp[0].atributos).lexema);
}
#line 2322 "y.tab.c"
    break;

  case 69:
#line 717 "alfa.y"
    {

	n_parametros_llamada_actual++;

	fprintf(yyout, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones> \n");
	}
#line 2333 "y.tab.c"
    break;

  case 70:
#line 723 "alfa.y"
    {fprintf(yyout, ";R90:\t<lista_expresiones> ::=  \n");}
#line 2339 "y.tab.c"
    break;

  case 71:
#line 725 "alfa.y"
    {

	n_parametros_llamada_actual++;

	fprintf(yyout, ";R91\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones> \n");
	}
#line 2350 "y.tab.c"
    break;

  case 72:
#line 731 "alfa.y"
    {fprintf(yyout, ";R92:\t<resto_lista_expresiones> ::=  \n");}
#line 2356 "y.tab.c"
    break;

  case 73:
#line 734 "alfa.y"
    {

	if((yyvsp[-2].atributos).tipo !=  ENTERO || (yyvsp[0].atributos).tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    (yyval.atributos).tipo = BOOLEANO;
    (yyval.atributos).es_direccion = 0;

    igual(fpasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiqueta);
    etiqueta++;

	fprintf(yyout, ";R93:\t<comparacion> ::= <exp> == <exp> \n");
	}
#line 2375 "y.tab.c"
    break;

  case 74:
#line 748 "alfa.y"
    {

		if((yyvsp[-2].atributos).tipo !=  ENTERO || (yyvsp[0].atributos).tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    (yyval.atributos).tipo = BOOLEANO;
    (yyval.atributos).es_direccion = 0;

    distinto(fpasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiqueta);
    etiqueta++;

		fprintf(yyout, ";R94:\t<comparacion> ::= <exp> != <exp> \n");
	}
#line 2394 "y.tab.c"
    break;

  case 75:
#line 762 "alfa.y"
    {

		if((yyvsp[-2].atributos).tipo !=  ENTERO || (yyvsp[0].atributos).tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    (yyval.atributos).tipo = BOOLEANO;
    (yyval.atributos).es_direccion = 0;

    menor_igual(fpasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiqueta);
    etiqueta++;

		fprintf(yyout, ";R95:\t<comparacion> ::= <exp> <= <exp> \n");
	}
#line 2413 "y.tab.c"
    break;

  case 76:
#line 776 "alfa.y"
    {

		if((yyvsp[-2].atributos).tipo !=  ENTERO || (yyvsp[0].atributos).tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    (yyval.atributos).tipo = BOOLEANO;
    (yyval.atributos).es_direccion = 0;

    mayor_igual(fpasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiqueta);
    etiqueta++;

		fprintf(yyout, ";R96:\t<comparacion> ::= <exp> >= <exp> \n");
	}
#line 2432 "y.tab.c"
    break;

  case 77:
#line 790 "alfa.y"
    {

		if((yyvsp[-2].atributos).tipo !=  ENTERO || (yyvsp[0].atributos).tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    (yyval.atributos).tipo = BOOLEANO;
    (yyval.atributos).es_direccion = 0;

    menor(fpasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiqueta);
    etiqueta++;

		fprintf(yyout, ";R97:\t<comparacion> ::= <exp> < <exp> \n");
	}
#line 2451 "y.tab.c"
    break;

  case 78:
#line 804 "alfa.y"
    {

		if((yyvsp[-2].atributos).tipo !=  ENTERO || (yyvsp[0].atributos).tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    (yyval.atributos).tipo = BOOLEANO;
    (yyval.atributos).es_direccion = 0;

    mayor(fpasm, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiqueta);
    etiqueta++;

		fprintf(yyout, ";R98:\t<comparacion> ::= <exp> > <exp> \n");
	}
#line 2470 "y.tab.c"
    break;

  case 79:
#line 819 "alfa.y"
    {

	(yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
  (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;

	fprintf(yyout, ";R99:\t<constante> ::= <constante_logica> \n");
	}
#line 2482 "y.tab.c"
    break;

  case 80:
#line 826 "alfa.y"
    {

		(yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
  	(yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;

		fprintf(yyout, ";R100:\t<constante> ::= <constante_entera> \n");
	}
#line 2494 "y.tab.c"
    break;

  case 81:
#line 834 "alfa.y"
    {

		(yyval.atributos).tipo = BOOLEANO;
    (yyval.atributos).es_direccion = 0;

    /* generacion de codigo */
    fprintf(fpasm, "; numero_linea: %d\n", linea);
    fprintf(fpasm, "\tpush dword 1\n");

	fprintf(yyout, ";R102:\t<constante_logica> ::= true \n");
	}
#line 2510 "y.tab.c"
    break;

  case 82:
#line 845 "alfa.y"
    {

		(yyval.atributos).tipo = BOOLEANO;
    (yyval.atributos).es_direccion = 0;

    /* generacion de codigo */
    fprintf(fpasm, "; numero_linea: %d\n", linea);
    fprintf(fpasm, "\tpush dword 0\n");


		fprintf(yyout, ";R103:\t<constante_logica> ::= false \n");
	}
#line 2527 "y.tab.c"
    break;

  case 83:
#line 860 "alfa.y"
    {

		(yyval.atributos).tipo = ENTERO;
    (yyval.atributos).es_direccion = 0;

    /* generacion de codigo */
    fprintf(fpasm, "; numero_linea %d\n", linea);
    fprintf(fpasm, "\tpush dword %d\n", (yyvsp[0].atributos).valor_entero);

	fprintf(yyout, ";R104:\t<constante_entera> ::= TOK_CONSTANTE_ENTERA \n");
}
#line 2543 "y.tab.c"
    break;

  case 84:
#line 874 "alfa.y"
    {

		if (ambito_actual == GLOBAL){
			printf("global\n");
	 		declarar = declarar_variable_global(tabla_global, (yyvsp[0].atributos).lexema, categoria_actual, tipo_actual, clase_actual, 0, 0);
		}else{
			printf("locals\n");
			declarar = declarar_variable_local(tabla_local, (yyvsp[0].atributos).lexema, categoria_actual, tipo_actual, clase_actual, 0, 0);
		}
		if(declarar == ERR){
			printf("****Error semantico en lin %d: Declaracion duplicada.\n", linea);
			return 0;
		}else{
			adicional1 ++;
		}
		if (ambito_actual == GLOBAL){
			valor = busqueda_global((yyvsp[0].atributos).lexema, tabla_global);
		}else{
			valor = busqueda_local((yyvsp[0].atributos).lexema, tabla_global, tabla_local);
		}
		if (!valor) {
			printf("****Error semantico en lin %d: IAcceso a variable no declarada (%s)\n", linea, (yyvsp[0].atributos).lexema);
			return 0;
		}

		/* generacion de codigo */

		if(es_funcion == 0){
			declarar_variable(fpasm, (yyvsp[0].atributos).lexema, clase_actual, tamano_vector_actual);
			valor->clase = clase_actual;
			valor->tipo = tipo_actual;
			/*vectores*/
			if(valor->clase == VECTOR){
				valor->adicional1 = tamano_vector_actual;
				strcpy(nombre_vector_actual, (yyvsp[0].atributos).lexema);
			}
		}else{
			if(clase_actual == VECTOR){
				printf("****Error semantico en lin %d: Variable local de tipo no escalar.\n", linea);
				return 0;
			}

			valor->tipo = tipo_actual;
			valor->clase = clase_actual;
			valor->adicional2 = pos_variable_local_actual;
			n_variables_locales_actual++;
			pos_variable_local_actual++;
	}

	fprintf(yyout, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR \n");
}
#line 2599 "y.tab.c"
    break;


#line 2603 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 926 "alfa.y"


void yyerror(char* s){
	if(error == 0){
		fprintf(stdout,"**** Error sintáctico en [lin %d, col %d]\n",linea, (columna-yyleng));
	}
	error = 0;
}

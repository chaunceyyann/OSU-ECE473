/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 22 "config_gram.y" /* yacc.c:339  */


#include "ac_cfg.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "avrdude.h"

#include "config.h"
#include "lists.h"
#include "par.h"
#include "serbb.h"
#include "pindefs.h"
#include "ppi.h"
#include "pgm.h"
#include "stk500.h"
#include "arduino.h"
#include "buspirate.h"
#include "stk500v2.h"
#include "stk500generic.h"
#include "avr910.h"
#include "butterfly.h"
#include "usbasp.h"
#include "osuisp2.h"
#include "usbtiny.h"
#include "avr.h"
#include "jtagmkI.h"
#include "jtagmkII.h"

#if defined(WIN32NATIVE)
#define strtok_r( _s, _sep, _lasts ) \
    ( *(_lasts) = strtok( (_s), (_sep) ) )
#endif

int yylex(void);
int yyerror(char * errmsg);

static int assign_pin(int pinno, TOKEN * v, int invert);
static int which_opcode(TOKEN * opcode);
static int parse_cmdbits(OPCODE * op);
 

#line 111 "config_gram.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
    K_READ = 258,
    K_WRITE = 259,
    K_READ_LO = 260,
    K_READ_HI = 261,
    K_WRITE_LO = 262,
    K_WRITE_HI = 263,
    K_LOADPAGE_LO = 264,
    K_LOADPAGE_HI = 265,
    K_LOAD_EXT_ADDR = 266,
    K_WRITEPAGE = 267,
    K_CHIP_ERASE = 268,
    K_PGM_ENABLE = 269,
    K_MEMORY = 270,
    K_PAGE_SIZE = 271,
    K_PAGED = 272,
    K_ARDUINO = 273,
    K_BAUDRATE = 274,
    K_BS2 = 275,
    K_BUFF = 276,
    K_BUSPIRATE = 277,
    K_CHIP_ERASE_DELAY = 278,
    K_DEDICATED = 279,
    K_DEFAULT_PARALLEL = 280,
    K_DEFAULT_PROGRAMMER = 281,
    K_DEFAULT_SERIAL = 282,
    K_DESC = 283,
    K_DEVICECODE = 284,
    K_DRAGON_DW = 285,
    K_DRAGON_HVSP = 286,
    K_DRAGON_ISP = 287,
    K_DRAGON_JTAG = 288,
    K_DRAGON_PDI = 289,
    K_DRAGON_PP = 290,
    K_STK500_DEVCODE = 291,
    K_AVR910_DEVCODE = 292,
    K_EEPROM = 293,
    K_ERRLED = 294,
    K_FLASH = 295,
    K_ID = 296,
    K_IO = 297,
    K_JTAG_MKI = 298,
    K_JTAG_MKII = 299,
    K_JTAG_MKII_AVR32 = 300,
    K_JTAG_MKII_DW = 301,
    K_JTAG_MKII_ISP = 302,
    K_JTAG_MKII_PDI = 303,
    K_LOADPAGE = 304,
    K_MAX_WRITE_DELAY = 305,
    K_MIN_WRITE_DELAY = 306,
    K_MISO = 307,
    K_MOSI = 308,
    K_NUM_PAGES = 309,
    K_NVM_BASE = 310,
    K_OFFSET = 311,
    K_PAGEL = 312,
    K_PAR = 313,
    K_PARALLEL = 314,
    K_PART = 315,
    K_PGMLED = 316,
    K_PROGRAMMER = 317,
    K_PSEUDO = 318,
    K_PWROFF_AFTER_WRITE = 319,
    K_RDYLED = 320,
    K_READBACK_P1 = 321,
    K_READBACK_P2 = 322,
    K_READMEM = 323,
    K_RESET = 324,
    K_RETRY_PULSE = 325,
    K_SERBB = 326,
    K_SERIAL = 327,
    K_SCK = 328,
    K_SIGNATURE = 329,
    K_SIZE = 330,
    K_STK500 = 331,
    K_STK500HVSP = 332,
    K_STK500PP = 333,
    K_STK500V2 = 334,
    K_STK500GENERIC = 335,
    K_STK600 = 336,
    K_STK600HVSP = 337,
    K_STK600PP = 338,
    K_AVR910 = 339,
    K_USBASP = 340,
    K_OSUISP2 = 341,
    K_USBTINY = 342,
    K_BUTTERFLY = 343,
    K_TYPE = 344,
    K_VCC = 345,
    K_VFYLED = 346,
    K_NO = 347,
    K_YES = 348,
    K_TIMEOUT = 349,
    K_STABDELAY = 350,
    K_CMDEXEDELAY = 351,
    K_HVSPCMDEXEDELAY = 352,
    K_SYNCHLOOPS = 353,
    K_BYTEDELAY = 354,
    K_POLLVALUE = 355,
    K_POLLINDEX = 356,
    K_PREDELAY = 357,
    K_POSTDELAY = 358,
    K_POLLMETHOD = 359,
    K_MODE = 360,
    K_DELAY = 361,
    K_BLOCKSIZE = 362,
    K_READSIZE = 363,
    K_HVENTERSTABDELAY = 364,
    K_PROGMODEDELAY = 365,
    K_LATCHCYCLES = 366,
    K_TOGGLEVTG = 367,
    K_POWEROFFDELAY = 368,
    K_RESETDELAYMS = 369,
    K_RESETDELAYUS = 370,
    K_HVLEAVESTABDELAY = 371,
    K_RESETDELAY = 372,
    K_SYNCHCYCLES = 373,
    K_HVCMDEXEDELAY = 374,
    K_CHIPERASEPULSEWIDTH = 375,
    K_CHIPERASEPOLLTIMEOUT = 376,
    K_CHIPERASETIME = 377,
    K_PROGRAMFUSEPULSEWIDTH = 378,
    K_PROGRAMFUSEPOLLTIMEOUT = 379,
    K_PROGRAMLOCKPULSEWIDTH = 380,
    K_PROGRAMLOCKPOLLTIMEOUT = 381,
    K_PP_CONTROLSTACK = 382,
    K_HVSP_CONTROLSTACK = 383,
    K_ALLOWFULLPAGEBITSTREAM = 384,
    K_ENABLEPAGEPROGRAMMING = 385,
    K_HAS_JTAG = 386,
    K_HAS_DW = 387,
    K_HAS_PDI = 388,
    K_HAS_TPI = 389,
    K_IDR = 390,
    K_IS_AVR32 = 391,
    K_RAMPZ = 392,
    K_SPMCR = 393,
    K_EECR = 394,
    K_FLASH_INSTR = 395,
    K_EEPROM_INSTR = 396,
    TKN_COMMA = 397,
    TKN_EQUAL = 398,
    TKN_SEMI = 399,
    TKN_TILDE = 400,
    TKN_NUMBER = 401,
    TKN_STRING = 402,
    TKN_ID = 403
  };
#endif
/* Tokens.  */
#define K_READ 258
#define K_WRITE 259
#define K_READ_LO 260
#define K_READ_HI 261
#define K_WRITE_LO 262
#define K_WRITE_HI 263
#define K_LOADPAGE_LO 264
#define K_LOADPAGE_HI 265
#define K_LOAD_EXT_ADDR 266
#define K_WRITEPAGE 267
#define K_CHIP_ERASE 268
#define K_PGM_ENABLE 269
#define K_MEMORY 270
#define K_PAGE_SIZE 271
#define K_PAGED 272
#define K_ARDUINO 273
#define K_BAUDRATE 274
#define K_BS2 275
#define K_BUFF 276
#define K_BUSPIRATE 277
#define K_CHIP_ERASE_DELAY 278
#define K_DEDICATED 279
#define K_DEFAULT_PARALLEL 280
#define K_DEFAULT_PROGRAMMER 281
#define K_DEFAULT_SERIAL 282
#define K_DESC 283
#define K_DEVICECODE 284
#define K_DRAGON_DW 285
#define K_DRAGON_HVSP 286
#define K_DRAGON_ISP 287
#define K_DRAGON_JTAG 288
#define K_DRAGON_PDI 289
#define K_DRAGON_PP 290
#define K_STK500_DEVCODE 291
#define K_AVR910_DEVCODE 292
#define K_EEPROM 293
#define K_ERRLED 294
#define K_FLASH 295
#define K_ID 296
#define K_IO 297
#define K_JTAG_MKI 298
#define K_JTAG_MKII 299
#define K_JTAG_MKII_AVR32 300
#define K_JTAG_MKII_DW 301
#define K_JTAG_MKII_ISP 302
#define K_JTAG_MKII_PDI 303
#define K_LOADPAGE 304
#define K_MAX_WRITE_DELAY 305
#define K_MIN_WRITE_DELAY 306
#define K_MISO 307
#define K_MOSI 308
#define K_NUM_PAGES 309
#define K_NVM_BASE 310
#define K_OFFSET 311
#define K_PAGEL 312
#define K_PAR 313
#define K_PARALLEL 314
#define K_PART 315
#define K_PGMLED 316
#define K_PROGRAMMER 317
#define K_PSEUDO 318
#define K_PWROFF_AFTER_WRITE 319
#define K_RDYLED 320
#define K_READBACK_P1 321
#define K_READBACK_P2 322
#define K_READMEM 323
#define K_RESET 324
#define K_RETRY_PULSE 325
#define K_SERBB 326
#define K_SERIAL 327
#define K_SCK 328
#define K_SIGNATURE 329
#define K_SIZE 330
#define K_STK500 331
#define K_STK500HVSP 332
#define K_STK500PP 333
#define K_STK500V2 334
#define K_STK500GENERIC 335
#define K_STK600 336
#define K_STK600HVSP 337
#define K_STK600PP 338
#define K_AVR910 339
#define K_USBASP 340
#define K_OSUISP2 341
#define K_USBTINY 342
#define K_BUTTERFLY 343
#define K_TYPE 344
#define K_VCC 345
#define K_VFYLED 346
#define K_NO 347
#define K_YES 348
#define K_TIMEOUT 349
#define K_STABDELAY 350
#define K_CMDEXEDELAY 351
#define K_HVSPCMDEXEDELAY 352
#define K_SYNCHLOOPS 353
#define K_BYTEDELAY 354
#define K_POLLVALUE 355
#define K_POLLINDEX 356
#define K_PREDELAY 357
#define K_POSTDELAY 358
#define K_POLLMETHOD 359
#define K_MODE 360
#define K_DELAY 361
#define K_BLOCKSIZE 362
#define K_READSIZE 363
#define K_HVENTERSTABDELAY 364
#define K_PROGMODEDELAY 365
#define K_LATCHCYCLES 366
#define K_TOGGLEVTG 367
#define K_POWEROFFDELAY 368
#define K_RESETDELAYMS 369
#define K_RESETDELAYUS 370
#define K_HVLEAVESTABDELAY 371
#define K_RESETDELAY 372
#define K_SYNCHCYCLES 373
#define K_HVCMDEXEDELAY 374
#define K_CHIPERASEPULSEWIDTH 375
#define K_CHIPERASEPOLLTIMEOUT 376
#define K_CHIPERASETIME 377
#define K_PROGRAMFUSEPULSEWIDTH 378
#define K_PROGRAMFUSEPOLLTIMEOUT 379
#define K_PROGRAMLOCKPULSEWIDTH 380
#define K_PROGRAMLOCKPOLLTIMEOUT 381
#define K_PP_CONTROLSTACK 382
#define K_HVSP_CONTROLSTACK 383
#define K_ALLOWFULLPAGEBITSTREAM 384
#define K_ENABLEPAGEPROGRAMMING 385
#define K_HAS_JTAG 386
#define K_HAS_DW 387
#define K_HAS_PDI 388
#define K_HAS_TPI 389
#define K_IDR 390
#define K_IS_AVR32 391
#define K_RAMPZ 392
#define K_SPMCR 393
#define K_EECR 394
#define K_FLASH_INSTR 395
#define K_EEPROM_INSTR 396
#define TKN_COMMA 397
#define TKN_EQUAL 398
#define TKN_SEMI 399
#define TKN_TILDE 400
#define TKN_NUMBER 401
#define TKN_STRING 402
#define TKN_ID 403

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 458 "config_gram.c" /* yacc.c:358  */

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
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
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
#  define YYSIZE_T unsigned int
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

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   375

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  149
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  380

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   403

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   237,   237,   238,   242,   243,   248,   250,   252,   258,
     264,   274,   273,   299,   298,   360,   361,   366,   367,   372,
     373,   378,   389,   395,   401,   407,   413,   419,   425,   431,
     437,   443,   449,   455,   461,   467,   473,   479,   485,   491,
     497,   502,   508,   514,   520,   526,   532,   538,   544,   550,
     556,   562,   568,   585,   602,   608,   610,   612,   613,   614,
     615,   616,   617,   619,   621,   623,   624,   625,   626,   627,
     628,   633,   634,   635,   636,   637,   638,   639,   640,   641,
     642,   643,   644,   649,   650,   655,   655,   659,   659,   663,
     663,   667,   674,   681,   691,   698,   705,   716,   758,   800,
     832,   864,   870,   876,   882,   892,   898,   904,   910,   916,
     922,   928,   934,   940,   946,   952,   958,   964,   970,   976,
     982,   988,   994,  1000,  1006,  1012,  1018,  1024,  1030,  1036,
    1042,  1048,  1054,  1060,  1070,  1080,  1090,  1100,  1110,  1120,
    1130,  1136,  1142,  1148,  1154,  1160,  1170,  1189,  1213,  1212,
    1224,  1241,  1241,  1246,  1247,  1252,  1258,  1265,  1271,  1277,
    1283,  1289,  1295,  1301,  1307,  1314,  1320,  1326,  1332,  1338,
    1345
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_READ", "K_WRITE", "K_READ_LO",
  "K_READ_HI", "K_WRITE_LO", "K_WRITE_HI", "K_LOADPAGE_LO",
  "K_LOADPAGE_HI", "K_LOAD_EXT_ADDR", "K_WRITEPAGE", "K_CHIP_ERASE",
  "K_PGM_ENABLE", "K_MEMORY", "K_PAGE_SIZE", "K_PAGED", "K_ARDUINO",
  "K_BAUDRATE", "K_BS2", "K_BUFF", "K_BUSPIRATE", "K_CHIP_ERASE_DELAY",
  "K_DEDICATED", "K_DEFAULT_PARALLEL", "K_DEFAULT_PROGRAMMER",
  "K_DEFAULT_SERIAL", "K_DESC", "K_DEVICECODE", "K_DRAGON_DW",
  "K_DRAGON_HVSP", "K_DRAGON_ISP", "K_DRAGON_JTAG", "K_DRAGON_PDI",
  "K_DRAGON_PP", "K_STK500_DEVCODE", "K_AVR910_DEVCODE", "K_EEPROM",
  "K_ERRLED", "K_FLASH", "K_ID", "K_IO", "K_JTAG_MKI", "K_JTAG_MKII",
  "K_JTAG_MKII_AVR32", "K_JTAG_MKII_DW", "K_JTAG_MKII_ISP",
  "K_JTAG_MKII_PDI", "K_LOADPAGE", "K_MAX_WRITE_DELAY",
  "K_MIN_WRITE_DELAY", "K_MISO", "K_MOSI", "K_NUM_PAGES", "K_NVM_BASE",
  "K_OFFSET", "K_PAGEL", "K_PAR", "K_PARALLEL", "K_PART", "K_PGMLED",
  "K_PROGRAMMER", "K_PSEUDO", "K_PWROFF_AFTER_WRITE", "K_RDYLED",
  "K_READBACK_P1", "K_READBACK_P2", "K_READMEM", "K_RESET",
  "K_RETRY_PULSE", "K_SERBB", "K_SERIAL", "K_SCK", "K_SIGNATURE", "K_SIZE",
  "K_STK500", "K_STK500HVSP", "K_STK500PP", "K_STK500V2",
  "K_STK500GENERIC", "K_STK600", "K_STK600HVSP", "K_STK600PP", "K_AVR910",
  "K_USBASP", "K_OSUISP2", "K_USBTINY", "K_BUTTERFLY", "K_TYPE", "K_VCC",
  "K_VFYLED", "K_NO", "K_YES", "K_TIMEOUT", "K_STABDELAY", "K_CMDEXEDELAY",
  "K_HVSPCMDEXEDELAY", "K_SYNCHLOOPS", "K_BYTEDELAY", "K_POLLVALUE",
  "K_POLLINDEX", "K_PREDELAY", "K_POSTDELAY", "K_POLLMETHOD", "K_MODE",
  "K_DELAY", "K_BLOCKSIZE", "K_READSIZE", "K_HVENTERSTABDELAY",
  "K_PROGMODEDELAY", "K_LATCHCYCLES", "K_TOGGLEVTG", "K_POWEROFFDELAY",
  "K_RESETDELAYMS", "K_RESETDELAYUS", "K_HVLEAVESTABDELAY", "K_RESETDELAY",
  "K_SYNCHCYCLES", "K_HVCMDEXEDELAY", "K_CHIPERASEPULSEWIDTH",
  "K_CHIPERASEPOLLTIMEOUT", "K_CHIPERASETIME", "K_PROGRAMFUSEPULSEWIDTH",
  "K_PROGRAMFUSEPOLLTIMEOUT", "K_PROGRAMLOCKPULSEWIDTH",
  "K_PROGRAMLOCKPOLLTIMEOUT", "K_PP_CONTROLSTACK", "K_HVSP_CONTROLSTACK",
  "K_ALLOWFULLPAGEBITSTREAM", "K_ENABLEPAGEPROGRAMMING", "K_HAS_JTAG",
  "K_HAS_DW", "K_HAS_PDI", "K_HAS_TPI", "K_IDR", "K_IS_AVR32", "K_RAMPZ",
  "K_SPMCR", "K_EECR", "K_FLASH_INSTR", "K_EEPROM_INSTR", "TKN_COMMA",
  "TKN_EQUAL", "TKN_SEMI", "TKN_TILDE", "TKN_NUMBER", "TKN_STRING",
  "TKN_ID", "$accept", "configuration", "config", "def", "prog_def", "$@1",
  "part_def", "$@2", "string_list", "num_list", "prog_parms", "prog_parm",
  "opcode", "part_parms", "reset_disposition", "parallel_modes",
  "retry_lines", "part_parm", "$@3", "yesno", "mem_specs", "mem_spec", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403
};
# endif

#define YYPACT_NINF -191

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-191)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -22,  -133,  -126,  -112,  -191,  -191,    43,   -22,  -191,  -100,
     -99,  -101,   -98,   -97,    59,   207,  -191,  -191,  -191,  -191,
     -96,   -93,   -92,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,   -94,   -89,   -88,   -87,   -86,
     -85,   -83,   -82,   -68,   -67,   -66,   -65,   -60,   -59,   -58,
     -57,   -54,   -53,   -52,   -49,   -46,   -44,   -42,   -41,   -40,
     -39,   -38,   -37,   -36,   -35,   -33,   -32,   -31,   -30,   -28,
     -26,   -24,   -23,   -21,   -20,   -19,   -17,   -16,   -13,   -11,
      -9,    -8,    -7,    -6,    -5,    -3,    -2,    -1,     0,     1,
       2,     3,     4,     5,    59,   -63,     6,     7,     8,     9,
      21,    22,    23,    24,    58,    75,    76,    78,    79,    80,
     207,    81,  -191,  -191,  -191,  -191,   -25,    56,    77,    83,
      84,    85,    86,    88,    90,   -51,   -18,   -62,   -84,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   101,   103,
     106,   107,   109,   111,   112,   115,   116,   117,   119,   123,
     124,   125,   127,   128,   131,   132,   133,   135,   136,   136,
     -84,   -84,   -84,   -84,   -84,   -84,   137,   -84,   138,   139,
     140,   136,   136,   141,   143,  -191,   144,   136,   142,  -132,
     141,  -130,  -127,  -125,  -123,  -120,  -118,   281,   136,  -116,
     147,  -191,   200,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,   146,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,   -95,   -95,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,   -95,   -95,  -191,
     151,  -191,  -191,   -95,  -191,   148,  -191,   151,   149,  -191,
     154,  -191,   156,  -191,   158,  -191,   163,  -191,   164,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,   -95,
     171,  -191,  -191,    89,   175,   176,   177,   178,   179,   180,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   200,
     196,   197,   198,   199,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,   201,   -84,   202,   203,   204,   205,   -84,   208,
     209,   210,   224,   225,   226,   227,   228,   141,   231,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,   151,  -191
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,    13,    11,     0,     3,     4,     0,
       0,     0,     0,     0,     0,     0,     1,     5,     6,     7,
       0,     0,     0,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      12,     0,     9,     8,    10,   148,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    83,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,     0,   103,   101,    92,    93,    94,    95,    91,
     144,   102,    88,   152,   151,   146,    87,    85,    86,   104,
      89,    90,   147,   145,     0,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   132,   125,   126,   127,   128,
     129,   130,   131,    17,    97,    98,   138,   139,   133,   134,
     135,   136,   140,   137,   141,   142,   143,    99,   100,    15,
     150,    84,    54,    53,    51,     0,    59,    21,     0,    58,
       0,    57,     0,    61,     0,    60,     0,    55,     0,    56,
      29,    30,    45,    46,    47,    48,    49,    50,    39,    40,
      41,    42,    43,    44,    22,    23,    24,    26,    27,    25,
      28,    31,    32,    33,    34,    35,    36,    37,    38,    52,
       0,    62,    20,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   149,
       0,     0,     0,     0,    67,    66,    65,    69,    68,    63,
      64,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   153,
      96,    18,    16,   157,   155,   161,   160,   158,   159,   162,
     163,   164,   156,   169,   165,   166,   167,   168,   170,   154
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -191,  -191,  -191,    52,  -191,  -191,  -191,  -191,  -179,   -79,
    -191,    15,  -190,  -191,  -191,  -191,  -191,   247,  -191,  -128,
    -191,  -102
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    15,    10,    14,   260,   244,
     110,   111,    93,    94,   209,   205,   212,    95,   192,   206,
     329,   330
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     213,   267,   328,     1,     2,     3,   207,   210,   203,   204,
      11,   211,   202,   265,   266,   268,   269,    12,   270,   271,
     272,   273,   274,   275,   208,   276,   277,   278,   279,   310,
     311,    13,   246,   247,   248,   249,   250,   251,     4,   253,
       5,   203,   204,    16,    18,    19,    20,   332,   112,    21,
      22,   113,   114,   115,   116,   117,   118,   119,   120,    17,
     121,   122,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,   123,   124,   125,   126,    36,
     245,   175,    37,   127,   128,   129,   130,    38,    39,   131,
     132,   133,   257,   258,   134,    40,    41,   135,   263,   136,
      42,   137,   138,   139,   140,   141,   142,   143,   144,   309,
     145,   146,   147,   148,    43,   149,    44,   150,    45,   151,
     152,   193,   153,   154,   155,   190,   156,   157,    46,    47,
     158,    48,   159,    49,   160,   161,   162,   163,   164,   328,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   176,
     177,   178,   179,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,   180,   181,   182,   183,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,   378,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,   184,   194,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,   364,   313,   314,   185,   186,
     369,   187,   188,   189,   195,   191,    96,   358,    97,   196,
     197,   198,   342,   199,   200,    98,   201,   214,   215,   216,
     217,   218,   219,   220,   221,   222,    99,   223,   100,   224,
     315,   316,   225,   226,   317,   227,   318,   228,   229,   101,
     102,   230,   231,   232,   319,   233,   320,   321,   103,   234,
     235,   236,   104,   237,   238,   322,   105,   239,   240,   241,
     106,   242,   243,   252,   254,   255,   256,   261,   259,   264,
     262,   312,   331,   333,   334,   335,   107,   108,   109,   280,
     336,   323,   337,   281,   338,   324,   325,   326,   327,   339,
     340,   282,   283,   284,   285,   286,   287,   341,   343,   344,
     345,   346,   347,   348,   288,   289,   290,   291,   292,   293,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   294,
     359,   174,     0,   360,   361,     0,   362,   363,   365,   366,
     367,   368,   295,     0,   370,   371,   372,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     373,   374,   375,   376,   377,   379
};

static const yytype_int16 yycheck[] =
{
     128,   180,   192,    25,    26,    27,    24,    69,    92,    93,
     143,    73,    63,   145,   146,   145,   146,   143,   145,   146,
     145,   146,   145,   146,    42,   145,   146,   145,   146,   145,
     146,   143,   160,   161,   162,   163,   164,   165,    60,   167,
      62,    92,    93,     0,   144,   144,   147,   142,   144,   147,
     147,   144,   144,   147,   143,   143,   143,   143,   143,     7,
     143,   143,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,   143,   143,   143,   143,    20,
     159,   144,    23,   143,   143,   143,   143,    28,    29,   143,
     143,   143,   171,   172,   143,    36,    37,   143,   177,   143,
      41,   143,   143,   143,   143,   143,   143,   143,   143,   188,
     143,   143,   143,   143,    55,   143,    57,   143,    59,   143,
     143,   146,   143,   143,   143,   110,   143,   143,    69,    70,
     143,    72,   143,    74,   143,   143,   143,   143,   143,   329,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   143,   143,   143,   143,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   357,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   143,   146,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   343,    16,    17,   143,   143,
     348,   143,   143,   143,   147,   144,    19,   329,    21,   146,
     146,   146,   143,   147,   146,    28,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,    39,   146,    41,   146,
      50,    51,   146,   146,    54,   146,    56,   146,   146,    52,
      53,   146,   146,   146,    64,   146,    66,    67,    61,   146,
     146,   146,    65,   146,   146,    75,    69,   146,   146,   146,
      73,   146,   146,   146,   146,   146,   146,   144,   147,   147,
     146,   144,   146,   142,   146,   146,    89,    90,    91,    18,
     146,   101,   146,    22,   146,   105,   106,   107,   108,   146,
     146,    30,    31,    32,    33,    34,    35,   146,   143,   143,
     143,   143,   143,   143,    43,    44,    45,    46,    47,    48,
     143,   143,   143,   143,   143,   143,   143,   143,   143,    58,
     144,    94,    -1,   146,   146,    -1,   147,   146,   146,   146,
     146,   146,    71,    -1,   146,   146,   146,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
     146,   146,   146,   146,   146,   144
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    25,    26,    27,    60,    62,   150,   151,   152,   153,
     155,   143,   143,   143,   156,   154,     0,   152,   144,   144,
     147,   147,   147,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    20,    23,    28,    29,
      36,    37,    41,    55,    57,    59,    69,    70,    72,    74,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   161,   162,   166,    19,    21,    28,    39,
      41,    52,    53,    61,    65,    69,    73,    89,    90,    91,
     159,   160,   144,   144,   144,   147,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   166,   144,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     160,   144,   167,   146,   146,   147,   146,   146,   146,   147,
     146,   146,    63,    92,    93,   164,   168,    24,    42,   163,
      69,    73,   165,   168,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   158,   158,   168,   168,   168,   168,
     168,   168,   146,   168,   146,   146,   146,   158,   158,   147,
     157,   144,   146,   158,   147,   145,   146,   157,   145,   146,
     145,   146,   145,   146,   145,   146,   145,   146,   145,   146,
      18,    22,    30,    31,    32,    33,    34,    35,    43,    44,
      45,    46,    47,    48,    58,    71,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,   158,
     145,   146,   144,    16,    17,    50,    51,    54,    56,    64,
      66,    67,    75,   101,   105,   106,   107,   108,   161,   169,
     170,   146,   142,   142,   146,   146,   146,   146,   146,   146,
     146,   146,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   170,   144,
     146,   146,   147,   146,   168,   146,   146,   146,   146,   168,
     146,   146,   146,   146,   146,   146,   146,   146,   157,   144
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   149,   150,   150,   151,   151,   152,   152,   152,   152,
     152,   154,   153,   156,   155,   157,   157,   158,   158,   159,
     159,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   162,   162,   163,   163,   164,   164,   165,
     165,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   167,   166,
     166,   168,   168,   169,   169,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     2,     2,     4,     4,
       4,     0,     3,     0,     3,     1,     3,     1,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     4,     4,     4,     4,     4,     4,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     5,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       3,     1,     1,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
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
  unsigned long int yylno = yyrline[yyrule];
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
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
            /* Fall through.  */
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

  return yystpcpy (yyres, yystr) - yyres;
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
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
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
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
| yyreduce -- Do a reduction.  |
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
        case 8:
#line 252 "config_gram.y" /* yacc.c:1646  */
    {
    strncpy(default_programmer, (yyvsp[-1])->value.string, MAX_STR_CONST);
    default_programmer[MAX_STR_CONST-1] = 0;
    free_token((yyvsp[-1]));
  }
#line 1832 "config_gram.c" /* yacc.c:1646  */
    break;

  case 9:
#line 258 "config_gram.y" /* yacc.c:1646  */
    {
    strncpy(default_parallel, (yyvsp[-1])->value.string, PATH_MAX);
    default_parallel[PATH_MAX-1] = 0;
    free_token((yyvsp[-1]));
  }
#line 1842 "config_gram.c" /* yacc.c:1646  */
    break;

  case 10:
#line 264 "config_gram.y" /* yacc.c:1646  */
    {
    strncpy(default_serial, (yyvsp[-1])->value.string, PATH_MAX);
    default_serial[PATH_MAX-1] = 0;
    free_token((yyvsp[-1]));
  }
#line 1852 "config_gram.c" /* yacc.c:1646  */
    break;

  case 11:
#line 274 "config_gram.y" /* yacc.c:1646  */
    { current_prog = pgm_new();
      strcpy(current_prog->config_file, infile);
      current_prog->lineno = lineno;
    }
#line 1861 "config_gram.c" /* yacc.c:1646  */
    break;

  case 12:
#line 279 "config_gram.y" /* yacc.c:1646  */
    { 
      if (lsize(current_prog->id) == 0) {
        fprintf(stderr,
                "%s: error at %s:%d: required parameter id not specified\n",
                progname, infile, lineno);
        exit(1);
      }
      if (current_prog->type[0] == 0) {
        fprintf(stderr, "%s: error at %s:%d: programmer type not specified\n",
                progname, infile, lineno);
        exit(1);
      }
      PUSH(programmers, current_prog); 
      current_prog = NULL; 
    }
#line 1881 "config_gram.c" /* yacc.c:1646  */
    break;

  case 13:
#line 299 "config_gram.y" /* yacc.c:1646  */
    {
      current_part = avr_new_part();
      strcpy(current_part->config_file, infile);
      current_part->lineno = lineno;
    }
#line 1891 "config_gram.c" /* yacc.c:1646  */
    break;

  case 14:
#line 305 "config_gram.y" /* yacc.c:1646  */
    { 
      LNODEID ln;
      AVRMEM * m;

      if (current_part->id[0] == 0) {
        fprintf(stderr,
                "%s: error at %s:%d: required parameter id not specified\n",
                progname, infile, lineno);
        exit(1);
      }

      /*
       * perform some sanity checking, and compute the number of bits
       * to shift a page for constructing the page address for
       * page-addressed memories.
       */
      for (ln=lfirst(current_part->mem); ln; ln=lnext(ln)) {
        m = ldata(ln);
        if (m->paged) {
          if (m->page_size == 0) {
            fprintf(stderr, 
                    "%s: error at %s:%d: must specify page_size for paged "
                    "memory\n",
                    progname, infile, lineno);
            exit(1);
          }
          if (m->num_pages == 0) {
            fprintf(stderr, 
                    "%s: error at %s:%d: must specify num_pages for paged "
                    "memory\n",
                    progname, infile, lineno);
            exit(1);
          }
          if (m->size != m->page_size * m->num_pages) {
            fprintf(stderr, 
                    "%s: error at %s:%d: page size (%u) * num_pages (%u) = "
                    "%u does not match memory size (%u)\n",
                    progname, infile, lineno,
                    m->page_size, 
                    m->num_pages, 
                    m->page_size * m->num_pages,
                    m->size);
            exit(1);
          }

        }
      }

      PUSH(part_list, current_part); 
      current_part = NULL; 
    }
#line 1947 "config_gram.c" /* yacc.c:1646  */
    break;

  case 15:
#line 360 "config_gram.y" /* yacc.c:1646  */
    { ladd(string_list, (yyvsp[0])); }
#line 1953 "config_gram.c" /* yacc.c:1646  */
    break;

  case 16:
#line 361 "config_gram.y" /* yacc.c:1646  */
    { ladd(string_list, (yyvsp[0])); }
#line 1959 "config_gram.c" /* yacc.c:1646  */
    break;

  case 17:
#line 366 "config_gram.y" /* yacc.c:1646  */
    { ladd(number_list, (yyvsp[0])); }
#line 1965 "config_gram.c" /* yacc.c:1646  */
    break;

  case 18:
#line 367 "config_gram.y" /* yacc.c:1646  */
    { ladd(number_list, (yyvsp[0])); }
#line 1971 "config_gram.c" /* yacc.c:1646  */
    break;

  case 21:
#line 378 "config_gram.y" /* yacc.c:1646  */
    {
    { 
      TOKEN * t;
      while (lsize(string_list)) {
        t = lrmv_n(string_list, 1);
        ladd(current_prog->id, dup_string(t->value.string));
        free_token(t);
      }
    }
  }
#line 1986 "config_gram.c" /* yacc.c:1646  */
    break;

  case 22:
#line 389 "config_gram.y" /* yacc.c:1646  */
    {
    { 
      par_initpgm(current_prog);
    }
  }
#line 1996 "config_gram.c" /* yacc.c:1646  */
    break;

  case 23:
#line 395 "config_gram.y" /* yacc.c:1646  */
    {
    {
      serbb_initpgm(current_prog);
    }
  }
#line 2006 "config_gram.c" /* yacc.c:1646  */
    break;

  case 24:
#line 401 "config_gram.y" /* yacc.c:1646  */
    {
    { 
      stk500_initpgm(current_prog);
    }
  }
#line 2016 "config_gram.c" /* yacc.c:1646  */
    break;

  case 25:
#line 407 "config_gram.y" /* yacc.c:1646  */
    {
    {
      stk500v2_initpgm(current_prog);
    }
  }
#line 2026 "config_gram.c" /* yacc.c:1646  */
    break;

  case 26:
#line 413 "config_gram.y" /* yacc.c:1646  */
    {
    {
      stk500hvsp_initpgm(current_prog);
    }
  }
#line 2036 "config_gram.c" /* yacc.c:1646  */
    break;

  case 27:
#line 419 "config_gram.y" /* yacc.c:1646  */
    {
    {
      stk500pp_initpgm(current_prog);
    }
  }
#line 2046 "config_gram.c" /* yacc.c:1646  */
    break;

  case 28:
#line 425 "config_gram.y" /* yacc.c:1646  */
    {
    {
      stk500generic_initpgm(current_prog);
    }
  }
#line 2056 "config_gram.c" /* yacc.c:1646  */
    break;

  case 29:
#line 431 "config_gram.y" /* yacc.c:1646  */
    {
    { 
      arduino_initpgm(current_prog);
    }
  }
#line 2066 "config_gram.c" /* yacc.c:1646  */
    break;

  case 30:
#line 437 "config_gram.y" /* yacc.c:1646  */
    {
    {
      buspirate_initpgm(current_prog);
    }
  }
#line 2076 "config_gram.c" /* yacc.c:1646  */
    break;

  case 31:
#line 443 "config_gram.y" /* yacc.c:1646  */
    {
    {
      stk600_initpgm(current_prog);
    }
  }
#line 2086 "config_gram.c" /* yacc.c:1646  */
    break;

  case 32:
#line 449 "config_gram.y" /* yacc.c:1646  */
    {
    {
      stk600hvsp_initpgm(current_prog);
    }
  }
#line 2096 "config_gram.c" /* yacc.c:1646  */
    break;

  case 33:
#line 455 "config_gram.y" /* yacc.c:1646  */
    {
    {
      stk600pp_initpgm(current_prog);
    }
  }
#line 2106 "config_gram.c" /* yacc.c:1646  */
    break;

  case 34:
#line 461 "config_gram.y" /* yacc.c:1646  */
    {
    { 
      avr910_initpgm(current_prog);
    }
  }
#line 2116 "config_gram.c" /* yacc.c:1646  */
    break;

  case 35:
#line 467 "config_gram.y" /* yacc.c:1646  */
    {
    {
      usbasp_initpgm(current_prog);
    }
  }
#line 2126 "config_gram.c" /* yacc.c:1646  */
    break;

  case 36:
#line 473 "config_gram.y" /* yacc.c:1646  */
    {
    {
      osuisp2_initpgm(current_prog);
    }
  }
#line 2136 "config_gram.c" /* yacc.c:1646  */
    break;

  case 37:
#line 479 "config_gram.y" /* yacc.c:1646  */
    {
    {
      usbtiny_initpgm(current_prog);
    }
  }
#line 2146 "config_gram.c" /* yacc.c:1646  */
    break;

  case 38:
#line 485 "config_gram.y" /* yacc.c:1646  */
    {
    { 
      butterfly_initpgm(current_prog);
    }
  }
#line 2156 "config_gram.c" /* yacc.c:1646  */
    break;

  case 39:
#line 491 "config_gram.y" /* yacc.c:1646  */
    {
    {
      jtagmkI_initpgm(current_prog);
    }
  }
#line 2166 "config_gram.c" /* yacc.c:1646  */
    break;

  case 40:
#line 497 "config_gram.y" /* yacc.c:1646  */
    {
    {
      jtagmkII_initpgm(current_prog);
    }
  }
#line 2176 "config_gram.c" /* yacc.c:1646  */
    break;

  case 41:
#line 502 "config_gram.y" /* yacc.c:1646  */
    {
    {
      jtagmkII_avr32_initpgm(current_prog);
    }
  }
#line 2186 "config_gram.c" /* yacc.c:1646  */
    break;

  case 42:
#line 508 "config_gram.y" /* yacc.c:1646  */
    {
    {
      jtagmkII_dw_initpgm(current_prog);
    }
  }
#line 2196 "config_gram.c" /* yacc.c:1646  */
    break;

  case 43:
#line 514 "config_gram.y" /* yacc.c:1646  */
    {
    {
      stk500v2_jtagmkII_initpgm(current_prog);
    }
  }
#line 2206 "config_gram.c" /* yacc.c:1646  */
    break;

  case 44:
#line 520 "config_gram.y" /* yacc.c:1646  */
    {
    {
      jtagmkII_pdi_initpgm(current_prog);
    }
  }
#line 2216 "config_gram.c" /* yacc.c:1646  */
    break;

  case 45:
#line 526 "config_gram.y" /* yacc.c:1646  */
    {
    {
      jtagmkII_dragon_dw_initpgm(current_prog);
    }
  }
#line 2226 "config_gram.c" /* yacc.c:1646  */
    break;

  case 46:
#line 532 "config_gram.y" /* yacc.c:1646  */
    {
    {
      stk500v2_dragon_hvsp_initpgm(current_prog);
    }
  }
#line 2236 "config_gram.c" /* yacc.c:1646  */
    break;

  case 47:
#line 538 "config_gram.y" /* yacc.c:1646  */
    {
    {
      stk500v2_dragon_isp_initpgm(current_prog);
    }
  }
#line 2246 "config_gram.c" /* yacc.c:1646  */
    break;

  case 48:
#line 544 "config_gram.y" /* yacc.c:1646  */
    {
    {
      jtagmkII_dragon_initpgm(current_prog);
    }
  }
#line 2256 "config_gram.c" /* yacc.c:1646  */
    break;

  case 49:
#line 550 "config_gram.y" /* yacc.c:1646  */
    {
    {
      jtagmkII_dragon_pdi_initpgm(current_prog);
    }
  }
#line 2266 "config_gram.c" /* yacc.c:1646  */
    break;

  case 50:
#line 556 "config_gram.y" /* yacc.c:1646  */
    {
    {
      stk500v2_dragon_pp_initpgm(current_prog);
    }
  }
#line 2276 "config_gram.c" /* yacc.c:1646  */
    break;

  case 51:
#line 562 "config_gram.y" /* yacc.c:1646  */
    {
    strncpy(current_prog->desc, (yyvsp[0])->value.string, PGM_DESCLEN);
    current_prog->desc[PGM_DESCLEN-1] = 0;
    free_token((yyvsp[0]));
  }
#line 2286 "config_gram.c" /* yacc.c:1646  */
    break;

  case 52:
#line 568 "config_gram.y" /* yacc.c:1646  */
    {
    { 
      TOKEN * t;
      int pin;

      current_prog->pinno[PPI_AVR_VCC] = 0;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
        pin = t->value.number;
        current_prog->pinno[PPI_AVR_VCC] |= (1 << pin);

        free_token(t);
      }
    }
  }
#line 2307 "config_gram.c" /* yacc.c:1646  */
    break;

  case 53:
#line 585 "config_gram.y" /* yacc.c:1646  */
    {
    { 
      TOKEN * t;
      int pin;

      current_prog->pinno[PPI_AVR_BUFF] = 0;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
        pin = t->value.number;
        current_prog->pinno[PPI_AVR_BUFF] |= (1 << pin);

        free_token(t);
      }
    }
  }
#line 2328 "config_gram.c" /* yacc.c:1646  */
    break;

  case 54:
#line 602 "config_gram.y" /* yacc.c:1646  */
    {
    {
      current_prog->baudrate = (yyvsp[0])->value.number;
    }
  }
#line 2338 "config_gram.c" /* yacc.c:1646  */
    break;

  case 55:
#line 608 "config_gram.y" /* yacc.c:1646  */
    { free_token((yyvsp[-2])); 
                                  assign_pin(PIN_AVR_RESET, (yyvsp[0]), 0); }
#line 2345 "config_gram.c" /* yacc.c:1646  */
    break;

  case 56:
#line 610 "config_gram.y" /* yacc.c:1646  */
    { free_token((yyvsp[-2])); 
                                  assign_pin(PIN_AVR_SCK, (yyvsp[0]), 0); }
#line 2352 "config_gram.c" /* yacc.c:1646  */
    break;

  case 57:
#line 612 "config_gram.y" /* yacc.c:1646  */
    { assign_pin(PIN_AVR_MOSI, (yyvsp[0]), 0); }
#line 2358 "config_gram.c" /* yacc.c:1646  */
    break;

  case 58:
#line 613 "config_gram.y" /* yacc.c:1646  */
    { assign_pin(PIN_AVR_MISO, (yyvsp[0]), 0); }
#line 2364 "config_gram.c" /* yacc.c:1646  */
    break;

  case 59:
#line 614 "config_gram.y" /* yacc.c:1646  */
    { assign_pin(PIN_LED_ERR, (yyvsp[0]), 0); }
#line 2370 "config_gram.c" /* yacc.c:1646  */
    break;

  case 60:
#line 615 "config_gram.y" /* yacc.c:1646  */
    { assign_pin(PIN_LED_RDY, (yyvsp[0]), 0); }
#line 2376 "config_gram.c" /* yacc.c:1646  */
    break;

  case 61:
#line 616 "config_gram.y" /* yacc.c:1646  */
    { assign_pin(PIN_LED_PGM, (yyvsp[0]), 0); }
#line 2382 "config_gram.c" /* yacc.c:1646  */
    break;

  case 62:
#line 617 "config_gram.y" /* yacc.c:1646  */
    { assign_pin(PIN_LED_VFY, (yyvsp[0]), 0); }
#line 2388 "config_gram.c" /* yacc.c:1646  */
    break;

  case 63:
#line 619 "config_gram.y" /* yacc.c:1646  */
    { free_token((yyvsp[-3])); 
                                  assign_pin(PIN_AVR_RESET, (yyvsp[0]), 1); }
#line 2395 "config_gram.c" /* yacc.c:1646  */
    break;

  case 64:
#line 621 "config_gram.y" /* yacc.c:1646  */
    { free_token((yyvsp[-3])); 
                                  assign_pin(PIN_AVR_SCK, (yyvsp[0]), 1); }
#line 2402 "config_gram.c" /* yacc.c:1646  */
    break;

  case 65:
#line 623 "config_gram.y" /* yacc.c:1646  */
    { assign_pin(PIN_AVR_MOSI, (yyvsp[0]), 1); }
#line 2408 "config_gram.c" /* yacc.c:1646  */
    break;

  case 66:
#line 624 "config_gram.y" /* yacc.c:1646  */
    { assign_pin(PIN_AVR_MISO, (yyvsp[0]), 1); }
#line 2414 "config_gram.c" /* yacc.c:1646  */
    break;

  case 67:
#line 625 "config_gram.y" /* yacc.c:1646  */
    { assign_pin(PIN_LED_ERR, (yyvsp[0]), 1); }
#line 2420 "config_gram.c" /* yacc.c:1646  */
    break;

  case 68:
#line 626 "config_gram.y" /* yacc.c:1646  */
    { assign_pin(PIN_LED_RDY, (yyvsp[0]), 1); }
#line 2426 "config_gram.c" /* yacc.c:1646  */
    break;

  case 69:
#line 627 "config_gram.y" /* yacc.c:1646  */
    { assign_pin(PIN_LED_PGM, (yyvsp[0]), 1); }
#line 2432 "config_gram.c" /* yacc.c:1646  */
    break;

  case 70:
#line 628 "config_gram.y" /* yacc.c:1646  */
    { assign_pin(PIN_LED_VFY, (yyvsp[0]), 1); }
#line 2438 "config_gram.c" /* yacc.c:1646  */
    break;

  case 91:
#line 668 "config_gram.y" /* yacc.c:1646  */
    {
      strncpy(current_part->id, (yyvsp[0])->value.string, AVR_IDLEN);
      current_part->id[AVR_IDLEN-1] = 0;
      free_token((yyvsp[0]));
    }
#line 2448 "config_gram.c" /* yacc.c:1646  */
    break;

  case 92:
#line 675 "config_gram.y" /* yacc.c:1646  */
    {
      strncpy(current_part->desc, (yyvsp[0])->value.string, AVR_DESCLEN);
      current_part->desc[AVR_DESCLEN-1] = 0;
      free_token((yyvsp[0]));
    }
#line 2458 "config_gram.c" /* yacc.c:1646  */
    break;

  case 93:
#line 681 "config_gram.y" /* yacc.c:1646  */
    {
    {
      fprintf(stderr, 
              "%s: error at %s:%d: devicecode is deprecated, use "
              "stk500_devcode instead\n",
              progname, infile, lineno);
      exit(1);
    }
  }
#line 2472 "config_gram.c" /* yacc.c:1646  */
    break;

  case 94:
#line 691 "config_gram.y" /* yacc.c:1646  */
    {
    {
      current_part->stk500_devcode = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
  }
#line 2483 "config_gram.c" /* yacc.c:1646  */
    break;

  case 95:
#line 698 "config_gram.y" /* yacc.c:1646  */
    {
    {
      current_part->avr910_devcode = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
  }
#line 2494 "config_gram.c" /* yacc.c:1646  */
    break;

  case 96:
#line 705 "config_gram.y" /* yacc.c:1646  */
    {
    {
      current_part->signature[0] = (yyvsp[-2])->value.number;
      current_part->signature[1] = (yyvsp[-1])->value.number;
      current_part->signature[2] = (yyvsp[0])->value.number;
      free_token((yyvsp[-2]));
      free_token((yyvsp[-1]));
      free_token((yyvsp[0]));
    }
  }
#line 2509 "config_gram.c" /* yacc.c:1646  */
    break;

  case 97:
#line 716 "config_gram.y" /* yacc.c:1646  */
    {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      if (current_part->ctl_stack_type != CTL_STACK_NONE)
	{
	  fprintf(stderr,
		  "%s: error at line %d of %s: "
		  "control stack already defined\n",
		  progname, lineno, infile);
	  exit(1);
	}

      current_part->ctl_stack_type = CTL_STACK_PP;
      nbytes = 0;
      ok = 1;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < CTL_STACK_SIZE)
	  {
	    current_part->controlstack[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in control stack\n",
                  progname, lineno, infile);
        }
    }
  }
#line 2555 "config_gram.c" /* yacc.c:1646  */
    break;

  case 98:
#line 758 "config_gram.y" /* yacc.c:1646  */
    {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      if (current_part->ctl_stack_type != CTL_STACK_NONE)
	{
	  fprintf(stderr,
		  "%s: error at line %d of %s: "
		  "control stack already defined\n",
		  progname, lineno, infile);
	  exit(1);
	}

      current_part->ctl_stack_type = CTL_STACK_HVSP;
      nbytes = 0;
      ok = 1;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < CTL_STACK_SIZE)
	  {
	    current_part->controlstack[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in control stack\n",
                  progname, lineno, infile);
        }
    }
  }
#line 2601 "config_gram.c" /* yacc.c:1646  */
    break;

  case 99:
#line 800 "config_gram.y" /* yacc.c:1646  */
    {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      nbytes = 0;
      ok = 1;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < FLASH_INSTR_SIZE)
	  {
	    current_part->flash_instr[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in flash instructions\n",
                  progname, lineno, infile);
        }
    }
  }
#line 2637 "config_gram.c" /* yacc.c:1646  */
    break;

  case 100:
#line 832 "config_gram.y" /* yacc.c:1646  */
    {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      nbytes = 0;
      ok = 1;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < EEPROM_INSTR_SIZE)
	  {
	    current_part->eeprom_instr[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in EEPROM instructions\n",
                  progname, lineno, infile);
        }
    }
  }
#line 2673 "config_gram.c" /* yacc.c:1646  */
    break;

  case 101:
#line 865 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->chip_erase_delay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2682 "config_gram.c" /* yacc.c:1646  */
    break;

  case 102:
#line 871 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->pagel = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2691 "config_gram.c" /* yacc.c:1646  */
    break;

  case 103:
#line 877 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->bs2 = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2700 "config_gram.c" /* yacc.c:1646  */
    break;

  case 104:
#line 883 "config_gram.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0])->primary == K_DEDICATED)
        current_part->reset_disposition = RESET_DEDICATED;
      else if ((yyvsp[0])->primary == K_IO)
        current_part->reset_disposition = RESET_IO;

      free_tokens(2, (yyvsp[-2]), (yyvsp[0]));
    }
#line 2713 "config_gram.c" /* yacc.c:1646  */
    break;

  case 105:
#line 893 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->timeout = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2722 "config_gram.c" /* yacc.c:1646  */
    break;

  case 106:
#line 899 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->stabdelay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2731 "config_gram.c" /* yacc.c:1646  */
    break;

  case 107:
#line 905 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->cmdexedelay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2740 "config_gram.c" /* yacc.c:1646  */
    break;

  case 108:
#line 911 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->hvspcmdexedelay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2749 "config_gram.c" /* yacc.c:1646  */
    break;

  case 109:
#line 917 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->synchloops = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2758 "config_gram.c" /* yacc.c:1646  */
    break;

  case 110:
#line 923 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->bytedelay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2767 "config_gram.c" /* yacc.c:1646  */
    break;

  case 111:
#line 929 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->pollvalue = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2776 "config_gram.c" /* yacc.c:1646  */
    break;

  case 112:
#line 935 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->pollindex = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2785 "config_gram.c" /* yacc.c:1646  */
    break;

  case 113:
#line 941 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->predelay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2794 "config_gram.c" /* yacc.c:1646  */
    break;

  case 114:
#line 947 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->postdelay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2803 "config_gram.c" /* yacc.c:1646  */
    break;

  case 115:
#line 953 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->pollmethod = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2812 "config_gram.c" /* yacc.c:1646  */
    break;

  case 116:
#line 959 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->hventerstabdelay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2821 "config_gram.c" /* yacc.c:1646  */
    break;

  case 117:
#line 965 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->progmodedelay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2830 "config_gram.c" /* yacc.c:1646  */
    break;

  case 118:
#line 971 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->latchcycles = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2839 "config_gram.c" /* yacc.c:1646  */
    break;

  case 119:
#line 977 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->togglevtg = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2848 "config_gram.c" /* yacc.c:1646  */
    break;

  case 120:
#line 983 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->poweroffdelay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2857 "config_gram.c" /* yacc.c:1646  */
    break;

  case 121:
#line 989 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->resetdelayms = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2866 "config_gram.c" /* yacc.c:1646  */
    break;

  case 122:
#line 995 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->resetdelayus = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2875 "config_gram.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1001 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->hvleavestabdelay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2884 "config_gram.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1007 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->resetdelay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2893 "config_gram.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1013 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->chiperasepulsewidth = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2902 "config_gram.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1019 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->chiperasepolltimeout = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2911 "config_gram.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1025 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->chiperasetime = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2920 "config_gram.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1031 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->programfusepulsewidth = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2929 "config_gram.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1037 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->programfusepolltimeout = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2938 "config_gram.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1043 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->programlockpulsewidth = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2947 "config_gram.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1049 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->programlockpolltimeout = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2956 "config_gram.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1055 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->synchcycles = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 2965 "config_gram.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1061 "config_gram.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_JTAG;
      else if ((yyvsp[0])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_JTAG;

      free_token((yyvsp[0]));
    }
#line 2978 "config_gram.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1071 "config_gram.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_DW;
      else if ((yyvsp[0])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_DW;

      free_token((yyvsp[0]));
    }
#line 2991 "config_gram.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1081 "config_gram.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_PDI;
      else if ((yyvsp[0])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_PDI;

      free_token((yyvsp[0]));
    }
#line 3004 "config_gram.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1091 "config_gram.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_TPI;
      else if ((yyvsp[0])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_TPI;

      free_token((yyvsp[0]));
    }
#line 3017 "config_gram.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1101 "config_gram.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0])->primary == K_YES)
        current_part->flags |= AVRPART_AVR32;
      else if ((yyvsp[0])->primary == K_NO)
        current_part->flags &= AVRPART_AVR32;

      free_token((yyvsp[0]));
    }
#line 3030 "config_gram.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1111 "config_gram.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0])->primary == K_YES)
        current_part->flags |= AVRPART_ALLOWFULLPAGEBITSTREAM;
      else if ((yyvsp[0])->primary == K_NO)
        current_part->flags &= ~AVRPART_ALLOWFULLPAGEBITSTREAM;

      free_token((yyvsp[0]));
    }
#line 3043 "config_gram.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1121 "config_gram.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0])->primary == K_YES)
        current_part->flags |= AVRPART_ENABLEPAGEPROGRAMMING;
      else if ((yyvsp[0])->primary == K_NO)
        current_part->flags &= ~AVRPART_ENABLEPAGEPROGRAMMING;

      free_token((yyvsp[0]));
    }
#line 3056 "config_gram.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1131 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->idr = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3065 "config_gram.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1137 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->rampz = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3074 "config_gram.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1143 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->spmcr = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3083 "config_gram.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1149 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->eecr = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3092 "config_gram.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1155 "config_gram.y" /* yacc.c:1646  */
    {
      current_part->nvm_base = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3101 "config_gram.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1161 "config_gram.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0])->primary == K_YES)
        current_part->flags |= AVRPART_SERIALOK;
      else if ((yyvsp[0])->primary == K_NO)
        current_part->flags &= ~AVRPART_SERIALOK;

      free_token((yyvsp[0]));
    }
#line 3114 "config_gram.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1171 "config_gram.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0])->primary == K_YES) {
        current_part->flags |= AVRPART_PARALLELOK;
        current_part->flags &= ~AVRPART_PSEUDOPARALLEL;
      }
      else if ((yyvsp[0])->primary == K_NO) {
        current_part->flags &= ~AVRPART_PARALLELOK;
        current_part->flags &= ~AVRPART_PSEUDOPARALLEL;
      }
      else if ((yyvsp[0])->primary == K_PSEUDO) {
        current_part->flags |= AVRPART_PARALLELOK;
        current_part->flags |= AVRPART_PSEUDOPARALLEL;
      }


      free_token((yyvsp[0]));
    }
#line 3136 "config_gram.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1190 "config_gram.y" /* yacc.c:1646  */
    {
      switch ((yyvsp[0])->primary) {
        case K_RESET :
          current_part->retry_pulse = PIN_AVR_RESET;
          break;
        case K_SCK :
          current_part->retry_pulse = PIN_AVR_SCK;
          break;
      }

      free_token((yyvsp[-2]));
    }
#line 3153 "config_gram.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1213 "config_gram.y" /* yacc.c:1646  */
    { 
      current_mem = avr_new_memtype(); 
      strcpy(current_mem->desc, strdup((yyvsp[0])->value.string)); 
      free_token((yyvsp[0])); 
    }
#line 3163 "config_gram.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1219 "config_gram.y" /* yacc.c:1646  */
    { 
      ladd(current_part->mem, current_mem); 
      current_mem = NULL; 
    }
#line 3172 "config_gram.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1224 "config_gram.y" /* yacc.c:1646  */
    {
    { 
      int opnum;
      OPCODE * op;

      opnum = which_opcode((yyvsp[-2]));
      op = avr_new_opcode();
      parse_cmdbits(op);
      current_part->op[opnum] = op;

      free_token((yyvsp[-2]));
    }
  }
#line 3190 "config_gram.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1253 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->paged = (yyvsp[0])->primary == K_YES ? 1 : 0;
      free_token((yyvsp[0]));
    }
#line 3199 "config_gram.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1259 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->size = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3208 "config_gram.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1266 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->page_size = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3217 "config_gram.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1272 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->num_pages = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3226 "config_gram.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1278 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->offset = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3235 "config_gram.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1284 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->min_write_delay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3244 "config_gram.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1290 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->max_write_delay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3253 "config_gram.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1296 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->pwroff_after_write = (yyvsp[0])->primary == K_YES ? 1 : 0;
      free_token((yyvsp[0]));
    }
#line 3262 "config_gram.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1302 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->readback[0] = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3271 "config_gram.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1308 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->readback[1] = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3280 "config_gram.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1315 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->mode = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3289 "config_gram.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1321 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->delay = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3298 "config_gram.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1327 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->blocksize = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3307 "config_gram.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1333 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->readsize = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3316 "config_gram.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1339 "config_gram.y" /* yacc.c:1646  */
    {
      current_mem->pollindex = (yyvsp[0])->value.number;
      free_token((yyvsp[0]));
    }
#line 3325 "config_gram.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1345 "config_gram.y" /* yacc.c:1646  */
    {
    { 
      int opnum;
      OPCODE * op;

      opnum = which_opcode((yyvsp[-2]));
      op = avr_new_opcode();
      parse_cmdbits(op);
      current_mem->op[opnum] = op;

      free_token((yyvsp[-2]));
    }
  }
#line 3343 "config_gram.c" /* yacc.c:1646  */
    break;


#line 3347 "config_gram.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
#line 1361 "config_gram.y" /* yacc.c:1906  */


#if 0
static char * vtypestr(int type)
{
  switch (type) {
    case V_NUM : return "NUMERIC";
    case V_STR : return "STRING";
    default:
      return "<UNKNOWN>";
  }
}
#endif


static int assign_pin(int pinno, TOKEN * v, int invert)
{
  int value;

  value = v->value.number;

  if ((value <= 0) || (value >= 18)) {
    fprintf(stderr, 
            "%s: error at line %d of %s: pin must be in the "
            "range 1-17\n",
            progname, lineno, infile);
    exit(1);
  }
  if (invert)
    value |= PIN_INVERSE;

  current_prog->pinno[pinno] = value;

  return 0;
}


static int which_opcode(TOKEN * opcode)
{
  switch (opcode->primary) {
    case K_READ        : return AVR_OP_READ; break;
    case K_WRITE       : return AVR_OP_WRITE; break;
    case K_READ_LO     : return AVR_OP_READ_LO; break;
    case K_READ_HI     : return AVR_OP_READ_HI; break;
    case K_WRITE_LO    : return AVR_OP_WRITE_LO; break;
    case K_WRITE_HI    : return AVR_OP_WRITE_HI; break;
    case K_LOADPAGE_LO : return AVR_OP_LOADPAGE_LO; break;
    case K_LOADPAGE_HI : return AVR_OP_LOADPAGE_HI; break;
    case K_LOAD_EXT_ADDR : return AVR_OP_LOAD_EXT_ADDR; break;
    case K_WRITEPAGE   : return AVR_OP_WRITEPAGE; break;
    case K_CHIP_ERASE  : return AVR_OP_CHIP_ERASE; break;
    case K_PGM_ENABLE  : return AVR_OP_PGM_ENABLE; break;
    default :
      fprintf(stderr, 
              "%s: error at %s:%d: invalid opcode\n",
              progname, infile, lineno);
      exit(1);
      break;
  }
}


static int parse_cmdbits(OPCODE * op)
{
  TOKEN * t;
  int bitno;
  char ch;
  char * e;
  char * q;
  int len;
  char * s, *brkt = NULL;

  bitno = 32;
  while (lsize(string_list)) {

    t = lrmv_n(string_list, 1);

    s = strtok_r(t->value.string, " ", &brkt);
    while (s != NULL) {

      bitno--;
      if (bitno < 0) {
        fprintf(stderr, 
                "%s: error at %s:%d: too many opcode bits for instruction\n",
                progname, infile, lineno);
        exit(1);
      }

      len = strlen(s);

      if (len == 0) {
        fprintf(stderr, 
                "%s: error at %s:%d: invalid bit specifier \"\"\n",
                progname, infile, lineno);
        exit(1);
      }

      ch = s[0];

      if (len == 1) {
        switch (ch) {
          case '1':
            op->bit[bitno].type  = AVR_CMDBIT_VALUE;
            op->bit[bitno].value = 1;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case '0':
            op->bit[bitno].type  = AVR_CMDBIT_VALUE;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'x':
            op->bit[bitno].type  = AVR_CMDBIT_IGNORE;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'a':
            op->bit[bitno].type  = AVR_CMDBIT_ADDRESS;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = 8*(bitno/8) + bitno % 8;
            break;
          case 'i':
            op->bit[bitno].type  = AVR_CMDBIT_INPUT;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'o':
            op->bit[bitno].type  = AVR_CMDBIT_OUTPUT;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          default :
            fprintf(stderr, 
                    "%s: error at %s:%d: invalid bit specifier '%c'\n",
                    progname, infile, lineno, ch);
            exit(1);
            break;
        }
      }
      else {
        if (ch == 'a') {
          q = &s[1];
          op->bit[bitno].bitno = strtol(q, &e, 0);
          if ((e == q)||(*e != 0)) {
            fprintf(stderr, 
                    "%s: error at %s:%d: can't parse bit number from \"%s\"\n",
                    progname, infile, lineno, q);
            exit(1);
          }
          op->bit[bitno].type = AVR_CMDBIT_ADDRESS;
          op->bit[bitno].value = 0;
        }
        else {
          fprintf(stderr, 
                  "%s: error at %s:%d: invalid bit specifier \"%s\"\n",
                  progname, infile, lineno, s);
          exit(1);
        }
      }

      s = strtok_r(NULL, " ", &brkt);
    }

    free_token(t);

  }  /* while */

  return 0;
}



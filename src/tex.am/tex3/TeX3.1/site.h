/*	@(#)site.h	1.1	91/11/21 14:17:01 */
/* Master configuration file for WEB to C.  Almost all the definitions
   are wrapped with #ifndef's, so that you can override them from the
   command line, if you want to.  */

#ifndef __WEB2C_SITE_H
#define __WEB2C_SITE_H

/* Define if you're running on 4.2 or 4.3 BSD-based system.  */
#ifndef BSD
#define	BSD
#endif

/* Define if you're running on System V-based system.  */
#ifndef SYSV
#undef	SYSV
#endif

/* Define if you're running on an HP-based system (also define SYSV).  */
#ifndef HP
#undef HP
#endif

/* Define if you're running on an AIX-based system.  */
#ifndef AIX
#undef AIX
#endif

/* Define if you're running on a POSIX-based system.  */
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif

/* Define this if the system will be compiled with an ANSI C compiler,
   and never with a non-ANSI compiler.  It changes web2c so that it
   produces ANSI C as its output.  This is a perhaps good idea, but you
   don't necessarily gain anything in the production programs by doing
   it.  If you do define this, you must also have a declaration for
   sprintf(3) in <stdio.h>.  */ 
#ifndef ANSI
#undef	ANSI
#endif

/* Define these according to your local setup.  It doesn't hurt anything
   to have `.' in all the paths, but since most users do not have their
   own fonts, formats, or string pools, it only slows things down.
   Do not put a leading or trailing colon in these paths, or double a
   colon in the middle.  That might lead to infinite recursion.
   Also see TEXFONTS_SUBDIR et al., below.  */
/*#define	TEXFONTS   ".:/usr/local/lib/tex/fonts/tfm"
#define	TEXFORMATS ".:/usr/local/lib/tex/formats"
#define	TEXINPUTS  ".:/usr/local/lib/tex/inputs"
#define	TEXPOOL    "/usr/local/lib/tex"
#define	MFBASES    ".:/usr/local/lib/mf/bases"
#define	MFINPUTS   ".:/usr/local/lib/mf/inputs"
#define	MFPOOL     "/usr/local/lib/mf"
#define VFFONTS	   "/usr/local/lib/tex/fonts/vfonts"*/
#define	TEXFONTS   ".:/public/module/tex/fonts/tfm"
#define	TEXFORMATS ".:/public/module/tex/formats"
#define	TEXINPUTS  ".:/public/module/tex/inputs"
#define	TEXPOOL    "/public/module/tex"
#define	MFBASES    ".:/public/module/mf/bases"
#define	MFINPUTS   ".:/public/module/mf/inputs"
#define	MFPOOL     "/public/module/mf"
#define VFFONTS	   "/public/module/tex/fonts/vfonts"

/* Define this if you want subdirectories of directories in the search
   paths to be searched.  (See discussion in ./README.W2C of directory
   hierarchies.)  */
#ifndef SEARCH_SUBDIRECTORIES
#define SEARCH_SUBDIRECTORIES
#endif

/* If SEARCH_SUBDIRECTORIES is defined, these symbols define paths in
   which to look for subdirectories.  The directories in TEXFONTS and
   the like, above, are not searched for subdirectories.  The
   directories named here are not themselves searched for files.  Not
   all of the symbols here need be defined.  If you don't want to define
   a default directory, but want users to be able to define the
   environment variables, define the symbol to be the empty string.  */
#ifdef SEARCH_SUBDIRECTORIES
/*#define TEXFONTS_SUBDIR "/usr/local/lib/tex/fonts"
#define TEXINPUTS_SUBDIR "/usr/local/lib/tex/inputs"
#define MFINPUTS_SUBDIR "/usr/local/lib/mf/inputs"*/
#define TEXFONTS_SUBDIR "/public/module/tex/fonts"
#define TEXINPUTS_SUBDIR "/public/module/tex/inputs"
#define MFINPUTS_SUBDIR "/public/module/tex/mf/inputs"

#endif

/* BibTeX search path for .bib files.  BibTeX uses TEXINPUTS to search
   for .bst files.  */ 
#define	BIBINPUTS	".:/public/module/tex/bib"

/* Metafont window support: More than one may be defined, as long as you
   don't try to have both X10 and X11 support (because there are
   conflicting routine names in the libraries).  After you've defined
   these, make sure to update the top-level Makefile accordingly.  Also,
   if you want X11 support, see the `Online output from Metafont'
   section in ./README before compiling.  */
#undef	HP2627WIN		/* HP 2627. */
#undef	SUNWIN			/* SunWindows. */
#undef	TEKTRONIXWIN		/* Tektronix 4014. */
#undef	UNITERMWIN		/* Uniterm Tektronix.  */
#undef	X10WIN			/* X Version 10. */
#define	X11WIN			/* X Version 11. */

#if defined(X10WIN) && defined(X11WIN)
sorry
#endif

/* Default editor command string: `%d' expands to the line number where
   TeX or Metafont found an error and `%s' expands to the name of the
   file.  The environment variables TEXEDIT and MFEDIT override this.  */
#define	EDITOR	"/bin/vi +%d %s"

/* Define this if you have getwd in your C library.  If you have getcwd,
   but not getwd, don't define it.  This symbol is only relevant if
   SEARCH_SUBDIRECTORIES is defined.  */
#ifndef HAVE_GETWD
#define HAVE_GETWD
#endif

/* Define this to be the return type of your signal handlers.  POSIX
   says it should be `void', but some older systems want `int'.  Check
   your <signal.h> include file if you're not sure.  */
#ifndef SIGNAL_HANDLER_RETURN_TYPE
#define SIGNAL_HANDLER_RETURN_TYPE void
#endif

/* Define this to be what your sprintf(3) routine returns---most likely
   `int' or `char *'.  Since the calls to sprintf are always cast to
   void, anyway, this is only necessary to avoid conflicts between
   declarations.  If you have ANSI or _POSIX_SOURCE defined, this symbol
   is irrelevant.  */
#ifndef SPRINTF_RETURN_TYPE
#define SPRINTF_RETURN_TYPE char *
#endif

/* The type `glueratio' should be a floating point type which won't
   unnecessarily increase the size of the memoryword structure.  This is
   the basic requirement.  On most machines, if you're building a
   normal-sized TeX, then glueratio must probably meet the following
   restriction: sizeof(glueratio) <= sizeof(integer).  Usually, then,
   glueratio must be `float'.  But if you build a big TeX, you can (on
   most machines) and should make it `double' to avoid loss of precision
   and conversions to and from double during calculations.  (All this
   also goes for Metafont.)  Furthermore, if you have enough memory, it
   won't hurt to have this defined to be `double' for running the
   trip/trap tests.  */
#ifdef SIZE16
typedef float glueratio;
#endif
#ifdef SIZE32
typedef double glueratio;
#endif

/* Define this if you want TeX to be compiled with local variables
   declared as `register'.  On SunOS 3.2 and 3.4 (at least), compiling
   with cc, this will cause problems.  If you're using gcc or the SunOS
   4.x compiler, and compiling with -O, register declarations are
   ignored, so there is no point in defining this.  */
#ifndef REGFIX
#undef	REGFIX
#endif

/* If the type `int' is at least 32 bits (including a sign bit), this
   symbol should be #undef'd; otherwise, it should be #define'd.  If
   your compiler uses 16-bit int's, arrays larger than 32K may give you
   problems, especially if indices are automatically cast to int's.  */
#ifndef SIXTEENBIT
#undef	SIXTEENBIT
#endif

/* Our character set is 8-bit ASCII unless NONASCII is defined.  For
   other character sets, make sure that first_text_char and
   last_text_char are defined correctly (they're 0 and 255,
   respectively, by default).  In the *.defines files, change the
   indicated range of type `char' to be the same as
   first_text_char..last_text_char, `#define NONASCII', and retangle and
   recompile everything.  */
#ifndef NONASCII
#undef	NONASCII
#endif

/* The type `schar' should be defined here to be the smallest signed
   type available.  ANSI C compilers may need to use `signed char'.  If
   your char type is unsigned, then define schar to be the type
   `short'.  */
#ifdef AIX
typedef int schar;
#else
typedef	char schar;
#endif

/* The type `integer' must be a signed integer capable of holding at
   least the range of numbers (-2^31)..(2^32-1).  The ANSI C standard
   says that `long' meets this requirement, but if you don't have an
   ANSI C compiler, you might have to change this definition.  */
typedef long integer;

/* You need not worry about the definitions in `defaults.h' unless
   something goes wrong.  */
#include "defaults.h"

#endif /* not __WEB2C_SITE_H */

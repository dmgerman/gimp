begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * BinReloc - a library for creating relocatable executables  * Written by: Hongli Lai<h.lai@chello.nl>  * http://autopackage.org/  *  * This source code is public domain. You can relicense this code  * under whatever license you want.  *  * See http://autopackage.org/docs/binreloc/ for  * more information and how to use this.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<limits.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|ENABLE_BINRELOC
end_ifdef

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ENABLE_BINRELOC */
end_comment

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|"gimpreloc.h"
end_include

begin_comment
comment|/** @internal  * Find the canonical filename of the executable. Returns the filename  * (which must be freed) or NULL on error. If the parameter 'error' is  * not NULL, the error code will be stored there, if an error occured.  */
end_comment

begin_function
specifier|static
name|char
modifier|*
DECL|function|_br_find_exe (GimpBinrelocInitError * error)
name|_br_find_exe
parameter_list|(
name|GimpBinrelocInitError
modifier|*
name|error
parameter_list|)
block|{
ifndef|#
directive|ifndef
name|ENABLE_BINRELOC
if|if
condition|(
name|error
condition|)
operator|*
name|error
operator|=
name|GIMP_RELOC_INIT_ERROR_DISABLED
expr_stmt|;
return|return
name|NULL
return|;
else|#
directive|else
name|char
modifier|*
name|path
decl_stmt|,
modifier|*
name|path2
decl_stmt|,
modifier|*
name|line
decl_stmt|,
modifier|*
name|result
decl_stmt|;
name|size_t
name|buf_size
decl_stmt|;
name|ssize_t
name|size
decl_stmt|;
name|struct
name|stat
name|stat_buf
decl_stmt|;
name|FILE
modifier|*
name|f
decl_stmt|;
comment|/* Read from /proc/self/exe (symlink) */
if|if
condition|(
sizeof|sizeof
argument_list|(
name|path
argument_list|)
operator|>
name|SSIZE_MAX
condition|)
name|buf_size
operator|=
name|SSIZE_MAX
operator|-
literal|1
expr_stmt|;
else|else
name|buf_size
operator|=
name|PATH_MAX
operator|-
literal|1
expr_stmt|;
name|path
operator|=
name|g_try_new
argument_list|(
name|char
argument_list|,
name|buf_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|path
operator|==
name|NULL
condition|)
block|{
comment|/* Cannot allocate memory. */
if|if
condition|(
name|error
condition|)
operator|*
name|error
operator|=
name|GIMP_RELOC_INIT_ERROR_NOMEM
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|path2
operator|=
name|g_try_new
argument_list|(
name|char
argument_list|,
name|buf_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|path2
operator|==
name|NULL
condition|)
block|{
comment|/* Cannot allocate memory. */
if|if
condition|(
name|error
condition|)
operator|*
name|error
operator|=
name|GIMP_RELOC_INIT_ERROR_NOMEM
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|strncpy
argument_list|(
name|path2
argument_list|,
literal|"/proc/self/exe"
argument_list|,
name|buf_size
operator|-
literal|1
argument_list|)
expr_stmt|;
while|while
condition|(
literal|1
condition|)
block|{
name|int
name|i
decl_stmt|;
name|size
operator|=
name|readlink
argument_list|(
name|path2
argument_list|,
name|path
argument_list|,
name|buf_size
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|size
operator|==
operator|-
literal|1
condition|)
block|{
comment|/* Error. */
name|g_free
argument_list|(
name|path2
argument_list|)
expr_stmt|;
break|break;
block|}
comment|/* readlink() success. */
name|path
index|[
name|size
index|]
operator|=
literal|'\0'
expr_stmt|;
comment|/* Check whether the symlink's target is also a symlink. 		 * We want to get the final target. */
name|i
operator|=
name|stat
argument_list|(
name|path
argument_list|,
operator|&
name|stat_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|==
operator|-
literal|1
condition|)
block|{
comment|/* Error. */
name|g_free
argument_list|(
name|path2
argument_list|)
expr_stmt|;
break|break;
block|}
comment|/* stat() success. */
if|if
condition|(
operator|!
name|S_ISLNK
argument_list|(
name|stat_buf
operator|.
name|st_mode
argument_list|)
condition|)
block|{
comment|/* path is not a symlink. Done. */
name|g_free
argument_list|(
name|path2
argument_list|)
expr_stmt|;
return|return
name|path
return|;
block|}
comment|/* path is a symlink. Continue loop and resolve this. */
name|strncpy
argument_list|(
name|path
argument_list|,
name|path2
argument_list|,
name|buf_size
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
comment|/* readlink() or stat() failed; this can happen when the program is 	 * running in Valgrind 2.2. Read from /proc/self/maps as fallback. */
name|buf_size
operator|=
name|PATH_MAX
operator|+
literal|128
expr_stmt|;
name|line
operator|=
operator|(
name|char
operator|*
operator|)
name|g_try_realloc
argument_list|(
name|path
argument_list|,
name|buf_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|line
operator|==
name|NULL
condition|)
block|{
comment|/* Cannot allocate memory. */
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
operator|*
name|error
operator|=
name|GIMP_RELOC_INIT_ERROR_NOMEM
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|f
operator|=
name|g_fopen
argument_list|(
literal|"/proc/self/maps"
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
name|f
operator|==
name|NULL
condition|)
block|{
name|g_free
argument_list|(
name|line
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
operator|*
name|error
operator|=
name|GIMP_RELOC_INIT_ERROR_OPEN_MAPS
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/* The first entry should be the executable name. */
name|result
operator|=
name|fgets
argument_list|(
name|line
argument_list|,
operator|(
name|int
operator|)
name|buf_size
argument_list|,
name|f
argument_list|)
expr_stmt|;
if|if
condition|(
name|result
operator|==
name|NULL
condition|)
block|{
name|fclose
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|line
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
operator|*
name|error
operator|=
name|GIMP_RELOC_INIT_ERROR_READ_MAPS
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/* Get rid of newline character. */
name|buf_size
operator|=
name|strlen
argument_list|(
name|line
argument_list|)
expr_stmt|;
if|if
condition|(
name|buf_size
operator|<=
literal|0
condition|)
block|{
comment|/* Huh? An empty string? */
name|fclose
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|line
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
operator|*
name|error
operator|=
name|GIMP_RELOC_INIT_ERROR_INVALID_MAPS
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|line
index|[
name|buf_size
operator|-
literal|1
index|]
operator|==
literal|10
condition|)
name|line
index|[
name|buf_size
operator|-
literal|1
index|]
operator|=
literal|0
expr_stmt|;
comment|/* Extract the filename; it is always an absolute path. */
name|path
operator|=
name|strchr
argument_list|(
name|line
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
comment|/* Sanity check. */
if|if
condition|(
name|strstr
argument_list|(
name|line
argument_list|,
literal|" r-xp "
argument_list|)
operator|==
name|NULL
operator|||
name|path
operator|==
name|NULL
condition|)
block|{
name|fclose
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|line
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
operator|*
name|error
operator|=
name|GIMP_RELOC_INIT_ERROR_INVALID_MAPS
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|path
operator|=
name|g_strdup
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|line
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|f
argument_list|)
expr_stmt|;
return|return
name|path
return|;
endif|#
directive|endif
comment|/* ENABLE_BINRELOC */
block|}
end_function

begin_comment
comment|/** @internal  * Find the canonical filename of the executable which owns symbol.  * Returns a filename which must be freed, or NULL on error.  */
end_comment

begin_function
specifier|static
name|char
modifier|*
DECL|function|_br_find_exe_for_symbol (const void * symbol,GimpBinrelocInitError * error)
name|_br_find_exe_for_symbol
parameter_list|(
specifier|const
name|void
modifier|*
name|symbol
parameter_list|,
name|GimpBinrelocInitError
modifier|*
name|error
parameter_list|)
block|{
ifndef|#
directive|ifndef
name|ENABLE_BINRELOC
if|if
condition|(
name|error
condition|)
operator|*
name|error
operator|=
name|GIMP_RELOC_INIT_ERROR_DISABLED
expr_stmt|;
return|return
operator|(
name|char
operator|*
operator|)
name|NULL
return|;
else|#
directive|else
define|#
directive|define
name|SIZE
value|PATH_MAX + 100
name|FILE
modifier|*
name|f
decl_stmt|;
name|size_t
name|address_string_len
decl_stmt|;
name|char
modifier|*
name|address_string
decl_stmt|,
name|line
index|[
name|SIZE
index|]
decl_stmt|,
modifier|*
name|found
decl_stmt|;
if|if
condition|(
name|symbol
operator|==
name|NULL
condition|)
return|return
operator|(
name|char
operator|*
operator|)
name|NULL
return|;
name|f
operator|=
name|g_fopen
argument_list|(
literal|"/proc/self/maps"
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
name|f
operator|==
name|NULL
condition|)
return|return
operator|(
name|char
operator|*
operator|)
name|NULL
return|;
name|address_string_len
operator|=
literal|4
expr_stmt|;
name|address_string
operator|=
name|g_try_new
argument_list|(
name|char
argument_list|,
name|address_string_len
argument_list|)
expr_stmt|;
name|found
operator|=
operator|(
name|char
operator|*
operator|)
name|NULL
expr_stmt|;
while|while
condition|(
operator|!
name|feof
argument_list|(
name|f
argument_list|)
condition|)
block|{
name|char
modifier|*
name|start_addr
decl_stmt|,
modifier|*
name|end_addr
decl_stmt|,
modifier|*
name|end_addr_end
decl_stmt|,
modifier|*
name|file
decl_stmt|;
name|void
modifier|*
name|start_addr_p
decl_stmt|,
modifier|*
name|end_addr_p
decl_stmt|;
name|size_t
name|len
decl_stmt|;
if|if
condition|(
name|fgets
argument_list|(
name|line
argument_list|,
name|SIZE
argument_list|,
name|f
argument_list|)
operator|==
name|NULL
condition|)
break|break;
comment|/* Sanity check. */
if|if
condition|(
name|strstr
argument_list|(
name|line
argument_list|,
literal|" r-xp "
argument_list|)
operator|==
name|NULL
operator|||
name|strchr
argument_list|(
name|line
argument_list|,
literal|'/'
argument_list|)
operator|==
name|NULL
condition|)
continue|continue;
comment|/* Parse line. */
name|start_addr
operator|=
name|line
expr_stmt|;
name|end_addr
operator|=
name|strchr
argument_list|(
name|line
argument_list|,
literal|'-'
argument_list|)
expr_stmt|;
name|file
operator|=
name|strchr
argument_list|(
name|line
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
comment|/* More sanity check. */
if|if
condition|(
operator|!
operator|(
name|file
operator|>
name|end_addr
operator|&&
name|end_addr
operator|!=
name|NULL
operator|&&
name|end_addr
index|[
literal|0
index|]
operator|==
literal|'-'
operator|)
condition|)
continue|continue;
name|end_addr
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|end_addr
operator|++
expr_stmt|;
name|end_addr_end
operator|=
name|strchr
argument_list|(
name|end_addr
argument_list|,
literal|' '
argument_list|)
expr_stmt|;
if|if
condition|(
name|end_addr_end
operator|==
name|NULL
condition|)
continue|continue;
name|end_addr_end
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|len
operator|=
name|strlen
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|len
operator|==
literal|0
condition|)
continue|continue;
if|if
condition|(
name|file
index|[
name|len
operator|-
literal|1
index|]
operator|==
literal|'\n'
condition|)
name|file
index|[
name|len
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
comment|/* Get rid of "(deleted)" from the filename. */
name|len
operator|=
name|strlen
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|len
operator|>
literal|10
operator|&&
name|strcmp
argument_list|(
name|file
operator|+
name|len
operator|-
literal|10
argument_list|,
literal|" (deleted)"
argument_list|)
operator|==
literal|0
condition|)
name|file
index|[
name|len
operator|-
literal|10
index|]
operator|=
literal|'\0'
expr_stmt|;
comment|/* I don't know whether this can happen but better safe than sorry. */
name|len
operator|=
name|strlen
argument_list|(
name|start_addr
argument_list|)
expr_stmt|;
if|if
condition|(
name|len
operator|!=
name|strlen
argument_list|(
name|end_addr
argument_list|)
condition|)
continue|continue;
comment|/* Transform the addresses into a string in the form of 0xdeadbeef, 		 * then transform that into a pointer. */
if|if
condition|(
name|address_string_len
operator|<
name|len
operator|+
literal|3
condition|)
block|{
name|address_string_len
operator|=
name|len
operator|+
literal|3
expr_stmt|;
name|address_string
operator|=
operator|(
name|char
operator|*
operator|)
name|g_try_realloc
argument_list|(
name|address_string
argument_list|,
name|address_string_len
argument_list|)
expr_stmt|;
block|}
name|memcpy
argument_list|(
name|address_string
argument_list|,
literal|"0x"
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|address_string
operator|+
literal|2
argument_list|,
name|start_addr
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|address_string
index|[
literal|2
operator|+
name|len
index|]
operator|=
literal|'\0'
expr_stmt|;
name|sscanf
argument_list|(
name|address_string
argument_list|,
literal|"%p"
argument_list|,
operator|&
name|start_addr_p
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|address_string
argument_list|,
literal|"0x"
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|address_string
operator|+
literal|2
argument_list|,
name|end_addr
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|address_string
index|[
literal|2
operator|+
name|len
index|]
operator|=
literal|'\0'
expr_stmt|;
name|sscanf
argument_list|(
name|address_string
argument_list|,
literal|"%p"
argument_list|,
operator|&
name|end_addr_p
argument_list|)
expr_stmt|;
if|if
condition|(
name|symbol
operator|>=
name|start_addr_p
operator|&&
name|symbol
operator|<
name|end_addr_p
condition|)
block|{
name|found
operator|=
name|file
expr_stmt|;
break|break;
block|}
block|}
name|g_free
argument_list|(
name|address_string
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|f
argument_list|)
expr_stmt|;
if|if
condition|(
name|found
operator|==
name|NULL
condition|)
return|return
operator|(
name|char
operator|*
operator|)
name|NULL
return|;
else|else
return|return
name|g_strdup
argument_list|(
name|found
argument_list|)
return|;
endif|#
directive|endif
comment|/* ENABLE_BINRELOC */
block|}
end_function

begin_decl_stmt
DECL|variable|exe
specifier|static
name|gchar
modifier|*
name|exe
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|set_gerror
parameter_list|(
name|GError
modifier|*
modifier|*
name|error
parameter_list|,
name|GimpBinrelocInitError
name|errcode
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/** Initialize the BinReloc library (for applications).  *  * This function must be called before using any other BinReloc functions.  * It attempts to locate the application's canonical filename.  *  * @note If you want to use BinReloc for a library, then you should call  *       _gimp_reloc_init_lib() instead.  * @note Initialization failure is not fatal. BinReloc functions will just  *       fallback to the supplied default path.  *  * @param error  If BinReloc failed to initialize, then the error report will  *               be stored in this variable. Set to NULL if you don't want an  *               error report. See the #GimpBinrelocInitError for a list of error  *               codes.  *  * @returns TRUE on success, FALSE if BinReloc failed to initialize.  */
end_comment

begin_function
name|gboolean
DECL|function|_gimp_reloc_init (GError ** error)
name|_gimp_reloc_init
parameter_list|(
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpBinrelocInitError
name|errcode
decl_stmt|;
comment|/* Shut up compiler warning about uninitialized variable. */
name|errcode
operator|=
name|GIMP_RELOC_INIT_ERROR_NOMEM
expr_stmt|;
comment|/* Locate the application's filename. */
name|exe
operator|=
name|_br_find_exe
argument_list|(
operator|&
name|errcode
argument_list|)
expr_stmt|;
if|if
condition|(
name|exe
operator|!=
name|NULL
condition|)
comment|/* Success! */
return|return
name|TRUE
return|;
else|else
block|{
comment|/* Failed :-( */
name|set_gerror
argument_list|(
name|error
argument_list|,
name|errcode
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
end_function

begin_comment
comment|/** Initialize the BinReloc library (for libraries).  *  * This function must be called before using any other BinReloc functions.  * It attempts to locate the calling library's canonical filename.  *  * @note The BinReloc source code MUST be included in your library, or this  *       function won't work correctly.  * @note Initialization failure is not fatal. BinReloc functions will just  *       fallback to the supplied default path.  *  * @returns TRUE on success, FALSE if a filename cannot be found.  */
end_comment

begin_function
name|gboolean
DECL|function|_gimp_reloc_init_lib (GError ** error)
name|_gimp_reloc_init_lib
parameter_list|(
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpBinrelocInitError
name|errcode
decl_stmt|;
comment|/* Shut up compiler warning about uninitialized variable. */
name|errcode
operator|=
name|GIMP_RELOC_INIT_ERROR_NOMEM
expr_stmt|;
name|exe
operator|=
name|_br_find_exe_for_symbol
argument_list|(
operator|(
specifier|const
name|void
operator|*
operator|)
literal|""
argument_list|,
operator|&
name|errcode
argument_list|)
expr_stmt|;
if|if
condition|(
name|exe
operator|!=
name|NULL
condition|)
comment|/* Success! */
return|return
name|TRUE
return|;
else|else
block|{
comment|/* Failed :-( */
name|set_gerror
argument_list|(
name|error
argument_list|,
name|errcode
argument_list|)
expr_stmt|;
return|return
name|exe
operator|!=
name|NULL
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|set_gerror (GError ** error,GimpBinrelocInitError errcode)
name|set_gerror
parameter_list|(
name|GError
modifier|*
modifier|*
name|error
parameter_list|,
name|GimpBinrelocInitError
name|errcode
parameter_list|)
block|{
name|gchar
modifier|*
name|error_message
decl_stmt|;
if|if
condition|(
name|error
operator|==
name|NULL
condition|)
return|return;
switch|switch
condition|(
name|errcode
condition|)
block|{
case|case
name|GIMP_RELOC_INIT_ERROR_NOMEM
case|:
name|error_message
operator|=
literal|"Cannot allocate memory."
expr_stmt|;
break|break;
case|case
name|GIMP_RELOC_INIT_ERROR_OPEN_MAPS
case|:
name|error_message
operator|=
literal|"Unable to open /proc/self/maps for reading."
expr_stmt|;
break|break;
case|case
name|GIMP_RELOC_INIT_ERROR_READ_MAPS
case|:
name|error_message
operator|=
literal|"Unable to read from /proc/self/maps."
expr_stmt|;
break|break;
case|case
name|GIMP_RELOC_INIT_ERROR_INVALID_MAPS
case|:
name|error_message
operator|=
literal|"The file format of /proc/self/maps is invalid."
expr_stmt|;
break|break;
case|case
name|GIMP_RELOC_INIT_ERROR_DISABLED
case|:
name|error_message
operator|=
literal|"Binary relocation support is disabled."
expr_stmt|;
break|break;
default|default:
name|error_message
operator|=
literal|"Unknown error."
expr_stmt|;
break|break;
block|}
empty_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|g_quark_from_static_string
argument_list|(
literal|"GBinReloc"
argument_list|)
argument_list|,
name|errcode
argument_list|,
literal|"%s"
argument_list|,
name|error_message
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/** Find the canonical filename of the current application.  *  * @param default_exe  A default filename which will be used as fallback.  * @returns A string containing the application's canonical filename,  *          which must be freed when no longer necessary. If BinReloc is  *          not initialized, or if the initialization function failed,  *          then a copy of default_exe will be returned. If default_exe  *          is NULL, then NULL will be returned.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_reloc_find_exe (const gchar * default_exe)
name|_gimp_reloc_find_exe
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_exe
parameter_list|)
block|{
if|if
condition|(
name|exe
operator|==
name|NULL
condition|)
block|{
comment|/* BinReloc is not initialized. */
if|if
condition|(
name|default_exe
operator|!=
name|NULL
condition|)
return|return
name|g_strdup
argument_list|(
name|default_exe
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
return|return
name|g_strdup
argument_list|(
name|exe
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/** Locate the directory in which the current application is installed.  *  * The prefix is generated by the following pseudo-code evaluation:  * \code  * dirname(exename)  * \endcode  *  * @param default_dir  A default directory which will used as fallback.  * @return A string containing the directory, which must be freed when no  *         longer necessary. If BinReloc is not initialized, or if the  *         initialization function failed, then a copy of default_dir  *         will be returned. If default_dir is NULL, then NULL will be  *         returned.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_reloc_find_exe_dir (const gchar * default_dir)
name|_gimp_reloc_find_exe_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_dir
parameter_list|)
block|{
if|if
condition|(
name|exe
operator|==
name|NULL
condition|)
block|{
comment|/* BinReloc not initialized. */
if|if
condition|(
name|default_dir
operator|!=
name|NULL
condition|)
return|return
name|g_strdup
argument_list|(
name|default_dir
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
return|return
name|g_path_get_dirname
argument_list|(
name|exe
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/** Locate the prefix in which the current application is installed.  *  * The prefix is generated by the following pseudo-code evaluation:  * \code  * dirname(dirname(exename))  * \endcode  *  * @param default_prefix  A default prefix which will used as fallback.  * @return A string containing the prefix, which must be freed when no  *         longer necessary. If BinReloc is not initialized, or if the  *         initialization function failed, then a copy of default_prefix  *         will be returned. If default_prefix is NULL, then NULL will be  *         returned.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_reloc_find_prefix (const gchar * default_prefix)
name|_gimp_reloc_find_prefix
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_prefix
parameter_list|)
block|{
name|gchar
modifier|*
name|dir1
decl_stmt|,
modifier|*
name|dir2
decl_stmt|;
if|if
condition|(
name|exe
operator|==
name|NULL
condition|)
block|{
comment|/* BinReloc not initialized. */
if|if
condition|(
name|default_prefix
operator|!=
name|NULL
condition|)
return|return
name|g_strdup
argument_list|(
name|default_prefix
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
name|dir1
operator|=
name|g_path_get_dirname
argument_list|(
name|exe
argument_list|)
expr_stmt|;
name|dir2
operator|=
name|g_path_get_dirname
argument_list|(
name|dir1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dir1
argument_list|)
expr_stmt|;
return|return
name|dir2
return|;
block|}
end_function

begin_comment
comment|/** Locate the application's binary folder.  *  * The path is generated by the following pseudo-code evaluation:  * \code  * prefix + "/bin"  * \endcode  *  * @param default_bin_dir  A default path which will used as fallback.  * @return A string containing the bin folder's path, which must be freed when  *         no longer necessary. If BinReloc is not initialized, or if the  *         initialization function failed, then a copy of default_bin_dir will  *         be returned. If default_bin_dir is NULL, then NULL will be returned.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_reloc_find_bin_dir (const gchar * default_bin_dir)
name|_gimp_reloc_find_bin_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_bin_dir
parameter_list|)
block|{
name|gchar
modifier|*
name|prefix
decl_stmt|,
modifier|*
name|dir
decl_stmt|;
name|prefix
operator|=
name|_gimp_reloc_find_prefix
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|prefix
operator|==
name|NULL
condition|)
block|{
comment|/* BinReloc not initialized. */
if|if
condition|(
name|default_bin_dir
operator|!=
name|NULL
condition|)
return|return
name|g_strdup
argument_list|(
name|default_bin_dir
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
name|dir
operator|=
name|g_build_filename
argument_list|(
name|prefix
argument_list|,
literal|"bin"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|prefix
argument_list|)
expr_stmt|;
return|return
name|dir
return|;
block|}
end_function

begin_comment
comment|/** Locate the application's data folder.  *  * The path is generated by the following pseudo-code evaluation:  * \code  * prefix + "/share/" + GIMP_PACKAGE + "/" + GIMP_DATA_VERSION  * \endcode  *  * @param default_data_dir  A default path which will used as fallback.  * @return A string containing the data folder's path, which must be freed when  *         no longer necessary. If BinReloc is not initialized, or if the  *         initialization function failed, then a copy of default_data_dir  *         will be returned. If default_data_dir is NULL, then NULL will be  *         returned.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_reloc_find_data_dir (const gchar * default_data_dir)
name|_gimp_reloc_find_data_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_data_dir
parameter_list|)
block|{
name|gchar
modifier|*
name|prefix
decl_stmt|,
modifier|*
name|dir
decl_stmt|;
name|prefix
operator|=
name|_gimp_reloc_find_prefix
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|prefix
operator|==
name|NULL
condition|)
block|{
comment|/* BinReloc not initialized. */
if|if
condition|(
name|default_data_dir
operator|!=
name|NULL
condition|)
return|return
name|g_strdup
argument_list|(
name|default_data_dir
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
name|dir
operator|=
name|g_build_filename
argument_list|(
name|prefix
argument_list|,
literal|"share"
argument_list|,
name|GIMP_PACKAGE
argument_list|,
name|GIMP_DATA_VERSION
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|prefix
argument_list|)
expr_stmt|;
return|return
name|dir
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|_gimp_reloc_find_plugin_dir (const gchar * default_plugin_dir)
name|_gimp_reloc_find_plugin_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_plugin_dir
parameter_list|)
block|{
name|gchar
modifier|*
name|libdir
decl_stmt|,
modifier|*
name|dir
decl_stmt|;
name|libdir
operator|=
name|_gimp_reloc_find_lib_dir
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|libdir
operator|==
name|NULL
condition|)
block|{
comment|/* BinReloc not initialized. */
if|if
condition|(
name|default_plugin_dir
operator|!=
name|NULL
condition|)
return|return
name|g_strdup
argument_list|(
name|default_plugin_dir
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
name|dir
operator|=
name|g_build_filename
argument_list|(
name|libdir
argument_list|,
name|GIMP_PACKAGE
argument_list|,
name|GIMP_PLUGIN_VERSION
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|libdir
argument_list|)
expr_stmt|;
return|return
name|dir
return|;
block|}
end_function

begin_comment
comment|/** Locate the application's localization folder.  *  * The path is generated by the following pseudo-code evaluation:  * \code  * prefix + "/share/locale"  * \endcode  *  * @param default_locale_dir  A default path which will used as fallback.  * @return A string containing the localization folder's path, which must be freed when  *         no longer necessary. If BinReloc is not initialized, or if the  *         initialization function failed, then a copy of default_locale_dir will be returned.  *         If default_locale_dir is NULL, then NULL will be returned.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_reloc_find_locale_dir (const gchar * default_locale_dir)
name|_gimp_reloc_find_locale_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_locale_dir
parameter_list|)
block|{
name|gchar
modifier|*
name|data_dir
decl_stmt|,
modifier|*
name|dir
decl_stmt|;
name|data_dir
operator|=
name|_gimp_reloc_find_data_dir
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|data_dir
operator|==
name|NULL
condition|)
block|{
comment|/* BinReloc not initialized. */
if|if
condition|(
name|default_locale_dir
operator|!=
name|NULL
condition|)
return|return
name|g_strdup
argument_list|(
name|default_locale_dir
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
name|dir
operator|=
name|g_build_filename
argument_list|(
name|data_dir
argument_list|,
literal|"locale"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data_dir
argument_list|)
expr_stmt|;
return|return
name|dir
return|;
block|}
end_function

begin_comment
comment|/** Locate the application's library folder.  *  * The path is generated by the following pseudo-code evaluation:  * \code  * prefix + "/lib"  * \endcode  *  * @param default_lib_dir  A default path which will used as fallback.  * @return A string containing the library folder's path, which must be freed when  *         no longer necessary. If BinReloc is not initialized, or if the  *         initialization function failed, then a copy of default_lib_dir will be returned.  *         If default_lib_dir is NULL, then NULL will be returned.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_reloc_find_lib_dir (const gchar * default_lib_dir)
name|_gimp_reloc_find_lib_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_lib_dir
parameter_list|)
block|{
name|gchar
modifier|*
name|prefix
decl_stmt|,
modifier|*
name|dir
decl_stmt|;
name|prefix
operator|=
name|_gimp_reloc_find_prefix
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|prefix
operator|==
name|NULL
condition|)
block|{
comment|/* BinReloc not initialized. */
if|if
condition|(
name|default_lib_dir
operator|!=
name|NULL
condition|)
return|return
name|g_strdup
argument_list|(
name|default_lib_dir
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
name|dir
operator|=
name|g_build_filename
argument_list|(
name|prefix
argument_list|,
literal|"lib"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|prefix
argument_list|)
expr_stmt|;
return|return
name|dir
return|;
block|}
end_function

begin_comment
comment|/** Locate the application's libexec folder.  *  * The path is generated by the following pseudo-code evaluation:  * \code  * prefix + "/libexec"  * \endcode  *  * @param default_libexec_dir  A default path which will used as fallback.  * @return A string containing the libexec folder's path, which must be freed when  *         no longer necessary. If BinReloc is not initialized, or if the initialization  *         function failed, then a copy of default_libexec_dir will be returned.  *         If default_libexec_dir is NULL, then NULL will be returned.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_reloc_find_libexec_dir (const gchar * default_libexec_dir)
name|_gimp_reloc_find_libexec_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_libexec_dir
parameter_list|)
block|{
name|gchar
modifier|*
name|prefix
decl_stmt|,
modifier|*
name|dir
decl_stmt|;
name|prefix
operator|=
name|_gimp_reloc_find_prefix
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|prefix
operator|==
name|NULL
condition|)
block|{
comment|/* BinReloc not initialized. */
if|if
condition|(
name|default_libexec_dir
operator|!=
name|NULL
condition|)
return|return
name|g_strdup
argument_list|(
name|default_libexec_dir
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
name|dir
operator|=
name|g_build_filename
argument_list|(
name|prefix
argument_list|,
literal|"libexec"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|prefix
argument_list|)
expr_stmt|;
return|return
name|dir
return|;
block|}
end_function

begin_comment
comment|/** Locate the application's configuration files folder.  *  * The path is generated by the following pseudo-code evaluation:  * \code  * prefix + "/etc/" + GIMP_PACKAGE + "/" + GIMP_SYSCONF_VERSION  * \endcode  *  * @param default_etc_dir  A default path which will used as fallback.  * @return A string containing the etc folder's path, which must be freed when  *         no longer necessary. If BinReloc is not initialized, or if the initialization  *         function failed, then a copy of default_etc_dir will be returned.  *         If default_etc_dir is NULL, then NULL will be returned.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_reloc_find_etc_dir (const gchar * default_etc_dir)
name|_gimp_reloc_find_etc_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_etc_dir
parameter_list|)
block|{
name|gchar
modifier|*
name|prefix
decl_stmt|,
modifier|*
name|dir
decl_stmt|;
name|prefix
operator|=
name|_gimp_reloc_find_prefix
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|prefix
operator|==
name|NULL
condition|)
block|{
comment|/* BinReloc not initialized. */
if|if
condition|(
name|default_etc_dir
operator|!=
name|NULL
condition|)
return|return
name|g_strdup
argument_list|(
name|default_etc_dir
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
name|dir
operator|=
name|g_build_filename
argument_list|(
name|prefix
argument_list|,
literal|"etc"
argument_list|,
name|GIMP_PACKAGE
argument_list|,
name|GIMP_SYSCONF_VERSION
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|prefix
argument_list|)
expr_stmt|;
return|return
name|dir
return|;
block|}
end_function

end_unit


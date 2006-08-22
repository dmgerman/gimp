begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * BinReloc - a library for creating relocatable executables  * Written by: Hongli Lai<h.lai@chello.nl>  * http://autopackage.org/  *  * This source code is public domain. You can relicense this code  * under whatever license you want.  *  * See http://autopackage.org/docs/binreloc/ for  * more information and how to use this.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RELOC_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RELOC_H__
define|#
directive|define
name|__GIMP_RELOC_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* These error codes can be returned from _gimp_reloc_init() or  * _gimp_reloc_init_lib().  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27fbe2720103
block|{
comment|/** Cannot allocate memory. */
DECL|enumerator|GIMP_RELOC_INIT_ERROR_NOMEM
name|GIMP_RELOC_INIT_ERROR_NOMEM
block|,
comment|/** Unable to open /proc/self/maps; see errno for details. */
DECL|enumerator|GIMP_RELOC_INIT_ERROR_OPEN_MAPS
name|GIMP_RELOC_INIT_ERROR_OPEN_MAPS
block|,
comment|/** Unable to read from /proc/self/maps; see errno for details. */
DECL|enumerator|GIMP_RELOC_INIT_ERROR_READ_MAPS
name|GIMP_RELOC_INIT_ERROR_READ_MAPS
block|,
comment|/** The file format of /proc/self/maps is invalid; kernel bug? */
DECL|enumerator|GIMP_RELOC_INIT_ERROR_INVALID_MAPS
name|GIMP_RELOC_INIT_ERROR_INVALID_MAPS
block|,
comment|/** BinReloc is disabled (the ENABLE_BINRELOC macro is not defined). */
DECL|enumerator|GIMP_RELOC_INIT_ERROR_DISABLED
name|GIMP_RELOC_INIT_ERROR_DISABLED
DECL|typedef|GimpBinrelocInitError
block|}
name|GimpBinrelocInitError
typedef|;
end_typedef

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_reloc_init
parameter_list|(
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_reloc_init_lib
parameter_list|(
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_reloc_find_exe
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_exe
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_reloc_find_exe_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_dir
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_reloc_find_prefix
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_prefix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_reloc_find_bin_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_bin_dir
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_reloc_find_data_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_data_dir
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_reloc_find_plugin_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_plugin_dir
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_reloc_find_locale_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_locale_dir
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_reloc_find_lib_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_lib_dir
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_reloc_find_libexec_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_libexec_dir
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_reloc_find_etc_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|default_etc_dir
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _GIMPRELOC_H_ */
end_comment

end_unit


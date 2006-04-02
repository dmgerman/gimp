begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdarg.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-run.h"
end_include

begin_include
include|#
directive|include
file|"gimpargument.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"internal_procs.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|procedural_db_init (Gimp * gimp)
name|procedural_db_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|procedural_ht
operator|=
name|g_hash_table_new
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|procedural_compat_ht
operator|=
name|g_hash_table_new
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|procedural_db_free_entry (gpointer key,gpointer value,gpointer user_data)
name|procedural_db_free_entry
parameter_list|(
name|gpointer
name|key
parameter_list|,
name|gpointer
name|value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
if|if
condition|(
name|value
condition|)
block|{
name|g_list_foreach
argument_list|(
name|value
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_procedure_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|procedural_db_free (Gimp * gimp)
name|procedural_db_free
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|procedural_ht
condition|)
block|{
name|g_hash_table_foreach
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|procedural_db_free_entry
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_destroy
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|procedural_ht
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimp
operator|->
name|procedural_compat_ht
condition|)
block|{
name|g_hash_table_destroy
argument_list|(
name|gimp
operator|->
name|procedural_compat_ht
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|procedural_compat_ht
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|procedural_db_init_procs (Gimp * gimp)
name|procedural_db_init_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
specifier|static
specifier|const
struct|struct
DECL|struct|__anon27dc6a700108
block|{
DECL|member|old_name
specifier|const
name|gchar
modifier|*
name|old_name
decl_stmt|;
DECL|member|new_name
specifier|const
name|gchar
modifier|*
name|new_name
decl_stmt|;
block|}
name|compat_procs
index|[]
init|=
block|{
block|{
literal|"gimp-blend"
block|,
literal|"gimp-edit-blend"
block|}
block|,
block|{
literal|"gimp-brushes-list"
block|,
literal|"gimp-brushes-get-list"
block|}
block|,
block|{
literal|"gimp-bucket-fill"
block|,
literal|"gimp-edit-bucket-fill"
block|}
block|,
block|{
literal|"gimp-channel-delete"
block|,
literal|"gimp-drawable-delete"
block|}
block|,
block|{
literal|"gimp-channel-get-name"
block|,
literal|"gimp-drawable-get-name"
block|}
block|,
block|{
literal|"gimp-channel-get-tattoo"
block|,
literal|"gimp-drawable-get-tattoo"
block|}
block|,
block|{
literal|"gimp-channel-get-visible"
block|,
literal|"gimp-drawable-get-visible"
block|}
block|,
block|{
literal|"gimp-channel-set-name"
block|,
literal|"gimp-drawable-set-name"
block|}
block|,
block|{
literal|"gimp-channel-set-tattoo"
block|,
literal|"gimp-drawable-set-tattoo"
block|}
block|,
block|{
literal|"gimp-channel-set-visible"
block|,
literal|"gimp-drawable-set-visible"
block|}
block|,
block|{
literal|"gimp-color-picker"
block|,
literal|"gimp-image-pick-color"
block|}
block|,
block|{
literal|"gimp-convert-grayscale"
block|,
literal|"gimp-image-convert-grayscale"
block|}
block|,
block|{
literal|"gimp-convert-indexed"
block|,
literal|"gimp-image-convert-indexed"
block|}
block|,
block|{
literal|"gimp-convert-rgb"
block|,
literal|"gimp-image-convert-rgb"
block|}
block|,
block|{
literal|"gimp-crop"
block|,
literal|"gimp-image-crop"
block|}
block|,
block|{
literal|"gimp-drawable-bytes"
block|,
literal|"gimp-drawable-bpp"
block|}
block|,
block|{
literal|"gimp-drawable-image"
block|,
literal|"gimp-drawable-get-image"
block|}
block|,
block|{
literal|"gimp-image-active-drawable"
block|,
literal|"gimp-image-get-active-drawable"
block|}
block|,
block|{
literal|"gimp-image-floating-selection"
block|,
literal|"gimp-image-get-floating-sel"
block|}
block|,
block|{
literal|"gimp-layer-delete"
block|,
literal|"gimp-drawable-delete"
block|}
block|,
block|{
literal|"gimp-layer-get-linked"
block|,
literal|"gimp-drawable-get-linked"
block|}
block|,
block|{
literal|"gimp-layer-get-name"
block|,
literal|"gimp-drawable-get-name"
block|}
block|,
block|{
literal|"gimp-layer-get-tattoo"
block|,
literal|"gimp-drawable-get-tattoo"
block|}
block|,
block|{
literal|"gimp-layer-get-visible"
block|,
literal|"gimp-drawable-get-visible"
block|}
block|,
block|{
literal|"gimp-layer-mask"
block|,
literal|"gimp-layer-get-mask"
block|}
block|,
block|{
literal|"gimp-layer-set-linked"
block|,
literal|"gimp-drawable-set-linked"
block|}
block|,
block|{
literal|"gimp-layer-set-name"
block|,
literal|"gimp-drawable-set-name"
block|}
block|,
block|{
literal|"gimp-layer-set-tattoo"
block|,
literal|"gimp-drawable-set-tattoo"
block|}
block|,
block|{
literal|"gimp-layer-set-visible"
block|,
literal|"gimp-drawable-set-visible"
block|}
block|,
block|{
literal|"gimp-palette-refresh"
block|,
literal|"gimp-palettes-refresh"
block|}
block|,
block|{
literal|"gimp-patterns-list"
block|,
literal|"gimp-patterns-get-list"
block|}
block|,
block|{
literal|"gimp-temp-PDB-name"
block|,
literal|"gimp-procedural-db-temp-name"
block|}
block|,
block|{
literal|"gimp-undo-push-group-end"
block|,
literal|"gimp-image-undo-group-end"
block|}
block|,
block|{
literal|"gimp-undo-push-group-start"
block|,
literal|"gimp-image-undo-group-start"
block|}
block|,
comment|/*  deprecations since 2.0  */
block|{
literal|"gimp-brushes-get-opacity"
block|,
literal|"gimp-context-get-opacity"
block|}
block|,
block|{
literal|"gimp-brushes-get-paint-mode"
block|,
literal|"gimp-context-get-paint-mode"
block|}
block|,
block|{
literal|"gimp-brushes-set-brush"
block|,
literal|"gimp-context-set-brush"
block|}
block|,
block|{
literal|"gimp-brushes-set-opacity"
block|,
literal|"gimp-context-set-opacity"
block|}
block|,
block|{
literal|"gimp-brushes-set-paint-mode"
block|,
literal|"gimp-context-set-paint-mode"
block|}
block|,
block|{
literal|"gimp-channel-ops-duplicate"
block|,
literal|"gimp-image-duplicate"
block|}
block|,
block|{
literal|"gimp-channel-ops-offset"
block|,
literal|"gimp-drawable-offset"
block|}
block|,
block|{
literal|"gimp-gradients-get-active"
block|,
literal|"gimp-context-get-gradient"
block|}
block|,
block|{
literal|"gimp-gradients-get-gradient"
block|,
literal|"gimp-context-get-gradient"
block|}
block|,
block|{
literal|"gimp-gradients-set-active"
block|,
literal|"gimp-context-set-gradient"
block|}
block|,
block|{
literal|"gimp-gradients-set-gradient"
block|,
literal|"gimp-context-set-gradient"
block|}
block|,
block|{
literal|"gimp-image-get-cmap"
block|,
literal|"gimp-image-get-colormap"
block|}
block|,
block|{
literal|"gimp-image-set-cmap"
block|,
literal|"gimp-image-set-colormap"
block|}
block|,
block|{
literal|"gimp-palette-get-background"
block|,
literal|"gimp-context-get-background"
block|}
block|,
block|{
literal|"gimp-palette-get-foreground"
block|,
literal|"gimp-context-get-foreground"
block|}
block|,
block|{
literal|"gimp-palette-set-background"
block|,
literal|"gimp-context-set-background"
block|}
block|,
block|{
literal|"gimp-palette-set-default-colors"
block|,
literal|"gimp-context-set-default-colors"
block|}
block|,
block|{
literal|"gimp-palette-set-foreground"
block|,
literal|"gimp-context-set-foreground"
block|}
block|,
block|{
literal|"gimp-palette-swap-colors"
block|,
literal|"gimp-context-swap-colors"
block|}
block|,
block|{
literal|"gimp-palettes-set-palette"
block|,
literal|"gimp-context-set-palette"
block|}
block|,
block|{
literal|"gimp-patterns-set-pattern"
block|,
literal|"gimp-context-set-pattern"
block|}
block|,
block|{
literal|"gimp-selection-clear"
block|,
literal|"gimp-selection-none"
block|}
block|,
comment|/*  deprecations since 2.2  */
block|{
literal|"gimp-layer-get-preserve-trans"
block|,
literal|"gimp-drawable-get-lock-alpha"
block|}
block|,
block|{
literal|"gimp-layer-set-preserve-trans"
block|,
literal|"gimp-drawable-set-lock-alpha"
block|}
block|}
struct|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|internal_procs_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|pdb_compat_mode
operator|!=
name|GIMP_PDB_COMPAT_OFF
condition|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|compat_procs
argument_list|)
condition|;
name|i
operator|++
control|)
name|g_hash_table_insert
argument_list|(
name|gimp
operator|->
name|procedural_compat_ht
argument_list|,
operator|(
name|gpointer
operator|)
name|compat_procs
index|[
name|i
index|]
operator|.
name|old_name
argument_list|,
operator|(
name|gpointer
operator|)
name|compat_procs
index|[
name|i
index|]
operator|.
name|new_name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|procedural_db_register (Gimp * gimp,GimpProcedure * procedure)
name|procedural_db_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|procedure
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|procedure
operator|->
name|name
argument_list|,
name|g_list_prepend
argument_list|(
name|list
argument_list|,
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|procedural_db_unregister (Gimp * gimp,const gchar * name)
name|procedural_db_unregister
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
block|{
name|list
operator|=
name|g_list_remove
argument_list|(
name|list
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
name|g_hash_table_insert
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
operator|(
name|gpointer
operator|)
name|name
argument_list|,
name|list
argument_list|)
expr_stmt|;
else|else
name|g_hash_table_remove
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpProcedure
modifier|*
DECL|function|procedural_db_lookup (Gimp * gimp,const gchar * name)
name|procedural_db_lookup
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
return|return
name|list
operator|->
name|data
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpArgument
modifier|*
DECL|function|procedural_db_execute (Gimp * gimp,GimpContext * context,GimpProgress * progress,const gchar * name,GimpArgument * args,gint n_args,gint * n_return_vals)
name|procedural_db_execute
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpArgument
modifier|*
name|args
parameter_list|,
name|gint
name|n_args
parameter_list|,
name|gint
modifier|*
name|n_return_vals
parameter_list|)
block|{
name|GimpArgument
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_return_vals
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|==
name|NULL
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"PDB calling error:\nprocedure '%s' not found"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
operator|&
name|return_vals
operator|->
name|value
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
operator|*
name|n_return_vals
operator|=
literal|1
expr_stmt|;
return|return
name|return_vals
return|;
block|}
for|for
control|(
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|list
operator|->
name|data
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_execute
argument_list|(
name|procedure
argument_list|,
name|gimp
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|args
argument_list|,
name|n_args
argument_list|,
name|n_return_vals
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
operator|&
name|return_vals
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
operator|==
name|GIMP_PDB_PASS_THROUGH
condition|)
block|{
comment|/*  If the return value is GIMP_PDB_PASS_THROUGH and there is            *  a next procedure in the list, destroy the return values            *  and run the next procedure.            */
if|if
condition|(
name|g_list_next
argument_list|(
name|list
argument_list|)
condition|)
name|gimp_arguments_destroy
argument_list|(
name|return_vals
argument_list|,
operator|*
name|n_return_vals
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  No GIMP_PDB_PASS_THROUGH, break out of the list of            *  procedures and return the current return values.            */
break|break;
block|}
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|GimpArgument
modifier|*
DECL|function|procedural_db_run_proc (Gimp * gimp,GimpContext * context,GimpProgress * progress,const gchar * name,gint * n_return_vals,...)
name|procedural_db_run_proc
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
modifier|*
name|n_return_vals
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|GimpArgument
modifier|*
name|args
decl_stmt|;
name|GimpArgument
modifier|*
name|return_vals
decl_stmt|;
name|va_list
name|va_args
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_return_vals
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
operator|==
name|NULL
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"PDB calling error:\nprocedure '%s' not found"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
operator|&
name|return_vals
operator|->
name|value
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
operator|*
name|n_return_vals
operator|=
literal|1
expr_stmt|;
return|return
name|return_vals
return|;
block|}
operator|*
name|n_return_vals
operator|=
name|procedure
operator|->
name|num_values
operator|+
literal|1
expr_stmt|;
name|args
operator|=
name|gimp_procedure_get_arguments
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|va_args
argument_list|,
name|n_return_vals
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|procedure
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
block|{
name|GimpPDBArgType
name|arg_type
init|=
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|GimpPDBArgType
argument_list|)
decl_stmt|;
name|GValue
modifier|*
name|value
decl_stmt|;
name|gint
name|count
decl_stmt|;
if|if
condition|(
name|arg_type
operator|==
name|GIMP_PDB_END
condition|)
break|break;
if|if
condition|(
name|arg_type
operator|!=
name|args
index|[
name|i
index|]
operator|.
name|type
condition|)
block|{
name|gchar
modifier|*
name|expected
init|=
name|procedural_db_type_name
argument_list|(
name|procedure
operator|->
name|args
index|[
name|i
index|]
operator|.
name|type
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|got
init|=
name|procedural_db_type_name
argument_list|(
name|arg_type
argument_list|)
decl_stmt|;
name|gimp_arguments_destroy
argument_list|(
name|args
argument_list|,
name|procedure
operator|->
name|num_args
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"PDB calling error for procedure '%s':\n"
literal|"Argument #%d type mismatch (expected %s, got %s)"
argument_list|)
argument_list|,
name|procedure
operator|->
name|name
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|expected
argument_list|,
name|got
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|expected
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|got
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
operator|&
name|return_vals
operator|->
name|value
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
name|value
operator|=
operator|&
name|args
index|[
name|i
index|]
operator|.
name|value
expr_stmt|;
switch|switch
condition|(
name|arg_type
condition|)
block|{
case|case
name|GIMP_PDB_INT32
case|:
if|if
condition|(
name|G_VALUE_HOLDS_INT
argument_list|(
name|value
argument_list|)
condition|)
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gint
argument_list|)
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_ENUM
argument_list|(
name|value
argument_list|)
condition|)
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gint
argument_list|)
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_BOOLEAN
argument_list|(
name|value
argument_list|)
condition|)
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gint
argument_list|)
condition|?
name|TRUE
else|:
name|FALSE
argument_list|)
expr_stmt|;
else|else
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT16
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gint
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT8
case|:
name|g_value_set_uint
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|guint
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_FLOAT
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STRING
case|:
name|g_value_set_static_string
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gchar
operator|*
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT32ARRAY
case|:
name|count
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|gimp_value_set_static_int32array
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gpointer
argument_list|)
argument_list|,
name|count
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT16ARRAY
case|:
name|count
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|gimp_value_set_static_int16array
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gpointer
argument_list|)
argument_list|,
name|count
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT8ARRAY
case|:
name|count
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|gimp_value_set_static_int8array
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gpointer
argument_list|)
argument_list|,
name|count
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_FLOATARRAY
case|:
name|count
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|gimp_value_set_static_floatarray
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gpointer
argument_list|)
argument_list|,
name|count
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STRINGARRAY
case|:
name|count
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|gimp_value_set_static_stringarray
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gpointer
argument_list|)
argument_list|,
name|count
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_COLOR
case|:
block|{
name|GimpRGB
name|color
init|=
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|GimpRGB
argument_list|)
decl_stmt|;
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_REGION
case|:
case|case
name|GIMP_PDB_BOUNDARY
case|:
break|break;
case|case
name|GIMP_PDB_DISPLAY
case|:
case|case
name|GIMP_PDB_IMAGE
case|:
case|case
name|GIMP_PDB_LAYER
case|:
case|case
name|GIMP_PDB_CHANNEL
case|:
case|case
name|GIMP_PDB_DRAWABLE
case|:
case|case
name|GIMP_PDB_SELECTION
case|:
case|case
name|GIMP_PDB_VECTORS
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gint
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_PARASITE
case|:
name|g_value_set_static_boxed
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gpointer
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STATUS
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|gint
argument_list|)
argument_list|)
expr_stmt|;
case|case
name|GIMP_PDB_END
case|:
break|break;
block|}
block|}
name|va_end
argument_list|(
name|va_args
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|procedural_db_execute
argument_list|(
name|gimp
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|name
argument_list|,
name|args
argument_list|,
name|procedure
operator|->
name|num_args
argument_list|,
name|n_return_vals
argument_list|)
expr_stmt|;
name|gimp_arguments_destroy
argument_list|(
name|args
argument_list|,
name|procedure
operator|->
name|num_args
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|procedural_db_type_name (GimpPDBArgType type)
name|procedural_db_type_name
parameter_list|(
name|GimpPDBArgType
name|type
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_PDB_ARG_TYPE
argument_list|,
name|type
argument_list|,
operator|&
name|name
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
literal|"(PDB type %d unknown)"
argument_list|,
name|type
argument_list|)
return|;
block|}
return|return
name|g_strdup
argument_list|(
name|name
argument_list|)
return|;
block|}
end_function

end_unit


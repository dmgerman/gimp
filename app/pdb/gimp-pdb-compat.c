begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimp-pdb-compat.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpPDBArgType
DECL|function|gimp_pdb_compat_arg_type_from_gtype (GType type)
name|gimp_pdb_compat_arg_type_from_gtype
parameter_list|(
name|GType
name|type
parameter_list|)
block|{
specifier|static
name|GQuark
name|pdb_type_quark
init|=
literal|0
decl_stmt|;
name|GimpPDBArgType
name|pdb_type
decl_stmt|;
if|if
condition|(
operator|!
name|pdb_type_quark
condition|)
block|{
struct|struct
DECL|struct|__anon2b3fa2260108
block|{
DECL|member|g_type
name|GType
name|g_type
decl_stmt|;
DECL|member|pdb_type
name|GimpPDBArgType
name|pdb_type
decl_stmt|;
block|}
name|type_mapping
index|[]
init|=
block|{
block|{
name|G_TYPE_INT
block|,
name|GIMP_PDB_INT32
block|}
block|,
block|{
name|G_TYPE_UINT
block|,
name|GIMP_PDB_INT32
block|}
block|,
block|{
name|G_TYPE_ENUM
block|,
name|GIMP_PDB_INT32
block|}
block|,
block|{
name|G_TYPE_BOOLEAN
block|,
name|GIMP_PDB_INT32
block|}
block|,
block|{
name|G_TYPE_UCHAR
block|,
name|GIMP_PDB_INT8
block|}
block|,
block|{
name|G_TYPE_DOUBLE
block|,
name|GIMP_PDB_FLOAT
block|}
block|,
block|{
name|G_TYPE_STRING
block|,
name|GIMP_PDB_STRING
block|}
block|,
block|{
name|GIMP_TYPE_RGB
block|,
name|GIMP_PDB_COLOR
block|}
block|,
block|{
name|GIMP_TYPE_INT32_ARRAY
block|,
name|GIMP_PDB_INT32ARRAY
block|}
block|,
block|{
name|GIMP_TYPE_INT16_ARRAY
block|,
name|GIMP_PDB_INT16ARRAY
block|}
block|,
block|{
name|GIMP_TYPE_INT8_ARRAY
block|,
name|GIMP_PDB_INT8ARRAY
block|}
block|,
block|{
name|GIMP_TYPE_FLOAT_ARRAY
block|,
name|GIMP_PDB_FLOATARRAY
block|}
block|,
block|{
name|GIMP_TYPE_STRING_ARRAY
block|,
name|GIMP_PDB_STRINGARRAY
block|}
block|,
block|{
name|GIMP_TYPE_RGB_ARRAY
block|,
name|GIMP_PDB_COLORARRAY
block|}
block|,
block|{
name|GIMP_TYPE_ITEM_ID
block|,
name|GIMP_PDB_ITEM
block|}
block|,
block|{
name|GIMP_TYPE_DISPLAY_ID
block|,
name|GIMP_PDB_DISPLAY
block|}
block|,
block|{
name|GIMP_TYPE_IMAGE_ID
block|,
name|GIMP_PDB_IMAGE
block|}
block|,
block|{
name|GIMP_TYPE_LAYER_ID
block|,
name|GIMP_PDB_LAYER
block|}
block|,
block|{
name|GIMP_TYPE_CHANNEL_ID
block|,
name|GIMP_PDB_CHANNEL
block|}
block|,
block|{
name|GIMP_TYPE_DRAWABLE_ID
block|,
name|GIMP_PDB_DRAWABLE
block|}
block|,
block|{
name|GIMP_TYPE_SELECTION_ID
block|,
name|GIMP_PDB_SELECTION
block|}
block|,
block|{
name|GIMP_TYPE_LAYER_MASK_ID
block|,
name|GIMP_PDB_CHANNEL
block|}
block|,
block|{
name|GIMP_TYPE_VECTORS_ID
block|,
name|GIMP_PDB_VECTORS
block|}
block|,
block|{
name|GIMP_TYPE_PARASITE
block|,
name|GIMP_PDB_PARASITE
block|}
block|,
block|{
name|GIMP_TYPE_PDB_STATUS_TYPE
block|,
name|GIMP_PDB_STATUS
block|}
block|}
struct|;
name|gint
name|i
decl_stmt|;
name|pdb_type_quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-pdb-type"
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
name|G_N_ELEMENTS
argument_list|(
name|type_mapping
argument_list|)
condition|;
name|i
operator|++
control|)
name|g_type_set_qdata
argument_list|(
name|type_mapping
index|[
name|i
index|]
operator|.
name|g_type
argument_list|,
name|pdb_type_quark
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|type_mapping
index|[
name|i
index|]
operator|.
name|pdb_type
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|pdb_type
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_type_get_qdata
argument_list|(
name|type
argument_list|,
name|pdb_type_quark
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|pdb_type
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_pdb_compat_procs_register (GimpPDB * pdb,GimpPDBCompatMode compat_mode)
name|gimp_pdb_compat_procs_register
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpPDBCompatMode
name|compat_mode
parameter_list|)
block|{
specifier|static
specifier|const
struct|struct
DECL|struct|__anon2b3fa2260208
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
literal|"gimp-item-delete"
block|}
block|,
block|{
literal|"gimp-channel-get-name"
block|,
literal|"gimp-item-get-name"
block|}
block|,
block|{
literal|"gimp-channel-get-tattoo"
block|,
literal|"gimp-item-get-tattoo"
block|}
block|,
block|{
literal|"gimp-channel-get-visible"
block|,
literal|"gimp-item-get-visible"
block|}
block|,
block|{
literal|"gimp-channel-set-name"
block|,
literal|"gimp-item-set-name"
block|}
block|,
block|{
literal|"gimp-channel-set-tattoo"
block|,
literal|"gimp-item-set-tattoo"
block|}
block|,
block|{
literal|"gimp-channel-set-visible"
block|,
literal|"gimp-item-set-visible"
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
literal|"gimp-item-delete"
block|}
block|,
block|{
literal|"gimp-layer-get-linked"
block|,
literal|"gimp-item-get-linked"
block|}
block|,
block|{
literal|"gimp-layer-get-name"
block|,
literal|"gimp-item-get-name"
block|}
block|,
block|{
literal|"gimp-layer-get-tattoo"
block|,
literal|"gimp-item-get-tattoo"
block|}
block|,
block|{
literal|"gimp-layer-get-visible"
block|,
literal|"gimp-item-get-visible"
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
literal|"gimp-item-set-linked"
block|}
block|,
block|{
literal|"gimp-layer-set-name"
block|,
literal|"gimp-item-set-name"
block|}
block|,
block|{
literal|"gimp-layer-set-tattoo"
block|,
literal|"gimp-item-set-tattoo"
block|}
block|,
block|{
literal|"gimp-layer-set-visible"
block|,
literal|"gimp-item-set-visible"
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
literal|"gimp-layer-get-lock-alpha"
block|}
block|,
block|{
literal|"gimp-layer-set-preserve-trans"
block|,
literal|"gimp-layer-set-lock-alpha"
block|}
block|,
comment|/*  deprecations since 2.6  */
block|{
literal|"gimp-drawable-is-valid"
block|,
literal|"gimp-item-is-valid"
block|}
block|,
block|{
literal|"gimp-drawable-is-layer"
block|,
literal|"gimp-item-is-layer"
block|}
block|,
block|{
literal|"gimp-drawable-is-text-layer"
block|,
literal|"gimp-item-is-text-layer"
block|}
block|,
block|{
literal|"gimp-drawable-is-layer-mask"
block|,
literal|"gimp-item-is-layer-mask"
block|}
block|,
block|{
literal|"gimp-drawable-is-channel"
block|,
literal|"gimp-item-is-channel"
block|}
block|,
block|{
literal|"gimp-drawable-delete"
block|,
literal|"gimp-item-delete"
block|}
block|,
block|{
literal|"gimp-drawable-get-image"
block|,
literal|"gimp-item-get-image"
block|}
block|,
block|{
literal|"gimp-drawable-get-name"
block|,
literal|"gimp-item-get-name"
block|}
block|,
block|{
literal|"gimp-drawable-set-name"
block|,
literal|"gimp-item-set-name"
block|}
block|,
block|{
literal|"gimp-drawable-get-visible"
block|,
literal|"gimp-item-get-visible"
block|}
block|,
block|{
literal|"gimp-drawable-set-visible"
block|,
literal|"gimp-item-set-visible"
block|}
block|,
block|{
literal|"gimp-drawable-get-linked"
block|,
literal|"gimp-item-get-linked"
block|}
block|,
block|{
literal|"gimp-drawable-set-linked"
block|,
literal|"gimp-item-set-linked"
block|}
block|,
block|{
literal|"gimp-drawable-get-tattoo"
block|,
literal|"gimp-item-get-tattoo"
block|}
block|,
block|{
literal|"gimp-drawable-set-tattoo"
block|,
literal|"gimp-item-set-tattoo"
block|}
block|,
block|{
literal|"gimp-drawable-parasite-find"
block|,
literal|"gimp-item-get-parasite"
block|}
block|,
block|{
literal|"gimp-drawable-parasite-attach"
block|,
literal|"gimp-item-attach-parasite"
block|}
block|,
block|{
literal|"gimp-drawable-parasite-detach"
block|,
literal|"gimp-item-detach-parasite"
block|}
block|,
block|{
literal|"gimp-drawable-parasite-list"
block|,
literal|"gimp-item-get-parasite-list"
block|}
block|,
block|{
literal|"gimp-image-get-layer-position"
block|,
literal|"gimp-image-get-item-position"
block|}
block|,
block|{
literal|"gimp-image-raise-layer"
block|,
literal|"gimp-image-raise-item"
block|}
block|,
block|{
literal|"gimp-image-lower-layer"
block|,
literal|"gimp-image-lower-item"
block|}
block|,
block|{
literal|"gimp-image-raise-layer-to-top"
block|,
literal|"gimp-image-raise-item-to-top"
block|}
block|,
block|{
literal|"gimp-image-lower-layer-to-bottom"
block|,
literal|"gimp-image-lower-item-to-bottom"
block|}
block|,
block|{
literal|"gimp-image-get-channel-position"
block|,
literal|"gimp-image-get-item-position"
block|}
block|,
block|{
literal|"gimp-image-raise-channel"
block|,
literal|"gimp-image-raise-item"
block|}
block|,
block|{
literal|"gimp-image-lower-channel"
block|,
literal|"gimp-image-lower-item"
block|}
block|,
block|{
literal|"gimp-image-get-vectors-position"
block|,
literal|"gimp-image-get-item-position"
block|}
block|,
block|{
literal|"gimp-image-raise-vectors"
block|,
literal|"gimp-image-raise-item"
block|}
block|,
block|{
literal|"gimp-image-lower-vectors"
block|,
literal|"gimp-image-lower-item"
block|}
block|,
block|{
literal|"gimp-image-raise-vectors-to-top"
block|,
literal|"gimp-image-raise-item-to-top"
block|}
block|,
block|{
literal|"gimp-image-lower-vectors-to-bottom"
block|,
literal|"gimp-image-lower-item-to-bottom"
block|}
block|,
block|{
literal|"gimp-vectors-is-valid"
block|,
literal|"gimp-item-is-valid"
block|}
block|,
block|{
literal|"gimp-vectors-get-image"
block|,
literal|"gimp-item-get-image"
block|}
block|,
block|{
literal|"gimp-vectors-get-name"
block|,
literal|"gimp-item-get-name"
block|}
block|,
block|{
literal|"gimp-vectors-set-name"
block|,
literal|"gimp-item-set-name"
block|}
block|,
block|{
literal|"gimp-vectors-get-visible"
block|,
literal|"gimp-item-get-visible"
block|}
block|,
block|{
literal|"gimp-vectors-set-visible"
block|,
literal|"gimp-item-set-visible"
block|}
block|,
block|{
literal|"gimp-vectors-get-linked"
block|,
literal|"gimp-item-get-linked"
block|}
block|,
block|{
literal|"gimp-vectors-set-linked"
block|,
literal|"gimp-item-set-linked"
block|}
block|,
block|{
literal|"gimp-vectors-get-tattoo"
block|,
literal|"gimp-item-get-tattoo"
block|}
block|,
block|{
literal|"gimp-vectors-set-tattoo"
block|,
literal|"gimp-item-set-tattoo"
block|}
block|,
block|{
literal|"gimp-vectors-parasite-find"
block|,
literal|"gimp-item-get-parasite"
block|}
block|,
block|{
literal|"gimp-vectors-parasite-attach"
block|,
literal|"gimp-item-attach-parasite"
block|}
block|,
block|{
literal|"gimp-vectors-parasite-detach"
block|,
literal|"gimp-item-detach-parasite"
block|}
block|,
block|{
literal|"gimp-vectors-parasite-list"
block|,
literal|"gimp-item-get-parasite-list"
block|}
block|,
block|{
literal|"gimp-image-parasite-find"
block|,
literal|"gimp-image-get-parasite"
block|}
block|,
block|{
literal|"gimp-image-parasite-attach"
block|,
literal|"gimp-image-attach-parasite"
block|}
block|,
block|{
literal|"gimp-image-parasite-detach"
block|,
literal|"gimp-image-detach-parasite"
block|}
block|,
block|{
literal|"gimp-image-parasite-list"
block|,
literal|"gimp-image-get-parasite-list"
block|}
block|,
block|{
literal|"gimp-parasite-find"
block|,
literal|"gimp-get-parasite"
block|}
block|,
block|{
literal|"gimp-parasite-attach"
block|,
literal|"gimp-attach-parasite"
block|}
block|,
block|{
literal|"gimp-parasite-detach"
block|,
literal|"gimp-detach-parasite"
block|}
block|,
block|{
literal|"gimp-parasite-list"
block|,
literal|"gimp-get-parasite-list"
block|}
block|,
comment|/*  deprecations since 2.8  */
block|{
literal|"gimp-edit-paste-as-new"
block|,
literal|"gimp-edit-paste-as-new-image"
block|}
block|,
block|{
literal|"gimp-edit-named-paste-as-new"
block|,
literal|"gimp-edit-named-paste-as-new-image"
block|}
block|}
struct|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|compat_mode
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
name|gimp_pdb_register_compat_proc_name
argument_list|(
name|pdb
argument_list|,
name|compat_procs
index|[
name|i
index|]
operator|.
name|old_name
argument_list|,
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

end_unit


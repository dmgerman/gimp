begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2004 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  This code is written so that it can also be compiled standalone.  *  It shouldn't depend on libgimp.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"gimphelptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimphelpitem.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|DISABLE_NLS
end_ifdef

begin_define
DECL|macro|_ (String)
define|#
directive|define
name|_
parameter_list|(
name|String
parameter_list|)
value|(String)
end_define

begin_else
else|#
directive|else
end_else

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpHelpItem
modifier|*
DECL|function|gimp_help_item_new (const gchar * ref,const gchar * title,const gchar * parent)
name|gimp_help_item_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|ref
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|parent
parameter_list|)
block|{
name|GimpHelpItem
modifier|*
name|item
init|=
name|g_new0
argument_list|(
name|GimpHelpItem
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|item
operator|->
name|ref
operator|=
name|g_strdup
argument_list|(
name|ref
argument_list|)
expr_stmt|;
name|item
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|item
operator|->
name|parent
operator|=
name|g_strdup
argument_list|(
name|parent
argument_list|)
expr_stmt|;
return|return
name|item
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_help_item_free (GimpHelpItem * item)
name|gimp_help_item_free
parameter_list|(
name|GimpHelpItem
modifier|*
name|item
parameter_list|)
block|{
name|g_free
argument_list|(
name|item
operator|->
name|ref
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|item
operator|->
name|title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|item
operator|->
name|parent
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|item
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2008 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HELP_PROGRESS_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HELP_PROGRESS_PRIVATE_H__
define|#
directive|define
name|__GIMP_HELP_PROGRESS_PRIVATE_H__
end_define

begin_comment
comment|/*  internal API  */
end_comment

begin_decl_stmt
name|void
name|_gimp_help_progress_start
argument_list|(
name|GimpHelpProgress
operator|*
name|progress
argument_list|,
name|GCancellable
operator|*
name|cancellable
argument_list|,
specifier|const
name|gchar
operator|*
name|format
argument_list|,
operator|...
argument_list|)
name|G_GNUC_PRINTF
argument_list|(
literal|3
argument_list|,
literal|4
argument_list|)
name|G_GNUC_INTERNAL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|void
name|_gimp_help_progress_update
argument_list|(
name|GimpHelpProgress
operator|*
name|progress
argument_list|,
name|gdouble
name|percentage
argument_list|)
name|G_GNUC_INTERNAL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|void
name|_gimp_help_progress_pulse
argument_list|(
name|GimpHelpProgress
operator|*
name|progress
argument_list|)
name|G_GNUC_INTERNAL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|void
name|_gimp_help_progress_finish
argument_list|(
name|GimpHelpProgress
operator|*
name|progress
argument_list|)
name|G_GNUC_INTERNAL
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ! __GIMP_HELP_PROGRESS_PRIVATE_H__ */
end_comment

end_unit


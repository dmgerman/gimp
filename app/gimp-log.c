begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"glib-object.h"
end_include

begin_include
include|#
directive|include
file|"gimp-debug.h"
end_include

begin_include
include|#
directive|include
file|"gimp-log.h"
end_include

begin_decl_stmt
DECL|variable|log_keys
specifier|static
specifier|const
name|GDebugKey
name|log_keys
index|[]
init|=
block|{
block|{
literal|"tool-events"
block|,
name|GIMP_LOG_TOOL_EVENTS
block|}
block|,
block|{
literal|"tool-focus"
block|,
name|GIMP_LOG_TOOL_FOCUS
block|}
block|,
block|{
literal|"dnd"
block|,
name|GIMP_LOG_DND
block|}
block|,
block|{
literal|"help"
block|,
name|GIMP_LOG_HELP
block|}
block|,
block|{
literal|"dialog-factory"
block|,
name|GIMP_LOG_DIALOG_FACTORY
block|}
block|,
block|{
literal|"menus"
block|,
name|GIMP_LOG_MENUS
block|}
block|,
block|{
literal|"save-dialog"
block|,
name|GIMP_LOG_SAVE_DIALOG
block|}
block|,
block|{
literal|"image-scale"
block|,
name|GIMP_LOG_IMAGE_SCALE
block|}
block|,
block|{
literal|"shadow-tiles"
block|,
name|GIMP_LOG_SHADOW_TILES
block|}
block|,
block|{
literal|"scale"
block|,
name|GIMP_LOG_SCALE
block|}
block|,
block|{
literal|"wm"
block|,
name|GIMP_LOG_WM
block|}
block|,
block|{
literal|"floating-selection"
block|,
name|GIMP_LOG_FLOATING_SELECTION
block|}
block|,
block|{
literal|"shm"
block|,
name|GIMP_LOG_SHM
block|}
block|,
block|{
literal|"text-editing"
block|,
name|GIMP_LOG_TEXT_EDITING
block|}
block|,
block|{
literal|"key-events"
block|,
name|GIMP_LOG_KEY_EVENTS
block|}
block|,
block|{
literal|"auto-tab-style"
block|,
name|GIMP_LOG_AUTO_TAB_STYLE
block|}
block|,
block|{
literal|"instances"
block|,
name|GIMP_LOG_INSTANCES
block|}
block|,
block|{
literal|"rectangle-tool"
block|,
name|GIMP_LOG_RECTANGLE_TOOL
block|}
block|,
block|{
literal|"brush-cache"
block|,
name|GIMP_LOG_BRUSH_CACHE
block|}
block|,
block|{
literal|"projection"
block|,
name|GIMP_LOG_PROJECTION
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_log_flags
name|GimpLogFlags
name|gimp_log_flags
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_log_init (void)
name|gimp_log_init
parameter_list|(
name|void
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|env_log_val
init|=
name|g_getenv
argument_list|(
literal|"GIMP_LOG"
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|env_log_val
condition|)
name|env_log_val
operator|=
name|g_getenv
argument_list|(
literal|"GIMP_DEBUG"
argument_list|)
expr_stmt|;
if|if
condition|(
name|env_log_val
condition|)
name|g_setenv
argument_list|(
literal|"G_MESSAGES_DEBUG"
argument_list|,
name|env_log_val
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|env_log_val
condition|)
block|{
comment|/*  g_parse_debug_string() has special treatment of the string 'help',        *  but we want to use it for the GIMP_LOG_HELP domain        */
if|if
condition|(
name|g_ascii_strcasecmp
argument_list|(
name|env_log_val
argument_list|,
literal|"help"
argument_list|)
operator|==
literal|0
condition|)
name|gimp_log_flags
operator|=
name|GIMP_LOG_HELP
expr_stmt|;
else|else
name|gimp_log_flags
operator|=
name|g_parse_debug_string
argument_list|(
name|env_log_val
argument_list|,
name|log_keys
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|log_keys
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_log_flags
operator|&
name|GIMP_LOG_INSTANCES
condition|)
name|gimp_debug_enable_instances
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_log (GimpLogFlags flags,const gchar * function,gint line,const gchar * format,...)
name|gimp_log
parameter_list|(
name|GimpLogFlags
name|flags
parameter_list|,
specifier|const
name|gchar
modifier|*
name|function
parameter_list|,
name|gint
name|line
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|gimp_logv
argument_list|(
name|flags
argument_list|,
name|function
argument_list|,
name|line
argument_list|,
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_logv (GimpLogFlags flags,const gchar * function,gint line,const gchar * format,va_list args)
name|gimp_logv
parameter_list|(
name|GimpLogFlags
name|flags
parameter_list|,
specifier|const
name|gchar
modifier|*
name|function
parameter_list|,
name|gint
name|line
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|domain
init|=
literal|"unknown"
decl_stmt|;
name|gchar
modifier|*
name|message
decl_stmt|;
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
name|log_keys
argument_list|)
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|log_keys
index|[
name|i
index|]
operator|.
name|value
operator|==
name|flags
condition|)
block|{
name|domain
operator|=
name|log_keys
index|[
name|i
index|]
operator|.
name|key
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|format
condition|)
name|message
operator|=
name|g_strdup_vprintf
argument_list|(
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|message
operator|=
name|g_strdup
argument_list|(
literal|"called"
argument_list|)
expr_stmt|;
name|g_log
argument_list|(
name|domain
argument_list|,
name|G_LOG_LEVEL_DEBUG
argument_list|,
literal|"%s(%d): %s"
argument_list|,
name|function
argument_list|,
name|line
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|message
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


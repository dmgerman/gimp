begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|ENABLE_NLS
end_ifndef

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_LIBINTL_H
end_ifdef

begin_define
DECL|macro|ENABLE_NLS
define|#
directive|define
name|ENABLE_NLS
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|ENABLE_NLS
end_ifdef

begin_include
include|#
directive|include
file|<libintl.h>
end_include

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|gettext (s)
define|#
directive|define
name|gettext
parameter_list|(
name|s
parameter_list|)
value|(s)
end_define

begin_define
DECL|macro|dgettext (d,s)
define|#
directive|define
name|dgettext
parameter_list|(
name|d
parameter_list|,
name|s
parameter_list|)
value|(s)
end_define

begin_define
DECL|macro|textdomain (d)
define|#
directive|define
name|textdomain
parameter_list|(
name|d
parameter_list|)
value|(d)
end_define

begin_define
DECL|macro|bindtextdomain (d,p)
define|#
directive|define
name|bindtextdomain
parameter_list|(
name|d
parameter_list|,
name|p
parameter_list|)
value|(p)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|__ (s)
define|#
directive|define
name|__
parameter_list|(
name|s
parameter_list|)
value|gettext (s)
end_define

begin_define
DECL|macro|N_ (s)
define|#
directive|define
name|N_
parameter_list|(
name|s
parameter_list|)
value|(s)
end_define

end_unit


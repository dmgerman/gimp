begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* These are the weighing factors used to convert color images to     the one-dimensional channel (luminosity?) to operate on     in gimp_ace.c:SeperateChannels()    They're recombined in glace.c:Glace_Output(),     which should undergo some scrutiny. */
end_comment

begin_comment
comment|/* For more on this subject, see the thread in gimp-developer    From: Carey Bunks<cbunks@bbn.com>    Subject: [gimp-devel] Conversion to Grayscale Bug    and http://www.inforamp.net/~poynton/ */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|NTSC_RGB
end_ifndef

begin_comment
comment|/* These are used to compute CIE luminace from linear RGB for    contemporary CRT phosphors, as specified in ITU-R Recommendation    BT.709 (formerly CCIR Rec. 709) */
end_comment

begin_comment
comment|/* Matrix for RGB -> XYZ conversion. */
end_comment

begin_define
DECL|macro|X_r
define|#
directive|define
name|X_r
value|0.412453
end_define

begin_define
DECL|macro|X_g
define|#
directive|define
name|X_g
value|0.357580
end_define

begin_define
DECL|macro|X_b
define|#
directive|define
name|X_b
value|0.180423
end_define

begin_define
DECL|macro|Y_r
define|#
directive|define
name|Y_r
value|0.212671
end_define

begin_define
DECL|macro|Y_g
define|#
directive|define
name|Y_g
value|0.715160
end_define

begin_define
DECL|macro|Y_b
define|#
directive|define
name|Y_b
value|0.072169
end_define

begin_define
DECL|macro|Z_r
define|#
directive|define
name|Z_r
value|0.019334
end_define

begin_define
DECL|macro|Z_g
define|#
directive|define
name|Z_g
value|0.119193
end_define

begin_define
DECL|macro|Z_b
define|#
directive|define
name|Z_b
value|0.950227
end_define

begin_comment
comment|/* Matrix for XYZ -> RGB version. */
end_comment

begin_define
DECL|macro|R_x
define|#
directive|define
name|R_x
value|3.240479
end_define

begin_define
DECL|macro|R_y
define|#
directive|define
name|R_y
value|-1.537150
end_define

begin_define
DECL|macro|R_z
define|#
directive|define
name|R_z
value|-0.498535
end_define

begin_define
DECL|macro|G_x
define|#
directive|define
name|G_x
value|-0.969256
end_define

begin_define
DECL|macro|G_y
define|#
directive|define
name|G_y
value|1.876992
end_define

begin_define
DECL|macro|G_z
define|#
directive|define
name|G_z
value|0.041556
end_define

begin_define
DECL|macro|B_x
define|#
directive|define
name|B_x
value|0.055648
end_define

begin_define
DECL|macro|B_y
define|#
directive|define
name|B_y
value|-0.204043
end_define

begin_define
DECL|macro|B_z
define|#
directive|define
name|B_z
value|1.057311
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* This computes luma from RGB, according to NTSC RGB CRT phosphors of    1953.  Standardized in ITU-R Recommendation BT.601-4. (formerly    CCIR Rec. 601) */
end_comment

begin_define
DECL|macro|Y_r
define|#
directive|define
name|Y_r
value|0.299
end_define

begin_define
DECL|macro|Y_g
define|#
directive|define
name|Y_g
value|0.587
end_define

begin_define
DECL|macro|Y_b
define|#
directive|define
name|Y_b
value|0.114
end_define

begin_endif
endif|#
directive|endif
end_endif

end_unit


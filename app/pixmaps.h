begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: default  */
end_comment

begin_define
DECL|macro|default_width
define|#
directive|define
name|default_width
value|13
end_define

begin_define
DECL|macro|default_height
define|#
directive|define
name|default_height
value|13
end_define

begin_decl_stmt
DECL|variable|default_bits
specifier|static
name|char
modifier|*
name|default_bits
index|[]
init|=
block|{
literal|"............."
block|,
literal|"eeeeeeee....."
block|,
literal|"eaaaaaae....."
block|,
literal|"eaaaaaae....."
block|,
literal|"eaaaaaae....."
block|,
literal|"eaaaaaaeeeee."
block|,
literal|"eaaaaaaehhhe."
block|,
literal|"eaaaaaaehhhe."
block|,
literal|"eeeeeeeehhhe."
block|,
literal|"....ehhhhhhe."
block|,
literal|"....ehhhhhhe."
block|,
literal|"....ehhhhhhe."
block|,
literal|"....eeeeeeee."
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: swap  */
end_comment

begin_define
DECL|macro|swap_width
define|#
directive|define
name|swap_width
value|13
end_define

begin_define
DECL|macro|swap_height
define|#
directive|define
name|swap_height
value|13
end_define

begin_decl_stmt
DECL|variable|swap_bits
specifier|static
name|char
modifier|*
name|swap_bits
index|[]
init|=
block|{
literal|"...e........."
block|,
literal|"..eae........"
block|,
literal|".eaaeee......"
block|,
literal|"eaaaaaae....."
block|,
literal|".eaaeeeae...."
block|,
literal|"..eae..eae..."
block|,
literal|"...e....eae.."
block|,
literal|"........eae.."
block|,
literal|".......eeaee."
block|,
literal|"......eaaaaae"
block|,
literal|".......eaaae."
block|,
literal|"........eae.."
block|,
literal|".........e..."
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* FIXME dialog is basically a temporary pixmap so the device status  * window doesn't have problems showing the dialog devices, it doesn't  * really represent anything and really should be changed  */
end_comment

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: dialog  */
end_comment

begin_define
DECL|macro|dialog_width
define|#
directive|define
name|dialog_width
value|22
end_define

begin_define
DECL|macro|dialog_height
define|#
directive|define
name|dialog_height
value|22
end_define

begin_decl_stmt
DECL|variable|dialog_bits
specifier|static
name|char
modifier|*
name|dialog_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"........aaaaa........."
block|,
literal|"......aagggggaa......."
block|,
literal|".....aaggh.gggaa......"
block|,
literal|".....agggh.eggga......"
block|,
literal|"....aggggh.egggga....."
block|,
literal|"....aghhhh.ehhhga....."
block|,
literal|"....ag.........ga....."
block|,
literal|"....aggeee.eeeega....."
block|,
literal|"....aggggh.egggga....."
block|,
literal|".....agggh.eggga......"
block|,
literal|".....aaggg.eggaa......"
block|,
literal|"......aagggggaa......."
block|,
literal|"........aaaaa........."
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

end_unit


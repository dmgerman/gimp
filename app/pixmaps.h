begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: airbrush  */
end_comment

begin_define
DECL|macro|airbrush_width
define|#
directive|define
name|airbrush_width
value|22
end_define

begin_define
DECL|macro|airbrush_height
define|#
directive|define
name|airbrush_height
value|22
end_define

begin_decl_stmt
DECL|variable|airbrush_bits
specifier|static
name|char
modifier|*
name|airbrush_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"................aaa..."
block|,
literal|"...............aaaae.."
block|,
literal|"..............aaaaae.."
block|,
literal|".............aaaaaee.."
block|,
literal|"............aaaaaee..."
block|,
literal|".......aa..aaaaaee...."
block|,
literal|"......aa..aaaaaee....."
block|,
literal|"......a.aaaaaaee......"
block|,
literal|"........ahaaaee......."
block|,
literal|".......ahhgaee........"
block|,
literal|"......ahhgaee........."
block|,
literal|".....ahhgaae.....aa..."
block|,
literal|"....ahhgaeea....a....."
block|,
literal|"....ahgaee.a....a....."
block|,
literal|"...ahaaee...a..a......"
block|,
literal|"...aaeee.....aa......."
block|,
literal|"....ee................"
block|,
literal|"......................"
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: bezier  */
end_comment

begin_define
DECL|macro|bezier_width
define|#
directive|define
name|bezier_width
value|22
end_define

begin_define
DECL|macro|bezier_height
define|#
directive|define
name|bezier_height
value|22
end_define

begin_decl_stmt
DECL|variable|bezier_bits
specifier|static
name|char
modifier|*
name|bezier_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"........eaaaaaae......"
block|,
literal|"......aaa......a......"
block|,
literal|".....a.........ae....."
block|,
literal|"....a.........aaae...."
block|,
literal|"....a........ahagae..."
block|,
literal|"...a.........ahahae..."
block|,
literal|"...a.........ahahae..."
block|,
literal|"..aaa.......ahgaggae.."
block|,
literal|"..aaae......ahgaggae.."
block|,
literal|"..aaae.....ahgaaaggae."
block|,
literal|"...aee.....ahgeaeggae."
block|,
literal|"...a........agggggaee."
block|,
literal|"...a.........agggaee.."
block|,
literal|"...a.........aaaaae..."
block|,
literal|"...a.........aeaaae..."
block|,
literal|"..a..........aeaaae..."
block|,
literal|"..a..........aeaaae..."
block|,
literal|".a...........aeaaae..."
block|,
literal|"..............eeeee..."
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: blur  */
end_comment

begin_define
DECL|macro|blur_width
define|#
directive|define
name|blur_width
value|22
end_define

begin_define
DECL|macro|blur_height
define|#
directive|define
name|blur_height
value|22
end_define

begin_decl_stmt
DECL|variable|blur_bits
specifier|static
name|char
modifier|*
name|blur_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"..........e..........."
block|,
literal|"..........e..........."
block|,
literal|".........ehe.........."
block|,
literal|".........ehee........."
block|,
literal|"........ehhge........."
block|,
literal|"........ehhgee........"
block|,
literal|".......ehhhgge........"
block|,
literal|"......ehhhhhgge......."
block|,
literal|"......ehhhhhggee......"
block|,
literal|".....ehhhhhgggga......"
block|,
literal|".....ehhhhhggggae....."
block|,
literal|".....egghhhggggae....."
block|,
literal|".....egggggggggae....."
block|,
literal|"......agggggggaee....."
block|,
literal|".......agggggaee......"
block|,
literal|"........aaaaaee......."
block|,
literal|".........eeeee........"
block|,
literal|"......................"
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: circ  */
end_comment

begin_define
DECL|macro|circ_width
define|#
directive|define
name|circ_width
value|22
end_define

begin_define
DECL|macro|circ_height
define|#
directive|define
name|circ_height
value|22
end_define

begin_decl_stmt
DECL|variable|circ_bits
specifier|static
name|char
modifier|*
name|circ_bits
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
literal|"........aahha........."
block|,
literal|"......hhgggggah......."
block|,
literal|".....ahgggggggha......"
block|,
literal|".....aggggggggga......"
block|,
literal|"....hgggggggggggh....."
block|,
literal|"....agggggggggggh....."
block|,
literal|"....aggggggggggga....."
block|,
literal|"....hggggggggggga....."
block|,
literal|"....hgggggggggggh....."
block|,
literal|".....agggggggggh......"
block|,
literal|".....ahgggggggaa......"
block|,
literal|"......haggggghh......."
block|,
literal|"........ahhaa........."
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

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: clone  */
end_comment

begin_define
DECL|macro|clone_width
define|#
directive|define
name|clone_width
value|22
end_define

begin_define
DECL|macro|clone_height
define|#
directive|define
name|clone_height
value|22
end_define

begin_decl_stmt
DECL|variable|clone_bits
specifier|static
name|char
modifier|*
name|clone_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"........eaaae........."
block|,
literal|".......eahhgae........"
block|,
literal|".......aheeega........"
block|,
literal|".......ahgggga........"
block|,
literal|".......aggggga........"
block|,
literal|".......eagggae........"
block|,
literal|"........eaaae........."
block|,
literal|".........aha.........."
block|,
literal|".....aaaaahaaaaa......"
block|,
literal|"....ahhhhaaahhhha....."
block|,
literal|"...ahhhhhhhhhhhhha...."
block|,
literal|"...aaaaaaaaaaaaaaae..."
block|,
literal|"...aggggaaaaaggggae..."
block|,
literal|"...agggggaaagggggae..."
block|,
literal|"...aggggggaggggggae..."
block|,
literal|"....aaaaaaaaaaaaaee..."
block|,
literal|".....eeeeeeeeeeeee...."
block|,
literal|"......................"
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: colorpicker  */
end_comment

begin_define
DECL|macro|colorpicker_width
define|#
directive|define
name|colorpicker_width
value|22
end_define

begin_define
DECL|macro|colorpicker_height
define|#
directive|define
name|colorpicker_height
value|22
end_define

begin_decl_stmt
DECL|variable|colorpicker_bits
specifier|static
name|char
modifier|*
name|colorpicker_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"...............aaa...."
block|,
literal|"..............aaaaa..."
block|,
literal|"..............aaaaae.."
block|,
literal|"...........aaaaaaaae.."
block|,
literal|"............aaaaaaee.."
block|,
literal|"...........ehaaaeee..."
block|,
literal|"..........ehhhaae....."
block|,
literal|".........ehhhaeae....."
block|,
literal|"........ehhhaee.e....."
block|,
literal|".......ehhhaee........"
block|,
literal|"......ehhhaee........."
block|,
literal|".....ehhhaee.........."
block|,
literal|"....ehhhaee..........."
block|,
literal|"....ehhaee............"
block|,
literal|"...ehaaee............."
block|,
literal|"....aeee.............."
block|,
literal|".....e................"
block|,
literal|"......................"
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: crop  */
end_comment

begin_define
DECL|macro|crop_width
define|#
directive|define
name|crop_width
value|22
end_define

begin_define
DECL|macro|crop_height
define|#
directive|define
name|crop_height
value|22
end_define

begin_decl_stmt
DECL|variable|crop_bits
specifier|static
name|char
modifier|*
name|crop_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"................eae..."
block|,
literal|"...............eaaa..."
block|,
literal|"..............eaaae..."
block|,
literal|".............eaaaee..."
block|,
literal|"............eaaaee...."
block|,
literal|"...........eaaaee....."
block|,
literal|"..........eaaaee......"
block|,
literal|".........eaaaee......."
block|,
literal|"........eaaaee........"
block|,
literal|".......eaaaee........."
block|,
literal|"......eaaaee.........."
block|,
literal|".....eahhae..........."
block|,
literal|"....eahhae............"
block|,
literal|"...eehhae............."
block|,
literal|"...aaaae.............."
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

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: erase  */
end_comment

begin_define
DECL|macro|erase_width
define|#
directive|define
name|erase_width
value|22
end_define

begin_define
DECL|macro|erase_height
define|#
directive|define
name|erase_height
value|22
end_define

begin_decl_stmt
DECL|variable|erase_bits
specifier|static
name|char
modifier|*
name|erase_bits
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
literal|"......................"
block|,
literal|"......................"
block|,
literal|"..........aaaaaaaa...."
block|,
literal|".........ahhhhhhaae..."
block|,
literal|"........ahhhhhhagae..."
block|,
literal|".......ahhhhhhaggae..."
block|,
literal|"......ahhhhhhaggaee..."
block|,
literal|".....ahhhhhhaggaee...."
block|,
literal|"....ahhhhhhaggaee....."
block|,
literal|"...aaaaaaaaggaee......"
block|,
literal|"...aggggggagaee......."
block|,
literal|"...aggggggaaee........"
block|,
literal|"...aaaaaaaaee........."
block|,
literal|"....eeeeeeee.........."
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

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: fill  */
end_comment

begin_define
DECL|macro|fill_width
define|#
directive|define
name|fill_width
value|22
end_define

begin_define
DECL|macro|fill_height
define|#
directive|define
name|fill_height
value|22
end_define

begin_decl_stmt
DECL|variable|fill_bits
specifier|static
name|char
modifier|*
name|fill_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|".........ee..........."
block|,
literal|"........eeee.........."
block|,
literal|".......eeggee........."
block|,
literal|".......eegaee........."
block|,
literal|".......eeahee........."
block|,
literal|".......aahheeaa......."
block|,
literal|".......ahhgeegaaa....."
block|,
literal|"......ahhghaeggaaa...."
block|,
literal|".....ahhghagaggeaaa..."
block|,
literal|"....ahhghggaggeeaaae.."
block|,
literal|"...ahhghgggggeeaaaae.."
block|,
literal|"...ahghgggggeeaeaaae.."
block|,
literal|"....ahgggggeeaeeaaae.."
block|,
literal|".....ahgggeeaee.aaae.."
block|,
literal|"......aggeeaee..aaee.."
block|,
literal|".......aeeaee...aee..."
block|,
literal|"........aaee.....e...."
block|,
literal|".........ee..........."
block|,
literal|"......................"
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: free  */
end_comment

begin_define
DECL|macro|free_width
define|#
directive|define
name|free_width
value|22
end_define

begin_define
DECL|macro|free_height
define|#
directive|define
name|free_height
value|22
end_define

begin_decl_stmt
DECL|variable|free_bits
specifier|static
name|char
modifier|*
name|free_bits
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
literal|".........aaaaaaa......"
block|,
literal|"......aaaeeeeeeeaa...."
block|,
literal|".....aeeee.......ea..."
block|,
literal|"....ae............ae.."
block|,
literal|"...ae.............ae.."
block|,
literal|"...ae...........aaee.."
block|,
literal|"...ae........aaaee...."
block|,
literal|"....aaa...aaaeee......"
block|,
literal|"...aa..aaae..........."
block|,
literal|"...a.a.ae............."
block|,
literal|"....aaa..............."
block|,
literal|"......a..............."
block|,
literal|"......a..............."
block|,
literal|".....a................"
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

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: fuzzy  */
end_comment

begin_define
DECL|macro|fuzzy_width
define|#
directive|define
name|fuzzy_width
value|22
end_define

begin_define
DECL|macro|fuzzy_height
define|#
directive|define
name|fuzzy_height
value|22
end_define

begin_decl_stmt
DECL|variable|fuzzy_bits
specifier|static
name|char
modifier|*
name|fuzzy_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......h..............."
block|,
literal|"....hgagh............."
block|,
literal|"....ahgha............."
block|,
literal|"...hgahagh............"
block|,
literal|"...aghahga............"
block|,
literal|"....hagah............."
block|,
literal|"....aghga.e..........."
block|,
literal|"......a..ege.........."
block|,
literal|"........eghge........."
block|,
literal|".........eghge........"
block|,
literal|"..........egaae......."
block|,
literal|"...........eaaae......"
block|,
literal|"............eaaae....."
block|,
literal|".............eaaae...."
block|,
literal|"..............eaaae..."
block|,
literal|"...............eaaae.."
block|,
literal|"................eae..."
block|,
literal|".................e...."
block|,
literal|"......................"
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: gradient  */
end_comment

begin_define
DECL|macro|gradient_width
define|#
directive|define
name|gradient_width
value|22
end_define

begin_define
DECL|macro|gradient_height
define|#
directive|define
name|gradient_height
value|22
end_define

begin_decl_stmt
DECL|variable|gradient_bits
specifier|static
name|char
modifier|*
name|gradient_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"..eeeeeeeeeeeeeeeeee.."
block|,
literal|"..aaaeeeegggggggghhe.."
block|,
literal|"..aaeaeegegggggghghe.."
block|,
literal|"..aaaeeeegggggggghhe.."
block|,
literal|"..aaeaeegegggggghghe.."
block|,
literal|"..aaaeeeegggggggghhe.."
block|,
literal|"..aaeaeegegggggghghe.."
block|,
literal|"..aaaeeeegggggggghhe.."
block|,
literal|"..aaeaeegegggggghghe.."
block|,
literal|"..aaaeeeegggggggghhe.."
block|,
literal|"..aaeaeegegggggghghe.."
block|,
literal|"..aaaeeeegggggggghhe.."
block|,
literal|"..aaeaeegegggggghghe.."
block|,
literal|"..aaaeeeegggggggghhe.."
block|,
literal|"..aaaaeegegggggghghe.."
block|,
literal|"..eeeeeeeeeeeeeeeeee.."
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: horizflip  */
end_comment

begin_define
DECL|macro|horizflip_width
define|#
directive|define
name|horizflip_width
value|22
end_define

begin_define
DECL|macro|horizflip_height
define|#
directive|define
name|horizflip_height
value|22
end_define

begin_decl_stmt
DECL|variable|horizflip_bits
specifier|static
name|char
modifier|*
name|horizflip_bits
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
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......a........a......"
block|,
literal|".....aa........aa....."
block|,
literal|"....aaaaaaaaaaaaaa...."
block|,
literal|"...aaaeeeeeeeeeeaaa..."
block|,
literal|"....aaaaaaaaaaaaaaee.."
block|,
literal|".....aaeeeeeeeeaaee..."
block|,
literal|"......ae.......aee...."
block|,
literal|".......e........e....."
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
block|,
literal|"......................"
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: iscissors  */
end_comment

begin_define
DECL|macro|iscissors_width
define|#
directive|define
name|iscissors_width
value|22
end_define

begin_define
DECL|macro|iscissors_height
define|#
directive|define
name|iscissors_height
value|22
end_define

begin_decl_stmt
DECL|variable|iscissors_bits
specifier|static
name|char
modifier|*
name|iscissors_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|".eaae.....aaa........."
block|,
literal|".aaaa...eee.ea........"
block|,
literal|".aaaa...a....a........"
block|,
literal|".eaae..ea....aha......"
block|,
literal|"..a....e..ha..hae....."
block|,
literal|"..a....a..hae.hae....."
block|,
literal|"..a....a..hae.hae....."
block|,
literal|"..ee...a...hahaee....."
block|,
literal|"...a..ee...hahae......"
block|,
literal|"...a..a.....haae......"
block|,
literal|"...a..a.....haae......"
block|,
literal|"...eeea.....haha......"
block|,
literal|".....a.....haeha......"
block|,
literal|"...........hae.ha....."
block|,
literal|"..........haee..haa..."
block|,
literal|".........haae..haeha.."
block|,
literal|"........haeha..haehae."
block|,
literal|"........haehae..haaee."
block|,
literal|".........haaee....ee.."
block|,
literal|"...........ee........."
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: magnify  */
end_comment

begin_define
DECL|macro|magnify_width
define|#
directive|define
name|magnify_width
value|22
end_define

begin_define
DECL|macro|magnify_height
define|#
directive|define
name|magnify_height
value|22
end_define

begin_decl_stmt
DECL|variable|magnify_bits
specifier|static
name|char
modifier|*
name|magnify_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"...........aaaa......."
block|,
literal|".........eaghh.ae....."
block|,
literal|".........ahheehhae...."
block|,
literal|"........aghehhhhga...."
block|,
literal|"........ahehhhhhhae..."
block|,
literal|"........ahhhhhhhhae..."
block|,
literal|"........aghhhhhhgae..."
block|,
literal|".........ahhhhhhaee..."
block|,
literal|"........aaaghhgaee...."
block|,
literal|".......aaaeaaaaee....."
block|,
literal|"......aaaee.eeee......"
block|,
literal|".....aaaee............"
block|,
literal|"....aaaee............."
block|,
literal|"...aaaee.............."
block|,
literal|"...eaee..............."
block|,
literal|"....ee................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: move  */
end_comment

begin_define
DECL|macro|move_width
define|#
directive|define
name|move_width
value|22
end_define

begin_define
DECL|macro|move_height
define|#
directive|define
name|move_height
value|22
end_define

begin_decl_stmt
DECL|variable|move_bits
specifier|static
name|char
modifier|*
name|move_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"..........a..........."
block|,
literal|".........aaa.........."
block|,
literal|"........aaaaa........."
block|,
literal|"..........aeee........"
block|,
literal|"..........ae.........."
block|,
literal|".....a....ae...a......"
block|,
literal|"....aa....ae...aa....."
block|,
literal|"...aaaaaaaaaaaaaaa...."
block|,
literal|"....aaeeeeaeeeeaaee..."
block|,
literal|".....ae...ae...aee...."
block|,
literal|"......e...ae....e....."
block|,
literal|"..........ae.........."
block|,
literal|"........aaaaa........."
block|,
literal|".........aaae........."
block|,
literal|"..........ae.........."
block|,
literal|"..........e..........."
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: new  */
end_comment

begin_comment
comment|/* #define new_width 22 #define new_height 22 static char *new_bits [] = {   "......................",   "......................",   "......................",   ".....aaaaaaaaa........",   ".....ahhhhhhhaa.......",   ".....ahhhhhhhaga......",   ".....ahhhhhhhagga.....",   ".....ahhhhhhhaaaae....",   ".....ahhhhhhhhggae....",   ".....ahhhhhhhhhhae....",   ".....ahhhhhhhhhhae....",   ".....ahhhhhhhhhhae....",   ".....ahhhhhhhhhhae....",   ".....ahhhhhhhhhhae....",   ".....ahhhhhhhhhhae....",   ".....ahhhhhhhhhhae....",   ".....ahhhhhhhhhhae....",   ".....aaaaaaaaaaaae....",   "......eeeeeeeeeeee....",   "......................",   "......................",   "......................" }; */
end_comment

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: open  */
end_comment

begin_comment
comment|/* #define open_width 22 #define open_height 22 static char *open_bits [] = {   "......................",   "......................",   "......................",   "......................",   "....eaaaae............",   "...eaggggae...........",   "...aggggggaaaaaaaae...",   "...agggggggggggggga...",   ".aaaaaaaaaaaaaagggae..",   ".aegegegegegegagggae..",   "..aegegegegegegaggae..",   "..agegegegegegeaggae..",   "...agegegegegegeagae..",   "...aegegegegegegagae..",   "...agegegegegegeagae..",   "....agegegegegegeaae..",   "....aegegegegegegaae..",   ".....aaaaaaaaaaaaaae..",   "......eeeeeeeeeeeeee..",   "......................",   "......................",   "......................" }; */
end_comment

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: paint  */
end_comment

begin_define
DECL|macro|paint_width
define|#
directive|define
name|paint_width
value|22
end_define

begin_define
DECL|macro|paint_height
define|#
directive|define
name|paint_height
value|22
end_define

begin_decl_stmt
DECL|variable|paint_bits
specifier|static
name|char
modifier|*
name|paint_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|".............aggae...."
block|,
literal|".............aggae...."
block|,
literal|"............aggaee...."
block|,
literal|"............aggae....."
block|,
literal|"...........aggaee....."
block|,
literal|"...........aggae......"
block|,
literal|"..........aggaee......"
block|,
literal|"..........aggae......."
block|,
literal|".........aaaaee......."
block|,
literal|"........aggaae........"
block|,
literal|".......ahhgaae........"
block|,
literal|".......ahgeaae........"
block|,
literal|"......ahgeaaee........"
block|,
literal|"......ageaaee........."
block|,
literal|".....aheaaee.........."
block|,
literal|"....aaaaeee..........."
block|,
literal|".....eeee............."
block|,
literal|"......................"
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: pencil  */
end_comment

begin_define
DECL|macro|pencil_width
define|#
directive|define
name|pencil_width
value|22
end_define

begin_define
DECL|macro|pencil_height
define|#
directive|define
name|pencil_height
value|22
end_define

begin_decl_stmt
DECL|variable|pencil_bits
specifier|static
name|char
modifier|*
name|pencil_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"..........aaaa........"
block|,
literal|"..........aggga......."
block|,
literal|".........aggggae......"
block|,
literal|".........aaggaee......"
block|,
literal|"........ahhaaae......."
block|,
literal|"........ahggaee......."
block|,
literal|".......ahhggae........"
block|,
literal|".......ahggaee........"
block|,
literal|"......ahhggae........."
block|,
literal|"......ahggaee........."
block|,
literal|"......aaggae.........."
block|,
literal|"......aaaaee.........."
block|,
literal|"......aaaee..........."
block|,
literal|"......aaee............"
block|,
literal|"......aee............."
block|,
literal|".......e.............."
block|,
literal|"......................"
block|,
literal|"......................"
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: perspective  */
end_comment

begin_comment
comment|/* #define perspective_width 22 #define perspective_height 22 static char *perspective_bits [] = {   "......................",   "......................",   "......................",   "......aaaaaaaaa.......",   ".....eegggggggee......",   ".....aegggggggea......",   "....agegggggggega.....",   "....agegggggggega.....",   "...eagegggggggegae....",   "...aggeeeeeeeeegga....",   "...aggggggggggggga....",   "..eagagagggggagagae...",   "..aggaagggggggaagga...",   "..aggaaagggggaaagga...",   ".aegggggggggggggggea..",   ".aaaaaaaaaaaaaaaaaaa..",   "......................",   "......................",   "......................",   "......................",   "......................",   "......................" }; */
end_comment

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: rect  */
end_comment

begin_define
DECL|macro|rect_width
define|#
directive|define
name|rect_width
value|22
end_define

begin_define
DECL|macro|rect_height
define|#
directive|define
name|rect_height
value|22
end_define

begin_decl_stmt
DECL|variable|rect_bits
specifier|static
name|char
modifier|*
name|rect_bits
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
literal|"......................"
block|,
literal|"....aahhaahhaahha....."
block|,
literal|"....hggggggggggga....."
block|,
literal|"....hgggggggggggh....."
block|,
literal|"....agggggggggggh....."
block|,
literal|"....aggggggggggga....."
block|,
literal|"....hggggggggggga....."
block|,
literal|"....hgggggggggggh....."
block|,
literal|"....agggggggggggh....."
block|,
literal|"....aggggggggggga....."
block|,
literal|"....hggggggggggga....."
block|,
literal|"....haahhaahhaahh....."
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
block|,
literal|"......................"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: rotate  */
end_comment

begin_comment
comment|/* #define rotate_width 22 #define rotate_height 22 static char *rotate_bits [] = {   "......................",   "......................",   ".aaaaaaaaaaa...aaa....",   ".aeeeeeeeeea..a...a.a.",   ".aeeeeeeeeea.......aa.",   ".aeeeeeeeeea......aaa.",   ".aeeeeeeeeeaae........",   ".aeeeeeeeeeggae.......",   ".aeeeeeeeegeggae......",   ".aeeeeeeeggegggae.....",   ".aeeeeeegggeggggae....",   ".aaaaaageeeegggggae...",   ".....eagggggggggggae..",   ".....agggggggggggggae.",   ".....eagggggggggggaee.",   "......eagggggggggaee..",   ".......eagggggggaee...",   ".aaa....eagggggaee....",   ".aa......eagggaee.....",   ".a.a...a..eagaee......",   "....aaa....eaee.......",   "............ee........" }; */
end_comment

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: scale  */
end_comment

begin_define
DECL|macro|scale_width
define|#
directive|define
name|scale_width
value|22
end_define

begin_define
DECL|macro|scale_height
define|#
directive|define
name|scale_height
value|22
end_define

begin_decl_stmt
DECL|variable|scale_bits
specifier|static
name|char
modifier|*
name|scale_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"..aaaaaaa............."
block|,
literal|"..aeeeeeaeaeaea......."
block|,
literal|"..aeeeeeaggggge......."
block|,
literal|"..aeeggggaaaaaaaaaa..."
block|,
literal|"..aeegggegggggegggae.."
block|,
literal|"..aaageeegggggagggae.."
block|,
literal|"...egaggggggggegggae.."
block|,
literal|"...agaggggggggegggae.."
block|,
literal|"...egagggggggaggggae.."
block|,
literal|"...aeaeaeaeaegagagae.."
block|,
literal|".....agggggggggaagae.."
block|,
literal|".....aggggggggaaagae.."
block|,
literal|".....aggggggggggggae.."
block|,
literal|".....aaaaaaaaaaaaaae.."
block|,
literal|"......eeeeeeeeeeeeee.."
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

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: sharpen  */
end_comment

begin_comment
comment|/* #define sharpen_width 22 #define sharpen_height 22 static char *sharpen_bits [] = {   "......................",   "......................",   "......................",   "..........a...........",   "..........ae..........",   ".........eha..........",   ".........eha..........",   ".........ehae.........",   "........ehgga.........",   "........ehgga.........",   "........ehggae........",   ".......ehgggga........",   ".......ehgggga........",   ".......ehggggae.......",   "......ehhggggga.......",   "......ehggggggae......",   "......ehggggggae......",   ".....ehhgggggeeae.....",   "......aaaaaaaaaee.....",   ".......eeeeeeeee......",   "......................",   "......................" }; */
end_comment

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: skew  */
end_comment

begin_comment
comment|/* #define skew_width 22 #define skew_height 22 static char *skew_bits [] = {   "......................",   "......................",   "......................",   "......................",   "...aaaaaaaaaaa........",   "...agggggggggea.......",   "...aeggggggggega......",   "...aeggggggggega......",   "...aeegggggggegga.....",   "...aeegggggggegga.....",   "...aeeeggggggeggga....",   "...aeeeggggggeggga....",   "...aeeeegggggegggga...",   "...aaaaageeeeegggga...",   "........agggggggggga..",   ".....a...aaaaaaaaaaa..",   "..aaaaa...............",   ".....a................",   "......................",   "......................",   "......................",   "......................" }; */
end_comment

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: text  */
end_comment

begin_define
DECL|macro|text_width
define|#
directive|define
name|text_width
value|22
end_define

begin_define
DECL|macro|text_height
define|#
directive|define
name|text_height
value|22
end_define

begin_decl_stmt
DECL|variable|text_bits
specifier|static
name|char
modifier|*
name|text_bits
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
literal|".....aaaaaaaaaaa......"
block|,
literal|".....aaeeaaaeeaae....."
block|,
literal|".....aee.aaae..ae....."
block|,
literal|"......e..aaae...e....."
block|,
literal|"........eaae.........."
block|,
literal|"........eaae.........."
block|,
literal|"........eaae.........."
block|,
literal|"........aaae.........."
block|,
literal|"........aae..........."
block|,
literal|".......eaae..........."
block|,
literal|".......eaae..........."
block|,
literal|".......aaae..........."
block|,
literal|"......aaaaa..........."
block|,
literal|".......eeeee.........."
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

begin_comment
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: vertflip  */
end_comment

begin_comment
comment|/* #define vertflip_width 22 #define vertflip_height 22 static char *vertflip_bits [] = {   "......................",   "......................",   "......................",   "..........a...........",   ".........aaa..........",   "........aaaaa.........",   ".......aaaeaaa........",   ".........aeaeee.......",   ".........aeae.........",   ".........aeae.........",   ".........aeae.........",   ".........aeae.........",   ".........aeae.........",   ".........aeae.........",   ".........aeae.........",   ".......aaaeaaa........",   "........aaaaaee.......",   ".........aaaee........",   "..........aee.........",   "...........e..........",   "......................",   "......................" }; */
end_comment

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
comment|/*  GIMP icon image format -- S. Kimball, P. Mattis  */
end_comment

begin_comment
comment|/*  Image name: ink  */
end_comment

begin_define
DECL|macro|ink_width
define|#
directive|define
name|ink_width
value|22
end_define

begin_define
DECL|macro|ink_height
define|#
directive|define
name|ink_height
value|22
end_define

begin_decl_stmt
DECL|variable|ink_bits
specifier|static
name|char
modifier|*
name|ink_bits
index|[]
init|=
block|{
literal|"......................"
block|,
literal|"......................"
block|,
literal|"...............aa....."
block|,
literal|"..............aaea...."
block|,
literal|".............aaeaaa..."
block|,
literal|"............aaeaaaa..."
block|,
literal|"...........aaeaaaae..."
block|,
literal|"..........aaeaaaae...."
block|,
literal|".........aaeaaaae....."
block|,
literal|".......aaaeaaaae......"
block|,
literal|".....aaaaaaaaae......."
block|,
literal|"....aaghhaaaae........"
block|,
literal|"....ahaeagaae........."
block|,
literal|"...aahgaegaae........."
block|,
literal|"...ahhaeaeae.........."
block|,
literal|"...ahaeggaae.........."
block|,
literal|"..ahaegaaae..........."
block|,
literal|"..aaeaaaee............"
block|,
literal|".aaaaeee.............."
block|,
literal|".aaee................."
block|,
literal|"..ee.................."
literal|"......................"
block|, }
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


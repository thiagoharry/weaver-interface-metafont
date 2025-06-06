/*678:*/
#line 18792 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 18798 "weaver-interface-metafont_en.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*679:*/
#line 18821 "weaver-interface-metafont_en.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:679*//*682:*/
#line 18865 "weaver-interface-metafont_en.cweb"

ERROR_DIVISION_BY_ZERO,
/*:682*//*685:*/
#line 18887 "weaver-interface-metafont_en.cweb"

ERROR_DUPLICATE_GLYPH,
/*:685*//*688:*/
#line 18916 "weaver-interface-metafont_en.cweb"

ERROR_EMPTY_DELIMITER,
/*:688*//*691:*/
#line 18961 "weaver-interface-metafont_en.cweb"

ERROR_EXPECTED_FOUND,
/*:691*//*694:*/
#line 18996 "weaver-interface-metafont_en.cweb"

ERROR_FAILED_OPENING_FILE,
/*:694*//*698:*/
#line 19038 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:698*//*701:*/
#line 19068 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:701*//*704:*/
#line 19099 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_CHAR,
/*:704*//*707:*/
#line 19200 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_COMPARISON,
/*:707*//*710:*/
#line 19232 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:710*//*713:*/
#line 19271 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_NAME,
/*:713*//*716:*/
#line 19317 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_TENSION,
/*:716*//*719:*/
#line 19369 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_EXPRESSION,
/*:719*//*722:*/
#line 19399 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_TOKEN,
/*:722*//*725:*/
#line 19428 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:725*//*728:*/
#line 19455 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:728*//*731:*/
#line 19483 "weaver-interface-metafont_en.cweb"

ERROR_NESTED_BEGINCHAR,
/*:731*//*734:*/
#line 19511 "weaver-interface-metafont_en.cweb"

ERROR_NO_MEMORY,
/*:734*//*737:*/
#line 19561 "weaver-interface-metafont_en.cweb"

ERROR_NO_PICKUP_PEN,
/*:737*//*740:*/
#line 19593 "weaver-interface-metafont_en.cweb"

ERROR_NONCYCLICAL_PEN,
/*:740*//*743:*/
#line 19619 "weaver-interface-metafont_en.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:743*//*746:*/
#line 19647 "weaver-interface-metafont_en.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:746*//*749:*/
#line 19701 "weaver-interface-metafont_en.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:749*//*752:*/
#line 19735 "weaver-interface-metafont_en.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:752*//*755:*/
#line 19770 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:755*//*758:*/
#line 19799 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_STRING,
/*:758*//*761:*/
#line 19836 "weaver-interface-metafont_en.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:761*//*764:*/
#line 19864 "weaver-interface-metafont_en.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:764*//*767:*/
#line 19896 "weaver-interface-metafont_en.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:767*//*770:*/
#line 19929 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:770*//*773:*/
#line 19960 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:773*//*776:*/
#line 19990 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:776*//*779:*/
#line 20020 "weaver-interface-metafont_en.cweb"

ERROR_UNOPENED_DELIMITER,
/*:779*//*782:*/
#line 20049 "weaver-interface-metafont_en.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:782*//*785:*/
#line 20091 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:785*//*788:*/
#line 20131 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:788*/
#line 18801 "weaver-interface-metafont_en.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,

/*39:*/
#line 1197 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2442 "weaver-interface-metafont_en.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2710 "weaver-interface-metafont_en.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*200:*/
#line 5172 "weaver-interface-metafont_en.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:200*//*204:*/
#line 5338 "weaver-interface-metafont_en.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:204*//*205:*/
#line 5351 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:205*//*212:*/
#line 5576 "weaver-interface-metafont_en.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:212*//*216:*/
#line 5697 "weaver-interface-metafont_en.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:216*//*232:*/
#line 5981 "weaver-interface-metafont_en.cweb"

TYPE_NORMALDEVIATE,
/*:232*//*246:*/
#line 6309 "weaver-interface-metafont_en.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:246*//*266:*/
#line 6861 "weaver-interface-metafont_en.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:266*//*273:*/
#line 7001 "weaver-interface-metafont_en.cweb"

TYPE_TRANSFORMED,
/*:273*//*292:*/
#line 7394 "weaver-interface-metafont_en.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:292*//*299:*/
#line 7548 "weaver-interface-metafont_en.cweb"

TYPE_CYCLE,
TYPE_AMPERSAND,
TYPE_JOIN,
TYPE_TENSION,
TYPE_AND,
TYPE_ATLEAST,
TYPE_CONTROLS,
TYPE_CURL,
TYPE_STRAIGHT_JOIN,
/*:299*//*360:*/
#line 9192 "weaver-interface-metafont_en.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:360*//*372:*/
#line 9570 "weaver-interface-metafont_en.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:372*//*394:*/
#line 10087 "weaver-interface-metafont_en.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:394*//*406:*/
#line 10360 "weaver-interface-metafont_en.cweb"

TYPE_MAKEPATH,
/*:406*//*450:*/
#line 11504 "weaver-interface-metafont_en.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:450*//*462:*/
#line 11862 "weaver-interface-metafont_en.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:462*//*468:*/
#line 12026 "weaver-interface-metafont_en.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:468*//*472:*/
#line 12265 "weaver-interface-metafont_en.cweb"

TYPE_OR,
/*:472*//*478:*/
#line 12416 "weaver-interface-metafont_en.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:478*//*486:*/
#line 12895 "weaver-interface-metafont_en.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:486*//*491:*/
#line 13110 "weaver-interface-metafont_en.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:491*//*500:*/
#line 13332 "weaver-interface-metafont_en.cweb"

TYPE_PICKUP,
/*:500*//*575:*/
#line 16104 "weaver-interface-metafont_en.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:575*//*583:*/
#line 16223 "weaver-interface-metafont_en.cweb"

TYPE_PICKCOLOR,
/*:583*//*586:*/
#line 16304 "weaver-interface-metafont_en.cweb"

TYPE_MONOWIDTH,
/*:586*//*591:*/
#line 16358 "weaver-interface-metafont_en.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:591*//*632:*/
#line 17568 "weaver-interface-metafont_en.cweb"

TYPE_SHIPIT,
/*:632*//*636:*/
#line 17671 "weaver-interface-metafont_en.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:636*//*645:*/
#line 17945 "weaver-interface-metafont_en.cweb"

TYPE_KERNING,
/*:645*//*651:*/
#line 18095 "weaver-interface-metafont_en.cweb"

TYPE_DEBUG,
/*:651*/
#line 18808 "weaver-interface-metafont_en.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 18815 "weaver-interface-metafont_en.cweb"
#endif
#line 18816 "weaver-interface-metafont_en.cweb"
/*:678*/

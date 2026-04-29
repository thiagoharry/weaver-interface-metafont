/*693:*/
#line 19125 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19131 "weaver-interface-metafont_en.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*694:*/
#line 19154 "weaver-interface-metafont_en.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:694*//*697:*/
#line 19201 "weaver-interface-metafont_en.cweb"

ERROR_DIVISION_BY_ZERO,
/*:697*//*700:*/
#line 19223 "weaver-interface-metafont_en.cweb"

ERROR_DUPLICATE_GLYPH,
/*:700*//*703:*/
#line 19252 "weaver-interface-metafont_en.cweb"

ERROR_EMPTY_DELIMITER,
/*:703*//*706:*/
#line 19297 "weaver-interface-metafont_en.cweb"

ERROR_EXPECTED_FOUND,
/*:706*//*709:*/
#line 19334 "weaver-interface-metafont_en.cweb"

ERROR_FAILED_OPENING_FILE,
/*:709*//*713:*/
#line 19376 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:713*//*716:*/
#line 19406 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:716*//*719:*/
#line 19437 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_CHAR,
/*:719*//*722:*/
#line 19538 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_COMPARISON,
/*:722*//*725:*/
#line 19572 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:725*//*728:*/
#line 19613 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_NAME,
/*:728*//*731:*/
#line 19661 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_TENSION,
/*:731*//*734:*/
#line 19715 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_EXPRESSION,
/*:734*//*737:*/
#line 19745 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_TOKEN,
/*:737*//*740:*/
#line 19774 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:740*//*743:*/
#line 19801 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:743*//*746:*/
#line 19829 "weaver-interface-metafont_en.cweb"

ERROR_NESTED_BEGINCHAR,
/*:746*//*749:*/
#line 19857 "weaver-interface-metafont_en.cweb"

ERROR_NO_MEMORY,
/*:749*//*752:*/
#line 19907 "weaver-interface-metafont_en.cweb"

ERROR_NO_PICKUP_PEN,
/*:752*//*755:*/
#line 19939 "weaver-interface-metafont_en.cweb"

ERROR_NONCYCLICAL_PEN,
/*:755*//*758:*/
#line 19965 "weaver-interface-metafont_en.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:758*//*761:*/
#line 19993 "weaver-interface-metafont_en.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:761*//*764:*/
#line 20047 "weaver-interface-metafont_en.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:764*//*767:*/
#line 20081 "weaver-interface-metafont_en.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:767*//*770:*/
#line 20109 "weaver-interface-metafont_en.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:770*//*773:*/
#line 20144 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:773*//*776:*/
#line 20173 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_STRING,
/*:776*//*779:*/
#line 20210 "weaver-interface-metafont_en.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:779*//*782:*/
#line 20238 "weaver-interface-metafont_en.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:782*//*785:*/
#line 20270 "weaver-interface-metafont_en.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:785*//*788:*/
#line 20305 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:788*//*791:*/
#line 20336 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:791*//*794:*/
#line 20366 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:794*//*797:*/
#line 20396 "weaver-interface-metafont_en.cweb"

ERROR_UNOPENED_DELIMITER,
/*:797*//*800:*/
#line 20425 "weaver-interface-metafont_en.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:800*//*803:*/
#line 20467 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:803*//*806:*/
#line 20507 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:806*/
#line 19134 "weaver-interface-metafont_en.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,

/*39:*/
#line 1221 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2466 "weaver-interface-metafont_en.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2734 "weaver-interface-metafont_en.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*200:*/
#line 5196 "weaver-interface-metafont_en.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:200*//*204:*/
#line 5362 "weaver-interface-metafont_en.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:204*//*205:*/
#line 5375 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:205*//*212:*/
#line 5600 "weaver-interface-metafont_en.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:212*//*216:*/
#line 5721 "weaver-interface-metafont_en.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:216*//*232:*/
#line 6005 "weaver-interface-metafont_en.cweb"

TYPE_NORMALDEVIATE,
/*:232*//*246:*/
#line 6333 "weaver-interface-metafont_en.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:246*//*266:*/
#line 6885 "weaver-interface-metafont_en.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:266*//*273:*/
#line 7025 "weaver-interface-metafont_en.cweb"

TYPE_TRANSFORMED,
/*:273*//*292:*/
#line 7421 "weaver-interface-metafont_en.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:292*//*299:*/
#line 7575 "weaver-interface-metafont_en.cweb"

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
#line 9223 "weaver-interface-metafont_en.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:360*//*372:*/
#line 9601 "weaver-interface-metafont_en.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:372*//*394:*/
#line 10118 "weaver-interface-metafont_en.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:394*//*406:*/
#line 10391 "weaver-interface-metafont_en.cweb"

TYPE_MAKEPATH,
/*:406*//*450:*/
#line 11535 "weaver-interface-metafont_en.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:450*//*462:*/
#line 11893 "weaver-interface-metafont_en.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:462*//*468:*/
#line 12057 "weaver-interface-metafont_en.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:468*//*472:*/
#line 12296 "weaver-interface-metafont_en.cweb"

TYPE_OR,
/*:472*//*478:*/
#line 12447 "weaver-interface-metafont_en.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:478*//*486:*/
#line 12926 "weaver-interface-metafont_en.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:486*//*491:*/
#line 13141 "weaver-interface-metafont_en.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:491*//*500:*/
#line 13363 "weaver-interface-metafont_en.cweb"

TYPE_PICKUP,
/*:500*//*576:*/
#line 16215 "weaver-interface-metafont_en.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16334 "weaver-interface-metafont_en.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16415 "weaver-interface-metafont_en.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16469 "weaver-interface-metafont_en.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*632:*/
#line 17673 "weaver-interface-metafont_en.cweb"

TYPE_SHIPIT,
/*:632*//*636:*/
#line 17776 "weaver-interface-metafont_en.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:636*//*645:*/
#line 18049 "weaver-interface-metafont_en.cweb"

TYPE_KERNING,
/*:645*//*651:*/
#line 18199 "weaver-interface-metafont_en.cweb"

TYPE_DEBUG,
/*:651*/
#line 19141 "weaver-interface-metafont_en.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19148 "weaver-interface-metafont_en.cweb"
#endif
#line 19149 "weaver-interface-metafont_en.cweb"
/*:693*/

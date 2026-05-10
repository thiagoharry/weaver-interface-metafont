/*702:*/
#line 19658 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19664 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*703:*/
#line 19687 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:703*//*706:*/
#line 19736 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:706*//*709:*/
#line 19758 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:709*//*712:*/
#line 19788 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:712*//*715:*/
#line 19833 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:715*//*718:*/
#line 19869 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:718*//*722:*/
#line 19910 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:722*//*725:*/
#line 19940 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:725*//*728:*/
#line 19972 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:728*//*731:*/
#line 20077 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:731*//*734:*/
#line 20112 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:734*//*737:*/
#line 20154 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:737*//*740:*/
#line 20202 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:740*//*743:*/
#line 20253 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:743*//*746:*/
#line 20283 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:746*//*749:*/
#line 20313 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:749*//*752:*/
#line 20341 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:752*//*755:*/
#line 20368 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:755*//*758:*/
#line 20395 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:758*//*761:*/
#line 20447 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:761*//*764:*/
#line 20480 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:764*//*767:*/
#line 20506 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:767*//*770:*/
#line 20534 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:770*//*773:*/
#line 20588 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:773*//*776:*/
#line 20622 "weaver-interface-metafont.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:776*//*779:*/
#line 20651 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:779*//*782:*/
#line 20687 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:782*//*785:*/
#line 20715 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:785*//*788:*/
#line 20752 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:788*//*791:*/
#line 20780 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:791*//*794:*/
#line 20813 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:794*//*797:*/
#line 20846 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:797*//*800:*/
#line 20877 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:800*//*803:*/
#line 20908 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:803*//*806:*/
#line 20939 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:806*//*809:*/
#line 20968 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:809*//*812:*/
#line 21011 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:812*//*815:*/
#line 21049 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:815*/
#line 19667 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1282 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2549 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2815 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5329 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5497 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5510 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5747 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5873 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6161 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6492 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7048 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7188 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7598 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7754 "weaver-interface-metafont.cweb"

TYPE_CYCLE,
TYPE_AMPERSAND,
TYPE_JOIN,
TYPE_TENSION,
TYPE_AND,
TYPE_ATLEAST,
TYPE_CONTROLS,
TYPE_CURL,
TYPE_STRAIGHT_JOIN,
/*:300*//*361:*/
#line 9425 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9804 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10325 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10606 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11760 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12121 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12288 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12527 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12678 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13165 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13369 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13593 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*577:*/
#line 16513 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:577*//*585:*/
#line 16633 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:585*//*588:*/
#line 16715 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:588*//*593:*/
#line 16769 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:593*//*633:*/
#line 17982 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:633*//*637:*/
#line 18087 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:637*//*646:*/
#line 18359 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:646*//*652:*/
#line 18512 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:652*/
#line 19675 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19682 "weaver-interface-metafont.cweb"
#endif
#line 19683 "weaver-interface-metafont.cweb"
/*:702*/

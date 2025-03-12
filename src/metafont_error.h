/*675:*/
#line 19046 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19052 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*676:*/
#line 19075 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:676*//*679:*/
#line 19121 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:679*//*682:*/
#line 19143 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:682*//*685:*/
#line 19173 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:685*//*688:*/
#line 19218 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:688*//*691:*/
#line 19252 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:691*//*695:*/
#line 19293 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:695*//*698:*/
#line 19323 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:698*//*701:*/
#line 19355 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:701*//*704:*/
#line 19460 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:704*//*707:*/
#line 19493 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:707*//*710:*/
#line 19533 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:710*//*713:*/
#line 19579 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:713*//*716:*/
#line 19628 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:716*//*719:*/
#line 19658 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:719*//*722:*/
#line 19688 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:722*//*725:*/
#line 19716 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:725*//*728:*/
#line 19743 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:728*//*731:*/
#line 19770 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:731*//*734:*/
#line 19822 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:734*//*737:*/
#line 19855 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:737*//*740:*/
#line 19881 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:740*//*743:*/
#line 19909 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:743*//*746:*/
#line 19963 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:746*//*749:*/
#line 19997 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:749*//*752:*/
#line 20033 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:752*//*755:*/
#line 20061 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:755*//*758:*/
#line 20098 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:758*//*761:*/
#line 20126 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:761*//*764:*/
#line 20159 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:764*//*767:*/
#line 20190 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:767*//*770:*/
#line 20221 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:770*//*773:*/
#line 20252 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:773*//*776:*/
#line 20283 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:776*//*779:*/
#line 20312 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:779*//*782:*/
#line 20355 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:782*//*785:*/
#line 20393 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:785*/
#line 19055 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1250 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2516 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2782 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5293 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5461 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5474 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5711 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5837 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6125 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6456 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7012 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7152 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7559 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7715 "weaver-interface-metafont.cweb"

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
#line 9382 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9761 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10282 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10563 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11715 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12083 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12250 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12489 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12640 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13127 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13331 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13555 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*576:*/
#line 16404 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16524 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16606 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16660 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*631:*/
#line 17859 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:631*//*635:*/
#line 17964 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:635*//*644:*/
#line 18236 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:644*//*650:*/
#line 18389 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:650*/
#line 19063 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19070 "weaver-interface-metafont.cweb"
#endif
#line 19071 "weaver-interface-metafont.cweb"
/*:675*/

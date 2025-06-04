/*675:*/
#line 19058 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19064 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*676:*/
#line 19087 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:676*//*679:*/
#line 19133 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:679*//*682:*/
#line 19155 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:682*//*685:*/
#line 19185 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:685*//*688:*/
#line 19230 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:688*//*691:*/
#line 19264 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:691*//*695:*/
#line 19305 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:695*//*698:*/
#line 19335 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:698*//*701:*/
#line 19367 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:701*//*704:*/
#line 19472 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:704*//*707:*/
#line 19505 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:707*//*710:*/
#line 19545 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:710*//*713:*/
#line 19591 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:713*//*716:*/
#line 19640 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:716*//*719:*/
#line 19670 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:719*//*722:*/
#line 19700 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:722*//*725:*/
#line 19728 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:725*//*728:*/
#line 19755 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:728*//*731:*/
#line 19782 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:731*//*734:*/
#line 19834 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:734*//*737:*/
#line 19867 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:737*//*740:*/
#line 19893 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:740*//*743:*/
#line 19921 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:743*//*746:*/
#line 19975 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:746*//*749:*/
#line 20009 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:749*//*752:*/
#line 20045 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:752*//*755:*/
#line 20073 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:755*//*758:*/
#line 20110 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:758*//*761:*/
#line 20138 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:761*//*764:*/
#line 20171 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:764*//*767:*/
#line 20202 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:767*//*770:*/
#line 20233 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:770*//*773:*/
#line 20264 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:773*//*776:*/
#line 20295 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:776*//*779:*/
#line 20324 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:779*//*782:*/
#line 20367 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:782*//*785:*/
#line 20405 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:785*/
#line 19067 "weaver-interface-metafont.cweb"


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
#line 2517 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2783 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5295 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5463 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5476 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5713 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5839 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6127 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6458 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7014 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7154 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7561 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7717 "weaver-interface-metafont.cweb"

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
#line 9384 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9763 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10284 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10565 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11717 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12085 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12252 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12491 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12642 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13129 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13333 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13557 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*576:*/
#line 16406 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16526 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16608 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16662 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*631:*/
#line 17861 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:631*//*635:*/
#line 17966 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:635*//*644:*/
#line 18238 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:644*//*650:*/
#line 18391 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:650*/
#line 19075 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19082 "weaver-interface-metafont.cweb"
#endif
#line 19083 "weaver-interface-metafont.cweb"
/*:675*/

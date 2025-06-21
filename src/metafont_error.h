/*679:*/
#line 19107 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19113 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*680:*/
#line 19136 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:680*//*683:*/
#line 19185 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:683*//*686:*/
#line 19207 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:686*//*689:*/
#line 19237 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:689*//*692:*/
#line 19282 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:692*//*695:*/
#line 19318 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:695*//*699:*/
#line 19359 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:699*//*702:*/
#line 19389 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:702*//*705:*/
#line 19421 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:705*//*708:*/
#line 19526 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:708*//*711:*/
#line 19561 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:711*//*714:*/
#line 19603 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:714*//*717:*/
#line 19651 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:717*//*720:*/
#line 19702 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:720*//*723:*/
#line 19732 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:723*//*726:*/
#line 19762 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:726*//*729:*/
#line 19790 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:729*//*732:*/
#line 19817 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:732*//*735:*/
#line 19844 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:735*//*738:*/
#line 19896 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:738*//*741:*/
#line 19929 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:741*//*744:*/
#line 19955 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:744*//*747:*/
#line 19983 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:747*//*750:*/
#line 20037 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:750*//*753:*/
#line 20071 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:753*//*756:*/
#line 20107 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:756*//*759:*/
#line 20135 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:759*//*762:*/
#line 20172 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:762*//*765:*/
#line 20200 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:765*//*768:*/
#line 20233 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:768*//*771:*/
#line 20266 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:771*//*774:*/
#line 20297 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:774*//*777:*/
#line 20328 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:777*//*780:*/
#line 20359 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:780*//*783:*/
#line 20388 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:783*//*786:*/
#line 20431 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:786*//*789:*/
#line 20469 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:789*/
#line 19116 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1253 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2520 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2786 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5300 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5468 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5481 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5718 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5844 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6132 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6463 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7019 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7159 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7569 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7725 "weaver-interface-metafont.cweb"

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
#line 9392 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9771 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10292 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10573 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11727 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12088 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12255 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12494 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12645 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13132 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13336 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13560 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*576:*/
#line 16409 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16529 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16611 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16665 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*632:*/
#line 17878 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:632*//*636:*/
#line 17983 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:636*//*645:*/
#line 18255 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:645*//*651:*/
#line 18408 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:651*/
#line 19124 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19131 "weaver-interface-metafont.cweb"
#endif
#line 19132 "weaver-interface-metafont.cweb"
/*:679*/

/*679:*/
#line 19169 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19175 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*680:*/
#line 19198 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:680*//*683:*/
#line 19247 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:683*//*686:*/
#line 19269 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:686*//*689:*/
#line 19299 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:689*//*692:*/
#line 19344 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:692*//*695:*/
#line 19380 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:695*//*699:*/
#line 19421 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:699*//*702:*/
#line 19451 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:702*//*705:*/
#line 19483 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:705*//*708:*/
#line 19588 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:708*//*711:*/
#line 19623 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:711*//*714:*/
#line 19665 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:714*//*717:*/
#line 19713 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:717*//*720:*/
#line 19764 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:720*//*723:*/
#line 19794 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:723*//*726:*/
#line 19824 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:726*//*729:*/
#line 19852 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:729*//*732:*/
#line 19879 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:732*//*735:*/
#line 19906 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:735*//*738:*/
#line 19958 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:738*//*741:*/
#line 19991 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:741*//*744:*/
#line 20017 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:744*//*747:*/
#line 20045 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:747*//*750:*/
#line 20099 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:750*//*753:*/
#line 20133 "weaver-interface-metafont.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:753*//*756:*/
#line 20162 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:756*//*759:*/
#line 20198 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:759*//*762:*/
#line 20226 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:762*//*765:*/
#line 20263 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:765*//*768:*/
#line 20291 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:768*//*771:*/
#line 20324 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:771*//*774:*/
#line 20357 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:774*//*777:*/
#line 20388 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:777*//*780:*/
#line 20419 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:780*//*783:*/
#line 20450 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:783*//*786:*/
#line 20479 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:786*//*789:*/
#line 20522 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:789*//*792:*/
#line 20560 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:792*/
#line 19178 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1256 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2523 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2789 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5303 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5471 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5484 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5721 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5847 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6135 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6466 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7022 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7162 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7572 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7728 "weaver-interface-metafont.cweb"

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
#line 9399 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9778 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10299 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10580 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11734 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12095 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12262 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12501 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12652 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13139 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13343 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13567 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*576:*/
#line 16471 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16591 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16673 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16727 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*632:*/
#line 17940 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:632*//*636:*/
#line 18045 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:636*//*645:*/
#line 18317 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:645*//*651:*/
#line 18470 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:651*/
#line 19186 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19193 "weaver-interface-metafont.cweb"
#endif
#line 19194 "weaver-interface-metafont.cweb"
/*:679*/

/*680:*/
#line 19127 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19133 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*681:*/
#line 19156 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:681*//*684:*/
#line 19205 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:684*//*687:*/
#line 19227 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:687*//*690:*/
#line 19257 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:690*//*693:*/
#line 19302 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:693*//*696:*/
#line 19338 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:696*//*700:*/
#line 19379 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:700*//*703:*/
#line 19409 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:703*//*706:*/
#line 19441 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:706*//*709:*/
#line 19546 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:709*//*712:*/
#line 19581 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:712*//*715:*/
#line 19623 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:715*//*718:*/
#line 19671 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:718*//*721:*/
#line 19722 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:721*//*724:*/
#line 19752 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:724*//*727:*/
#line 19782 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:727*//*730:*/
#line 19810 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:730*//*733:*/
#line 19837 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:733*//*736:*/
#line 19864 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:736*//*739:*/
#line 19916 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:739*//*742:*/
#line 19949 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:742*//*745:*/
#line 19975 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:745*//*748:*/
#line 20003 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:748*//*751:*/
#line 20057 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:751*//*754:*/
#line 20091 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:754*//*757:*/
#line 20127 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:757*//*760:*/
#line 20155 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:760*//*763:*/
#line 20192 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:763*//*766:*/
#line 20220 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:766*//*769:*/
#line 20253 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:769*//*772:*/
#line 20286 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:772*//*775:*/
#line 20317 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:775*//*778:*/
#line 20348 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:778*//*781:*/
#line 20379 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:781*//*784:*/
#line 20408 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:784*//*787:*/
#line 20451 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:787*//*790:*/
#line 20489 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:790*/
#line 19136 "weaver-interface-metafont.cweb"


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
/*:592*//*633:*/
#line 17890 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:633*//*637:*/
#line 17995 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:637*//*646:*/
#line 18267 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:646*//*652:*/
#line 18420 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:652*/
#line 19144 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19151 "weaver-interface-metafont.cweb"
#endif
#line 19152 "weaver-interface-metafont.cweb"
/*:680*/

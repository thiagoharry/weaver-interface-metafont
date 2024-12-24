/*659:*/
#line 18645 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 18651 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*660:*/
#line 18674 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:660*//*663:*/
#line 18720 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:663*//*666:*/
#line 18742 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:666*//*669:*/
#line 18772 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:669*//*672:*/
#line 18817 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:672*//*675:*/
#line 18851 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:675*//*679:*/
#line 18892 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:679*//*682:*/
#line 18922 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:682*//*685:*/
#line 18954 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:685*//*688:*/
#line 19059 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:688*//*691:*/
#line 19092 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:691*//*694:*/
#line 19132 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:694*//*697:*/
#line 19178 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:697*//*700:*/
#line 19227 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:700*//*703:*/
#line 19257 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:703*//*706:*/
#line 19287 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:706*//*709:*/
#line 19315 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:709*//*712:*/
#line 19342 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:712*//*715:*/
#line 19369 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:715*//*718:*/
#line 19421 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:718*//*721:*/
#line 19454 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:721*//*724:*/
#line 19480 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:724*//*727:*/
#line 19508 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:727*//*730:*/
#line 19562 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:730*//*733:*/
#line 19596 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:733*//*736:*/
#line 19632 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:736*//*739:*/
#line 19660 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:739*//*742:*/
#line 19697 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:742*//*745:*/
#line 19725 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:745*//*748:*/
#line 19758 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:748*//*751:*/
#line 19789 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:751*//*754:*/
#line 19820 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:754*//*757:*/
#line 19851 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:757*//*760:*/
#line 19882 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:760*//*763:*/
#line 19911 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:763*//*766:*/
#line 19954 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:766*//*769:*/
#line 19992 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:769*/
#line 18654 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1246 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2512 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2778 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5292 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5460 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5473 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5710 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5836 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6124 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6455 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7011 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7150 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7557 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7713 "weaver-interface-metafont.cweb"

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
#line 9380 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9759 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10280 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10561 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11711 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12079 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12246 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12485 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12636 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13123 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13327 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13551 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*576:*/
#line 16397 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16517 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16599 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16653 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*631:*/
#line 17851 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:631*//*635:*/
#line 17956 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:635*/
#line 18662 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 18669 "weaver-interface-metafont.cweb"
#endif
#line 18670 "weaver-interface-metafont.cweb"
/*:659*/

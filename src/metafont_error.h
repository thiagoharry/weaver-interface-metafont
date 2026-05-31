/*739:*/
#line 20493 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 20499 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*740:*/
#line 20522 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:740*//*743:*/
#line 20571 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:743*//*746:*/
#line 20593 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:746*//*749:*/
#line 20623 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:749*//*752:*/
#line 20668 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:752*//*755:*/
#line 20704 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:755*//*759:*/
#line 20745 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:759*//*762:*/
#line 20775 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:762*//*765:*/
#line 20807 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:765*//*768:*/
#line 20912 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:768*//*771:*/
#line 20947 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:771*//*774:*/
#line 20989 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:774*//*777:*/
#line 21037 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:777*//*780:*/
#line 21088 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:780*//*783:*/
#line 21118 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:783*//*786:*/
#line 21148 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:786*//*789:*/
#line 21176 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:789*//*792:*/
#line 21203 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:792*//*795:*/
#line 21230 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:795*//*798:*/
#line 21282 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:798*//*801:*/
#line 21315 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:801*//*804:*/
#line 21341 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:804*//*807:*/
#line 21369 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:807*//*810:*/
#line 21423 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:810*//*813:*/
#line 21457 "weaver-interface-metafont.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:813*//*816:*/
#line 21486 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:816*//*819:*/
#line 21522 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:819*//*822:*/
#line 21550 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:822*//*825:*/
#line 21587 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:825*//*828:*/
#line 21615 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:828*//*831:*/
#line 21648 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:831*//*834:*/
#line 21681 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:834*//*837:*/
#line 21712 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:837*//*840:*/
#line 21743 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:840*//*843:*/
#line 21774 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:843*//*846:*/
#line 21803 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:846*//*849:*/
#line 21846 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:849*//*852:*/
#line 21884 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:852*/
#line 20502 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1294 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2561 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2827 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5341 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5509 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5522 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5759 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5885 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6173 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6504 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7060 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7200 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7610 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7766 "weaver-interface-metafont.cweb"

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
#line 9437 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9816 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10337 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10618 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11772 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12133 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12300 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12539 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12690 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13177 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13381 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13605 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*577:*/
#line 16525 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:577*//*585:*/
#line 16645 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:585*//*588:*/
#line 16727 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:588*//*593:*/
#line 16781 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:593*//*633:*/
#line 17994 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:633*//*637:*/
#line 18099 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:637*//*646:*/
#line 18371 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:646*//*652:*/
#line 18524 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:652*/
#line 20510 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 20517 "weaver-interface-metafont.cweb"
#endif
#line 20518 "weaver-interface-metafont.cweb"
/*:739*/

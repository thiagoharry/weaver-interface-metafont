/*701:*/
#line 19636 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19642 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*702:*/
#line 19665 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:702*//*705:*/
#line 19714 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:705*//*708:*/
#line 19736 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:708*//*711:*/
#line 19766 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:711*//*714:*/
#line 19811 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:714*//*717:*/
#line 19847 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:717*//*721:*/
#line 19888 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:721*//*724:*/
#line 19918 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:724*//*727:*/
#line 19950 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:727*//*730:*/
#line 20055 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:730*//*733:*/
#line 20090 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:733*//*736:*/
#line 20132 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:736*//*739:*/
#line 20180 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:739*//*742:*/
#line 20231 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:742*//*745:*/
#line 20261 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:745*//*748:*/
#line 20291 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:748*//*751:*/
#line 20319 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:751*//*754:*/
#line 20346 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:754*//*757:*/
#line 20373 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:757*//*760:*/
#line 20425 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:760*//*763:*/
#line 20458 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:763*//*766:*/
#line 20484 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:766*//*769:*/
#line 20512 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:769*//*772:*/
#line 20566 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:772*//*775:*/
#line 20600 "weaver-interface-metafont.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:775*//*778:*/
#line 20629 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:778*//*781:*/
#line 20665 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:781*//*784:*/
#line 20693 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:784*//*787:*/
#line 20730 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:787*//*790:*/
#line 20758 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:790*//*793:*/
#line 20791 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:793*//*796:*/
#line 20824 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:796*//*799:*/
#line 20855 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:799*//*802:*/
#line 20886 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:802*//*805:*/
#line 20917 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:805*//*808:*/
#line 20946 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:808*//*811:*/
#line 20989 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:811*//*814:*/
#line 21027 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:814*/
#line 19645 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1280 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2547 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2813 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5327 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5495 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5508 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5745 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5871 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6159 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6490 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7046 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7186 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7596 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7752 "weaver-interface-metafont.cweb"

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
#line 9423 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9802 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10323 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10604 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11758 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12119 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12286 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12525 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12676 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13163 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13367 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13591 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*577:*/
#line 16511 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:577*//*585:*/
#line 16631 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:585*//*588:*/
#line 16713 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:588*//*593:*/
#line 16767 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:593*//*633:*/
#line 17980 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:633*//*637:*/
#line 18085 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:637*//*646:*/
#line 18357 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:646*//*652:*/
#line 18510 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:652*/
#line 19653 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19660 "weaver-interface-metafont.cweb"
#endif
#line 19661 "weaver-interface-metafont.cweb"
/*:701*/

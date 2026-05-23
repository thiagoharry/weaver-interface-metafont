/*717:*/
#line 20026 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 20032 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*718:*/
#line 20055 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:718*//*721:*/
#line 20104 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:721*//*724:*/
#line 20126 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:724*//*727:*/
#line 20156 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:727*//*730:*/
#line 20201 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:730*//*733:*/
#line 20237 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:733*//*737:*/
#line 20278 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:737*//*740:*/
#line 20308 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:740*//*743:*/
#line 20340 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:743*//*746:*/
#line 20445 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:746*//*749:*/
#line 20480 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:749*//*752:*/
#line 20522 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:752*//*755:*/
#line 20570 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:755*//*758:*/
#line 20621 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:758*//*761:*/
#line 20651 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:761*//*764:*/
#line 20681 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:764*//*767:*/
#line 20709 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:767*//*770:*/
#line 20736 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:770*//*773:*/
#line 20763 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:773*//*776:*/
#line 20815 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:776*//*779:*/
#line 20848 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:779*//*782:*/
#line 20874 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:782*//*785:*/
#line 20902 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:785*//*788:*/
#line 20956 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:788*//*791:*/
#line 20990 "weaver-interface-metafont.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:791*//*794:*/
#line 21019 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:794*//*797:*/
#line 21055 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:797*//*800:*/
#line 21083 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:800*//*803:*/
#line 21120 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:803*//*806:*/
#line 21148 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:806*//*809:*/
#line 21181 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:809*//*812:*/
#line 21214 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:812*//*815:*/
#line 21245 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:815*//*818:*/
#line 21276 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:818*//*821:*/
#line 21307 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:821*//*824:*/
#line 21336 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:824*//*827:*/
#line 21379 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:827*//*830:*/
#line 21417 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:830*/
#line 20035 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1286 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2553 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2819 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5333 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5501 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5514 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5751 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5877 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6165 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6496 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7052 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7192 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7602 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7758 "weaver-interface-metafont.cweb"

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
#line 9429 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9808 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10329 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10610 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11764 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12125 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12292 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12531 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12682 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13169 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13373 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13597 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*577:*/
#line 16517 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:577*//*585:*/
#line 16637 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:585*//*588:*/
#line 16719 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:588*//*593:*/
#line 16773 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:593*//*633:*/
#line 17986 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:633*//*637:*/
#line 18091 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:637*//*646:*/
#line 18363 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:646*//*652:*/
#line 18516 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:652*/
#line 20043 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 20050 "weaver-interface-metafont.cweb"
#endif
#line 20051 "weaver-interface-metafont.cweb"
/*:717*/

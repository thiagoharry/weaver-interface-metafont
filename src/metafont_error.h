/*708:*/
#line 19821 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19827 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*709:*/
#line 19850 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:709*//*712:*/
#line 19899 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:712*//*715:*/
#line 19921 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:715*//*718:*/
#line 19951 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:718*//*721:*/
#line 19996 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:721*//*724:*/
#line 20032 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:724*//*728:*/
#line 20073 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:728*//*731:*/
#line 20103 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:731*//*734:*/
#line 20135 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:734*//*737:*/
#line 20240 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:737*//*740:*/
#line 20275 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:740*//*743:*/
#line 20317 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:743*//*746:*/
#line 20365 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:746*//*749:*/
#line 20416 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:749*//*752:*/
#line 20446 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:752*//*755:*/
#line 20476 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:755*//*758:*/
#line 20504 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:758*//*761:*/
#line 20531 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:761*//*764:*/
#line 20558 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:764*//*767:*/
#line 20610 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:767*//*770:*/
#line 20643 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:770*//*773:*/
#line 20669 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:773*//*776:*/
#line 20697 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:776*//*779:*/
#line 20751 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:779*//*782:*/
#line 20785 "weaver-interface-metafont.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:782*//*785:*/
#line 20814 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:785*//*788:*/
#line 20850 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:788*//*791:*/
#line 20878 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:791*//*794:*/
#line 20915 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:794*//*797:*/
#line 20943 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:797*//*800:*/
#line 20976 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:800*//*803:*/
#line 21009 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:803*//*806:*/
#line 21040 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:806*//*809:*/
#line 21071 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:809*//*812:*/
#line 21102 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:812*//*815:*/
#line 21131 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:815*//*818:*/
#line 21174 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:818*//*821:*/
#line 21212 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:821*/
#line 19830 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1288 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2555 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2821 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5335 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5503 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5516 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5753 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5879 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6167 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6498 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7054 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7194 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7604 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7760 "weaver-interface-metafont.cweb"

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
#line 9431 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9810 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10331 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10612 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11766 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12127 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12294 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12533 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12684 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13171 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13375 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13599 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*577:*/
#line 16519 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:577*//*585:*/
#line 16639 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:585*//*588:*/
#line 16721 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:588*//*593:*/
#line 16775 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:593*//*633:*/
#line 17988 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:633*//*637:*/
#line 18093 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:637*//*646:*/
#line 18365 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:646*//*652:*/
#line 18518 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:652*/
#line 19838 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19845 "weaver-interface-metafont.cweb"
#endif
#line 19846 "weaver-interface-metafont.cweb"
/*:708*/

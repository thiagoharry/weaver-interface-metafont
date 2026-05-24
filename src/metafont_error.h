/*723:*/
#line 20155 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 20161 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*724:*/
#line 20184 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:724*//*727:*/
#line 20233 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:727*//*730:*/
#line 20255 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:730*//*733:*/
#line 20285 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:733*//*736:*/
#line 20330 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:736*//*739:*/
#line 20366 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:739*//*743:*/
#line 20407 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:743*//*746:*/
#line 20437 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:746*//*749:*/
#line 20469 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:749*//*752:*/
#line 20574 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:752*//*755:*/
#line 20609 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:755*//*758:*/
#line 20651 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:758*//*761:*/
#line 20699 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:761*//*764:*/
#line 20750 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:764*//*767:*/
#line 20780 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:767*//*770:*/
#line 20810 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:770*//*773:*/
#line 20838 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:773*//*776:*/
#line 20865 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:776*//*779:*/
#line 20892 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:779*//*782:*/
#line 20944 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:782*//*785:*/
#line 20977 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:785*//*788:*/
#line 21003 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:788*//*791:*/
#line 21031 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:791*//*794:*/
#line 21085 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:794*//*797:*/
#line 21119 "weaver-interface-metafont.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:797*//*800:*/
#line 21148 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:800*//*803:*/
#line 21184 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:803*//*806:*/
#line 21212 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:806*//*809:*/
#line 21249 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:809*//*812:*/
#line 21277 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:812*//*815:*/
#line 21310 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:815*//*818:*/
#line 21343 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:818*//*821:*/
#line 21374 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:821*//*824:*/
#line 21405 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:824*//*827:*/
#line 21436 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:827*//*830:*/
#line 21465 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:830*//*833:*/
#line 21508 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:833*//*836:*/
#line 21546 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:836*/
#line 20164 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1290 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2557 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2823 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5337 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5505 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5518 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5755 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5881 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6169 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6500 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7056 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7196 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7606 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7762 "weaver-interface-metafont.cweb"

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
#line 9433 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9812 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10333 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10614 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11768 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12129 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12296 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12535 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12686 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13173 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13377 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13601 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*577:*/
#line 16521 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:577*//*585:*/
#line 16641 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:585*//*588:*/
#line 16723 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:588*//*593:*/
#line 16777 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:593*//*633:*/
#line 17990 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:633*//*637:*/
#line 18095 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:637*//*646:*/
#line 18367 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:646*//*652:*/
#line 18520 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:652*/
#line 20172 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 20179 "weaver-interface-metafont.cweb"
#endif
#line 20180 "weaver-interface-metafont.cweb"
/*:723*/

/*665:*/
#line 18806 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 18812 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*666:*/
#line 18835 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:666*//*669:*/
#line 18881 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:669*//*672:*/
#line 18903 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:672*//*675:*/
#line 18933 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:675*//*678:*/
#line 18978 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:678*//*681:*/
#line 19012 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:681*//*685:*/
#line 19053 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:685*//*688:*/
#line 19083 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:688*//*691:*/
#line 19115 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:691*//*694:*/
#line 19220 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:694*//*697:*/
#line 19253 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:697*//*700:*/
#line 19293 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:700*//*703:*/
#line 19339 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:703*//*706:*/
#line 19388 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:706*//*709:*/
#line 19418 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:709*//*712:*/
#line 19448 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:712*//*715:*/
#line 19476 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:715*//*718:*/
#line 19503 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:718*//*721:*/
#line 19530 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:721*//*724:*/
#line 19582 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:724*//*727:*/
#line 19615 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:727*//*730:*/
#line 19641 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:730*//*733:*/
#line 19669 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:733*//*736:*/
#line 19723 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:736*//*739:*/
#line 19757 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:739*//*742:*/
#line 19793 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:742*//*745:*/
#line 19821 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:745*//*748:*/
#line 19858 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:748*//*751:*/
#line 19886 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:751*//*754:*/
#line 19919 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:754*//*757:*/
#line 19950 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:757*//*760:*/
#line 19981 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:760*//*763:*/
#line 20012 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:763*//*766:*/
#line 20043 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:766*//*769:*/
#line 20072 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:769*//*772:*/
#line 20115 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:772*//*775:*/
#line 20153 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:775*/
#line 18815 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1248 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2514 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2780 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5291 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5459 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5472 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5709 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5835 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6123 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6454 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7010 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7149 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7556 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7712 "weaver-interface-metafont.cweb"

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
#line 9379 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9758 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10279 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10560 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11710 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12078 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12245 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12484 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12635 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13122 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13326 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13550 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*576:*/
#line 16401 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16521 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16603 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16657 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*631:*/
#line 17856 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:631*//*635:*/
#line 17961 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:635*//*644:*/
#line 18233 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:644*/
#line 18823 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 18830 "weaver-interface-metafont.cweb"
#endif
#line 18831 "weaver-interface-metafont.cweb"
/*:665*/

/*659:*/
#line 18640 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 18646 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*660:*/
#line 18669 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:660*//*663:*/
#line 18715 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:663*//*666:*/
#line 18737 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:666*//*669:*/
#line 18767 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:669*//*672:*/
#line 18812 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:672*//*675:*/
#line 18846 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:675*//*679:*/
#line 18887 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:679*//*682:*/
#line 18917 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:682*//*685:*/
#line 18949 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:685*//*688:*/
#line 19054 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:688*//*691:*/
#line 19087 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:691*//*694:*/
#line 19127 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:694*//*697:*/
#line 19173 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:697*//*700:*/
#line 19222 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:700*//*703:*/
#line 19252 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:703*//*706:*/
#line 19282 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:706*//*709:*/
#line 19310 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:709*//*712:*/
#line 19337 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:712*//*715:*/
#line 19364 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:715*//*718:*/
#line 19416 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:718*//*721:*/
#line 19449 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:721*//*724:*/
#line 19475 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:724*//*727:*/
#line 19503 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:727*//*730:*/
#line 19557 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:730*//*733:*/
#line 19591 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:733*//*736:*/
#line 19627 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:736*//*739:*/
#line 19655 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:739*//*742:*/
#line 19692 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:742*//*745:*/
#line 19720 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:745*//*748:*/
#line 19753 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:748*//*751:*/
#line 19784 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:751*//*754:*/
#line 19815 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:754*//*757:*/
#line 19846 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:757*//*760:*/
#line 19877 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:760*//*763:*/
#line 19906 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:763*//*766:*/
#line 19949 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:766*//*769:*/
#line 19987 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:769*/
#line 18649 "weaver-interface-metafont.cweb"


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
#line 2510 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2776 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5290 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5458 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5471 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5708 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5834 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6122 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6453 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7009 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7148 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7555 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7711 "weaver-interface-metafont.cweb"

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
#line 9378 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9757 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10278 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10559 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11709 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12077 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12244 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12483 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12634 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13121 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13325 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13549 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*576:*/
#line 16395 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16515 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16597 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16651 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*631:*/
#line 17849 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:631*//*635:*/
#line 17954 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:635*/
#line 18657 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 18664 "weaver-interface-metafont.cweb"
#endif
#line 18665 "weaver-interface-metafont.cweb"
/*:659*/

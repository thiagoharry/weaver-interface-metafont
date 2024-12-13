/*659:*/
#line 18624 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 18630 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*660:*/
#line 18653 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:660*//*663:*/
#line 18699 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:663*//*666:*/
#line 18721 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:666*//*669:*/
#line 18751 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:669*//*672:*/
#line 18796 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:672*//*675:*/
#line 18830 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:675*//*679:*/
#line 18871 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:679*//*682:*/
#line 18901 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:682*//*685:*/
#line 18933 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:685*//*688:*/
#line 19038 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:688*//*691:*/
#line 19071 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:691*//*694:*/
#line 19111 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:694*//*697:*/
#line 19157 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:697*//*700:*/
#line 19206 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:700*//*703:*/
#line 19236 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:703*//*706:*/
#line 19266 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:706*//*709:*/
#line 19294 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:709*//*712:*/
#line 19321 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:712*//*715:*/
#line 19348 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:715*//*718:*/
#line 19400 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:718*//*721:*/
#line 19433 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:721*//*724:*/
#line 19459 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:724*//*727:*/
#line 19487 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:727*//*730:*/
#line 19541 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:730*//*733:*/
#line 19575 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:733*//*736:*/
#line 19611 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:736*//*739:*/
#line 19639 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:739*//*742:*/
#line 19676 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:742*//*745:*/
#line 19704 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:745*//*748:*/
#line 19737 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:748*//*751:*/
#line 19768 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:751*//*754:*/
#line 19799 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:754*//*757:*/
#line 19830 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:757*//*760:*/
#line 19861 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:760*//*763:*/
#line 19890 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:763*//*766:*/
#line 19933 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:766*//*769:*/
#line 19971 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:769*/
#line 18633 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1245 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2509 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2775 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5289 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5457 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5470 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5707 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5833 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6121 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6452 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7008 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7147 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7554 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7710 "weaver-interface-metafont.cweb"

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
#line 9377 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9756 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10277 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10558 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11708 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12076 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12243 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12482 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12633 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13107 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13311 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13535 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*576:*/
#line 16379 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16499 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16581 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16635 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*631:*/
#line 17833 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:631*//*635:*/
#line 17938 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:635*/
#line 18641 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 18648 "weaver-interface-metafont.cweb"
#endif
#line 18649 "weaver-interface-metafont.cweb"
/*:659*/

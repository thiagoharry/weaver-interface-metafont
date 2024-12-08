/*655:*/
#line 18382 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 18388 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*656:*/
#line 18411 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:656*//*659:*/
#line 18457 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:659*//*662:*/
#line 18479 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:662*//*665:*/
#line 18509 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:665*//*668:*/
#line 18554 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:668*//*671:*/
#line 18588 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:671*//*675:*/
#line 18629 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:675*//*678:*/
#line 18659 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:678*//*681:*/
#line 18691 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:681*//*684:*/
#line 18796 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:684*//*687:*/
#line 18829 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:687*//*690:*/
#line 18869 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:690*//*693:*/
#line 18915 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:693*//*696:*/
#line 18964 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:696*//*699:*/
#line 18994 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:699*//*702:*/
#line 19024 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:702*//*705:*/
#line 19052 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:705*//*708:*/
#line 19079 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:708*//*711:*/
#line 19106 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:711*//*714:*/
#line 19158 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:714*//*717:*/
#line 19191 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:717*//*720:*/
#line 19217 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:720*//*723:*/
#line 19245 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:723*//*726:*/
#line 19299 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:726*//*729:*/
#line 19334 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:729*//*732:*/
#line 19370 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:732*//*735:*/
#line 19398 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:735*//*738:*/
#line 19435 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:738*//*741:*/
#line 19463 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:741*//*744:*/
#line 19496 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:744*//*747:*/
#line 19527 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:747*//*750:*/
#line 19558 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:750*//*753:*/
#line 19589 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:753*//*756:*/
#line 19620 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:756*//*759:*/
#line 19649 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:759*//*762:*/
#line 19692 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:762*//*765:*/
#line 19730 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:765*/
#line 18391 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1166 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2430 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2696 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5210 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5378 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5391 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5628 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5754 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6043 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6374 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 6929 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7068 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7475 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7631 "weaver-interface-metafont.cweb"

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
#line 9298 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9677 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10198 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10479 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11630 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 11998 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12165 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12404 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12555 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13029 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13233 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13457 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*576:*/
#line 16301 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16421 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16503 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16557 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*631:*/
#line 17750 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:631*//*635:*/
#line 17855 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:635*/
#line 18399 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 18406 "weaver-interface-metafont.cweb"
#endif
#line 18407 "weaver-interface-metafont.cweb"
/*:655*/

/*680:*/
#line 19185 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19191 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*681:*/
#line 19214 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:681*//*684:*/
#line 19263 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:684*//*687:*/
#line 19285 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:687*//*690:*/
#line 19315 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:690*//*693:*/
#line 19360 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:693*//*696:*/
#line 19396 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:696*//*700:*/
#line 19437 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:700*//*703:*/
#line 19467 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:703*//*706:*/
#line 19499 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:706*//*709:*/
#line 19604 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:709*//*712:*/
#line 19639 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:712*//*715:*/
#line 19681 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:715*//*718:*/
#line 19729 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:718*//*721:*/
#line 19780 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:721*//*724:*/
#line 19810 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:724*//*727:*/
#line 19840 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:727*//*730:*/
#line 19868 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:730*//*733:*/
#line 19895 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:733*//*736:*/
#line 19922 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:736*//*739:*/
#line 19974 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:739*//*742:*/
#line 20007 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:742*//*745:*/
#line 20033 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:745*//*748:*/
#line 20061 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:748*//*751:*/
#line 20115 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:751*//*754:*/
#line 20149 "weaver-interface-metafont.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:754*//*757:*/
#line 20178 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:757*//*760:*/
#line 20214 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:760*//*763:*/
#line 20242 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:763*//*766:*/
#line 20279 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:766*//*769:*/
#line 20307 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:769*//*772:*/
#line 20340 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:772*//*775:*/
#line 20373 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:775*//*778:*/
#line 20404 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:778*//*781:*/
#line 20435 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:781*//*784:*/
#line 20466 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:784*//*787:*/
#line 20495 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:787*//*790:*/
#line 20538 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:790*//*793:*/
#line 20576 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:793*/
#line 19194 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1256 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2523 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2789 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5303 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5471 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5484 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5721 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5847 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6135 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6466 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7022 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7162 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7572 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7728 "weaver-interface-metafont.cweb"

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
#line 9399 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9778 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10299 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10580 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11734 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12095 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12262 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12501 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12652 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13139 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13343 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13567 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*577:*/
#line 16487 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:577*//*585:*/
#line 16607 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:585*//*588:*/
#line 16689 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:588*//*593:*/
#line 16743 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:593*//*633:*/
#line 17956 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:633*//*637:*/
#line 18061 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:637*//*646:*/
#line 18333 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:646*//*652:*/
#line 18486 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:652*/
#line 19202 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19209 "weaver-interface-metafont.cweb"
#endif
#line 19210 "weaver-interface-metafont.cweb"
/*:680*/

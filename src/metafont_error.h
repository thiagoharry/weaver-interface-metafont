/*680:*/
#line 19114 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19120 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*681:*/
#line 19143 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:681*//*684:*/
#line 19192 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:684*//*687:*/
#line 19214 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:687*//*690:*/
#line 19244 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:690*//*693:*/
#line 19289 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:693*//*696:*/
#line 19325 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:696*//*700:*/
#line 19366 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:700*//*703:*/
#line 19396 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:703*//*706:*/
#line 19428 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:706*//*709:*/
#line 19533 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:709*//*712:*/
#line 19568 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:712*//*715:*/
#line 19610 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:715*//*718:*/
#line 19658 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:718*//*721:*/
#line 19709 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:721*//*724:*/
#line 19739 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:724*//*727:*/
#line 19769 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:727*//*730:*/
#line 19797 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:730*//*733:*/
#line 19824 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:733*//*736:*/
#line 19851 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:736*//*739:*/
#line 19903 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:739*//*742:*/
#line 19936 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:742*//*745:*/
#line 19962 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:745*//*748:*/
#line 19990 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:748*//*751:*/
#line 20044 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:751*//*754:*/
#line 20078 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:754*//*757:*/
#line 20114 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:757*//*760:*/
#line 20142 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:760*//*763:*/
#line 20179 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:763*//*766:*/
#line 20207 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:766*//*769:*/
#line 20240 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:769*//*772:*/
#line 20273 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:772*//*775:*/
#line 20304 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:775*//*778:*/
#line 20335 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:778*//*781:*/
#line 20366 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:781*//*784:*/
#line 20395 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:784*//*787:*/
#line 20438 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:787*//*790:*/
#line 20476 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:790*/
#line 19123 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1250 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2517 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2783 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5295 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5463 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5476 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5713 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5839 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6127 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6458 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7014 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7154 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7561 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7717 "weaver-interface-metafont.cweb"

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
#line 9384 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9763 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10284 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10565 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11719 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12080 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12247 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12486 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12637 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13124 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13328 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13552 "weaver-interface-metafont.cweb"

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
/*:592*//*633:*/
#line 17877 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:633*//*637:*/
#line 17982 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:637*//*646:*/
#line 18254 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:646*//*652:*/
#line 18407 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:652*/
#line 19131 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19138 "weaver-interface-metafont.cweb"
#endif
#line 19139 "weaver-interface-metafont.cweb"
/*:680*/

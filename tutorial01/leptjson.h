#ifndef LEPTJSON_H__
#define LEPTJSON_H__

typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT } lept_type;

//树状结构节点类型
typedef struct {
    lept_type type;
}lept_value;

//解析器返回值
enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

//解析JSON的API函数
int lept_parse(lept_value* v, const char* json);

//访问结果的函数
lept_type lept_get_type(const lept_value* v);

#endif /* LEPTJSON_H__ */

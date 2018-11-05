#ifndef LEPTJSON_H__
#define LEPTJSON_H__

#include <stddef.h> /* size_t */

typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT } lept_type;

typedef struct {
    union {
        struct { char* s; size_t len; }s;  /* string: null-terminated string, string length */
        double n;                          /* number */
    }u;
    lept_type type;
}lept_value;

// 程序执行解析过程中遇到各种崩溃时的反馈符号
enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR,
    LEPT_PARSE_NUMBER_TOO_BIG,
    LEPT_PARSE_MISS_QUOTATION_MARK,
    LEPT_PARSE_INVALID_STRING_ESCAPE,
    LEPT_PARSE_INVALID_STRING_CHAR,
    LEPT_PARSE_INVALID_UNICODE_HEX,
    LEPT_PARSE_INVALID_UNICODE_SURROGATE
};

//宏定义初始化操作：类型设为空
#define lept_init(v) do { (v)->type = LEPT_NULL; } while(0)

//主解析
int lept_parse(lept_value* v, const char* json);

//释放函数：如果v的类型是string，释放解析后字符串占用的空间。类型设置为空。
void lept_free(lept_value* v);

lept_type lept_get_type(const lept_value* v);

// 宏定义设置节点为空
#define lept_set_null(v) lept_free(v)


int lept_get_boolean(const lept_value* v);
void lept_set_boolean(lept_value* v, int b);

//获取n
//设置v的n和type变量
double lept_get_number(const lept_value* v);
void lept_set_number(lept_value* v, double n);

//获取字符串的值
//获取字符串的长度
//为s分配内存，设置结尾‘\0’、len、type变量
const char* lept_get_string(const lept_value* v);
size_t lept_get_string_length(const lept_value* v);
void lept_set_string(lept_value* v, const char* s, size_t len);

#endif /* LEPTJSON_H__ */

#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

//接收字符串部分
typedef struct {
    const char* json;
}lept_context;

//缩小字符串长度，过滤前面的空白部分
static void lept_parse_whitespace(lept_context* c) {
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

//判断是否是NULL，如果是就返回1，并且让v->type=NULL
//c->json 待解析字符串
//v->type等于NULL
static int lept_parse_null(lept_context* c, lept_value* v) {
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}

//解析value，这里只有两个，一是调用函数判断值是否为NULL，一个是判断是否合法
//*c->json == *(c->json) 代表一个字符值。
static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
        case 'n':  return lept_parse_null(c, v);
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
        default:   return LEPT_PARSE_INVALID_VALUE;
    }
}

//判断字符串中value部分是哪种类型
//首先接收树结构，并判断树为空
//接收字符串，把字符串给结构体中的变量
//设置树结构节点值为空。
//过滤字符串空白部分
//做一些接收参数和初始化的工作。去掉空白部分，判断value的部分是哪种类型
int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    return lept_parse_value(&c, v);
}

//获取值的类型
//判断传进来的树为空
//返回树的类型
lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}

#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

//这里json是个const数组，类型名是lept_context为了减少解析函数之间传递多个参数，我们把这些数据都放进一个 lept_context 结构体
typedef struct {
    const char* json;
}lept_context;

//跳过空白，这个函数现阶段还没有处理value之后的空白部分或者多于字符部分
static void lept_parse_whitespace(lept_context* c) { //为什么要用static？实参是引用，这里形参用的是指针
    const char *p = c->json; //为什么要用const？指针的指向不能改变？下边代码改变了呀，这里意思应该是，不要改动c所指向的字符串，但是可以改变c的指向。
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;//我觉得这里c应该指向json非空格部分了
}

//解析NULL
static int lept_parse_null(lept_context* c, lept_value* v) {
    EXPECT(c, 'n');//如果json开头字母不等于n就终止程序。
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}

//解析数值,返回的是int型？
static int lept_parse_value(lept_context* c, lept_value* v) {//json字符部分
    switch (*c->json) {
        case 'n':  return lept_parse_null(c, v);//
        case '\0': return LEPT_PARSE_EXPECT_VALUE;//JSON 只含有空白
        default:   return LEPT_PARSE_INVALID_VALUE;//值不是那三种字面值
    }
}

//解析器的API函数：把json字符串变为tree
int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL); //如果树不为空，就终止程序
    c.json = json;//json就是从服务器传过来的字符串，这里用c.json说明c不是指针，而是一个结构体（只包含一个名为json的指针，因为后面json数组也是指针表
    //示的，所以可以传值，不用&符，即，c.json指向了传过来的字符串数组的头部）
    v->type = LEPT_NULL;//初始值设置为NULL，注意这里值为"LEPT_NULL"与空不相同。这里"LEPT_NULL"是一个枚举类型的值。
    lept_parse_whitespace(&c);
    return lept_parse_value(&c, v);
}

//获取类型
lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}

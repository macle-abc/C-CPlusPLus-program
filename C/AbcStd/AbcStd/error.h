#ifndef ABCSTD_ERROR_H_
#define ABCSTD_ERROR_H_

#define INVALID_ARGUMENT	1 //使用了无效参数
#define DOMAIN_ERROR		2 //使用了一个无效的数学域时
#define LENGTH_ERROR		3 //试图超过一些对象的实现定义长度所导致的错误
#define OUT_OF_RANGE		4 //访问试图受定义范围外的元素所带来的错误

#define RANG_ERROR			11 //计算结果不能以目标类型表示的情形
#define OVERFLOW_ERROR		12 //用于报告算数上溢错误
#define UNDERFLOW_ERROR		13 //用于报告算数下溢错误

#define BAD_ALLOC			21 //内存分配失败
#endif // !ABCSTD_ERROR_H_

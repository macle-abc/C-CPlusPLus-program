#pragma once
#include "UIAssistance.h"
#include "..//Lib/String/__string.h"

void readToTemp(mystring* des,const char* path);//使用前des需要初始化
void saveFromTemp(mystring* temp, const char* path);//使用前temp需要初始化
void clickOpen();
void clickSave();


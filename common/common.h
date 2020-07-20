/*************************************************************************
	> File Name: common.h
	> Author: 
	> Mail: 
	> Created Time: 一  7/20 21:29:55 2020
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
extern char conf_ans[512];
char *get_conf_value(const char *path, const char *key);
printf("name=%s\n", get_conf_value("./football.conf", "NAME"));

#endif

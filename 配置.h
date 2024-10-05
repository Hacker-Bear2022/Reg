#pragma once


int 读配置(wstring 节名称, wstring 项名称);

void 写配置(wstring 节名称, wstring 项名称, wstring 数据);

std::wstring 桌面路径();

wstring 读配置文本(wstring 节名称, wstring 项名称);

int 取输入框内容(HWND 输入框句柄, std::wstring& content);

char* GetRegistryValueAsString(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName);
#pragma once


int ������(wstring ������, wstring ������);

void д����(wstring ������, wstring ������, wstring ����);

std::wstring ����·��();

wstring �������ı�(wstring ������, wstring ������);

int ȡ���������(HWND �������, std::wstring& content);

char* GetRegistryValueAsString(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName);
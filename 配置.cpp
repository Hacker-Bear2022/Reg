#include "framework.h"


int 读配置(wstring 节名称, wstring 项名称)
{
	wstring 文件路径 = 桌面路径() + L"\\" + L"EA86.ini";
	return GetPrivateProfileIntW(节名称.c_str(), 项名称.c_str(), 0, 文件路径.c_str());
}

void 写配置(wstring 节名称, wstring 项名称, wstring 数据)
{
	wstring 文件路径 = 桌面路径() + L"\\" + L"EA86.ini";
	WritePrivateProfileStringW(节名称.c_str(), 项名称.c_str(), 数据.c_str(), 文件路径.c_str());
}

std::wstring 桌面路径()
{
	LPWSTR path[255];
	ZeroMemory(path, 255);
	SHGetSpecialFolderPath(0, (LPWSTR)path, CSIDL_DESKTOPDIRECTORY, 0);
	wstring 局_路径 = ((LPWSTR)path);
	wstring 局_斜线 = L"\\";
	局_路径 = 局_路径 + 局_斜线;
	return 	局_路径;
}

wstring 读配置文本(wstring 节名称, wstring 项名称)
{
	wstring 文件路径 = 桌面路径() + L"\\" + L"EA86.ini";
	wchar_t 缓冲区[4096];
	GetPrivateProfileStringW(节名称.c_str(), 项名称.c_str(), L"", 缓冲区, 4096, 文件路径.c_str());
	return 缓冲区;
}

int 取输入框内容(HWND 输入框句柄, std::wstring& content)
{
    // 获取输入框中文本的长度
    int textLength = GetWindowTextLengthW(输入框句柄) + 1; // 包含末尾的空字符
    if (textLength <= 0)
    {
        content.clear();
        return 0;
    }

    // 分配缓冲区来存储文本
    std::vector<wchar_t> buffer(textLength);

    // 获取文本
    int result = GetWindowTextW(输入框句柄, &buffer[0], textLength);
    if (result > 0)
    {
        // 将缓冲区内容转换为 std::wstring
        content.assign(buffer.begin(), buffer.begin() + result); // 包括末尾的空字符
    }
    else
    {
        content.clear();
    }

    return result;
}

char* GetRegistryValueAsString(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName)
{
    HKEY hKey;
    DWORD dwType;
    DWORD dwSize;
    std::wstring wstrValue;
    char* cstrValue = nullptr;

    // 打开注册表项
    if (RegOpenKeyEx(hKeyRoot, subKey.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        // 查询注册表值的类型和大小
        if (RegQueryValueEx(hKey, valueName.c_str(), NULL, &dwType, NULL, &dwSize) == ERROR_SUCCESS)
        {
            if (dwType == REG_SZ)
            {
                // 分配内存以存储字符串值
                std::vector<char> buffer(dwSize);
                if (RegQueryValueEx(hKey, valueName.c_str(), NULL, NULL, (LPBYTE)&buffer[0], &dwSize) == ERROR_SUCCESS)
                {
                    // 将宽字符串转换为窄字符串
                    int sizeNeeded = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)&buffer[0], -1, NULL, 0, NULL, NULL);
                    std::vector<char>窄字符串(buffer.begin(), buffer.end());
                    cstrValue = new char[sizeNeeded];
                    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)&buffer[0], -1, cstrValue, sizeNeeded, NULL, NULL);
                }
            }
        }

        RegCloseKey(hKey);
    }

    return cstrValue;
}
#include "framework.h"


int ������(wstring ������, wstring ������)
{
	wstring �ļ�·�� = ����·��() + L"\\" + L"EA86.ini";
	return GetPrivateProfileIntW(������.c_str(), ������.c_str(), 0, �ļ�·��.c_str());
}

void д����(wstring ������, wstring ������, wstring ����)
{
	wstring �ļ�·�� = ����·��() + L"\\" + L"EA86.ini";
	WritePrivateProfileStringW(������.c_str(), ������.c_str(), ����.c_str(), �ļ�·��.c_str());
}

std::wstring ����·��()
{
	LPWSTR path[255];
	ZeroMemory(path, 255);
	SHGetSpecialFolderPath(0, (LPWSTR)path, CSIDL_DESKTOPDIRECTORY, 0);
	wstring ��_·�� = ((LPWSTR)path);
	wstring ��_б�� = L"\\";
	��_·�� = ��_·�� + ��_б��;
	return 	��_·��;
}

wstring �������ı�(wstring ������, wstring ������)
{
	wstring �ļ�·�� = ����·��() + L"\\" + L"EA86.ini";
	wchar_t ������[4096];
	GetPrivateProfileStringW(������.c_str(), ������.c_str(), L"", ������, 4096, �ļ�·��.c_str());
	return ������;
}

int ȡ���������(HWND �������, std::wstring& content)
{
    // ��ȡ��������ı��ĳ���
    int textLength = GetWindowTextLengthW(�������) + 1; // ����ĩβ�Ŀ��ַ�
    if (textLength <= 0)
    {
        content.clear();
        return 0;
    }

    // ���仺�������洢�ı�
    std::vector<wchar_t> buffer(textLength);

    // ��ȡ�ı�
    int result = GetWindowTextW(�������, &buffer[0], textLength);
    if (result > 0)
    {
        // ������������ת��Ϊ std::wstring
        content.assign(buffer.begin(), buffer.begin() + result); // ����ĩβ�Ŀ��ַ�
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

    // ��ע�����
    if (RegOpenKeyEx(hKeyRoot, subKey.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        // ��ѯע���ֵ�����ͺʹ�С
        if (RegQueryValueEx(hKey, valueName.c_str(), NULL, &dwType, NULL, &dwSize) == ERROR_SUCCESS)
        {
            if (dwType == REG_SZ)
            {
                // �����ڴ��Դ洢�ַ���ֵ
                std::vector<char> buffer(dwSize);
                if (RegQueryValueEx(hKey, valueName.c_str(), NULL, NULL, (LPBYTE)&buffer[0], &dwSize) == ERROR_SUCCESS)
                {
                    // �����ַ���ת��Ϊխ�ַ���
                    int sizeNeeded = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)&buffer[0], -1, NULL, 0, NULL, NULL);
                    std::vector<char>խ�ַ���(buffer.begin(), buffer.end());
                    cstrValue = new char[sizeNeeded];
                    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)&buffer[0], -1, cstrValue, sizeNeeded, NULL, NULL);
                }
            }
        }

        RegCloseKey(hKey);
    }

    return cstrValue;
}
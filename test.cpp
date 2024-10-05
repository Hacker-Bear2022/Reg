#include <Windows.h>
#include <sal.h>  // 包含SAL定义
#include "resource.h"
#include"framework.h"

HWND 选择框句柄;
HWND 输入框句柄;
HWND 登陆按钮句柄;
HWND 卸载按钮句柄;
int 选择框状态;
// 控件ID定义


// 定义窗口过程函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// 使用SAL批注
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	// 注册窗口类
	WNDCLASSW wc = { };
	wc.lpfnWndProc = WndProc;// 设置窗口过程函数
	wc.hInstance = hInstance;// 设置实例句柄
	wc.lpszClassName = L"BY：228470874";// 设置窗口类名

	// 加载图标
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));  // 假设 IDI_ICON1 是你的图标资源的标识符

	RegisterClassW(&wc);// 注册窗口类
	SetProcessDPIAware();// 使进程 DPI 意识化，确保在高 DPI 显示器上正确显示
	// 创建窗口
	HWND hWnd = CreateWindowW(L"BY：228470874", L"EA86", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 400, 150, nullptr, nullptr, hInstance, nullptr);  // 增加窗口高度以容纳更多控件
	if (!hWnd)
	{
		return FALSE;// 如果创建窗口失败，返回 FALSE 并退出应用程序
	}

	_SetMachinecode(TRUE, TRUE, FALSE, FALSE, FALSE);//设置程序机器码
	_Verificationbegins(IP, HOSTSHORT, COPYRIGHT, VERSIONNUMBER, NULL, 0);//验证初始化

	char buf[1000] = { 0 };
	//检查更新函数
	bool ret1 = _CheckForUpdates(buf);

	// 创建复选框
	选择框句柄 = CreateWindowExW(0, L"BUTTON", L"记住卡号", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		280, 10, 100, 25, hWnd, (HMENU)IDC_CHECKBOXCONTROL, GetModuleHandle(nullptr), nullptr);
	if (读配置(L"Path", L"记住密码") != 1)
	{
		SendMessage(选择框句柄, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	if (读配置(L"Path", L"记住密码") == 1)
	{
		SendMessage(选择框句柄, BM_SETCHECK, BST_CHECKED, 0);
	}

	// 获取复选框的状态
	选择框状态 = (int)SendMessage(选择框句柄, BM_GETCHECK, 0, 0);
	std::wstring 卡密 = 读配置文本(L"Path", L"卡密");

	// 根据状态进行相应的处理
	switch (选择框状态)
	{
	case BST_UNCHECKED:
		SetWindowTextW(输入框句柄, L"");
		break;
	case BST_CHECKED:
		SetWindowTextW(输入框句柄, 卡密.c_str());
		break;
	}

	// 显示和更新窗口
	ShowWindow(hWnd, nCmdShow);// 根据 nCmdShow 参数显示窗口
	UpdateWindow(hWnd);// 更新窗口内容

	// 运行消息循环
	MSG msg = { };
	while (GetMessage(&msg, nullptr, 0, 0))// 从消息队列中获取消息
	{
		TranslateMessage(&msg);// 将虚拟键消息转换为字符消息
		DispatchMessage(&msg);// 分发消息到相应的窗口过程
	}

	return 0;// 当 GetMessage 返回 0（即接收到 WM_QUIT 消息）时，退出消息循环并返回 0
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		// 创建文本框
		输入框句柄 = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			70, 10, 200, 25, hWnd, (HMENU)IDC_EDITCONTROL, GetModuleHandle(nullptr), nullptr);
		SendMessage(输入框句柄, EM_SETPASSWORDCHAR, (WPARAM)'*', 0);

		// 创建按钮
		HWND 登陆按钮句柄 = CreateWindowExW(0, L"BUTTON", L"登陆", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			200, 60, 50, 25, hWnd, (HMENU)IDC_BUTTON1, GetModuleHandle(nullptr), nullptr);

		// 创建第二个按钮
		HWND 卸载按钮句柄 = CreateWindowExW(0, L"BUTTON", L"卸载", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			100, 60, 50, 25, hWnd, (HMENU)IDC_BUTTON2, GetModuleHandle(nullptr), nullptr);

		// 创建标签
		HWND hWndLabel = CreateWindowExW(0, L"STATIC", L"卡密：", WS_CHILD | WS_VISIBLE | SS_CENTER,
			10, 10, 60, 25, hWnd, (HMENU)IDC_LABELCONTROL, GetModuleHandle(nullptr), nullptr);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
	{
		char 返回值[10000];
		std::wstring 输入框内容;
		int bufferSize;
		bool ret3;
		char* narrowString;
		char* 安装目录;
		WPARAM id = LOWORD(wParam);
		switch (id)
		{
		case IDC_CHECKBOXCONTROL:
			if ((int)SendMessage(选择框句柄, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				写配置(L"Path", L"记住密码", L"1");
			}
			if ((int)SendMessage(选择框句柄, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				写配置(L"Path", L"记住密码", L"0");
			}
			break;
		case IDC_EDITCONTROL:
			// 处理文本框事件
			break;
		case IDC_BUTTON1://登陆按钮被单击
			取输入框内容(输入框句柄, 输入框内容);
			// 使用 WideCharToMultiByte 进行转换
			bufferSize = WideCharToMultiByte(CP_ACP, 0, 输入框内容.c_str(), -1, NULL, 0, NULL, NULL);
			narrowString = new char[bufferSize];
			WideCharToMultiByte(CP_ACP, 0, 输入框内容.c_str(), -1, narrowString, bufferSize, NULL, NULL);

			ret3 = _CardLogin(narrowString, 返回值);
			if (ret3)
			{
				if ((int)SendMessage(选择框句柄, BM_GETCHECK, 0, 0) == BST_CHECKED)
				{
					写配置(L"Path", L"卡密", 输入框内容.c_str());
				}
				MessageBoxA(hWnd, 返回值, "信息", MB_OK);
				ExitProcess(0);


			}
			// 清理分配的内存
			delete[] narrowString;
			break;
		case IDC_BUTTON2://卸载按钮被单击
			// 处理第二个按钮点击事件
			MessageBox(hWnd, L"按钮2被点击了！", L"信息", MB_OK);
			break;
		default:
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}
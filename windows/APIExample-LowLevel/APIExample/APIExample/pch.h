// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
#include "CConfig.h"
#include "Language.h"
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <vector>
#include <string>
#include "sdk_api.h"
#include <afxcontrolbars.h>
#include <shellscalingapi.h>
#pragma comment(lib, "Shcore.lib")
#pragma comment (lib, "agora_rtc_sdk")
#define APP_ID               _T("")
#define MAIN_AREA_TOP 20
#define MULTI_CAMERA_CONNECTED               WM_USER + 0x00000001
#define MULTI_CAMERA_DISCONNECTED            WM_USER + 0x00000002
#define MULTI_CAMERA_SUBSCRIBE_VIDEO_TRACKS  WM_USER + 0x00000003
std::string cs2utf8(CString str);
CString utf82cs(std::string utf8);
CString getCurrentTime();
extern std::string appid;

#endif //PCH_H

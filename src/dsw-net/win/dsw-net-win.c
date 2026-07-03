#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
#include "dsw-net/win/dsw-net-win.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

//delete this \/ on release
#define BOT_TOKEN
#define APP_ID
#define USER_ID

#ifndef BOT_TOKEN
#error "BOT_TOKEN must be defined at compile time (-DBOT_TOKEN=L\"...\")"
#endif

#ifndef APP_ID
#error "APP_ID must be defined at compile time (-DAPP_ID=L\"...\")"
#endif

#ifndef USER_ID
#error "USER_ID must be defined at compile time (-DUSER_ID=L\"...\")"
#endif

uint32_t fetch_github_stats(t_gsr *result, t_cpr *config){
    memset(result, 0x00, sizeof(t_gsr));
    HINTERNET hFetchSession = WinHttpOpen(L"dsw-bot/0.1", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    HINTERNET hGithubConnect = WinHttpConnect(hFetchSession, L"api.github.com", INTERNET_DEFAULT_HTTPS_PORT, 0);
    
    HINTERNET hGithubRequest = WinHttpOpenRequest(hGithubConnect, L"GET", L"/users/lost-ctrl-s0nny13", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    WinHttpAddRequestHeaders(hGithubRequest, L"User-Agent: dsw-bot\r\n", (DWORD)-1, WINHTTP_ADDREQ_FLAG_ADD);
    BOOL sent = WinHttpSendRequest(hGithubRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
    printf((sent == TRUE)?"sent TRUE\n":"sent FALSE\n");
    BOOL received = WinHttpReceiveResponse(hGithubRequest, NULL);
    printf((received == TRUE)?"received TRUE":"received FALSE");
    DWORD status_code = 0;
    DWORD size = sizeof(status_code);
    WinHttpQueryHeaders(hGithubRequest, WINHTTP_QUERY_STATUS_CODE|WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &status_code, &size, WINHTTP_NO_HEADER_INDEX);
    char* body = NULL;
    size_t bodySize = 0;
    DWORD bytesAvailable = 0;
    do {
        WinHttpQueryDataAvailable(hGithubRequest, &bytesAvailable);
        if (bytesAvailable == 0) break;

        char* newBody = realloc(body, bodySize + bytesAvailable + 1);
        body = newBody;

        DWORD bytesRead = 0;
        WinHttpReadData(hGithubRequest, body + bodySize, bytesAvailable, &bytesRead);
        bodySize += bytesRead;
    } while (bytesAvailable > 0);

    printf("\nSTATUS_CODE: %lu", status_code);
    printf("\nRESPONSE:\n%s\n", body);

    WinHttpCloseHandle(hGithubRequest);
    WinHttpCloseHandle(hGithubConnect);
    WinHttpCloseHandle(hFetchSession);

    if (body) body[bodySize] = '\0';
        return 0;
}
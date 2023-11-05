#include "spoofer.h";


// Used GPT LOL for this function
std::string GetRandomString(int length, bool upperCase = false, bool onlyNumber = true)
{
    std::string chars = "abcdefghijklmnopqrstuvwxyz";
    if (upperCase)
        chars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (onlyNumber)
        chars = "0123456789abcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, chars.length() - 1);

    std::string randomString;
    for (int i = 0; i < length; ++i)
        randomString += chars[dist(gen)];

    return randomString;
}


std::string GetCryptoReg() {
	HKEY HHKEY;
	std::string Reg = "SOFTWARE\\Microsoft\\Cryptography";
	std::string RegValue = "MachineGuid";
	std::string KeyValue;


    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, Reg.c_str(), 0, KEY_READ, &HHKEY) == ERROR_SUCCESS)
    {
        char buffer[256];
        DWORD bufferSize = sizeof(buffer);

        if (RegQueryValueExA(HHKEY, RegValue.c_str(), nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer), &bufferSize) == ERROR_SUCCESS)
        {
            KeyValue = buffer;
        }

        RegCloseKey(HHKEY);
    }

    return KeyValue;
}





void SetHwidReg() {
    std::string RegName = "HwProfileGuid";
    HKEY HHKEY;
    std::string RegPath = "SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0001";
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, RegPath.c_str(), 0, KEY_SET_VALUE, &HHKEY) == ERROR_SUCCESS)
    {
        std::string random1 = GetRandomString(8);
        std::string random2 = GetRandomString(4);
        std::string random3 = GetRandomString(4);
        std::string random4 = GetRandomString(4);
        std::string random5 = GetRandomString(12);
        std::string randID3 = random1 + "-" + random2 + "-" + random3 + "-" + random4 + "-" + random5;

        RegSetValueExA(HHKEY, RegName.c_str(), 0, REG_SZ, (const BYTE*)randID3.c_str(), randID3.length());

        RegCloseKey(HHKEY);
    }

}

std::string GetHwidReg() {
    HKEY HHKEY;
    std::string Reg = "SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0001";
    std::string RegValue = "HwProfileGuid";
    std::string KeyValue;


    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, Reg.c_str(), 0, KEY_READ, &HHKEY) == ERROR_SUCCESS)
    {
        char buffer[256];
        DWORD bufferSize = sizeof(buffer);

        if (RegQueryValueExA(HHKEY, RegValue.c_str(), nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer), &bufferSize) == ERROR_SUCCESS)
        {
            KeyValue = buffer;
        }

        RegCloseKey(HHKEY);
    }
    std::string NewKey = KeyValue.substr(1, KeyValue.length() - 2);
    return NewKey;
}


bool RefreshUserProfile()
{
    HANDLE hToken;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))
    {
        return false;
    }

    wchar_t username[256];
    DWORD usernameSize = sizeof(username) / sizeof(username[0]);
    if (!GetUserName(username, &usernameSize))
    {
        CloseHandle(hToken);
        return false;
    }

    PROFILEINFO profileInfo = {};
    profileInfo.dwSize = sizeof(PROFILEINFO);
    profileInfo.lpUserName = username;
    profileInfo.dwFlags = PI_NOUI;

    if (!ImpersonateLoggedOnUser(hToken))
    {
        CloseHandle(hToken);
        return false;
    }

    if (!LoadUserProfile(hToken, &profileInfo))
    {
        RevertToSelf();
        CloseHandle(hToken);
        return false;
    }

    if (!UnloadUserProfile(hToken, profileInfo.hProfile))
    {
        RevertToSelf();
        CloseHandle(hToken);
        return false;
    }

    RevertToSelf();
    CloseHandle(hToken);
    return true;
}

void SetCryptoReg() {
    std::string RegName = "MachineGuid";
    HKEY HHKEY;
    std::string RegPath = "SOFTWARE\\Microsoft\\Cryptography";
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, RegPath.c_str(), 0, KEY_SET_VALUE, &HHKEY) == ERROR_SUCCESS)
    {
        std::string random1 = GetRandomString(8);
        std::string random2 = GetRandomString(8);
        std::string random3 = GetRandomString(4);
        std::string random4 = GetRandomString(4);
        std::string random5 = GetRandomString(12);
        std::string randID3 = random1 + "-" + random2 + "-" + random3 + "-" + random4 + "-" + random5;

        RegSetValueExA(HHKEY, RegName.c_str(), 0, REG_SZ, (const BYTE*)randID3.c_str(), randID3.length());

        RegCloseKey(HHKEY);
    }

}

void refreshNTUserData()
{
    LPCWSTR cleanupUtilityPath = L"cleanmgr.exe";
    LPCWSTR cleanupParameters = L"/sagerun:65535";

    SHELLEXECUTEINFO shExInfo = { 0 };
    shExInfo.cbSize = sizeof(shExInfo);
    shExInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    shExInfo.hwnd = nullptr;
    shExInfo.lpVerb = L"open";
    shExInfo.lpFile = cleanupUtilityPath;
    shExInfo.lpParameters = cleanupParameters;
    shExInfo.lpDirectory = nullptr;
    shExInfo.nShow = SW_HIDE;
    shExInfo.hInstApp = nullptr;

    if (ShellExecuteEx(&shExInfo))
    {
        WaitForSingleObject(shExInfo.hProcess, INFINITE);
        CloseHandle(shExInfo.hProcess); // Close the handle when done
    }
    else
    {
        // Handle the error if ShellExecuteEx fails
        DWORD dwError = GetLastError();
        // You might want to log or handle the error accordingly
    }
}
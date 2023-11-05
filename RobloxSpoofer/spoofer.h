#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <random>
#include <Shlobj.h>
#include <Userenv.h>
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Userenv.lib")

std::string GetCryptoReg();
void SetCryptoReg();
bool RefreshUserProfile();
std::string GetHwidReg();
void SetHwidReg();
void refreshNTUserData();
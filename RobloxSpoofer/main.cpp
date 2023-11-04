#include "console.h";
#include "spoofer.h";
bool IsRunningAsAdmin() {
	BOOL isAdmin = FALSE;
	PSID adminGroup = NULL;

	SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
	if (!AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0, &adminGroup)) {
		return false;
	}

	if (!CheckTokenMembership(NULL, adminGroup, &isAdmin)) {
		isAdmin = FALSE;
	}

	FreeSid(adminGroup);
	return isAdmin == TRUE;
}

int main() {
	SetConsoleTitleA("RxSpoofer");
	Header();

	if (!IsRunningAsAdmin()) {
		Error("You need to run this spoofer as administrator!");
		Success("Press any key to exit...");
		system("pause > nul");
		return 0;
	}

	if (!GetCryptoReg().empty()) {
		Success("Your previous MUID: " + GetCryptoReg());
		SetCryptoReg();
		Success("Your new MUID: " + GetCryptoReg());
	}
	else {
		Error("Failed to retrieve MUID!");
		Success("Press any key to exit...");
		system("pause > nul");
		return 0;
	}
	if (!GetHwidReg().empty()) {
		Success("Your previous HWID: " + GetHwidReg());
		SetHwidReg();
		Success("Your new HWID: " + GetHwidReg());
	}

	if (RefreshUserProfile()) {
		Success("Sucessfully refreshed user profile!");
	}

	Success("Sucessfully spoofed!");
	Success("Press any key to exit...");
	system("pause > nul");
	return 0;
}
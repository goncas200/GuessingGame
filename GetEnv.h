#pragma once

#include <iostream>
std::string env(std::string envname) {
	char* envresult;
	size_t len;
	errno_t err = _dupenv_s(&envresult, &len, envname.c_str());
	return envresult;
}
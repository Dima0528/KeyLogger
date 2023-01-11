#pragma once
#include <msclr\marshal_cppstd.h>
#include <string>

ref class CastingUtils
{
public:
	static std::string castAsString(System::String^ str) {
		return msclr::interop::marshal_as<std::string>(str);
	}

	static System::String^ castAsString(std::string str) {
		return gcnew System::String(str.c_str());
	}
	static System::String^ castAsString(int num) {
		return System::Convert::ToString(num);
	}
};

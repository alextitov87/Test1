#ifndef RUSTEXTRECODER_H
#define RUSTEXTRECODER_H
#include <string>
#include <cstring>
#include <stdexcept>

class RusTextRecoderClass
{
	public:
        static std::string ANSI866toUTF8(std::string line);
        static std::string UTF8toANSI866(std::string line);
		static bool isHaveUTF8_rus(std::string line);		
	protected:
		static int findInUTF8(std::string str);
        static int findInANSI866(char c);
        static char ansi_866_aplhabet[];
		static char utf8_rus_aplhabet[];
        static char ansi_1251_aplhabet[];
		
};
#endif

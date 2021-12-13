#include "rustextrecoderclass.h"



char RusTextRecoderClass::ansi_866_aplhabet[] ={-96, -95, -94, -93, -92, -91, -15, -90, -89, -88, -87, -86, -85, -84, -83, -82, -81, -32, -31, -30, -29, -28, -27, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17, -128, -127, -126, -125, -124, -123, -16, -122, -121, -120, -119, -118, -117, -116, -115, -114, -113, -112, -111, -110, -109, -108, -107, -106, -105, -104, -103, -102, -101, -100, -99, -98, -97};
char RusTextRecoderClass::ansi_1251_aplhabet[] ={-32, -31, -30, -29, -28, -27, -72, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, -64, -63, -62, -61, -60, -59, -88, -58, -57, -56, -55, -54, -53, -52, -51, -50, -49, -48, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38, -37, -36, -35, -34, -33};
char RusTextRecoderClass::utf8_rus_aplhabet[] ={-48, -80, -48, -79, -48, -78, -48, -77, -48, -76, -48, -75, -47, -111, -48, -74, -48, -73, -48, -72, -48, -71, -48, -70, -48, -69, -48, -68, -48, -67, -48, -66, -48, -65, -47, -128, -47, -127, -47, -126, -47, -125, -47, -124, -47, -123, -47, -122, -47, -121, -47, -120, -47, -119, -47, -118, -47, -117, -47, -116, -47, -115, -47, -114, -47, -113, -48, -112, -48, -111, -48, -110, -48, -109, -48, -108, -48, -107, -48, -127, -48, -106, -48, -105, -48, -104, -48, -103, -48, -102, -48, -101, -48, -100, -48, -99, -48, -98, -48, -97, -48, -96, -48, -95, -48, -94, -48, -93, -48, -92, -48, -91, -48, -90, -48, -89, -48, -88, -48, -87, -48, -86, -48, -85, -48, -84, -48, -83, -48, -82, -48, -81};

int RusTextRecoderClass::findInUTF8(std::string str)
{
	
	if (str.length()!=2)
		throw std::runtime_error("UTF-8 char challenger must have length = 2");
	for(int i=0; i<(sizeof(utf8_rus_aplhabet)-1); i=i+2)
		if (str.at(0)==utf8_rus_aplhabet[i] && str.at(1)==utf8_rus_aplhabet[i+1])
			return(i/2);
	return -1;
}

int RusTextRecoderClass::findInANSI866(char c)
{	

    for(int i=0; i<sizeof(ansi_866_aplhabet); i++)
        if (c==ansi_866_aplhabet[i] )
			return(i);
	return -1;
}

std::string RusTextRecoderClass::UTF8toANSI866(std::string line)
{
	std::string result="";
	for (int i=0; i<line.length(); i++)
	{
		if(i==line.length()-1)
		{
			result+=line.at(i);
			break;
		}
		int r = findInUTF8(line.substr(i,2));			
		if (r<0)
			result+=line.at(i);
		else
		{
            result+=ansi_866_aplhabet[r];
			i++;
		}
	}	
	return result;
}

std::string RusTextRecoderClass::ANSI866toUTF8(std::string line)
{
    std::string result="";

    for (int i=0; i<line.length(); i++)
	{
        int r = findInANSI866(line.at(i));
        if (r<0)
            result+=line.at(i);
		else
		{
            result+=utf8_rus_aplhabet[r*2];
            result+=utf8_rus_aplhabet[r*2+1];
		}
	}
	return result;
}

bool RusTextRecoderClass::isHaveUTF8_rus(std::string line)
{
	for (int i=0; i<line.length(); i++)
	{
		if(i==line.length()-1)
		{
			return false;
		}
		int r = findInUTF8(line.substr(i,2));
		if (r>=0)
			return true;
	}
	return false;
}



/*checks for pragma once support*/
// check this site: https://en.wikipedia.org/wiki/Pragma_once
#if (defined(__SUNPRO_C)&&(__SUNPRO_C>=0x5140))||(defined(__SUNPRO_CC)&&(__SUNPRO_CC>=0x5140))
        //Oracle Developer Studio C/C++ (12.5 or later)
#    define _pragma_once_support 1
#elif defined(_MSC_VER)&&(_MSC_VER>=1020)	//MSVC
#    define _pragma_once_support 1
#elif defined(__clang__)		//clang
#    define _pragma_once_support 1
#elif defined(__COMO__)			//comeau
#    define _pragma_once_support 1
#elif defined(__CODEGEARC__)&&(__CODEGEARC__ >=650)
        //C++Builder (XE3 or greater)
#    define _pragma_once_support 1
#elif defined(__DMC__)			//Digital Mars
#    define _pragma_once_support 1
#elif defined(__GNUC__)&&((__GNUC__ >3)||(defined(__GNUC_MINOR__)&&(__GNUC__ ==3)&&(__GNUC_MINOR__ >=4)))
        //GCC
#    define _pragma_once_support 1
#elif defined(__HP_aCC)&&(__HP_aCC >=61200)
        //HP aC++ (A.06.12)
#    define _pragma_once_support 1
#elif defined(__xlC__)&&((__xlC__ >1301)||((__xlC__ ==1301)&&(__xlC_ver__ >0100)))
        //IBM
#    define _pragma_once_support 1
#elif defined(__INTEL_COMPILER)||defined(__ICC)||defined(__ECC)||defined(__ICL)
        //intel
#    define _pragma_once_support 1
#elif defined(__POCC__)			//Pelles C
#    define _pragma_once_support 1
#elif defined(__CC_ARM)			//ARM compiler
#    define _pragma_once_support 1
#elif defined(__IAR_SYSTEMS_ICC__)	//IAR C/C++
#    define _pragma_once_support 1
#elif defined(__PGI)			//Portland Group C/C++
#    define _pragma_once_support 0
#else							//Unknown
#    define _pragma_once_support 0
#endif

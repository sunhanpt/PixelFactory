#include "AFilePackage.h"

unsigned int AFPCK_GUARDBYTE0 = 0xfdfdfeee;
unsigned int AFPCK_GUARDBYTE1 = 0xf00dbeef;
unsigned int AFPCK_MASKDWORD = 0xa8937462;
unsigned int AFPCK_CHECKMASK = 0x59374231;

unsigned __int64 AFPCK_MASKDWORD_I64 = 0;
unsigned __int64 AFPCK_CHECKMASK_I64 = 0;

const DWORD SAFE_HEADER_TAG1_22 = 0x4DCA23EF;
const DWORD SAFE_HEADER_TAG2_22 = 0x56a089b7;

const DWORD SAFE_HEADER_TAG1 = 0x5EDB34F0;

#define ENTRY_BUFFER_SIZE (1024 * 1024)

extern std::hash_map<std::string, bool> _file_no_found_map;

AFilePackMan g_AFilePackMan;


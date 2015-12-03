#define _CRT_SECURE_NO_DEPRECATE /* When copiling in cygwin comment out this line*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 ******************************************************************************
 * Copilation macros
 *****************************************************************************/

#define DEBUG_PRINT
//#define CONCATINATE_CB1_AT_START
//#define DEBUG_1_PRINT

/**
 ******************************************************************************
 * Private definitions
 *****************************************************************************/

typedef enum GSN_BRFLASHLDR_BLOCK_OWNER_E
{
    GSN_BRFLASHLDR_BLOCK_OWNER_BR = 0,
    GSN_BRFLASHLDR_BLOCK_OWNER_AFW = 1,
    GSN_BRFLASHLDR_BLOCK_OWNER_WFW =2,

} GSN_BRFLASHLDR_BLOCK_OWNER_T;

typedef enum GSN_BRFLASHLDR_FLAG_E
{
    GSN_BRFLASHLDR_BLOCK_DESC_FLAG_LOADREMAPRUN = 0x1, /* bit 0 */
    GSN_BRFLASHLDR_BLOCK_DESC_FLAG_LOADREMAP = 0x2, /* bit 1 */
    GSN_BRFLASHLDR_BLOCK_DESC_FLAG_LOAD = 0x4 /* bit 2 */
}GSN_BRFLASHLDR_FLAG_T;

typedef struct GSN_BRFLASHLDR_BLOCK_DESC_S
{
    unsigned int offset;  /* offset starting from beginning of image */
    unsigned int size;    /* size of block in bytes */
    unsigned int programAddr; /* address for remapping */
    unsigned int sramAddr;
    unsigned short owner;   /* owner of block - who loads the block into sram */
    unsigned short flags;   /* flags + remap index, remap index is in upper 4 bits */

} GSN_BRFLASHLDR_BLOCK_DESC_T;

typedef struct GSN_BRFLASHLDR_CTL_BLOCK_S
{
    unsigned char     fwok[4];
    unsigned int      rev;
    unsigned int      ctlBlockSize; /* size of data following this field */
    GSN_BRFLASHLDR_BLOCK_DESC_T blockDesc[2];    /* stretchable array of block descriptors */
} GSN_BRFLASHLDR_CTL_BLOCK_T;


typedef struct GSN_BRFLASHLDR_SUPER_BLOCK_S
{
    unsigned char   flok[4];
    unsigned int    f0cb1;
    unsigned int    f0cb2;
    unsigned int    f1cb1;
    unsigned int    f1cb2;
    unsigned int    f2cb1;
    unsigned int    f2cb2;
} GSN_BRFLASHLDR_SUPAR_BLOCK_T;
/* used to calculate offset*/
#define APP_START_ADDRESS				0x00100000

#define ROM_PATCH_AUTO_SEC_START_NAME 	"ROM_PATCH_AUTO$$Base"
#define ROM_PATCH_AUTO_SEC_END_NAME 	"ROM_PATCH_AUTO$$Limit"

#define ROM_PATCH_FPT_SEC_START_NAME 	"ROM_PATCH_FPT_SECTION$$Base"
#define ROM_PATCH_FPT_SEC_END_NAME 		"ROM_PATCH_FPT_SECTION$$Limit"
#define STARTUP_FUNCTION_NAME 			"GsnStartup_Main"

#define APP_CODE_1_SEC_START_NAME 		"APP_CODE_SECTION_1$$Base"
#define APP_CODE_1_SEC_END_NAME 		"APP_CODE_SECTION_1$$Limit"
#define APP_CODE_2_SEC_START_NAME 		"APP_CODE_SECTION_2$$Base"
#define APP_CODE_2_SEC_END_NAME 		"APP_CODE_SECTION_2$$Limit"

/* Data Init section is the last section in app code*/
#define APP_DATA_INIT_SEC_START_NAME		"DATA_INIT_SECTION$$Base"
#define APP_DATA_INIT_SEC_END_NAME			"DATA_INIT_SECTION$$Limit"

#define FLASH_RESERVED_FOR_APP			(512 * 1024)
#define CB1_RESERVED_SIZE				(4 * 1024)
#define AUTO_PATCH_RESERVED_SIZE		(128 * 1024)
#define FPT_RESERVED_SIZE				(8 *1024)
#define STARTUP_CODE_RESERVED_SIZE		(1024 * 2)

#define STARTUP_CODE_OFFSET_INFLASH (CB1_RESERVED_SIZE+AUTO_PATCH_RESERVED_SIZE+FPT_RESERVED_SIZE)
#define STARTUP_CODE_SRAM_ADDR 			0x20000000

#define BUFFER_SIZE						(512 * 1024)

/**
 ******************************************************************************
 * Private function prototypes
 *****************************************************************************/

unsigned int get_value_from_map_file( char *pFileName, char* pStr );
unsigned char char_to_hex(unsigned char c);
unsigned int string_to_hex( unsigned char *pStr );
unsigned int closest_power_of_2( unsigned int value );
void createCtrlBlkFile(GSN_BRFLASHLDR_CTL_BLOCK_T *pCtrlBlk);

/**
 ******************************************************************************
 *Arg 1:- map file name with path
 *Arg 2:- bin file name with path
 *Arg 2:- output image file name with path
 *****************************************************************************/
int main(int argc, char *argv[])
{
    FILE *bin, *map, *finalBin;
	unsigned int autoPatchStartLoc, autoPatchEndLoc, autoPatchSize;
	unsigned int fptStartLoc;
    unsigned int appStartUpLoc;
//    unsigned int appCodeStartLoc;
	unsigned int appCode1StartLoc, appCode2StartLoc, appCode1EndLoc, appCode2EndLoc;
    unsigned int dataInitEndLoc, dataInitStartLoc;
	unsigned int appCodeOffset, appCodeSize;
	GSN_BRFLASHLDR_CTL_BLOCK_T ctrlBlk;
	unsigned char *buffer = NULL;

    if(argc != 4)
    {
        printf("please give <map file name with location> <bin file name with location> <output file name with location>\n");
        return;
    }
	buffer = (unsigned char *)malloc(BUFFER_SIZE);
	if(NULL == buffer)
	{
		printf("Memory Error\n");
		return -1;
	}
	/*open app bin file*/
	if(NULL == (bin = fopen(argv[2],"rb+")))
	{
		printf("Could Not open bin file\n");
		free(buffer);
		return -1;
	}
	/* open app image file*/
	if(NULL == (finalBin = fopen(argv[3], "wb+")))
	{
		printf("could Not create final image file\r");
		free(buffer);
		return -1;
	}

	/* Extract information from the map file*/
	if(0 == (autoPatchStartLoc = get_value_from_map_file(argv[1], ROM_PATCH_AUTO_SEC_START_NAME))) return -1;
	if(0 == (autoPatchEndLoc = get_value_from_map_file(argv[1], ROM_PATCH_AUTO_SEC_END_NAME))) return -1;
	if(0 == (fptStartLoc = get_value_from_map_file(argv[1], ROM_PATCH_FPT_SEC_START_NAME))) return -1;
	if(0 == (appStartUpLoc = get_value_from_map_file(argv[1], STARTUP_FUNCTION_NAME))) return -1;
    
    
	if(0 == (appCode1StartLoc = get_value_from_map_file(argv[1], APP_CODE_1_SEC_START_NAME))) return -1;
	if(0 == (appCode1EndLoc = get_value_from_map_file(argv[1], APP_CODE_1_SEC_END_NAME))) return -1;
    if(0 == (appCode2StartLoc = get_value_from_map_file(argv[1], APP_CODE_2_SEC_START_NAME))) return -1;
    if(0 == (appCode2EndLoc = get_value_from_map_file(argv[1], APP_CODE_2_SEC_END_NAME))) return -1;    
    
    if(0 == (dataInitEndLoc = get_value_from_map_file(argv[1], APP_DATA_INIT_SEC_END_NAME))) return -1;

    if(0 == (dataInitStartLoc = get_value_from_map_file(argv[1], APP_DATA_INIT_SEC_START_NAME))) return -1;

	
#ifdef DEBUG_PRINT
	printf("autoPatchStartLoc = 0x%x\n""autoPatchEndLoc = 0x%x\n"
			"fptStartLoc = 0x%x\n"
			"appStartUpLoc = 0x%x\n"
			"appCode1StartLoc = 0x%x\n"
			"dataInitStartLoc = 0x%x\n""dataInitEndLoc = 0x%x\n",
			autoPatchStartLoc, autoPatchEndLoc, 
			fptStartLoc, 
			appStartUpLoc, 
			appCode1StartLoc,
			dataInitStartLoc, dataInitEndLoc);
#endif
	autoPatchSize = autoPatchEndLoc - autoPatchStartLoc;
    
	/* construct CB 1 and place at 0x1000 */
	ctrlBlk.fwok[0] = 'f';
	ctrlBlk.fwok[1] = 'w';
	ctrlBlk.fwok[2] = 'o';
	ctrlBlk.fwok[3] = 'k';
	ctrlBlk.rev = 0;
	ctrlBlk.ctlBlockSize = sizeof(GSN_BRFLASHLDR_BLOCK_DESC_T);
	/* App Block Desriptor*/
	/*offset of GsnFlash_Startup() w.r.t  CtrlBlock location */
	ctrlBlk.blockDesc[0].offset = (CB1_RESERVED_SIZE+autoPatchSize+FPT_RESERVED_SIZE);
	ctrlBlk.blockDesc[0].size = STARTUP_CODE_RESERVED_SIZE;/* Startup code size*/
	ctrlBlk.blockDesc[0].programAddr = appStartUpLoc;/* Remap address */
	ctrlBlk.blockDesc[0].sramAddr = STARTUP_CODE_SRAM_ADDR;/* Placeing in RAM auto patch region as its temporarily used*/
	ctrlBlk.blockDesc[0].owner = GSN_BRFLASHLDR_BLOCK_OWNER_BR;
	ctrlBlk.blockDesc[0].flags = GSN_BRFLASHLDR_BLOCK_DESC_FLAG_LOADREMAPRUN;

	memset(buffer, 0, CB1_RESERVED_SIZE);
	memcpy(buffer,(unsigned char *)&ctrlBlk,sizeof( GSN_BRFLASHLDR_CTL_BLOCK_T ));
#ifdef CONCATINATE_CB1_AT_START
    fwrite( buffer, CB1_RESERVED_SIZE, 1, finalBin);
#endif
	createCtrlBlkFile(&ctrlBlk);   
#ifdef DEBUG_PRINT
	{
		unsigned int i;
		printf("Auto Patch Size = 0x%x\n", autoPatchSize);
		//printf("\nControl Block:\n");
		//for (i = 0; i < sizeof(ctrlBlk); i+= 4)
			//printf("%x %x %x %x\n",buffer[i+0],buffer[i+1],buffer[i+2],buffer[i+3]);
    }
#endif
	/*Place auto patch at 0x2000*/
	memset(buffer, 0, AUTO_PATCH_RESERVED_SIZE);
	fread( buffer, AUTO_PATCH_RESERVED_SIZE, 1, bin);
    printf("After AutoPatch Read, BIN offset = 0x%x\n", ftell( bin ));
#ifdef DEBUG_PRINT
	printf("Placing Auto patch at offset = 0x%x\n", ftell( finalBin ));
#endif
    fwrite( buffer, autoPatchSize, 1, finalBin);

	/* place FPT at 0x22000 */
	memset(buffer, 0, FPT_RESERVED_SIZE);
	fread( buffer, FPT_RESERVED_SIZE, 1, bin);
#ifdef DEBUG_PRINT
	printf("Placing FPT at offset = 0x%x\n", ftell( finalBin ));
#endif
    fwrite( buffer, FPT_RESERVED_SIZE, 1, finalBin);

	/* place flash start up code at 0x24000 */
	memset(buffer, 0, STARTUP_CODE_RESERVED_SIZE);

#ifdef DEBUG_PRINT
		printf("Reading Start Up Code at offset = 0x%x\n", ftell( bin ));
#endif
	fread( buffer, STARTUP_CODE_RESERVED_SIZE, 1, bin);
#ifdef DEBUG_PRINT
	printf("Placing Start Up Code at offset = 0x%x\n", ftell( finalBin ));
#endif
    fwrite( buffer, STARTUP_CODE_RESERVED_SIZE, 1, finalBin);

	/* place app code at 0x24800 */
    printf("\n\nPlaceing App Code 1\n\n""\nappCode1StartLoc  = %x \n" "\nappCode1EndLoc  = %x \n",
           appCode1StartLoc, appCode1EndLoc);
    
	appCodeOffset = appCode1StartLoc - APP_START_ADDRESS;
	appCodeSize = appCode1EndLoc - appCode1StartLoc;//dataInitEndLoc - appCodeStartLoc;
    fseek( bin, appCodeOffset, SEEK_SET);

#ifdef DEBUG_PRINT
	printf("\nApp Code 1 Size = %x \n""Reading App Code at offset = 0x%x\n""Placing App Code at offset = 0x%x\n",
			appCodeSize, ftell( bin ), ftell( finalBin ));
#endif
	fread( buffer, appCodeSize, 1, bin);
    fwrite( buffer, appCodeSize, 1, finalBin);

   	/* place app code at 0x24800 */
    printf("\n\nPlaceing App Code 2\n\n""\nappCode2StartLoc  = %x \n" "\nappCode2EndLoc  = %x \n",
           appCode2StartLoc, appCode2EndLoc);
    
	appCodeOffset = appCode2StartLoc - APP_START_ADDRESS;
	//appCodeSize = appCode2EndLoc - appCode2StartLoc;//dataInitEndLoc - appCodeStartLoc;
	appCodeSize = dataInitEndLoc - appCode2StartLoc;//dataInitEndLoc - appCodeStartLoc;
    fseek( bin, appCodeOffset, SEEK_SET);

#ifdef DEBUG_PRINT
	printf("\nApp Code 2Size = %x %x\n""Reading App Code at offset = 0x%x\n""Placing App Code at offset = 0x%x\n",
			appCodeSize,(dataInitEndLoc - appCode2StartLoc),  ftell( bin ), ftell( finalBin ));
#endif
	fread( buffer, appCodeSize, 1, bin);
    fwrite( buffer, appCodeSize, 1, finalBin);

	fclose(bin);
    fclose(finalBin);
}

unsigned int get_value_from_map_file( char *pFileName, char* pStr )
{
	FILE *map;
	char line[1024];
	char *pSubStr;
	unsigned int value = 0, cnt = 0;
	map = fopen( pFileName,"r+" );

	if(!map)
	{
		printf("\r\n ERROR: Couldn't open the map file\n");
		return 0;
	}

   while (!feof(map))
   {
        fgets(&line[0],1000, map );

        if('#' != line[0])/* Make sure line is NOT commented */
        {
            pSubStr= strstr((const char *)&line[0], pStr );

            if(pSubStr)
            {
#ifdef DEBUG_1_PRINT
                {
                    int i;
                    for(i=0;i<100;i++)printf("%c", pSubStr[i]);
                    printf("\n");
                }
#endif
                pSubStr = strstr(pSubStr,"0x");
				if( NULL == pSubStr )
				{
					fgets(&line[0],1000, map );
					pSubStr = strstr(line,"0x");
					if( NULL == pSubStr )
						return 0;
				}
                pSubStr += 2;
#ifdef DEBUG_1_PRINT
                {
                    int i;
                    for(i=0;i<100;i++)printf("%c", pSubStr[i]);
                    printf("\n");
                }
#endif
                value = string_to_hex( pSubStr );
#ifdef DEBUG_1_PRINT
                printf("GsnStartup_Main is at location 0x%x\n", value );
#endif
            }
			memset(line, 0, 1024);
        }
   }
   fclose( map );
#ifdef DEBUG_PRINT
   printf(" %s location = 0x%x\n", pStr, value );
#endif
   return value;
}

unsigned char char_to_hex(unsigned char c)
{
    unsigned char val = 0;

    if (c >= '0' && c <= '9')
    {
        val = c - '0';
    }
    else if (c >= 'A' && c <= 'F')
    {
        val = c - 'A' + 10;
    }
    else if (c >= 'a' && c <= 'f')
    {
        val = c - 'a' + 10;
    }

    return val;
}


unsigned int string_to_hex( unsigned char *pStr )
{
    unsigned int j;
    unsigned int val = 0;

    for( j = 0; *(pStr+j) != '\0' && *(pStr+j) != ' '; j++ )
    {
        val = val * 16 + char_to_hex(*(pStr + j));
    }

    return val;

}

unsigned int closest_power_of_2( unsigned int value )
{
    unsigned int ret = 1;
    while( ret < 0x80000000 )
    {
        if( value < ret )break;
        ret <<= 1;
    }
    return ret;
}


void createCtrlBlkFile(GSN_BRFLASHLDR_CTL_BLOCK_T *pCtrlBlk)
{

    FILE *fCtrlBlk2;
	char *buf = (char *)malloc(4096);

	memset(buf, 0xff, 4096);
	memcpy(buf, pCtrlBlk, sizeof(GSN_BRFLASHLDR_CTL_BLOCK_T));
	fCtrlBlk2 = fopen("ctrlBlk", "wb+");


    fwrite( buf, 4096, 1, fCtrlBlk2);
}


















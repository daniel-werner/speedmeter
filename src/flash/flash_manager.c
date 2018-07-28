/*******************************************************************************

    Transfer layer of the communication (I2C) 
    ========================================

    Arnold Remete
    rarnold83@gmail.com

    Daniel Verner
    vernerd@gmail.com

  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <inc/flash/flash_manager.h>
#include <msp430x16x.h>
#include <string.h>

/*=============================================================================
   Writing data to flash memory
  ============================================================================*/
//void flash_write( char* srcAddr, char* dstAddr, u16_t size )
//{
//u16_t srcAddr1 = (u16_t)srcAddr;
//u16_t dstAddr1 = (u16_t)dstAddr;
//
//int     i;
//  
//_DINT();
//
//  FCTL2 = FWKEY + FSSEL0 + FN0;                 // MCLK/2 for Flash Timing Generator
//  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
//  FCTL3 = FWKEY;                            // Clear Lock bit
//  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation
//  
//  for ( i = 0; i <= size; i += SEGMENT_SIZE )
//  {
//    FCTL1 = FWKEY + ERASE;                        // Set Erase bit
//    FCTL3 = FWKEY;                                // Clear Lock bit
//    *( dstAddr + i ) = 0;                         // Dummy write to erase Flash segment
//  }
//  
//  FCTL1 = FWKEY + WRT;                           // Set WRT bit for write operation
//  
//  for (i=0; i<size; i++)
//  {
//    *dstAddr = *srcAddr;                        // Sorban irjuk a kivalasztott Szegmens-t a RAM beli ertekekkel
//    srcAddr1 = (u16_t)srcAddr;
//    srcAddr1++;
//    srcAddr = (char*)srcAddr1;
//    dstAddr1 = (u16_t)dstAddr;
//    dstAddr1++;
//    dstAddr = (char*)dstAddr1;
//  }
//
// FCTL1 = FWKEY;                                 // Password, WRT bit torlese a tobbivel egyutt
// FCTL3 = FWKEY + LOCK;                          // Password, LOCK bit beallitasa
// 
// _EINT();
// 
//}

/*----------------------------------------------------------------------------*/

void flash_write( char* srcAddr, char* dstAddr, u16_t size )
{

	u16_t srcAddr1 = (u16_t)srcAddr;
	u16_t dstAddr1 = (u16_t)dstAddr;

	char* segmentAddress = (char*)( ( (u16_t)dstAddr >> SEGMENT_SHIFT ) << SEGMENT_SHIFT );
	
	u16_t segmentsToWrite;// = size >> SEGMENT_SHIFT;
	for( segmentsToWrite = 1; (segmentsToWrite << SEGMENT_SHIFT) + (u16_t)segmentAddress < (dstAddr1 + size); segmentsToWrite++ );

//	if( size % SEGMENT_SIZE > 0 )
//		segmentsToWrite++;
	
	u16_t offset = (u16_t)dstAddr % SEGMENT_SIZE;
	u16_t segmentFreeSize = (u16_t) SEGMENT_SIZE  - offset;
	u16_t segmentWriteSize = size;
	if( segmentWriteSize > segmentFreeSize )
	{
		segmentWriteSize = segmentFreeSize;
	}
	
	char backupData[SEGMENT_SIZE];
	memcpy( backupData, segmentAddress, SEGMENT_SIZE );
	memcpy( &backupData[offset], srcAddr, segmentWriteSize );
	char* segmentSrc = backupData;
	
	int     i;
	
	for( i_t segment = 0; segment < segmentsToWrite; segment++ )	
	{
		FCTL2 = FWKEY + FSSEL0 + FN0;                 // MCLK/2 for Flash Timing Generator
		FCTL1 = FWKEY + ERASE;                    // Set Erase bit
		FCTL3 = FWKEY;                            // Clear Lock bit
		FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation		

		FCTL1 = FWKEY + ERASE;                        // Set Erase bit
		FCTL3 = FWKEY;                                // Clear Lock bit
		*( segmentAddress + segment ) = 0;                         // Dummy write to erase Flash segment		
		
		FCTL1 = FWKEY + WRT;                           // Set WRT bit for write operation
		
		for (i=0; i < SEGMENT_SIZE; i++)
		{
			*segmentAddress = *segmentSrc;                        // Sorban irjuk a kivalasztott Szegmens-t a RAM beli ertekekkel
			srcAddr1 = (u16_t)segmentSrc;
			srcAddr1++;
			segmentSrc = (char*)srcAddr1;
			dstAddr1 = (u16_t)segmentAddress;
			dstAddr1++;
			segmentAddress = (char*)dstAddr1;
		}
		
		memcpy( backupData, segmentAddress, SEGMENT_SIZE );
		size -= segmentWriteSize;
		srcAddr = &srcAddr[segmentWriteSize];
		if( size > SEGMENT_SIZE )
		{
			segmentWriteSize = SEGMENT_SIZE;
		}
		else
		{
			segmentWriteSize = size;
		}
		memcpy( backupData, srcAddr, segmentWriteSize );		
		segmentSrc = backupData;
		
		FCTL1 = FWKEY;                                 // Password, WRT bit torlese a tobbivel egyutt
		FCTL3 = FWKEY + LOCK;                          // Password, LOCK bit beallitasa
		
		_EINT();		
	}
 
}
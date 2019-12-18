// Mailbox Channels.  These are defined at:
// https://github.com/raspberrypi/firmware/wiki/Mailboxes
#define CHANNEL_POWER_MANAGEMENT        0
#define CHANNEL_FRAME_BUFFER            1
#define CHANNEL_VIRTUAL_UART            2
#define CHANNEL_VCHIQ                   3
#define CHANNEL_LEDS                    4
#define CHANNEL_BUTTONS                 5
#define CHANNEL_TOUCH_SCREEN            6
#define CHANNEL_COUNT                   7
#define CHANNEL_PROPERTY_TAGS_ARMTOVC   8
#define CHANNEL_PROPERTY_TAGS_VCTOARM   9

// Mailbox messages
#define MAILBOX_REQUEST                 0

// Mailbox Property Tags.  These are defined at:
// https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface

// Video Core Tag
#define TAG_GET_FIRMWARE_REVISION       0x00000001

// Hardware Tags
#define TAG_GET_BOARD_MODEL             0x00010001
#define TAG_GET_BOARD_REVISION          0x00010002
#define TAG_GET_MAC_ADDRESS             0x00010003
#define TAG_GET_BOARD_SERIAL            0x00010004
#define TAG_GET_ARM_MEMORY              0x00010005
#define TAG_GET_VC_MEMORY               0x00010006
#define TAG_GET_CLOCKS                  0x00010007

// Configuration Tag
#define TAG_GET_COMMAND_LINE            0x00050001

// Shared Resource Management Tag
#define TAG_GET_DMA_CHANNELS            0x00060001

// Power Tags
#define TAG_GET_POWER_STATE             0x00020001
#define TAG_GET_TIMING                  0x00020002
#define TAG_SET_POWER_STATE             0x00028001

// Unique Power Device IDs
#define POWER_SD_CARD                   0x00000000
#define POWER_UART0                     0x00000001
#define POWER_UART1                     0x00000002
#define POWER_USB_HCD                   0x00000003
#define POWER_I2C0                      0x00000004
#define POWER_I2C1                      0x00000005
#define POWER_I2C2                      0x00000006
#define POWER_SPI                       0x00000007
#define POWER_CCP2TX                    0x00000008

// Clock Tags
#define TAG_GET_CLOCK_STATE             0x00030001
#define TAG_SET_CLOCK_STATE             0x00038001
#define TAG_GET_CLOCK_RATE              0x00030002
#define TAG_SET_CLOCK_RATE              0x00038002
#define TAG_GET_MAX_CLOCK_RATE          0x00030004
#define TAG_GET_MIN_CLOCK_RATE          0x00030007
#define TAG_GET_TURBO                   0x00030009
#define TAG_SET_TURBO                   0x00038009

// Unique Clock IDs
#define CLOCK_EMMC                      0x00000001
#define CLOCK_UART                      0x00000002
#define CLOCK_ARM                       0x00000003
#define CLOCK_CORE                      0x00000004
#define CLOCK_V3D                       0x00000005
#define CLOCK_H264                      0x00000006
#define CLOCK_ISP                       0x00000007
#define CLOCK_SDRAM                     0x00000008
#define CLOCK_PIXEL                     0x00000009
#define CLOCK_PWM                       0x0000000A

// Voltage and Temperature Tags
#define TAG_GET_VOLTAGE                 0x00030003
#define TAG_SET_VOLTAGE                 0x00038003
#define TAG_GET_MAX_VOLTAGE             0x00030005
#define TAG_GET_MIN_VOLTAGE             0x00030008
#define TAG_GET_TEMPERATURE             0x00030006
#define TAG_GET_MAX_TEMPERATURE         0x0003000A

// Unique Voltage IDs
#define VOLTAGE_CORE                    0x00000001
#define VOLTAGE_SDRAM_C                 0x00000002
#define VOLTAGE_SDRAM_P                 0x00000003
#define VOLTAGE_SDRAM_I                 0x00000004

// GPU Memory Tags
#define TAG_ALLOCATE_MEMORY             0x0003000C
#define TAG_LOCK_MEMORY                 0x0003000D
#define TAG_UNLOCK_MEMORY               0x0003000E
#define TAG_RELEASEMEMORY               0x0003000F

// Miscellaneous Tags
#define TAG_EXECUTE_CODE                0x00030010
#define TAG_GET_DISPMANX_HANDLE         0x00030014
#define TAG_GET_EDID_BLOCK              0x00030020

// Frame Buffer Tags
#define TAG_ALLOCATE_BUFFER             0x00040001
#define TAG_RELEASE_BUFFER              0x00048001
#define TAG_BLANK_SCREEN                0x00040002
#define TAG_GET_PHYSICAL_WIDTH_HEIGHT   0x00040003
#define TAG_TEST_PHYSICAL_WIDTH_HEIGHT  0x00044003
#define TAG_SET_PHYSICAL_WIDTH_HEIGHT   0x00048003
#define TAG_GET_VIRTUAL_WIDTH_HEIGHT    0x00040004
#define TAG_TEST_VIRTUAL_WIDTH_HEIGHT   0x00044004
#define TAG_SET_VIRTUAL_WIDTH_HEIGHT    0x00048004
#define TAG_GET_DEPTH                   0x00040005
#define TAG_TEST_DEPTH                  0x00044005
#define TAG_SET_DEPTH                   0x00048005
#define TAG_GET_PIXEL_ORDER             0x00040006
#define TAG_TEST_PIXEL_ORDER            0x00044006
#define TAG_SET_PIXEL_ORDER             0x00048006
#define TAG_GET_ALPHA_MODE              0x00040007
#define TAG_TEST_ALPHA_MODE             0x00044007
#define TAG_SET_ALPHA_MODE              0x00048007
#define TAG_GET_PITCH                   0x00040008
#define TAG_GET_VIRTUAL_OFFSET          0x00040009
#define TAG_TEST_VIRTUAL_OFFSET         0x00044009
#define TAG_SET_VIRTUAL_OFFSET          0x00048009
#define TAG_GET_OVERSCAN                0x0004000A
#define TAG_TEST_OVERSCAN               0x0004400A
#define TAG_SET_OVERSCAN                0x0004800A
#define TAG_GET_PALETTE                 0x0004000B
#define TAG_TEST_PALETTE                0x0004400B
#define TAG_SET_PALETTE                 0x0004800B
#define TAG_SET_CURSOR_INFO             0x00008010
#define TAG_SET_CURSOR_STATE            0x00008011

#define TAG_LAST                        0


// External declaration for the mailbox buffer.
// It is allocated in mailbox.c
extern volatile unsigned int mailbox_buffer[36];

// Function prototype
int mailbox_query(unsigned char channel);

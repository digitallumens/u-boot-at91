/*
 * Configuation settings for the SAMA5D3xEK board.
 *
 * Copyright (C) 2012 - 2013 Atmel
 *
 * based on at91sam9m10g45ek.h by:
 * Stelian Pop <stelian@popies.net>
 * Lead Tech Design <www.leadtechdesign.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*Needed to overwrite MAC ADDRESS*/
#define CONFIG_ENV_OVERWRITE 1

#include "at91-sama5_common.h"

/*#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG*/

/* watchdog */
#define CONFIG_HW_WATCHDOG
#define CONFIG_AT91SAM9_WATCHDOG
#define CONFIG_AT91_HW_WDT_TIMEOUT 16

/*
 * This needs to be defined for the OHCI code to work but it is defined as
 * ATMEL_ID_UHPHS in the CPU specific header files.
 */
#define ATMEL_ID_UHP			ATMEL_ID_UHPHS

/*
 * Specify the clock enable bit in the PMC_SCER register.
 */
#define ATMEL_PMC_UHP			AT91SAM926x_PMC_UHP

/* LCD */
#ifdef CONFIG_ATMEL_HLCD
#define CONFIG_SYS_WHITE_ON_BLACK
#endif

/* board specific (not enough SRAM) */
/*#define CONFIG_SAMA5D3_LCD_BASE		0x23E00000*/

/* NOR flash */
#ifdef CONFIG_MTD_NOR_FLASH
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_SYS_FLASH_PROTECTION
#define CONFIG_SYS_FLASH_BASE		0x10000000
#define CONFIG_SYS_MAX_FLASH_SECT	131
#define CONFIG_SYS_MAX_FLASH_BANKS	1
#endif

/* SDRAM */
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE           ATMEL_BASE_DDRCS
#define CONFIG_SYS_SDRAM_SIZE		0x20000000

#ifdef CONFIG_SPL_BUILD
#define CONFIG_SYS_INIT_SP_ADDR		0x318000
#else
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_SDRAM_BASE + 16 * 1024 - GENERATED_GBL_DATA_SIZE)
#endif

/* SerialFlash */

#ifdef CONFIG_CMD_SF
#define CONFIG_SF_DEFAULT_SPEED		30000000
#endif

/* NAND flash */
#define CONFIG_CMD_NAND

#ifdef CONFIG_CMD_NAND
#define CONFIG_NAND_ATMEL
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		ATMEL_BASE_CS3
/* our ALE is AD21 */
#define CONFIG_SYS_NAND_MASK_ALE	(1 << 21)
/* our CLE is AD22 */
#define CONFIG_SYS_NAND_MASK_CLE	(1 << 22)
#define CONFIG_SYS_NAND_ONFI_DETECTION
/* PMECC & PMERRLOC */
#define CONFIG_ATMEL_NAND_HWECC
#define CONFIG_ATMEL_NAND_HW_PMECC
#define CONFIG_PMECC_CAP		4
#define CONFIG_PMECC_SECTOR_SIZE	512
#define CONFIG_CMD_NAND_TRIMFFS
#define CONFIG_CMD_MTDPARTS

#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_RBTREE
#define CONFIG_LZO
#define CONFIG_CMD_UBIFS

#define MTDIDS_DEFAULT "nand0=atmel_nand"
#define MTDPARTS_DEFAULT "mtdparts=atmel_nand:6M(kernel)ro,-(rootfs)"
#endif

#define CONFIG_PHY_MICREL_KSZ9021

/* USB */

#ifdef CONFIG_CMD_USB
#define CONFIG_USB_ATMEL_CLK_SEL_UPLL
#define CONFIG_USB_OHCI_NEW
#define CONFIG_SYS_USB_OHCI_CPU_INIT
#define CONFIG_SYS_USB_OHCI_REGS_BASE		ATMEL_BASE_OHCI
#define CONFIG_SYS_USB_OHCI_SLOT_NAME		"sama5d3"
#define CONFIG_SYS_USB_OHCI_MAX_ROOT_PORTS	3
#endif

#if defined(CONFIG_CMD_USB) || defined(CONFIG_CMD_MMC)
#define CONFIG_FAT_WRITE
#endif

#define CONFIG_SYS_LOAD_ADDR			0x22000000 /* load address */

#ifdef CONFIG_SYS_USE_SERIALFLASH
/* override the bootcmd, bootargs and other configuration for spi flash env*/
#undef CONFIG_ENV_OFFSET
#undef CONFIG_ENV_SIZE
#undef CONFIG_ENV_SECT_SIZE
#undef CONFIG_BOOTCOMMAND
#undef CONFIG_BOOTARGS
#define CONFIG_ENV_OFFSET     0x010000
#define CONFIG_ENV_SIZE       0x010000
#define CONFIG_ENV_SECT_SIZE  0x1000
#define CONFIG_BOOTCOMMAND    "mtdparts default; "                            \
                              "ubi part rootfs; "                             \
                              "ubifsmount ubi0:rootfs; "                      \
                              "ubifsload 0x21000000 /boot/gateway3.dtb; "     \
                              "ubifsload 0x22000000 /boot/zImage; "           \
                              "bootz 0x22000000 - 0x21000000; "               \
                              "ubifsload 0x21000000 /boot/gateway3-old.dtb; " \
                              "ubifsload 0x22000000 /boot/zImage-old; "       \
                              "bootz 0x22000000 - 0x21000000; "               \
                              "reset"
#define CONFIG_BOOTARGS                                                       \
	"console=ttyS0,115200 "                                               \
	"mtdparts=atmel_nand:6M(rescue_kernel)ro,-(rootfs);"                  \
	"spi32766.0:64k(bootloader)ro,64k(env),64k(dtb)ro,-(uboot)ro "        \
	"rootfstype=ubifs ubi.mtd=1 root=ubi0:rootfs"

#elif CONFIG_SYS_USE_NANDFLASH
/* override the bootcmd, bootargs and other configuration nandflash env */
#elif CONFIG_SYS_USE_MMC
/* override the bootcmd, bootargs and other configuration for sd/mmc env */
#else
#define CONFIG_ENV_IS_NOWHERE
#endif

/* SPL */
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_TEXT_BASE		0x300000
#define CONFIG_SPL_MAX_SIZE		0x18000
#define CONFIG_SPL_BSS_START_ADDR	0x20000000
#define CONFIG_SPL_BSS_MAX_SIZE		0x80000
#define CONFIG_SYS_SPL_MALLOC_START	0x20080000
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x80000

#define CONFIG_SPL_BOARD_INIT
#define CONFIG_SYS_MONITOR_LEN		(512 << 10)

#ifdef CONFIG_SYS_USE_MMC
#define CONFIG_SPL_LDSCRIPT		arch/arm/mach-at91/armv7/u-boot-spl.lds
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION	1
#define CONFIG_SPL_FS_LOAD_PAYLOAD_NAME	"u-boot.img"

#elif CONFIG_SYS_USE_NANDFLASH
#define CONFIG_SPL_NAND_DRIVERS
#define CONFIG_SPL_NAND_BASE
#define CONFIG_SYS_NAND_U_BOOT_OFFS	0x40000
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
#define CONFIG_SYS_NAND_PAGE_SIZE	0x800
#define CONFIG_SYS_NAND_PAGE_COUNT	64
#define CONFIG_SYS_NAND_OOBSIZE		64
#define CONFIG_SYS_NAND_BLOCK_SIZE	0x20000
#define CONFIG_SYS_NAND_BAD_BLOCK_POS	0x0
#define CONFIG_SPL_GENERATE_ATMEL_PMECC_HEADER

#elif CONFIG_SYS_USE_SERIALFLASH
#define CONFIG_SPL_SPI_LOAD
#define CONFIG_SYS_SPI_U_BOOT_OFFS	0x030000

#endif

#endif

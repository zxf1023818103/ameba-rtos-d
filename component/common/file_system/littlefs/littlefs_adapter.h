#include "osdep_service.h"
#include "device_lock.h"
#include "flash_api.h"
#include "lfs.h"

#ifndef CONFIG_USE_FLASHCFG
#define LFS_FLASH_BASE_ADDR 0x300000
#define LFS_DEVICE_SIZE 0x100000
#endif

extern struct lfs_config g_lfs_cfg;
extern lfs_t g_lfs;

/**
 * lfs��ײ�flash�����ݽӿ�
 * @param  c
 * @param  block  ����
 * @param  off    ����ƫ�Ƶ�ַ
 * @param  buffer ���ڴ洢��ȡ��������
 * @param  size   Ҫ��ȡ���ֽ���
 * @return
 */
int lfs_diskio_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size);

/**
 * lfs��ײ�flashд���ݽӿ�
 * @param  c
 * @param  block  ����
 * @param  off    ����ƫ�Ƶ�ַ
 * @param  buffer ��д�������
 * @param  size   ��д�����ݵĴ�С
 * @return
 */
int lfs_diskio_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size);

/**
 * lfs��ײ�flash�����ӿ�
 * @param  c
 * @param  block ����
 * @return
 */
int lfs_diskio_erase(const struct lfs_config *c, lfs_block_t block);

int lfs_diskio_sync(const struct lfs_config *c);

#ifdef LFS_THREADSAFE
int lfs_diskio_lock(const struct lfs_config *c);
int lfs_diskio_unlock(const struct lfs_config *c);
#endif